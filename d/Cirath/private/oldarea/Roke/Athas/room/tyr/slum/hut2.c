inherit "/std/room";
#include "slum.h"

#define NUM	1

	object *npc;
 
void make_monster(int i)
{
	npc[i]=clone_object(A_NPC_D+"poorcit");
    npc[i]->move(this_object());
}

void reset_room()
{
    int i;
    for(i=0; i<NUM; i++)
	if(!npc[i])
	    call_out("make_monster", 1, i);
}

create_room() {
	npc = allocate(1);

	set_short("Inside a small hut");
	set_long(BSS("You find yourself inside a small hut, very small "+
		"actually and there is only some spartan furniture "+
			"around here: A small table and some rugs to sleep "+
		"on in the corner.\n"));

	add_item(({"small table","table"}),BSS(
			"This small wood table looks as if it would "+
			"break if you put something on it.\n"));
	add_item(({"rugs","rug"}),BSS(
			"These rugs are put here to make it a soft place "+
			"to sleep.\n"));

	add_exit(SUL_STR+"road7","north",0);

	call_out("reset_room", 1);

}

