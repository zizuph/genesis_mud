/* A standard armour of the guards of Lake Town */
#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"

void
create_armour()
{
    set_name("jacket");
    set_short("leather jacket");
    set_adj("leather");
    set_long(BS("This jacket has been made of sturdy leather. It is a piece "
      + "of standard equipment of the guards of the Lake Town.\n"));

    set_default_armour(8, A_TORSO, ({ 0, 1, -1 }), 0);
    add_prop(OBJ_I_WEIGHT, F_VALUE_ARMOUR(8) + random(200));
}

string query_recover() { return MASTER + ":" + query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
