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
set_long("You have come to an intersection at the west end of the port "
	+"area of Zhentil Keep. A road leads off to the northwest, and "
	+"another leads east. There are a few houses lined up against "
	+"the city wall here, it may be possible to enter some of them. "
	+"Guards rush by, off to put fear in the hearts of the citizens "
	+"here. The rough cobbled streets are anything but easy on the "
	+"feet. The streets are lined with tall buildings interspersed "
	+"with small homes. The buildings are unenterable by all but "
	+"their owners, and those with special permission. Overhead, a "
	+"dark gray cloud looms menacingly, keeping the city in a "
	+"perpetually foul mood.\n");
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
add_cmd_item("house","enter","@@enter");
add_exit(ZHENT +"port/p1","east");
add_exit(ZHENT +"port/p21","northeast");
add_exit(ZHENT +"port/p3","northwest");
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
set_alarm(1.0,0.0,"reset_room");
}
enter()
{
write("You push open the door and step into the house.");
set_dircmd("house");
TP->move_living("into a small house.\n","/d/Kalad/common/zhent/port/house1");
return 1;
}
/*
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
