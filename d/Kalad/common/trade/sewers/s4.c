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
set_long("The sewers continue to the north and south, darkness making "
	+"directions seem to blend together. The walls of the sewer "
	+"are covered with a shiny fungus type growth, and offer "
	+"the only reproach from the vast void of the darkness. "
	+"There is a peculiar odor to the air here, one that "
	+"does not seem characteristic of a typical dirty sewer. "
	+"The strangest thing about the sewers so far, is that "
	+"there is no sewage, just empty, dark tunnels.\n");
add_item(({"wall","walls"}),"The walls are slick with a shiny fungus "
                           +"and condensation from the damp sewer.\n");
add_item(({"odor"}),"The odor is uncharacteristic of any sewer you "
                   +"have ever been in, almost alien to this place. "
                    +"But you aren't really an expert on sewers, so "
                  +"you can't be sure.\n");
add_item(({"fungus"}),"This is a shiny, almost luminescent fungus. "
	   	     +"it is shiny, and slightly glowing, but "
		     +"enough for the naked eye to see by.\n");
add_exit(TRADE(sewers/s3),"north");
add_exit(TRADE(sewers/s5),"south");
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
