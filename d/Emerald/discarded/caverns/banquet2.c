/*
 * BANQUET2.c
 * north banquet hall
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void dinner_time(int n);

void
create_cave()
{
   set_short("North Banquet Hall");
   set_long("   This is the north end of the smokey banquet hall of "+
	    "the pirates. There is evidence of pirate activity "+
	    "everywhere. You see a huge, wooden table stacked high "+
	    "with burnt cuts of meat. On the north wall is an "+
	    "elaborate figurehead from the bow of a majestic but "+
	    "seemingly ill-fated ship. In addition, there is a bust "+
	    "of a prominate pirate displayed on that wall. The room "+
	    "has a loud, boisterous feel to it. The tables in the "+
	    "southern section of the banquet hall are stacked high "+
	    "with hundreds of kinds of food, some of which you "+
	    "have never seen. The sight makes you wonder if some or "+
	    "all of that food is plunder.\n\n");

   add_item(({"tables", "southern section", "food"}),
	    "The food arrayed on the tables in the southern "+
	    "section of the banquet hall is far more than "+
	    "bounteous. The tables holding the food look as if they "+
	    "are going to crumble under the weight of the delights.\n");

   add_item(({"table","wooden table"}),
	    "This table is elegantly crafted in the finest teak in Emerald. "+
	    "The goblin that made it was very talented, indeed! It looks as "+
	    "though many feasts have been held upon it, and it seems "+
	    "that it will last for many more.\n");

   add_item(({"cuts of meat","meat cuts","meat","meats","burnt cuts of meat"}),
	    "The meat is stacked high upon the table. It is burned, "+
	    "but still edible.\n");
   add_item(({"bust","mishrak","bust of mishrak"}),
	    "This is a bust of Mishrak the Pirate.  The beard is tipped with "+
	    "black pearls. Around his neck is a thick necklace of "+
	    "jade.  The hat on his head is one of the fanciest ones you have "+
	    "ever seen.  What really grabs your eye is his lovely eyepatch. "+
	    "You wonder what lies beyond that patch: death or glory.\n");
   
   add_item(({"elaborate figurehead","figurehead","statue"}),
	    "The carved statue from the bow of the ship is a "+
	    "dedication to Neptune, God of the sea.\n");

   add_exit(THIS_DIR + "banquet1.c","south");
   
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   int n;
   if (present("pirate")) return;
   n = 5;
   seteuid(getuid(this_object()));
   set_alarm(1.0,0.0,"dinner_time",n);
}

void dinner_time(int n)
{
   object ob;
   ob = clone_object(THIS_DIR+"/npc/diner");
   if (!ob) return;
   ob->move(this_object());
   tell_room(this_object(), capitalize(LANG_ADDART(ob->
            query_nonmet_name())) + " stands from the table and faces you.\n");
   n--;
  if (n > 0)
    dinner_time(n);
}
