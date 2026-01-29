/*
 * This is file that handles the map for map_serv
 * created by Milan back in 199x
 */

/****************************************************/
//   Your file with map should contain following:
//
//   #pragma no_clone
//   #pragma no_inherit
//   inherit "/d/Gondor/common/mirkwood/map_map";
//
//   void
//   set_map()
//   {
//	 Map = {( ...your map... });
//   }
//
/****************************************************/

#pragma save_binary
#pragma strict_types
#pragma no_clone

public string *Map;

public nomask void
create()
{
    this_object()->set_map();
}

/* Function name: query_local_map
 * Description:	  Local map contains room + attached rooms
 * Argument:	  x,y - coordinates of room on global map
 * Returns:	  3x3 array of letters
 */
public nomask mixed *
query_local_map(int x, int y)
{
    int i, j, size, length;
    mixed *m = ({ ({" "," "," "}), ({" "," "," "}), ({" "," "," "}) });

    if (!(size = sizeof(Map))) return m;
    for (i=0; i<3; i++)
	if ((i+y > 0) && (i+y <= size))
	{
	    length = strlen(Map[i+y-1]);
	    for (j=0; j<3; j++)
		if ((j+x > 0) && (j+x <= length))
		    m[j][i] = Map[i+y-1][j+x-1..j+x-1];
	}
    return m;
}

