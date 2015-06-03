README -- About the files in this folder

Custom EESchema Components
--------------------------
The 'library/' folder contains custom component libraries -- typically with only one or two components actually in them, some of which share the same name as components in the default library. The 'Preferences/Library/Component library files' search-order box in EESchema (saved in gruvin9x.pro) should ensure that these gruvin9x components are used in preference to any with duplicate names from your own libraries.


Custom PCBNEW Component Footprint Modules
--------------------------------------------
There should be no reason to import component footprint modules into PCBNEW as they *should* all be drawn from ../gruvin9x-cache.lib. However, if for some reason you have to (or want to) import gruvin9x custom footprints into your own library, then .emp files are available for that in the 'Modules/' folder.


3D Drawings for 3D Display Rendering
------------------------------------
The 3D VRML2.0 (.wrl) files needed for rendering the 3D display are located in the three folders 'connectors/', 'discret/', and 'smd/', as these are the relative paths specified in each module that uses them. (They could have all been in one folder, but I simply duplicated the relative paths from my master library.)

Other Stuff
-----------
Four your convenience or interest, the original Wings3D (.wings) files for the 3D images are in the 'Wings3D Sources' folder. (These get exported from Wings3D as VRML v2.0 [Swap Z any axis] to make their respective .wry files for use by PCBNEW.)

The 'Modules' and 'Wings 3D Sources folders', plus this README file can be safely deleted without harm to either EESchema or PCBNEW functionality -- though I'd recommend they stay as is.



