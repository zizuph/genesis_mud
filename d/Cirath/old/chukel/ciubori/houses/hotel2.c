/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/hotel2.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";

#include "defs.h"

void
create_room()
{
  	set_short("Small room in Ciubori City Hotel.");
  	set_long("This is a nicely furnitured room in 'Ciubori City Hotel'. It has "+
           	"a large bed that looks really nice to sleep in. There is a sign "+
           	"on one of the walls.\n");

/*  	add_item("sign","The hotel is closed by the Ciubori board of health.\n");
*/
  	add_item("sign","If you have a ticket you may type 'start here'\n"+
           	"to start here the next time you enter the game.\n"+
           	"You will quit automagically when you do so.\n");

  	add_cmd_item("sign","read",
               	"If you have a ticket you may type 'start here'\n"+
               	"to start here the next time you enter the game.\n"+
               	"Note that you will be logged out when you type\n"+
               	"'start here'.\n");

  	INSIDE;
  	
  	add_exit(CIU_HOU + "hotel", "down", 0, 1);
	reset_room();
}

init()
{
  	::init();
    	add_action("start","start");
}

int start(string s)
{
  	object ob;
	
	notify_fail("Start where?\n");
    	if(s!="here")
        	return 0;

  	if(!(ob=present("ciuboribille",TP)))
     	{
      	 	write("You don't have a ticket! You snort!\n");
       		return 1;
     	}
  
  	NF("start where?\n");
  	if(s!="here") return 0;

     	ob->remove_object();

     	TP->set_temp_start_location(CIU_HOU + "hotel2");

     	write("You will start here the next time you enter the game.\n");
  	TP->command("quit");
  	return 1;  
}
