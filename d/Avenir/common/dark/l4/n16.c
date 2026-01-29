// file name: ~Avenir/common/dark/l4/n16.c
// creator(s): Farlong, Boriska, Denis
// revision history:
// - added rock for ghost quest. -=Denis /Jan,95
// purpose:
// note:
// bug(s):
// to-do:

/*
n15.c is N
*/

#include "/d/Avenir/common/dark/dark.h"

inherit "/std/room";

void
create_room()
{
  set_short("dead-end");
  set_long("You have reached yet another dead-end in the maze "+
	   "of twisting passages.  This one is large and circular, with " +
	   "small stalactites hanging from the ceiling.\n"); 

  add_exit(L4 + "n15","north");
  add_exit(L3 + "ec3","up");

  BLACK;
  IN;

  AI(({"stalactite", "stalactites"}),
       "The stalactites are phallic shapes hanging from " +
       "the ceiling above and formed of minerals deposited " +
       "by dripping water.\n");    
    AI(({"ceiling", "walls", "wall", "floor", "tunnel"}),
       "Very uninteresting stone.\n");   

	add_npc(MON + "bat", 3);

    clone_object(OBJ+"rock")->move(TO);
}
