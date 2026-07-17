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

# 6/18/2026 11 PM - Added Smooth Underside to the Arm and added Electronics Housing

_Time spent: 1h 26m_

<img width="1004" height="476" alt="image" src="https://github.com/user-attachments/assets/612a4224-f60f-449f-93eb-2c0455087e59" />
Added Landing Legs for the Drone: After I moved the project from stasis, I added a better landing leg for the drone and added M3 holes to screw them to the main body. After this, I’ll fix the BOM in my GitHub as well as finish up the Raspberry PI Camera code and submit it for review. Should be almost done.
<img width="995" height="652" alt="image" src="https://github.com/user-attachments/assets/8ec7eaaa-c7c9-4a88-b821-821d035fec59" />
