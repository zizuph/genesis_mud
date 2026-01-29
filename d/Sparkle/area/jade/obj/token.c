/*
 * /d/Sparkle/area/jade/obj/token.c
 * Token for the Runaway quest
 * Created 2017-01-27 by Martin Berka (Mar) for Genesis MUD
 */

#pragma strict_types

inherit "/std/object";
inherit "/d/Sparkle/area/jade/obj/throwable_item";

#include <macros.h>
#include <stdproperties.h>

string  token_from,
        token_for,
        stored_value;
