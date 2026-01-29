/* An Vicious Ogre Guard (humanoid) - Recoded 18/07/95, Tulix III */
/* Cloned by cave /d/Emerald/cave/levelc/cave24c.c */

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"

void
create_monster()
{
    set_name("graspuch");
    set_race_name("ogre");
    set_short("vicious ogre guard");
    set_adj("vicious");
    add_name("guard");
    set_long("This Ogre is a big, vicious piece of work.\n"
        +"He looks rather more of a challenge that the average Ogre, "
        +"and is not the kind of thing you want to run into without " 
        +"a decent suit of armour. Best not to try and annoy him "
        +"too much, for your own safety. His job is to protect the "
        +"Ogre lord - if he needs protection, that is....\n");
    
    add_prop(CONT_I_WEIGHT,75000);
    add_prop(CONT_I_HEIGHT,220);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_QUICKNESS, 120);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    
    set_gender(0);  /* male=0, female=1, other=2 */

    set_default_answer("The ogre glares at you menacingly.\n");
    /* stats -   STR  DEX  CON  INT  WIS  DIS  */
    set_stats(({ 140, 135, 140, 100, 100, 140}));
    set_hp(20400);    
    set_alignment(-200);

    /* Set unarmed attacks and armour classes. */
    set_all_hitloc_unarmed(35);
    set_all_attack_unarmed(30,38);

    set_attack_chance(50);

    /* Set the all important skills. */
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_WEP_AXE, 90);
    
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_DEFENCE, 90);

    set_skill(SS_AWARENESS, 90);

    set_chat_time(10);                  /* Set speaking interval */
    add_chat("Go on, get out!");
    add_chat("Maybe I'll make your death slow and painful.");
    add_chat("Go on, you just try it!");
    add_chat("You want to fight, I'll give you a bloody fight!");
    add_chat("You weaklings make me sick!");
    add_chat("Okay, come on you bastards!!"); /* Many ogres say this. */
    
    set_cchat_time(2);            /* Set combat speaking interval  */
    add_cchat("Die, scum!");
    add_cchat("Pathetic little fool!");
    
    set_act_time(20);   
    add_act("spit at lichen");
    add_act("snarl all");
    add_act("spit");
    /*
    add_act(emote grinds his teeth.);
    */
    add_act("grin");
    add_act("growl");
    add_act("scream");
    
}

void
arm_me()
{
    object armour, weapon;

    armour=clone_object(CAVE_DIR + "arm/brig_leggings.c");
    armour->move(this_object());

    armour=clone_object(CAVE_DIR + "arm/augment_mail.c");
    armour->move(this_object());

    armour=clone_object(CAVE_DIR + "arm/iron_helm.c");
    armour->move(this_object());

    weapon=clone_object(CAVE_DIR + "wep/ogre_halberd.c");
    weapon->move(this_object());

    command("wield all");
    command("wear all");
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
        command("say You will die for this!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}

