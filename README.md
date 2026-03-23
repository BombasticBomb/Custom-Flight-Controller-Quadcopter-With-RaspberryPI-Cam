## 🚁 Custom Drone Flight Controller
Arduino + MPU9250 based Flight Controller for Quadcopter!
This project is a custom-built quadcopter drone that uses an Arduino-based flight controller with an MPU9250 IMU for stabilization. The system is designed from scratch and I am currently working on the hardware, firmware, and the system architecture utilizing a combination of Arduino & Raspberry PI.

## 🖼️ 3D Model
<img width="1208" height="608" alt="image" src="https://github.com/user-attachments/assets/597906a4-b4d2-417b-bde2-e7fed3b08809" />
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
|   | **Arduino**       | → | **MPU9250** |
|   | 5V                | → | 5V          |
|   | GND               | → | GND         |
|   | A4                | → | SDA         |
|   | A5                | → | SCL         |

| # | Arduino --> RC Receiver |   |                 |
| - | --------------------- | - | --------------- |
|   | **Arduino**           | → | **RC Receiver** |
|   | 5V                    | → | 5V              |
|   | GND                   | → | GND             |
|   | RX                    | → | IBus            |

| # | Arduino --> ESC |   |         |
| - | ------------- | - | ------- |
|   | **Arduino**   | → | **ESC** |
|   | 5V            | → | 5V      |
|   | GND           | → | GND     |
|   | 3            | → | ESC1    |
|   | 4            | → | ESC2    |
|   | 5            | → | ESC3    |
|   | 6            | → | ESC4    |

Note: Brushless motors need Electronic Speed Controllers (ESCs) to operate. The ESC's themselves are part of the wiring diagram and are powered by the Arduino. It is crucial to note the motors themselves, and the Arduino also gets power from the main battery. The reason this configuration was required is that the Arduino converts the 11.1V on the 3S battery to 5V and supplies it to the other electronics.

## 📦 Bill of Materials

