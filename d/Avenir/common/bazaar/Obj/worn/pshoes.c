// Standard peasant shoes for guards in the Bazaar area.
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
  randadj = ({ "well-worn", "dusty", "old", "dirty", "white", 
               "leather", "large", "soiled", "new", "clean",
               "tattered"});
  randtype = ({ "shoes", "boots", "sandals", "moccassins" });

  thisadj = randadj[random(sizeof(randadj))];
  thistype = randtype[random(sizeof(randtype))];

  set_name(thistype);
  set_short("pair of "+thisadj+" "+thistype);
  set_adj(thisadj);

  set_long ("These "+thistype+" look cheap and well used. They are "
           +"probably quite comfortable, although they afford "
           +"little protection.\n");
  set_ac (2);
  set_am(({ 0, 1, -1}));
  set_at (A_FEET);
}

