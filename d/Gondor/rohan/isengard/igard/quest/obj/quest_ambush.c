/*
 * This file is IGARD_QUEST_OBJ + "quest_ambush.c"
 *
 * Last modified by Alto, 5 December 2001
 *
 */

#pragma strict_types

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

public void
create_monster()
{
    set_short("_ambush_object_");
    set_name("_ambush_object_");
    set_long("There is something strange here.\n");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The object cannot be taken.\n");
    add_prop(OBJ_I_VOLUME,      1);
    add_prop(OBJ_I_WEIGHT,      1);

}


public int
remove_ambush()
{
    TO->remove_object();
    return 1;
}


public int
try_trap()
{
    if (TP->query_npc())
    {
        return 0;
    }

    TP->add_prop(IGARD_AMBUSHED, 1);

    if (!ENEMY)
    {
        TP->add_prop(ENEMY_OF_IGARD, 1);
    }

    set_alarm(0.5, 0.0, &write("A large net of meshing suddenly drops "
        + "over your head!\n"));
    set_alarm(0.5, 0.0, &tell_room(environment(TP), QCTNAME(TP) 
        + " stumbles as a large "
        + "net of meshing suddenly drops over " + HIS_HER(TP)
        + " head!\n", ({TP})));

    ENV(TO)->initiate_trap();
    ENV(TO)->spring_quest_trap();

    return 1;
 
}


int
init_attack()
{
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
    return 1;
    }

    set_alarm(3.0, 0.0, &remove_ambush());
    try_trap();
    return 1;
}

