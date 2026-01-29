#pragma no_clone
#pragma no_inherit
#pragma strict_types
#pragma save_binary
inherit "/d/Ansalon/std/map_map";

public nomask void
set_map()
{
    Map = ({
/*  0 */"  xxxppfff",
/*  1 */"   xxxpxff",
/*  2 */"  xxxpxxxf",
/*  3 */"  xxpxxfff",
/*  4 */"    pfffff",
/*  5 */"pppp  ffff",
	  });
}

/*
	x: plains (not obvious exits)
	p: path (obvious exits)
	f: forest (not obvious relative exits)

	NOTE that rooms and paths when necessary also connect diagonaly.
	So above path is a connected path and all rooms are reachable.
*/
