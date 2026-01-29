/*
 * A large chest that contains the reward for the White Towers quest.
 *
 *					Tricky, 28-2-92
 */
inherit "/std/container";

#include "defs.h"
#include "/sys/macros.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"

/* Prototypes */
void reset_container();

void
create_container()
{
    set_name("chest");
    set_adj("large");
    set_short("large chest");
    set_long(break_string(
	  "The large chest does not look weatherbeaten. It is made "
	+ "of oak, and you wonder who got it up here in the first "
	+ "place, since it looks very heavy.\n", 70));

    add_prop(CONT_I_MAX_WEIGHT, 700000);
    add_prop(CONT_I_WEIGHT,     699000);
    add_prop(CONT_I_MAX_VOLUME,  20000);
    add_prop(CONT_I_VOLUME,      10000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_NO_GET, "The large chest is much too heavy.\n");

    reset_container();
}

void
reset_container()
{
    add_prop(CONT_I_CLOSED, 1);		/* Close the chest */

    /* Get your nice robes here. */
    if (!present("quest_robe"))
	clone_object(STAND_ARMOUR + "tower_robe")->move(this_object());
}
