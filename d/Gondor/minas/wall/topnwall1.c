inherit "/d/Gondor/common/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

object guard;

void add_guard();

void
create_room()
{
  set_short("Upon the battlements of the First Wall");
  set_long("@@describe");
  add_exit(MINAS_DIR+"wall/ninwall1","down",0,0);
  add_exit(MINAS_DIR+"wall/battlement1","south",0,0);
  add_item(({"gate","gates","Gate","first gate","First Gate"}),"@@checkgates");
  add_item("fields","@@fielddesc");
  add_prop(ROOM_I_INSIDE, 0);
  add_guard();
}

string
fielddesc()
{
  return "The Fields of Pelennor stretch out to the east, surrounded by the\n"+
    "Rammas Echor, the great outer wall built to protect the city and its\n"+
      "farmlands from the prepending onslaught.\n";
}

string
checkgates()
{
  string time;
  time = tod();
  if (time == "evening" || time == "night")
      return "The Great Gates of Minas Tirith are closed now in the "+time+".\n"+
	"Only in the daytime may people enter and leave the City freely.\n";  
  else return "The Great Gates of Minas Tirith are opened now in the "+time+".\n"+
    "The Gate is kept closed in the nighttime though, to prevent spies and\n"+
      "agents of the Enemy entering the City.\n";
}

string
describe()
{
  string time,longstr;
  time = tod();
  longstr = "You are upon the battlements of the First Wall of Minas Tirith. ";
  if (time == "night") {
    longstr = "In the darkness of the night you don't see much, but the city "+
      "lies behind you to the west, and a few lights can be seen in the "+
      "windows. The plains that you know exist to the east lies in darkness. "+
      "Further south of here the First Gate leads through the wall below. A "+
      "stairway goes down into the wall here. ";
    }
  if (time == "morning"|| time=="early morning") {
    longstr = "The rising sun in the east casts long shadows in the City "+
      "behind you to the west. Stretching out before you to the east are "+
      "the Pelennor fields, the farmlands outside Minas Tirith. Further "+
      "south the First Gate leads through the wall you are on. A stairway "+
	"leads down into the wall here. ";
  }
  if (time == "noon")
    {
      longstr = "The sun is at its peak on the sky above Gondor, as you "+
	"stand here looking out across the Fields of Pelennor to the east. "+
	"The First Gate leads through the wall further south of here, and "+
	  "a set of stairs lead down in the wall here. ";
    }
  if (time == "afternoon" || time == "evening")
    {
      longstr = "The "+time+" sun is disappearing behind the looming Mount "+
	"Mindolluin to the west, putting the City in shadow. To the east "+
	"are the Pelennor fields, while the City of Minas Tirith is on the "+
	"other side of the protecting First Wall. A stairway leads down "+
	"inside the wall here, while further along the wall to the south "+
	  "you can see the battlements above the First Gate. ";
    }
  return break_string(longstr+"\n",75);
}

reset_room()
{
    if (!objectp(guard))
        add_guard();
}

add_guard()
{
    guard = clone_object(MINAS_DIR + "npc/wall_guard");
    guard->arm_me();
    guard->move(TO);
}
