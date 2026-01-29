/* 
 *
 * A crack in the mountain leading to the tunnels
 *
 * (C) 2003 Jaacar (Mike Phipps)
 *
 * Thanks to Baldacin for the map :)
 *
 */

inherit "/std/room.c";

#include <ss_types.h>
#include "defs.h"

#define CONNECTING_ROOM "/d/Calia/argos/nwterr/rooms/wfpath6"

void
create_room()
{
    set_short("Inside a small crack in the mountain wall");
    set_long("Inside a small crack in the mountain wall. It is "+
        "almost pitch-black here, only a few rays of light enters "+
        "through the crack, breaking the darkness.\n");
      
    add_item("darkness","Pitch-black darkness fills the western "+
        "parts of the small chamber.\n");
    add_item(({"light","ray","ray of light","rays of light"}),""+
        "A few rays of light breaks through the crack opening to "+
        "the east, lighting the cave somewhat.\n");
    add_item(({"opening","crack opening","crack"}),"The crack is large "+
        "enough for you to crawl out through, but concealed enough "+
        "from the outside as to not notice it right away.\n");
   
    add_prop(OBJ_S_SEARCH_FUN,"search_darkness");
    add_prop(ROOM_I_NO_ALLOW_STEED,1);
    add_prop(ROOM_I_INSIDE,1);
   
    add_exit(CONNECTING_ROOM,"out",0,1);
    
}

string
search_darkness(object me, string arg)
{
   if (!CAN_SEE_IN_ROOM(TP))
       return "It is far to dark to search anything here. You find "+
         "nothing.\n";
       
   if (arg == "darkness" || arg == "the darkness")
   {     
       if(me->query_skill(SS_AWARENESS) < (25 + random(5)))
           return "You don't seem to find anything.\n";
           
       add_exit(ROOMS + "tunnel14_07.c","west");
       set_alarm(15.0,0.0,"remove_exit","west");
       return "You find a hidden exit in the darkness, leading west.\n";
   }
   	
   return "You don't seem to find anything.\n";
}