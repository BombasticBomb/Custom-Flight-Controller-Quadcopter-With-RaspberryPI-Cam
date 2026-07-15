## Custom Drone Flight Controller
Arduino + MPU9250 based Flight Controller for Quadcopter!
This project is a custom-built quadcopter drone that uses an Arduino flight controller with an MPU9250 IMU. 

## 3D Model
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/2295d726-c978-430c-b60e-c23687e94a5f" />
This'll be printed in Carbon Fiber Nylon Filament, so it is actually strong enough to be a drone chassis. I will also use a Gyroid infill pattern with 40% infill to make it really strong, and I'll also use a wall count of 6 for further reinforcement.

## Inspiration
This is my hack club project to build a quadcopter from scratch with a custom flight controller with Arduino &amp; MPU9250. Growing up, I'd watch many science and engineering videos online; I've always been a science kid who spends his time watching astronomy, engineering, etc type videos. I did this project to challenge myself in learning the ins and outs of how a quadcopter actually works, and also to combine my skills in hardware, electronics, and coding to create something unique and not just follow a tutorial.
<img width="1919" height="970" alt="image" src="https://github.com/user-attachments/assets/6066f4e6-7fbe-49cd-982a-4385e910c6f5" />


 ## What Makes This Project Unique
Unlike most custom drones that rely on preprogrammed ready-to-fly flight controllers, my project uses a fully custom flight controller using Arduino & mpu9250 that I had to do a lot of research to actually learn how it works using custom cascaded PID controller loops (and in the future, an extended Kalman filter), and I am working on developing it into a fully functioning firmware. Along with that, I am utilizing a novel method to stream video transmission using a USB camera and the Raspberry Pi using a Python script that uses OpenCV to play video on a web dashboard hosted in Flask and streamed with Flask-socketio. This is a unique method as I offload the low-level control to the Arduino, while I implement advanced features such as a camera (and hopefully in the future GPS, ultrasonic sensors, etc) through the more powerful Raspberry Pi, which actually runs the Linux Operating System.
- Arduino --> Does the low-level flight control and sensor fusion
- Raspberry Pi --> Video Streaming
**Note: Using the onboard wifi on the Raspberry Pi does mean the video transmission range is limited, and beyond that range, we have to rely solely on radio.

## Wiring Diagrams
<img width="1024" height="559" alt="circuit diagram" src="https://github.com/user-attachments/assets/9755f03a-04df-4491-be2b-8414541a13d2" />
<img width="1024" height="890" alt="image" src="https://github.com/user-attachments/assets/b0647f15-fe06-47f9-b61d-f54ff77f57d4" />

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

## Custom PCB:
<img width="1065" height="599" alt="image" src="https://github.com/user-attachments/assets/d90e29e1-4f88-41d8-8d7b-a8cb62e65f28" />
<img width="4032" height="3024" alt="pcb" src="https://github.com/user-attachments/assets/90fb526e-7d27-4eea-8660-46171f0596db" />
Note: The ESCs themselves are part of the wiring diagram and are powered by the Arduino. It is crucial to note the motors themselves, and the Arduino also gets power from the main battery. The reason this configuration was required is that the Arduino converts the 11.1V on the 3S battery to 5V and supplies it to the other electronics.


# Bill of Materials

