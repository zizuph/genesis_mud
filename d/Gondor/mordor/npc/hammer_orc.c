/*
 * /d/Gondor/mordor/npc/hammer_orc.c
 *
 * This orc does not wield one of the random weapons that will be given to
 * him in the make_the_orc function, but he will wield a special hammer with
 * a few very nice features.
 *
 * Do you think that this is an ugly construct? *shrug* It works and it allows
 * me to use my 'towerorc' without having to do a lot of changes in the orc
 * that will inflict other orcs I have coded with the 'towerorc'. As long as
 * you make sure that you don't do clone_object(hammer_orc)->move(room); but
 * clone the orc now and move him into the room later, there is nothing that
 * mortals will notice.
 *
 * /Mercade, 23 October 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/npc/towerorc";

#include "/d/Gondor/defs.h"

#define HAMMER_FILE MORDOR_DIR + "obj/wep/hammer"

void
make_the_orc(int base, int whip)
{
    object weapon;

    FIX_EUID;

    ::make_the_orc(base, whip);

    command("unwield all");
    /* He might wear a shield and needs both hand for the hammer, so.... */
    command("remove all");

    /* remove his other weapons from 'make_the_orc'. */
    while(objectp(weapon = present("weapon", TO)))
    {
        weapon->remove_object();
    }

    clone_object(HAMMER_FILE)->move(TO);

    /* wield the hammer before you (try to) wear a possible shield */
    command("wield all");
    command("wear all");
}
