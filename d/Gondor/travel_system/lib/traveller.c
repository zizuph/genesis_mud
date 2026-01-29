/*
 * /d/Gondor/travel_system/lib/traveller.c
 *
 * Functions for an npc to be able to travel through
 * the domain.
 */
#pragma strict_types

#include "/d/Gondor/defs.h"
#include "../sys/defs.h"
#include DEFS_LOCATIONS

int travel_destination = 0;
string travel_destination_command = "";
int travel_alarm = 0;
float travel_speed = 2.0;

public void
travel_next_step()
{
  mixed cmd = travel_destination;

  while (!stringp(cmd))
  {
    cmd = ENV(TO)->query_direction(cmd);

    if (cmd == LOCATION_REACHED)
    {
      command(travel_destination_command);
      
      return;
    }

    if (cmd == 0)
    {
      // Let the world know I can't reach my destination!

      return;
    }
  }

  command(cmd);

  travel_alarm = set_alarm(travel_speed, 0.0, &travel_next_step());
}

public varargs int
travel(int location, string cmd = "")
{
  travel_destination = location;
  travel_destination_command = cmd;

  if (!travel_alarm || (get_alarm(travel_alarm) == 0))
    travel_alarm = set_alarm(travel_speed, 0.0, &travel_next_step());

  return 1;
}

public int
set_travel_speed(float speed)
{
  travel_speed = speed;

  return 1;
}
public float
query_travel_speed()
{
  return travel_speed;
}
