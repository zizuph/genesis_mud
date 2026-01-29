/*
 * /d/Gondor/minas/lib/master.c
 *
 * Modification log:
 * 20-jan-97, Olorin: typecasts
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object.c";
inherit "/d/Gondor/common/lib/tell_funcs.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/mordor/sys/clock.h"

#define SUNRISE  "Bells chime in all towers of Minas Tirith, "+\
    "announcing that a new day has begun.\n"
#define SUNSET   "Bells chime in all towers of Minas Tirith, "+\
    "warning about the day coming to an end.\n"

public void
sunrise()
{
    tell_players_in_dir("/d/Gondor/minas",            SUNRISE);
    tell_players_in_dir("/d/Gondor/minas/houses",     SUNRISE);
    tell_players_in_dir("/d/Gondor/minas/rooms",      SUNRISE);
    tell_players_in_dir("/d/Gondor/minas/harlond",    SUNRISE);
    tell_players_in_dir("/d/Gondor/anorien/pelennor", SUNRISE);
    tell_players_in_dir("/d/Gondor/minas/citadel",    SUNRISE);
}

public void
sunset()
{
    tell_players_in_dir("/d/Gondor/minas",            SUNSET);
    tell_players_in_dir("/d/Gondor/minas/houses",     SUNSET);
    tell_players_in_dir("/d/Gondor/minas/rooms",      SUNSET);
    tell_players_in_dir("/d/Gondor/minas/citadel",    SUNSET);
    tell_players_in_dir("/d/Gondor/minas/harlond",    SUNSET);
    tell_players_in_dir("/d/Gondor/anorien/pelennor", SUNSET);
}

public void
create_object()
{
    set_long("This is not an object to clone, but a master for daily messages\n"+
        "in Minas Tirith.\n");
    CLOCK->notify_dawn(sunrise);
    CLOCK->notify_dusk(sunset);
}
