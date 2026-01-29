inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

string quest_hint();

void
create_room()
{

  set_short("A ruined entryway");
  set_long("The entryway to the castle is almost impassible. Blackened "
	+"white marble comprises the walls and floor, and huge brazen "
	+"doors lie on the floor, bent and mangled by the fury of the "
	+"Witchking's armies. Although there are large quantities of "
	+"rubble here, there is no dust. That alone is evidence of "
	+"inhabitance by the remnants of the so called Army of Angmar. "
	+"The vaulted ceiling above you is scarred by cracks and chips, "
	+"as well as by the huge black streaks caused by flames. Empty "
	+"torch brackets line the walls, giving some company to the "
	+"once beautiful cracked marble. To the east, a massive pile "
	+"of rubble blocks what was once a passage.\n");

   add_item(({"marble","white marble","floor","walls"}),
   "Once white, the marble floor and walls are now blackened by fire.\n");

   add_item(({"torch brackets","bracket","torch bracket"}),
   "Long ago rusted red, these iron brackets must have held "+
   "large torches in their era of use.\n");

   add_item(({"rubble"}),
   "Heaps of rubble lie about the room, broken statues and carven figures.\n");

   add_item(({"figures","figure","statues","statue"}),
   "They are broken into hundreds of pieces and are unrecognizable.\n");

   add_item(({"pile","massive pile of rubble","massive pile"}),
   "The massive pile of rubble, blocking what was the eastern "+
   "alcove apparently has fallen from the ceiling.\n");

   add_item(({"ceiling","cracks","chips","crack","chip"}),
   "The ceiling overhead is evidence of the floor above having taken "+
   "an extreme pounding in the battle that gutted this royal palace.\n");

   add_item(({"door","doors","brazen door","brazen doors"}),
   "@@quest_hint");

  add_exit(ANNUM_DIR + "am19", "south", 0,2);
  add_exit(CASTLE_DIR + "c2", "west", 0,2);
  add_exit(CASTLE_DIR + "c3","north",0,2);
  add_prop(ROOM_I_INSIDE,1);

}


string
quest_hint()
{
   if(TP->query_prop("_castle_quest_"))
   {
     return "These brass doors are probably the only thing of worth left in "+
   "this ransacked castle.  At a close glance they seem to be the "+
   "height of six men and width generous enough for fifteen to "+
   "walk abreast.  On the top door you see the emblem of a rayed sun.\n";
   }

   else return "These brass doors look extremely heavy.\n";
}
