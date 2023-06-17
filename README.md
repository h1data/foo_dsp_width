## Stereo Width

### What is this?
A DSP component for foobar2000 which narrows the width of stereo panning.

### Installation
1. download the zip file started with "foo_dsp_width" from [Releases](https://github.com/h1data/foo_dsp_width/releases/latest) section 
2. open foobar2000 > File > Preferences > Components
3. click Install and select the zip file and restart foobar2000
4. open File > Preferences > Playback > DSP Manager
5. add "Stereo Width" to "Active DSPs" and adjust width in percent
6. enjoy!

### Build dependencies
- Visual Studio Community 2022 Version 17.0.5
- foobar2000 SDK 2021-02-23 v1.6 https://www.foobar2000.org/SDK
- Windows Template Library https://sourceforge.net/projects/wtl/

#### Project directories
<pre>
foobar2000/                       from foobar2000 SDK
  foo_dsp_width/                  this project
  foobar2000_component_client/    from foobar2000 SDK
  helpers/                        from foobar2000 SDK
  SDK/                            from foobar2000 SDK
  shared/                         from foobar2000 SDK
libPPUI/                          from foobar2000 SDK
pfc/                              from foobar2000 SDK
WTL/                              from Windows Template Library
  Include/                        from Windows Template Library
</pre>
You need to add WTL/Include/ to include directory for foobar2000_sdk_helpers and libPPUI project.
