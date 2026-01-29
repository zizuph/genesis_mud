
 /* 
    Turtle neck leftovers by Jaacar 

    Adjusted by Maniac 24/9/96
 */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_fish_meat()
{
    set_name("_turtle_neck_");
    set_pname("necks"); 
    add_adj("turtle");
    add_name("neck");
    set_short("turtle neck");
    set_long("It is a turtle neck.\n");
    set_amount(125);
    add_prop(OBJ_I_VALUE, 31);
    add_prop(FISH_I_FROM_THALASSIAN_SEA, 1);
}


int
do_wear(string str)
{
    object tp = this_player(); 

    if (str == "neck" || str == "turtle neck") { 
        tp->catch_msg("You try to wear a turtle neck, but " +     
                      "it doesn't fit.\n"); 
        tell_room(environment(tp), QCTNAME(tp) + " tries to " +
                      "wear a turtle neck but it doesn't fit.\n", tp); 
        return 1;
    } 
}


void
init()
{
    ::init(); 
    add_action(do_wear, "wear"); 
}
