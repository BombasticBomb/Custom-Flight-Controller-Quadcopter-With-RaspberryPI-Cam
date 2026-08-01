# 8/1/2026 1:25 PM - Soldering the Drone Battery

_Time spent: 3h 13m_

Confident after soldering the last batch of batteries. I decided to start soldering the RS50 Reliance batteries I bought for the actual drone. It started of really rough, with me burning my hands a couple times. So I tried like last time to not use flux, which improved a little bit, but not enough to make it work. Then, I finally ran out of solder, which made me open my new pack of solder I bought. And miraculously, the solder started working. I realized that this new solder had a flux core, which made my life way more easier, and I was able to finish soldering all the batteries.

I hooked it up to my Arduino and ESC, and it was providing nice power.
<img width="3024" height="4032" alt="IMG_0028" src="https://github.com/user-attachments/assets/4e845e1a-7554-4062-89e9-f01d0bc6cd57" />
<img width="3024" height="4032" alt="IMG_0027" src="https://github.com/user-attachments/assets/1fe58f9f-fd94-4799-ae37-5294cc4ed5a7" />

Just to be sure, I also measured the voltage of the batteries, and since they were almost fully charged, they showed 12.3V, which is normal for a 3S cell.
<img width="3024" height="4032" alt="IMG_0029" src="https://github.com/user-attachments/assets/c7eeaa88-a06f-4bb1-ab60-6f30053baba5" />

I also connected it to the smart charger after attaching the load balancing wires, and the 3 cells were all charging normally.
<img width="3024" height="4032" alt="IMG_0030" src="https://github.com/user-attachments/assets/268c75f7-d991-427f-b7e3-4425d3f69abb" />

# 7/27/2026 3:40 PM - Designing a second low-profile Chassis for Drone.
I wanted to add a smaller low-profile chassis for the drone if I ever fly it with no big landing legs or payload or cameras, and so I designed another chassis that I'll also manufacture soon.
<img width="1182" height="672" alt="image" src="https://github.com/user-attachments/assets/ee63d8d0-2d9c-49ad-92cc-c61b0a212b91" />
<img width="1902" height="794" alt="image" src="https://github.com/user-attachments/assets/a88bce9a-0f3e-4442-9297-ad9c0319218f" />
<img width="1919" height="879" alt="image" src="https://github.com/user-attachments/assets/65283aea-db1a-4f53-ba48-04d757ff9f84" />


# 7/24/2026 10:58 PM - Soldering 1st batch of batteries.

_Time spent: 2h 26m_

Today, my order from 18650 battery store for 3 21700 Li-ion cells came in. These are very beefy cells with a max pulse current of 70A and 5000mah capacity, so should be more than enough for my drone project. 
<img width="700" height="933" alt="image" src="https://github.com/user-attachments/assets/6773ed9f-a30b-4acf-8a8d-b1befe19468a" />
But, since I've never soldered batteries together before and I can't afford a spot solder right now, I decided to test solder on some old 18650 cells I had, and that's what I did.
<img width="700" height="933" alt="image" src="https://github.com/user-attachments/assets/72f77009-2f98-4122-9c2d-1a83a6caf021" />
Overall, it started off pretty rough as the solder was not sticking to the ends of the cells no matter what I tried. Then, i figured that it worked better if I didn't use any flux, which'd to me was counterintuitive as flux makes the solder stick. But anyways, I tried without and managed to solder all the wires together, and it gave me a nice 12V on the 3S cell.
<img width="700" height="933" alt="image" src="https://github.com/user-attachments/assets/7924936c-a82d-4a4e-b6a8-d1ff03a68e41" />
To interface with the smart charger I also bought, I also attached a 4 pin connector to the battery for load-balancing smart charging. Overall it works great and the charger can individually tune the voltages of each cell for protection.
<img width="571" height="933" alt="image" src="https://github.com/user-attachments/assets/c7baa17a-cb12-41eb-8032-22b9e4ece54c" />
<img width="700" height="933" alt="image" src="https://github.com/user-attachments/assets/b0290a45-75da-4329-9931-a8499cb64b89" />
Hopefully in the next log I'd be able to finish soldering the actual 21700 cells to make another, much beefier pack that I'll actually use on the drone. This was for first-time practice and getting to actually know how its done!





# 7/23/2026 7:29 PM - Added Secondary Landing Legs.

_Time spent: 3h 21m_

Firstly, I decided to write the Motors mixer function for the drone with a standard Quad X setup, so I can just call it in the main loop and it'll update the motor values on each iteration according to the PID values.
<img width="968" height="368" alt="image" src="https://github.com/user-attachments/assets/71bee40e-fbb5-415c-9b8c-32709f5e6a27" />
<img width="780" height="106" alt="image" src="https://github.com/user-attachments/assets/c1338c15-fe76-489d-aa34-cc90ccd79c53" />

Then, I write a simple PID function that I'll be using in the main loop. This is not yet a cascaded PID controller, but it's a start. I made some state variables and wrote the function to add up the proportional, integral and derivative part.
<img width="1125" height="448" alt="image" src="https://github.com/user-attachments/assets/a78ca2d4-e061-447b-9acc-e97a5302ef82" />

