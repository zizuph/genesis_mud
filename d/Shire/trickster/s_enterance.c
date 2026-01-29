#pragma save_binary

inherit "/d/Shire/room.c";
#include "/d/Shire/common/defs.h"
#include "trickster.h"

#define ROAD_DIR "/d/Shire/rooms/road/"
void
create_room()
{
   set_short("A well concealed hole in the ground");
   set_long(
      "This room is a well concealed hole in the ground near the outskirts " +
      "of Bree.  It is a place where the mischievous lot, known as the " +
      "Tricksters, hang out.  There is a hole in the ground here which looks " +
      "somewhat inviting, as well as a ladder which leads downwards. " +
      "The only obvious way out of here is to crawl out of here, or to " +
      "head downwards down the ladder.\n");
   
   add_item("ladder", "This ladder certainly looks strudy enough to " +
      "support your weight.  It would probably hold up if you " +
      "went down it.\n");
   
   add_item(({"hole","holes"}),"Which hole did you wish to look at?  The "+
      "floor hole or the concealed hole?\n");
   
   add_item("concealed hole","This hole is very well concealed, hidden "+
      "for everyones view except for the select few that know of it's "+
      "existance.\n");
   
   add_item("floor hole",
      "The hole is lined with a slippery substance, which would " +
      "probably aid in someone sliding down it.  It would probably " +
      "be loads of fun if you were to jump down it.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   
//   add_exit(BREE_DIR + "ngreenway","out",0,2);
   add_exit("/d/Shire/bree/rooms/road/shedge07", "out");
   add_exit(TRICK_DIR + "ladder_room","down",0,2);
}

void
init()
{
   ::init();
   add_action("do_enter","enter");
   add_action("do_enter","jump");
}

int
do_enter(string str)
{
   if (!str)
      {
      NF("Enter what?\n");
      return 0;
   }
   if (str == "down hole" || str == "hole" || str == "down floor hole" || str == "floor hole")
      {
      if ((TRICK_DIR + "slide")->query_prop("_this_room_is_occupied"))
         {
         write("You still hear someone screaming down this hole. " +
            "You'll have to wait till the person still inside, to finish their "+
            "trip before you can go.\n");
         return 1;
       }
      TP->move_living("screaming down the hole", TRICK_DIR + "slide");
      return 1;
   }
   write("Enter the floor hole maybe?\n");
   return 1;
}
