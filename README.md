# ACCESS MDP
This projects consists on making use of a Raspberry pi Zero and a camera that reads QR codes and allow users to get in offices. The software is written in C++ that reads QR codes using OpenCV and compares that hased decoded QR codes with data fetch from an endpoint using Rest API.  

## Packages
* OpenCV
* zbar

# Building
To build the C++ code, run:
```console
make
```

The data of the allowed users is fetched using a python script called communication.py. Moreover, this code also POST the timestamps a user is entering the office.