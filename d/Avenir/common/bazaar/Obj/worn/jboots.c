// leather boots for jadestone doll
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>


void
create_armour ()
{
  set_short("pair of low boots");
  set_name(({"boots","pair","boot"}));
  set_adj(({"pair","low","leather"}));
  set_long ("These leather boots are extremely comfortable and well "+
            "broken in. The tops are folded down around the base, so "+
           "they don't really provide any protection for the legs.\n");
  set_ac (4);
  set_am(({ 1, 0, -1}));
  set_at (A_FEET);
}

