<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">

</head>
<body>
  <h1>Controller Area Network (CAN)</h1>
  
  <h2>Introduction</h2>
  <p>
    Controller Area Network (CAN) is a robust vehicle bus standard designed to allow microcontrollers and devices to communicate with each other without a host computer. It was originally developed by Bosch in the 1980s for in-vehicle networking but has since found applications in various industries due to its reliability and efficiency.
  </p>
  
  <h2>Key Features</h2>
  <ul>
    <li>
      <strong>Message-Based Protocol:</strong> CAN is a message-based protocol, meaning that data is transmitted in frames, each identified by a unique identifier.
    </li>
    <li>
      <strong>Multi-Master Capability:</strong> Any node can initiate communication, making the network highly flexible.
    </li>
    <li>
      <strong>Error Detection and Handling:</strong> CAN includes multiple error detection mechanisms and automatic retransmission of corrupted messages.
    </li>
    <li>
      <strong>Real-Time Communication:</strong> CAN supports real-time communication with a high level of determinism.
    </li>
  </ul>
  
  <h2>CAN Arbitration</h2>
  <p>
    <strong>Overview:</strong> CAN arbitration is the process by which nodes on a CAN bus determine which node has the right to transmit data when multiple nodes attempt to send messages simultaneously. This is crucial for avoiding data collisions and ensuring efficient communication.
  </p>
  
  <h3>Arbitration Process</h3>
  <ol>
    <li>
      <strong>Message Priority:</strong> Each CAN message has a unique identifier, which also determines its priority. Lower numerical values indicate higher priority.
    </li>
    <li>
      <strong>Bit-by-Bit Arbitration:</strong> During arbitration, nodes transmit their message identifiers bit by bit. The CAN bus uses a dominant (logical 0) and recessive (logical 1) bit level system.
    </li>
    <li>
      <strong>Dominant vs. Recessive:</strong> If a node transmits a recessive bit but detects a dominant bit on the bus, it stops transmitting and waits for the next arbitration round.
    </li>
    <li>
      <strong>Winning Node:</strong> The node with the highest priority (lowest identifier) continues to transmit, while others switch to listening mode.
    </li>
  </ol>
  
  <h2>Connections</h2>
  <ol>
    <li>
      <p><strong>Connect the potentiometer to the Arduino Mega 2560.</strong></p>
      <ul>
        <li>Connect the middle pin of the potentiometer to the analog input pin A0 on the Arduino.</li>
        <li>Connect the other two pins of the potentiometer to VCC (5V) and GND.</li>
      </ul>
    </li>
    <li>
      <p><strong>Connect the I2C LCD to the Arduino Mega 2560.</strong></p>
      <ul>
        <li>SDA to SDA on Arduino (pin 20)</li>
        <li>SCL to SCL on Arduino (pin 21)</li>
        <li>VCC to 5V on Arduino</li>
        <li>GND to GND on Arduino</li>
      </ul>
    </li>
    <li>
      <p><strong>Connect the MCP2515 CAN controller to the Arduino Mega 2560.</strong></p>
      <ul>
        <li>VCC to 5V on Arduino</li>
        <li>GND to GND on Arduino</li>
        <li>CS to pin 53 on Arduino</li>
        <li>SI to pin 51 on Arduino</li>
        <li>SO to pin 50 on Arduino</li>
        <li>SCK to pin 52 on Arduino</li>
        <li>INT to pin 2 on Arduino</li>
        <li>CANH and CANL to the CAN Bus lines (CANH to CANH, CANL to CANL)</li>
      </ul>
    </li>
  </ol>
</body>
</html>
