/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * roam_half.c
 *
 * A roaming halfling in the town of Dabaay 
 * Goldberry - June 29, 1999 
 */

#include "/d/Terel/include/Terel.h"
inherit DABAAY_DIR + "npc/roamer";  
inherit "/std/act/domove";

#define WEP_DIR DABAAY_DIR + "weapon/"
#define ARM_DIR DABAAY_DIR + "armour/"

#include <ss_types.h>

int power;
void dress_me();
string adj1();
string adj2();

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    power = random(20) + 55;
    set_name("halfling");
    set_long(
        "A quite rugged-looking, sleepy-eyed halfling, who seems " +
	"to enjoy a long, meandering stroll.  From his appearance, " +
        "he appears to be a gardener of some sorts.\n");
    set_adj(adj1());
    set_adj(adj2());
    set_race_name("halfling");
    set_gender(MALE);
    set_alignment(random(400));

    set_stats(({power - random(10), 
                power, 
                power - random(5), 
                power - random(10),
                power - random(10),
                power - random(5)}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      power);
    set_skill(SS_PARRY,        power - random(10));
    set_skill(SS_WEP_POLEARM,  power);
    set_skill(SS_WEP_KNIFE,    power);
    set_skill(SS_BLIND_COMBAT, power - random(10));
    set_skill(SS_AWARENESS,    power - random(5));
    set_skill(SS_UNARM_COMBAT, power - random(10));
    
    add_prop(LIVE_I_QUICKNESS, power);
    add_prop(LIVE_I_NEVERKNOWN,1);
    
    add_prop(OBJ_M_HAS_MONEY, power * 5);
 
    set_restrain_path(DABAAY_DIR);
    set_random_move(random(10)+10);
    dress_me();
    set_stuffed(TO->eat_max());
}

void
dress_me()
{
    seteuid(getuid(this_object()));     
 
    clone_object(ARM_DIR + "stew_pot")->move(TO);
    clone_object(ARM_DIR + "fry_pan")->move(TO);
    if (random(10) > 4)
        clone_object(WEP_DIR + "hoe")->move(TO);      
    else
        clone_object(WEP_DIR + "trowel")->move(TO);      
    command("wield weapons");
    command("wear armours");
}

string adj1()
{
    string *adj1;
    adj1 = ({"wandering", "stumbling", "merry", "excited",
             "smiling", "wizened", "mysterious", "lean", 
             "bouncy"});
    return adj1[random(sizeof(adj1))];
}

string adj2()
{
    string *adj2;
    adj2 = ({"green-eyed", "bleary-eyed", "sleepy-eyed", "black-eyed",
             "weathered", "old", "tanned", "leather-skinned", "ancient",
             "tired", "stocky", "brown-haired"});
    return adj2[random(sizeof(adj2))];
}


