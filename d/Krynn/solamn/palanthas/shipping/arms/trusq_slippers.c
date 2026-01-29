/* Mortis 03.2006
 *
 * Slippers of High Guard of merchant house Trusq in
 * Palanthas.
 *
 * Mortis 09.2014 - Improved sneak bonus from 2-4 to 7-12 to compete with
 * today's skill enhancing items.
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include "../../local.h"

int silence = 7 + random(6); // Provides +7-12 levels of sneak.

void
create_armour()
{
    set_name("slippers");
    set_adj("chromatic");
    add_adj(({"black"}));
    set_short("pair of chromatic black slippers");
    set_pshort("pairs of chromatic black slippers");
    set_long("The rigid woven finish of these black slippers reflects in "
    + "chromatic hues of the spectrum as the light changes though always "
    + "returning to its enigmatic, sparkly black.  Somewhat elastic around "
    + "the ankles, the slippers are very easy to slip into.  Inside, they "
    + "are lined with swansdown and a strangely yielding, soft rubbery "
    + "gel in the bottom that supports your feet in surprisingly relaxing "
    + "comfort.\n");

    set_ac(10);
    set_am(({-1, 0, 1}));
    set_at(A_FEET);
    set_af(TO);

    add_prop(OBJ_I_WEIGHT, 440 + random(80) - 20 * silence);
    add_prop(OBJ_I_VOLUME, 450 + random(110));
    add_prop(OBJ_I_VALUE, 400 * silence + random(175));

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC,({2 + 3 * silence, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"Woven from the hide of a Guletter, the "
    + "horned, six legged, goat-like animal of the dark elves capable of "
    + "spinning webs, its black woolish fur has been woven rigidly into "
    + "the shape of these slippers.  The strangely yielding gel support "
    + "in the bottom of the slippers is taken straight from its web sac "
    + "in gel form before it has been spun into web.  You detect a slight "
    + "enchantment on the soles dampening sound.\n", 20}));
    add_prop(OBJ_S_WIZINFO, "Woven from the hide of a Guletter, the "
    + "horned, six legged, goat-like animal of the dark elves capable of "
    + "spinning webs, its black woolish fur has been woven rigidly into "
    + "the shape of these slippers.  The strangely yielding gel support "
    + "in the bottom of the slippers is taken straight from its web sac "
    + "in gel form before it has been spun into web.  You detect a slight "
    + "enchantment on the soles dampening sound.\nGrants 7-12 levels of "
    + "sneak determined upon item creation.\n");
}

mixed
wear(object what)
{
    if (TP->query_npc())
    { return 0; }

    TP->set_skill_extra(SS_SNEAK, (TP->query_skill_extra(SS_SNEAK) + silence));
    return 0;
}

mixed
remove(object what)
{
    TP->set_skill_extra(SS_SNEAK, (TP->query_skill_extra(SS_SNEAK) - silence));
    return 0;
}
