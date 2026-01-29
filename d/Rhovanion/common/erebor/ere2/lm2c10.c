inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <filter_funs.h>
#include "door.h"
#define CAVE_DIR ERE_DIR + "ere2/"

 
 
object key;
object pen;
object servant;
int pen_present = 1;
 
void reset_room();
 
void create_cave()
{
  object west_door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(5);
  set_long("This is the schoolhouse for the dwarves in Erebor. "
        + "Some desks are arranged in lines and a bigger "
        + "desk belonging to the teacher is standing in front "
        + "of the rest. The smell in here makes you belive that "
        + "no education has taken place here for a long time.\n");

  add_item(({"first desk","fourth desk"}),"This desk "
        + "is like almost all of the desks carved out of rock. "
        + "The only exeption is the third desk made out of "
        + "bauxit.\n");
 
  add_item("third desk","This desk is no different from "
        + "the rest, exept beeing made from bauxit.\n");
  add_item("second desk","This little desk attracts your "
        + "suspicious mind. You cannot really tell why though.\n");

  add_item(({"desk","desks"}),"The desks are made of "
        + "rock and lined in perfect lines from front to back.\n");
 
  add_prop(OBJ_I_SEARCH_TIME, 2);
  add_prop(OBJ_S_SEARCH_FUN, "search");
 
  west_door = clone_object(CAVE_DIR + "door_lm2c10");
  west_door->move(TO);
 
  key = clone_object(CAVE_DIR + "small_key");
  key->set_key(SMALL);
  west_door->set_key(SMALL);
 
  reset_room();
 
}
 
void 
reset_room() 
{
    pen_present = 1; 
     if(sizeof(FILTER_LIVE(all_inventory(TO))))
         {
         servant = clone_object(CAVE_DIR + "servant");
         servant->move(TO);
         }
}
 
string search(object player, string str)
{
  string item, rest;
  int skill;
  
  if (sscanf(str, "%s for %s", item, rest) != 2)
    item = str;
  
    if (item != "second desk")
    return "";
  
  skill = TP -> query_skill(SS_AWARENESS);
  
    if (pen_present && (skill > 30))
    {
      pen_present = 0;
      pen = clone_object(CAVE_DIR + "silver_pen");
      pen -> move(TP);
      return "You find a silver pen inside the desk. \n";
    }
  else
    return "";
}
