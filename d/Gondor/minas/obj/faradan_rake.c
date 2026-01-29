/*
 * /d/Gondor/minas/obj/rake.c
 *
 * A weapon for Farmer Faradan (oat quest)
 *
 * Alto, 17 May 2001
 *
 */

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

object actor;

void
create_weapon()
{
    set_name("rake");
    add_name("old rake");
    set_pname("rakes");
    add_pname("old rakes");
    set_short("old rake");
    set_pshort("old rakes");
    set_long("This rake is well-worn from many years of use in the "
        + "fields of the Lossarnach. It is best used for tilling soil, "
        + "but would no doubt make a reasonable weapon in a pinch.\n");
    set_default_weapon(26,39,W_POLEARM,W_SLASH|W_IMPALE,W_BOTH,0);
    add_prop(OBJ_I_WEIGHT,9000);
    add_prop(OBJ_I_VOLUME,1280);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(29,26)+random(200)-100);
}

void
init()
{
   ::init();
   add_action("rake_here", "rake");
}

int
rake_here(string str)
{

    actor = TP;

    if (!strlen(str))
        NF0("Rake what?\n");

    if (str != "ground")
        NF0("What do people usually rake with a rake?\n");
    switch (random(2))
    {
    case 0:
        write("You skillfully rake up a patch of ground. What a gardener "
            + "you must be!\n");
        say(QTNAME(actor) + " skillfully rakes up a patch of ground. What a "
            + "gardener "
            + actor->query_pronoun() + " must be!\n");
        break;
    case 1:
        write("You dig the old rake deeply into the ground and almost put "
            + "your back out.\n");
        say(QTNAME(actor) + " digs the old rake deeply into the ground and "
            + "almost puts "
            + actor->query_possessive() + " back out.\n");
        break;
    default:
        break;
    }
        return 1;

}

