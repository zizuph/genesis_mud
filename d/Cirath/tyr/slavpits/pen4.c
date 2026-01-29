inherit "/std/room";

#include "defs.h"

#define NUM		10
#define NUMM		 5

object *slave, *child;

void make_monster(int i)
{
    slave[i]=clone_object(TYR_NPC+"slave");
    slave[i]->move(this_object());
}
 
void make_monster_two(int x)
{
    child[x]=clone_object(TYR_NPC+"slavekid");
    child[x]->move(this_object());
}

reset_room()
{
    int i;
    for(i=0; i<NUM; i++)
	if ( !objectp(slave[i]) )
	    call_out("make_monster", 1, i);

    for(i=0; i<NUMM; i++)
	if ( !objectp(child[i]) )
	    call_out("make_monster_two", 1, i);
}

create_room()
{
    set_short("Slave pits in Tyr");
    set_long("This is where the king keeps the lowliest of the "+
       "slaves. They usually end up thrown into the the arena "+
       "for the gladiators to brutally slaughter, a dozen at a "+
       "time.\n");

    add_exit(TYR_PITS+ "pen5.c", "east");
    slave = allocate(NUM);
    child = allocate(NUMM);
    call_out("reset_room",1);

}

