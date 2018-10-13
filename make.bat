call lib\egcc.bat
set LIBPATH=-Ilib -Llib
windres resource.rc -O coff -o resource.o
gcc %CCFLAGS2% %LIBPATH% *.cc resource.o -lwin32hlp -lstdshit -lcomctl32 -lcomdlg32 -lgdi32 -lole32 -luuid -lddraw -lwinmm -mwindows -o vsyncTest.exe
