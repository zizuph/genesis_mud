/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tguard1.c
 *
 * A roaming halfling guard in the town of Dabaay 
 * Goldberry - October 19, 1999 
 */

#include "/d/Terel/include/Terel.h"
inherit DABAAY_DIR + "npc/militia";  
inherit "/std/act/domove";

#define WEP_DIR DABAAY_DIR + "weapon/"
#define ARM_DIR DABAAY_DIR + "armour/"
#define DAB_TOWN DABAAY_DIR + "town/"

#include <ss_types.h>

int power;
void dress_me();
string adj2();

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    power = random(40) + 55;
    set_name("town_guard");
    set_long(
        "A serious looking member of the town's militia. " +
	"His gaze travels over everything in the area.\n");
    set_adj("watchful");
    set_adj(adj2());
    set_race_name("halfling");
    set_gender(MALE);
    set_alignment(power * 5);

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
    set_skill(SS_UNARM_COMBAT, power);
    set_skill(SS_2H_COMBAT,    power - random(20));
    
    add_prop(LIVE_I_QUICKNESS, power);
    add_prop(LIVE_I_NEVERKNOWN,1);

    add_prop(OBJ_M_HAS_MONEY, power * 5);

    set_restrain_path(DAB_TOWN);
    set_random_move(random(20) + 10);
    dress_me();
    set_stuffed(TO->eat_max());
}

void
dress_me()
{
    seteuid(getuid(this_object()));     
 
    clone_object(ARM_DIR + "grd_helm")->move(TO);
    clone_object(ARM_DIR + "grd_chain")->move(TO);
    if (random(10) > 4)
        clone_object(WEP_DIR + "halberd")->move(TO);      
    else
        {
         clone_object(WEP_DIR + "dagger")->move(TO);      
         clone_object(WEP_DIR + "dagger")->move(TO);      
        }
    command("wield weapons");
    command("wear all");
}

string adj2()
{
    string *adj2;
    adj2 = ({"blue-eyed", "hazel-eyed", "black-eyed", "brown-eyed",
            "green-eyed","olive-skinned","brown-skinned",
            "tanned","dark-skinned","light-skinned","grey-eyed"});
    return adj2[random(sizeof(adj2))];
}

