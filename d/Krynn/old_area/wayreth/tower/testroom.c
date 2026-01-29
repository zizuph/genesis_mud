/*
   Wayreth. Testing room

   testroom.c
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
   set_short("Secured testing room");
   set_long("This pocket of space is where apprentices and wizards come " +
	"to test their magics. With the most powerful spells of " +
	"protection, nothing will escape this room into the rest of " +
	"the universe. Some of the most advanced magic ever has been " +
	"practiced in this room, and where this place is in relation " +
	"to the rest of the universe is one of the mysteries of Wayreth " +
	"Tower. Runes cover the obsidian floor and a diffused light, " +
	"akin to twilight, brightens the room. Nothing can be seen of " +
	"the outer limits of this room except for the portal that is " +
	"the only exit.\n");
	
   AI(({"runes","floor","obsidian","obsidian floor"}),
	"The runes of protection glow with a soft red light, keeping " +
	"those who practice their arts safe.\n");
   AI(({"outer limits","limits"}),
	"You can't see them as the light doesn't illuminate that far.\n");
   AI(({"portal","exit","south"}),
	"This dark portal leads back to the Tower of Wayreth, from " +
	"wherever it is you are.\n");
   AI(({"light","diffused light","twilight"}),
	"Though you can't see where it comes from, the light brightens " +
	"the majority of the room but fades at the outer reaches, making " +
	"this room seem quite large.\n");

   add_exit(WTOWER + "training", "south", 0);
   add_prop(OBJ_I_LIGHT, 2);
}


