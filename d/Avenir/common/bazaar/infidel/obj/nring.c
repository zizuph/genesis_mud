// Gold ring for Nochipa
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>


void
create_armour ()
{
  set_short("thin golden ring");
  set_name(({"band","ring"}));
  set_adj(({"thin","golden","gold"}));
  set_long ("This is a very thin band that fits around the finger. "+
            "Inscribed upon it in miniscule letters is: Nochipa, "+
            "disciple of Alphum.\n");
  set_ac (3);
  set_am(({ 0, 0, 0}));
  set_at (A_ANY_FINGER);
  add_prop(OBJ_I_VALUE, 1500);
  add_prop(OBJ_I_WEIGHT, 200);
  add_prop(OBJ_I_VOLUME, 100);   // It is small, after all...

}
