inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("On a road in an opening in the jungle");
  
  set_long(break_string(
           "This is a clearing in the jungle. East of you "+
           "lies some houses. On the ground grows grass and "+
           "flowers. The clearing is not natural. The inhabitants "+
           "cut down the trees for material to their neat houses.\n"
           ,60));  

  add_item(({"clearing","opening"}),"The clearing is quite big.\n");
  add_item(({"jungle","tree","trees"}),"The jungle all around the clearing.\n");
  add_item("road","It's a small, almost invisible road leding through "+
           "the clearing.\n");
  add_item(({"house","houses"}),"The houses is small but nicely built.\n");
  add_item(({"inhabitant","inhabitants"}),"You can't see any. Perhaps they're "+
           "inside.\n");

  add_exit(JUNGLE+"j14","west");
  add_exit(JUNGLE+"road/r5","southeast");

}
