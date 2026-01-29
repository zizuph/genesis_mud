/* The Ogre Lord (humanoid) - Recoded 18/07/95, Tulix III */
/* Cloned by cave /d/Emerald/cave/levelc/24c.c */

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"

void
create_monster()
{
    set_name("kraucher");
    set_race_name("ogre");
    set_short("Lord ogre");
    set_adj("lord");
    add_name("lord");
    set_long("This is a very big and very nasty ogre. "
        +"He looks a bit of a big-head: too big for his boots. "
        +"Judging by the scars, he has seen a lot of fighting and "
        +"he has a certain menacing quality about him that sets him "
        +"apart from the other ogres. What really catches your eye, "
        +"however, is the sword he is wielding - it looks very similar "
        +"to the fabled Nemesis sword that you have heard about.\n"
        +"But to suppose it still exists (if it ever did exist!) would be "
        +"a little too far fetched for anyone sensible.\n"); 
    
    add_prop(CONT_I_WEIGHT,80000);
    add_prop(CONT_I_HEIGHT,250);
    add_prop(LIVE_I_QUICKNESS, 250);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_gender(0);  /* male=0, female=1, other=2 */

    set_default_answer("The Lord ogre points his sword at you...\n");
    /* stats -   STR  DEX  CON  INT  WIS  DIS  */
    set_stats(({ 190, 190, 190, 140, 140, 160}));
    set_hp(20400);
    set_alignment(-250);

    /* Set unarmed attacks and armour classes. */
    set_all_hitloc_unarmed(60);
    set_all_attack_unarmed(40,50);
    
    /* Set the all important skills. */
    set_skill(SS_WEP_SWORD, 150);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_AXE, 80);
    
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 150);

    set_skill(SS_AWARENESS, 100);

    set_chat_time(25);              /* Set speaking interval         */
    add_chat("Get out!");
    add_chat("If you don't get out of here, I'll kill you!");
    add_chat("Out of my sight, before I get mad.");
    add_chat("You want to fight, I'll give you a bloody fight!");
    add_chat("What you lookin' at? Just get out!");
    
    set_cchat_time(2);            /* Set combat speaking interval  */
    add_cchat("You think you can fight eh?");
    add_cchat("Meet your Nemesis, scum!");

    set_act_time(15);
    add_act("spit at lichen");
    add_act("snarl all");
    add_act("spit all");
    add_act("emote stares at you with his black eyes.");
}

void
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
    beer->set_heap_size(30);
    beer->move(this_object());

    command("wield all");
    command("wear all");
}

public int
special_attack(object victim)
{
    if (!random(10))
        command("drink beer");
    return 0;
}

/* 
 * The rest here is to get this mobile to be a nice buddy and if he is in a
 * team and he or a members gets attacked he will join the fight.
 * This code has been taken from the troll.c example and modified.
 */

/*
 * Function name: attack_object
 * Description:   This function is called when we attack another object
 * Arguments:     ob - The object we are about to attack
 */
void
attack_object(object ob)
{
    object *arr;
    int i;

    ::attack_object(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);

    command("drink 10 beers");

    return;
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
        arr[i]->notify_ob_attacked_me(this_object(), ob);

    command("drink 10 beers");

    return;
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend   - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;

    if (random(30))
        set_alarm( 4.0, 0.0, "help_friend", attacker);
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
        command("say Guards....! Attack!!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}

