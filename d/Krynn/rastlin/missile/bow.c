inherit "/d/Wiz/rastlin/missile/mweapon";
#include "missile.h"

create_mweapon()
{
   set_adj("short");
   set_name("bow");
   add_name("shortbow");
   set_long("A short bow of dark wood, strung with a " +
      "thong of lion skin.\n");
   set_bow_class(M_BOW);
   set_bow_pen(60);
   set_bow_acc(10);
}
