inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#define DOWNROOM CASTLE_DIR + "b1"
int do_climb(string str);


void
create_room()
{

  set_short("A blackened alcove");
  set_long("This dim alcove off the main entrance is lit only by "+
   "whatever light, sun or moon, manages to creep in through the "+
   "cracks in the outside wall.  Similarly, small holes, probably made by "+
   "the years and the elements have developed in the tile floor.  "+
   "The entrance to the castle is east.\n");

   add_item(({"light","sun","moon"}),
   "The dim surroundings make sunlight and moonlight equally "+
   "luminescent, no matter the time of day.\n");

   add_item(({"wall","outside wall","plaster"}),
   "The plaster of the outside wall has cracked and now would "+
   "permit small insects to wriggle into the castle.\n");

   add_item(({"holes","small holes"}),
   "The small holes have appeared as the tile flooring has failed, "+
   "though there is one particularly large hole in the center of the "+
   "flooring, big enough for an ox to fall into.\n");

   add_item(({"large hole","center of the floor","center"}),
   "This large hole leads down into darkness.\n");

  add_exit(CASTLE_DIR + "c1", "east", 0);
  add_prop(ROOM_I_INSIDE,1);

}


void
init()
{
    ::init();
    add_action("do_climb","climb");
    add_action("do_climb","crawl");
    add_action("do_climb","enter");
}

int
do_climb(string str)
{
   if(!str)
   {
     write(capitalize(query_verb())+ " what?\n");
     return 1;
    }
    if((str != "into hole") && (str != "down hole") && (str != "down into hole")  && (str != "hole"))
   {
     write(capitalize(query_verb())+ " where?\n");
     return 1;
    }
    write("You climb carefully into the unknown darkness below.\n");
   say(QCTNAME(TP)+" leaves climbing down a hole.\n");
   tell_room(DOWNROOM, QCTNAME(TP)+ " arrives climbing down "+
   "from the ceiling.\n");
   TP->move_living("M",DOWNROOM,1,0);
   return 1;

}
