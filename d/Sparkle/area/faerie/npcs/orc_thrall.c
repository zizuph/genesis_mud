/*
 * Orc for the roads in Faerie
 * By Finwe, April 2005
 */

#include "defs.h"
#include "orc.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/d/Sparkle/area/faerie/npcs/orc_maker.c";

#define WEAK_ARMS   ({"ibracers"})
#define WEAK_HELM   ({"ihelm"})
#define WEAK_BODY   ({"brig"})
#define WEAK_LEGS   ({"igreaves", "lboots"})
#define SHIELDS     ({"bshield", "oshield"})


#define WEAK_WEPS   ({"scrimasax", "broadsword"})

#define FAERUN_ORC_DIR  "/d/Faerun/orcmaker/"

void arm_me();

void create_orc()
{
    string mental, phys;

    seteuid(getuid());

    mental = ONE_OF_LIST(MENTAL);
    phys   = ONE_OF_LIST(PHYS);

    add_name(ORC_THRALL_NAME);
    set_race_name("orc");
    set_adj(mental);
    set_adj(phys);
    set_short(mental + " " + phys + " orc");
    set_long("This is an orc thrall. It is one of the lowest of the race " +
        "and an orc servant. Its hair is disheveled and bristly looking. " +
        "The dog-like face is black and blue and has sharp fangs. The long " +
        "arms almost reach the ground, and it looks around nervously.\n");

    make_copper(12+random(24));

    set_base_stat(0, 35, 10);
    set_base_stat(1, 35, 10);
    set_base_stat(2, 35, 10);
    set_base_stat(3, 25, 10);
    set_base_stat(4, 25, 10);
    set_base_stat(5, 35, 10);

//    arm_me();
    equip(({FAERUN_ORC_DIR + "wep/" + ONE_OF_LIST(WEAK_WEPS),
            FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(WEAK_ARMS),
            FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(WEAK_HELM),
            FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(WEAK_BODY),
            FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(WEAK_LEGS),
            FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(SHIELDS)}));

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

void
init_living()
{
    ::init_living();
    init_team_pickup();
}
