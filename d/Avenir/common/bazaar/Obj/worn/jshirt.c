// chain mesh shirt for jadestone doll
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>


void
create_armour ()
{
  set_short("black shirt of fine chain mesh");
  set_name(({"shirt","mesh","chainmail"}));
  set_adj(({"black","fine","chain"}));
  set_long ("This shirt is masterfully crafted by linking "+
            "together thousands of tiny, black steel rings, to "+
            "make a very strong and light armour.\nIt feels "+
            "slightly warm, as if someone has been wearing it "+
            "recently.\n");
  set_ac (40);
  set_am(({ 1, 3, -5}));
  set_at (A_BODY);
  add_prop (OBJ_I_WEIGHT, 2200);  // about 5 pounds
  add_prop (OBJ_I_VOLUME, 1500);
}


