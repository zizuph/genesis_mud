// leather gloves for jadestone doll
//    -Ilyian, May 1995

inherit "/d/Avenir/inherit/cloth_arm";

#include <wa_types.h>
#include <stdproperties.h>


void
create_armour ()
{
  set_short("pair of leather gloves");
  set_name(({"gloves","pair","glove"}));
  set_adj(({"pair","leather","black"}));
  add_pname(({"clothes", "clothing"}));
  set_long ("This pair of black leather gloves does not seem "+
            "to offer a whole lot of protection, but they are "+
            "very comfortable\nThe feel slightly warm, as if they "+
            "had been worn recently.\n");
  set_ac (3);
  set_am(({ 0, 0, 0}));
  set_at (A_HANDS);
}

