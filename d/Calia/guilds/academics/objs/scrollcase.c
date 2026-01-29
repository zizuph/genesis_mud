/*
 * Scrollcase for the Academics.
 *
 * The guild object for the Academy of Elemental Arts. It really doesn't
 * do anything except give them a description and let them know where
 * to get help files.
 * 
 * Created by Petros, December 2009
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

void
create_object()
{
    set_name("scrollcase");
    add_name("case");
    add_adj(({"rustic", "bamboo"}));
    add_name("academic_guild_object");
    set_long("This " + short() + " is given to each and every student "
        + "of the Academy of Elemental Arts. The case itself is made from "
        + "strips of bamboo, which have been laced together using smaller "
        + "intertwined vines. It looks like it has gotten a lot of use over "
        + "the years, and it is clear that it was passed down from a "
        + "previous student here at the Academy. It contains within it "
        + "scrolls which can be read using <help academic>.\n");

    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_M_NO_STEAL,1);
}
