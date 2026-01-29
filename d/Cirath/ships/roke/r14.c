inherit  "/std/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Roke/common/defs.h"


int ran;
string long;

create_room() 
{
 ::create_room();

set_short("Track");
set_long("@@slong");

add_item(({"mountain","mountains"}),"The huge range towers above you.\n"
	+ "You feel very small...\n");
add_item(({"road","track"}),"The road is little more that a dirt"
	+ " track leading north and south.\n");
add_item(({"orchard","tree","trees"}),"You can barely make out the apple"
	+ " trees to the south.\n");


add_exit("/d/Cirath/ships/roke/roke_port.c","north",0,1,0);
add_exit(ATUAN + "r13","south",0);
add_exit(ATUAN + "r16","northeast",0);

/* I have disabled these weather-things until someone codes 
   it properly. /Glindor
call_out("weather1",10);
*/
}

slong()
{
ran = random(6);

long = (BS("You are on a rough dirt track that leads north and south."
	+ " To the south are rows of trees all in full blossom. To the"
   + " north looms a massive mountain range, which spread its shadow"
	+ " over you. There is a distinct chill in the air.",70));

return long;
}

weather1()
{
	tell_room(TO,"It starts raining.\n");
	call_out("weather2",20);
}

weather2()
{
	tell_room(TO,"The rain gets harder.\n");
	call_out("weather3",20);
}

weather3()
{
	tell_room(TO,"The rain begins to ease off.\n");
	call_out("weather4",20);
}

weather4()
{
	tell_room(TO,"It stops raining.\n");
	call_out("weather1",20);
}
