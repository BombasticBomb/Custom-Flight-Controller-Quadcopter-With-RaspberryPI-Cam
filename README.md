## 🚁 Custom Drone Flight Controller
Arduino + MPU9250 based Flight Controller for Quadcopter!
This project is a custom-built quadcopter drone that uses an Arduino-based flight controller with an MPU9250 IMU for stabilization. The system is designed from scratch and I am currently working on the hardware, firmware, and the system architecture utilizing a combination of Arduino & Raspberry PI.
A major focus of this project is the 📷 Raspberry Pi Camera system — used for:
-🎥 Real-time video streaming

## 🖼️ 3D Model
<img width="1550" height="836" alt="drone" src="https://github.com/user-attachments/assets/44a0481e-011e-4183-ab1a-c5b240e199d9" />

 If looking for my 3D model to review and approve my project, please look in the releases section. Due to the large file size of the .step file when extracted from the original STL file, it had to be uploaded to releases.
<img width="1287" height="762" alt="image" src="https://github.com/user-attachments/assets/9f28285b-bbc9-417f-9daf-f7c4b00d5090" />

## 💡 Inspiration
This is my hack club project to build a quadcopter from scratch with a custom flight controller with Arduino &amp; MPU9250. Growing up, I'd watch many science and engineering videos online; I've always been a science kid who spends his time watching astronomy, engineering, etc type videos. And, I've seen many people make videos about making drones, and I'd dream, but I'll tell myself - "They're on another level, I cannot reach that yet". However, in 2026, in my 9th-grade year, I believe I finally have the capability and, of course, the passion to pull it off. I present my first attempt to build my own custom flight controller, as well as PID stabilization, as part of this drone project. I did this project to challenge myself in learning the ins and outs of how a quadcopter actually works, and also combine my skills in hardware, electronics, and embedded programming to create something unique and not just follow a tutorial.
<img width="1001" height="719" alt="image" src="https://github.com/user-attachments/assets/24605bc7-c428-4ba1-9c08-294bb76b4471" />

 ## 🧠 What Makes This Project Unique
Unlike most hobbyist drones that rely on prebuilt flight controller firmware (Betaflight), my project implements a fully custom flight controller using Arduino & mpu9250 that I had to do a lot of research to actually learn how it works, and I am working on developing it into a fully functioning firmware. Along with that, I am utilizing a novel method to stream video transmission using a USB camera and the Raspberry Pi using a Python script that uses OpenCV to play video on a web dashboard hosted in Flask and streamed with Flask-socketio. This is a unique method as I offload the low-level control to the Arduino, while I implement advanced features such as a camera (and hopefully in the future GPS, ultrasonic sensors, etc) through the more powerful Raspberry Pi, which actually runs the Linux Operating System.
- Arduino --> Handles low-level flight control and sensor processing
- Raspberry Pi --> Handles higher-level features like video streaming
**Note: The utilization of onboard wifi on the Raspberry Pi does mean the video transmission range is limited, and beyond that range, we have to rely solely on radio.

## ⚡ Wiring Diagram
<img width="1307" height="805" alt="image" src="https://github.com/user-attachments/assets/c730b36d-18da-4402-9e17-9dd2fa1ceded" />

| # | Arduino --> MPU9250 |   |             |
| - | ----------------- | - | ----------- |
|   | **Arduino**       | --> | **MPU9250** |
|   | 5V                | --> | 5V          |
|   | GND               | --> | GND         |
|   | A4                | --> | SDA         |
|   | A5                | --> | SCL         |

| # | Arduino --> RC Receiver |   |                 |
| - | --------------------- | - | --------------- |
|   | **Arduino**           | --> | **RC Receiver** |
|   | 5V                    | --> | 5V              |
|   | GND                   | --> | GND             |
|   | RX                    | --> | IBus            |

