/* An Large Ogre (humanoid) - Recoded 18/07/95, Tulix III */
/* Cloned by various caves in /d/Emerald/cave/levelc/ */

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"

void
create_monster()
{
    set_name("jufrinel");
    set_race_name("ogre");
    set_short("large ogre");
    set_adj("large");
    set_long("This Ogre is rather large, and is looking hungrily "
        +"in your direction, which is a little disturbing. "
        +"He is fairly bulky, and probably quite tough.\n");
    
    add_prop(CONT_I_WEIGHT,75000);
    add_prop(CONT_I_HEIGHT, 220);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    
    set_gender(0);  /* male=0, female=1, other=2 */

    set_default_answer("The ogre ignores you.\n");
    /* stats -   STR  DEX  CON  INT  WIS  DIS  */
    set_stats(({  95,  90, 110,  80,  80,  50})); 
    set_hp(20400);    
    set_alignment(-150);

    /* Set unarmed attacks and armour classes. */
    set_all_hitloc_unarmed(35);
    set_all_attack_unarmed(30,36);

    set_attack_chance(25);

    /* Set the all important skills. */
    set_skill(SS_WEP_CLUB, 80);
    set_skill(SS_WEP_POLEARM, 80);
    set_skill(SS_WEP_AXE, 80);
    
    set_skill(SS_2H_COMBAT, 80);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_DEFENCE, 80);

    set_skill(SS_AWARENESS, 80);

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
    add_act("emote eyes you with distrust.");
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

    weapon=clone_object(CAVE_DIR + "wep/goblin_axe.c");
    weapon->move(this_object());
    
    weapon=clone_object(CAVE_DIR + "wep/goblin_axe.c");
    weapon->move(this_object());
    
    command("wield all");
    command("wear all");
}

