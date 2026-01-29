/*
 * /d/Earthsea/gont/sewers/arm/turtle_shell.c
 *
 * This is the helmet that is left from the corpse of a sewer turtle
 * 
 * 
 *
 * AEG, March 2021
 */
#pragma strict_types

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include "../defs.h"

public void             create_armour();
public int              do_knock(string str);
public int              do_tip(string str);

public void
create_armour()
{
    set_name("shell");
    set_name("helmet");
    set_name("helm");
    add_name("slippery shell");
    add_adj("slippery");
    add_adj("green");
    set_short("slippery green shell");
    set_long("Once the shell of a sewer turtle, this carapace can now be "
           + "used as a makeshift helmet. The scales are chipped and scuffed "
           + "in a few places, but the overall shell looks solid. If you're "
           + "feeling forgetful, you could <knock> yourself on the head. "
           + "You could also <tip> your helmet respectfully.\n");
        
    set_ac(10 + random(5));
    set_at( A_HEAD );
    /*          impale  slash   bludeon */
    set_am(({   -1,      -1,      0 }));
    
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
}

/* Function name:       init
 * Description  :       adds the action
 */
public void
init()
{
    ::init();
    add_action("do_knock", "knock");
    add_action("do_tip", "tip");

}

public int
do_knock(string str)
{
    if (str == "shell" || str == "helmet")
    {
        if (!query_worn())
        {
            write("You must wear the shell to do this.\n");
            return 1;
        }
        write("Trying to help yourself remember, you knock yourself "
            + "on the helmet.\n");
        tell_room(environment(this_player()), 
            "Trying to remember something, " + QCTNAME(this_player())
          + " knocks " + this_player()->query_possessive()
          + " slippery green shell in an attempt to jar a memory "
          + "loose!\n", this_player());
        return 1;
        }
    
    notify_fail("Knock what?\n");
    return 0;
}


public int
do_tip(string str)
{
    if (!query_worn())
    {
        write("You must wear the shell to do this.\n");
        return 1;
    }
    write("You tip your slippery green shell respectfully.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
        + " tips " + this_player()->query_possessive()
        + " slippery green shell respectfully.\n", this_player());
    return 1;
}

    