/*
 * /d/Gondor/guilds/rangers/obj/hamper.c
 *
 * Coded by ?
 *
 */
inherit "/std/receptacle";
#include <stdproperties.h>

void
create_receptacle()
{
    set_short("towel hamper");
    set_name("hamper");
    add_adj("towel");
    set_long("The towel hamper is large and deep. It is also " +
        "where the towels go after one has dried off.\n");

    add_prop(CONT_I_WEIGHT,     10000000);
    add_prop(CONT_I_MAX_WEIGHT, 100000000);
    add_prop(CONT_I_VOLUME,     10000);
    add_prop(CONT_I_MAX_VOLUME, 10000000000);
    add_prop(CONT_I_RIGID,      0);
    add_prop(CONT_I_CLOSED,     0);
}
