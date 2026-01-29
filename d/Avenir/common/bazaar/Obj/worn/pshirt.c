// Standard peasant shirt for guards in the Bazaar area.
//    -Ilyian, May 1995

inherit "/d/Avenir/inherit/cloth_arm";

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
               "tattered", "red", "black", "button-down"});
  randtype = ({ "shirt", "tunic", "blouse",  });

  thisadj = randadj[random(sizeof(randadj))];
  thistype = randtype[random(sizeof(randtype))];

  set_name(thistype);
  set_adj(thisadj);

   set_long("This "+thistype+" looks cheap and well used. It is the "
           +"typical clothing of a peasant in these parts. It may "
           +"be comfortable, but offers little protection.\n");

  set_short(thisadj+" "+thistype);

  set_ac (2);
  set_am(({ 0, 1, -1}));
  set_at (A_ARMS | A_BODY);
}


