// file name: quar5
// creator: Ilyian (October 9, 1995)
// last update:
// purpose: Quarters in the Infidel Hideout
// note: 
// bug(s):
// to_do:

inherit "/d/Avenir/common/bazaar/infidel/infidel";
#include "infidel.h"

void reset_room();
object guard, female;

void
create_room()
{
   quar_long("Someone has tried to make this room as "
            +"comfortable as possible, placing soft "
            +"chairs in the middle, and covering "
            +"the walls with heavy light tapestries.");
   set_short("lounge");
   AI(({"chair","chairs"}),"The chairs are quite soft, and "
            +"thickly stuffed.\n");
   AI(({"tapestry","tapestries"}),"The tapestries are heavy, "
            +"and made from a light grey cloth that has "
            +"gentle designs on it.\n");
   AI(({"design","designs"}),"The designs are pleasing "
            +"to the eye, although somewhat abstract.\n");
   hall_exit("9","northeast");

   reset_room();
}

void
reset_room()
{
   if(!guard)
     {
        guard = clone_object(MON+"guard");
        guard->arm_me();
        guard->move(TO);
        guard->add_act("hmm");

     }
   if(!female)
     {
        female = clone_object(MON+"g_infidel");
        female->arm_me();
        female->move(TO);
     }
 
}
