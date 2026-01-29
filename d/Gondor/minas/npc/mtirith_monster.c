/*
 *  /d/Gondor/minas/npc/mtirith_monster.c
 *
 *  Standard monster for Minas Tirith
 *
 *  Olorin, January 1995
 */
#pragma strict_types

inherit "/d/Gondor/std/monster";
inherit "/d/Gondor/common/lib/friend_or_foe";
inherit "/d/Gondor/common/lib/logkill.c";

#include "/d/Gondor/defs.h"

#define DID_ATTACK_MT_GATES    "_attacked_mt_gate"

public int		second_life(object killer);
public varargs int	query_friend_or_foe(mixed pl);

/*
 * Function name:	second_life
 * Description	:	add killer to minas tirith's enemies list
 * Arguments	:	object killer -- who did us in
 * Returns	:	0 -- we die
 */
public int
second_life(object killer)
{
    FIX_EUID
    M_TIRITH_MASTER->add_enemy(killer);
    return 0;
} /* second_life */


/*
 * Function name:	query_friend_or_foe
 * Description	:	mask parent to check minas tirith's
 *			enemies list
 * Arguments	:	mixed pl -- player name or object 
 * Returns	:	-1 = goblins, morgul mages, angmarim, align < -250
 *			 0 = others
 *			 1 = elves, rangers, paladines, align > 750
 */
public varargs int
query_friend_or_foe(mixed pl)
{
    if (stringp(pl))
    {
        pl = find_living(LOW(pl));
    }
    else if (!objectp(pl))
    {
        pl = TP;
    }

    if (!objectp(pl))
    {
        return 0;
    }

    if (M_TIRITH_MASTER->query_enemy(pl->query_real_name(),
        pl->query_race()))
    {
        return -1;
    }
  
    return ::query_friend_or_foe(pl);
} /* query_friend_or_foe */
