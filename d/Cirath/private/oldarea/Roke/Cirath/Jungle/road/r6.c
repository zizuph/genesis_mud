inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("In a small village");
  
  set_long(break_string(
           "You're standing in a small village placed in a "+
           "clearing. The houses looks neat and well-kept. "+
           "All around the clearing, the jungle grows tight. "+
           "North is an entrance to one of the small houses "+
           "of the village.\n"
           ,60));  

  add_item(({"clearing","opening"}),"The clearing is quite big.\n");
  add_item(({"djungle","tree","trees"}),"The jungle all around the clearing.\n");
  add_item("road","It's a small, almost invisible road leding through "+
           "the clearing.\n");
  add_item(({"house","houses"}),"The houses is small but nicely built.\n");
  add_item(({"inhabitant","inhabitants"}),"You can't see any. Perhaps they're "+
           "inside.\n");

  add_exit(JUNGLE+"road/house","north");
  add_exit(JUNGLE+"j15","northeast");
  add_exit(JUNGLE+"road/r5","west");

}
