#include <macros.h>

#include "defs.h"

inherit TRICKSTER_STD_ROOM;

void create_room()
{
 set_short("End of a hallway");
 set_long(BS(
   "The hallway comes to a sudden end.  This room looks very strange.."+
   "There are pillows scattered all over the room... most of them "+
   "gathered in a pile underneath a hole, which has been dug in the "+
   "ceiling.  But the thing which strikes you as the most out of place "+
   "in this room, is a wooden panel which lies against the south wall. "+
   "The only obvious way out of here is to head back the way you "+
   "came.\n"));

 add_item("pillows","A pile of pillows lie scattered across the ground, "+
   "a pile of them lie directly underneath a hole in the ceiling.\n");
 add_item("hole","The hole is a rather dark one, just about the proper "+
   "size for a person to fit into.  It resides just above you in the "+
   "ceiling hanging over a pile of pillows which are scattered across "+
   "the floor.\n");
 add_item(({"wall","panel"}),"Hmmm... part of the wall is a wooden "+
   "panel..  It seems  out of place here in the room, where all the "+
   "other walls are of earth. Upon closer examination of the panel "+
   "you notice that it looks very loose and you might be able to give "+
   "it a push.\n");

 add_cmd_item(({"wall","panel"}),"push","@@do_push");

 add_exit(TRICKSTERS+"hall","north");

 clone_object(TRICKSTERS+"obj/shelf")->move(TO);
}

int do_push(string what)
{
 write("As you push the panel it swings , throwing you through the "+
   "opening in wall and down!\n");
 say(QCTNAME(TP)+" pushes the "+what+" and suddenly disappears! You "+
   "hear some scream downstairs!!\n");
 TP->move_living("M",TRICK_TUNNEL);
 say("With a loud scream "+QTNAME(TP)+" falls from above!\n");
 return 1;
}

