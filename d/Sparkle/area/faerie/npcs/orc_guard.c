/*
 * Orc for the roads in Faerie
 * By Finwe, April 2005
 *
 * Cleaned up code and added equip() function
 * Finwe, October 2017
 */

#include "defs.h"
#include "orc.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/d/Sparkle/area/faerie/npcs/orc_maker.c";

#define ARMS    ({"sbracers"})
#define HELM    ({"shelm"})
#define BODY    ({"chainmail"})
#define LEGS    ({"sgreaves", "sboots"})
#define SHIELDS ({"bshield", "oshield"})
#define WEPS    ({"scimitar", "waraxe", "smace"})

#define FAERUN_ORC_DIR  "/d/Faerun/orcmaker/"

//void arm_me();

void create_orc()
{
    string mental, phys;

    seteuid(getuid());

    mental = ONE_OF_LIST(MENTAL);
    phys   = ONE_OF_LIST(PHYS);

    add_name(ORC_GUARD_NAME);
    add_name("orc");
    set_race_name("orc");
    set_adj(mental);
    set_adj(phys);
    set_short(mental + " " + phys + " orc");
    set_long("This is an orc guard. The dog-like face is black and blue " +
        "and has sharp fangs. Its hair is disheveled and bristly-looking. " +
        "The long arms almost reach the ground. The orc looks around, " +
        "ready attack anything that enters the camp.\n");

    make_silver(12+random(48));

    set_base_stat(0, 85, 10);
    set_base_stat(1, 85, 10);
    set_base_stat(2, 85, 10);
    set_base_stat(3, 85/2, 10);
    set_base_stat(4, 85/2, 10);
    set_base_stat(5, 85, 10);

//    arm_me();
    equip(({FAERUN_ORC_DIR + "wep/" + ONE_OF_LIST(WEPS),
            FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(ARMS),
            FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(HELM),
            FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(BODY),
            FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(LEGS),
            FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(SHIELDS)}));
}
/*
void arm_me()
{
    clone_object(FAERUN_ORC_DIR + "wep/" + ONE_OF_LIST(WEPS))->move(TO);
    clone_object(FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(ARMS))->move(TO);
    clone_object(FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(HELM))->move(TO);
    clone_object(FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(BODY))->move(TO);
    clone_object(FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(LEGS))->move(TO);
    clone_object(FAERUN_ORC_DIR + "arm/" + ONE_OF_LIST(SHIELDS))->move(TO);

    command("wield all");
    command("wear all");

    return;
}
*/
void
init_living()
{
    ::init_living();
    init_team_pickup();
}
