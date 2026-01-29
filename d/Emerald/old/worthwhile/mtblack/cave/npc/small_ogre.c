/* A Small Ogre (humanoid) - Recoded 18/07/95, Tulix III */
/* Cloned by various caves in /d/Emerald/cave/levelc/cave8c.c */

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"

void
create_monster()
{
    set_name("giamari");
    set_race_name("ogre");
    set_short("small ogre");
    set_adj("small");
    set_long("This is not the biggest Ogre that you have ever "
        + "seen, but he still looks as if he could be quite nasty.\n");
    
    set_gender(0);  /* male=0, female=1, other=2 */

    set_default_answer("The small ogre gestures at you, showing you where " +
        "he's likely to shove the weapon he is wielding...\n");
    /* stats -   STR  DEX  CON  INT  WIS  DIS  */
    set_stats(({  50,  50,  50,  50,  50,  50}));
    set_hp(20400);
    set_alignment(-100);

    /* Set unarmed attacks and armour classes. */
    set_all_hitloc_unarmed(20);
    set_all_attack_unarmed(40,20);

    /* Set the all important skills. */
    set_skill(SS_WEP_CLUB, 60);
    set_skill(SS_WEP_POLEARM, 70);
    set_skill(SS_WEP_AXE, 80);
    
    set_skill(SS_2H_COMBAT, 60);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 50);

    set_skill(SS_AWARENESS, 80);

    set_chat_time(10);              /* Set speaking interval         */
    add_chat("Get lost!");
    add_chat("If you don't get out of here, I'll kill you!");
    add_chat("Go on, you just try it!");
    add_chat("You want to fight, I'll give you a bloody fight!");
    add_chat("What you lookin' at? Just get out!");
    
    set_cchat_time(2);            /* Set combat speaking interval  */
    add_cchat("Die, scum!"); 

    set_act_time(20);              /* Set action interval           */
    add_act("snarl all");
    add_act("spit at lichen");
    add_act("spit");
    add_act("swear");
    add_act("grin");
}

void
arm_me()
{
    object armour, weapon;
    int a,w;

    a = random(2);
    w = random(2);

        armour=clone_object(CAVE_DIR + "arm/quilt_leggings.c");
        armour->move(this_object());

        armour=clone_object(CAVE_DIR + "arm/studded_mail.c");
        armour->move(this_object());

    if (a==1)
    {
        armour=clone_object(CAVE_DIR + "arm/studded_helm.c");
        armour->move(this_object());
    }
    else
    {
        armour=clone_object(CAVE_DIR + "arm/iron_buckler.c");
        armour->move(this_object());
    }

    if (w==1)
    {
        weapon=clone_object(CAVE_DIR + "wep/goblin_axe.c");
        weapon->move(this_object());
    }
    else
    {
        weapon=clone_object(CAVE_DIR + "wep/goblin_mace.c");
        weapon->move(this_object());
    }

    command("wield all");
    command("wear all");
}
