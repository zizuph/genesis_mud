/* Ashlar, 2 Aug 97 - Mail shirt worn by lower ranking dragonarmy officers */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

string color = "blue";

#include "insignia.h"

#define ARMOUR_CLASS    34

void
create_armour()
{
    set_name("shirt");
    add_name("mail");
    set_adj("mail");
    add_adj(color);
    set_short(color + " mail shirt");
    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_long("The shirt is made of chainmail with strips of metal woven " +
        "through the links. The whole shirt has been painted " +
        "@@query_color@@. A patch on the left side of the shirt bears " +
        "the insignia of the @@query_Color@@ Dragonarmy.\n");
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
    set_short(color + " mail shirt");
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

