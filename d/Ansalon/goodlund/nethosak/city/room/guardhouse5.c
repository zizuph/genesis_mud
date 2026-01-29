#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_IN;

object guard;
object guard2; 

void 
reset_mithas_room()
{
    if(!objectp(guard))
    {
      guard = clone_object(MNPC + "minotaurGuard");
      guard -> move(this_object());
   }
   if(!objectp(guard2))
      {
      guard2 = clone_object(MNPC + "minotaurGuard");
      guard2 -> move(this_object());
   }
}
void
create_mithas_room()
{
   set_short("Southern guardroom");
   set_long("@@long_descr");

   add_exit(MROOM + "road25","southwest","@@guard_exit",0); 
   add_exit(MROOM + "road24","northwest","@@guard_exit",0);

   reset_mithas_room();
}

string
long_descr()
{ 
   return "This is a crude guardroom in the southern part of "+
   "the Isle of Mithas. The floor is covered with dirt however "+
   "there are some places where the floor is paved with grey "+
   "rocks. The room is made out of wood, crudely assembled "+
   "and unpainted. A large wooden rack, has been placed by the "+
   "north wall, and a small table with two chairs stands in "+
   "the middle of the room. The road to the northwest and "+
   "southwest leads back to the main road.\n";
}

int
guard_exit()
{
   write("You walk out of the guardroom... \n");
   return 0;
}

