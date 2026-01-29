inherit "/std/room.c";

#include "cave2.h"
#include "cube.h"

int i,j,k;	/* coordinates */
int occupied;	/* Is there a player in the maze? */
int ready;	/* Is maze ready for player? */
object player;
int *ps = ({0,0,0});
int *pe = ({0,0,0});

create_room()
{
  i = j = k = 0;
  set_short("Inside the cube");
  set_long("You're inside a cube.\n");
  make_path();
  make_exits();
}

void
remove_exits()
{
  int l;
  string *exits;
  exits = query_exit();
  for(l = 1; l < sizeof(exits); l += 3)
    remove_exit(exits[l]);
}

void
make_exits()
{
  int l;
  for(l = 0; l < MAX_EXITS; l++)
    if(vertex[i][j][k][l] > NAV)
      add_exit(CAVE2 + "cube", direction[l], "@@moving|" + direction[l] + "@@");
}

int
moving(string direction)
{
  switch(direction)
  {
    case "north":          j++;      break;
    case "northeast": i++; j++;      break;
    case "east":      i++;           break;
    case "southeast": i++; j--;      break;
    case "south":          j--;      break;
    case "southwest": i--; j--;      break;
    case "west":      i--;           break;
    case "northwest": i--; j++;      break;
    case "up":                  k++; break;
    case "down":                k--; break;
    default:                           return 1;
  }
  remove_exits();
  make_exits();
  return 0;
}

enter_inv(object obj, object from)
{
  if(from != TO)
    if(living(obj))
      if(occupied)
      {
        tell_object(obj, "You can't enter the cube now. It looks too " +
          "insecure for more than one player.\n");
        obj->move(from);
      }
      else
      {
        player = obj;
        occupied = 1;
      }
    else
    {
      tell_object(from, "Something prevents you from dropping anything.\n");
      obj->move(from);
    }
}

leave_inv(object obj, object to)
{
  if(obj == player)
    occupied = 0;
}

int
make_path()
{
  int i, j, k, l;
  int edges;
  int index;
  int direction;
  int swap;

  /* fix start-point */
  i = ps[0] = random(L);
  j = ps[1] = random(L);
  k = ps[2] = 0;

  for(edges = 0; ((COUNT > 0) && (edges < MAX_EDGES)); edges++)
  {
    index = random(COUNT);

    for(l = 0; index >= 0; l++)
      if(vertex[i][j][k][l] == AV)
        index--;
    direction = l - 1;
        
    vertex[i][j][k][direction] = STABLE;
    COUNT--;
    switch(direction)
    {
      case  N:      j++;      break;
      case NE: i++; j++;      break;
      case  E: i++;           break;
      case SE: i++; j--;      break;
      case  S:      j--;      break;
      case SW: i--; j--;      break;
      case  W: i--;           break;
      case NW: i--; j++;      break;
      case  U:           k++; break;
      case  D:           k--; break;
    }
    direction = (direction + (MAX_EXITS/2))%MAX_EXITS;
    vertex[i][j][k][direction] = STABLE;
    COUNT--;
  }
  pe[0] = i;
  pe[1] = j;
  pe[2] = k;
  if(edges < MIN_EDGES)
    TO->destruct();
  else
    ready = 1;
}
