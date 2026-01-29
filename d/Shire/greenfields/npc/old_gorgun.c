#include "/d/Shire/sys/defs.h"
#include ORC_FILE

inherit "/lib/unique.c";
inherit ORCMAKER;
inherit KILL_LOGGER;

#include "/d/Shire/private/shire_admin.h"
#include MONEY_FILE
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
/* Gorgun, orc, wielder of Leech, leader of camp in Hsqwin Mountain
    5 April 1994 by Mayhem  
 */
/*
   Major reversions to make him a wolf-rider and to test out
    the new code for the orcmaker :-)
    Igneous Jan 98
   Added UNIQUE_WEAPON code to limit number of JBS in the game
    to a total of 10.
    Jaypeg Apr 99
   Changed to Gen-wide clone_unique code BS
    Jaypeg May 00
   added MAX_UNIQUE_ITEMS to manage max uniques items
    Finwe, Oct 2001

*/


void
create_orc()
{
    remove_adj(query_adj());
    remove_adj(query_adj());
    set_adj(({"filthy","long-armed"}));
    set_living_name("gorgun");
    set_name("gorgun");
    set_race_name("orc");
    set_long("This filthy, long-armed orc has an air of command about "+
      "him. While his bearing could never be described as regal or noble, "+
      "it still projects power and the impression of impatience and "+
      "strength.\n");
    set_alignment(-300-random(101));
    default_config_npc(70+random(6));
    set_base_stat(SS_STR, 200+random(30));
    set_base_stat(SS_CON,150+random(21));
    set_base_stat(SS_DEX,140+random(11));
    set_base_stat(SS_DIS,90+random(10));

    set_skill(SS_WEP_SWORD,90+random(11));
    set_skill(SS_DEFENCE,80+random(11));
    set_skill(SS_PARRY,75+random(16));
    set_skill(SS_AWARENESS,50+random(11));
    set_skill(SS_2H_COMBAT,75+random(26));
    set_skill(SS_BLIND_COMBAT,50+random(31));
    set_skill(SS_MOUNTED_COMBAT, 60 + random(11));
    set_skill(SS_RIDING, 90);
    set_skill(SS_WEP_KNIFE, 60 + random(10));
    set_skill(SS_WEP_AXE, 40 + random(15));
    set_skill(SS_WEP_POLEARM, 75 + random(5));

    add_chat("Where is that damned mage, he was supposed to be "+
      "here days ago.");
    add_chat("You there, find my lieutenant, I have a job for him.");
    add_act("wield scimitar");

    add_prop(LIVE_I_SEE_DARK, 4);
    add_prop("_ranger_m_no_disarm_drop", 1);
    add_prop("_live_m_no_drain", 1);
    MAKE_MONEY;
    set_kill_log_name("gorgun");
    set_kill_log_size(50000);

    // Movement stuff
    set_restrain_path(GREEN_DIR + "camp/");
    set_random_move(3,0);

}

void 
arm_shire_npc()
{
    object key,wep,arm,drink;

    seteuid(getuid(TO));
    key=clone_object(GREEN_DIR+"obj/hchest_key");
    key->move(TO);
    arm = clone_object(GREEN_DIR + "arm/hhelm");
    arm->move(TO);
    arm = clone_object(GREEN_DIR + "arm/hplate");
    arm->move(TO);
    arm = clone_object(GREEN_DIR + "arm/hboots");
    arm->move(TO);
    command("wear all");
    command("lower visor");

    switch(random(2)) 
   {
        case 0 :  clone_unique(GREEN_DIR+"wep/greysabre",MAX_UNIQUE_ITEMS,
                     "/d/Shire/orcmaker/wep/gthsword")->move(TO);
                  break;
        case 1 :  clone_unique(GREEN_DIR+"wep/magebane",MAX_UNIQUE_ITEMS,
                     "/d/Shire/orcmaker/wep/gthsword")->move(TO);
                  break;
    }

    command("wield all");
    drink = clone_object("/d/Shire/moria/obj/orcdrink");
    drink->set_heap_size(9);
    drink->move(TO);

    command("say Prepare to eat scimitar, scum.");

    // Mounting routines
    get_mount();
    set_alarm(0.1,0.0,mount_steed);
}

int
check_health()
{
    if (query_hp() <= (2 * query_max_hp() / 3))
    {
	if (!command("drink yummy"))
	    return 0;
	return 1;
    }

    return 0;
}


int
special_attack(object enemy)
{
    int flag;

    if (!random(4))
    {
	flag = check_health();
    }
    if (!flag)
    {
	flag = ::special_attack(enemy);
    }   
    return flag;
}

void
attacked_by(object ob)
{
    object *arr;

    ::attacked_by(ob);
    TELL_ADMIN("Gorgun was attacked by " + ob->query_cap_name() + "("+ob->query_average_stat()+") at " + ctime(time()));
}
