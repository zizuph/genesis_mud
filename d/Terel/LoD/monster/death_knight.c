/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * death_knight.c
 *
 * a knight of the legion 921103 redhawk
 * Modified by Sorgum 941029
 */

#include "/d/Terel/include/Terel.h"
inherit "/lib/unique";
inherit LOD_DIR + "monster/legion_knight";

#include <ss_types.h>
#include <money.h>

void arm_me();

/*
 * Function name: query_chats
 * Description:   return list of chats for this monster.
 */
public string *
query_chats()
{
    string *chats =  ({
	"You are lucky. I will kill you quickly and painlessly.",
	"The devil's work will be done.",
	"Now you have made a mistake!  Now you are messing with " +
	    "the devil's servant HA HA HA!.\n"
	 });

    return chats;
}

/*
 * Function name: query_spell_level
 * Description:   spell level is used in spell_attack()
 * Returns:       this knights spell level.
 */
public int
query_spell_level()
{
    return 3;
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
    add_name("death_knight");
    set_short("devil's knight of the legion of darkness");
    set_long("A human knight that is a member of the powerful and evil " +
	     "legion of darkness, the legion which is known " +
	     "to take no prisoners. This knight seems to work in " +
	     "the devil's leash, he evinces a really evil aura.\n");
    set_adj("evil");
    add_adj("devil's");
    set_race_name("human");
    set_gender(MALE);
    set_alignment(-500);

    set_stats(({99, 99, 110, 110, 110, 110}));
    SET_MAX_HP;
    
    add_prop(LIVE_I_QUICKNESS, 120);
    
    set_skill(SS_DEFENCE,      80 + random(11));
    set_skill(SS_UNARM_COMBAT, 80 + random(11));
    set_skill(SS_PARRY,        85 + random(11));
    set_skill(SS_WEP_SWORD,    99 + random(5));
    set_skill(SS_BLIND_COMBAT, 85);
    set_skill(SS_AWARENESS,    50);
    AGGRESSIVE;
    
    set_act_time(30);
    add_act(({"laugh","grin"}));
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

