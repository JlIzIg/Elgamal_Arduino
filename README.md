The scheme is based on two Arduino devices, one of which is an IoT device (control unit), and the second ⸺ a key device. The system is based on the El-Gamal algorithm.
The control unit stores the decryption key, while the key device ⸺ an encryption key.
The key device requests the unlocking of the control unit, to which the control unit responds to the key device with a (pseudo)random request code.
The key device encrypts it with the selected asymmetric algorithm and sends it back to the control unit.
The control unit decrypts the request code with the decryption key and compares it with the sent code. If the codes match, a decision is made to unlock the system.
