/*	this is a room of the volcano

	coder(s):   Deinonychus

	history:	DD.MM.YY	what done	who did
			13.10.93	created 	Deinonychus

	purpose:	none
	exits:		none

	objects:	none
	npcs:		none

	quests: 	none
	special:	none

	to do:		none
	bug:		none known
*/

inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include "cave2.h"
#include "cube.h"

int i,j,k;	/* coordinates */
int occupied;	/* Is there a player in the maze? */
int ready;	/* Is maze ready for player? */
int questing;	/* Has the player started the quest or not */
int to_walk;	/* How many connections are not walked while questing */
object player;	/* The player itself */
int *ps = ({0,0,0});	/* Point where to start the maze */
int *pe = ({0,0,0});	/* Point where to end the maze */
mixed *vertex;	/* array holding the connections */
mixed *line;	/* used for drawing. Represents line of vertex */

/*
 * Function name: create_room
 * Description:   creats the roome
 * Arguments:	  none
 * Returns:	  nothing
 */
create_room()
{
  int x, y, z, d;
  
  set_short("In a strange construction");
  set_long(BS("Now this really is a strange thing. You are in a " +
    "construction of some small boards to stand on and lots of ropes. " +
    "Some of the ropes seem to support the whole construction, some " +
    "seem to be useless at all and some can be used to climb from one " +
    "board to the other. You don't trust in this construction at all. " +
    "There's a cord hanging down.\n"));
  add_item("cord", "It looks perfect to pull on it.\n");
  add_prop(ROOM_I_LIGHT, 1);
  vertex = allocate(L * L * L * (MAX_EXITS + 1));
  line = allocate(L);
  for(x = 0; x < L; x++)
    line[x] = allocate(MAX_EXITS + 1);
  make_path();	/* Try to create a maze with enough connections */
}

/*
 * Function name: remove_exits
 * Description:   removes all existing exits
 * Arguments:	  none
 * Returns:	  nothing
 */
void
remove_exits()
{
  int l;		/* index */
  string *exits;	/* holds result of query_exit */
  exits = query_exit(); /* store existing exits in 'exits' */
  for(l = 1; l < sizeof(exits); l += 3)
    remove_exit(exits[l]);	/* remove every existing exit */
}

/*
 * Function name: make_exits
 * Description:   creates all exits
 * Arguments:	  none
 * Returns:	  nothing
 */
void
make_exits()
{
  int l;	/* index */
  for(l = 0; l < MAX_EXITS; l++) /* N, NE, E, SE, U, S, SW, W, NW, D */
    if(vertex[i][j][k][l] > NAV) /* There's an exit in direction l */
      add_exit(CAVE2 + "cube", dirstring[l], "@@moving|" + dirstring[l] + "@@");
  if((ps[0] == i) && (ps[1] == j) && (ps[2] == k))
    add_exit(CAVE2 + "cave2", "down", 0);	/*Point where the maze is entered */
}

/*
 * Function name: moving
 * Description:   adjusts indices and room
 * Arguments:	  direction where the player moves
 * Returns:	  0/1 (always 1 :)
 */
int
moving(string direction)
{
  if(questing)	/* check if connection is stable */
    if(vertex[i][j][k][dirint[direction]] == STABLE)	/* mark connection instable */
    {
      vertex[i][j][k][dirint[direction]] = INSTABLE;
      to_walk--;
    }
    else	/* The player will fall down */
    {
      tell_object(player, BS("The rope you wanted to climb to the other " +
	"board breaks and you fall down to the bottom of the cave.\n"));
      tell_room(CAVE2 + "cave2", QCNAME(player) + " falls down " +
        "from the construction above you.\n");
      player->move_living("M", CAVE2 + "cave2", 1);
      return 1;
    }

  remove_exits();	/* remove old exits */

  switch(direction)	/* in-/decrement right indices */
  {
    case "north":	   j++;      break;
    case "northeast": i++; j++;      break;
    case "east":      i++;	     break;
    case "southeast": i++; j--;      break;
    case "south":	   j--;      break;
    case "southwest": i--; j--;      break;
    case "west":      i--;	     break;
    case "northwest": i--; j++;      break;
    case "up":			k++; break;
    case "down":		k--; break;
    default:			     return 1;	/* dunno whatfor this is */
  }

  if(questing)	/* mark conter-direction instable */
    vertex[i][j][k][conter_dir[dirint[direction]]] = INSTABLE;

  make_exits(); 	/* create new exits */
  player->move_living("M",TO,1);	/* player gets desc of new room */

  if(to_walk == 0)	/* the quest if done */
  {
    give_reward();
    tell_object(player, "You fall down.\n");
    tell_room(CAVE2 + "cave2", QCNAME(player) + " falls down " +
      "from the construction above you.\n");
    tell_room(CAVE2 + "cave2", QCNAME(player) + " falls down " +
      "from the construction above you.\n");
    player->move_living("M", CAVE2 + "cave2", 1);
  }

  return 1;
}

