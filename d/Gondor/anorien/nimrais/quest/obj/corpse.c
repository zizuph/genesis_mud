inherit "/std/food";
#include "stdproperties.h"
#include "/d/Gondor/defs.h"
 
create_food()
{
    set_short("@@my_short");
    set_name("eagle");
    add_name("corpse of eagle");
    add_name("corpse");
    set_long("@@my_long");
    set_amount(2000);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 6000);
 
}
 
string
my_short()
{
    if (ENV(TO)->test_fire()) return "corpse of an eagle (being roasted on "+
      "the fire)";
    return "corpse of an eagle";
}
 
string
my_long()
{
    string str;
    str = "Once it was a large eagle, but now it has been plucked. ";
    if (ENV(TO)->test_fire())
      str += "It is being roasted on the fire.";
    return BS(str + "\n");
}
