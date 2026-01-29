/*
 * SaMorgan utility functions
 *
 * Tapakah, 04/2021
 */

#pragma strict_types

#include "defs.h"

object *workers;

public void
reset_worker_team (int team_size)
{
  int i;

  if (! workers)
    workers = allocate(team_size);
  for (i = 0; i < team_size; i++)
    if (! objectp(workers[i])) {
      workers[i] = clone_object(NPC + "worker");
      workers[i]->set_team_name("worker_team");
      i ? workers[i]->set_team_follower() : workers[i]->set_team_leader();
      workers[i]->set_autoassist();
      workers[i]->arm_me();
      workers[i]->move(TO);
      tell_room(this_object(),
                capitalize(workers[i]->short()) + " arrives.\n");
    }

}


