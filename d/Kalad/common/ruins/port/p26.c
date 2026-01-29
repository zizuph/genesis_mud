inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/common/zhent/defs.h"
#include "/d/Kalad/defs.h"
/*
#include "/d/Kalad/common/zhent/guard.h"
#define HOUSE "/d/Kalad/common/zhent/port/house8.c"
object ob1;
object ob2;
object ob3;
*/
void
create_room()
{
set_short("Street in Zhentil Keep");
set_long("There is an intersection here with the street continuing "
	+"east and west, but with branches going north and southeast. "
	+"To the north, the street once again approaches the foul "
	+"river that flows through the city. The street has a few homes "
	+"and buildings along it, but not too many here. The guards "
	+"of the city stand around, keeping some semblance of peace.\n");
add_item(({"shadow","shadows"}),"The shadows seem to move as if with "
	+"a will of their own.\n");
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
add_exit(ZHENT +"port/p25","west");
add_exit(ZHENT +"port/p27","east");
add_exit(ZHENT +"port/p15","southeast");
add_exit(ZHENT +"port/p8","north");
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
set_alarm(1.0,0.0,"reset_room");
}
