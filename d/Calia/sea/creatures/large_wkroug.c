
/* 	
    A small water kroug in the Calian sea.

    Original code by Digit. 
    Modified by Maniac 8/8/96. 
*/

#pragma save_binary;

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <money.h>
#include <language.h>
#include <macros.h>
#include <const.h>
#include "defs.h"
#include "/d/Calia/sys/kroug.h"

inherit "/d/Calia/std/sea_monster";

string *battle_emotes = 
   ({ ("emote growls: Curse the Calian Warriors, what a bunch "+
        "of wimps!"), 
      ("emote screams: The Elementals will pay for what "+
       "they have done to us!"),
      "emote throws some slime at you.", 
      "emote claims: Thou limp frog's bladder!", 
      "emote snarls: Thou electrified eel's puke! ", 
      "emote blurts: Thou sorry haddock's kidney!", 
      "emote splashes around uncontrollably.",
      "emote takes a mouthful of sea water and spits it at you!", 
      "emote sings: Fish, ah-ah, it's a mackerel!", 
      "emote declares: The islanders will all die." }); 


void
arm_me()
{
    object this;
    string type;

    this = this_object(); 
    seteuid(getuid(this));
    clone_object(SEA_WEAPONS+"short_spear")->move(this);
    command("wield spear");
    clone_object(SEA_ARMOURS+"small_gauntlets")->move(this);

    type = ({ "small_greaves", "small_helmet", "small_shield" })[random(3)]; 
    clone_object(SEA_ARMOURS+type)->move(this);

    command("wear all");

    MONEY_MAKE_CC(40)->move(this_object());
}


int
special_attack(object victim)
{
    if (!random(6)) 
        command(battle_emotes[random(sizeof(battle_emotes))]); 
    return 0;
}


void
create_monster()
{
    int lev, slev;

    string *as1, *as2; 
    string a1, a2; 
     
    as1 = KROUG_ADJ1; 
    as2 = KROUG_ADJ2[0]; 

    a1 = as1[random(sizeof(as1))]; 
    a2 = as2[random(sizeof(as2))]; 

    set_short(a2 + " " + a1 + " water-kroug"); 

    set_adj(({ a2, a1 })); 

    set_long(capitalize(LANG_ADDART(a2)) + " " + a1 + " water-kroug. " + 
        "It is a blackened, scaly creature that appears " +
        "to be covered in a dripping slime. Your guess is that " +
        "it was once an ordinary kroug, but it has clearly " +
        "has undergone drastic changes (as if being an ordinary " +
        "kroug were not drastic changes enough!) Its scales are quite " +
        "thick, as if it were wearing a scalemail.\n"); 

    set_race_name("water-kroug");
    add_name("kroug");

    if (!random(2)) 
        set_gender(G_MALE); 
    else
        set_gender(G_FEMALE); 

    lev = random(11) + 70; 
    slev = lev - 6; 

    set_base_stat(SS_INT, lev);
    set_base_stat(SS_WIS, lev);
    set_base_stat(SS_DIS, lev);
    set_base_stat(SS_STR, lev);
    set_base_stat(SS_DEX, lev);
    set_base_stat(SS_CON, lev);
    set_skill(SS_WEP_POLEARM, slev);
    set_skill(SS_PARRY, slev);
    set_skill(SS_DEFENCE, slev);
    set_hp(query_max_hp());
    set_alignment(-30 - random(30));
    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(NPC_I_NO_LOOKS, 1); 
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_VOLUME, 30000);

    set_act_time(3);
    add_act("emote drips slime into the water.");
    add_act("emote scratches its scales.");
    add_act("emote spits in your face.");
    add_act("emote growls: Curse the Calian Warriors, what a bunch "+
        "of wimps!");
    add_act("emote screams: The Elementals will pay for what "+
        "they have done to us!");
    add_act("emote cackles with glee.");
    add_act("emote grins evilly, slime dripping from its face.");
    add_act("emote throws slime at you.");
    add_act("emote adjusts its armour.");
    add_act("emote taunts you to fight it.");

    set_hitloc_unarmed(A_BODY, 14, 45, "body"); 

    add_leftover(SEA_ARMOURS+"scalemail", "scales", 1, 0, 1, 1); 

    set_aggressive(1); 
}

