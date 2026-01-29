/* This file is /d/Gondor/common/npc/std_isengard_orc.c */
/*                                                      */
/* This orc will attack anyone attacking a member       */
/* of his team                                          */
/* copied in parts from /doc/examples/mobiles/troll.c   */
/* Updated code, May 30, 1996 			        */
/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */

inherit "/std/monster";

#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/common/lib/logkill.c"

#include "/d/Gondor/defs.h"

void	help_friend(object ob);

create_monster()
{
    if (!IS_CLONE)
	return;
    set_name("orc");
    set_pname("orcs");
    set_short("orc");
    set_pshort("orcs");
    set_race_name("orc"); 
    set_adj(alignlook());
    set_long(BS("A big and strong orc.\n"));
    default_config_npc(20+random(10));
    set_base_stat(SS_INT, 15+random(5));
    set_base_stat(SS_WIS, 15+random(5));
    set_base_stat(SS_DIS, 85+random(5));
    set_hp(500+random(4)*100);
    set_aggressive(0);
    set_alignment(-100-random(5)*20);
    set_skill(SS_WEP_SWORD,20+random(10));
    set_skill(SS_WEP_CLUB,20+random(10));
    set_skill(SS_PARRY,15+random(5));
    set_skill(SS_DEFENCE,20+random(10));
    add_prop(CONT_I_HEIGHT,170+random(20));
    add_prop(CONT_I_WEIGHT,75000+random(10000));
    add_prop(CONT_I_VOLUME,70000+random(20000));    
    add_prop(LIVE_I_NEVERKNOWN,1);

    set_chat_time(15+random(15));
    add_chat("Let's hurry!");

    set_cchat_time(2+random(2));
    add_cchat("Finish him!");
    add_cchat("No prisoners, no witnesses!"); 
    add_cchat("@@loot_item");

    set_act_time(15+random(15));	
    add_act("burp");
    add_act("hiss");
    add_act("grin");		

    set_cact_time(2+random(2));
    add_cact("@@shout_loot_item");
    add_cact("scream"); 

    set_alarm(1.0, 0.0, get_money());
    seq_new("do_things");
    seq_addfirst("do_things","@@arm_me");
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

arm_me()
{
    object wep, arm, roarm;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(TO));

    if (1==random(2)) 
    {
        wep = clone_object(WEP_DIR + "orcsword");
        arm = clone_object(ARM_DIR + "dushield");
        arm->move(TO);
        command("wear all");
    }
    else 
    {
        wep = clone_object(WEP_DIR + "orcclub");
    }
    wep->move(TO);
    command("wield all");

    if (1<random(5))
      {
        arm = clone_object(ARM_DIR + "dustlarm");
        arm->move(TO);
      }
    command("wear all");
}


get_money() {
    make_money(random(50)+10,"copper");
    make_money(random(5),   "silver");
}

make_money(i,type) {
	object money;
	
	money=clone_object("/std/coins");
	money->set_heap_size(i);
	money->set_coin_type(type);
	money->move(TO,1);
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

    itof(i);
   
    if (query_attack())
        return;
 
    if (random(10))
        set_alarm(i, 0.0, help_friend(attacker));
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
        command("say I'll kill it, I want to have it's " 
           + (string)loot_list[random(sizeof(loot_list))]->short() + "!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}

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
query_knight_prestige() {return 400;}
