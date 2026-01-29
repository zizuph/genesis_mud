/*
 * This file is FANGORN_NPC + "torchless_object.c"
 *
 * Last modified by Alto, 30 August 01 2002
 *
 */

#pragma strict_types

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void
create_monster()
{
    set_short("_torchless_object_");
    set_name("_torchless_object_");
    set_long("There is something strange here.\n");
    set_race_name("insect buzzing about");

    set_no_show();

    add_prop(OBJ_M_NO_GET, "The object cannot be taken.\n");
    add_prop(OBJ_I_VOLUME,      1);
    add_prop(OBJ_I_WEIGHT,      1);

}

int
init_attack()
{
    ENV(TO)->initiate_torchless();
    return 1;
}

