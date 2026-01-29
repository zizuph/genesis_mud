/*
 * Dunlending soldier
 * 
 * 
 * By Hordak@Genesis
 */
#pragma strict_types

#include "/d/Gondor/dunland/wild/dunlendings.h"
#include "/d/Gondor/defs.h"

inherit DUN_WILD_NPC + "std_dunl_npc";

inherit "/d/Genesis/lib/intro";

#include <const.h> 
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#define ADJ  ({"short-haired", "pot-bellied", "long-haired", \
      "muscular", "angry", "hairy", "sweaty", "calm", "furious", \
      "hateful", "big-armed", "broad-shouldered", "skinny", \
      "long-bearded", "big", "small", "nasty", "upset", "smelly", \
      "tall", "short", "large", "big-mouthed", "slouchy", "ugly", \
      "dirty", "scarred"})

string *weapons = ({ DUN_WILD_WEAPON + "axe", DUN_WILD_WEAPON
+ "club", DUN_WILD_WEAPON + "spear", DUN_WILD_WEAPON +
  "mace" }); 

string *helmets = ({ DUN_WILD_ARMOUR + "cap", DUN_WILD_ARMOUR
+ "hood" });

string *bodyarmour = ({ DUN_WILD_ARMOUR + "harness", DUN_WILD_ARMOUR
+ "vest", DUN_WILD_ARMOUR + "brigandine" });

string *legs = ({ DUN_WILD_ARMOUR + "boots", DUN_WILD_ARMOUR
+ "pants" });

string *arms = ({ DUN_WILD_ARMOUR + "bracers", DUN_WILD_ARMOUR
+ "gloves" });

void
create_dunl_npc()
{
    string adj;

    seteuid(getuid());

    adj = ONE_OF_LIST(ADJ);

    set_adj(adj);
    set_adj("dark-haired");
    set_short(adj + " dark-haired dunlending");
    set_race_name("human");
    set_name("dunlending");

    set_long("This is one of the dunlendings, a people with a rough " +
      "history with the rohirrim. He is swarthy and have dark hair. " +
      "You get the impression that this people is used to harsh " +
      "conditions.\n");
    add_name("man");

    set_gender(G_MALE);
    /*          STR DEX CON INT WIS DIS */
    set_stats(({ 160, 180, 190, 111, 110, 160 }), 20);

    set_alignment(-400);

    set_skill(SS_WEP_AXE, 55);
    set_skill(SS_WEP_POLEARM, 55);
    set_skill(SS_WEP_CLUB, 55);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_BLIND_COMBAT, 50);

    set_chat_time(12);
    add_chat("Wonder how long we have to wait.");
    add_chat("Galuk even defeated Elfhelm himself!");
    add_chat("We will re-take what is ours!");
    add_chat("This is our land, we were here first!");
    add_chat("Wulf did it, so can Galuk.");
    add_chat("The White Hand will help us.");

    set_cchat_time(8);
    add_cchat("Finally some battle!");
    add_cchat("Fool! Its to late to save Rohan!");
    add_cchat("No!");

    equip(({ 
	one_of_list(weapons),
	one_of_list(helmets),
        one_of_list(bodyarmour),
        one_of_list(legs),
        one_of_list(arms)
      }));

}


