/*
 * This is an NPC named "Brooke".  She is called by stumble.c, and exists
 * to serve and watch over the Stumble Inn. 
 *
 * Jan 2021 - Lucius - Commented out set_living_name
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <const.h>
#include <ss_types.h>

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    if (!IS_CLONE)
	return;

    ::create_monster();
    set_name("brooke");
//    set_living_name("brooke");    
    set_race_name("halfling");
    set_adj(({"black-haired","smiling"}));
    set_long(
        "She is a pleasant-looking halfling who serves drinks in the "+
        "Stumble Inn.\n");

    default_config_npc(70);
    set_all_hitloc_unarmed(35);
    set_skill(SS_DEFENCE,      60);
    set_skill(SS_AWARENESS,    60);
    set_skill(SS_UNARM_COMBAT, 70);

    set_gender(G_FEMALE);
    add_prop(LIVE_I_QUICKNESS, 50);
    add_prop(LIVE_I_ALWAYSKNOWN, 1);

    add_prop(OBJ_M_NO_ATTACK,"She is much to helpful to want to do that.\n");

}

