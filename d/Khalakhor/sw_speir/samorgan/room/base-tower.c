/*
 * Guard tower in Sa Morgan
 * Pretty mundane stuff
 * Tapakah, 04/2021
 */

#pragma no_clone
#pragma strict_types

#include <stdproperties.h>
#include <terrain.h>

#include "../defs.h"

inherit SM_ROOM_BASE;

object *team;
mapping *people_ground = ({
  (["file": SM_SERGEANT, "count": 1,
    "arrival": "The sergeant staggers tiredly into the room.\n"]),
  (["file": SM_COURIER, "count": 1,
    "arrival": "The courier walks into the room and sits down, relaxed.\n"]),
});
mapping *people_up = ({
  (["file": SM_GUARD, "count": 3,
    "arrival": "The guard marches into the room.\n"]),
});
mapping *people;
string team_name;

public int
member_ok (object ob)
{
  return ob ? 1 : 0;
}

public void
add_team (object warrior)
{
  team += ({warrior});
  team = filter(team, member_ok);
  warrior->set_team_name(team_name);
  warrior->set_autoassist();
  
  tell_room(TO, warrior["arrival"]);
  sizeof(team) > 1 ? warrior->set_team_follower() : warrior->set_team_leader();
}

public void
configure_samorgan_guard_tower (string location, mixed *exits)
{
  set_terrain(TERRAIN_RESIDENCE);
  add_prop(ROOM_I_INSIDE, 1);

  foreach (string *exit : exits)
    add_exit(exit[0], exit[1]);
  people    = location == "up" ? people_up : people_ground;
  team_name = location == "up" ? "tower_up_team" : "tower_ground_team";
  foreach (mapping person: people) {
    add_npc(person["file"], person["count"]);
  }
}
