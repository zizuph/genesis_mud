/* Ashlar, 17 May 97 - Breastplate worn by dragonarmy officers */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

string color = "blue";

#include "insignia.h"

#define ARMOUR_CLASS    40

void
create_armour()
{
    set_name("breastplate");
    add_name("plate");
    set_adj("steel");
    add_adj("breast");
    add_adj(color);
    set_short(color + " steel breastplate");
    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_long("The breastplate is made of fine steel, and painted " +
        "@@query_color@@. A small patch on the left side bears the " +
        "insignia of the @@query_Color@@ Dragonarmy.\n");
    add_item(({"patch","small patch"}),"The patch bears the insignia of " +
        "the @@query_Color@@ Dragonarmy.\n");
    add_item("insignia","@@show_insignia");
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_TORSO));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));
    add_prop(OBJ_I_COLORABLE, 1);
}

void
set_color(string new_color)
{
	remove_adj(color);
    color = new_color;
    add_adj(color);
    set_short(color + " steel breastplate");
}

string
query_color()
{
	return color;
}

string
query_Color()
{
	return C(color);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + color;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_color(a[1]);
    init_arm_recover(a[0]);
}

