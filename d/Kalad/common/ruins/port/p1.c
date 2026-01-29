inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/common/zhent/defs.h"
#include "/d/Kalad/defs.h"
object ob1;
object ob2;

void
create_room()
{
set_short("Street in Zhentil Keep");
set_long("This is a plain street in the city of Zhentil Keep. To your "
	+"south lies the great southern gate that protects the city "
	+"from invaders, and champions of good. The gate, in conjunction "
	+"with the city wall, have never been broken through by "
	+"invaders. The rough cobbled streets "
	+"lead to both the east and west. Towering over the streets are "
	+"tall buildings which seem to hover overhead like dark cliffs. "
	+"Soldiers pass by on a regular basis, off to quell some threat, "
	+"or stop one before it starts. An oppressive cloud of gray "
	+"hangs over the city, keeping the people apathetic to the "
	+"horrible evil commited by the rulers of Zhentil Keep.\n");
add_item(({"street","streets"}),"The streets are worn cobblestones, "
	+"which apparently get a lot of use. The cobbles are covered "
	+"in crabweed and lichen.\n");
add_item(({"gate","southern gate","great southern gate"}),"It is a "
	+"massive gate made of wood reinforced with strips of "
	+"tempered steel, and attached to the city wall.\n");
add_item(({"wall","city wall"}),"This wonder of stone towers 20 feet "
	+"into the air, and has battlements and towers for the guards "
	+"of the city to man in case of attack.\n");
add_item(({"buildings","building"}),"The buildings are tall, some reaching "
	+"six stories, and are dark and gloomy.\n");
add_item(({"soldiers","soldier"}),"They are the guards of the city who "
	+"do their best to maintain order in the city.\n");
add_item(({"cloud"}),"A dark gray cloud hangs over the city, veiling "
	+"the city from the normal weather experienced by the realms. "
	+"Here the will of the gods creates the weather, and for the "
	+"grim gods of death, gray clouds are perfect.\n");
add_item(({"tower","towers"}),"These are guard towers mounted along "
	+"the city's wall.\n");
add_item(({"battlements"}),"They are used to provide cover from archers "
	+"for guards on the wall.\n");
/*
add_cmd_item("house","enter","@@enter");
*/
add_exit(ZHENT +"port/p20","east");
add_exit(ZHENT +"port/p2","west");
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
set_alarm(1.0,0.0,"reset_room");
}
/*
enter()
{
write("You push open the door and step into the house.");
set_dircmd("house");
TP->move_living("into a small house.","/d/Kalad/common/zhent/port/house1");
return 1;
}
*/
reset_room()
{
       if (!ob1 || !ob2)
      {
	ob1 = clone_object("/d/Kalad/common/zhent/npc/r_guard.c");
      ob1 ->move_living("xxx", this_object());
	ob2 = clone_object("/d/Kalad/common/zhent/npc/r_guard.c");
      ob2 ->move_living("xxx", this_object());
	ob1->team_join(ob2);
      }
       
}
