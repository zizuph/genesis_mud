/*  file:  /d/Calia/sea/creatures/xlarge_wkroug.c
 *  description: xlarge underwater kroug for caves in sea area
 *                 of Calia
 *  coder:  Tigerlily
 *  date:  2002-09-03
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
({ "emote inflates its gills.",
  "emote throws some slime at you.", 
  "emote emits a stream of black bubbles.",
}); 


void
arm_me()
{
    object this;
    string arm_type, wep_type;
    object weap, arm;

    this = this_object(); 
    seteuid(getuid(this));
    wep_type = ({SEA_WEAPONS + "obsid_halberd", 
      SEA_WEAPONS +"thonker", SEA_WEAPONS+"ori_trident"})[random(3)];

    clone_object(wep_type)->move(this);
    command("wield all");
    clone_object(SEA_ARMOURS + "helmet")->move(this);

    arm_type = ({SEA_ARMOURS + "carapace_shield",
      SEA_ARMOURS+"platemail"})[random(2)];
    arm = clone_object(arm_type);
    arm->move(this);

    command("wear all");

    MONEY_MAKE_GC(random(4)+2)->move(this);
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
    as2 = KROUG_ADJ2[2]; 

    a1 = as1[random(sizeof(as1))]; 
    a2 = as2[random(sizeof(as2))]; 

    set_short(a2 + " " + a1 + " water-kroug"); 

    set_adj(({ a2, a1 })); 

    set_long(capitalize(LANG_ADDART(a2)) + " " + a1 + " water-kroug. " + 
      "It is a blackened, scaly amphibious creature that appears " +
      "to be covered in a dripping slime. Your guess is that " +
      "it was once an ordinary kroug, but it has clearly " +
      "undergone drastic changes. It is one of the"+
      " more advanced members of its race. There are black gills on"+
      " either side of its head. It has lost the ability to speak and"+
      " can only hiss.\n"); 

    set_race_name("water-kroug");
    add_name("kroug");

    set_gender(G_NEUTER);

    lev = random(18) + 95;
    slev = lev - 50;

    set_base_stat(SS_INT, lev);
    set_base_stat(SS_WIS, lev);
    set_base_stat(SS_DIS, lev);
    set_base_stat(SS_STR, lev);
    set_base_stat(SS_DEX, lev);
    set_base_stat(SS_CON, lev);
    set_skill(SS_WEP_POLEARM, slev);
    set_skill(SS_WEP_CLUB, slev);
    set_skill(SS_WEP_AXE, slev);
    set_skill(SS_PARRY, slev);
    set_skill(SS_DEFENCE, slev);
    set_hp(query_max_hp());
    set_alignment(-30 - random(30));
    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(NPC_I_NO_LOOKS, 1); 
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_VOLUME, 30000);
    add_prop(LIVE_I_SEE_DARK, 1);


    set_act_time(3);
    add_act("emote drips slime.");
    add_act("emote emits a dark inky cloud into the water.");
    add_act("emote hisses through its black gills, ejecting"+
      " a stream of black bubbles.");
    set_hitloc_unarmed(A_BODY, 14, 45, "body"); 
    arm_me();
    set_aggressive(1); 
}

