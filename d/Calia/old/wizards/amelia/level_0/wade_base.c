inherit "/std/room";
inherit "/d/Calia/std/room_tell";

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

int *coord;

void
set_coord(int x, int y)
{
	coord = ({x,y});
}
void
create_room()
{
int x, y, z;
string tmp1, tmp2, tmp3;
  ::create_room();
}


void
init()
{
	::init();
	add_action("wade", "wade");
}
void
enter_inv(object ob, object from)
{
	::enter_inv(ob,from);
	if(living(ob))
		{
		start_room_tells();
		}
}

int
wade (string str)
{
int *go_coords;
string where, dest;
	string tmp1;
	int x, y, check;

check = 0;

	notify_fail("Wade where?\n");

  if(!strlen(str))     /*No direction specified*/
    return 0;

	/* where are we now?? */
	if (sscanf(file_name(this_room()), "%s_%d_%d", tmp1, x, y) ==3)
	set_coord(x,y);
	else return 0;
  if(str == "north" || str == "n")
    {
    where = "north";
	go_coords=({coord[0], coord[1]+1});
	check = 1;
    }

  if(str == "south" || str == "s")
    {
    where = "south";
	go_coords = ({coord[0], coord[1]-1});
	check = 1;
    }

  if(str == "east" || str  == "e")
     {
    where = "east";
	go_coords= ({coord[0]-1, coord[1]});
	check = 1;
    }

  if(str == "west"  ||  str  == "w")
    {
    where = "west";
	go_coords = ({coord[0]+1, coord[1]});
	check = 1;
    }

  if(str == "northeast" || str == "ne")
    {
    where = "northeast";
	go_coords=({coord[0]-1, coord[1]+1});
	check = 1;
    }

  if(str == "northwest"  || str == "nw")
    {
    where = "northwest";
	go_coords=({coord[0]+1, coord[1]+1});
	check = 1;
    }

  if(str == "southeast"  || str == "se")
    {
    where = "southeast";
	go_coords=({coord[0]-1,coord[1]-1});
	check = 1;
    }

  if(str == "southwest" || str == "sw")
    {
    where = "southwest";
	go_coords = ({coord[0]+1, coord[1]-1});
	check = 1;
    }

	if (!check)
		return 0;

	if ((x==1)&&(where=="east"))
	dest=BEACH+go_coords[1];
	else
   dest = SEA0+"wade_"+go_coords[0]+"_"+go_coords[1];

  if(file_size(dest+".c") < 0)
    {
	notify_fail("You can't wade in that direction.\n");
    return 0;
    }

    environment(TP)->set_dircmd(where);
	TP->catch_msg("You wade "+where+"wards.\n");
	tell_room(environment(TP),QCTNAME(TP)+" wades away "+
		where+"wards through the water.\n", ({TP}));
  TP->move_living("M",dest,0,0);
    TP->add_fatigue(-5);
	tell_room(environment(TP), QCTNAME(TP)+" wades in.\n", ({TP}));

  return 1;
}

query_coord() {return coord;}


void
create_level0()
{

	set_short("A blue-green sea");
	set_long("Blue green sea");

}
