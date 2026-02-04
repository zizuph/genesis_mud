/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/container";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO   this_object()

public void
init()
{
    ::init();
    add_action("do_drink", "drink");
}

public int
do_drink(string str)
{
    int ret;
    object drink;

    notify_fail("Drink what?\n");
    if (!str) return 0;
    if (!parse_command(str, TO, " %o [from] 'chalice' ", drink))
        return 0;

    if (ret = drink->drink_it(drink->query_name())) {
        write("You drink from the " + short() + ".\n");
    }
    return ret;
}

public void
create_container()
{
    set_name("chalice");
    add_name(MYSTIC_CHALICE);
    add_name("mystic_vessel");
    set_adj("silver");
    set_long(
       "It is a beautifully crafted silver chalice. It is covered with " +
       "intricate scroll-work design. Around the rim of the chalice are " +
       "the images of winged spirits holding four-pointed stars.\n");

    add_prop(CONT_M_NO_INS, "That may not be placed in the chalice.\n");
    add_prop(CONT_I_VOLUME, 100);
    add_prop(CONT_I_MAX_VOLUME, 730);
    add_prop(CONT_I_WEIGHT, 100);
    add_prop(CONT_I_MAX_WEIGHT, 730);
    add_prop(OBJ_I_VALUE, 208);
    add_prop("_can_hold_amount", 5);
}
