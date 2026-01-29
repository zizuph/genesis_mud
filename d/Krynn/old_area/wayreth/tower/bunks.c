/*
   Wayreth. Apprentice Sleeping Bunks

   bunks.c
   -----------

   Coded ........: February 1997
   By ...........: Kentari

   Latest update : February 1997
   By........... : Kentari

*/

#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;


public void
create_tower_room()
{
   set_short("Apprentice Bunks");
   set_long("Though secluded, this room sees enough traffic to make " + 
	"it another test to be endured by the Apprentices of Wayreth. " +
	"At the front of the room " +
	"by the entrance are the bunks for the apprentices. In the " +
	"back of the room, a large red black and white curtain " +
	"separates the chamber for the full wizards. Silence is the " +
	"understood policy to be in effect here, and any loud noises " +
	"or chatter would seem out of place.\n");
	
   AI(({"bunks","bunk","apprentice bunks","front"}),
	"These plain bunks serve as the beds for the apprentices at " +
	"Wayreth Tower. A bit rickety and run down, and also subject to " +
	"the traffic going in and out of the chambers, the bunks are " +
	"something to be endured while learning the arts of magic.\n");
   AI(({"curtain","large curtain","middle","red black and white curtain"}),
	"Patterned with the three colors of the magic orders, this " +
	"curtain separates the chamber for the privacy and respect of " +
	"the full mages of Wayreth Tower.\n");

   add_exit(WTOWER + "meditation", "south", 0);
   add_exit(WTOWER + "wizsleep", "north", 0);
   add_prop(OBJ_I_LIGHT, 2);
}

public int
query_start_room() 
{
	return 1;
}

