/*
 * Guide Stone for Locating Gelan Locations
 *
 * This is an adaptation of the Sparkle Guide Stone that will
 * assist in the finding of places in Gelan, including the Academy
 * of Elemental Arts and the Cadets of Gelan. This should be especially
 * useful for beginners.
 *
 * Created by Petros, April 2011
 */

#pragma strict_types
#include <macros.h>
#include <files.h>
#include <cmdparse.h>
#include <composite.h>

inherit "/d/Sparkle/area/city/obj/guide_stone";


public void
create_object()
{
    ::create_object();
        
    add_target("/d/Calia/guilds/academics/school/joinroom");
    add_target("/d/Calia/gelan/cadet/cadet_trainroom");
}

public void
hook_route_not_found(object player)
{
    player->catch_tell("You sense that the " + short() + " is too far "
        + "away from your chosen destination to guide you there.\n");
}

public void
hook_display_next_direction(object player, string next_dir)
{
    player->catch_tell("The light from the runes on the " + short() 
        + " bursts brightly for a moment and you suddenly sense the "
        + short() + " urging you to go " 
        + next_dir + ".\n");
}
