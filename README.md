# RFID and Password-Based Smart Door Lock System

**Author:** Prajwal Navalagi  
**Technologies:** Arduino (C/C++), Embedded Systems, RFID, EEPROM, Keypad, LCD, Relay Control  
**Project Cost:** ₹2100  
**Repository Purpose:** Showcase of a complete hardware-software integrated access control system with clean code, optimization techniques, and documentation.

---

## Project Overview

This project is a **Smart Door Lock System** that uses a combination of:

- RFID authentication
- 6-digit secure password
- EEPROM-based password storage
- Manual override with a push-button
- LCD interface with custom icons
- RGB LED and buzzer for feedback
- Optimized wiring using I2C and RGB LED

It was built with cost-effective components, designed for reliability, and supports both hardware and software optimizations.

---

## Bill of Materials (BoM)

| SI.No | Component                        | Cost (INR) |
|-------|----------------------------------|------------|
| 1     | 5V Active Buzzer                 | 12         |
| 2     | 5V, 10A Relay Module             | 55         |
| 3     | ATmega328P Microcontroller       | 189        |
| 4     | MFRC522 RFID Reader + Tags       | 120        |
| 5     | 4x4 Keypad                       | 100        |
| 6     | 16x2 LCD with I2C Interface      | 105        |
| 7     | RGB LED                          | 8          |
| 8     | EEPROM (Internal to ATmega328P) | -          |
| 9     | Push Button                      | 3          |
| 10    | 12V Solenoid Lock                | 399        |
| 11    | Fog Maker (Optional)            | 680        |
| ...   | Wires, Potentiometer, etc.       | -          |
|       | **Total**                        | **₹2100**  |

---

##  Features

✅ Dual Authentication: RFID or Password  
✅ EEPROM Storage: Password remains even after power-off  
✅ Auto Lock after Timeout  
✅ Retry Limit with System Lockdown  
✅ Change Password Feature  
✅ LCD UI with Custom Icons (Lock/Unlock)  
✅ Feedback via RGB LED and Buzzer  


---

##  How It Works

###  Case 1: Authorized RFID
- Green LED + buzzer feedback
- Unlocks the solenoid for 4 seconds
- Locks automatically

###  Case 2: Password Authentication
- Press `A` and enter 6-digit password
- On success: Unlocks & shows access granted
- On failure: Red LED + buzzer, lockdown after 3 retries

###  Case 3: Change Password
- Press `C` to enter password change mode
- Verify old password → enter new password → confirm

###  Case 4: Failed Attempts
- After 3 wrong passwords or 5 wrong RFID scans
- System locks down for 1 minute

###  Case 5: Manual Unlock from Inside
- Press internal push button → unlocks the door


---

---

## Optimizations

### Hardware Optimizations
- **Potentiometer** to control LCD backlight
- **RGB LED** to save space and add colored indicators
- **I2C LCD** to reduce wiring
- **Use of solenoid lock** for better power and security handling

### Software Optimizations
- **Custom LCD characters** for lock/unlock symbols
- **EEPROM** used instead of RAM for persistent password
- **Structured code** for better readability and reusability

---

## Results

- High security with dual authentication
- Accurate and fast door unlocking mechanism
- Minimal component usage through optimization
- System recovery and lockout protection in place

---

## Future Scope

- Add IoT integration (e.g., Blynk, MQTT, WiFi notifications)
- Integrate biometric (fingerprint) sensor
- Power monitoring and backup battery system
- Add admin override mode

---

## License

This project is open-source and free to use for educational and personal purposes. If you use this in your own projects or modify it, a credit to the original author is appreciated.

---

## Acknowledgments

Thanks to my mentors and fellow students who contributed ideas during development.  
Special thanks to open-source libraries like MFRC522, Keypad, and LiquidCrystal_I2C.

---

## Author

**Prajwal Navalagi**  
[LinkedIn](https://www.linkedin.com/in/prajwalnavalagi/) 
[GitHub](https://github.com/Prajwalsn17)  

## Project Demo

Watch the full video demo of the RFID & Password-Based Smart Door Lock System on YouTube:

[Watch Video](https://youtu.be/yyq3W6xdE-Q?si=zBkAn0m8AnAUlIcN)



