# commands help

### since [update 0.3](/smedit_versions/v0.3) there exists **some special commands** for the program.
### they are the following:
 - [**$od**](https://github.com/zetef/Smedit/new/master#od---open-directory)
 - [**$cd**](https://github.com/zetef/Smedit/new/master#cd---create-directory)
 - [**$dd**](https://github.com/zetef/Smedit/new/master#dd---delete-directory)
 - [**$cl**](https://github.com/zetef/Smedit/new/master#cl---current-location)
 - [**$sc**](https://github.com/zetef/Smedit/new/master#sc---set-color)
 - [**$rc**](https://github.com/zetef/Smedit/new/master#rc---reset-color)
 - [**$cls**](https://github.com/zetef/Smedit/new/master#cls)
 - [**$ex**](https://github.com/zetef/Smedit/new/master#ex)
 
### [update 0.4](/smedit_versions/v0.4) introduced:
 - $st
 - $rt
## **_$od_ - _open directory_**
  **example:** 
```
>$od
location: another folder
```
when using this **command** you'll be be asked to **input** the location of the **desired** directory. it will also **open** the file explorer **within** the folder you chose.
you can input as the location '.' standing for **_current directory_**, '..' standing for **_parent or previous directory_** or a directory name within the current folder you are in.

## **_$cd_ - _create directory_**
  **example:**
```
>$cd
new directory name: name of directory(can contain whitespaces)
location: C:\another random location
```
when using this **command** you'll be asked to **input** the name of the directory you want to create and the location of the **desired** directory. the location of the folder **_must_** be a full path or use '.' or '..', mentioned in [**_open directory_**](https://github.com/zetef/Smedit/new/master#od---open-directory).

## **_$dd - delete directory_**
  **example:**
  ```
  >$dd
  location: C:\this_folder
  ```
 
when using this **command** you'll be asked to **input** the location of the directory you want to delete. it **_must_** be a full location, '.' or '..'. it autochecks if it is a file and if so it deletes it.
**_I AM NOT RESPONSABLE FOR ANY DAMAGE THIS FUNCTION CAN DO. USE IT AT YOUR OWN RISK!_**

## **_$cl - current location_**
  **example:**
  ```
  >$cl
  C:\your\location
  ```
  
when using this **command** you'll see **the location** of the folder you are **currently** in navigating.

## **_$sc - set color_**
  **example:**
  ```
  >$sc
  green
  blue
  red
  pink
  yellow
  white
  >blue
  ```

when using this **command** you'll see a bunch of **options** you can choose. you just have to **type in** the option you want and the **color of the text** is your chosen color.

## **_$rc - reset color_**
  **example:**
  ```
  >$rc
  ```

when using this **command** the color of the text **will start** to be randomized again.

## **_$cls_**
  **example:**
  ```
  >$cls
  ```
 
when using this **command** it will clear the screen for **_one session_**, so the next time using **another** command the **files** and **directories** will show up.

## **_$st_**
  **example:**
  ```
  >$st
  name of title: my title
  ```
when using this **command** it will ask you the name of the title **of the program.**

## **_$rt_**
 **example:**
 ```
 >$rt
 ```
when using this **command** the title of the program will **reset** its title, being the path of the **current folder.**
## **_$ex_**
  **example:**
  ```
  >$ex
  ```

it **_exits_** the program.

### tip:
 - if you **ever** forget the commands you can simply **type $** in the program.
