/* 
 *  Eldoral Underground Base Room
 *
 *  This is the base room that all underground rooms will inherit from.
 *  It will set up some common functions and properties such as the
 *  mapping file that contains the maps for this. 
 *
 *  Created by Petros, November 2008
 *  Fixed typo - Jaacar, May 2016
 */

inherit "/d/Calia/std/room_tell_room_new";

#include <composite.h>
#include "../defs.h"

// Prototypes
public int      try_item(mixed names, mixed desc);
public string   query_short_desc();
public string   query_long_desc();


// Defines
#define MAP_LOCATION    "/d/Calia/open/MAP_FILES/"
#define UNDEAD_MAKER    (STD + "undead_maker")

// Global Variables
public int      areatype = 0;
public string   default_short_desc = "A standard eldoral tunnel room";
public string   default_long_desc = "This is a standard tunnel room in Eldoral.\n";

/*
 * Function     : query_map_file
 * Description  : Returns the map file in /d/Calia/open/MAP_FILES
 *                that contains the information used in the magic
 *                map.
 * Arguments    : none
 * Returns      : nothing
 */
public string
query_map_file()
{
    return "eldoral_tunnel_map.txt";
}

/*
 * Function     : create_tunnel_room
 * Description  : Default room creation function for all tunnel rooms.
 *                this will be masked by all children.
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_tunnel_room() 
{ 
}

/*
 * Function:    banshee_wail
 * Description: The banshee if she is in the caves causes shrieking
 *              noises.
 * Arguments:   None
 * Returns:     empty string if banshee is dead. Description otherwise
 */
public string
banshee_wail()
{
    object banshee_master;
    object * banshees;
    
    banshee_master = find_object(BASE + "tunnel/npcs/banshee");
    if (!objectp(banshee_master))
    {
        return "";
    }
    
    banshees = object_clones(banshee_master);
    if (!banshees || !sizeof(banshees))
    {
        return "";
    }
    
    return "You hear a loud, shrieking sound reverberate throughout the "
        + "caves.\n";
}

/*
 * Function     : create_room
 * Description  : this is the default configuration for a room. It
 *                will call create_tunnel_room to configure the room
 *                specific items.
 * Arguments    : none
 * Returns      : nothing
 */
public nomask void
create_room()
{
    string map_file;
    
    map_file = query_map_file();
    if (strlen(map_file) && file_size(MAP_LOCATION + map_file))
    {
        add_prop(ROOM_S_MAP_FILE, query_map_file());
    }
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    set_short("@@query_tunnel_short");
    set_long("@@query_tunnel_long");    
    
    setuid();
    seteuid(getuid());
    // Call create_tunnel_room to set up the room specific items
    create_tunnel_room();
    
    // Now try to add the items that may not have been added
    try_item( ({ "moss", "fusty smelling moss" }),
        "It is a dark-green slimy plant that grows almost like a "
      + "mat on the walls. The soft glow that exudes from them "
      + "provides the only source of light in this tunnel.\n");
    try_item( ({ "wall", "walls" }), 
        "The small spaces of the wall that are not covered with a fusty "
      + "smelling moss are dark, almost pitch-black, in colour.\n");
    try_item( ({ "space", "spaces", "small space", "small spaces" }),
        "It is difficult to tell what is inside those small spaces, but "
      + "it is very likely that there is simply more moss there.\n");
    try_item( ({ "floor", "ground" }),
        "You are upon a stony surface that has been roughly hewn to "
      + "provide the necessary means to travel through this tunnel.\n");
    try_item( ({ "tunnel", "cave", "caves", "tunnels" }),
        "The tunnel you are in is eerily quiet, yet occasionally interrupted "
      + "by a sudden sound that can startle the light of heart.\n");
    try_item( ({ "ceiling", "roof" }),
        "The ceiling of the tunnel must be quite high because from where "
      + "you stand, you see only pitch black.\n");
    try_item( ({ "light", "light source", "source of light" }),
        "The only visible source of light that you see is the mat of "
      + "moss that covers the wall. The moss seems to give off a soft "
      + "glow that iluminates the room just ever so slightly.\n");

    set_tell_time(90); // gives message every 90 seconds on average
    add_tell("A dull scraping sound echoes through the tunnels.\n");
    add_tell("It feels as if something is nibbling at your feet, but as "
        + "you look down you see nothing.\n");
    add_tell("You think you spot something moving in the corner of your "
        + "eye, but as you turn your head to look, you see nothing.\n");
    add_tell("Suddenly everything is very quiet.\n");
    add_tell("This malodorous smell is really awful!\n");
    add_tell("banshee_wail");
}

