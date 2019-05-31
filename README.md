# edhMonitor
A simple app I’m using at my house to monitor the status of the edh (main power in Haiti) and the status of my generator.
![App example](/docs/app_example.PNG?raw=true)

# Setup
The app is built on top of blynk: https://blynk.io/  
Which is a free platform that lets you interact with IOT  
Required materials:
- 1 node mcu
- 3 120v relays
Cabling to do the installation.

Setup diagram:  
![Diagram](/docs/diagram.png?raw=true)

# Double throw setup
The double throw is setup like this:
- A cable that goes straight from the edh in to a power outlet
- A cable that goes straight from the generator in to a power outlet
- A cable that goes straight from the main out to a power outlet

![doubleThrow](/docs/doubleThrowSwitch.jpeg?raw=true "doubleThrow")

# Blynk clone code
![Blynk clone](/docs/blynk_clone.JPG?raw=true)
