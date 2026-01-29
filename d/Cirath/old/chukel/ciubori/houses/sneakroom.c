/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/sneakroom.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include <ss_types.h>
#include <language.h>
#include "defs.h"
#include <macros.h>
#define SBEACH (CIU_HOU + "sneakbeach")

int door = 0; /*closed */

void
create_room()
{
  	set_short("In a small room");  
  	set_long("You're standing inside a small room underneath the city wall. There's a "+
        	"ladder leading upwards and a door leading out. The door is closed.\n");
  
  	add_item("ladder","It's a wooden ladder leading down.\n");

  	INSIDE;
  	DARK;

  	add_exit(CIU_HOU + "sneakladder", "up", 0, 1);
  	add_exit(CIU_HOU + "sneakbeach", "north", "@@query_door@@", 1);
	reset_room();
}

void
init()
{
  	::init();
  	add_action("d_open","open");
  	add_action("d_close","close");
}

int query_door()
{
  	if (!door)
    	{
        	TP->catch_msg("You can't walk through a closed door.\n");
        	return 1;
    	}

  	return 0;
}

int d_open(string str)
{
  	NF("The door is already open!\n");

  	if (str == "door" && door == 0)
  	{
    	write("You open the door.\n");
    	say(QCTNAME(TP)+" opens the door.\n");
    	door = 1;
    	set_long("You're standing inside a small room underneath the city wall. There's a "+
             "ladder leading upwards and a door leading out. The door is open.\n");
    	SBEACH->ch_door(1);
    	return 1;
  	}
  	else if (str == "door" && door == 1) return 0;

  	NF("What?\n");
  	return 0;
}

int d_close(string str)
{
  	NF("The door is already closed!\n");

  	if (str == "door" && door == 1)
  	{
    		write("You close the door.\n");
    		say(QCTNAME(TP)+" closes the door.\n");
    		door = 0;
    		set_long("You're standing inside a small room underneath the city wall. There's a "+
             	"ladder leading upwards and a door leading out. The door is closed.\n");
    	SBEACH->ch_door(0);
    	return 1;
  	}
  	else if (str == "door" && door == 0) return 0;

  	NF("What?\n");
  	return 0;
}

int ch_door(int a)
{
  	if (!a)
  	{
    	door = 0;
    	tell_room(TO,"Someone closes the door from the other side.\n");
    	set_long("You're standing in a small room. The floor slopes into the water. "+
           "There's a door to the south. The door is closed.\n");
    	return 1;
  	}
  	door = 1;
  	tell_room(TO,"Someone opens the door from the other side.\n");
    	set_long("You're standing in a small room. The floor slopes into the water. "+
         "There's a door to the south. The door is open.\n");
  	return 1;
}
