/* Ashlar, 15 Jul 97 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

string gColour, gMaterial;
#define ARMOUR_CLASS    3

void
set_desc(string c, string m)
{
    int ac;
    if (stringp(gColour))
        remove_adj(gColour);
    if (stringp(gMaterial))
        remove_adj(gMaterial);

    set_adj(gColour = c);
    add_adj(gMaterial = m);

    if (m=="leather")
        ac = ARMOUR_CLASS + 1;
    else
        ac = ARMOUR_CLASS;

    set_short(c + " " + m + " vest");
    set_long("The vest is made of soft " + m + ", and is dyed " +
        c + ". It is a little worn around the edges.\n");

    set_ac(ac);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, A_TORSO));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac));
}

void
create_armour()
{
    string colour =
        ({ "black", "red", "green", "blue" })[random(4)];
    string material = ({ "cloth", "leather" })[random(2)];

    set_name("vest");
    set_at(A_TORSO);

    set_desc(colour,material);

    add_prop(OBJ_I_VOLUME, 1100);
    set_am(({0,0,0}));
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + gColour + "&&" + gMaterial;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_desc(a[1],a[2]);
    init_arm_recover(a[0]);
}
