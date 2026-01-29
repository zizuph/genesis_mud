/*
 * Created By : Ibun 070524
 */
#pragma strict_types
inherit "/std/armour.c";
inherit "/lib/keep";
#include "/d/Avenir/common/common.h"
#include <stdproperties.h>     /* Where the properties are defined. */
#include <wa_types.h>          /* Where weapon and armour defs are. */
#include <ss_types.h>          /* Where the skill defines are.      */
#include <tasks.h>             /* For using resolve_task in wear()  */
#include <formulas.h>          /* Where the formulas for value, */

void
create_armour()
{
    set_name("gloves");
    add_adj("black");
    set_adj("leather");
    set_short("pair of black leather gloves");
    set_long("Theese are a pair of gloves made from "+
      "skin. The leather is shimmering in black, " +
      "almost distracting you.\n");
    set_at(A_HANDS);
    set_ac(2);
    set_af(TO);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 300);
}
