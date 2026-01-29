
/*
  A room in the foothills of Mount Kyrus
  One of the spheres for the Emerald Tomb quest is hidden in Calia here
  among the loose rocks. It re-appears on each reset_room().  
  One must have reasonable awareness and probably a few tries to find
  it. 

  Coded by Maniac 20/7/95
  Updated for sphere 15/11/96, Maniac.  

*/

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>

#undef ACTIVATE_ESQ

#define EMERALD_TOMB_QUEST_SPHERE "/d/Emerald/kroad/graveyard/obj/sphere2"
#define MIN_AWARENESS_ROLL 25

#include "foothill.h"

inherit "/d/Calia/std/std_foothills";

int sphere_present;

#ifdef ACTIVATE_ESQ
void
reset_room()
{
    sphere_present = 1;
}
#endif

void
create_room()
{
    make_the_room("There are a number of loose rocks strewn around " +
                  "the area at the base of the mountain.\n", 
                   "northeast", 0, 1);

    add_item(({"rocks", "loose rocks", "grey rocks"}), 
           "There are a lot of loose rocks on the ground " +
           "at the base of the mountain, grey and of varying " +
           "size.\n"); 


#ifdef ACTIVATE_ESQ
    add_prop(OBJ_S_SEARCH_FUN, "rock_search"); 
    add_prop(OBJ_I_SEARCH_TIME, 5); 
#endif

    add_exit(FOOTHILL+"fh37", "north");
    add_exit(FOOTHILL+"fh38", "northeast");
    add_exit(FOOTHILL+"fh46", "east");
    add_exit(FOOTHILL+"fh52", "southeast");
    add_exit(FOOTHILL+"fh36", "northwest");

#ifdef ACTIVATE_ESQ
    reset_room(); 
#endif
}


string
rock_search(object searcher, string str)
{
    object tp, sphere;

    tp = this_player(); 

    if (!objectp(tp)) 
        return "Huh?\n";

    if ((str == "rocks") || 
        (str == "loose rocks") || 
        (str == "grey rocks")) 
    { 
        if (sphere_present) 
        {  
             if (random(tp->query_skill(SS_AWARENESS)) > MIN_AWARENESS_ROLL)  
             { 
                 sphere = clone_object(EMERALD_TOMB_QUEST_SPHERE); 
                 if (!sphere->move(tp)) 
                 { 
                     sphere_present = 0; 
                     tell_room(this_object(), QCTNAME(tp) + " finds " +
                               "something in the rocks.\n", tp); 
                     return ("You find " + LANG_ASHORT(sphere) + "!\n"); 
                 } 
                 else 
                     return "You find something but lose it!\n"; 
             } 
             else
                 return ("You didn't find anything, but you feel you " + 
                         "may have missed something.\n"); 
         } 
         else 
             return "You didn't find anything in the rocks.\n"; 
    } 
    return "Your search reveals nothing special.\n"; 
}

