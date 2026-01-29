// pants for jadestone doll
//    -Ilyian, May 1995

inherit "/d/Avenir/inherit/cloth_arm";

#include <wa_types.h>
#include <stdproperties.h>


void
create_armour ()
{
  set_short("pair of light grey pants");
  set_name(({"pair","pants","pant"}));
  set_adj(({"light","grey"}));
  add_pname(({"clothes", "clothing"}));
  set_long ("These pants are fashioned of a strange sort of "+
            "cloth that you have never seen before. They are "+
            "very light, and seem to be impervious to rips "+
            "or tears.\n");
  set_ac (20);
  set_am(({ 3, 1, -5}));
  set_at (A_LEGS);
  add_prop (OBJ_I_WEIGHT, 1000);  // about 2 pounds
  add_prop (OBJ_I_VOLUME, 1500);
}


