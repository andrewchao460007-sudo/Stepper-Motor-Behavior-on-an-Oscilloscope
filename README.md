# Stepper-Motor-Behavior-on-an-Oscilloscope
the rise and fall cycles of a stepper motor going clockwise, stopping and going counterclockwise can be vissualized on an oscilloscope



ffmpeg -i "https://github.com/user-attachments/assets/cb312d16-0589-43d1-a769-4199c75ca09b" \
  -vf "tonemap=hable,eq=brightness=-0.08:contrast=1.15:saturation=1.1,format=yuv420p" \
  -c:v libx264 -crf 22 -movflags +faststart output.mp4