/*
 * Function name: give_reward
 * Description:   give the reward for the quest
 * Arguments:	  none
 * Returns:	  nothing
 */
void
give_reward()
{
  if(player->test_bit(DOMAIN, BITFIELD, BITNUM))
  {
    tell_object(player, BS("A misterious voice whispers to you: " +
      "\"remember the word '.....'\".\n"));
    player->add_exp(SMALL_REWARD);
    tell_object(player, "You feel a little more experienced.\n");
  }
  else
  {
    tell_object(player, BS("A misterious voice whispers to you: " +
      "\"remember the word '.....'\n\""));
    player->add_exp(REWARD);
    tell_object(player, BS("You feel a great experience running " +
      "through your body.\n"));
    player->set_bit(BITFIELD, BITNUM);
  }
}

/*
 * Function name: init
 * Description:   add commands to the player
 * Arguments:	  none
 * Returns:	  nothing
 */
init()
{
  ::init();
  add_action("do_pull", "pull");
}

/*
 * Function name: enter_inv
 * Description:   check if somethings's dropped or someone wants to enter
 * Arguments:	  what enters, whereform does it enter
 * Returns:	  0/1
 */
enter_inv(object obj, object from)
{
  if(ready && (from != TO))	/* No move inside maze */
    if(living(obj))		/* living tries to enter maze */
      if(occupied)		/* There's a player in the maze */
      {
	tell_object(obj, "You can't enter the construction now. It " +
	  "looks too insecure for more than one player.\n");
	obj->move(CAVE2 + "cave2");
      }
      else		/* The maze is free */
      {
	player = obj;
	occupied = 1;
      }
    else
    {
      tell_object(from, "It falls down to the bottom of the cave.\n");
      obj->move(CAVE2 + "cave2");
    }
  else
  {
    tell_object(obj, BS("At the moment the whole construction's moving " +
      "around and looks too insecure to enter.\n"));
    obj->move(from);
  }

}

/*
 * Function name: leave_inv
 * Description:   set maze free if player leaves it.
 * Arguments:	  what leaves the room, whereto
 * Returns:	  0/1
 */
leave_inv(object obj, object to)
{
  if((obj == player) && (to != TO))
  /* the player leaves the maze */
  {
      tell_object(player, BS("As you leave the construction everything " +
	"trembles and moves around. What a mess. You changed the " +
	"whole construction.\n"));
      player = NULL;	/* reset player */
      occupied = 0;	/* maze is free */
      ready = 0;	/* maze no longer ready */
      make_path();	/* generate a new maze */
  }
  ::leave_inv(obj, to);
}

/*
 * Function name: make_path
 * Description:   tries to make a maze with enough connections
 * Arguments:	  none
 * Returns:	  0/1
 */
