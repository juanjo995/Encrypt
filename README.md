# Encrypt
Simple software to encrypt your text files.

![Image](https://github.com/user-attachments/assets/1b89990c-26f3-480f-9ac3-441847fa9af4)

This project relies on a few libraries to work:

* [**Glad**](https://github.com/Dav1dde/glad) to initialize **OpenGL**.
* [**GLFW**](https://www.glfw.org/) to manage the window creation and events.
* [**ImGui**](https://github.com/ocornut/imgui) to build the user interface.
* [**Native File Dialog**](https://github.com/btzy/nativefiledialog-extended) to pop up the select file dialog window.
* [**Tiny AES in C**](https://github.com/kokke/tiny-AES-c) to encrypt and decrypt text files.

## Instructions

To create a new encrypted file just create a new empty text file anywhere you want.

Click on the button with three dots (...) and select that file.

Choose a password for your file.

Write the content you want to encrypt and click on **Encrypt**.

To decrypt a file just click on the button with three dots (...) and select the file to decrypt.

Introduce the password and click on **Decrypt**.

## Run it

Just go to **Releases** and download the executable for your OS version, Windows or Linux.

## Compile it

### GLFW

First you may need to compile GLFW.

Navigate to `/Encrypt/include/glfw-3.4`

`mkdir build`

`cd build`

`cmake ..`

`make`

### Glad

You may also need to download your own glad folder.

First check your OpenGL version.

**On Linux:**

`glxinfo | grep "OpenGL"`

**On Windows:**

`glewinfo | findstr "OpenGL"`

`wglinfo | findstr "OpenGL"`

Or using GPU-Z:

https://www.techpowerup.com/gpuz/

Once you know your OpenGL version go to:

https://glad.dav1d.de/

Select your OpenGL version and click on generate.

Delete the `/Encrypt/include/glad` folder and replace it with the one you downloaded.

### Compile

Now to compile the proyect just navigate to `/Encrypt`.

`mkdir build`

`cd build`

`cmake ..`

`make`

This shall generate the executable.
