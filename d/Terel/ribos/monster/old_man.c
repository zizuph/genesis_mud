/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * old_man.c
 *
 * Vader
 * Modified by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <money.h>

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({
            RIBOS_DIR + "weapon/club",
		});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("oldman");
    set_race_name("human");
    set_adj("foolish old");
    set_long("This foolish old man is protecting his home.\n");
    
    default_config_npc(20);

    SET_MAX_HP;
}

/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{
    ::equip_me();
    FIX_EUID;
    MONEY_MAKE_CC(20) -> move(TO);
}

/*
 * Function name: equip_actions
 * Description:   Initial commands (e.g. wield sword)
 */
public void
equip_actions()
{
    TO->command("wield club");
}
