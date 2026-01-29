/*
 * Orc for the roads in Faerie
 * By Finwe, April 2005
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/d/Sparkle/area/faerie/npcs/orc_maker.c";

#define MENTAL  ({"angry", "barbaric", "beastly", "bloodthirsty", "brutal", \
    "cold-blooded", "cranky", "cruel", "dangerous", "demonic", "deranged", \
    "evil", "ferel", "ferocious", "fierce", "foul", "grim", "grouchy", \
    "insane", "mad", "malevolent", "mean", "murderous", "nasty", "rabid", \
    "raging", "ravening", "savage", "sinister", "terrible", "testy", \
    "wicked", "wild"})
#define PHYS    ({"big", "black-haired", "bloody", "broad", "dark-eyed", \
    "dark-skinned", "dirty", "fanged", "grey-skinned", "hairy", "large", \
    "massive", "orange-eyed", "powerful", "red-eyed", "reeking", "short", \
    "smelly", "squat", "squinty-eyed", "strong", "sturdy", "tall", \
    "towering", "ugly", "yellow-eyed", "yellow-tusked"})

#define WEAK_ARMS   ({"ibracers"})
#define WEAK_HELM   ({"ihelm"})
#define WEAK_BODY   ({"brig"})
#define WEAK_LEGS   ({"igreaves", "lboots"})
#define SHIELDS     ({"bshield", "oshield"})


#define WEAK_WEPS   ({"scrimasax", "broadsword", "haxe", "baxe", "sclub"})

#define FAERUN_ORC_DIR  "/d/Faerun/orcmaker/"

void create_orc()
{
    string mental, phys;

    seteuid(getuid());

    mental = ONE_OF_LIST(MENTAL);
    phys   = ONE_OF_LIST(PHYS);

    set_name("orc");
    add_name(FAERIE + ORC + "_");
    set_race_name("orc");
    set_adj(mental);
    set_adj(phys);
    set_short(mental + " " + phys + " orc");
    set_long("This is one of the soldier orcs. It has long manes of " +
        "bristly hair on its heads shoulders, and back. The orc has a " +
        "dog-like face with sharp fangs. Its arms are long and almost " +
        "reach the ground.\n");

    set_alarm(1.0,0.0,"arm_me");
    make_silver(12+random(24));

    set_base_stat(0, 55, 10);
    set_base_stat(1, 55, 10);
    set_base_stat(2, 55, 10);
    set_base_stat(3, 55/2, 10);
    set_base_stat(4, 55/2, 10);
    set_base_stat(5, 55, 10);
}

void
arm_me()
{

    clone_object(FAERUN_ORC_DIR + "wep/" + ONE_OF_LIST(WEAK_WEPS))->move(TO);
    clone_object(FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(WEAK_ARMS))->move(TO);
    clone_object(FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(WEAK_HELM))->move(TO);
    clone_object(FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(WEAK_BODY))->move(TO);
    clone_object(FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(WEAK_LEGS))->move(TO);
    clone_object(FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(SHIELDS))->move(TO);

    command("wield all");
    command("wear all");

    return;
}
