/* Ashlar, 15 Jul 97 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

string gColour;
#define ARMOUR_CLASS  3

void
set_desc(string c)
{
    if (stringp(gColour))
        remove_adj(gColour);
    add_adj(gColour = c);
    set_short("pair of " + c + " breeches");
    set_pshort("pairs of " + c + " breeches");

    set_long("The breeches are made of cloth, dyed a " +
        (c == "brown" ? "deep" : "bright") + " " + c +
        "colour. They reach just below your knees.\n");
}

void
create_armour()
{
    string colour =
        ({ "green", "blue", "red", "brown", "yellow" })[random(5)];

    set_name("breeches");
    add_name("pair");
    set_pname("breeches");
    add_pname("pairs");
    add_pname("armours");
    set_adj("pair");
    add_adj("of");
    set_desc(colour);
    set_ac(ARMOUR_CLASS);
    set_at(A_LEGS);

    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_LEGS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
    set_am(({0,0,0}));
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + gColour;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_desc(a[1]);
    init_arm_recover(a[0]);
}
