// Sandals for Nochipa
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_short("pair of soft sandals");
  set_name(({"sandals","pair","sandal"}));
  set_adj(({"pair","soft","leather"}));
  set_long ("These sandals are made from leather, with a very "+
            "simple design. Their straps cross over the tops "+
            "of the feet, and then tie at the back.\nThey feel "+
            "somewhat warm, like they have been worn recently.\n");
  set_ac (4);
  set_am(({ 1, 0, -1}));
  set_at (A_FEET);
}

