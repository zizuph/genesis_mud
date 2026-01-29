/* Ashlar, 11 May 97 - Cape worn by Dragonarmy officers
   based on brobe.c by <unknown> */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

string color = "blue";

#include "insignia.h"

void
create_armour()
{
    set_name("cape");
    set_adj("fancy");
    add_adj(color);
    set_short("fancy " + color + " cape");
    set_ac(4);
    set_at(A_ROBE);
    set_af(TO);
    set_long("It is a fancy cape usually worn by officers of the " +
        "Dragonarmies. The cape is fastened around the neck with a " +
        "silver clasp bearing the insignia of the @@query_Color@@ " +
        "Dragonarmy. The cape itself is @@query_fancy_color@@, and " +
        "has dragons embroidered in fine silver thread along the edges.\n");
    add_item(({"clasp","silver clasp"}),"The clasp bears the insignia of " +
        "the @@query_Color@@ Dragonarmy. It is of exquisite craftmanship.\n");
    add_item("insignia","@@show_insignia");
    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(4, A_ROBE));
    /* The cape is finely made, and contains pure silver in the clasp */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(4) + 60 + random(50));
    add_prop(OBJ_I_COLORABLE, 1);
}

void
set_color(string new_color)
{
	remove_adj(color);
    color = new_color;
    add_adj(color);
    set_short("fancy " + color + " cape");
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
query_fancy_color()
{
	switch(color)
    {
    	case "black":
            return "midnight black";
        case "blue":
            return "sky blue";
        case "green":
            return "emerald green";
        case "red":
            return "of a fiery red colour";
        case "white":
            return "snow-white";
        default:
            return color;
    }
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

int
wear(object obj)
{
	object w;
    w = E(obj);
    if (w->query_prop(LIVE_I_IS) && !w->query_npc())
    {
    	w->catch_msg("You wear the " + short() + ", fastening the clasp " +
            "around your neck.\n");
        tell_room(E(w),QCTNAME(w) + " wears the " + short() + ".\n",w);
        return 1;
    }
    return 0;
}

int
remove(object obj)
{
	return 0;
}

