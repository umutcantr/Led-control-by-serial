# Led-control-by-serial
This project contains led on/off period control by uart data. 
# Usage
By default led on/off period is 1 second and echo incoming data. Period can be changed following uart commands;


>ledon=500 

Changes led on period to 500 milisecond.

>ledoff=500   

Changes led off period to 500 milisecond.

Echoing data stops with this uart command(also sets led on/off period 1 second);

>stop

With start command echo will start again;
>start
