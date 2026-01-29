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
           "The small village doesn't look especially well-kept. The "+
           "people who lives here are poor and lives on what they can "+
           "get from their fields and the river. The small houses are "+
           "made of wood and an entrance to one of them is to the south. "+
           "The road continues west and northeast. To the west further "+
           "into the village and northeast to a pier where a boat takes "+
           "travellers over the river Durni.\n"
           ,60));  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"The river "+
           "Durni flows west of you.\n");
  add_item("jungle","This is the jungle that covers the southeastern "+
           "part of Athas.\n");
  add_item("village","It's one of the poor villages that are inhabited by "+
           "the 'inlanders' as the cirathian people prefer to call them./n");
  add_item(({"city","ciubori"}),"A cirathian city that lies south of here.\n");
  add_item("pier","It's a wooden pier nortwest of you.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r15","west");
  add_exit(S_TRADE+"r13","northeast");
  add_exit(S_VILLAGE+"house2","south");

}
