/*
 * Room mapper
 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit "/std/object";

mixed gMap = ({ });
mapping gCoord = ([ ]);
int gAlarm_id;
int X, Y, Z;
mixed *gFrom;

void
create_object()
{
    set_name("mapper");
    set_short("Room mapper");
    seteuid(getuid());
}

void
init()
{
    add_action("start_mapper", "map");
    add_action("debug_map", "debugm");
    add_action("store_map", "storem");
    ::init();
}

public int
store_map()
{
    save_map(gCoord, "/d/Krynn/pax/std/pax_map");
    return 1;
}

public int
start_mapper(string str)
{
    mixed exits;
    int i = -1, size;
    string tmp;

    if (!str || !strlen(str))
    {
        NF("Usage: map <whole path + room name>\n");
        return 0;
    }

    if (TO->move(str))
    {
        NF("Couldn't locate room: " + str + "\n");
        return 0;
    }

    exits = E(TO)->query_exit();
    
    size = sizeof(exits)/3;

    gFrom = ({ file_name(E(TO)), 0 });

    gMap = ({ 0 });

    while (++i < size)
    {
        if (!sscanf(exits[i * 3],"%s.c", tmp))
	    tmp = exits[i * 3];
	gMap += ({ ({ tmp, exits[i * 3 + 1] }) });
    }

    gCoord += ([ file_name(E(TO)) : ({ X, Y, Z }) ]);

    gAlarm_id = set_alarm(2.0, 3.0, "map_next_room");

    return 1;
}

void
debug_map()
{
    find_player("rastlin")->catch_msg(sprintf("gMap: %O\n", gMap));
    find_player("rastlin")->catch_msg(sprintf("gCoord: %O\n", gCoord));
}

void
map_next_room()
{
    int size_map, size_room, size_tmp, i = -1, size;
    mixed *exits;
    mixed *room;
    string tmp;

    size_map = sizeof(gMap);

    size_room = sizeof(gMap[size_map - 1]);

    size_room = 2;

    if (size_room > 1)
    {
         room = gMap[size_map - 1];

         find_player("rastlin")->catch_msg("Mapping: " + room[0]);

         gMap = gMap[0..size_map - 2];

         if (!gCoord[room[0]])
	 {
    	     gMap += ({ gFrom });

             exits = call_other(room[0], "query_exit");

             size = sizeof(exits)/3;

	     while (++i < size)
	     {
	         if (!sscanf(exits[i * 3],"%s.c", tmp))
		     tmp = exits[i * 3];
	         if ((gFrom[0] != tmp) &&  (exits[i * 3 + 1] != "tunnel"))
		     gMap += ({ ({ tmp, exits[i * 3 + 1] }) });
	     }

             gFrom = room;

	     find_player("rastlin")->catch_msg(room[1]);
	     switch(room[1])
	     {
	         case "east" : X += 1; break;
		 case "west" : X -= 1; break;
		 case "north" : Y += 1; break;
		 case "south" : Y -= 1; break;
		 case "up" : Z += 1; break;
		 case "down" : Z -= 1; break;
		 case "northeast" : Y += 1;
	                            X += 1; break;
		 case "southeast" : Y -= 1;
		                    X += 1; break;
		 case "southwest" : Y -= 1;
		                    X -= 1; break;
		 case "northwest" : Y += 1;
		                    X -= 1; break;
		 default:
		   find_player("rastlin")->catch_msg("Exit: " + room[1] + "\n");
	     }
	     gCoord += ([ room[0] : ({X, Y, Z}) ]);
         }
         else
	 {
/*   	     if (!sizeof(gMap[size_map - 1][2]))
             {
	         gFrom = gMap[size_map - 1][0];
		 gMap = gMap[0..size_map - 2];
		 i = -1;
		 while ((++i < size_map) && (gFrom != gMap[i][1])) do
		 {
		 }
	     } 
*/	     X = gCoord[room[0]][0];
	     Y = gCoord[room[0]][1];
	     Z = gCoord[room[0]][2];
	 }
	 find_player("rastlin")->catch_msg(sprintf("%O %O %O\n", X, Y, Z));
    }
}








