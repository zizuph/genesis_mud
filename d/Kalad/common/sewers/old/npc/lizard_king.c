/*     Created by:      Sir Toby, 97-09-27
 *     Location:        Lizard king 
 *     Modified:        
 */

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed"; 
#include "/d/Kalad/defs.h"

#define BODY	"/d/Kalad/common/sewers/arm/orange_scalemail.c"
#define	HEAD	"/d/Kalad/common/sewers/arm/black_scale_helmet.c"
#define ARMS	"/d/Kalad/common/sewers/arm/black_scale_sleeves.c"
#define LEGS	"/d/Kalad/common/sewers/arm/black_scale_leggings.c"
#define KEY	"/d/Kalad/common/sewers/obj/treasury_key.c"


void
create_monster()
{
    if (!IS_CLONE)
        return;


    set_race_name("lizard"); 
    set_name("Zelthor");
    add_name("king");
    add_pname("guards");

    set_gender(G_MALE);

    set_short("lizard king");

    set_long("This is a proud tall lizardman, it is the King of lizards. " +
	     "He looks hideous, his arms is bulging under the armours as " +
	     "well as the legs and it is not of fat. His skin is black.\n");

    set_adj("watching");
    set_adj("elite");
    set_adj("black");
    set_adj("guard");

    set_stats(({134+random(7),134+random(11),160+random(5),60,60,120+random(11)})); 

    set_alignment(-100);
    set_knight_prestige(50);   

    set_skill(SS_AWARENESS,40 + random(4));
    set_skill(SS_BLIND_COMBAT,80 + random(4));
    set_skill(SS_DEFENCE,80 + random(5));
    set_skill(SS_UNARM_COMBAT,100);

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);

    set_act_time(35);
    add_act("emote leans back in his throne.");
    add_act("emote adjusts his armours.");
    add_act("emote straightens his back.");
    add_act("emote sighs silently.");
    add_act("ponder should we go and raid Kabal?");

    set_cact_time(25);
    add_cact("emote grins at the thought of killing you.");
    add_cact("say I shall eat your corpse with delight.");
    add_cact("emote laughs at you without fear.");
    add_cact("emote smiles wickedly.");

return;
}


arm_me()
{
    object arm, arm2, arm3, arm4, key;

    seteuid(getuid(TO));


    arm = clone_object(BODY);
    arm->move(TO);

    arm2 = clone_object(HEAD);
    arm2->move(TO);

    arm3 = clone_object(LEGS);
    arm3->move(TO);

    arm4 = clone_object(ARMS);
    arm4->move(TO);

    command("wear all");

    key = clone_object(KEY);
    key->move(TO);

   MONEY_MAKE_PC(random(6))->move(TO,1);
   MONEY_MAKE_GC(random(11)+5)->move(TO,1);

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
        set_alarm(1.0, 0.0, "help_friend", attacker);
}


/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */


void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("say You will regret this stupid action.");
        command("kill " + lower_case(ob->query_real_name()));
    }
}



//------------ SPECIAL ATTACK ------------------------

int
special_attack(object ob)
{
    string phurt;
    mixed *hitres;

    if(random(100) > 75)
    {

    if (query_combat_object()->cb_tohit(-1, 70 + random(30), ob) < 1)
        return 0;

    hitres = ob->hit_me(random(150)+150,W_BLUDGEON,TO,-1);
    phurt = "";
    switch(hitres[0])
    {
        case 1..20:
            phurt = " with hardly any effect";
            break;
        case 21..40:
            phurt = " slightly";
            break;
        case 41..60:
            phurt = " hard";
            break;
        case 61..80:
            phurt = " viciously";
            break;
        default:
            phurt = " extremely hard";
    }

    tell_object(ob, query_The_name(ob)+ " swings his tail at you " +
		"and you are hit" +phurt+ "!\n");
    tell_watcher(QCTNAME(TO)+ " swings its tail at " +QTNAME(ob)+
                " and " +QTNAME(ob)+ " is hit " +phurt+ "!\n",ob);

    if(ob->query_hp() <= 0)
        ob->do_die(TO);
    return 1;
    }

return 1;
}



 