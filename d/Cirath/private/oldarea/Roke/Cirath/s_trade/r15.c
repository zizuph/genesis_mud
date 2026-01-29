inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("In a village on the southern trade-route");
  
  set_long(break_string(
           "This little village is not in the best shape. Propably "+
           "because the inhabitants are very poor. The houses are "+
           "small and made of wood. To the north is a house that looks "+
           "like a taverna of some kind and south is an entrance to "+
           "another house. The trade-route leads out of the village to "+
           "the west and further into it to the east.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"river","water","stream","durni","Durni"}),"The river "+
           "Durni flows west of you.\n");
  add_item("village","It's one of the poor villages that are inhabited by "+
           "the 'inlanders' as the cirathian people prefer to call them./n");
  add_item(({"house","houses"}),"The houses are small and not very well-kept.\n");
  add_item(({"inhabitant","inhabitants","inlander","inlanders"}),"You can't "+
           "see any, perhaps they're inside?\n");
  add_item("wood","The houses are made of it.\n");
  add_item("tavern","It's a little tavern called 'Olgor's Fish and Crops'.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r16","west");
  add_exit(S_TRADE+"r14","east");
  add_exit(S_VILLAGE+"tavern","north");
  add_exit(S_VILLAGE+"house1","south");

}