void
make_path()
{
  int x, y, z, l;	/* indices for array holding holding connections */
  int edges;		/* counter for connections */
  int index;		/* holds free connection to choose */
  int direction;	/* direction of connection */

  init_vertex();	/* init vertex */
  /* fix start-point */
  x = ps[0] = random(L);
  y = ps[1] = random(L);
  z = ps[2] = 0;	/* startpoint must be in ground-level */

  /* loop until MAX_EDGES connection or no more free connection 	*/
  /* available from actual room (COUNT returns # available connections) */
  for(edges = 0; ((COUNT > 0) && (edges < MAX_EDGES)); edges++)
  {
    index = random(COUNT);	/* generate 0 < index < COUNT */

    for(l = 0; index >= 0; l++) 	/* loop over connections */
      if(vertex[x][y][z][l] == AV)	/* free connection, dec index */
	index--;
    direction = l - 1;

    vertex[x][y][z][direction] = STABLE;	/* make connection stable */
    COUNT--;	/* decrement * of available free connections */
    switch(direction)	/* in-/decrement right indices */
    {
      case  N:	    y++;      break;
      case NE: x++; y++;      break;
      case  E: x++;	      break;
      case SE: x++; y--;      break;
      case  S:	    y--;      break;
      case SW: x--; y--;      break;
      case  W: x--;	      break;
      case NW: x--; y++;      break;
      case  U:		 z++; break;
      case  D:		 z--; break;
    }
    /* calculate conter-direction */
    direction = conter_dir[direction];
    /* make connection back and set it stable */
    vertex[x][y][z][direction] = STABLE;
    COUNT--;	/* decrement # of available free connections of to-room */
  }
  if(edges < MIN_EDGES) /* Not enough connections created */
    call_out("make_path", 1);	/* recalculate a new path */
  else
  {
    /* set endpoint */
    pe[0] = x;
    pe[1] = y;
    pe[2] = z;
    /* set startpoint where the player enters the maze */
    i = ps[0];
    j = ps[1];
    k = ps[2];
    remove_exits();	/* remove old exits */
    make_exits();	/* make exits of this point */
    ready = 1;		/* set maze ready */
    questing = 0;	/* the player can first explore the maze */
    to_walk = edges;	/* connections that should be walked for the quest */
  }
}

/*
 * Function name: init_vertex
 * Description:   initialize the array holding the connections
 * Arguments:	  none
 * Returns:	  none
 */
void init_vertex()
{
  vertex =
    ({
      ({
	({
	  ({ AV,  AV,  AV, NAV,  AV, NAV, NAV, NAV, NAV, NAV,  4, }),
	  ({ AV,  AV,  AV, NAV,  AV, NAV, NAV, NAV, NAV,  AV,  5, }),
	  ({ AV,  AV,  AV, NAV, NAV, NAV, NAV, NAV, NAV,  AV,  4, }),
	}),
	({
	  ({ AV,  AV,  AV,  AV,  AV,  AV, NAV, NAV, NAV, NAV,  6, }),
	  ({ AV,  AV,  AV,  AV,  AV,  AV, NAV, NAV, NAV,  AV,  7, }),
	  ({ AV,  AV,  AV,  AV, NAV,  AV, NAV, NAV, NAV,  AV,  6, }),
	}),
	({
	  ({NAV, NAV,  AV,  AV,  AV,  AV, NAV, NAV, NAV, NAV,  4, }),
	  ({NAV, NAV,  AV,  AV,  AV,  AV, NAV, NAV, NAV,  AV,  5, }),
	  ({NAV, NAV,  AV,  AV, NAV,  AV, NAV, NAV, NAV,  AV,  4, }),
	}),
      }),
      ({
	({
	  ({ AV,  AV,  AV, NAV,  AV, NAV, NAV,	AV,  AV, NAV,  6, }),
	  ({ AV,  AV,  AV, NAV,  AV, NAV, NAV,	AV,  AV,  AV,  7, }),
	  ({ AV,  AV,  AV, NAV, NAV, NAV, NAV,	AV,  AV,  AV,  6, }),
	}),
	({
	  ({ AV,  AV,  AV,  AV,  AV,  AV,  AV,	AV,  AV, NAV,  9, }),
	  ({ AV,  AV,  AV,  AV,  AV,  AV,  AV,	AV,  AV,  AV, 10, }),
	  ({ AV,  AV,  AV,  AV, NAV,  AV,  AV,	AV,  AV,  AV,  9, }),
	}),
	({
	  ({NAV, NAV,  AV,  AV,  AV,  AV,  AV,	AV, NAV, NAV,  6, }),
	  ({NAV, NAV,  AV,  AV,  AV,  AV,  AV,	AV, NAV,  AV,  7, }),
	  ({NAV, NAV,  AV,  AV, NAV,  AV,  AV,	AV, NAV,  AV,  6, }),
	}),
      }),
      ({
	({
	  ({ AV, NAV, NAV, NAV,  AV, NAV, NAV,	AV,  AV, NAV,  4, }),
	  ({ AV, NAV, NAV, NAV,  AV, NAV, NAV,	AV,  AV,  AV,  5, }),
	  ({ AV, NAV, NAV, NAV, NAV, NAV, NAV,	AV,  AV,  AV,  4, }),
	}),
	({
	  ({ AV, NAV, NAV, NAV,  AV,  AV,  AV,	AV,  AV, NAV,  6, }),
	  ({ AV, NAV, NAV, NAV,  AV,  AV,  AV,	AV,  AV,  AV,  7, }),
	  ({ AV, NAV, NAV, NAV, NAV,  AV,  AV,	AV,  AV,  AV,  6, }),
	}),
	({
	  ({NAV, NAV, NAV, NAV,  AV,  AV,  AV,	AV, NAV, NAV,  4, }),
	  ({NAV, NAV, NAV, NAV,  AV,  AV,  AV,	AV, NAV,  AV,  5, }),
	  ({NAV, NAV, NAV, NAV, NAV,  AV,  AV,	AV, NAV,  AV,  4, }),
	}),
      }),
    });
}

