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
#define WEAPON  ({"waraxe", "bastardsword"})
#define SHIELD  ({"w_heater"})
#define BOD_ARM ({"hauberk", "b_hauberk"})
#define BOOTS   ({"boots"})
#define HELMET  ({"coif", "spangenhelm", "spangenhelm"})

#define TYPE    ({"mature", "middle-aged", "young", "scarred", "lean", "massive", "muscular", "slender", "stocky", "stout", "heavy", "dangerous", "determined", "grim", "quiet", "stoic", "bald", "balding"})
#define PHYS    ({"tidy-looking", "long-armed", "strong-armed", "black-bearded", "mustachioed", "broad-chested", "broad-shouldered", "black-eyed", "blue-eyed", "brown-eyed", "gray-eyed", "green-eyed", "one-eyed", "black-haired", "blond-haired", "brown-haired", "gray-haired", "short-haired"})

//#define NAME    ({"Lorid", "Abbe", "Olland", "Feyan", "Telf", "Kardor", "Crimb", "Radaer", "Olle", "Galward", "

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

    set_short(phys + " " + type + " guard");
    set_pshort(phys + " " + type + " guards");
    set_long("This " + race + " is one of the guards whose task is to " + 
		"prevent people from approaching Neverwinter. He is strong and " + 
		"extremely confident in his abilities.\n");

	// stat avg = ~120, combat skill avg = ~70
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

	arm = clone_object(ARM_DIR + ONE_OF_LIST(BOD_ARM));
    arm -> move(TO);
    arm = clone_object(ARM_DIR + "spangenhelm");
    arm -> move(TO);
    arm = clone_object(ARM_DIR + "w_heater");
    arm -> move(TO);
    arm = clone_object(ARM_DIR + "gloves");
    arm -> move(TO);
    arm = clone_object(ARM_DIR + "boots");
    arm -> move(TO);
    
    command("wear armours");
    command("wield weapons");
}


void
init_living()
{
    ::init_living();
}