// file name: stair1
// creator: Ilyian (October 9, 1995)
// last update:
// purpose: Quarters in the Infidel Hideout
// note:
// bug(s):
// to_do:

inherit "/d/Avenir/common/bazaar/infidel/infidel";
#include "infidel.h"

void
create_room()
{
   set_long("This is a narrow and unsteady set of stairs "
           +"that leads down into a dingy hall below. ");
   set_short("stairs");
   AI(({"stair","stairs","staircase"}),"The stairs seems to "
           +"be hastily constructed and lead down into a "
           + "dingy hallway below.\n");
   hall_exit("1","down");
   clone_object(OBJ+"trapdoor_d")->move(TO);
}
