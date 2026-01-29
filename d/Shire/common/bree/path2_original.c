inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#define MAX_ORCS 5

/*
 * Global variables
 */
object leader, *orcs = ({ });

/*
 * Prototypes
 */
void make_orcs();

void
reset_room()
{
  make_orcs();
}

void
create_room()
{
   set_short("A dense path north of Bree");
   set_long("The path you have been following has come to an abrupt and "+

   "utter end. There is no way out except that which you arrived on, "+
    "and all signs point to an ambush. You'd better beat "+
   "a hasty retreat.\n");

   add_item(({"bushes","bush","vegetation","tracks","track"}), "The "+
    "bushes around here are quite dense, though you can find your way "+
    "back to the south, even though there is absolutely no way you can "+
    "go in any other direction.\n");

   add_item(({"sign","signs","ambush"}), "The signs are just like "+
   "you expect: rustling in the bushes around you, smoldering campfires, "+
   "and scattered debris.\n");

   add_item(({"debris","campfire","campfires","smoldering campfires"}), "Well, "+
   "it's mostly trash and ashes.\n");

   add_exit(BREE_DIR + "path1","south",0,1);

   reset_room();
}

void
make_orcs()
{
  int i;

  if(!leader)
  {
    leader = clone_object(BREE_DIR + "npc/lead_orc");
    leader->move(TO);
    tell_room(TO,capitalize(LANG_ADDART(leader->query_nonmet_name()))+
                 " smashes down the bushes.\n");
  }
  if(!sizeof(orcs))
    orcs = allocate(MAX_ORCS);
  for(i = 0; i < MAX_ORCS; i++)
    if(!orcs[i])
    {
      orcs[i] = clone_object(BREE_DIR + "npc/path_orc");
      leader->team_join(orcs[i]);
      orcs[i]->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(orcs[i]->query_nonmet_name()))+
                   " suddenly jumps from behind the bushes!\n");
    }  
    else
      if(orcs[i]->query_leader() != leader)
        leader->team_join(orcs[i]);
}
