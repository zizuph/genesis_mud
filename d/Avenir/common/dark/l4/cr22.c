// -*-C++-*-
// file name: ~Avenir/common/dark/l4/cr22.c
// creator(s):  Boriska
// last update: Jan 23 1995
//              Zizuph Aug 2022 - syntax and grammer fixes while 
//                looking for quest bug. 
// purpose:     Main room of the magic_square quest
// note:
// bug(s):
// to-do:     


inherit "/d/Avenir/common/dark/l4/cr.c";

#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/magic_square.h"

#define X_MAX 4
// maximal coordinate of room in square cavern. 4 makes it 5x5
// used when computing the placement of 3x3 magic square
// in the center.

#define DEBUG

#ifdef DEBUG
#define D(x) (find_player("boriska")->catch_msg("SQUARE debug: " + (x)))
#else
#define D(x) ;
#endif

int check_square(object tp);

mixed *map = ({
    ({0,0,0,0,0}),
    ({0,0,0,0,0}),
    ({0,0,0,0,0}),
    ({0,0,0,0,0}),
    ({0,0,0,0,0}),
  });


static int *row = allocate(X_MAX);  // sum of stones in each row
static int *col = allocate(X_MAX);  // sum of stones in each column
static int diag1, diag2;           // ascending and descending diagonals.

static object to = this_object();

static int pillar_raised = 0;      // keeps track of pillar's state in the center

// corner coordinates of the magic square
int sq_min = X_MAX/2 - (SIZE-1)/2;
int sq_max = X_MAX/2 + (SIZE-1)/2;

void
create_room ()
{
  ::create_room();
  set_long (
    "This is a vast underground cavern. Your steps are echoing\n" +
    "from the walls and high ceiling which you cannot see in pitch\n" +
    "darkness.@@long_extra@@");
  add_item ("dais","@@dais_desc");
  add_item ("pillar", "@@pillar_desc");
}

string
long_extra()
{
  string str ="";

  if (this_player()->query_skill(SS_AWARENESS) > 20 &&
      ARTIFACT_ROOM->query_artifact() )
    str+= " You notice faint light emitting from above.\n";
  else
    str+="\n";

  if (pillar_raised)
    str+="There's tall pillar here, going up to the ceiling.\n";
  else
    str+="There is a low dais here.\n";
  return str;
}
      
string
dais_desc()
{
  return pillar_raised ? "You find no dais.\n" :
	    "There is a piece of stone in the center of the room that is "+
        "a step up from the rest of the floor. You could probably "+
        "stand on it if you wanted to.\n" ;
}

string
pillar_desc()
{
  return pillar_raised ? "A stone pillar rising up to the cavern ceiling.\n" :
    "You find no pillar.\n";
}


int
do_stand (string str)
{
  object tp = this_player();
  int i,j;
  
  notify_fail ("Stand where?\n");
  if (!str || !CAN_SEE_IN_ROOM(tp) || pillar_raised ||
      (str != "dais" && str != "on dais" && 
       str != "up on dais" && str != "upon dais"))
    return 0;

  if (!tp->query_prop (SQUARE_SUM)) // curious player standing on dais.
    {
      tp->catch_msg ("Standing on the dais you can see more of the cavern.\n" +
	    "To your disappointment nothing happens, so you decide to step down.\n");
      say (QCTNAME(tp) + " stood on the dais and then stepped back down.\n");
      return 1;
    }

  // Player standing on dais got magic square quest before. Check the square.
    if (check_square(tp))
    {
      D ("\nSquare OK.\n");
      D ("Removing stones from rooms...\n");
      for ( i = sq_min; i <= sq_max; i++)
	for (j = sq_min; j <= sq_max; j++ )
	  {
	    tell_room (environment(map[i][j]),
	     "The stones placed around the dais magically disappear!\n");
      	    map[i][j]->remove_object();
	  }
      D ("Stones removed.\n");
      
      say("As " + QNAME(tp) +" stands on the dais, it starts to rise upward, "+
	  "forming a pillar that carries "+tp->query_objective() + " toward the "+
      "ceiling!\n");
      
      tp->catch_msg ("You hear faint click as you stand on the dais.\n");
      tp->move(L4 + "pillar");
      pillar_raised = 1;
    }
    else { 
      D ("\nBad square.\n");
      // what to do when stones placed wrong ? Probably try a new combo.
      tp->catch_msg ("You feel tremendous tension growing in the cavern, "+
         "a sense of expectation awaiting fulfillment.\n"+
	     "Nothing happens though, so you step down from the dais.\n");
      say (QCTNAME(tp) + " steps onto the dais and then back down again.\n");
    }
  return 1;
}

private int
check_square(object tp)
{
  int i,j;
  int foo;
  int *seq = ({});
  object room;
  object *inv;
  
  D("initializing square\n");
// check magic square
  for ( i = sq_min; i <= sq_max; i++)
    {
      for (j = sq_min; j <= sq_max; j++ )
	{
	  D ( QUEST_ROOM + i + j + "\n");
	  room = find_object(QUEST_ROOM + i + j);

	  if (!room)  // player have not even visited this room
	    return 0;
	  D ("room OK\n");
	  inv = filter (all_inventory (room), "is_right_stone", to, tp);

	  if (!sizeof(inv))    // no stones at all there.
	    return 0;
	  // check for all numbers to be different
	  if (member_array(inv[0]->num_heap(), seq) < 0)
	    seq += ({inv[0]->num_heap()});
	  else
	    return 0;
	  
	  map[i][j] = inv[0]; 
	}
      row[i] = 0;
      col[i] = 0;
    }
  diag1 = 0;
  diag2 = 0;
  
  D ("checking square\n");
  // compute rows, columns and diagonals sums
  for ( i = sq_min; i <= sq_max; i++)
    for (j = sq_min; j <= sq_max; j++ )
      {
	D ( QUEST_ROOM + i + j + "\n");

	foo = map[i][j]->num_heap();

	row[i] += foo;
	col[j] += foo;
	if ( i == j )
	  diag1 += foo;
	if ( i + j == SIZE + 1 )
	  diag2 += foo;
      }
  
  D ("row: " + row[1] + " " + row[2] + " " + row[3] + "\n");
  D ("col: " + col[1] + " " + col[2] + " " + col[3] + "\n");
  D ("diag1: " + diag1 + "\n");
  D ("diag2: " + diag2 + "\n" );
  
  // now compare with correct value stored as prop in player
  foo = tp->query_prop (SQUARE_SUM);
  
  for ( i = sq_min; i <= sq_max; i++)
    if ( foo != row[i] || foo != col[i] )
      return 0;
  
  if (diag1 != foo || diag2 != foo)
    return 0;
  
  return 1;
}

// identificates the stones placed by this player only
private int
is_right_stone (object ob, object tp)
{
  return ob->query_prop(QUEST_ID) == tp->query_real_name();
}

// called from pillar room to reflect its state in room long.
void
set_pillar_raised(int state) { pillar_raised = state; }

void init ()
{
  ::init();
  add_action (do_stand, "stand");
  // Adding some more syntax options - Zizuph Aug 2022
  add_action (do_stand, "step");
  add_action (do_stand, "balance");
  add_action (do_stand, "walk");
  
  
}