| # | Arduino --> ESC |   |         |
| - | ------------- | - | ------- |
|   | **Arduino**   | --> | **ESC** |
|   | 5V            | --> | 5V      |
|   | GND           | --> | GND     |
|   | 3             | --> | ESC1    |
|   | 4             | --> | ESC2    |
|   | 5             | --> | ESC3    |
|   | 6             | --> | ESC4    |

Custom PCB:
<img width="1175" height="788" alt="image" src="https://github.com/user-attachments/assets/4022f9d7-cd2c-42dd-9d95-3de0f98c9033" />
<img width="799" height="647" alt="image" src="https://github.com/user-attachments/assets/474f7709-70ed-4500-a96a-6f5e19cf00ba" />
<img width="1065" height="599" alt="image" src="https://github.com/user-attachments/assets/d90e29e1-4f88-41d8-8d7b-a8cb62e65f28" />

Note: Brushless motors need Electronic Speed Controllers (ESCs) to operate. The ESC's themselves are part of the wiring diagram and are powered by the Arduino. It is crucial to note the motors themselves, and the Arduino also gets power from the main battery. The reason this configuration was required is that the Arduino converts the 11.1V on the 3S battery to 5V and supplies it to the other electronics.

## 📦 Bill of Materials

| Name | Purpose | Quantity | Total Cost (USD) | Link | Distributor |
|------|---------|----------|------------------|------|-------------|
| JLCPCB Order + Shipping | I'll be manufacturing my custom PCB from JLCPCB. | 1 | 4.30 | https://cart.jlcpcb.com/quote?stencilLayer=2&stencilWidth=100&stencilLength=100&stencilCounts=5&plateType=1&spm=Jlcpcb.Homepage.1010 | JLCPCB |
| Male & Female Headers | It'll be used to connect things on the PCB. | 1 | 3.82 | https://www.aliexpress.us/item/3256805860047704.html?spm=a2g0o.cart.0.0.347038daeMTzKz&mp=1&pdp_npi=6%40dis%21USD%21USD%202.56%21USD%202.48%21%21USD%202.48%21%21%21%40210311a017759634443543759ee48c%2112000035473388533%21ct%21US%212842570567%21%211%210%21&_gl=1*hb3qht*_gcl_aw*R0NMLjE3NzU5NjE3NjQuQ2p3S0NBanc0dWZPQmhCa0Vpd0FmdUM3LVN4Wk1VVThydWVYUFUtRldvTkVNRkdlU1g5UkxIbzBkY1JpdmRNRlpicjZjYzA5cVpvUTNCb0Nxb3dRQXZEX0J3RQ..*_gcl_au*MTA5ODg3MDg0OS4xNzc0MTUwMTU1*_ga*MTgzMDIyMjAwNi4xNzc1OTYyMjM1*_ga_VED1YSGNC7*czE3NzU5NjIyMzQkbzEkZzEkdDE3NzU5NjM0NTAkajIzJGwwJGgw&gatewayAdapt=glo2usa | AliExpress |
| XT90 Male to XT60 Female connector for battery | This converts the XT90 on the battery to XT60 so it can be connected to the PCB. | 1 | 1.00 | https://www.aliexpress.us/item/3256809870073827.html?spm=a2g0o.productlist.main.2.6ec677250MQCzi&algo_pvid=cdafdfe4-f998-4543-be9e-b0735b928c6e&algo_exp_id=cdafdfe4-f998-4543-be9e-b0735b928c6e-1&pdp_ext_f=%7B%22order%22%3A%22124%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%2111.54%210.99%21%21%2179.06%216.79%21%402103212317741506875214915ecc89%2112000050973827105%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Af626b5c8%3Bm03_new_user%3A-29895%3BpisId%3A5000000197847475&curPageLogUid=TNcZo29qJmvN&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005010056388579%7C_p_origin_prod%3A | Aliexpress |
| Drone Frame | This will be the frame of the drone that'll hold all the parts and be the structural support. I have decided to use aliminium for the drone, but I'm still at the designing phase for it. | 1 | 16.42 | https://www.aliexpress.us/item/3256808348360675.html?spm=a2g0o.productlist.main.9.723a23ddzBsgBr&algo_pvid=08be54b7-91ea-4690-8401-7f548ac3c948&algo_exp_id=08be54b7-91ea-4690-8401-7f548ac3c948-8&pdp_ext_f=%7B%22order%22%3A%22903%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%212.24%211.13%21%21%2115.25%217.73%21%402101e2b217759625642954949e169c%2112000045600976575%21sea%21US%212842570567%21ACX%211%210%21n_tag%3A-29919%3Bd%3A3fe947d3%3Bm03_new_user%3A-29894%3BpisId%3A5000000204591263&curPageLogUid=eTSY5SnT7m82&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005008534675427%7C_p_origin_prod%3A | Amazon |
| CNHL G+Plus 3000mAh 11.1V 3S Lipo Battery | This will be the battery for the drone and it will power it. | 1 | 19.99 | https://chinahobbyline.com/products/cnhl-gplus-series-3000mah-11-1v-3s-70c-lipo-battery-with-xt90-plug?variant=42646820520150&country=US&currency=USD&utm_medium=product_sync&utm_source=google&utm_content=sag_organic&utm_campaign=sag_organic&utm_source=google&utm_medium=paid-search&utm_campaign=pmax-all-us&gad_source=1&gad_campaignid=20679418975&gbraid=0AAAAADLM11YyMvG3qD_NDLKjEs94c2Nh8&gclid=CjwKCAjwg_nNBhAGEiwAiYPYA0O9yFw_d91XaKJ55l3Hq386bwSOqDSKlXSrVLVT1E4AFfyVf2CtmxoCuc0QAvD_BwE | China Hobbyline |
| 1400KV Brushless Motors | These will be the motors that generate lift for the drone.  | 4 | 33.40 | https://www.robotshop.com/products/e-s-motor-xxd-a2212-brushless-motor-160w-mounting-base-kits-kv-1400?qd=f82c3b340c3f619c5c40ab447d536a69 | Robotshop |
| Raspberry PI 4 4GB | This will be used to connect the usb camera and for video transmission. I already have this, so I will not need to buy it. | 1 | 0.00 | https://www.centralcomputer.com/raspberry-pi-4-model-b-rpi4-modbp-4gb-4gb-ddr4-ram-bcm2711-soc-usb-3-0-poe-enabled.html | Central Computers |
| Arduino Nano | This will be running the flight software and controlling the motors. I already have this, so I will not need to buy it. | 1 | 0.00 | https://www.amazon.com/ELEGOO-Presoldered-Compatible-Arduino-Microcontroller/dp/B0F6Y7GS4Q/ref=sr_1_3?crid=1WI33AN7K85LS&dib=eyJ2IjoiMSJ9.MIYfXZ6wi0Vk6H_aXvUqPsaVmGqwhO_Uv02Fkr2rtnyjHmw6vUpjkGNdn29kkFnYleTyu93FZm5UZJJe_eWCPlWYyrWUN4coKcwz0-h7cjBxN_Xxja2jrhTP0rn1gihJIvdIjvErBPzCuiLMqGQZwJAUoA6FF24FRGTj6rRStLesiVjahW7XgAUWyCSem2_TOLjxPilnrbsep46oDrqeT30r69GJ6CTw5QobnYW92tk.sUco9rijTMiM7zkJXQbO3_IAQdr1UIemyin8BEwZDtg&dib_tag=se&keywords=arduino+nano&qid=1775963764&sprefix=arduino+u%2Caps%2C565&sr=8-3 | Amazon |
| GY-91 Board with both MPU-9250 & BMP180 | This will the the 9 Axis Flight Controller for the drone (Gyroscope, Accelerometer, Magnetometer, Altometer) | 1 | 8.79 | https://www.amazon.com/gp/product/B0CMQSYR2Y/ref=ewc_pr_img_1?smid=A2YE8NZRGVUJGM&psc=1 | Amazon |
| 8x4.5 Inch RC Drone Propellers | These will be used on the brushless motors to provide lift for the drone. I am buying 8 pieces instead of 4 in case some breaks during testing. | 1 | 10.79 | https://www.amazon.com/gp/product/B07YYV2JL4/ref=ox_sc_act_title_6?smid=A1THAZDOWP300U&psc=1 | Amazon |
| 3S Li-po Battery Charger US Plug | This will be used to charge the battery for the drone. | 1 | 11.61 | https://www.aliexpress.us/item/3256805934795867.html?spm=a2g0o.productlist.main.5.5574546cUwMiyN&algo_pvid=89444658-625e-497a-9161-8886d6b7c66c&algo_exp_id=89444658-625e-497a-9161-8886d6b7c66c-4&pdp_ext_f=%7B%22order%22%3A%2236%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%2114.61%219.61%21%21%2114.61%219.61%21%402103122117759642911075864e8f33%2112000035846729871%21sea%21US%212842570567%21ACX%211%210%21n_tag%3A-29919%3Bd%3A3fe947d3%3Bm03_new_user%3A-29894%3BpisId%3A5000000203531302&curPageLogUid=vJ4Xx6RcBVto&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005006121110619%7C_p_origin_prod%3A | AliExpress |
| MicroZone MC6C Mini V2 2.4G 6CH Controller Transmitter w/ Receiver | This will be used for the radio communication with the drone. | 1 | 35.24 | https://www.aliexpress.us/item/3256807243819244.html?spm=a2g0o.productlist.main.35.4ab577e7dXjt8P&algo_pvid=51c9d117-d897-430c-8a26-849a75ee0eb6&algo_exp_id=51c9d117-d897-430c-8a26-849a75ee0eb6-34&pdp_ext_f=%7B%22order%22%3A%22543%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%21118.36%2135.24%21%21%21804.10%21239.42%21%40210319b717759622763998627ecd25%2112000040726294727%21sea%21US%212842570567%21ACX%211%210%21n_tag%3A-29919%3Bd%3A3fe947d3%3Bm03_new_user%3A-29894%3BpisId%3A5000000203531302&curPageLogUid=uuj3pbufhNDE&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005007430133996%7C_p_origin_prod%3A | AliExpress |
| 30A Brushless Motor ESC | This will be the Electronic Speed Controller for the 4 brushless motors on the drone. I need to buy 2 pieces for a total of 4 for each motor. | 1 | 12.87 | https://www.aliexpress.us/item/2252799818726193.html?spm=a2g0o.detail.0.0.57c84iEw4iEwcX&mp=1&pdp_npi=6%40dis%21USD%21USD%2019.37%21USD%2012.87%21%21USD%2012.87%21%21%21%402101e62517759623597128640e4864%2112000037347798186%21ct%21US%212842570567%21%211%210%21&_gl=1*bd7qv0*_gcl_aw*R0NMLjE3NzU5NjE3NjQuQ2p3S0NBanc0dWZPQmhCa0Vpd0FmdUM3LVN4Wk1VVThydWVYUFUtRldvTkVNRkdlU1g5UkxIbzBkY1JpdmRNRlpicjZjYzA5cVpvUTNCb0Nxb3dRQXZEX0J3RQ..*_gcl_au*MTA5ODg3MDg0OS4xNzc0MTUwMTU1*_ga*MTgzMDIyMjAwNi4xNzc1OTYyMjM1*_ga_VED1YSGNC7*czE3NzU5NjIyMzQkbzEkZzEkdDE3NzU5NjIzNjEkajEwJGwwJGgw&gatewayAdapt=glo2usa | AliExpress |
| Shipping | Additional shipping cost. | 1 | 5.95 | N/A | N/A |

---

## 💰 Total Cost

**$164.18 USD**
