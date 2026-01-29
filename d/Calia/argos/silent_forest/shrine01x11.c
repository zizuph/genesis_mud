/*
 *   shrine01x11.c
 * 
 *  A shrine, with the entrance to the lower
 *  crypt chamber.
 *
 * Baldacin@Genesis, Sep 2003
 */

#pragma strict_types
#include <stdproperties.h>
#include <ss_types.h>
#include "ldefs.h"
inherit "/std/room";

public void
create_room()
{   
    set_short("Inside a holy sanctuary");
    set_long("Inside a holy sanctuary, the whole room is filled with a "+
      "divine aura@@get_aura@@. A large crystal altar has been placed "+
      "in the very center of the room. Large pillars encircle the altar, "+
      "stretching from the floor all the way up to the ceiling, giving the "+
      "chamber a good base foundation.\n");
    
    add_item(({"crystal altar", "altar"}),"It is a platform-shaped table, "+
      "most likely used for sacrifices or other religious ceremonies. "+
      "The crystal material it was chipped from gleams with a mysterious glow. "+
      "A pattern resembling an ancient dragon has been etched into the surface.\n");
    add_item(({"pattern", "surface", "dragon"}),"A pattern resembling an ancient dragon "+
      "has been etched into the surface of the altar.\n");
    add_item(({"pillar", "pillars"}),"The pillars encircling the altar are made "+
      "of pure crystal, gleaming with a mysterious glow. They are without any "+
      "markings or patterns.\n");
    add_item(({"divine aura","aura"}),"The room is filled with a divine aura"+
      "@@get_aura@@.\n");
	
    add_prop(OBJ_S_SEARCH_FUN,"search_floor");

    add_exit(SFDIR + "forest01x10.c", "south");
}

string
get_aura()
{
    if (TP->query_alignment() > 0)
        return ", warming your soul";
    return ", sickening your wicked soul";
}
string
search_floor(object me, string arg)
{
   string *allowed_args = ({"crystal altar", "altar"});
   
   if (member_array(arg, allowed_args) != -1)
   {     
       if(me->query_skill(SS_AWARENESS) < (25 + random(5)))
           return "";
           
       add_exit(SFDIR + "shrine_low1.c","down");
       set_alarm(15.0,0.0,"remove_exit","down");
       return "You find some markings around the altar, as if it "+
         "was pushed to the side.\nYou summon all your strength "+
         "and manage to push it a few feet, revealing an opening "+
         "leading down!\n";
   }
   	
   return "";
}