*** Plugin SDK for the A6 engine of 3D GameStudio ***

You can freely use this SDK for creating plugin DLLs for
the A6 engine, as long as you provide a machine readable 
copy of the complete product source code along with the 
product.

If you have purchased the GameStudio Pro Edition or a
SDK license from Conitec, you don't have to provide the 
source code.

You are allowed to distribute the .cpp, and .h, files 
that are included in SDK, but not the .lib libraries. 

You must not use the SDK to produce a DLL that can be used 
as a 'wrapper' for the library by providing access to the interface 
structures or to library functions from outside the DLL.

C++ SDK -------------------------------------------------------

This SDK supports engine versions 6.31 and above.
Note: for 6.31, don't set the warn_level variable
at 2 when using the SDK. Otherwise you'll get some
warnings at startup. You can safely ignore the
warnings.