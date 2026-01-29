#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/raum/std/jewelry.h"

inherit RAUM(std/jewelry);

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/join_beads.c
 * Purpose    : This is magical join necklace
 * Located    : Can be taken from sacrifice room.
 * Created By : Sarr  24.Apr.97
 * Modified By: 
 */



void
create_jewelry()
{
    set_name("pendant");
    add_name("_khiraa_joinchain_");
    add_adj("silver");
    add_adj("skull");
    set_short("silver skull pendant");
    set_ok_jewelry_slots(({ANSALON_JEWELRY_NECK}));
    set_long("A silver chain that holds a very detailed carving of a "+
    "grim looking skull. The eyes are carved in deep, and you see two "+
    "very tiny ruby gems in them.\n");

    set_jewelry_value(0);
}
