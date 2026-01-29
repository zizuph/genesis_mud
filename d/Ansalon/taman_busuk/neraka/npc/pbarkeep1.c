/* Ashlar, 10 Jul 97 */

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
    set_adj("short");
    add_adj("stocky");
    set_long("The short stocky human is the barkeeper of the Red Dragon " +
        "Tavern. He wears a full, black beard which he scratches " +
        "constantly.\n");
    set_stats(({95,70,75,50,55,75}));
    set_act_time(5);
    add_act("emote scratches his beard.");
    add_act("emote scratches his beard.");
    add_act("emote pulls slowly on his beard.");
    add_act("emote scratches his head.");
    add_act("say By the Gods, the fleas are biting today.");
    set_cact_time(2);
    add_cact("shout Guards, guards!");
    add_cact("say You'll regret this!");

    add_prop(CONT_I_HEIGHT, 160);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(LIVE_I_NEVERKNOWN, 1);

}

void
arm_me()
{
    object arm, wep;
    seteuid(getuid(TO));
    arm = clone_object(NARM+"shirt");
    arm->move(TO);
    arm = clone_object(NARM+"breeches");
    arm->move(TO);
    arm = clone_object(NARM+"boots1");
    arm->move(TO);
    /*
    wep = clone_object(NWEP+"knobkerrie");
    wep->move(TO);
    */
    command("wear all");
    command("wield all");
    
}


