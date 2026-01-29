  /* 
   * a rabbit pelt
   * Olorin 		Feb 1993
   */

inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() 
{
  set_name("rabbit pelt");
  add_name("skin");
  set_pname("pelts");
  add_pname("skins");
  add_name("pelt");
  set_short("soft rabbit pelt");
  set_pshort("pelts");
  set_long("A soft rabbit pelt, still bloody.\n");
  set_long("@@long_desc");
  set_adj(({"soft","rabbit","rabbit's"}));
  set_ac(5);
  set_at(A_NECK);
  set_am(({-2,1,1}));
  add_prop(OBJ_I_WEIGHT,(400+(random(200))));
  add_prop(OBJ_I_VOLUME,(400+(random(100))));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(20)-20);
}

public string
query_race()
{
    return "rabbit";
}

string
long_desc()
{
  string ldesc;
  ldesc = "A soft rabbit pelt, still bloody. ";
  if(this_object()->query_prop("_skin_by_gresolle"))
    ldesc += "A tailor could probably make something nice out of it! ";
  return break_string(ldesc + "\n", 75);
}
