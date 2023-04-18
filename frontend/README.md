# Wt Ui template with Theme and Navigation

## Instalation

Just folow the Dockerfile instructions from ../Dockerfile and you are golden with one exception, the Wt libraries may not link after the install and there are two fixes for that
1. run the next command to dynamicly link to those binaries 
~~~
export LD_LIBRARY_PATH=/usr/local/lib/
~~~
2. run the next command to copy the wt library files from /usr/local/lib/ to /usr/lib/
~~~ 
cp /usr/local/lib/libwt*.so.* /usr/lib/
~~~

### Custom Theme
The theme is implemented in "Theme" class and its set as the theme of the app
To customize the theme, go to /resources/style/README.md

### Navigation
Navigation is implemented in "App" class, with the help of Wt::WNavigation and it has intarnal path suport(it works for going back and forword between URL pages)
This is not a big deal but its nice to have it from the start. It even comes with PageOne and PageTwo classes that are containers of the contents in page one and two menu

### Dockerfile 
In case you want to run this in a container, you have a dockerfile to :D

### Jenkins
Jenkins file ready to go, working with script files from folder /scripts for building, testing and deploying the app

### Sqlite database
Sqlite3 is implemented in the backend Tier

### Example of putting and getting data from the dbo 
The example PageOne has a form with different data types and a table witch represents the table in the sqlite dbo
You can put rows in table, modify data individualy, and every change you make in the table is reflected in the dbo

