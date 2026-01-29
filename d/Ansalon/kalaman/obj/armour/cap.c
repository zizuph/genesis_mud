inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

string *gAdj1 = ({"fancy","broad-rimmed",
  "well-worn","new","bright","wide-brimmed","jaunty",
  "plumed","elegant","black","blue","white","red"});

string *gName = ({"hat","cap","beret","hat"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif
create_armour()
{

    set_name(ONE_OF(gName));
    set_adj(ONE_OF(gAdj1));
    set_short(query_adj() + " " +query_name());
    set_long("This is a simple " +short() +
      " often worn by citizens of Kalaman.\n");
    set_ac(2);
    set_am(({0,0,0}));
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 200);
}
