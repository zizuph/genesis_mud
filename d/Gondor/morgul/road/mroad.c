/*
 *	/d/Gondor/morgul/road/mroad.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/morgul/feeling.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

int
query_allow_escape(object victim, object *enemy)
{
    int     i,
            chance = 0;

    if (victim->query_npc())
        return 1;

    for (i = 0; i < sizeof(enemy); i ++)
        chance += enemy[i]->query_stat(SS_DEX);

    chance -= victim->query_stat(SS_DEX);
    if (chance > 90)
        chance = 90;
    else if (chance < 10)
        chance = 10;
    if (random(100) < chance)
        return 0;
    return 1;
}

int is_present(object x) { return (objectp(x) && objectp(present(x, TO))); }

/*
 * Function name: stop_escape
 * Description:   Prevents escape if in combat.
 */
int
stop_escape()
{
    object *enemy,
            attacker;

    /* original code. restore after we find out why enemy array
     * contains integers. gnadnar
     */
    enemy = filter((object *)(TP->query_enemy(-1)) - ({0}), "is_present", TO);

    if (!sizeof(enemy))
        return 0;

    if (!query_allow_escape(TP, enemy))
    {
        if (objectp(attacker = TP->query_attack()))
        {
            if (present(attacker, TO) && !interactive(attacker))
            {
                TP->catch_msg(QCTNAME(attacker)
                  + " stops you from running away!\n");
                say(QCTNAME(attacker)+" stops "+QTNAME(TP)+" from leaving.\n",
                    ({TP, attacker}) );
                return 1;
            }
        }  
    }
    return 0;
}

/*
 * Function name: check_allow
 * Description:   Makes npcs stop enemies from advancing towards Minas Morgul.
 */
int
check_allow()
{
    object stopper;

    if (stop_escape())
        return 1;

    if (query_feeling(TP) == -1)
        return 0;

    if (stopper = present("_stopping_npc",TO)) 
    {
        if (CAN_SEE(stopper,TP) &&
          (stopper->query_skill(SS_AWARENESS) > TP->query_skill(SS_SNEAK))) 
        {
            write(CAP(LANG_ADDART(stopper->query_race_name()))
              + " stops you from going that way.\n");
            return 1;
        }
        write("You sneak past the " + stopper->query_race_name() + "!\n");
    }
    return 0;
}

public int
block_npc(int flag = 0)
{
    if (!interactive(TP))
	return 1;

    if (flag)
	return check_allow();
    return stop_escape();
}
