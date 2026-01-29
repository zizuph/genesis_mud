
int boundaries;

int x = 0;
int y = 0;
int z = 0;

string room_ore;
string master_mine_ore;
string master_mine_terrain;

mapping opositeDirs = (["south": "north",
                   		"north": "south",
                   		"west": "east",
                   		"east": "west",
                   		"up": "down",
                   		"down": "up"
                   		]);

mapping dirLocs = (["south": -1,
                   		"north": 1,
                   		"west": -1,
                   		"east": 1,
                   		"up": -1,
                   		"down": 1
                   		]);

mapping dirLocsLetters = (["south": "x",
                   		"north": "x",
                   		"west": "y",
                   		"east": "y",
                   		"up": "z",
                   		"down": "z"
                   		]);

mapping rooms = ([]);

object master_instance_room = 0;

object tied; /* The rope that is tied here. */
object query_tied() { return tied; }

int thrown_rope = 0; /* If the rope was thrown below. */
int query_thrown_rope() { return thrown_rope; }

string dungeon = "none";


/*	Function name: set_master_instance_pointer
	Description: 

*/
void
set_master_instance_pointer(object ob)
{
    master_instance_room = ob;
}

/*  Function name: set_master_instance_pointer
    Description: 

*/
object
query_master_instance_pointer()
{
    return master_instance_room;
}

/*	Function name: set_room_loc
	Description: 

*/
void
set_room_loc(int x, int y, int z, object ob)
{
    rooms[x+(y*100)+(z*10000)] = ob;
}

/*  Function name: query_rooms
  Description: 

*/
object
query_rooms(int x, int y, int z)
{
    return rooms[x+(y*100)+(z*10000)];
}

/*	Function name: set_x
	Description: 

*/
void
set_x(int set_x)
{
	x = set_x;
}

/*	Function name: set_y
	Description: 

*/
void
set_y(int set_y)
{
	y = set_y;
}

/*	Function name: set_z
	Description: 

*/
void
set_z(int set_z)
{
	z = set_z;

  this_object()->add_item(({ "debug" }),
    "X:"+x+" Y:"+y+" Z:"+z+".\n");
}

/*	Function name: set_master_mine_ore
	Description: 

*/
void
set_master_mine_ore(string set_ore)
{
	master_mine_ore = set_ore;
}

/*	Function name: query_master_mine_ore
	Description: 

*/
string
query_master_mine_ore()
{
	return master_mine_ore;
}

/*	Function name: set_room_ore
	Description: 

*/
void
set_room_ore(string set_ore)
{
	room_ore = set_ore;
}

/*	Function name: set_master_mine_terrain
	Description: To add types of rocks to the mine

*/
void
set_master_mine_terrain(string set_terrain)
{
	master_mine_terrain = set_terrain;
}

/*	Function name: query_master_mine_terrain
	Description: 

*/
string
query_master_mine_terrain()
{
	return master_mine_terrain;
}

/*
 * Function name: block_player
 * Description  : If a monster is present, it will block the desired exit.
 */
public int
block_player()
{
    if (present("_instance_monster_"))
    {
        write("Something or someone blocks you from travelling in "
        +"that direction!\n");

        return 1;
    }

    return 0;
}

/*
 * Function name: block_player_down
 * Description  : If there's no rope attached, you cant go down.
 */
public int
block_player_down()
{
    if (!query_tied() || !query_thrown_rope())
    {
        write("You need to throw a rope that supports your weight to move further down.\n");

        return 1;
    }

    return 0;
}

/*
 * Function name: block_player_dungeon
 * Description  : If a player mines into a dungeon, stop him from going in.
 */
public int
block_player_dungeon()
{
    write("Impossible to go that way. Theres a rock formation with various inscriptions, " +
        "that seems protected by magic.\n");

    return 1;
}

/*  Function name: set_dungeon
    Description: 
    none - not dungeon
    door - dungeon door
    trap - dungeon trap
    trsr - dungeon treasure
    

*/
public void
set_dungeon(string dun)
{
    dungeon = dun;
}

/*  Function name: query_dungeon_type
    Description: 

*/
public string
query_dungeon_type()
{
    return dungeon;
}

/*	Function name: set_boundaries
	Description: 

*/
void
set_boundaries(int boun)
{
	boundaries = boun;
}

/*  Function name: get_boundaries
    Description: 

*/
int
get_boundaries()
{
    return boundaries;
}

/*
 * Function name: query_mine_boundaries
 * Description  : Tells us if this room is at the border of the mine. (no more digging)
 */
int
query_mine_boundaries(int x_boun, int y_boun, int z_boun)
{
	if (x_boun - boundaries == 0 || x_boun + boundaries == 0 ||
		y_boun - boundaries == 0 || y_boun + boundaries == 0 ||
		z_boun - boundaries == 0 || z_boun + boundaries == 0)
	{
    	return 0;
	}
	else
	{
		return 1;
	}
}

/*	Function name: create_reward
	Description: creates an ore in the room unless parameter is "none"

*/
void
create_reward(string reward)
{
	object tp = this_player();

	if (reward != "none")
	{
		object rwrd = clone_object(ORES_DIR + "ore/" + reward);
		tp->catch_msg("You catch a glimpse of some useful ore in the rubble.\n");
		rwrd->move(environment(tp));
	}
}