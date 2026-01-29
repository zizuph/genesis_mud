#include "defs.h"

/* /d/Emerald/room/vamp/default.h */

#define MAX_BATS 10

object *bats = ({});
int i;

void make_bats();

CONSTRUCT_ROOM {

    set_short("The Bat Cave.");
    set_long("The Bat Cave. Up under the roof there hangs thousands of "+
	     "small vampire bats. The floor is covered with bad-smelling "+
	     "excrements, and it is an intense vapour here. Some of the "+
	     "beasts move and wheeze loudly. Unless you want to be an "+
	     "involuntary blood donor you should leave now!");
    EXIT("dome","south");
    EXIT("cave_e","east");
    EXIT("cave_n","north");
    EXIT("crosroad","west");
    set_alarm(0.0, 0.0, &make_bats());
}

RESET_ROOM {
    set_alarm(0.0, 0.0, &make_bats());
}

make_bats()
{
    int add;        /* Additional bats. */
    object new_bat; 

    add = MAX_BATS - sizeof(bats);
    while (add-- > 0) {
	new_bat = clone_object(MORIA_NPC + "bat");
	new_bat ->move(TO);
	bats += ({ new_bat });
    }
}
	
    
/*
    if (!bats)
      bats = allocate(4);
    for(i=0;i<4;i++)
      if (!bats[i]) {
	bats[i] = clone_object("players/rogon/npc/bat");
	bats[i]->move(this_object());
      }
    if (!bigbat) {
      bigbat = clone_object("players/rogon/npc/bigbat");
      bigbat->move(this_object());
    }
*/

