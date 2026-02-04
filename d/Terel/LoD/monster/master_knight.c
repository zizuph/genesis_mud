/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * master_knight.c
 *
 * a knight of the legion 921103 redhawk
 * Modified by Sorgum 941002
 */

#include "/d/Terel/include/Terel.h"
inherit "/lib/unique";
inherit LOD_DIR + "monster/legion_knight";

#include <ss_types.h>

void arm_me();

/*
 * Function name: query_chats
 * Description:   return list of chats for this monster.
 */
public string *
query_chats()
{
    return ({"The legion of darkness will rule the world.",
	     "Now you've made a mistake!  You are messing with the BAD boys."
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
    set_name ("knight");
    add_name("master_knight");
    set_short("master knight of the legion of darkness");
    set_long("A human knight that is a member of the powerful and evil " +
	     "legion of darkness, the legion which is known " +
	     "to take no prisoners.\n");
    set_adj("evil");
    add_adj("master");
    set_race_name("human");
    set_gender(MALE);
    set_alignment(-300);

    set_stats(({85, 75, 75, 90, 90, 90}));
    SET_MAX_HP;
    
    add_prop(LIVE_I_QUICKNESS, 90);
    AGGRESSIVE;
    
    set_skill(SS_DEFENCE,      65 + random(11));
    set_skill(SS_UNARM_COMBAT, 60 + random(11));
    set_skill(SS_PARRY,        60 + random(11));
    set_skill(SS_WEP_SWORD,    85 + random(5));
    set_skill(SS_AWARENESS,    80);
    set_skill(SS_BLIND_COMBAT, 70);
    arm_me();
}

void
arm_me()
{
    FIX_EUID;
    clone_unique(LOD_DIR + "armour/deaths_helmet",10,LOD_DIR +
                 "armour/steel_helmet",50)->move(TO);
    clone_unique(LOD_DIR + "armour/deaths_shield",10,LOD_DIR +
                 "armour/dark_shield",50)->move(TO);
    clone_object(LOD_DIR + "armour/deaths_chainmail")->move(TO);
    clone_object(LOD_DIR + "weapon/deaths_sword")->move(TO);
    command("wield all");
    command("wear all");
    return;
}
