/* Special brew made by Raspatoon for use in the polymorph quest.

   Coded by Maniac 29/8/95

*/

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "obj.h"
#include POLYMORPH_QUEST


void
create_object()
{
    set_name("brew");
    set_adj("strange");
    add_name(BREW_NAME);
    set_long("It's the strange brew that Raspatoon made for you. " +
             "It stinks so much that it must be really potent. " +
             "Better not drink it!\n");
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 0); 
    add_prop(OBJ_M_NO_GIVE, "Why give it away? It is so important to your " +
                            "quest!\n");
    add_prop(OBJ_M_NO_SELL, "Why sell it? It is so important to your " +
                            "quest!\n");
    add_prop(OBJ_M_NO_INS, 1);
}


void
lose_msg(object room)
{
    tell_room(room, "The " + short() + " breaks as it hits the ground.\n"); 
    remove_object();
}


void
leave_env(object old, object dest)
{
    if (dest->query_prop(ROOM_I_IS)) 
        set_alarmv(1.0, 0.0, "lose_msg", ({dest}));

    ::leave_env(old, dest);
}



int
drink(string str)
{
    if ((str != "brew") && (str != "strange brew")) {
        notify_fail("Drink what?\n");
        return 0;
    }
         
    this_player()->catch_msg("Your nose has a fight with " +
                  "your hands when you try to drink the strange brew. " +
                  "Your nose wins, hands down (pun intended).\n");  
    return 1;
}


void
init()
{
    ::init();
    add_action("drink", "drink");
}

