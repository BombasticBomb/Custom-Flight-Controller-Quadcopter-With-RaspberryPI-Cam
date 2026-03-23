from flask import *
import cv2
import time
from threading import *
import traceback
import sys

app = Flask(__name__)
cam_index = 0
Cam_Width = 640
Cam_Height = 480
FPS = 30
Display_WIDTH, Display_HEIGHT = 640, 480

#Set up the function for camera
def Open_Camera(cam_index):
    try:
        Camera = cv2.VideoCapture(cam_index, cv2.CAP_V4L2)
        Camera.set(cv2.CAP_PROP_FRAME_WIDTH, Cam_Width)
        Camera.set(cv2.CAP_PROP_FRAME_HEIGHT, Cam_Height)
        Camera.set(cv2.CAP_PROP_FPS, FPS)

        if Camera.isOpened():
            print(f"✅ Camera initialized!")
            return Camera
    except:
        raise RuntimeError(f"Camera at index {cam_index} not found!")

Camera = Open_Camera(cam_index)

# Threaded Camera Capture
class CameraStream:
    def __init__(self, cam):
        self.cam = cam
        self.frame = None
        self.lock = Lock()
        Thread(target=self.update, daemon=True).start()
        Thread(target=self.capture_frame, daemon=True).start()

    def update(self):
        while True:
            grabbed, frame = self.cam.read()
            if grabbed:
                with self.lock:
                    self.frame = frame
            else:
                time.sleep(0.01)

    def capture_frame(self):
        with self.lock:
            if self.frame is None:
                return None
            return self.frame.copy()

# Stream object
Stream = CameraStream(Camera)

def generate_frames():
    while True:
        try:
            frame = Stream.capture_frame()  # Capture frame (assuming Stream is defined)
            
            if frame is None:  # Skip if no frame is returned
                continue

            # Encode the frame to JPEG
            ret, jpeg = cv2.imencode('.jpg', frame)
            if ret:
                # Yield the encoded frame as a multipart HTTP response for streaming
                yield (b'--frame\r\n'
                       b'Content-Type: image/jpeg\r\n\r\n' + jpeg.tobytes() + b'\r\n')
            
            # Control frame rate with sleep
            time.sleep(1 / FPS)  # FPS defines how many frames per second to display

        except Exception as e:
            print(f"Error in generate_frames: {e}")
            traceback.print_exc()

        
@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/')
def index():
    return render_template("index.html", Display_WIDTH=Display_WIDTH, Display_HEIGHT=Display_HEIGHT)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=6900, debug=False, threaded=True)
