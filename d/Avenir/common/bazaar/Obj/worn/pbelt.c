// Standard peasant belt for guards in the Bazaar area.
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

string *randadj;
string *randtype;
string thisadj;
string thistype;

void
create_armour ()
{
  randadj = ({ "long", "thick", "leather", "thin",
               "frayed", "loose" });
  randtype = ({ "rope", "belt" });

  thisadj = randadj[random(sizeof(randadj))];
  thistype = randtype[random(sizeof(randtype))];

  set_name(thistype);
  set_adj(thisadj);
   set_short(thisadj+" "+thistype);
  set_long ("This "+thistype+" is worn around the waist to hold "+
            "the pants up.\n");
  set_ac (1);
  set_am(({ 0, 0, 0}));
  set_at (A_WAIST);
}

