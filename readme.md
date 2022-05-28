# YOLOV4-Tiny+Robotic_fish+Jetson_Nano_inference


![image](https://user-images.githubusercontent.com/64571422/170802351-0e54dde1-930a-4e1f-8d18-6598bd6dd49b.png)


## 目录
1) [Environment](#Environment)
2) [Attention](#Attention)
3) [How2train](#How2train)
4) [How2predict](#How2Predict)
5) [Compile_on_Jetson](#Compile_on_Jetson)
6) [PID_control_algorithm](#PID_control_algorithm)

## Environment
**PC**\
    torch==1.9.0\
    torchvision 0.10.0\
    cudatoolkit 11.1.1\
    OpenCV 4.1.1\
    Python 3.7.6\
**Jetson Nano**\
    Jetson Nano B01 8GB\
    Tensorrt 8.0.1.6\
    cuDNN 8.2.1.32\
    Python 3.6.9
## Attention
All kinds of weights in the code are based on 416x416 image training.

## How2train
This document only provide brief steps to train & predict the model offline.
The main code of training yolo & faster-rcnn is open-source by https://github.com/bubbliiiing/yolov4-tiny-pytorch & https://github.com/bubbliiiing/faster-rcnn-pytorch
### Train the gas leakage dataset
1. Preparation
**Train in VOC Format**
2. Data processing
After the data set is placed, we need to use **VOC_ annotation.py** get **2007_train.txt** and **2007_val.txt** for training.\
Modify Parameters in **voc_annotation.py**. **classes_path** can be modified for the first training only，**classes_path** is used to point to the txt corresponding to the detection category.
When training your own data set, you can create a **cls_classes.txt** and write the categories you need to distinguish.\
Content in **model_data/cls_classes.txt**：      
```python
leak1
leak2
leak3
...
```
Change classes_path in voc_annotation.py, which is corresponded with number in cls_classes.txt. Run ***voc_annotation.py***

3. Model Training   
**Remember ***classes_path*** in train.py**\
Finished modifying classes_path, you can run train.py to start training. After training multiple epochs, the weights will be generated in the logs folder.
4. Predict&Test
The prediction of training results requires two files, yolo.py and predict.py. Modify model_path and classes_path in yolo.py.

## How2Predict
### Using leak detection model
1. Set parameters in ***predict.py***
2. Run ***predict.py***
## Compile_on_Jetson
### This document only provide the brief step 
1. install Jetpack
2. set CUDA&CUDNN environment（Nvidia has installed the package in Jetpack)
```python
sudo vi ~/.bashrc
```
  add those code into /.bashrc
```python
export PATH=/usr/local/cuda-10.0/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH
export CUDA_HOME=$CUDA_HOME:/usr/local/cuda-10.0
```
   restart /.bashrc to validate
```python
source ~/.bashrc
```
3. install pip & Cython
```python
sudo apt-get install python3-pip libopenblas-base libopenmpi-dev
pip3 install Cython
```
3. install pytorch-1.9.0
4. install torchvision-0.10.0
5. install Tensorrt-8.0.1.6
6. For Yolov4-tiny, we have to use tools to convert pytorch .pth file into onnx file, and then convert it into .engine file.
7. For Faster-rcnn, there's no accelerating method provided by tensorrt, so we can only use pytorch to run it.
8. set startup script to run the object detection once the jetson was started.


## PID_control_algorithm
the robotic fish is controlled by the PID algorithm, which is compiled in STM32. The code is in HARDWARE Directory.


![序列 01_1](https://user-images.githubusercontent.com/31895962/170829272-e667b88f-8075-4007-96dc-8e17798f51ac.gif)



This document was edited by Shuyuhu, Fengao, Jihaoshi. The demonstration video was uploaded in the directory
