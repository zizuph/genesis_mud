/*
 * uniform.c
 * Worn by npc named deanak
 * Ares, 2004
 *
 */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/solamn/splains/local.h"
#include "../defs.h"

string color = "blue";

/*I figure I made a messenger NPC for the Dragonarmies
 *so why not make something for enemies as well?
 *A uniform to mock the Dragonarmies! I'm sure kenders
 *will love it!
 *
 *Ares 2004
 */

void
create_armour()
{
    set_name("uniform");
    set_ac(3);
    set_at(A_ROBE);
    add_adj("old");
    add_adj("dragonarmy");
    set_short("old dragonarmy uniform");
    set_long(BS("This is an old uniform worn by an officer "+
    "some years back. It is a little faded. The new ones are "+
    "much nicer and not as restricting as this one is. ",SL));
    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
    add_prop(OBJ_I_COLORABLE, 1);
}


set_color(string new_color)
{
    color = new_color;
    if (color == "black")
      set_long("It's made of soft and thick material, but yet it's not " +
           "very heavy.\nIt is deep " + color + ".\n");
    else
      set_long(BS("It's made of soft and thick material, but yet it's not " +
           "very heavy. It is black but has a " + color + " tinge to it. " +
           "As you look closer you can see fine " + color + " threads woven into it.",SL));
}


string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + color;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_color(a[1]);
    init_arm_recover(a[0]);
}

