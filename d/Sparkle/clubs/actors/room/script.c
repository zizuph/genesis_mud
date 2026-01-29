/*
 * The actors club scriptorium
 */
#pragma strict_types

inherit "/std/room";

#include <std.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

#include "actor.h"

public nomask void
create_room()
{
    setuid();
    seteuid(getuid());
    
    set_short("A scriptorium");
    set_long("This is obviously a scriptorium. The walls are covered with hangings to absorb sound, and the only furniture are low benches and tables covered with writing material.\n\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "south_of_sparkle.txt");

    add_exit(AC_ROOMS+"inner", "west");

    clone_object(AC_IBOARD)->move(this_object());
}
