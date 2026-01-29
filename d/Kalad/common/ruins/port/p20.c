inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/common/zhent/defs.h"
#include "/d/Kalad/defs.h"
/*
object ob1;
object ob2;
*/
void
create_room()
{
set_short("Street in Zhentil Keep");
set_long("You are on a street in the city of Zhentil Keep. This street "
	+"is in the far southern half of the city, and is more or less "
	+"a port area. There are buildings hovering over the road, "
	+"looming overhead like vultures over a kill. To the south "
	+"lies the massive city wall, complete with towers and "
	+"battlements. Guards brush by you on their way to stop crime, "
	+"as well as quell uprisings. Overhead, a massive cloud hangs "
	+"like a forebearer of the plague, stifling joy, and causing "
	+"oppression in the name of the foul gods of this city.\n"); 
add_item(({"house","houses","home","homes"}),"They are the small homes "
	+"of commoners.\n");
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
add_item(({"guard","guards","soldiers","soldier"}),"They are the guards "
	+"of the city who do their best to maintain order in the city.\n");
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
add_exit(ZHENT +"port/p1","west");
add_exit(ZHENT +"port/p23","northeast");
add_exit(ZHENT +"port/p19","east");
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
reset_room()
{
       if (!ob1 || !ob2)
      {
      ob1 = clone_object("/d/Kalad/common/zhent/npc/kid.c");
      ob1 ->move_living("xxx", this_object());
      ob2 = clone_object("/d/Kalad/common/zhent/npc/woman.c");
      ob2 ->move_living("xxx", this_object());
      }
       
}
*/
