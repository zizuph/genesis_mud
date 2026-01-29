// Borrowed, with permissions from Boriska.
// grace march 1995

// file name: ~Avenir/common/map/mapper.c
// creator(s):  Boriska 
// last update: Dec 1994
// purpose:     Creates different map layout for areas each game reboot.
// note:
// bug(s):
// to-do:     

#pragma no_clone
#pragma no_inherit
#pragma strict_prototypes

#define CONFIG_FILE "/d/Krynn/solamn/hctower/spur/mapper/map.config"
#define LOG_FILE "/d/Krynn/solamn/hctower/spur/mapper/map.log"

#define LOG(x) write_file (LOG_FILE, ctime(time()) + " " + (x) + "\n")

#undef DEBUG
#ifdef DEBUG
#define D(x)   find_player("cotillion")->catch_msg ((x));
#else
#define D(x) ;
#endif

private int create_map (string file);
public mapping query_room_exits (object room);
public mapping query_map();

static mapping mm = ([]);
// format room : ([ next_room : "exit command" , ...])

static string *exits = ({
    "north" ,
        "east"  ,
        "northeast",
        "northwest",
        "southeast",
        "southwest",
        "west" , 
        "south" 
        });

static int num_exits = sizeof (exits);
// note: exits[i] and exits[num_exits-1-i] should lead to opposite directions
// this is used to create euclidean areas.

void
create()
{
    string str;
    string *maps_to_load;
    int i;

    seteuid(getuid());
    //  rm (LOG_FILE);
    LOG ("Starting mapper.");
    str = read_file (CONFIG_FILE);

    if (!str)
    {
        LOG ("Cannot find config file: " + CONFIG_FILE);
        return;
    }

    LOG ("Using config file: " + CONFIG_FILE);
    maps_to_load = explode (str, "\n");

    for (i = 0; i < sizeof(maps_to_load); i++)
    {
        if (!strlen(maps_to_load[i]) || maps_to_load[i][0] == '#')
            // skip empty lines and comments
            continue;
        create_map (maps_to_load[i]);
#ifdef DEBUG
        /*dump_array (mm);*/
#endif
    }
}


// add mm entries corresponding to map from file. 
private int
create_map (string file)
{
    string str;
    string *lines, *next_rooms;
    string path, room, this_room, next_room;
    string *reserved; // array of reserved exits from this room
    string *bad_rooms = ({});
    mapping ex = ([]);
    // stores exits from the room that already are picked up in binary form
    int index, i,j, opp, old_size;

    str = read_file (file);
    if (!str)
    {
        LOG ("Cannot find map file :" + file);
        return 0;
    }
  
    old_size = m_sizeof(mm);
    lines = explode (str, "\n");
    for ( i= 0; i < sizeof(lines); i++ )
    {
        if (!strlen(lines[i]) || lines[i][0] == '#')
            // skip empty lines and comments
            continue;

        // path entry. Current path from now on
        if (sscanf (lines[i], "$path$ %s", path))
            continue;
      
        // room entry. Current room from now on.
        if (sscanf (lines[i], "$room$ %s", room))
            continue;
      
        // make reserved exits appear already added for this room
        if (sscanf (lines[i], "$reserved$ %s", str))
	{
            reserved = explode (str, " ");
            for (j=0; j < sizeof(reserved); j++)
                if ((index = member_array (reserved[j], exits)) > -1)
                {
                    dump_array(ex[path+room]);
                    ex[path+room] |= 1 << index; 
                    D(path+room + " reserved: " + ex[path+room] + "\n");
                }
            continue;
	}
        this_room = path + room;
        if (!mm[this_room])
            mm[this_room] = ([]);

        next_rooms = explode (lines[i], " ");

        for (j = 0; j < sizeof(next_rooms); j++)
	{
            if (!strlen(next_rooms[j]))
                continue;
	      
            if ( member_array(next_rooms[j], bad_rooms) > -1)
                continue;

            if (ex[this_room] == (1 << num_exits) -1 )
	    {
                LOG("Number of possible exits exceeded for " + this_room + "\n");
                bad_rooms += ({this_room});  // no way in and out from now on
		continue;
	    }

            next_room = path + next_rooms[j];
            if (mm[this_room][next_room])
                continue;
      
            index = random(num_exits);
            while ((ex[this_room] & (1 << index)) ||
                (ex[next_room] & (1 << (num_exits - index - 1))))
                index = random(num_exits);

            opp = num_exits - index - 1;
            ex[this_room] |= 1 << index;
            ex[next_room] |= 1 << opp;
	  
            mm[this_room] += ([next_room : exits[index] ]);
      
            if (!mm[next_room])
                mm[next_room] = ([this_room : exits[opp] ]);
            else
                mm[next_room] += ([this_room : exits[opp] ]);
	}
    }
    LOG (m_sizeof(mm) - old_size + " rooms loaded for " + file);
    return 1;
}

public mapping
query_room_exits (object room)
{
    /*
      D ("query called for " + file_name(room) + "\n");
    */
    return mm[file_name(room)];
}

public mapping
query_map()
{
    return mm;
}
  










