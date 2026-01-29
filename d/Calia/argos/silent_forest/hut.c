/*
 *   hut.c
 * 
 *  An old abandoned hut..
 *
 * Baldacin@Genesis, Nov 2003
 */
#include "ldefs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
inherit "/std/room.c";

int room_searched;

void
create_room()
{
    set_short("Inside an old rickety hut");
    set_long("You have stepped into an old rickety hut. It is "+
      "completely empty, save the piles of dust laying on the floor. "+
      "\n");
    
    add_item(({"dust", "pile of dust", "piles of dust"}), "Thick layers "+
      "of dust covers almost everything in this room. The drafty wind has "+
      "formed some piles of dust, especially along the floor.\n");
      
    add_prop(OBJ_S_SEARCH_FUN,"search_func");
    room_searched = 0;
   
    add_exit(SFDIR + "trail04","out");
    
}

string
search_func(object me, string arg)
{
   string *allowed_args = ({"dust", "pile of dust", "piles of dust"});
   
   if (member_array(arg, allowed_args) != -1)
   {     
       if(room_searched || me->query_skill(SS_AWARENESS) < (15 + random(5)))
           return "";
       
       object item = clone_object(SFOBJDIR+"shard");
       item->move(me, 1);
       room_searched = 1;
       return "You find "+LANG_ASHORT(item)+"!\n";
   }  
   return "";
}
