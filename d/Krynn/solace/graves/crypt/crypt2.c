/* The crypt by percy */

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <filter_funs.h>

inherit INSIDE_BASE;

object sk1, zo1, zo2;

/*prototype*/



void
create_solace_room()
{
    set_short("Crypt room");
    set_long(BS("This very large well lit room is largely bare except for the north"
	 + " wall, carved into which is a beautiful mural that gives a "
	 + "very realistic three dimensional effect of a lich."
	 + " A giant sized archway leads out of the room to the south.", 70));

    add_exit(TDIR + "crypt1", "south", 0);
    add_exit(TDIR + "crypt3", "east", 0);
    add_exit(TDIR + "crypt4", "west", 0);

    add_item(({"carving", "mural", "tree", "north wall"}), "@@carving");
    add_item(({"hand", "lich"}), "The lich seems to have his hand " +
	"outstretched towards you.\n");
    add_item("floor", "@@floor");
    add_item(({"arch", "archway"}), "@@arch");
    add_item(({"wall", "walls", "hall", "hallway", "ceiling", "roof"}),
	"@@wall");

    INSIDE
    LIGHT

    reset_room();
}

void
reset_solace_room()
{
    if (!sk1)
    {
	sk1 = clone_object(MONSTER + "skwarrior");
	sk1->move_living("xxx", TO);
    }
    if (!zo1)
    {
	zo1 = clone_object(MONSTER + "zowarrior");
	zo1->move_living("xxx", TO);
    }
    if (!zo2)
    {
	zo2 = clone_object(MONSTER + "zowarrior");
	zo2->move_living("xxx", TO);
    }
}

void
init()
{
  ADA("shake");	
  ::init();
}

int
go_north()
{
  object cr5 = find_object(TDIR + "crypt5");
  object* players = FILTER_PLAYERS(cr5 ? all_inventory(cr5) : 0);
  if (players && sizeof(players))
  {
    write("You are unable to go north.\n");
    return 1;
  }
  set_alarm(1.0,0.0,"remove_north");
  return 0;
}

void
remove_north()
{
    write("The exit closes behind you.\n");
    tell_room(TO, "The exit closes silently.\n");
    remove_exit("north");
}

int
shake(string str)
{
  string *dirs;
  dirs = query_exit_cmds();
  
  if (sizeof(dirs) && member_array("north", dirs) >= 0)
  {
    write("The exit is already open.\n");
    return 1;
  } 
  NF("Shake what?\n");
  if ((str == "lich") || (str == "the hand") || (str == "hand"))
  {
    write("You reach out and shake the liches hand."
	  + " You hear a soft click and a secret passage"
	  + " opens in the north wall. You get a strange feeling"
	  + " that there is much danger to the north.\n");
    say(QCTNAME(TP) + " reaches out to shake hands with the mural and"
	+ " a secret passage opens in the north wall! You feel it would"
	+ " be dangerous to go north.\n");
    add_exit(TDIR + "crypt5", "north", "@@go_north");
    return 1;
  }
  return 0;
}

string
floor()
{
    write(BS("The floor is just a clean bare normal stone floor.", 70));
    say(BS(QCTNAME(TP) + " studies the floor carefully.", 70));
    return "";
}

string
arch()
{
    write(BS("The archway looks like a normal arch, perfectly safe..", 70));
    say(BS(QCTNAME(TP) + " studies the archway carefully.", 70));
    return "";
}

string
wall()
{
    write(BS("The walls and the ceiling of the room are black though"
	 + " they appear to only be made of normal stone, unlike the clean"
	 + " white floor. The exception is the north wall which"
	 + " depicts a horrific carving of a lich. The"
	 + " lich has its hand outstretched.", 70));
    say(BS(QCTNAME(TP) + " studies the room carefully.", 70));
    return "";
}

string
carving()
{
    write(BS("The mural is an amazing work of art. It is an almost"
	 + " life like representation of a lich his hand outstretched.", 70));
    say(BS(QCTNAME(TP) + " studies the mural carefully.", 70));
    return "";
}

