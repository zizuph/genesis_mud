inherit "/d/Rhovanion/lib/caves.c";
#include "def.h"
#include "/sys/macros.h"
#include "door.h"
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"

object key;
int key_present=1;

create_cave()
{
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(1);
  set_long("The corridor ends here, on the walls you see some" +
	   " crevices. The corridor continues back to the north. "
	   + " \n");

  add_prop(OBJ_I_SEARCH_TIME, 2);
  add_prop(OBJ_S_SEARCH_FUN, "search");
  
  add_item(({"ledge","crevice","crevices"}),
	   "It looks like the elves planned to extend this corridor here " +
	   "but forgot it, the crevices containing nothing of interest, " +
	   "or? \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave27","north",0,1);
}

void 
reset_room(){ 
  key_present=1; 
}

string search(object player, string str)
{
  string item, rest;
  int skill;
  
  if (sscanf(str, "%s for %s", item, rest) != 2)
    item = str;
  
  if (item != "ledge" && item != "crevice" && item != "crevices")
    return "";
  
  skill = TP -> query_skill(SS_AWARENESS);
  
  if (key_present && (skill > 30) && random(5))
    {
      key_present = 0;
      key = clone_object(THIS_DIR + "silver_key");
      key -> set_key(SILVER);
      key -> move(TP);
      return "You find a silver key on the ledge. \n";
    }
  else
    return "";
}
