/* room coded by Elizabeth Cook/Mouse, September 1996 */

inherit "std/room";
#include <stdproperties.h>
#include <ss_types.h>
#include "../../mouse.h"

int searched;

   void create_room() {
     int i;
     searched=0;        
     add_prop(OBJ_S_SEARCH_FUN, "search_fun");
     add_prop(OBJ_I_SEARCH_TIME, 5);
     add_prop(ROOM_I_LIGHT,1);
     add_prop(ROOM_I_INSIDE, 1);
     set_short("In the sleeping chamber");
     set_long("   This chamber is similar to the one you just left, but "+
          "it is noticeably darker. One corner of the room is occupied "+
          "by a bed of fine wood chips the mother beaver has fashioned "+
          "for her kits. The young kits play and explore between "+
          "periods of sleep. While they scamper unaware, the mother "+
          "and yearlings keep watchful eyes on them, and you.\n");
     add_item("chamber", "The walls, floor and ceiling are the same as "+
          "in the room south of here.\n");
     add_item("bed", "A soft pile of wood chips the mother beaver spent "+
          "long days preparing for the newest additions to her family.\n");
     add_item("wood chips", "Soft white pieces of wood the mother beaver "+
          "nibbled until they were as small as possible, in order to "+ 
          "make a soft bed for the kits.\n");

     clone_object(ROOT+"pond/mons/beavermom.c")->move(TO);

     for(i=0;i<4;i++)
         clone_object(ROOT+"pond/mons/beaver_yearling.c")->move(TO);
     for (i=0;i<4;i++)
         clone_object(ROOT+"pond/mons/beaver_kit.c")->move(TO);

     add_exit(ROOT+"pond/rooms/beaver_room4","south");
}

void reset_room()
{
     int i;
     searched=0;
     if(present("beaver"))
        return;
     clone_object(ROOT+"pond/mons/beavermom.c")->move(TO);

     for(i=0;i<4;i++)
         clone_object(ROOT+"pond/mons/beaver_yearling.c")->move(TO);
     for (i=0;i<4;i++)
         clone_object(ROOT+"pond/mons/beaver_kit.c")->move(TO);
}
     

string
search_fun(object player, string str)
{
    if((str == "bed") || (str=="wood chips"))
    {
        if (! searched)
        {
           clone_object(ROOT+"pond/items/iring.c")->move(TP);
           searched = 1;
           return "You discover an ivory ring buried beneath the wood chips.\n";
        }
        else
            return "There is nothing here now but wood chips.\n";
    }
    return "";
}
