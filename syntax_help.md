# editor syntax

### there are **_only_** **4 editor-specific commands** in smedit.
### they are the following:
- [**name declaration**](https://github.com/zetef/Smedit/new/master#name-declaration)
- [**extension declaration**](https://github.com/zetef/Smedit/new/master#extension-declaration)
- [**new file command**](https://github.com/zetef/Smedit/new/master#new-file-command)
- [**stop editing**](https://github.com/zetef/Smedit/new/master#stop-editing)

## **_syntax rules_**
  - the first two declarations in the editor will **_always_** be the [**name declaration**](https://github.com/zetef/Smedit/new/master#name-declaration) and **extension declaration**.
  - [**stop editing**](https://github.com/zetef/Smedit/new/master#stop-editing) **_must be_** at the end of the file.
  - [**new file command**](https://github.com/zetef/Smedit/new/master#new-file-command) and [**stop editing**](https://github.com/zetef/Smedit/new/master#stop-editing) **_must be_** on a separate line on their on.
  - ```
    file_name .txt content
    $stopf
    ```
    is legal and will make a text file named `file_name` with content written in.
    
## **_name declaration_**
  **example:** `file_name`
  
  a **name declaration** can contain **uppercase or lowercase letters**, begin or contain **numbers** or **any other symbol** **_except_** the **whitespace or tab** because it will be **automatically** intrepreted as an [**extension declaration**](https://github.com/zetef/Smedit/new/master#extension-declaration).
  
## **_extension declaration_**
  **example:** `.extName`
  
  an **extension declaration** is **_always_** after the [**name declaration**](https://github.com/zetef/Smedit/new/master#name-declaration) and can be any of the [**supported extensions**](https://en.wikipedia.org/wiki/List_of_file_formats#Archive_and_compressed). it **_must not be_** like this `.ext Name` because Name will be interpreted as the **content of the file**.
  
## **_new file command_**
  **syntax:** `$stop`
  
  used when you finish writing the contents of a file. ~~**_please don't write this command first_**~~.
  
## **_stop editing_**
  **syntax:** `$stopf` **(f from forever)**
  
  used when you finish your buisness with the editor. ~~**_again, don't write this command first. have mercy on me_**~~
  
  
 ## **_examples_**
  - **make a single file:**
  ```
  hello_world .bat
  @echo off
  
  :noInput
  set /P c = you want to visit my site? y/n
  if /I "%c%" EQU "Y" goto :my site
  if /I "%c%" EQU "N" goto :exit
  goto :noInput
  
  :exit
  exit

  :mySite
  start https://github.com/zetef/Smedit/
  exit
 
  $stopf
  ```
  
  - **make multiple files:**
  ```
  hey!I_can_use_$ymbols! .txt
  some sad text :(
  $stop
  
  waaait!this_is_another_file! .txt of course dummy! also this is legal!
  and this is a new line!!!!
  $stopf
  ```
  
  
  
  # **_hope you will enjoy this useless tool!_**