/*
 * Function     : query_tunnel_short
 * Description  : Returns the short description for this particular
 *                room.
 * Arguments    : none
 * Returns      : short description
 */
public string
query_tunnel_short()
{
    return areatype ? query_short_desc() : default_short_desc;
}

/*
 * Function     : query_tunnel_long
 * Description  : Returns the long description for this particular
 *                room.
 * Arguments    : none
 * Returns      : long description
 */
public string
query_tunnel_long()
{
    return areatype ? query_long_desc() : default_long_desc;
}


/*
 * Function name:       try_item
 * Description  :       checks to see if an item already exists
 *                      within a given object, and if it does not, it then
 *                      adds it as add_item() would.
 * Arguments    :       mixed names --  string or array of strings, the
 *                                      item name(s).
 *                      mixed desc -- string or function, the description.
 * Returns      :       int -- the number of items added
 */
public int
try_item(mixed names, mixed desc)
{
    int         i;
    string      *exists;

    if (pointerp(names)) 
    { 
        exists = ({});
        foreach (string name : names)
        {
            if (item_id(name)) 
            {
                exists += ({ name });
            }
        }
        names -= exists;
        if (sizeof(names))
        {
            add_item(names, desc);
        }
        i = sizeof(names);
    } 
    else if (!this_object()->item_id(names))
    {
        add_item(names, desc);
        i = 1;
    }
    return i;   // # of items added
}


/*
 * Function     : clone_undead
 * Description  : Returns the long description for this particular
 *                room.
 * Arguments    : race  - race of the undead to create
 *                level - level of the undead to generate
 * Returns      : long description
 */
public varargs void
clone_undead(string race, int level, int number = 1, int maxsize = 0)
{
    object undead;

    for (int i = 0; i < number; ++i)
    {
        if (maxsize
            && sizeof(filter(all_inventory(TO), &->id(race))) >= maxsize)
        {
    		return;
        }
    
        undead = UNDEAD_MAKER->clone_undead(race, level);
        if (objectp(undead))
        {
            undead->move(TO);
        }
    }
}

// Temporary Function - To be removed - for backwards compat for now
void 
add_items()
{
    switch(areatype)
    {
        case 1: // 1 - Intersection (type a).
            try_item(({"skeletons", "bones", "leftovers"}),"They seem to be some "+
                "humanoid bones. Perhaps you should turn back!\n");
            break;
        
        case 2: // 2 - Tunnel (type b).
            try_item("","");
            break;
        
        case 3: // 3 - Tunnel (type c).
            try_item(({"skeletons", "bones", "leftovers"}),"They seem to be some "+
                "humanoid bones. Perhaps you should turn back!\n");
            break;
        
        case 4: // 4 - Tunnel (type d).
            try_item(({"stream","streams","puddle", "pool"}),"Small streams of "+
                "water run down the walls, forming a small, shallow pool of "+
                "water on the ground.\n");
            break;
        
        case 5: // 5 - dead end (type e).
            try_item("","");
            break;

        case 6: // 6 - dead end (flooded pool).
            try_item(({"pool","flooded pool"}),"This flooded pool seems to lead "+
                "deep into the ground and leads off to the northeast. The pool "+
                "is too small for you to attempt to enter.\n");
            break;

        case 7: // 7 - Banshee Lair.
            try_item(({"ruins","ancient ruins","ancient looking ruins"}),
                "There are many ruined columns and what appears to be the "+
                "remains of some type of altar.\n");
            try_item("columns","The columns are all collapsing on one another "+
                "and have many chips and cracks in them.\n");
            try_item(({"bones","many bones"}),"There are many bones strewn "+
                "throughout the ruins here in this cave. They appear to be "+
                "humanoid mostly.\n");
            try_item("altar","You can make nothing out about this ruined altar "+
                "except that it was once an altar.\n");
            break;

        case 8: // 8 - Heucuva Lair.
            try_item("corpses","The corpses are all decaying humanoid figures "+
                "set into a position as though they are praying.\n");
            break;
    }
    
    try_item("moss","It is a dark-green slimy plant that "+
        "grows almost like a mat on the walls.\n");
    try_item(({"wall", "walls"}), "The small spaces of the wall "+
        "that are not covered with a fusty smelling moss are dark, "+
        "almost pitch-black, in colour.\n");
    
    return;    
}

