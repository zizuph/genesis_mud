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
   set_short("Southern waiting room (Coffee room)");
   add_item(({"couch","couches"}),
	"These couches look soft and inviting.  Plain, yet suitable, " +
	"like most things around this tower of mysterious nature.\n");
   add_item(({"table","coffee table"}),
	"This stained table is made from a wood you can't quite seem to " +
	"recognize, and looks like a coffee table in all respects.  Wait! " +
	"It _is_ a coffee table!\n");
   add_item(({"wood","stained wood"}),
	"Though it seems familiar, the wood of this table escapes " +
	"identity.  A rich stain covers the surface.\n");
   add_item(({"coffee","coffee-pot","mug","set","coffee mugs","porcelain",
		"mugs","porcelain coffee mugs","steaming coffee-pot"}),
	"This beautiful set is made of plain, delicate porcelain. " +
	"Contained within the coffee-pot is of course coffee, at just " +
	"the right temperature, the aroma of which is quite inviting.\n");
   add_item(("tea"),
	"No, no, there is no tea here, just coffee.  Besides, tea " +
	"will stunt your growth, didn't you know?\n");
   add_item(({"placard","silver placard","small placard"}),
        "For a mug of coffee just 'pour coffee' for yourself and enjoy!\n");
   add_item(("fire"),
	"This little flame seems to give off just the right amount of " +
	"heat, and, unlike most fires, doesn't worry you at all about " +
	"burning you, which in itself is a bit alarming.\n");
   set_long("You are standing in a comfortable waiting room. " +
	"Comfortable couches, a table with a set of porcelain coffee mugs " +
	"a steaming coffee-pot, and a small golden placard, and a pleasant, " +
	"though most likely magical, fire adorn this room. " +
	"You feel at ease here and decide that it wouldn't be " +
	"so bad to wait here for a while.\n"); 

   add_exit(WTOWER + "guestroom", "northeast", 0);
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

	if ((str=="coffee")||(str=="mug of coffee"))
	  {
	     clone_object(TOBJ + "coffee")->move(TP);
	     write("You lift the steaming coffee-pot from the tray and " +
		"pour yourself a mug full of warm and refreshing coffee.\n");
 	     say(QCTNAME(TP)+ " pours a mug full of coffee.\n");
	     return 1;
	  }
	if ((str=="tea")||(str=="cup of tea"))
	  {
	     write("As you pick up the coffee-pot, you realize what it " +
		"contains and embarrasedly blush.  The tea is in " +
		"the other waiting room!\n");
	     say(QCTNAME(TP)+ " blushes as " +
		TP->query_pronoun() + 
                " tries to pour tea from a coffee-pot.\n");
	     return 1;
	  }
	NF("Pour some what?\n");
        return 0;
}            
