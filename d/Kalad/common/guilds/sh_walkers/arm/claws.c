/*
 * /d/Kalad/common/guilds/sh_walkers/arm/claws.c
 * Created By :  Sarr
 * Modified By:  Rico
 * First Modif:  18.12.96
 */

inherit "/d/Kalad/std/armour";

#include "/d/Kalad/defs.h"
#include "../defs.h"

int
query_recover()
{
    return 0;
}

void
create_armour()
{
    set_name("gloves");
    add_name(({ "claws", "cat claws", "cat-claws" }));
    add_adj("cat");
    set_adj("steel");
    set_short("pair of steel cat-claws");
    set_pshort("pairs of steel cat-claws");
    set_long("These are unique gloves.  Very useful as a tool for "+
        "thieves.  The gloves, when worn, go up to the elbow.  There "+
        "are several slightly curved, steel spikes jutting out from "+
        "around the hand area.  These spikes would probably make "+
        "climbing a touch easier.\n");

    set_at(A_HANDS);

    set_ac(1);
    set_am(({ -2,  1,  1 }));  /* impale, slash, bludgeon */

    set_af(this_object());

    add_prop(OBJ_I_WEIGHT, (250 + random(50)));
    add_prop(OBJ_I_VOLUME, (150 + random(40)));
    add_prop(OBJ_I_VALUE,  (300 + random(75)));
}

/*
 * Function: wear
 * Purpose : Temporarilly increase the wearer's climb skill.
 */
mixed
wear(object what)
{
    set_this_player(environment(what));
    this_player()->set_skill_extra(SS_CLIMB, this_player()->
        query_skill_extra(SS_CLIMB) + 2);

    return 0;
}

/*
 * Function: remove
 * Purpose : Set the players climb skill back after removing claws.
 */
mixed
remove(object what)
{
    set_this_player(environment(what));
    this_player()->set_skill_extra(SS_CLIMB, this_player()->
        query_skill_extra(SS_CLIMB) - 2);

    return 0;
}

