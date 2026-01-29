/* 
 *	/d/Gondor/common/npc/std_mordor_orc.c
 *
 * This orc has default chats/cchats, descriptions and equipment
 * to be used as an orc of the Red Eye, Mordor-orcs.
 * This orc will attack anyone attacking a member of his team.
 * Copied in parts from /doc/examples/mobiles/troll.c
 *
 *	Updated code, Boron, May 30 1996.
 */
#pragma strict_types
inherit "/std/monster";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/d/Gondor/common/lib/make_money.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

string  alignlook();

void
create_monster()
{
    set_name("orc");
    set_pname("orcs");
    set_pshort("orcs");
    set_race_name("orc"); 
    set_adj(alignlook());
    set_long(BSN("This is an ugly and dirty orc, with long arms and crooked legs. "+
    "On its armour you can see a crest painted: A red eye."));
    default_config_npc(20+random(10));
    set_base_stat(SS_INT, 15+random(5));
    set_base_stat(SS_WIS, 15+random(5));
    set_base_stat(SS_DIS, 85+random(5));

    set_alignment(-100-random(10)*20);
    set_skill(SS_WEP_SWORD,20+random(10));
    set_skill(SS_WEP_CLUB,20+random(10));
    set_skill(SS_PARRY,15+random(5));
    set_skill(SS_DEFENCE,20+random(10));
    set_skill(SS_AWARENESS,20+random(10));
    add_prop(CONT_I_HEIGHT,170+random(20));
    add_prop(CONT_I_WEIGHT,75000+random(10000));
    add_prop(CONT_I_VOLUME,70000+random(20000));    
    add_prop(LIVE_I_NEVERKNOWN,1);

    set_chat_time(15+random(15));
    add_chat("Let's hurry!");
    add_chat("When are we gonna eat?");
    add_chat("Let's find some humans to molest!");
    add_chat("I don't like running in the sunlight!");

    set_cchat_time(2+random(2));
    add_cchat("Finish it!");
    add_cchat("No prisoners, no witnesses!"); 
    add_cchat("Do you think we can eat this one right away?");
    add_cchat("Die, ugly dog!");
    add_cchat("@@loot_item");

    set_act_time(15+random(15));	
    add_act("burp");
    add_act("hiss");
    add_act("grin");		

    set_cact_time(2+random(2));
    add_cact("@@shout_loot_item");
    add_cact("scream"); 
}

int
query_show_list(object x)
{
    return !((x->query_no_show()) || (x->query_prop(OBJ_I_INVIS)));
}

string
loot_item()
{
    object *loot_list,
	    tp = TP;

    if (!interactive(tp) ||
	!present(tp, ENV(TO)))
    {
        return "";
    }
    loot_list = filter(all_inventory(tp), query_show_list);
    if (!sizeof(loot_list))
        return "I want to kill " + OBJECTIVE(tp) + "!";

    return "I want to have " + POSSESSIVE(tp) + " "
      + (ONE_OF_LIST(loot_list))->short() + "!";
}

string
shout_loot_item()
{
    return "shout "+loot_item();
}

public void
arm_me()
{
    object wep, arm, roarm;

    seteuid(getuid(TO));

    if (random(2)) 
    {
	clone_object(WEP_DIR + "orcscim")->move(TO);
	clone_object(ARM_DIR + "reshield")->move(TO);
    }
    else 
	clone_object(WEP_DIR + "orcclub")->move(TO);
    command("wield all");

    clone_object(ARM_DIR + "releather")->move(TO);
    command("wear all");
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(TO, ob);
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;

    if (random(10))
        call_out("help_friend", random(5), attacker);
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
    object *loot_list;
    if (ob && !query_attack() && present(ob, environment()))
    {
        loot_list = all_inventory(ob); /* lower_case(ob->query_real_name()));*/
        loot_list = filter(loot_list,"query_show_list", TO);
        command("say I'll kill it, I want to have its " 
           + (string)loot_list[random(sizeof(loot_list))]->short() + "!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}

string
alignlook() 
{
    string *alignlooks;
    alignlooks = ({"grim", "grumpy", "cruel", "angry","beastly",
                   "mean", "dirty", "foul", "brutal", "battered", 
                   "sinister","wicked","evil","savage", "ugly", 
                   "dangerous"});
    return alignlooks[random(sizeof(alignlooks))];
}

/* Solemnian prestige */
int query_knight_prestige() {return 575;}

void
init_attack()
{
    object  victim;

    if (objectp(query_attack()))
        return;

    if ((victim = TP)->query_npc())
        return;
    if (!IS_GOOD(victim))
        return;

    set_alarm(0.0, 0.0, &command("kill "+victim->query_real_name()));
}

