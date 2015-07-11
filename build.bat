call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86
msbuild.exe CPPDebuggerVisualizers.VS2012.sln /t:Build /p:Configuration=Release;"Platform=Mixed Platforms"
msbuild.exe CPPDebuggerVisualizers.VS2013.sln /t:Build /p:Configuration=Release;"Platform=Mixed Platforms"
msbuild.exe CPPDebuggerVisualizers.VS2015.sln /t:Build /p:Configuration=Release;"Platform=Mixed Platforms"
