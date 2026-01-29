inherit "/d/Gondor/common/room";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include "/d/Gondor/defs.h"

#define BEFORE_GATE   "/d/Gondor/anorien/pelennor/citygate"
object *guards;
int nr;

void reset_room();
void add_guards(int n);

void
create_room()
{
  set_short("Upon the battlements of the Great Gate");
  set_long("@@describe");
  add_exit(MINAS_DIR+"wall/topswall1","south",0,0);
  add_exit(MINAS_DIR+"wall/topnwall1","north",0,0);
  add_item(({"gate","gates","Gate","first gate","First Gate"}),"@@checkgates");
  add_item("fields","@@fielddesc");
  add_item("battlements",BSN(
    "You are standing on the battlements upon the Great Gate. Strong stone "+
    "crenelations guard the soldiers up here from enemy archery from below. "+
    "At the same time, enemies below will be nice targets for bowmen "+
    "up here."));
  add_item("gatehouse",BSN(
    "You are standing on top of the gatehouse battlements. Below you is "+
    "the white stone gatehouse of the Great Gate, through "+
    "which all traffic to the City must pass, though you see nothing "+
    "of what's inside, from here."));
  add_prop(ROOM_I_INSIDE, 0);
  nr = 3 + random(3);
  guards = allocate(nr);
  reset_room();
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
    string time,desc;
    object *lnames, outgate;
    time = tod();
    
    if (time == "evening" || time == "night")
    {
	desc = "The Great Gate of Minas Tirith is always kept closed, and " +
	    "especially so in the night-time. Only trusted persons are " +
	    "allowed to pass through now.\n";
    }
    else
    {
	desc = "The Great Gate of Minas Tirith is always kept closed, even " +
	    "now in the daytime. But guards let through people who don't " +
	    "look too suspicious, and whom they are sure are not enemies " +
	    "of Gondor.\n";
    }
    
    seteuid(getuid(TO));
    (BEFORE_GATE)->load_me();
    lnames = FILTER_LIVE(all_inventory(find_object(BEFORE_GATE)));
    
    if (sizeof(lnames) > 0)
    {
	desc += "You see " + COMPOSITE_LIVE(lnames) +
	    " standing before the Great Gate.\n";
    }
    else
    {
	desc += "There is no one before the Great Gate.\n";
    }
    
    return desc;
}

mixed
query_range_targets(object archer)
{
   seteuid(getuid(TO));
   (BEFORE_GATE)->load_me();
   return ({    (BEFORE_GATE),
		"[before] [the] 'gate'",
		"before the gate",
		"the battlements above the gate" });
} 

string
describe()
{
  string time,longstr;
  time = tod();
  longstr = "You are upon the battlements of the Great Gate of Minas Tirith. ";
  if (time == "night") {
    longstr = "In the darkness of the night you don't see much, but the city "+
      "lies behind you to the west, and a few lights can be seen in the "+
      "windows. The plains that you know exist to the east lies in darkness. "+
      "Below your feet, the Great Gate leads through the First Wall. "+
      "Stairways go down into the wall north and south of here. ";
    }
  if (time == "morning"|| time=="early morning") {
    longstr = "The rising sun in the east casts long shadows in the City "+
      "behind you. Stretching out before you to the east are "+
      "the Pelennor fields, the farmlands outside Minas Tirith. Below "+
      "you, the Great Gate leads through the wall of the City. Stairways "+
	"lead down into the wall north and south of here. ";
  }
  if (time == "noon")
    {
      longstr = "The sun is at its peak on the sky above Gondor, as you "+
	"stand here looking out across the Fields of Pelennor to the east. "+
	"The Great Gate leads through the wall just below your feet, and "+
	  "sets of stairs lead down in the wall north and south of here. ";
    }
  if (time == "afternoon" || time == "evening")
    {
      longstr = "The "+time+" sun is disappearing behind the looming Mount "+
	"Mindolluin to the west, putting the City in shadow. To the east "+
	"are the Pelennor fields, while the City of Minas Tirith is on the "+
	"other side of the protecting First Wall. Stairways lead down "+
	"inside the wall north and south of here, while just below your feet "+
	  "is the gatehouse of the Great Gate of Minas Tirith. ";
    }
  return break_string(longstr+"\n",75);
}

void
add_guards(int limit)
{
    int number, i;

    for (i = 0; i < limit ; i++)
    {
	if(!guards[i])
	{
	    number++;
	    guards[i] = clone_object(MINAS_DIR + "npc/gondor_archer");
	    guards[i]->arm_me();
	    guards[i]->move(TO, 1);
	}
    }
    
    if (number == 1)
    {
	tell_room(TO, QCNAME(guards[0]) + " arrives.\n");
    }
    else if (number > 1)
    {
	tell_room(TO, capitalize(LANG_WNUM(number)) + " " +
			 guards[0]->short() + "s arrives.\n");
    }	    
}

reset_room()
{
    add_guards(nr);
}

object *
query_guards()
{
    return filter(guards, &objectp());
}

