/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * small_guard.c
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
    return ({LOD_DIR + "armour/small_chainmail",
     	     LOD_DIR + "armour/small_helmet",
	     LOD_DIR + "armour/small_shield",
	     LOD_DIR + "weapon/short_sword"});
}

/*
 * Function name: query_chats
 * Description:   return list of chats for this monster.
 */
public string *
query_chats()
{
    return ::query_chats() +
	({"Just wait until my brothers come, they will kill you slowly."});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("guard");
    add_name("small_guard");
    set_short("small legion guard");
    set_long("A small elf guard who is a member of the evil legion " +
	     "of darkness - the legion who have sworn to take over the " +
	     "world so the power of darkness can rule forever in the " +
	     "world.\n");
    set_adj("small");
    set_race_name("elf");
    set_gender(MALE);
    AGGRESSIVE;
   
    set_stats(({30, 30, 30, 25, 25, 25}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      40 + random(5));
    set_skill(SS_UNARM_COMBAT, 25 + random(5));
    set_skill(SS_PARRY,        50 + random(5));
    set_skill(SS_WEP_SWORD,    20 + random(5));
}
