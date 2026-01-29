/*
 * Inside tent in Bree orc camp
 * By Finwe, July 2000
 */

#pragma strict_types

#include "local.h"
#include <language.h>
inherit TENT_BASE;
//#define max_orcs 5

object leader, *orcs = ({ });

void make_orcs();

void
create_tent_room()
{
    add_my_desc("Crudely constructed furniture lies scattered " +
        "about the tent. Debris is piled in heaps throughout " +
        "the tent.\n");

    add_exit(CAMP_DIR + "path03", "out");
    reset_shire_room();

    furniture();
    chairs();
    table();
}

void reset_shire_room()
{
	make_orcs();
}

void
make_orcs()
{
  int i;
  int max_orcs;
  object orcleader;
   FIXEUID;


  max_orcs=random(5);

  if(!leader)
  {
     orcleader = clone_object(ORCMAKER_DIR + "orcmaker");
     orcleader->set_long("This is an monstrously large orc guard.\n");
     orcleader->add_name("leader");
     orcleader->set_power(55 + random(21));
     orcleader->set_type(GUARD);
     orcleader->move(TO);
  }
  if(!sizeof(orcs))
    orcs = allocate(max_orcs);
    for(i = 0; i < max_orcs; i++)
    if(!orcs[i])
    {
/*
      orcs[i] = clone_object(BREE_DIR + "npc/path_orc");
      leader->team_join(orcs[i]);
      orcs[i]->move(TO);

      tell_room(TO,capitalize(LANG_ADDART(orcs[i]->query_nonmet_name()))+
                   " suddenly jumps from behind the bushes!\n");
*/
     orcs[i] = clone_object(ORCMAKER_DIR + "orcmaker");
     orcs[i]->set_long("This orc guard is eyeing you warily.\n");
     orcs[i]->add_name("guard1");
     orcs[i]->set_power(30 + random(16));
     orcs[i]->set_type(GUARD);
     orcs[i]->move(TO);
     orcleader->team_join(orcs[i]);

    }  
    else
      if(orcs[i]->query_leader() != leader)
        leader->team_join(orcs[i]);
}