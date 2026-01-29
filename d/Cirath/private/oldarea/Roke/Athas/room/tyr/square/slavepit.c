inherit "/std/room";

#include "/d/Roke/common/defs.h"

#define NUM		10
#define NUMM		 5

object *slave, *child;

void make_monster(int i)
{
    slave[i]=clone_object(A_NPC_D+"slave");
    slave[i]->move(this_object());
}
 
void make_monster_two(int x)
{
    child[x]=clone_object(A_NPC_D+"slavekid");
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
    set_long(BSS("You have entered the slave pits in Tyr, here "+
		 "the king keeps the slaves unsold, or the ones who "+
		 "are going to the arenas to fight Gladiators. "+
		 "\n"));

    add_exit(TEM_STR+"road3","south","@@check");
    slave = allocate(NUM);
    child = allocate(NUMM);
    call_out("reset_room",1);

}

check()	
{
    write(BSS("The guard looks carefully at you, so that he can "+
	      "be certain you are not one of the slaves, trying to "+
	      "escape.\n"));
}
