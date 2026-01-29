/*
 *  Ghast in the barrow downs
 *  The randomize func's are originally Rogon's
 *  Cloned by ~Shire/common/downs/stone4*.c
 *
 *  Modified a little by Odin, 9. March 1994
 *
 *  Renamed to dark wights and updated for the new barrows 
 *  Finwe, December 2001  
 */

inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/common/make_money.h"
#include <stdproperties.h>
//#include "/d/Shire/common/include/abbrevs.h"
//#include "/d/Shire/common/lib/evilkill.h"

#define RADJ ({ "black eyed","horrible looking", "ghastly","smelly", \
               "rigid","handsome","slimy","red eyed","grinning"})

create_monster()
{

    seteuid(getuid());
    create_ghast(random(10));
}
int myrand(int val)
{
    return val-val/4+random(val/2)+1;
}

create_ghast(int r)
{
    set_short(RADJ[r] + " dark barrow wight");
    set_adj(RADJ[r]);
    set_name("wight");
    add_name ("dark wight");
    add_name ("dark barrow wight");
    add_name ("barrow wight");
    add_name (RADJ[r] + " dark wight");
    add_name (RADJ[r] + " barrow wight");
    add_name (RADJ[r] + " wight");
    add_name (RADJ[r] + " dark barrow wight");

    set_race_name("wight");
    if (!IS_CLONE)
      return;

   
    set_long("This is a "+short()+". It in habits the deeper regions " +
        "of the barrow, luring travellers to their deaths and " +
        "taking over their bodies. It looks like it was once a " +
        "fair person before death but now is corrupted and " +
        "searching for blood.\n");

    add_prop(CONT_I_WEIGHT,70000);   /* 70 kg  */
    add_prop(CONT_I_HEIGHT,180);     /* 180 cm */
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);     /*Does NOT look plesant*/
    add_prop(LIVE_I_UNDEAD, 38);      /*Is an undead*/
    add_prop(LIVE_I_NO_CORPSE, 1);   /*Leaves no corpse*/
    add_prop("_ranger_i_not_blind",1);

            /* STR DEX CON INT WIS DIS */
    set_stats(({ 100, 100, 100, 71, 34, 89}));
    set_alignment(-200 - random (100));
    set_skill(SS_UNARM_COMBAT, 90 + random(8));
    set_skill(SS_DEFENCE, 80 + random(12));

    set_aggressive(99);
    set_attack_chance(99);

    set_hp(900); /* Heal fully */

    set_act_time(15+random(30));
    add_act("emote hisses: Ghaaaaaasssst");
    add_act("emote hisses something unintelligible at you.");
    add_act("emote hisses: I smell fresh blood...");
    add_act("emote hisses: Sooo good to see you...");
    add_act("emote hisses: Have you come to claim your reward?");
    add_act("emote looks you up and down, smililing evilly.");
    add_act("emote smiles evilly at you.");
    add_act("emote hisses at you.");
    add_act("emote stretches forth a skeletal hand towards you.");
    

    set_cact_time(15+random(30));
    add_cact("emote howls devilishly at you.");
    add_cact("emote hisses: I shall feast on your earthly remains");
    add_cact("emote hisses: Soon I shall chew your bones!!");
    add_cact("emote reaches out and chills to the bone you with a " +
        "skeletal hand.");
   
   /* Global sequence */
    set_act_time(5);
    seq_new("do_things");
    MAKE_MONEY;
    make_gold(4+random(5));
}


return_to_normal()
{
   set_act_time(5);
}
