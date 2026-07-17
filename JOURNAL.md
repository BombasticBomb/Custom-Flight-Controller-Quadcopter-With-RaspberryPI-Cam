# 7/16/2026 9:38 PM - Added Superior Landing Legs & Added Extra Mounting Holes (Future Development)

_Time spent: 2h 34m_

<img width="1149" height="729" alt="image" src="https://github.com/user-attachments/assets/141da5e8-1b58-4f86-86f5-53739f99d774" />
I added 2 extra mounting holes so I can add on new modules in the future for items like Gimbal Camera, GPS, Drop mechanism, etc.

<img width="1000" height="515" alt="image" src="https://github.com/user-attachments/assets/4dc7a503-dce1-4675-8990-23432ff40aec" />
The previous landing leg design had a center of gravity that was relatively high, and standing on tiny legs with little surface area. This design fixed it by making the legs shorter, and adding a smooth pad at the bottom
that'll also be reinforced with shock absorbing foam. Even added some tall standoffs on the arms that may or may not allow me to completely take of the landing legs and land on those!

# 6/26/2026 10:25 PM - Switched Flight Controller From MPU6050 to MPU9250

_Time spent: 21m_

<img width="1600" height="899" alt="image" src="https://github.com/user-attachments/assets/799c4ac0-c287-42d7-a2b7-cb84e2f1e6d5" />
Updated Flight Controller Code for MPU9250 Since I previously tested and wrote code with a MPU6050 because I physically had the sensor, I now decided to update the code to the new and more advanced 
MPU9250. Today’s session was mostly about getting the sensory data (Roll, Pitch, Yaw) from the sensor, and I haven’t implemented a PID loop yet, and I’ll focus on that next, as well as implementing the 
connections from the custom PCB.
<img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/cab0059d-ea0a-4a8e-adad-0b5aa55f1da3" />

# 6/19/2026 1:30 PM - Added Smooth Underside to the Arm and added Electronics Housing

_Time spent: 22m_

<img width="1268" height="758" alt="image" src="https://github.com/user-attachments/assets/cf81be26-77fd-4bba-b437-f4b71e000bd5" />
I made the arms of the drone thicker so it is more resistant to crashes, which may happen quite a bit during initial PID tuning and testing.
<img width="1271" height="755" alt="image" src="https://github.com/user-attachments/assets/2ac10c67-d928-4ba2-9527-7caab304371a" />
Not only that, I also added a small cutout on the top to house the main electronics, including the battery, the Raspberry PI, and also the custom PCB.
<img width="1199" height="773" alt="image" src="https://github.com/user-attachments/assets/f339330d-11ec-4512-8e6f-486c1a7318d8" />


# 6/11/2026 9 PM - More changes to the 3D model of the Drone

_Time spent: 1.5h_

