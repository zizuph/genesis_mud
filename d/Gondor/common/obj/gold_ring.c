/*  Armour coded by Arren, April 94 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("ring");
    set_adj("gold");
    add_adj(({ "precious", "ruby", "smooth", "flaming" }));
    set_short("gold ring");
    set_long(BSN(
    "A smooth gold ring set with a flaming ruby. The ruby sparkles as "+
    "if it has a light of its own. "));

    set_af(TO);
    set_default_armour(1, A_ANY_FINGER, ({0,0,0}), 0);

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 300 + random(50));
}

int
wear(object ob)
{
    write("You wear the " + query_short() + " on your finger.\n");
    say(QCTNAME(TP) + " wears the " + query_short() + ".\n");
    return 1;
}
