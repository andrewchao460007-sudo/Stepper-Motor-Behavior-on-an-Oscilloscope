# Stepper-Motor-Behavior-on-an-Oscilloscope
the rise and fall cycles of a stepper motor going clockwise, stopping and going counterclockwise can be vissualized on an oscilloscope



ffmpeg -i "https://github.com/user-attachments/assets/cb312d16-0589-43d1-a769-4199c75ca09b" \
  -vf "zscale=t=linear:npl=100,format=gbrpf32le,zscale=p=bt709,tonemap=tonemap=hable:desat=0,zscale=t=bt709:m=bt709:r=tv,format=yuv420p" \
  -c:v libx264 -crf 22 -preset medium -movflags +faststart output.mp4
