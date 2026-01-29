/*
 * Guard tower in Sa Morgan
 * Pretty mundane stuff
 * Tapakah, 04/2021
 */

#pragma strict_types

#include <stdproperties.h>
#include <terrain.h>
#include "../defs.h"

inherit KSTDROOM;

object sergeant, courier;
mapping *people_here = ({
  (["file": SM_SERGEANT,
    "arrival": "The sergeant staggers tiredly into the room.\n"]),
  (["file": SM_COURIER,
    "arrival": "The courier walks into the room and sits down, relaxed.\n"]),
});

public int *
query_local_coords()
{
  return ({4, 0});
}

public int *
query_global_coords()
{
  return SAMORGAN_COORDS;
}

public void
set_room_npcs (string team_name)
{
  object ob_person;
  int p = 0;
  
  foreach (mapping person: people_here) {
    if (! HERE(person["file"])) {
        ob_person = clone_object(person["file"]);
        ob_person->arm_me();
        ob_person->move(TO);
        ob_person->set_team_name(team_name);
        ob_person->set_autoassist();
        p ? ob_person->set_team_follower() : ob_person->set_team_leader();
        tell_room(TO, person["arrival"]);
    }
    p++;
  }
}

public void
reset_room ()
{
  ::reset_room();
  set_room_npcs("tower_base_team");
}

public void
create_khalakhor_room ()
{
  set_terrain(TERRAIN_RESIDENCE);
  add_prop(ROOM_I_INSIDE, 1);

  set_short("Guard tower, base level");
  set_long("This is the base level of Sa Morgan's guard tower. The room is "+
           "pretty spartan, with a table and a couple of benches in it. "+
           "Stairs lead up to the landing where the real watch happens. "+
           "You can see the village of Sa Morgan bustling outside the door. ");
  add_exit("southeast", "vil0201");
  add_exit("up", "tower-nw-up");
  
  set_alarm(0.5, 0.0, reset_room);  
}