/*
 * Function name: none
 * Description:   none
 * Arguments:	  none
 * Returns:	  none
 */
int
do_pull(string what)
{
  NF("pull what?\n");
  if(what != "cord")
    return 0;
  else
    if(questing)	/* The player's already on questing */
      write("Nothing happens.\n");
    else	/* The player wants to start the quest */
    {
      write(BS("The eintire construction seems to come alive. " +
	"Everywhere there are sounds of slowly tearing ropes and " +
	"creaking boards. You tremble with fear.\n") +
	BS("Go ahead, make your day!\n"));
      questing = 1;
    }
  return 1;
}

/*
 * Function name: add_my_desc
 * Description:   Additional descriptions are fobidden in this room
 * Arguments:	  string to add, object responsible for description
 * Returns:	  none
 */
add_my_desc(string str, object cobj)
{
  return 1;
}

/*
 * Function name: none
 * Description:   none
 * Arguments:	  none
 * Returns:	  none
 */
void
wizinfo()
{
  int x, y, z, n;

  write("startpoint: (" + ps[0] + ", " + ps[1] + ", " + ps[2] + ")\n");
  write("endpoint: (" + pe[0] + ", " + pe[1] + ", " + pe[2] + ")\n");
  write("actual coordinates: (" + i + ", " + j + ", " + k + ")\n");
  for(y = (L - 1); y >= 0; y--)
    for(n = 0; n < 3; n++)
    {
      for(z = 0; z < L; z++)
      {
	for(x = 0; x < L; x++)
	  line[x] = vertex[x][y][z];
	draw_part(n);
      }
      write("\n");
    }
}

void
draw_part(int n)
{
  switch(n)
  {
    case 0: draw_0(); break;
    case 1: draw_1(); break;
    case 2: draw_2(); break;
  }
}

void
draw_0()
{
  int i;

  for(i = 0; i < L; i++)
  {
    if((line[i][U] > NAV) && (line[i][D] > NAV )) write("X");
    else if((line[i][U] > NAV) && !(line[i][D] > NAV)) write("^");
    else if(!(line[i][U] > NAV) && (line[i][D] > NAV)) write("v");
    else write("O");
    if((line[i][E] > NAV)) write("--");
    else write("  ");
  }
}

void
draw_1()
{
  int i;

  for(i = 0; i < (L - 1); i++)
  {
    if(line[i][S] > NAV) write("|");
    else write(" ");
    if(line[i][SE] > NAV) write("\\");
    else write(" ");
    if(line[i+1][SW] > NAV) write("/");
    else write(" ");
  }
  i = L-1;
  if(line[i][S] > NAV) write("|  ");
  else write("   ");
}

void
draw_2()
{
  int i;

  for(i = 0; i < (L - 1); i++)
  {
    if(line[i][S] > NAV) write("|");
    else write(" ");
    if(line[i+1][SW] > NAV) write("/");
    else write(" ");
    if(line[i][SE] > NAV) write("\\");
    else write(" ");
  }
  i = L-1;
  if(line[i][S] > NAV) write("|  ");
  else write("   ");
}

