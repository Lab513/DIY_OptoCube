# DIY_OptoCube
The OptoCube is a static temperature-controlled incubator equipped with a DMD to project light patterns on a set of agar plates. The agar plates are placed on top of a scanner to record time-lapse images of microbial growth. This setup allows high spatial and temporal resolution of light patterning (~ 0.1 mm, ~ 1 s) compared to the dimensions and dynamics of microbial colonies (> 1 mm, > 1 hour).

## Building your own OptoCube
Building an OptoCube is relatively straightforward. You need to gather a static incubator of relatively large dimension, a Digital micromirror device, a micro controller and a flatbed scanner. We propose here a set of devices that worked for us, but other commercial or DIY alternatives are of course possible.

-	Incubator : Memert XXX
-	DMD : DLP® LightCrafter™ 4500 TI
-	Scanner : Canon LIDE400. Note that, we opened the glass cover and apply black tape on some part of the bottom which are reflecting surfaces (this prevent undesired optogenetic activation reflection artefacts).
-	Microcontroler : Arduino UNO.

Briefly, the DMD was mounted on an incubator rack (OpenBeam construction kits). The scanner was placed below, facing up. The distance between the scanner glass and the DMD lens was 39cm. 

## Controlling the DMD with the Arduino board.
The DMD was powered with a 12V 4.16A power supply and connected to the Arduino at the pins J11.4, J11.5 and J11.6 using a molex 51021-0600 connector. The scanner was connected to the computer with a USB cable. The Arduino UNO was also connected to the computer with a USB cable and was controlling the DMD using its pin number 2 to apply 3.3V at the J11.5 pin trough a voltage divider (2.2kOhm and 3.3kOhm). The Arduino 3.3V pin was connected to the J11.4 pin and the ground pin to the J11.6. 
We use Jupyter to drive the OptoCube. To run the Jupyter script, you need to install the following package: serial (https://pypi.org/project/pyserial/) , time (https://docs.python.org/fr/3/library/time.html) and os.( https://docs.python.org/fr/3/library/os.html). You can alternatively directly download an anaconda environment containing all required packages from our github webpage.
https://anaconda.org/matthias.lebec/optocube

The DLP® LightCrafter™ 4500 TI is a Digital Micromirror Device composed of 912 × 1140 micromirror that can switch ON or OFF to reflect the light coming from integrated LEDs (Red, Green and Blue). The projected pixel intensity is controlled by Pulse Width Modulation. An important technical limitation is that even when the mirrors are completely OFF, there is a significant amount of light leaking out of the DMD onto the projected surface. The DMD offer two main modes of projection: video mode or sequence mode. The video mode is performed trough classical HDMI communication with a computer, allowing for straightforward and dynamic patterning. However, the range of light intensity in video mode is quite reduce, with a strong leaking. We thus used the sequence mode which give better intensities range (from 0.0014 mW.cm-² to 1.13mW/.cm-² for the blue LED). The main drawback of this mode is the lack of flexibility to change the mask being projected by the DMD. The mask must be loaded in the DMD before the experiment started using the DLPLCR software, and the maximum number of 8-bits masks that can be stored was 6. We use the DLPLCR software (“DLPLCR4500EVM-GUI” can be download here https://www.ti.com/tool/DLPLCR4500EVM) to create and load the masks, and to design the pattern sequence. More information on the procedure can be found in the DMD user guide. Briefly the workflow is the following:

1.	Create a 8 bits image in the BMP format, of dimension 912x1140 (Width x Height). The pattern has to be drawn with a 200% deformation in the vertical axis (due to the diamond shaped of the mirrors, see DLPLCR documentation for details)
2.	This image is transformed by the DLPLCR software to a 24 bits BMP image.
3.	In the DLPLCR software we load the 24 bits images to add to the firmware. The firmware is then built.
4.	Connect the computer to the DMD using a USB cable and power the DMD (this is not mandatory for the previous step).
5.	Load the firmware in the DMD.
6.	Edit the pattern sequence and save it in the DMD. You can then unplug the computer to the DMD.

## Seeting up the VueScan software to drive the scanner.
We used the following parameters. Note that the use of this software is not mandatory and other open-source software that can drive a scanner should do the trick. 
-	Media: “Black&White”
-	Media size: A4
-	Output file: 16 bits greyscale .tiff (no reduction nor compression)
-	Make Grey from: Auto
-	Scan resolution: 600 dpi
-	Number of passes: 1
-	Color balance: “None”

## Additional Requirements
The petri dishes lids can generate imaging artefacts due to light reflexion. To prevent this, we used 3D printed parts (“PlateTilterAngle5”) to tilt the lids of the petri dishes at 5°.
3D printed part “PlateTilterAngle5”

Note that to maximize the image acquisition quality you should ensure that agar plates are: 
1.	Highly transparent to avoid light scattering (this is why we relied on Phytagel).
2.	The gel layer is thin to allow the yeast layer to be in the focal plan of the scanner.
3.	The lid should be coated with a surfactant solution to reduce droplet formation due to condensation. We used a solution of Triton 100X 0.05% (v/v) (Eth 20%)


///
Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
