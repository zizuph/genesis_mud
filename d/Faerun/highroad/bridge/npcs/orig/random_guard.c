/*
 * Randomly generated guard, bridge near Neverwinter 
 * by Kehr, Oct-Nov 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include "/d/Faerun/highroad/bridge/npcs/base_smart_npc.h"

inherit "/d/Faerun/highroad/bridge/npcs/base_smart_npc";

// Humans happen more often !
#define RACE	({"human", "human", "dwarf", "elf"})

//#define WEAPON  ({"longsword", "battleaxe", "warhammer"})
#define WEAPON  ({"waraxe"})
#define SHIELD  ({"steel_shield"})
#define BOD_ARM ({"breastplate", "chainmail"})
//#define GREAVES ({"greaves", "greaves_i", "greaves_sp"})
//#define HELMET  ({""})

#define TYPE    ({"mature", "middle-aged", "young", "scarred", "lean", "massive", "muscular", "slender", "stocky", "stout", "heavy", "dangerous", "determined", "grim", "quiet", "stoic", "bald", "balding"})

#define PHYS    ({"tidy-looking", "long-armed", "strong-armed", "black-bearded", "mustachioed", "broad-chested", "broad-shouldered", "black-eyed", "blue-eyed", "brown-eyed", "gray-eyed", "green-eyed", "one-eyed", "black-haired", "blond-haired", "brown-haired", "gray-haired", "short-haired"})


void create_faerun_npc()
{
    string type, phys, race;

	::create_faerun_npc();
	init_living();

    type = ONE_OF_LIST(TYPE);
    phys = ONE_OF_LIST(PHYS);
    race = ONE_OF_LIST(RACE);

    add_adj(type);
    add_adj(phys);

    set_race_name(race);
    add_name("guard");
    set_name("__bridge_guard");

    set_short(phys + " " + type + " guard");
    set_pshort(phys + " " + type + " guards");
    set_long("This " + race + " is one of the guards whose task is to " + 
	"prevent people from approaching Neverwinter. He is strong and " + 
	"extremely confident in his abilities.\n");

    set_act_time(50+random(100));
    add_act("listen attent");
    add_act("emote studies his weapons carefully");
    add_act("emote looks worriedly towards Neverwinter");
    add_act("say The plague killed my brother!");
    add_act("say Noone is allowed to go to Neverwinter, at least until priests contain the plague.");
    add_act("say I have seen infected people... Horrible sight.");
    add_act("say I wish I had a swift death. Those who have fallen to the plague suffer horribly."); 

	set_level(120, 70);

	set_alarm(2.0, 0.0, "arm_me");
}

void arm_me ()
{
	object arm, wep;

    wep = clone_object(WEP_DIR + ONE_OF_LIST(WEAPON));
    wep -> move(TO);
    wep = clone_object(WEP_DIR + ONE_OF_LIST(WEAPON));
    wep -> move(TO);

    //arm = clone_object("/d/Krynn/common/armours/kite-shield.c");
    //arm -> move(TO);
    
    command("wear armours");
    command("wield weapons");

    fightmode = FIGHT_SHIELD_WEP;
}


void
init_living()
{
    ::init_living();
    init_team_pickup();
}