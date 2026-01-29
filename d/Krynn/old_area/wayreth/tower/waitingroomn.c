/*
   Wayreth.

   waitingroomn.c
   --------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 96/12/2
   By ...........: Kentari

*/

#include "/d/Krynn/wayreth/local.h"
#include <macros.h>
inherit TOWERROOM;


void
create_tower_room()
{
   set_short("Northern waiting room (Tea room)");
   add_item(({"couch","couches"}),
	"These couches look soft and inviting.  Plain, yet suitable, " +
	"like most things around this tower of mysterious nature.\n");
   add_item(({"table","coffee table"}),
	"This stained table is made from a wood you can't quite seem to " +
	"recognize, and looks like a coffee table in all respects except " +
	"that it currently has tea on it, not coffee.\n");
   add_item(({"wood","stained wood"}),
	"Though it seems familiar, the wood of this table escapes " +
	"identity.  A rich stain covers the surface.\n");
   add_item(({"tea","teapot","teacup","set","teacups","silver",
		"silver teacups","steaming teapot"}),
	"This beautiful set is made of a bright, polished silver. " +
	"Contained within the teapot is of course tea, at just the " +
	"temperature, the aroma of which is quite inviting.\n");
   add_item(("coffee"),
	"No, no, there is no coffee here, just tea.  Besides, coffee " +
	"will stunt your growth, didn't you know?\n");
   add_item(({"placard","silver placard","small placard"}),
	"For a cup of tea just 'pour tea' for yourself and enjoy!\n");
   add_item(("fire"),
	"This little flame seems to give off just the right amount of " +
	"heat, and, unlike most fires, doesn't worry you at all about " +
	"burning you, which in itself is a bit alarming.\n");
   set_long("You are standing in a comfortable waiting room. " +
	"Comfortable couches, a table containing a set of silver teacups, " +
	"a steaming teapot, and a small silver placard, and a pleasant, " +
	"though most likely magical, fire adorn this room. " +
	"You feel at ease here and decide that it wouldn't be " +
	"so bad to wait here for a while.\n"); 

   add_exit(WTOWER + "guestroom", "southeast", 0);
}

void
init()
{
   ::init();
   ADD("do_pour", "pour");
}

nomask static int
do_pour(string str)
{
	seteuid(getuid());

	if ((str=="tea")||(str=="cup of tea"))
	  {
	     clone_object(TOBJ + "tea")->move(TP);
	     write("You lift the silver teapot from the tray and pour " +
		"yourself a cup of warm and soothing tea.\n");
	     say(QCTNAME(TP)+ " pours a cup of tea.\n");
	     return 1;
	  }
 	if ((str=="coffee")||(str=="mug of coffee"))
	  {
	     write("As you pick up the teapot, you realize what it " +
		"contains and embarrasedly blush.  The coffee is in " +
		"the other waiting room!\n");
	     say(QCTNAME(TP)+ " blushes as " +
            TP->query_pronoun() +
		" tries to pour coffee from a teapot.\n");
         return 1;
	  }
	NF("Pour some what?\n");
	return 0;
}
