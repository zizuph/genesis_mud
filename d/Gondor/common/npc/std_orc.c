/* 
 *    /d/Gondor/common/npc/std_orc.c
 *
 * This orc will attack anyone attacking a member
 * of his team
 * copied in parts from /doc/examples/mobiles/troll.c
 *
 * Olorin
 *
 * Modification log:
 * Updated the code, Olorin, 26-may-1995
 * Updated the code, Boron, 30-may-1996
 */
#pragma strict_types

inherit "/std/monster.c";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/d/Gondor/common/lib/make_money.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

string  alignlook();
void    do_attack(object victim);
void    help_friend(object ob);

public void
create_monster()
{
    int     rnd = random(10) + 1;

    set_name("orc");
    set_pname("orcs");
    set_pshort("orcs");
    set_race_name("orc"); 
    set_adj(alignlook());
    set_long(BSN("A big and strong orc."));

    default_config_npc(20 + rnd);
    set_base_stat(SS_INT, 15+rnd/2);
    set_base_stat(SS_WIS, 15+rnd/2);
    set_base_stat(SS_DIS, 85+rnd/2);
    set_alignment(-100-rnd*20);
    set_skill(SS_WEP_SWORD,20+rnd);
    set_skill(SS_AWARENESS,15+rnd);
    set_skill(SS_WEP_CLUB,20+rnd);
    set_skill(SS_PARRY,15+rnd/2);
    set_skill(SS_DEFENCE,20+rnd);
    add_prop(CONT_I_HEIGHT,170+2*rnd);
    add_prop(CONT_I_WEIGHT,75000+1000*rnd);
    add_prop(CONT_I_VOLUME,70000+2000*rnd);    
    add_prop(LIVE_I_NEVERKNOWN,1);

    set_chat_time(15+random(15));
    add_chat("Let's hurry!");

    set_cchat_time(5+random(5));
    add_cchat("Finish him!");
    add_cchat("No prisoners, no witnesses!"); 
    add_cchat("@@loot_item");

    set_act_time(15+random(15));
    add_act("burp");
    add_act("get all");
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

void
arm_me()
{
    object wep, arm, roarm;

    seteuid(getuid(TO));

    if (1<random(5))
        clone_object(ARM_DIR + "orcstlarm")->move(TO);

    if (random(2)) 
    {
        wep = clone_object(WEP_DIR + "orcsword");
        clone_object(ARM_DIR + "orcshield")->move(TO);
    }
    else 
        wep = clone_object(WEP_DIR + "orcclub");

    wep->move(TO);
    command("wield all");
    command("wear all");

    get_money();
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
    int i = random(5);

    if (objectp(query_attack()))
        return;

    if (random(10))
        set_alarm(itof(i), 0.0, &help_friend(attacker));
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
    if (!objectp(ob) || objectp(query_attack()) ||
        !present(ob, ENV(TO)) || !interactive(ob) ||
        !CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO,ob))
        return;

    loot_list = all_inventory(ob);
    loot_list = filter(loot_list,"query_show_list", TO);
    command("say I'll kill " + ob->query_objective()
      + ", I want to have " + ob->query_possessive() + " "
      + (ONE_OF_LIST(loot_list))->short() + "!");
    command("kill " + ob->query_real_name());
}

string
alignlook() 
{
    string *alignlooks =
                 ({"grim", "grumpy", "cruel", "angry","beastly",
                   "mean", "dirty", "foul", "brutal", "battered", 
                   "sinister","wicked","evil","savage", "ugly", 
                   "dangerous"});
    return ONE_OF_LIST(alignlooks);
}

public void
init_attack()
{
    object *arr;
    int     i;

    if (objectp(query_attack()))
        return;
    if (query_friend_or_foe(TP) >= 0)
    {
        set_alarm(2.0, 0.0, &do_attack(TP));
        arr = (object *)query_team_others();
        for (i = 0; i < sizeof(arr); i++)
            arr[i]->order_attack_enemy(TO, TP);
    }
}

int
notify_you_killed_me(object player)
{
    set_alarm(2.0, 0.0, "command", "get all from corpse");
    if (player->query_npc())
        return 1;
    seteuid(getuid(TO));
    log_file("evilkill", player->query_name()
      + " ("+player->query_average_stat() + ") was killed by "
      + TO->query_name()+" on " + ctime(time())
      + " ("+file_name(ENV(TO))+").\n");
    return 1;
}

void
do_attack(object victim)
{
    if (objectp(query_attack()))
        return;
    if (!objectp(victim) || !present(victim,ENV(TO)) ||
        !interactive(victim) || !CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, victim))
        return;
    command("shout I'll kill this " + victim->query_race_name() + "!");
    command("kill "+victim->query_real_name());
}

void
order_attack_enemy(object commander, object victim)
{
    if (objectp(query_attack()))
        return;
    set_alarm(2.0, 0.0, "do_attack", victim);
}

int query_knight_prestige() {return 400;}

