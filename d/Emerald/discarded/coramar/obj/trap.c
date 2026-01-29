/*
 * TRAP.c
 * This is an animal trap. There should be several of these located
 * throughout the Coramar forest in Emerald. They are an interesting side
 * element to the quests that adds a lot of flavor, realism and character.
 * 
 * Alaron - Feb 1998
 */

#include "../coramar.h"
#include "../dirheader.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/receptacle";

object mygame;

nomask void set_game(object ob);
nomask mixed query_game();

void
create_container()
{
    set_name("trap");
    set_adj("small"); add_adj("game"); add_adj("pit");

    set_short("small game pit trap");

    set_long("It is a fairly small trap, and simply made. It is a small "+
             "hole dug in the ground. Resting atop a bed of grass and "+
             "leaves are various vegetables and plants which rabbits in "+
             "particular seem to enjoy. You notice the glint of several "+
             "sharp spikes beneath the leaves. When the game drops into "+
             "the hole to eat the food, the spikes should finish the "+
             "animal.\n");
    add_prop(OBJ_M_NO_GET,"It is a hole in the ground. How do you propose to pick that up?\n");

    /* Now we set the weight and volume of the trap, and the weight and volume
     * it can hold.
     */

    add_prop(CONT_I_RIGID, 1);    /* Makes the trap volume always the max */

    add_prop(CONT_I_WEIGHT, 20000);
    add_prop(CONT_I_VOLUME, 20000);
    add_prop(CONT_I_MAX_WEIGHT, 120000);
    add_prop(CONT_I_MAX_VOLUME, 120000);

    add_prop(CONT_I_CLOSED, 0);

    set_cf(this_object());

    add_prop(CONT_M_NO_INS, "You decide against putting things in the trap.\n");

    add_prop(OBJ_I_HIDE, 5); /* Hidden, but only hidden enough so animals don't see */
}

int
open()
{
    return 3;
}

int
close()
{
    write("You can't close this trap, it is a pit in the ground!\n");
    return 3;
}

public varargs string
short(object for_obj)
{
    return this_object()->query_short();
}

nomask void
set_game(object ob)
{
    if (ob) mygame=ob;
}

nomask mixed
query_game()
{
    if (mygame) return mygame;
    else
      return 0;
}