Today, I completely redesigned the chassis of the drone to better suit my needs, as the previous one was too small.
![image](https://stasis.hackclub-assets.com/images/1781213142716-jm1z42.png)

Kept the drone mounting holes the same for the brushless motors, but for simpler building also added screw holes for the 4 arms to attach to the main body.
![image](https://stasis.hackclub-assets.com/images/1781213202038-4pw80q.png)
Also further tweaked the brushless motor part.
![image](https://stasis.hackclub-assets.com/images/1781213241385-vs5smg.png)

In the bottom, added landing legs to provide better stability.
![image](https://stasis.hackclub-assets.com/images/1781213291150-uvns13.png)
![image](https://stasis.hackclub-assets.com/images/1781213316718-xz8g2e.png)

To house the electronics, I added a small area on the top to hold the parts.
![image](https://stasis.hackclub-assets.com/images/1781213353701-xb3eld.png)


# 6/10/2026 10 PM - Designing New Drone Chassis

_Time spent: 2.5h_

In this session, as per the instructions, I decided to make a more stable version of the drone, and this time, it will be fully 3D printed in carbon fiber instead of aluminium to save costs. Since my 3D printer can't print carbon fiber, I will be using Hack Club PrintingLegion. 
![image](https://stasis.hackclub-assets.com/images/1781129874856-9uzzh7.png)
For the main drone body, I took inspiration from this YouTube video. 
Link: https://www.youtube.com/watch?v=jeBfLHX1kos&t=72s

However, that'd not fit my requirements, so I will also be adding proper M3 holes and a through-hole for my Bushless motors, and this video helped a lot.
Link: https://www.youtube.com/watch?v=4bDNXpWQaW4
![image](https://stasis.hackclub-assets.com/images/1781130056879-7fp3xl.png)


Lastly, I think I'll make some more changes to the drone to make it even sturdier, like adding some pressure absorbers at the bottom of the legs.


# 4/18/2026 6 PM - Finish Designing Custom PCB

_Time spent: 2.5h_

While I was working on the PCB, I decided it's out of my scope to use bare metal chips for the sensors, so in order to improve electronic noise and have a better chance of the PCB working, I decided to switch out the sensor chips for modules. 
![image](https://stasis.hackclub-assets.com/images/1776535204736-pji7hj.png)
Also, due to size constraints, I decided to go with Arduino Nano instead of the big Arduino UNO, as it better fits the PCB. For future developments, I also added lots of header pins connected to the digital and analog pins on the Arduino, so I can expand my capabilities in the future. Similarly, I also added some power pins to power those sensors.
![image](https://stasis.hackclub-assets.com/images/1776535300926-nwz8xy.png)
Lastly, I made the PCB and made all the traces. I went with thicker 4mm traces for the Motor power distribution, as more current will flow through them, and everything else with normal 0.025mm traces.
![image](https://stasis.hackclub-assets.com/images/1776535399958-vzd0is.png)
Here's the final PCB:
![image](https://stasis.hackclub-assets.com/images/1776535449528-0ceizj.png)

# 4/7/2026 3 AM - Flight Controller PCB V1

_Time spent: 2h_

I decided to start working on a custom PCB because, without it, the complexity isn't high enough. This is my first time making a custom PCB, so I gave it my best shot :)
![image](https://stasis.hackclub-assets.com/images/1775531093412-96yffh.png)

I decided to use KiCad for this, and I used bare chips instead of modules for now. Apparently, there are a lot of issues with electronic noise for quacopter PCBs, so I had to do a lot of research on where and how to place components. And, for better sensor readings, I also had to put a 10K resistor, decoupling capacitors, and a MOSFET for level-shifting.

![image](https://stasis.hackclub-assets.com/images/1775531121795-v1llih.png)
Still not sure whether I will continue this setup, as the electronic noise is a big deal. Might end up switching that out for the GY-91 module itself.


# 3/23/2026 3 AM - PID Loop V1 (Stabilization)

_Time spent: 1h_

In order for a drone to be stable, it needs a feedback loop system that constantly tries to keep it stable, thus keeping its angle 0*. One industry standard way is to implement a PID loop. A PID loop consists of 3 different parts: the proportional, the integral, and the derivative, and the PID controller is the sum of all these 3 controllers. I plan to create a PID controller for each dimension of the drone.
![image](https://stasis.hackclub-assets.com/images/1774235952619-k8qh70.png)
Source: https://en.wikipedia.org/wiki/Proportional%E2%80%93integral%E2%80%93derivative_controller

After some research on YouTube about how a PID controller works, I tried creating my own loop in the stabilization part of my firmware and called the stabilize() function which has the controller. As of right now, I don't have much of an idea as to how the motors behave and how much thrust increases as I increase speed in percentage, so I just made it increase and decrease thrust based on the values from the PID loop. When I actually build the physical drone, it'll have the PID constants tuned, and I'll also tune the thrust increase/decrease for optimal flight.
![image](https://stasis.hackclub-assets.com/images/1774235903144-oo93fk.png)


# 3/19/2026 4 AM - Basic Gyroscope & Accelerometer Sensor Fusion along with Throttle Control

_Time spent: 3.5h_

After choosing the parts for the drone, I decided to start working on the flight controller. In my previous journal logs, I've already shown getting the gyroscope roll, pitch, and yaw values, but as I learned during my research, the gyroscope is subject to drift. The solution - fusing data from the gyroscope along with roll and pitch values gained by integrating the angular velocity given by the accelerometer to get angles, with the gyroscope contributing 98%, while the accelerometer 2% for corrections.

![image](https://stasis.hackclub-assets.com/images/1773894588188-me5n5q.png)
The yaw values cannot be corrected as it would require a magnetometer, which I will use in the final build by replacing the MPU6050 with an MPU9250. 
![image](https://stasis.hackclub-assets.com/images/1773894843603-6uyued.png)


I also started writing code for reading signals from the radio receiver and its corresponding actions on the motors, which I've defined as servos in the code.
![Channels](https://stasis.hackclub-assets.com/images/1773894688320-mes3dt.png)

![image](https://stasis.hackclub-assets.com/images/1773894792856-d98bn3.png)


# 3/18/2026 4 AM - Designing 3D Model of Drone

_Time spent: 2h_

In the past 2 hours, I designed the basic 3D outline of the drone in TinkerCAD to be approved by Hack Club. I chose the parts that I will be using and looked for 3D models online, and if I found them, I used them in the design. Otherwise, I tried to mimic the actual part with TinkerCAD shapes and labels. Things to note: this may be subject to change as I build the project and make important decisions.
![image](https://stasis.hackclub-assets.com/images/1773806495093-j3iobu.png)


If looking for my 3D model to review and approve my project, please look in the releases section. Due to the large file size of the .step file when extracted from the original STL file, it had to be uploaded to releases. 
![image](https://stasis.hackclub-assets.com/images/1773806522670-wy8610.png)


# 3/17/2026 9 PM - Deciding Propeller, Motor & Battery Sizes

_Time spent: 3h_

In this session, I finished researching the different configurations for the drone and chose the most efficient for my purpose. I decided to stick with 1400kv Brushless motors for a good balance between speed and efficiency, and chose 4 pieces to buy on Amazon.
![image](https://stasis.hackclub-assets.com/images/1773782883657-xkhlok.png)
Then, I chose a 4000mAh 3S Li-po battery for a good flight time and also 4 30A ESCs separately for a better price. Ended up with an 8x4.5 propeller size for the final drone.
![image](https://stasis.hackclub-assets.com/images/1773782997945-qfr7qd.png)
Finally, started working on choosing a frame for the drone. I am not sure whether I should buy a frame or print one on my 3D printer, but let's see.

Considering this one:
![image](https://stasis.hackclub-assets.com/images/1773783095039-14muix.png)
Source: https://www.printables.com/model/250067-drone-frame


# 3/17/2026 4 AM - Choose Parts

_Time spent: 2.5h_

In the last 2 and a half hours, I brainstormed ideas as to how to build the drone in real life, and decided to choose electronics parts for each job. I decided to go with 1400KV brushless drone motors along with 30A ESCs, along with a radio controller and transmitter for communication. I decided to build a custom IMU with Arduino and MPU6050, and I haven't decided yet on how to build the structural part of the drone. I also started tinkering with the MPU6050 to start building the PID controller for the IMU. 

![image](https://stasis.hackclub-assets.com/images/1773720346633-ba1z0l.png)

![image](https://stasis.hackclub-assets.com/images/1773720803594-j6lp8g.png)



