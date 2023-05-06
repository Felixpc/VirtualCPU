# VirtualCPU
## 8-Bit-CPU-Simulation

Dieses Projekt ist eine Simulation einer einfachen 8-Bit-CPU in C. Die Architektur der CPU ist um einen 8-Bit-Bus aufgebaut und besteht aus verschiedenen Komponenten, einschließlich Register A, Register B, einem Ausgaberegister und einer ALU, die Operationen auf den Daten in den Registern ausführt.

Die CPU wurde modular aufgebaut, um eine einfache Anpassung und Erweiterung der Architektur zu ermöglichen. Jede Komponente wurde als eigenständiges Modul implementiert und kann leicht ausgetauscht oder erweitert werden, um die Funktionalität der CPU zu ändern oder zu erweitern.

I have written a simulation of a simple 8-bit CPU in C. The processor's architecture is similar to that of a breadboard computer by Ben Eater https://eater.net/8bit, with an 8-bit bus connecting multiple 8-bit registers such as A, B, and an output register. The processor has an ALU that can perform operations with the data from A and B.

The program is stored in RAM, which is addressed by the instruction counter. The current instruction is stored in RAM, and the first four bits of the instruction contain a command, while the remaining 4 bits are data. The various components of the processor can place their data on the bus while another component reads information from the bus.

I have built the software modularly to make it universally adaptable. My goal was to understand the basic functions of a processor, and I was fascinated by breadboard computers. I wanted to build such a computer myself, but the hardware implementation was too cumbersome for me. Therefore, I decided to develop a simulation to understand the basics of computer architecture and machine learning.

By simulating a simple processor, I have understood the basic functions of a processor and learned how they work together to create a computer architecture. It has also improved my programming and simulation skills and deepened my understanding of how hardware and software work. If I want to expand my simulation, I can add more features and components to increase complexity and expand my understanding.

