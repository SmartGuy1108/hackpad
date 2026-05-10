# hackpad


My Hackpad is a 9 key macropad that uses 9 keyboard switches, a 0.96in oled screen, a xiao rp2040, 9 rgb leds, and a ATtiny85 for the leds. I made a PCB for this which can be found in the repo. It includes the gerber and drill files. My total price for this project was around $40 I used AliExpress to source the components for cheap and I used JLPCB for the PCB. The point of this was to make a maacropad that was cool and could be used for custom purposes instead of using the defualt layout. It works by making the Xiao do all the proccesing for the keys and the ATtiny doing all the led controls while being powered by the Xiao. I considered adding a usb C port for the ATtiny but decided against it to keep it all connected using one usb C so it looks clean. The total cost was around $48 I made a custom case that has a big hole for all the 9 keys because I didn't want they keycaps to get stuck on the lid. The lid connects to the body using "rails" in the body. I also added a hole on the top for the OLED. I added circles on each corner of the pcb groove to make sure it stayed in place. Here is a image of the case: <img width="910" height="705" alt="image" src="https://github.com/user-attachments/assets/33a456d2-afbe-40b3-8633-02e5bddc1be7" />

<img width="307" height="363" alt="image" src="https://github.com/user-attachments/assets/c5853a69-ba43-4add-9cd9-3851ccf84c03" />          
<img width="422" height="546" alt="image" src="https://github.com/user-attachments/assets/2048304a-e809-4db8-b929-d0c93c0cf11d" />
<img width="641" height="227" alt="image" src="https://github.com/user-attachments/assets/6273f66b-9f5b-4fa9-bd42-77378716bff0" />
<img width="518" height="380" alt="image" src="https://github.com/user-attachments/assets/2b9b8aa3-317e-47c4-9ceb-e90cd93c5099" />

#,Component,Quantity,Price,Supplier,Link
1,XDA Profile PBT Blank Black Keycaps (MX compatible 10pcs),10,included,AliExpress,https://www.aliexpress.us/item/3256805328092200.html
2,ATtiny85-20PU DIP-8 AVR Microcontroller,1,included,AliExpress,https://www.aliexpress.us/item/3256808555620766.html?spm=a2g0o.productlist.main.11.801cl6gel6geQO&algo_pvid=50602609-ecce-48ad-855f-07c378396dc5&algo_exp_id=50602609-ecce-48ad-855f-07c378396dc5-10&pdp_ext_f=%7B%22order%22%3A%2221%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.10%210.99%21%21%213.10%210.99%21%40210325a917783087227717348eeebc%2112000046478972951%21sea%21US%217621068922%21ABX%211%210%21n_tag%3A-29910%3Bd%3Af74fba6a%3Bm03_new_user%3A-29895%3BpisId%3A5000000203537318&curPageLogUid=gMP6Stg2v8xJ&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005008741935518%7C_p_origin_prod%3A
3,SSD1306 0.96in 128x64 OLED Display (I2C white 3pcs),1,included,AliExpress,https://www.aliexpress.us/item/3256805899077405.html
4,WS2812B 5mm RGB Through-hole LED (5V diffused 10pcs),9,included,AliExpress,https://www.aliexpress.us/item/3256806040849067.html?spm=a2g0o.productlist.main.10.7ab6paVEpaVEjr&algo_pvid=62cb0c92-1c9e-4fdd-96d2-34d27e3ec640&algo_exp_id=62cb0c92-1c9e-4fdd-96d2-34d27e3ec640-9&pdp_ext_f=%7B%22order%22%3A%221074%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%218.65%210.99%21%21%2158.53%216.73%21%40210311c217783083894485439e7f81%2112000036369823577%21sea%21US%217621068922%21ABX%211%210%21n_tag%3A-29910%3Bd%3Af74fba6a%3Bm03_new_user%3A-29895%3BpisId%3A5000000203537318&curPageLogUid=7gXFasjcGqQz&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005006227163819%7C_p_origin_prod%3A
5,Outemu Blue 3-Pin MX Switches (10pcs),10,included,AliExpress,https://www.aliexpress.us/item/3256803795058460.html
6,Custom PCB 2 layer black 5pcs (JLCPCB),5,$9.30,JLCPCB,N/A
7,AliExpress Subtotal,-,-,$11.02,-
8,AliExpress Total,-,-,$11.02,-
9,PCB + Shipping,-,-,$12.00,-
10,Grand Total,-,-,$23.02,-




