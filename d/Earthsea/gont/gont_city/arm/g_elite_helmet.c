#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 27

public void
create_armour()
{
  set_name("helmet");
  set_pname("helmets");
  set_adj("shiny");
  set_adj("steel");
  set_short("shiny steel helmet");
  set_pshort("shiny steel helmets");
  set_long("This helmet is standard issue for the elite Gont guards." +
           " On the top of the helmet, it is decorated by" +
           " a plume of fluffy white feathers. It is well" +
           " constructed and offer good protection for" +
           " the wearer's head.\n");
    set_ac(ARMOUR_CLASS);
    set_at(A_HEAD);
    set_am( ({1,1,1}) );
    add_prop(OBJ_I_WEIGHT, 2000 + (random(50) -  25));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(25) - 10);
}

public string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
}
