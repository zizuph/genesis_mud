#include "/d/Ansalon/goodlund/nethosak/city/local.h" 
#include "/d/Ansalon/common/defs.h"#include <stdproperties.h>
inherit MITHAS_IN;
 
object captain;
object guard;
object guard2;

void 
reset_mithas_room()
{
    if (!captain)
    {
        captain = clone_object(MNPC + "captainGuard");
        captain->move(TO);
    }
    if (!guard)
    {
        guard = clone_object(MNPC + "cGuard");
        guard->move(TO);
    }
    if (!guard2)
    {
        guard2 = clone_object(MNPC + "cGuard");
        guard2->move(TO);
    }
}
void
create_mithas_room()
{
   object door;
   set_short("Captain Quarters");
   set_long("@@long_descr"); 
   add_item(({"bed"}),"The bed looks real soft and comfortable, "+
                      "it makes you feel all tired.\n");
   add_item(({"door"}),"The door has been made from some heavy "+
                       "wooden boards, it has a large lock, but "+
                       "it looks quite rusty and unused.\n");
   add_item(({"table"}),"The table has been made like a circle, it's "+
                        "made out of wood.\n");
   add_item(({"desk"}),"A simple desk, that the captain use to write "+
                       "different papers on. At the moment the desk "+
                       "is empty.\n");

    set_tell_time(150);
    add_tell(({
       "You hear someone snoring close by.\n",
       "The smell of sweet and leather fills the room.\n", }));  

    door = clone_object(MOBJ + "woodendoor");
    door->move(this_object());
    reset_mithas_room();
}

string
long_descr()
{ 
   return "You are standing in a luxury room in the barracks "+
          "of the Imperial guards. The room here looks much "+
          "cleaner then any of the other rooms. A large table "+
          "is place in the center of the room and four chains "+
          "surrounds it. There's also a small wooden desk and "+
          "soft looking bed stading by one of the walls. The "+
          "only exit out of this room is to the north, through "+
          "a wooden door.\n";
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


