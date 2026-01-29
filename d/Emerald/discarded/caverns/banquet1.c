/*
 * BANQUET1.c
 * Main Banquet Hall
 * Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Main Banquet Hall");
   set_long("   The dining area is an impressive sight. The huge, strong "+
	    "tables look almost as if they are bending underneath the "+
	    "weight of the food and drink heaped upon their tops. There "+
	    "is food of all kinds, from all origins, and most of it is "+
	    "probably food stolen from the victims of piracy, along with "+
	    "the treasure came the food. Hanging along the wall are many "+
	    "trophies of piracy on the sea. Among the trophies you notice "+
	    "a cutlass, a shield, a banner, and, of course, brasierre. Each "+
	    "of the trophies have a rather mangled, makeshift plaque "+
	    "beneath them.\n\n");

   add_item("trophies","The trophies hang on the wall as "+
	    "reminders of great voyages and pillages of old.\n");
   add_item("trophy","Which one do you want to examine?\n");

   add_item("cutlass","The cutlass is a beautiful piece of "+
	    "weaponry. It has some runes etched on the blade. They "+
	    "read: Thonalis Seerig, Captain of the Protector Merisious. The "+
	    "plaque beneath reads: He was a worthy opponent.\n");

   add_item("shield","On the wall, the shield is the most "+
	    "visible item. It takes up roughly the size of a man and is "+
	    "emblazoned with the coat-of-arms of Meliticas, the warring "+
	    "kingdom of tyrannical power. The plaque reads: Belonged to "+
	    "a man-at-arms aboard the late Devastator.\n");

   add_item("banner","The banner of green and silver covers the "+
	    "top portion of the wall. It has a pictorial history of the "+
	    "rise and fall of the late king Endorillig of the Elves. The "+
	    "most well embroidered part is the account of his experiences "+
	    "with the mer-people of elvish legend. The plaque reads: "+
	    "Interesting account of Elvish legends. Not much to put stock "+
	    "with.\n");

   add_item(({"bra", "brassier"}),
	    "The bra is hanging loosely "+
	    "on the wall. It is frilly and of a white colour with "+
	    "flowered print. The plaque below reads: A token of affection "+
	    "for the whole crew from Lillian Petrontig. Wow.\n");

   add_exit(THIS_DIR + "foodhall", "west");
   add_exit(THIS_DIR + "banquet2.c", "north");
   add_prop( ROOM_I_INSIDE, 1 );
   set_alarm(0.0,0.0,"reset_room");
}

void
init()
{
   add_action("get_bra", "get");
   ::init();
}

int
get_bra(string str)
{
   if(str != "bra" || str != "brassier")
      return 0;
   if (this_player()->query_gender() == 0)
      write("Wouldn't you look silly with that?\n");
   if(this_player()->query_gender() == 1)
      write("You check and make sure you already have one.\n");
   if (this_player()->query_gender() == 2)
      write("You don't like anything to do with gender.\n");
   return 0;
}

reset_room()
{
   int n;
   if (present("pirate")) return;
   n = 4;
   seteuid(getuid(this_object()));
   set_alarm(1.0,0.0,"dinner_time",n);
}

dinner_time(n)
{
   object ob;
   ob = clone_object(THIS_DIR+"npc/diner");
   if (!ob) return;
   ob->move(this_object());
   tell_room(this_object(), capitalize(LANG_ADDART(ob->
            query_nonmet_name())) + " stands from the table and faces you.\n");
   n--;
   if(n>0) set_alarm(0.0,0.0,"dinner_time",n);
}

