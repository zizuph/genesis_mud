/* Ashlar, 15 Jul 97 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

string gColour, gSleeve;

#define ARMOUR_CLASS    3

void
set_desc(string c, string s)
{
    if (stringp(gColour))
        remove_adj(gColour);
    if (stringp(gSleeve))
        remove_adj(gSleeve+"-sleeved");

    set_adj(gColour = c);
    add_adj((gSleeve = s) + "-sleeved");

    set_short(c + " " + s + "-sleeved shirt");
 
    set_long("It is a " + c + " shirt of soft cloth with " + s +
        " sleeves. It is of good make, and surprisingly clean.\n");
}

void
create_armour()
{
    string colour =
        ({ "white", "grey", "brown", "green", "yellow", "blue" })[random(6)];
    string sleeve = ({ "long", "short", "wide" })[random(3)];

    set_name("shirt");
    set_desc(colour,sleeve);
    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO | A_ARMS);
    add_prop(OBJ_I_VOLUME, 850);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS,
        A_TORSO | A_ARMS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
    set_am(({0,0,0}));
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + gColour + "&&" + gSleeve;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_desc(a[1],a[2]);
    init_arm_recover(a[0]);
}
