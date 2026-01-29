/*
 * Farm NPC
 * by Finwe, August, 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include "/d/Faerun/flowers/flowers.h"

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";

#define FLOWER_KINDS ({ "columbine", "coneflower", "coreopsis", "freesia_pink", "freesia_white", "freesia_yellow"})
#define FLOWER_IDENT   8675309867 /* the large number. */
#define FLOWER_RANGE   6         /* the number of flowers. */
#define QUEST_NAME_PROP "_flower_quest"
#define PICKED_FLOWER    "_i_picked_flower"
void arm_me();
string flower_to_find = ONE_OF_LIST(FLOWER_KINDS),
    flower_name_prop = "",
    flower_name = "";

string check_flower_name();

void create_monster()
{
    int i;

    seteuid(getuid());
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    npc_name = "_farm_human";

    add_adj("frumpy");
    add_adj("cheerful");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    set_name(npc_name);
    add_name("_flower_npc");
    set_short("frumpy cheerful human");
    set_long("This is a " + query_short() + ". She has long brown hair tied into a ponytail. This is the mother of the farm and looks like she has spent all day cleaning the house. She is pudgy and looks like she takes care of everyone who lives on the farm.\n");
        
    set_gender(G_FEMALE);
    add_prop(CONT_I_WEIGHT,85000);
    add_prop(CONT_I_HEIGHT,190);
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 80 + random(25));
    set_base_stat(5, 80);

    set_alignment(110 + random(50));

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_2H_COMBAT, 50);

   /* Actions */
    set_act_time(5);
    set_cact_time(5);
    add_act("emote scurries around room, cleaning it.");
    add_act("emote chases a child away.");
    add_act("emote brushes out her apron.");
    add_act("emote smiles happily.");
    add_act("emote sighs deeply.");
    add_chat("This family keeps me busy.");
    add_chat("I love flowers.");
    add_chat("Please don't make a mess, I'll have to clean it up later.");

    set_cchat_time(5);
    add_cchat("Die, you scabrous mongrel!");
    add_cchat("What are you fighting me for?");
    add_cchat("You will die for this crime!");
    add_cchat("Just wait until my husband hears about this, he will kill you!");
    add_cchat("Take that, and that, and that!");
    add_cchat("I can't believe you are doing this!");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    arm_me();

    set_pick_up_team(({npc_name}));
    add_ask(({"quest", "help", "task", "flower", "flowers"}),
        VBFC_ME("ask_flower"));

}



void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

    wep = clone_object(FWEP_DIR + "butcher");
    wep -> move(TO);
    arm = clone_object(FARM_DIR + "dress");
    arm -> move(TO);

    command("wield weapon");
    command("wear all");
}

void
init_living()
{
    ::init_living();
    init_team_pickup();
}


string ask_flower()
{
    if(TP->test_bit(DOMAIN, FLOWER_QUEST_GROUP, FLOWER_QUEST_BIT))
    {
        command("emote smiles happily.");
        command("say Thank-you for your interest, but I believe you helped me already.");
        return "";
    }


    if (TP->query_prop(QUEST_NAME_PROP))
    {
        command("say Have you found the flower I was looking for " +
            "or have you forgotten? I'm looking for a " + check_flower_name() + ".");
        command("say If you haven't, I just know it grows somewhere around here.");
        return "";
    }
    command("say I love flowers, they are so beautiful but I have a hard time growing them. They smell wonderful and make me think of my childhood.");
    command("say I would be most appreciative if you found my favorite and brought it back for me. I have many favorites but today it is " + check_flower_name() + ".");
    command("say Thank you very much and good luck!");

    TP->add_prop(QUEST_NAME_PROP,1);
    return "";

}


void
test_quest(object player, object obj)
{

    if(TP->test_bit(DOMAIN, FLOWER_QUEST_GROUP, FLOWER_QUEST_BIT))
    {
        command("say Thank-you for the offer, but you helped me already.");
        return;
    }


    command("grin broadly");
    command("say Oooo, you found the flower!!!");
    command("say Thank-you so very much!!!");
    player->remove_prop(QUEST_NAME_PROP);
    player->remove_prop(PICKED_FLOWER);
    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " was rewarded.\n");
    TP->set_bit(FLOWER_QUEST_GROUP, FLOWER_QUEST_BIT);
    TP->add_exp_quest(FLOWER_QUEST_EXP);
    QUEST_LOG_FILE(FLOWER_QUEST_LNG, FLOWER_QUEST_EXP);


// time for a new flower.
     flower_name = ONE_OF_LIST(FLOWER_KINDS);

}

void
return_object(object from, object obj)
{
    string  obname = OB_NAME(from);

    if (obj->id("coin"))
    {
        command("say Thanks for the money!");
        return;
    }

    command("say Thank-you for this, but I do not need it.");
    write("The " + short() + " gives it back to you.\n");
    obj->move(from);
    return;
}


public void
enter_inv(object obj, object from)
{
    string flower_path = FLOWERS_DIR + flower_to_find;

    ::enter_inv(obj, from);
    if (!living(from))
        return;

    check_flower_name();

    if (MASTER_OB(obj)==flower_path)
    {
//        if(!from->query_prop(PICKED_FLOWER))
//        {
//            command("say Eww, yuck! This flower looks disgusting, like a troll found it or it was picked from the wilds! Please find me your own flower.");
//            command("shudder");
//            command("drop " + OB_NAME(obj));
//            return;
//        }

        set_alarmv(1.0,0.0,"test_quest",({from, obj}));
    }
    else
    {
        set_alarmv(1.0,0.0,"return_object",({from, obj}));
        return;
    }
}

string check_flower_name()
{
    switch(flower_to_find)
    {
        case "columbine" :    flower_name = "columbine"; break;
        case "coneflower":    flower_name = "coneflower"; break;
        case "coreopsis" :    flower_name = "coreopsis"; break;
        case "freesia_pink":  flower_name = "pink freesia"; break;
        case "freesia_white": flower_name = "white freesia"; break;
        case "freesia_yellow":   flower_name = "yellow freesia"; break;
        default: 
            flower_name = "broken flower. Please report this to a faerun wizard..";
            break;
    }
    flower_name_prop = flower_to_find + "_faerun_flower_";
    return flower_name;
}
