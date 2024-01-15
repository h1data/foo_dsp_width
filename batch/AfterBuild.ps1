New-Item -Path ..\Releases\temp -ItemType "directory" -Force
New-Item -Path ..\Releases\temp\x64\ -ItemType "directory" -Force
Copy-Item .\Release\Win32\foo_dsp_width.dll -Destination ..\Releases\temp\ -Force
Copy-Item .\Release\x64\foo_dsp_width.dll -Destination ..\Releases\temp\x64\ -Force
Compress-Archive -Path ..\Releases\temp\* -DestinationPath ..\Releases\foo_dsp_width_1.2.0.zip  -Force
Remove-Item -LiteralPath ..\Releases\temp -Force -Recurse
