inherit "std/room";
#include "/d/Rhovanion/defs.h"
#include "campdef.h"
#include "trygo.o"
#include <ss_types.h>
 
int maxbar;
 
void create_room()
{
  set_long("Very dirty looking room. There are many items lying "+
           "around between diffirent piles of garbage. You wonder "+
           "what is this room used for..\n");
  set_short("Dirty room");
  add_item(({"pile","piles","garbage"}),"Obviously looking piles "+
             "of garbage.\n");
  maxbar=0;
 
  add_exit(CAMPDIR+"wandroom","north",0);
  add_exit(CAMPDIR+"wcamp4","east",0);
}
 
#include "resetcamp.o"
 
