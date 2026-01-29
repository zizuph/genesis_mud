/*
 * Cherek Standard Room.
 *
 * Coded by Belzaroth.
 */
#pragma strict_types
#pragma save_binary

#include "../sys/defs.h"
#include DEFS_LOCATIONS

inherit "/std/room";

public void
create_example_room()
{
}

public nomask void
create_room()
{
  create_example_room();
}


/*
 * Location functionality.
 *
 * Makes it possible for us (and, especially, NPCs) to
 * know where another room is relative to this one.
 */
int this_location;
int this_division, this_area, this_subarea, this_room;
mapping known_locations = ([]);

public int
set_this_location(int location)
{
  if (DIVISION_PART(location) != 0)
    this_division = DIVISION_PART(location);
  if (AREA_PART(location) != 0)
    this_area = AREA_PART(location);
  this_subarea = SUBAREA_PART(location);
  this_room = ROOM_PART(location);

  this_location = this_division | this_area | this_subarea | this_room;
}
public int
query_this_location()
{
  return this_location;
}

public int
add_known_location(int location, mixed direction)
{
  known_locations[location] = direction;
}

public mixed
try_directions(int *directions)
{
  int count = -1;
  mixed direction;

  while (direction == 0 && ++count < sizeof(directions))
    direction = known_locations[directions[count]];

  return direction;
}

public string
query_direction(int location)
{
  mixed direction;
  int division, area, subarea, room;

  division = DIVISION_PART(location);
  if (division != this_division && division != 0)
  {
    direction = try_directions(({ division, DIRECTION_OTHER_DIVISIONS, }));
  }
  else
  {
    area = AREA_PART(location);
    if (area != this_area && area != 0)
    {
      direction = try_directions(({ area, area | this_division,
				    DIRECTION_OTHER_AREAS, }));
    }
    else
    {
      subarea = SUBAREA_PART(location);
      if (subarea != this_subarea && subarea != 0)
      {
	direction = try_directions(({ subarea, subarea | this_area,
				      subarea | this_area | this_division,
				      DIRECTION_OTHER_SUBAREAS, }));
      }
      else
      {
	room = ROOM_PART(location);

	if (room != this_room && room != 0)
	{
	  direction = try_directions(({ room, room | this_subarea,
					room | this_subarea | this_area,
					room | this_subarea |
					this_area | this_division,
					DIRECTION_OTHER_ROOMS, }));
	}
	else
	{
	  direction = LOCATION_REACHED;
	}
      }
    } 
  }

  if (direction == 0)
    direction = known_locations[DIRECTION_DEFAULT];

  return direction;
}
