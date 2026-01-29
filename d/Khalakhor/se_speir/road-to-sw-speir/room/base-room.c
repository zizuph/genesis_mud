/*
 * Common functions for rooms in the way linking SE Speir and SW Speir
 * Tapakah, 09/2021
 */

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <filepath.h>
#include "../defs.h"

int room_type;
int *coords;

int *
query_local_coords ()
{
  string prefix;
  int x ,y;

  int match = sscanf(FILE_NAME(MASTER),
                     "%s-%d-%d.c",
                     prefix, x, y);
  if (match == 3)
    return ({x, y});

  return ({0, 0});
}

int *
query_global_coords ()

{
  return ({ -2, 0 });
  
}

void
set_room_type () {
  if (! coords)
    coords = query_local_coords();
  
  if (coords[1] == 7)
    room_type = LEVEL_CAPTAIN;
  else if (coords[1] == 6 && coords[0] == 17)
    room_type = LEVEL_LIEUTENANT;
  else if (coords[1] == 6 && coords[0] == 16)
    room_type = LEVEL_SERGEANT;
  else
    room_type = LEVEL_SOLDIER;
}
