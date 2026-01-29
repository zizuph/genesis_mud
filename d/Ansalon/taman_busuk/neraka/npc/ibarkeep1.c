/* Ashlar, 5 Jul 97 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

void arm_me();

void
create_krynn_monster()
{
    set_name("barkeeper");
    add_name("barkeep");
    set_race_name("human");
    set_adj("tall");
    add_adj("black-haired");
    //set_short("tall black-haired male human");
    set_long("The tall black-haired human is the barkeeper of the Swan and " +
        "Hedgehog Inn. He is a gaunt man, clean shaven, with a " +
        "prominent nose between two piercing blue eyes.\n");
    set_stats(({80,65,75,50,55,70}));
    set_act_time(12);
    add_act("emote cleans the bar with a rag.");
    add_act("emote cleans some glasses.");
    add_act("emote taps his nose in a surreptious manner.");
    set_cact_time(2);
    add_cact("shout Guards, guards!");
    add_cact("say Curse you!");

    add_prop(CONT_I_HEIGHT, 185);
    add_prop(CONT_I_WEIGHT, 55000);
    add_prop(LIVE_I_NEVERKNOWN, 1);

}

void
arm_me()
{
    object arm, wep;
    seteuid(getuid(TO));
    
    arm = clone_object(NARM+"apron");
    arm->move(TO);
    arm = clone_object(NARM+"breeches");
    arm->move(TO);
    /*
    wep = clone_object(NWEP+"knobkerrie");
    wep->move(TO);
    */
    command("wear all");
    command("wield all");
    
}


