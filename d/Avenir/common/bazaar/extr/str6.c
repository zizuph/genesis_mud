// Bazaar Street6 (/d/Avenir/common/bazaar/extr/str6.c)
// creator(s):   Triana 1994
// last update:  Tepisch Aug 94,
//		 Ilyian May 95
//		 Denis, Sep'96: Corrected the tent direction.
//               Cirion, Aug '98: Added pillar for Genesis donations
// purpose:
//
// note:
// bug(s):
// to-do:


inherit "/d/Avenir/common/bazaar/extr/std_center.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

object slave1, slave2, slave3;
reset_room()
{

  if (!slave1)
   {
      slave1 = clone_object(BAZAAR + "NPCS/wom1.c");
      slave1->arm_me();
      slave1->move_living("M", this_object());
    }

  if (!slave2)
   {
      slave2 = clone_object(BAZAAR + "NPCS/man1.c");
      slave2->arm_me();
      slave2->move_living("M", this_object());
    }

  if (!slave3)
   {
      slave3 = clone_object(BAZAAR + "NPCS/ch1.c");
      slave3->arm_me();
      slave3->move_living("M", this_object());
    }
}

void
create_column()
{
    object column;

    reset_euid();

    column = clone_object("/d/Genesis/obj/donation/column");

    if(objectp(column))
        column->move(this_object(), 1);
}

void
create_room()
{
   AE(EXTR + "str5", "west", 0);
   AE(EXTR + "str7", "east", 0);
   AE(EXTR + "centr", "south", 0);
   AE(EXTR + "str3", "north", 0);

   SHORT("North of Bazaar center. A pink and green tent to the east");
   make_the_room(" The cobblestone square gives way to a " +
      "gravel path north of you. The bazaar's center " +
      "is south.\n");

    reset_room();

    // Cirion: pillar for Genesis donations
    create_column();
}

