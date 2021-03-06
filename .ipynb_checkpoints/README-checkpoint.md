# **Bear Robotics Coding Challenge Project**
---
## **Simple ATM Controller**

[image0]: ./images/atm_controller_system_diagram.png "System Diagram"

## Project Requirements
---
At least the following flow should be implemented:

Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw

For simplification, there are only 1 dollar bills in this world, no cents. Thus account balance can be represented in integer.

Your code doesn't need to integrate with a real bank system, but keep in mind that we may want to integrate it with a real bank system in the future. It doesn't have to integrate with a real cash bin in the ATM, but keep in mind that we'd want to integrate with that in the future. And even if we integrate it with them, we'd like to test our code. Implementing bank integration and ATM hardware like cash bin and card reader is not a scope of this task, but testing the controller part (not including bank system, cash bin etc) is within the scope.

A bank API wouldn't give the ATM the PIN number, but it can tell you if the PIN number is correct or not.

Based on your work, another engineer should be able to implement the user interface. You don't need to implement any REST API, RPC, network communication etc, but just functions/classes/methods, etc.

You can simplify some complex real world problems if you think it's not worth illustrating in the project.

**How to submit**

Please upload the code for this project to GitHub or anywhere, and post a link to your repository below. Please attach the instruction to clone your project, build and run tests in README.md file in the root directory of the repository.

## Project Implementation 
---

The ATM Controller is implemented as a Finite-state Machine (FSM), using C++11 as the programming language.

### System Components

The image below shows the main system components:

![][image0]

All the above system components are represented by C++ Classes.

**ATM Controller** *(class ATMController)*

Implements the ATM Controller functionality. Uses the ATM Hardware Interface, Bank API, and IO Interface to communicate with the ATM hardware, Bank, and Console respectively.

*Hardware*

**ATM Hardware Interface** *(class ATMHardwareInterface)*

Defines an interface to communicate with the ATM Hardware, such as the Cash Bin and Card Reader.

**Sample ATM Hardware** *(class SampleATMHardware: public ATMHardwareInterface)*

A sample implementation to simulate ATM hardware behavior. Inherits the ATM Hardware Interface.

**ATM Hardware Factory** *(class ATMHardwareFactory)*

Provides the Controller with an ATM Hardware object that implements the ATM Hardware Interface.

*Bank*

**Bank API** *(class BankAPI)*

Defines an interface the Controller can use to communicate with a bank for performing various user initiated transactions.  

**Sample Bank** *(class SampleBank: public BankAPI)*

Simulates a user bank account for testing basic ATM transactions. Inherits the Bank API.

**Bank Server Connection** *(class BankServerConnection)*

Class that simulates bank connection functionality and connects the ATM to an appropriate bank.

*User*

**IO Interface** *(class IOInterface)*

Interface for User-ATM Controller interaction.

**Console IO** *(class ConsoleIO: public IOInterface)*

Class that enables user interaction via console. Inherits the IO Interface.

**IO Factory** *(class IOFactory)*

Provides the Controller with an IO object (e.g: console io) that implements the IO Interface.

## Testing the ATM Controller
Currently only manual testing from the console is supported.

## Basic Instructions to Clone this Repo and Build
---
From Command Line:
1. Go to the parent folder where you want to clone this project
2. Execute Command: `git clone https://github.com/ashishsnaik/ATMController.git`
3. Execute Command: cd `ATMController/Debug`
4. Execute Command: *make*

To manually test the ATM Controller functionality:
From the command line:
1. Go to `ATMController/Debug` folder
2. Execute Command: `./atm_controller` and test 


## Dependencies
---
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Code Style
---
As much as possible, I have tried to stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).