To then feed data into the PID function, I used the BolderFlight Invensense Arduino library to interface it with the MPU9250, and get all the data.
<img width="845" height="261" alt="image" src="https://github.com/user-attachments/assets/264e9409-4e41-4e53-975b-c2336f464489" />
<img width="439" height="92" alt="image" src="https://github.com/user-attachments/assets/d89769e4-9d75-4407-ba3f-fdd96fc52462" />

All IMU sensors have noise in the data, but since an Arduino is a relatively weak microcontroller running at only 16Mhz, I decided to use a light filter called a Mahony filter, and used the MahonyAHRS library to implement it in my code. If i ever upgrade the flight controller hardware, I'll then manually implement a Extended Kalman Filter, but right now it is too expensive for the Arduino.
<img width="863" height="253" alt="image" src="https://github.com/user-attachments/assets/a9e361b2-f3d4-4f56-8025-98d8c846cd04" />

I also decided to set the PID loop at a 500Hz rate, which is also how I calculated dt in my code.
<img width="861" height="217" alt="image" src="https://github.com/user-attachments/assets/fb0dfdf3-b7b4-4355-9754-1e82c892d56f" />


Finally, I made a PID controller for each axis of the drone and ran the mixer function at the end of the loop. Also made it that the integral portion will go to 0 when the drone is on the ground to prevent integral buildup when the drone is stationary.
<img width="896" height="286" alt="image" src="https://github.com/user-attachments/assets/2beecc00-cb0f-4b5c-9cd8-67321269bc38" />

# 7/21/2026 11:34 PM - Added Secondary Landing Legs.

_Time spent: 57m_

I added some small DJI Mini style landing legs to the drone, so that if I ever want I can take the big landing legs off and just have a low profile setup.
<img width="1210" height="534" alt="image" src="https://github.com/user-attachments/assets/5c2e5df5-b1e3-4d53-9aff-5593bcd419cb" />
<img width="1161" height="549" alt="image" src="https://github.com/user-attachments/assets/f0da94c7-e94f-44fe-9bf2-d7b771583c5f" />
<img width="1202" height="674" alt="image" src="https://github.com/user-attachments/assets/d3cca06b-afc8-4c2a-8e80-85dc597b540e" />

# 7/20/2026 10:28 PM - Started writing code to interface the Arduino with the RC transmitter.

_Time spent: 2h 47m_

Firstly, I decided to do some research about the channel configuration and how to read PWM signals from the receiver. Originally, I thought I was going to use the IbusBM library, but apparently my receiver didn't support it.
<img width="1919" height="847" alt="image" src="https://github.com/user-attachments/assets/aee3893d-1b5c-40e9-9bcc-897fb29919a9" />

To solve this problem, I thought I'd use Arduino Nano's hardware interrupts, but the Nano only had 2 pins, and I needed a minimum for my 4 channels: Throttle, Pitch, Yaw, and Roll. Then, I found out about something called pin change interrupts, but those required manual memory address and pin registry configuring, and thankfully the Arduino PinChangeInterrupt library took care of that for me.
<img width="1160" height="397" alt="image" src="https://github.com/user-attachments/assets/b4e88ca3-5096-4f5d-8dea-8a8d4f669ddf" />

Not only that, but I also found out that RC transmitters like these don't have perfect PWM signal outputs, as I measured with the arduino. To fix that and scale it to the perfect 1000um-2000um range needed for the ESCs to work well, I decided to log the range of values that each of the 4 channels output, and used the arduino map() function to scale it to the desired range and constrained it with the constrain() function. This worked remarkably well and I tested it with a Brushless motor and it worked well.
<img width="719" height="258" alt="image" src="https://github.com/user-attachments/assets/1872b9d3-a235-4796-b68f-cf5f85f02581" />
<img width="568" height="124" alt="image" src="https://github.com/user-attachments/assets/0ebd69e6-ac06-4cd7-8e2b-56e0ddf70e30" />


# 7/19/2026 18:03 PM - Completely changed the thickness of parts as Carbon Fiber Nylon is strong enough, and added many decoration holes and patterns to vastly reduce weight.

_Time spent: 3h 19m_

<img width="1706" height="702" alt="image" src="https://github.com/user-attachments/assets/5a9de6c2-abc0-4d23-b40f-d7c917860265" />
I added these design holes found in other drone chassis kits that not only made it look nicer, it reduced a lot of weight without making the arms that much weaker, as carbon fiber is a very strong material. This reduced the weight of the individual arms from 37g to 25g, as per the printing settings I used. 

<img width="449" height="531" alt="image" src="https://github.com/user-attachments/assets/0d283936-0bf7-474e-ad96-b90c5d63ec18" />
Also added some cutouts to the chassis that didn't drastically reduce weight, as the chassis is relatively thin. However, this'll allow me to tie things onto the drone if I ever need to do so in the future, and it also looks nice on the drone chassis.

<img width="1293" height="467" alt="image" src="https://github.com/user-attachments/assets/bc861eae-7d36-4839-bfa0-1f996200ef41" />
Similarly, added cutouts to the bottom legs and thinned the pads out a bit too to reduce weight. This resulted in almost 50g of weight reduction.

<img width="1081" height="651" alt="chip" src="https://github.com/user-attachments/assets/ef7aa236-dce8-4b5b-aab3-3f944ded3d1e" />
I was having anxiety about flexing where the motor attaches to the arms, so I made it thicker at just that part. I also added a smooth hilly part that should make it really strong.

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



