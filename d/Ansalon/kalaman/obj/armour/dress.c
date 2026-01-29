inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

string *gAdj1 = ({"silk","frilly","alluring",
  "suggestive","seductive","long","high-necked","expensive",
  "snow-white","azure","midnight-black","brown",
  "green","dirty","plain","sleek","velvet"});

string *gName = ({"dress","gown","blouse","frock","garment"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif
create_armour()
{

    set_name(ONE_OF(gName));
    set_adj(ONE_OF(gAdj1));
    set_short(query_adj() + " " + query_name());
    set_long("This is a simple " +short() +
      ", typical of women from Kalaman.\n");
    set_ac(2);
    set_am(({0,0,0}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 200);
}
