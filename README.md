# opencv-handeye

Build:
```
cd ~/git/opencv-handeye
docker run -v $(pwd):/root/opencv-handeye -it jjanzic/docker-python3-opencv bash
# Now you are inside the docker container
cd /root/opencv-handeye
mkdir build && cd build
cmake ..
make
```

Run:
```
docker run -v $(pwd):/root/opencv-handeye -it jjanzic/docker-python3-opencv bash
cd /root/opencv-handeye/build
./TestHandeye
```

Expected output:
```
---
OpenCV version : 4.1.0
Major version : 4
Minor version : 1
Subminor version : 0
---
Num of gripper2base transforms: 10
Num of target2cam transforms: 10
---
Estimated cam2gripper: 
[0.8357872530342421, 0.4275441928943817, 0.344478781331692, 30.08659781703733;
 -0.410875161208457, 0.90320366951094, -0.1241158059390394, 88.40409398451877;
 -0.3641994914430832, -0.03780336630863101, 0.9305534030502145, 297.8756595212807;
 0, 0, 0, 0]
```