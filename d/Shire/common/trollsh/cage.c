inherit "/d/Shire/room";
#include "../defs.h"
#include <stdproperties.h>

void add_stuff();
void
reset_room()
{
   add_stuff();
}

create_room()
{
    set_short("Inside a cage under the Trollshaws.");
    set_long("This cage is probably where you will spend your "
   	    +"last days. The door looks very sturdy and is made in some "
            +"troll-fashion. It is probably unbendable by even the "
            +"strongest of non-trolls. Looks like you are "
   	    +"out of luck.\n");
    
   add_item(({"door","lock","floor","cage"}),
         "The door to the cage is locked. Even such a crude lock will keep "
   +"you in here, as the bars are too strong for even you to bend, "
	+"as is the rest of the door.\n");

   add_item(({"bar","bars","wall","walls","cage bars"}),
   	 "The bars look pretty strong but not well attached to the cage. "
	+"Perhaps you can squeeze through them?\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    
   reset_room();
    
}

void
init()
{
   ::init();
   write("The cage door slams shut behind you, and you hear "+
   "the most horrible sound of your life as the lock snaps shut.\n");
   add_action("do_bend","bend");
   add_action("do_pick","pick");
   add_action("do_squeeze","squeeze");
   add_action("do_squeeze","push");

}

void
add_stuff()
{
   object bracelet;


   if(!present("bracelet"))
   {
   bracelet = clone_object(TROLLSH_DIR + "obj/bracelet");
   bracelet->move(TO);
   }

}
int
do_bend(string str)
{
    if (!strlen(str) || str != "bars")
        return 0;

   write("You try to bend the "+str+" but you're just too weak!\n");
   say(QCTNAME(TP)+ " tries to bend the "+str+" but is too weak.\n");
   return 1;

}

int
do_pick(string str)
{
   if(str = "lock")
   {
   write("You can't get any leverage on the tumbler, and fail.\n");
   say(QCTNAME(TP)+ " tries to pick the lock, but fails.\n");
   return 1;
   }
}

int
do_squeeze(string str)
{
   if(str != "through bars")
   {
   write("What?\n");
   return 1;
   }

   tell_room(TROLLSH_DIR + "hall_room", QCTNAME(TP)+ " jumps down from the cage.\n");
   write("You squeeze the bars and make an "+
   "escape. You climb down from the cage, into the room below.\n");
   say(QCTNAME(TP)+ " climbs down from the cage into the room below.\n");
   TP->move_living("M","/d/Shire/common/trollsh/hall_room",1);
   return 1;



}

