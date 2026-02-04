/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * war_officer.c
 *
 * an elf guard 920921 Redhawk
 * Modified by Sorgum 941002
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "monster/legion_soldier";

#include <ss_types.h>

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({LOD_DIR + "armour/small_helmet",
             LOD_DIR + "weapon/dark_sword"});
}

/*
 * Function name: query_chats
 * Description:   return list of chats for this monster.
 */
public string *
query_chats()
{
    return
	({"I kill anyone that tries to disturb the planning of the battle"});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("officer");
    add_name("war_officer");
    set_short("war officer");
    set_long("A war officer that's on duty, he is responsible for how " +
	     "the battles go and how it's reported to his higher ranking " +
	     "officers; you can't really figure out this officer's " +
	     "ranking though.\n");
    set_adj("confident");
    add_adj("war");
    set_race_name("human");
    set_gender(MALE);
    set_alignment(-100);
    set_assist("mergula");

    set_stats(({125, 125, 125, 80, 80, 175}));
    SET_MAX_HP;
    set_skill(SS_DEFENCE,      60 + random(5));
    set_skill(SS_UNARM_COMBAT, 35 + random(5));
    set_skill(SS_PARRY,        75 + random(5));
    set_skill(SS_WEP_SWORD,    70 + random(5));
}