string
query_short_desc()
{
    switch(areatype)
    {
        case 1: // 1 - Intersection (type a).
            return "In a tunnel intersection";
            break;
        
        case 2: // 2 - Tunnel (type b).
            return "Along a narrow tunnel";
            break;
    
        case 3: // 3 - Tunnel (type c).
            return "In a narrow tunnel";
            break;
    
        case 4: // 4 - Tunnel (type d).
            return "A bend in the tunnel";
            break;
    
        case 5: // 5 - Dead end (type e).
            return "Dead end";
            break;
        
        case 6: // 6 - Dead end (flooded pool).
            return "Dead end";
            break;

        case 7: // 7 - Banshee lair.
            return "Ruins";
            break;

        case 8: // 8 - Heucuva lair.
            return "Ruined temple";
            break;
    }
}

string
query_long_desc()
{
    int *exits = TO->query_obvious_exits();
    string desc = "";

    switch(areatype)
    {
        case 1: // 1 - Intersection (type a).
            desc = "You have arrived at an intersection in the tunnel. "+
                "Exits leads off in "+LANG_WNUM(sizeof(exits))+" directions - "+
                COMPOSITE_WORDS(exits)+". The cave walls are covered with "+
                "a dark-green, slimy moss that has a very fusty smell. Some old "+
                "bones and leftovers are lying on the ground here.";
            break;

        case 2: // 2 - Tunnel (type b).
            desc = "You are venturing along a narrow tunnel inside a big "+
                "cave system. The tunnel continues "+COMPOSITE_WORDS(exits)+
                ". The cave walls are covered with a dark-green, slimy moss. "+
                "There is a malodorous smell here but you can't really figure "+
                "out where it is coming from.";
            break;

        case 3: // 3 - Tunnel (type c).
            desc = "You have stopped at a narrow tunnel of what seems to "+
                "be a big tunnel system. It continues "+COMPOSITE_WORDS(exits)+
                ". Some old skeletons and bones are spread all over the tunnel "+
                "floor here.";
            break;
    
        case 4: // 4 - Tunnel (type d).
            desc = "You are standing in the middle of a sharp bend in the tunnel. "+
                "It leads "+COMPOSITE_WORDS(exits)+ ". A very fusty smell rises "+
                "from the mossy walls here, almost too much for you to handle. "+
                "Small streams of water run down the walls, forming a puddle on "+
                "the ground.";
            break;
    
        case 5: // 5 - Dead end (type e).
            desc = "You have arrived at a dead end. The only way out of here "+
                "is the to the "+COMPOSITE_WORDS(exits)+".";
            break;

        case 6: // 6 - Dead end (flooded pool).
            desc = "You have arrived at a dead end. The only way out of here "+
                "is to the "+COMPOSITE_WORDS(exits)+". On the ground there "+
                "is a flooded pool.";
            break;

        case 7: // 7 - Banshee lair.
            desc = "You have arrived at a dead end. The only way out of here "+
                "is to the "+COMPOSITE_WORDS(exits)+". Scattered around the "+
                "area are some ancient looking ruins. Strewn throughout the "+
                "ruins are the many bones of the victims of the inhabitants of "+
                "this cave.";
            break;

        case 8: // 8 - Heucuva lair.
            desc = "You have arrived at a dead end. The only way out of here "+
                "is to the "+COMPOSITE_WORDS(exits)+". This appears to be a "+
                "grotesque mockery of an old temple. There are many corpses "+
                "lining the walls, set into positions resembling those praying "+
                "in a chapel.";
            break;
    }
    
    return desc + "\n";
}

void
set_area_type(int type)
{
    areatype = type;
    add_items();
}

