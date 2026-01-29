inherit "/std/room";

#include "road.h"
object monster;
create_room()	{
	set_short("Stadium Road");
	set_long(BSS("You are walking along the Stadium Road, and to the south "+
		"you see the Warriors Way, which leads towards the "+
		"stadium gate. North of here you see the south walls "+
		"of the gladiatorial arena, and to the northwest you "+
		"can see the temple.\n"));


	add_exit(STA_STR+"road2","west",0);
	add_exit(STA_STR+"road4","east",0);
	add_exit(WAR_STR+"road1","south",0);
	add_exit("/d/Roke/Athas/room/tyr/stadium/stadium","north",0);

   set_alarm(1.0,0.0,"reset_room");
}


reset_room()
{
   if(monster) return;

   tell_room(TO, "A gladiator walks out from the arena.\n");
	monster=clone_object("/d/Roke/Athas/npc/gladiator");
   monster->move(TO);
}