| Name | Purpose | Quantity | Total Cost (USD) | Link | Distributor |
|------|---------|----------|------------------|------|-------------|
| XT90 Male to XT60 Female connector for battery | This converts the XT90 on the battery to XT60 so it can be connected to the PDB board. | 1 | 1.00 | https://www.aliexpress.us/item/3256809870073827.html?spm=a2g0o.productlist.main.2.6ec677250MQCzi&algo_pvid=cdafdfe4-f998-4543-be9e-b0735b928c6e&algo_exp_id=cdafdfe4-f998-4543-be9e-b0735b928c6e-1&pdp_ext_f=%7B%22order%22%3A%22124%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%2111.54%210.99%21%21%2179.06%216.79%21%402103212317741506875214915ecc89%2112000050973827105%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Af626b5c8%3Bm03_new_user%3A-29895%3BpisId%3A5000000197847475&curPageLogUid=TNcZo29qJmvN&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005010056388579%7C_p_origin_prod%3A | Aliexpress |
| ESC PDB Board XT60 | This will be used to connect all the ESCs to the battery for power. | 1 | 1.00 | https://www.aliexpress.us/item/3256804130464172.html?spm=a2g0o.productlist.main.37.73adeKBWeKBW1Q&algo_pvid=4540c0fb-bf3a-4abb-a723-bebf7cb9852f&algo_exp_id=4540c0fb-bf3a-4abb-a723-bebf7cb9852f-36&pdp_ext_f=%7B%22order%22%3A%22146%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%212.72%210.99%21%21%212.72%210.99%21%402101df0e17741501994371074e1309%2112000028730244243%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Af626b5c8%3Bm03_new_user%3A-29895%3BpisId%3A5000000197847450&curPageLogUid=MHimRomaIX8v&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005004316778924%7C_p_origin_prod%3A | Aliexpress |
| Drone Frame | This will be the frame of the drone that'll hold all the parts and be the structural support. I have decided to use aliminium for the drone, but I'm still at the designing phase for it. | 1 | 22.00 | https://www.amazon.com/gp/product/B0CJ7V24MN/ref=ewc_pr_img_3?smid=A3V9RPWJAAQ27C&th=1 | Amazon |
| CNHL G+Plus 3000mAh 11.1V 3S Lipo Battery | This will be the battery for the drone and it will power it. | 1 | 18.99 | https://chinahobbyline.com/products/cnhl-gplus-series-3000mah-11-1v-3s-70c-lipo-battery-with-xt90-plug?variant=42646820520150&country=US&currency=USD&utm_medium=product_sync&utm_source=google&utm_content=sag_organic&utm_campaign=sag_organic&utm_source=google&utm_medium=paid-search&utm_campaign=pmax-all-us&gad_source=1&gad_campaignid=20679418975&gbraid=0AAAAADLM11YyMvG3qD_NDLKjEs94c2Nh8&gclid=CjwKCAjwg_nNBhAGEiwAiYPYA0O9yFw_d91XaKJ55l3Hq386bwSOqDSKlXSrVLVT1E4AFfyVf2CtmxoCuc0QAvD_BwE | China Hobbyline |
| 1400KV Brushless Motors | These will be the motors that generate lift for the drone.  | 4 | 33.40 | https://www.robotshop.com/products/e-s-motor-xxd-a2212-brushless-motor-160w-mounting-base-kits-kv-1400?qd=f82c3b340c3f619c5c40ab447d536a69 | Robotshop |
| Raspberry PI 4 4GB | This will be used to connect the usb camera and for video transmission. I already have this, so I will not need to buy it. | 1 | 0.00 | https://www.centralcomputer.com/raspberry-pi-4-model-b-rpi4-modbp-4gb-4gb-ddr4-ram-bcm2711-soc-usb-3-0-poe-enabled.html | Central Computers |
| Arduino UNO R3 | This will be running the flight software and controlling the motors. I already have this, so I will not need to buy it. | 1 | 0.00 | https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/ref=sr_1_1_sspa?crid=6G7O7K7CO1Z8&dib=eyJ2IjoiMSJ9.MazmhFfn-DF8W5oyX_S-tH7qkt_WuogERq_8M3-FTf428RcK1V-0k2CDkJste5CNBGaeyZhzdZU8lFsqqd8UDr_8_HoVEUcLN7hQizeKtT1WlcFNxf38hc9OzCVz-gA1ut4dbKaEA8_EiBspV4fyW5vaaKM5DNYC0RQ4w8r27-zJnMMphk1KJiiCClEj_VHcCIIIGY11AI8nE1SvBySq18V26pH2T89g0DfOs5Pc6Nc.PHAq9TzAk7fqvmCgDpX4rLFbxQsvazigK6K8VrcqWvM&dib_tag=se&keywords=arduino+uno&qid=1773894970&sprefix=arduino+uno%2Caps%2C150&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1 | Amazon |
| GY-91 Board with both MPU-9250 & BMP180 | This will the the 9 Axis Flight Controller for the drone (Gyroscope, Accelerometer, Magnetometer, Altometer) | 1 | 8.79 | https://www.amazon.com/gp/product/B0CMQSYR2Y/ref=ewc_pr_img_1?smid=A2YE8NZRGVUJGM&psc=1 | Amazon |
| 8x4.5 Inch RC Drone Propellers | These will be used on the brushless motors to provide lift for the drone. I am buying 8 pieces instead of 4 in case some breaks during testing. | 1 | 10.79 | https://www.amazon.com/gp/product/B07YYV2JL4/ref=ox_sc_act_title_6?smid=A1THAZDOWP300U&psc=1 | Amazon |
| 3S Li-po Battery Charger | This will be used to charge the battery for the drone. | 1 | 16.99 | https://www.amazon.com/gp/product/B0FPDJP4GK/ref=ox_sc_act_title_4?smid=A3OUEA3BPILM2W&psc=1 | Amazon |
| FLYSKY FS-i6 6Channel 2.4GHz AFHDS2A RC Transmitter & Reciever | This will be used for the radio communication with the drone. | 1 | 49.65 | https://www.amazon.com/gp/product/B07CXL9LCT/ref=ox_sc_act_title_1?smid=A3FG05GA5NMSJ&th=1 | Amazon |
| 30A Brushless Motor ESC | This will be the Electronic Speec Controller for the 4 brushless motors on the drone. Please buy 2 pieces for a total of 4 for each motor. | 2 | 35.18 | https://www.amazon.com/gp/product/B0CZNM4H7H/ref=ox_sc_act_title_6?smid=A3SITFGXOINFFJ&th=1 | Amazon |

## 💰 Total Cost

**$198.79 USD**
