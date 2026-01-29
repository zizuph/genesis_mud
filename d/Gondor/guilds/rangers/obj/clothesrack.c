/*
 * /d/Gondor/guilds/rangers/obj/clothesrack.c
 *
 * Coded by ?
 *
 * Modification log:
 *   Gwyneth, 6 May 2004
 */
inherit "/std/receptacle";
#include <stdproperties.h>

void
create_receptacle()
{
    set_short("tall clothes stand");
    set_name("stand");
    add_name("rack");
    add_adj(({"tall", "clothes"}));
    set_long("This tall clothes stand is made of iron painted in " +
        "a heavy-duty black lacquer. It is strong and sturdy. You " +
        "can put your clothes here to keep them dry while you bathe.\n");

    add_prop(CONT_I_WEIGHT,     10000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME,     100000000);
    add_prop(CONT_I_MAX_VOLUME, 10000000000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_CLOSED,     0);
}
