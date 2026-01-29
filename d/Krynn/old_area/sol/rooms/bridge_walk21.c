/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

create_solace_room()
{
    set_place(BRIDGEWALK);

    set_long_desc("@@my_desc@@");

    add_exit(TDIR + "platform4", "north");
    add_exit(TDIR + "platform6", "south");
}

public string
my_desc()
{
    string str, people;

    str = "This is a bridge-walk between two platforms. The thick canopy " +
	  "overhead forms a protective shield against the outside " +
	  "world. Looking down, you see a path";

    if (people = get_living(({TDIR + "ns_path1"})))
        str += ", walking along the path you can see " + people;

    return str + ".";
}
