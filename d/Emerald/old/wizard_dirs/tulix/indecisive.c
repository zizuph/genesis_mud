/* An indecisive monster. He just can't decide who to kill..... */
/* Coded for Godfire on 20/04/96, by Tulix III.                 */

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
#include "/d/Emerald/defs.h"
#include <filter_funs.h>

/* Prototype functions */
public void arm_me();
public void attack_random_enemy();


public void
create_monster()
{
    set_name("ummarr");
    set_race_name("ogre");
    set_short("indecisive ogre");
    set_adj("indecisive");
    set_long("This guy can't decide who to kill. "
        +"If attacked by a team, he will switch between attackers every "
        +"once in a while.\n"); 
    
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_gender(0);  /* male=0, female=1, other=2 */

    set_default_answer("The ogre can't decide how to reply...\n");
    
    /* stats -   STR  DEX  CON  INT  WIS  DIS  */
    set_stats(({ 100,  90, 120,  80,  70, 100}));
    refresh_mobile();
    set_alignment(-250);

    /* Set unarmed attacks and armour classes. */
    set_all_hitloc_unarmed(30);
    set_all_attack_unarmed(30,30);
    
    /* Set the all important skills. */
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_AXE, 80);
    
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);

    set_skill(SS_AWARENESS, 60);

    set_chat_time(7);              /* Set speaking interval         */
    add_chat("I wonder what I should do next?");
    add_chat("Any ideas what I should do now?");
    add_chat("I not sure if I'm a decisive person or not.");
    add_chat("Umm, errr, well...maybe.");
    
    set_cchat_time(2);            /* Set combat speaking interval  */
    add_cchat("Oh, er, who should I attack..?");
    add_cchat("Um, yes, perhaps that one...");

    set_act_time(10);
    add_act("ponder");
    add_act("think");
    add_act("shrug");
}

/*
 * Function name: arm_me()
 * Description:   Give the monster a few toys to play with
 */
public void
arm_me()
{
    object armour,weapon,beer;

    weapon=clone_object(CAVE_DIR + "wep/nemesis.c");
    weapon->move(this_object());

    armour=clone_object(CAVE_DIR + "arm/banded_mail.c");
    armour->move(this_object());

    armour=clone_object(CAVE_DIR + "arm/visored_helm.c");
    armour->move(this_object());
    
    armour=clone_object(CAVE_DIR + "arm/brig_leggings.c");
    armour->move(this_object());

    beer=clone_object(CAVE_DIR + "obj/strong_beer.c");
    beer->set_heap_size(20);
    beer->move(this_object());

    command("wield all");
    command("wear all");
}

/*
 * Function name: attack_object
 * Description:   This function is called when we attack another object
 * Arguments:     victim - The object we are currently attacking
 * Returns:       0 - continue with attack, 1 - do not continue with attack
 */
public int
special_attack(object victim)
{
    /* Once in every ten attacks, we (try to) drink another beer. */
    if (!random(10))
        command("drink beer");
    
    /* Once in every seven attacks, we switch to a random attacker. */
    if (!random(7))
        attack_random_enemy();

    /* Important - must return 0 to continue with normal attacks. */
    return 0;
}

/*
 * Function name: attack_random_enemy
 * Description:   Attack a different enemy
 */
public void
attack_random_enemy()
{
    object *living_list, me, env, new_target, old_target; 
    int size;

    me = this_object();
    env = environment(me);
    old_target = me->query_attack();

    /* Lets sort out all the living objects in the room. */
    living_list = FILTER_LIVE(all_inventory(env));

    /* Attacking yourself is probably not a good idea. */
    living_list -= ({ me });

    /* We don't want to fight our current attacker, either. */
    living_list -= ({ old_target });

    size = sizeof(living_list);
    if (size)
    {
        /* Pick a new target from the list */
        new_target = living_list[random(size)];
        
        /* Check to make sure the new target is on of our enemies. */
        if (new_target->query_attack() != me)
        {
            command("say Err, um, nah, perhaps not.");    
            return;
        }
        
        /* Ok, lets try to attack the new target. */
        if (new_target && present(new_target, env))
        {
            command("say Um, err, who to attack, I wonder...?");
        
            /* Note: we will only attack a new target if we can see them. */
            command("kill " + lower_case(new_target->query_real_name()));
        }
    }
    else
    {
        command("say Phew, I don't have to make a decision...!");
        return;
    }
}

/*
 * Function name: attack_object
 * Description:   This function is called when we attack another object
 * Arguments:     ob - The object we are about to attack
 */
public void
attack_object(object ob)
{
    ::attack_object(ob);
    
    /* Always best to fight while drunk. */
    command("drink 10 beers");

    return;
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    /* Always best to fight while drunk. */
    command("drink 10 beers");

    return;
}
