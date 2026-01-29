/*
 * /d/Gondor/mordor/npc/scared_orc.c
 *
 * This orc is modified from the orc at Cirith Ungol. This orc is the orc
 * that will enter stairs0 and run from you after a moment.. He will not
 * attack the first time and therefor I needed to do a little patching :-)
 *
 * /Mercade 27 September 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/npc/towerorc";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_monster()
{
    if (!IS_CLONE)
	return;

    set_pname("orcs");
    set_race_name("orc");
    set_adj(looks);
    set_short(looks + " orc");
    set_pshort(looks + " orcs");

    set_long("@@long_description");

    add_prop(CONT_I_HEIGHT, 170 + random(20));
    add_prop(CONT_I_WEIGHT, 75000 + random(10000));
    add_prop(CONT_I_VOLUME, 70000 + random(20000));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);

    set_cchat_time(5 + random(5));
    add_cchat("Finish it!");
    add_cchat("No prisoners, no witnesses!");
    add_cchat("Ash nazg gimba, burz goth thraka!");
    add_cchat("Rum marzgitul! Auga bukratul!");
    add_cchat("Kill this bastard!");
    add_cchat("Attack this intruder!");
    add_cchat("Die! You miserable rat!");
    add_cchat("Lets feed him to Shelob.");
    add_cchat("It this that elf warrior we were warned for?");

    set_cact_time(5 + random(5));
    add_cact("scream");
    add_cact("grin");
    add_cact("@@do_tackle");
}

void
finish_the_orc()
{
    set_aggressive(1);

    set_chat_time(10 + random(10));
    add_chat("Let's hurry!");
    add_chat("When are we gonna eat?");
    add_chat("Let's find some humans to molest!");
    add_chat("I don't like running in the sunlight!");
    add_chat("Attack on sight. You can ask questions later.");
    add_chat("Why are we always sent out on Patrol?");
    add_chat("News from high up: prisoners must be taken to Lugburz.");
    add_chat("Be wary! There is a large elf warrior on the run.");
    add_chat("Uruk drepa tuluk! Egur lug en vesall hai krimpatul!");
    add_chat("Onreinn hundur drepa!");

    set_act_time(10 + random(10));
    add_act("burp");
    add_act("hiss");
    add_act("grin");
    add_act("spit");
}
