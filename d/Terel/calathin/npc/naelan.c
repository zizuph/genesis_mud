/*  This is an NPC named "Naelan" Smitt. He is called by shop.c as a
 *  shopkeeper.  If he is killed, the shop will not function.  
 *
 *  Coded by Vader on 6/25/92
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#define HUNTING_TREVIN "_i_hunting_trevin"
#define KILLS_CAL "_kills_cal"
dress_me();

public string
reply_assassin()
{
    if(TP->query_prop(HUNTING_TREVIN))
    {
        command("say Yes, I saw him.");
        command("say He headed towards the southern port.");
        command("say Not a very friendly fellow that one.");
        return "";
    }
    return "";
}



void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("naelan");
    add_name("shopkeeper");
    add_name("smitt");
    set_race_name("human");
    set_long("Mr Smitt is the proud owner of the Magic Lamp, lamp shop. "
      + "Kill him, you\nwon't be able to trade!  Plus, you'll get "
      + "the locals MAD at you.\n");

    /* Average stat: 72
     */
    default_config_npc(72);

    /* But we want it to have more hitpoints
     */
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 70);
    set_skill(SS_UNARM_COMBAT, 80);
    set_hp(9999);

    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(50, 40);

    set_chat_time(15);
    add_chat("Boy, how I love my job.  The clean air!  The snow!");
    add_chat("You're not from around here, are you?");
    add_chat("How did you find your way through the forest?");

    add_chat("It's all diet.");
    add_chat("Ahhh.... Whatever.");
    add_chat("What is all this fuss about the one ring?");
    add_chat("I hear the ranks of the Solamnian Knights are thinning out.");
    add_chat("There is much mystery in the valley.");
    add_chat("How come nobody protects ME?");
    add_chat("Have you been to the orc caves?");
    add_chat("My brother Talok sells quality packs.");
    add_chat("I heard there are herbs growing in the forest."); 

    add_chat("I offer many more bargains than the dealers of Last or the gypsies!");
    set_act_time(1);
    add_act("close door");

    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 80);
    add_ask("tall wiry male human", reply_assassin, 1);
   
    dress_me();
}

void
dress_me()
{
    FIX_EUID;
    
    clone_object(CALATHIN_DIR + "armour/b_boots")->move(TO);
    clone_object(CALATHIN_DIR + "armour/gr_breeches")->move(TO);
    clone_object(CALATHIN_DIR + "armour/w_tunic")->move(TO);
    command("wear all");
}

void
do_die(object killer)
{
    int i;
    object *enemies;

    if (query_hp() > 0) return;
    enemies = query_my_enemies();
    for (i=0; i<sizeof(enemies); i++)
    {
        if(enemies[i]->query_prop(KILLS_CAL) > 6)
        {
            object kill_logger = find_object(CALATHIN_DIR+"obj/kill_logger");
            kill_logger->add_killer(enemies[i]->query_name());
        }
        enemies[i]->add_prop(KILLS_CAL,
                           enemies[i]->query_prop(KILLS_CAL) + 3);
    }
    if(killer->query_prop(KILLS_CAL) > 6)
    {
        object kill_logger = find_object(CALATHIN_DIR+"obj/kill_logger");
        kill_logger->add_killer(killer->query_name());
    }
    killer->add_prop(KILLS_CAL,
                       killer->query_prop(KILLS_CAL) + 3);
    ::do_die(killer);
}


