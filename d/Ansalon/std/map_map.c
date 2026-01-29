/*
 * This is file that handles the map for map_serv
 * created by Milan
 */

/****************************************************/
//   Your file with map should contain following:
//
//   #pragma no_clone
//   #pragma no_inherit
//   #pragma strict_types
//   #pragma save_binary
//   inherit "/d/Ansalon/std/map_map";
//
//   void
//   set_map()
//   {
//	 Map = {( ...your map... });
//	 // optionaly
//	 // Map2 = ({ ...your secondary map... });
//   }
//
/****************************************************/

#pragma save_binary
#pragma strict_types
#pragma no_clone

public string *Map = ({});

public nomask void
create()
{
    this_object()->set_map();
}

/* Function name: query_local_map
 * Description:	  Local map contains room + attached rooms
 * Argument:	  x,y - coordinates of room on global map
 * Returns:	  string of lenght 9 representing local map in order:
 *		  n,ne,e,se,s,sw,w,nw,center
 */
public nomask string
query_local_map(int x, int y)
{
    int i, j, size, length;
    mixed *m = ({ ({" "," "," "}), ({" "," "," "}), ({" "," "," "}) });
    string mm = "";

    if (!(size = sizeof(Map)))
	return "12345678 ";
    for (i=0; i<3; i++)
	if ((i+y > 0) && (i+y <= size))
	{
	    length = strlen(Map[i+y-1]);
	    for (j=0; j<3; j++)
		if ((j+x > 0) && (j+x <= length))
		    m[j][i] = Map[i+y-1][j+x-1..j+x-1];
	}
    mm += m[1][0];
    mm += m[2][0];
    mm += m[2][1];
    mm += m[2][2];
    mm += m[1][2];
    mm += m[0][2];
    mm += m[0][1];
    mm += m[0][0];
    mm += m[1][1];
    return mm;
}

public nomask int
query_map_size()
{
    return sizeof(Map);
}

public nomask string
query_map_line(int i)
{
    if (i >= 0 && i < query_map_size())
	return Map[i];
    return "";
}
