inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
object ob1;
object ob2;

void
create_room()
{
set_short("Sewers");
set_long("You are in a damp sewer. It is very warm here, as well as "
	+"extremely dark. The walls lead off north into the darkness, "
	+"and there is an exit leading up through a trap door. It "
	+"is rather plain here, but the air smells strange, an odor "
	+"that typically does not emanate from sewers seems to be "
	+"present.\n");
add_item(({"wall","walls"}),"The walls are slick with a shiny fungus "
                           +"and condensation from the damp sewer.\n");
add_item(({"odor"}),"The odor is uncharacteristic of any sewer you "
                   +"have ever been in, almost alien to this place. "
                    +"But you aren't really an expert on sewers, so "
                  +"you can't be sure.\n");

add_exit(TRADE(house_entrance),"up");
add_exit(TRADE(sewers/s6),"north");
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_I_LIGHT,0);
add_prop(ROOM_NO_TIME_DESC,1);
set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
       if (!ob1 || !ob2)
      {
      ob1 = clone_object("/d/Kalad/common/trade/thief.c");
      ob1 ->move_living("xxx", this_object());
      ob2 = clone_object("/d/Kalad/common/trade/thief.c");
      ob2 ->move_living("xxx", this_object());
      ob1->team_join(ob2);
   }
       
}
