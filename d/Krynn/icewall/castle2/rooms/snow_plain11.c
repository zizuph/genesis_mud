#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/common/warfare/warfare.h"

#include <macros.h>
#include <stdproperties.h>

inherit ICEOUTROOM2;

void add_stuff();

object ship;

void
create_icewall_room()
{

   set_short("In an icy bay");
   set_long("@@long_descr");

   set_area_name(WAR_AREA_ICEWALL);

   add_exit("snow_plain9","northwest","@@northwest");

   add_item(({"bay","icy bay"}),"The icy bay is nothing more then a " +
     "deep gouge in the snow-covered coast, offering shelter from the " +
     "mad, cold wind.\n");
   add_item(({"waste","snow waste","snow plains","plains"}),"Frozen. " +
     "Endless. Dangerous. Venture with care...\n");

   add_prop(ROOM_I_NO_CLEANUP,1);
   add_prop(OBJ_S_WIZINFO,"To restart the ship, ONLY if it is stuck, type " +
         "'Call here restart_ship <reason>'.\n");

   set_tell_time(900);

   add_tell("Outside the shelter of the icy bay, the mad, cold wind " +
    "shrieks in its fury. Unnerving, to say the least...\n");

   add_stuff();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string
long_descr()
{
   string ret_str = "" +
   "You are sheltered within an ice bay. The snow-covered coast is " +
   "littered here with frozen crates, broken ship equipment, and even " +
   "old, torn canvas. It is suprising, but apparently a ship makes " +
   "a regular stop here. " +
   "There is a path venturing out of sheltered ice bay but " +
   "one could always wait in the relative safety of the bay " +
   "for the ship to return and carry him from " +
   "this forsaken land. ";

    switch (GET_SEASON)
    {
        case WINTER:
            ret_str += "However, the deeper chill of the winter is in the air, " +
                       "and the ocean is frozen solid. No ship will " +
                       "be arriving here any time soon...\n";
            break;
        case SPRING:
           ret_str += "The ocean is turbulent and unruly\n";
            break;
        case SUMMER:
            ret_str += "The ocean appears calm and sad.\n";
            break;
        case AUTUMN:        
            ret_str += "The ocean batters the coast, raging.\n";
            break;
    }
    return ret_str;
}
      
int
northwest()
{ 
  write("You tred upward, out of the sheltered ice bay. The wind picks " +
   "up around you.\n");
  say(QCTNAME(TP) + " treds upward, out of the sheltered ice bay.\n");
  return 0;
}        

void
add_stuff()
{
    seteuid(getuid(this_object()));
    if (!ship)
    {
        ship = clone_object("/d/Krynn/icewall/castle2/ship/ship");
        ship->start_ship();
    }
}

void
reset_room()
{
    add_stuff();
}

void
restart_ship(string reason)
{
    if (!reason)
      {
      write("Can't restart the ship without a reason.\n");
      return 0;
      }
    (ship->query_captain())->remove_object();
    ship->remove_object();
    add_stuff();
    write_file("/d/Krynn/common/log/shiprestart", extract(ctime(time()), 4, 15)
     + " Palanthas-Icewall " + capitalize(this_player()->query_real_name()) + " " + reason + "\n");
    write("Ship restarted.\n");
}
