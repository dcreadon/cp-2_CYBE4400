# cp-2_CYBE4400: Class Project 2 for Operating System Security Course
---

## Building the Environment
- In order to be able to run this tutorial the correct environemtn will need to be set up using QEMU. The provided document below gives a step by step explanation of how to set up this environment. 
- Refer to Setting up seL4 on QEMU-2 document that is provided in this github

## Cloning the Repo
- Once you have the environment set up correctly the next step is to repo the repository.
- In the home folder, run mkdir sel4_tutorials_manifest, and then cd into this folder
- From here run: repo init -u https://github.com/seL4/sel4-tutorials-manifest and then repo sync
- Once sync is done, you have successfully cloned the necessary repo for this project.

## Project Structure
- For this project the specific tutorial we worked with was the ipc tutorial
- To get this tutorial, run ./init --tut ipc from within the seL4_tutorial_manifest folder
- This creates the necessary ipc and ipc_build folders
- ipc contains the source code of the project (client1.c, client2.c, CMakeLists.txt and server.c)
- ipc_build is where the project will be compiled and ran/tested

## Running the Project
- As stated earlier, /seL4_tutorials_manifest/ipc contains all of the source code necessary for this project
- To run this project, simply download this reposity and replace the ipc folder you currently have, with the one from this repo
- Follwing this navigate to the ipc_build folder
- From this folder, run ninja to compile the source code you juse placed into ipc
- Once the ninja build is complete, run the tutorial with ./simulate and observe the output

## Extra Notes
- To run each of the tasks some things will need to be commented out.
- For task 1, all of the else statement can be commented out.
- For task 2, all of the else statement other than the len and for loop can be commented out.
- For task 3, all of the else statemnt other than len variable, for loop, and seL4_ReplyRecv can be commented out
- For task 4, run as is.
