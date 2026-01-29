#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include "/d/Ansalon/goodlund/nethosak/city/obj/door.h"
inherit MITHAS_IN;

object guard;
object guard2;
object guard3;

void 
reset_mithas_room()
{
    if (!guard)
    {
        guard = clone_object(MNPC + "minotaurGuard");
        guard->move(TO);
    }
    if (!guard2)
    {
        guard2 = clone_object(MNPC + "minotaurGuard");
        guard2->move(TO);
    }
    if (!guard3)
    {
        guard3 = clone_object(MNPC + "minotaurGuard");
        guard3->move(TO);
    }

}
void
create_mithas_room()
{
   object door;
   set_short("Barracks hallway");
   set_long("@@long_descr"); 
   add_item(({"bed"}),"The bed looks real soft and comfortable, "+
                      "it makes you feel all tired.\n");

    set_tell_time(150);
    add_tell(({
       "A team consisting of imperial guards rushes pass you.\n",
       "You hear someone snoring close by.\n",
       "The smell of sweet and leather fills the room.\n", }));

    door = clone_object(MOBJ + "woodendoor2");
    door->move(this_object());
  

    reset_mithas_room();
}

string
long_descr()
{ 
   return "You are standing in a busy hallway in the barracks of "+
          "the Imperial guards of Nethosak. The barracks has been "+
          "made of the same grey stone that the guardhouses has "+
          "been by. The hallway continues to the east, west, southeast "+
          "and southwest. To the south a heavy wooden door leads into "+
          "a more luxurious room and the exit to the north takes you "+
          "back to the streets of Nethosak.\n";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
       start_room_tells();
    }
}