| Name | Purpose | Quantity | Total Cost (USD) | Link | Distributor |
|------|---------|----------|------------------|------|-------------|
| EVE 50PL 21700 5000mAh 50A Battery | This'll power the drone through its flight. I decided to buy Li-ion batteries and manually connect 3 to make a 3S cell to make a 5000mAh 3S battery pack. This'll help the drone fly longer. I'm buying one extra just in case. | 4 | 24.00 | https://www.18650batterystore.com/products/eve-50pl-21700-5000mah-50a-battery?variant=46405896798359 | 18650 Battery Store |
| JLCPCB Order + Shipping | I'll be manufacturing my custom PCB from JLCPCB. | 1 | 4.30 | https://cart.jlcpcb.com/quote?stencilLayer=2&stencilWidth=100&stencilLength=100&stencilCounts=5&plateType=1&spm=Jlcpcb.Homepage.1010 | JLCPCB |
| Male & Female Headers | It'll be used to connect things on the PCB. | 1 | 3.82 | https://www.aliexpress.us/item/3256805860047704.html?spm=a2g0o.cart.0.0.347038daeMTzKz&mp=1&pdp_npi=6%40dis%21USD%21USD%202.56%21USD%202.48%21%21USD%202.48%21%21%21%40210311a017759634443543759ee48c%2112000035473388533%21ct%21US%212842570567%21%211%210%21&_gl=1*hb3qht*_gcl_aw*R0NMLjE3NzU5NjE3NjQuQ2p3S0NBanc0dWZPQmhCa0Vpd0FmdUM3LVN4Wk1VVThydWVYUFUtRldvTkVNRkdlU1g5UkxIbzBkY1JpdmRNRlpicjZjYzA5cVpvUTNCb0Nxb3dRQXZEX0J3RQ..*_gcl_au*MTA5ODg3MDg0OS4xNzc0MTUwMTU1*_ga*MTgzMDIyMjAwNi4xNzc1OTYyMjM1*_ga_VED1YSGNC7*czE3NzU5NjIyMzQkbzEkZzEkdDE3NzU5NjM0NTAkajIzJGwwJGgw&gatewayAdapt=glo2usa | AliExpress |
| XT90 Male to XT60 Female connector for battery | This converts the XT90 on the battery to XT60 so it can be connected to the PCB. | 1 | 1.00 | https://www.aliexpress.us/item/3256809870073827.html?spm=a2g0o.productlist.main.2.6ec677250MQCzi&algo_pvid=cdafdfe4-f998-4543-be9e-b0735b928c6e&algo_exp_id=cdafdfe4-f998-4543-be9e-b0735b928c6e-1&pdp_ext_f=%7B%22order%22%3A%22124%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%2111.54%210.99%21%21%2179.06%216.79%21%402103212317741506875214915ecc89%2112000050973827105%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Af626b5c8%3Bm03_new_user%3A-29895%3BpisId%3A5000000197847475&curPageLogUid=TNcZo29qJmvN&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005010056388579%7C_p_origin_prod%3A | AliExpress |
| Drone Frame | This will be the frame that I will be doing all the testing on. I'll have to ship it to my location. | 1 | 5.00 | https://github.com/hackclub/print-legion | Hack Club Legion |
| 1400KV Brushless Motors | These will be the motors that generate lift for the drone. | 4 | 33.40 | https://www.robotshop.com/products/e-s-motor-xxd-a2212-brushless-motor-160w-mounting-base-kits-kv-1400?qd=f82c3b340c3f619c5c40ab447d536a69 | Robotshop |
| Raspberry PI 4 4GB | This will be used to connect the USB camera and for video transmission. I already have this, so I will not need to buy it. | 1 | 0.00 | https://www.centralcomputer.com/raspberry-pi-4-model-b-rpi4-modbp-4gb-4gb-ddr4-ram-bcm2711-soc-usb-3-0-poe-enabled.html | Central Computers |
| Arduino Nano | This will be running the flight software and controlling the motors. I already have this, so I will not need to buy it. | 1 | 0.00 | https://www.aliexpress.us/item/3256809956121978.html?aem_p4p_detail=2026061807213415670671290773640000102442&algo_pvid=3fc0e9e0-2e6c-470b-8047-724649fb7564&algo_exp_id=3fc0e9e0-2e6c-470b-8047-724649fb7564-3&pdp_ext_f=%7B%22order%22%3A%222454%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.74%212.32%21%21%2125.14%2115.59%21%402103128817817924947762687ecb01%2112000051298773766%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A3fe947d3%3Bm03_new_user%3A-29895&curPageLogUid=GvMORCvxgsTu&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005010142436730%7C_p_origin_prod%3A&search_p4p_id=2026061807213415670671290773640000102442_1 | AliExpress |
| GY-91 Board with both MPU-9250 & BMP180 | This will the the 9 Axis Flight Controller for the drone (Gyroscope, Accelerometer, Magnetometer, Altometer). | 1 | 6.34 | https://www.aliexpress.us/item/3256810419378175.html?spm=a2g0o.productlist.main.5.666b2322l9xEzg&algo_pvid=7fd4cfff-d2cf-4cf7-afad-2ea0b819e83e&algo_exp_id=7fd4cfff-d2cf-4cf7-afad-2ea0b819e83e-4&pdp_ext_f=%7B%22order%22%3A%2249%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%217.21%216.34%21%21%217.21%216.34%21%402101ef5e17817925960768424e7f71%2112000058167636174%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A3fe947d3%3Bm03_new_user%3A-29895&curPageLogUid=rwzrzHfS3o8g&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005010605692927%7C_p_origin_prod%3A | AliExpress |
| 8x4.5 Inch RC Drone Propellers | These will be used on the brushless motors to provide lift for the drone. I am buying 8 pieces instead of 4 in case some break during testing. | 1 | 0.92 | https://www.aliexpress.us/item/2251832730802090.html?spm=a2g0o.productlist.main.4.780ePWPrPWPrdV&algo_pvid=f486226a-b9b0-4b15-9514-1ad157b2ce74&algo_exp_id=f486226a-b9b0-4b15-9514-1ad157b2ce74-3&pdp_ext_f=%7B%22order%22%3A%22290%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%211.14%210.92%21%21%211.14%210.92%21%402103126e17817925437511508e4a1e%2165941027930%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A3fe947d3%3Bm03_new_user%3A-29895&curPageLogUid=cXlmlSlAPHTO&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A32917116842%7C_p_origin_prod%3A | AliExpress |
| 3S Li-po Battery Charger US Plug | This will be used to charge the battery. | 1 | 11.61 | https://www.aliexpress.us/item/3256805934795867.html?spm=a2g0o.productlist.main.5.5574546cUwMiyN&algo_pvid=89444658-625e-497a-9161-8886d6b7c66c&algo_exp_id=89444658-625e-497a-9161-8886d6b7c66c-4&pdp_ext_f=%7B%22order%22%3A%2236%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%2114.61%219.61%21%21%2114.61%219.61%21%402103122117759642911075864e8f33%2112000035846729871%21sea%21US%212842570567%21ACX%211%210%21n_tag%3A-29919%3Bd%3A3fe947d3%3Bm03_new_user%3A-29894%3BpisId%3A5000000203531302&curPageLogUid=vJ4Xx6RcBVto&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005006121110619%7C_p_origin_prod%3A | AliExpress |
| MicroZone MC6C Mini V2 2.4G 6CH Controller Transmitter w/ Receiver | This will be used for the radio communication with the drone. | 1 | 35.24 | https://www.aliexpress.us/item/3256807243819244.html?spm=a2g0o.productlist.main.35.4ab577e7dXjt8P&algo_pvid=51c9d117-d897-430c-8a26-849a75ee0eb6&algo_exp_id=51c9d117-d897-430c-8a26-849a75ee0eb6-34&pdp_ext_f=%7B%22order%22%3A%22543%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%21118.36%2135.24%21%21%21804.10%21239.42%21%40210319b717759622763998627ecd25%2112000040726294727%21sea%21US%212842570567%21ACX%211%210%21n_tag%3A-29919%3Bd%3A3fe947d3%3Bm03_new_user%3A-29894%3BpisId%3A5000000203531302&curPageLogUid=uuj3pbufhNDE&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005007430133996%7C_p_origin_prod%3A | AliExpress |
| 30A Brushless Motor ESC | This will be the Electronic Speed Controller for the 4 brushless motors on the drone. I need to buy 2 pieces for a total of 4 for each motor. | 1 | 12.87 | https://www.aliexpress.us/item/2252799818726193.html?spm=a2g0o.detail.0.0.57c84iEw4iEwcX&mp=1&pdp_npi=6%40dis%21USD%21USD%2019.37%21USD%2012.87%21%21USD%2012.87%21%21%21%402101e62517759623597128640e4864%2112000037347798186%21ct%21US%212842570567%21%211%210%21&_gl=1*bd7qv0*_gcl_aw*R0NMLjE3NzU5NjE3NjQuQ2p3S0NBanc0dWZPQmhCa0Vpd0FmdUM3LVY5UkxIbzBkY1JpdmRNRlpicjZjYzA5cVpvUTNCb0Nxb3dRQXZEX0J3RQ..*_gcl_au*MTA5ODg3MDg0OS4xNzc0MTUwMTU1*_ga*MTgzMDIyMjAwNi4xNzc1OTYyMjM1*_ga_VED1YSGNC7*czE3NzU5NjIyMzQkbzEkZzEkdDE3NzU5NjIzNjEkajEwJGwwJGgw&gatewayAdapt=glo2usa | AliExpress |
| 12V-5V Buck Converter | This'll convert the 11.1V from the 21700 battery pack to 5V so the Raspberry PI can use it. | 1 | 0.99 | https://www.aliexpress.us/item/3256806059787124.html?spm=a2g0o.productlist.main.47.356d56843bI7xm&algo_pvid=37468c4f-56f3-46fc-b45b-78fc5e97108e&algo_exp_id=37468c4f-56f3-46fc-b45b-78fc5e97108e-44&pdp_ext_f=%7B%22order%22%3A%228%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%211.57%210.99%21%21%211.57%210.99%21%402101e2b217831438404382735e9fc9%2112000036452024405%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A3fe947d3%3Bm03_new_user%3A-29895%3BpisId%3A5000000207260799&curPageLogUid=bAlAl3PlYxYP&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005006246101876%7C_p_origin_prod%3A | AliExpress |
| **Total** | | | **139.49** | | |
