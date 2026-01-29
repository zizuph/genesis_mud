/*
 * A stronger draconian soldier 
 */

#pragma save_binary
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/std/draconian.h"
#include <ss_types.h>
#include <macros.h>

inherit DRACONIAN;

/*
 * Function name: set_kapak_skills
 * Description:   Calc and set the stats and skills for the draconian.
 */
nomask static void
set_kapak_skills()
{
    int i, level;

    for (i = 0; i < 6; i++) /* 30 - 57 */
        set_base_stat(i, (random(4) + 3) * 6 + 12 + random(10));

    level = query_draconian_level();

    set_skill(SS_DEFENCE,     level * 6 + random(20) + 10);
    set_skill(SS_PARRY,       level * 6 + random(8) + 10);
    set_skill(SS_WEP_SWORD,   level * 6 + random(8) + 10);
    set_skill(SS_WEP_KNIFE,   level * 6 + random(8) + 10);
    set_skill(SS_WEP_CLUB,    level * 6 + random(8) + 10);
    set_skill(SS_WEP_POLEARM, level * 6 + random(8) + 10);
    set_skill(SS_WEP_JAVELIN, level * 6 + random(8) + 10);
    set_skill(SS_WEP_AXE,     level * 6 + random(8) + 10);
    set_skill(SS_AWARENESS,   level * 5);

    set_draconian_alignment();
}

/*
 * Function name: create_kapak
 * Description:
 */
public void
create_kapak()
{
}

/*
 * Function name: create_draconian
 * Description:
 */
nomask public void
create_draconian()
{
    set_kapak_skills();
    set_draconian_type(KAPAK);

    create_kapak();

    add_name("kapak");

    add_prop(OBJ_I_RES_FIRE, 80);
    add_prop(OBJ_I_RES_ACID, 100);    

/*
    add_act("emote flaps its wings.");
*/
}

/*
 * Function name: special_draconian_attack
 * Description:   Called from the draconian special_attack
 *                routine. By redefining this, draconians can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 */
public int
special_draconian_attack(object victim)
{
    // Cast spells
    return 0;
}

/*
 * Function name: second_life
 * Description:
 * Arguments:     killer - 
 * Returns:
 */
public int
second_life(object killer)
{
    object corpse;

    tell_room(E(TO),"The draconian melts down into a pool of " +
	      "liquid!\n");

    corpse = clone_object(ACID);
    corpse->set_my_victims(({ killer }) + killer->query_team_others());
    corpse->move(E(TO));
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */










