inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/common/zhent/defs.h"
#include "/d/Kalad/defs.h"
/*
#include "/d/Kalad/common/zhent/house.h"
*/
#include "/d/Kalad/common/zhent/guard.h"
#define HOUSE "/d/Kalad/common/zhent/port/house4.c"
object ob1;
object ob2;
object ob3;
void
create_room()
{
set_short("Street in Zhentil Keep");
set_long("You have arrived at the secondary southern gate in Zhentil "
	+"Keep. Outside lies only the wilderness, and untamed "
	+"countryside. The gate is connected to the city wall, and is "
	+"as tall and as strong. A guardhouse is here, and some guards "
	+"can be seen inside of it. The buildings are not as densely "
	+"concentrated as in the rest of the city, and there are no "
	+"civilian homes here. Shadows leap across the ground, cast by "
	+"an angry gray cloud that rests overhead.\n"); 
add_item(({"guardhouse"}),"It is a small guardhouse where the guards "
	+"rest.\n");
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
add_exit(ZHENT +"port/p16","west");
add_exit(ZHENT +"port/p14","east");
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
set_alarm(1.0,0.0,"reset_room");
}
