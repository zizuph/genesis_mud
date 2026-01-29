/* A knife  */

inherit "/std/weapon";
inherit "/lib/keep";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_short("ivory handled knife");
    set_pshort("ivory handled knives");
    set_adj("ivory");
    add_adj("handled");
    set_long("A small blade with an ivory handle. The ivory has " +
    "turned brown and glossy with use and age, and is shaped " +
    "like a bear. The blade is thin and sharp, like a stilletto.\n");
    
    set_default_weapon(10,10,W_KNIFE,W_SLASH,W_ANYH,0);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10)+random(40)-20);
}
