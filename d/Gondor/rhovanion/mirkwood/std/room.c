/*
 * /d/Gondor/rhovanion/mirkwood/std/room.c
 *
 * Default base room for Mirkwood in the Rhovanion part of ME.
 *
 * Created by Eowul, Juni 29th, 2008
 */

#include "../defs.h"

inherit RHOVANION_STD_DIR + "room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/common/lib/room_tell";

#include <stdproperties.h>

#define GONDOR_CLOCK            ("/d/Gondor/common/obj/clock")

int query_mirkwood_location();
int calculate_mirkwood_light();
string query_mirkwood_long();
void add_long(string text, mixed levels);
int add_item_light(mixed names, mixed desc, mixed light_levels);

int max_spider_nest_size = 0;
int spider_nest_chance = 0;

mapping descriptions = ([ 
    LIGHT_DUSKDAWN : "",
    LIGHT_MIDDAY : "",
    LIGHT_BRIGHT : ""
    ]);
mapping add_item_light_levels = ([
    LIGHT_DUSKDAWN : ({ }),
    LIGHT_MIDDAY : ({ }),
    LIGHT_BRIGHT : ({ })
    ]);

#include "room_items.c"
#include "room_descriptions.c"

private int mirkwood_location;
private mixed original_room_light;

/*
 * Function name: create_mirkwood_room
 * Description  : Create a room in mirkwood
 */
void create_mirkwood_room()
{
}

/*
 * Function name: create_rhovanion_room
 * Description  : Constructs a rhovanion room, will call the mirkwood
 *              : specific constructor.
 */
void create_rhovanion_room()
{
    set_tell_time(20);

    create_mirkwood_room();
    
    if (!query_prop(ROOM_I_INSIDE)) 
    {
        remove_prop(ROOM_I_LIGHT);
        add_prop(ROOM_I_LIGHT,  calculate_mirkwood_light);
    }
    
    set_long(query_mirkwood_long);
}

/*
 * Function name: find_responsible_living
 * Description  : Travel up the previous_object chain and return the first 
 *                living found.
 * Returns      : a living or 0 when not found
 */
private object find_responsible_living() {
    object previous = previous_object();
    int level = 0;
    while(objectp(previous) && !living(previous)) {
        previous = previous_object(--level);
    }
    return previous;
}

/*
 * Function name: add_prop_room_i_light
 * Description:   Used to store the original property value
 * Arguments:     mixed val
 */
void add_prop_room_i_light(mixed val)
{
    if (val != calculate_mirkwood_light)
    {
        original_room_light = val;
    }
}

/*
 * Function name: calculate_mirkwood_light
 * Description  : Calculate the level of light depending on the time of day
 * Returns      : the light level for this room.
 */
int calculate_mirkwood_light() 
{
    int hour = GONDOR_CLOCK->query_hour();
    switch(hour) 
    {
        case EVENING:
        case EARLY_NIGHT:
        case LATE_NIGHT:
        case EARLY_MORNING:
            return LIGHT_NIGHT;
        case MORNING:
        case AFTERNOON:
            return LIGHT_DUSKDAWN;
        case NOON:
            return LIGHT_MIDDAY;
    }
    
    return 1;
}

/*
 * Function name: reset_long
 * Description  : Resets the long descriptions to empty values so a new 
 *              : description can be loaded.
 */
void reset_long()
{
    descriptions = ([ 
        LIGHT_DUSKDAWN : "",
        LIGHT_MIDDAY : "",
        LIGHT_BRIGHT : ""
        ]);
}

/*
 * Function name: add_long
 * Description  : Add a line to the long description, taking into account he
 *              : light level.
 * Arguments    : text - the text to add
 *              : levels - either an array with light levels, or a single light 
 *              :        level
 */
void add_long(string text, mixed levels) 
{
    if(!pointerp(levels)) 
    {
        levels = ({ levels });
    }
    
    foreach(mixed light_level : levels) 
    {
        descriptions[light_level] += text;
    }
}

/*
 * Function name: query_light_level_for_living
 * Description  : Calculate the light level the living can see.
 * Arguments    : living - the living to calculate for
 * Returns      : One of the valid light levels
 */
int query_light_level_for_living(object living)
{
    if(living->query_wiz_level()) {
        object mirkwood_light = present("_mirkwood_debug_light", living);
        if(objectp(mirkwood_light)) return mirkwood_light->query_mirkwood_light_level();
    }
    
    int living_light_level = living->query_prop(LIVE_I_SEE_DARK)
        + query_prop(OBJ_I_LIGHT);
        
    if(living_light_level < LIGHT_NIGHT) return LIGHT_NIGHT;
    if(living_light_level > LIGHT_BRIGHT) return LIGHT_BRIGHT;
    return living_light_level;
}

private object find_spider_nest() {
    return present(MIRKWOOD_SPIDER_NEST_ID, this_object());
}

/*
 * Function name: query_mirkwood_long
 * Description  : Generate the long description for this room based on
 *              : the players light level.
 * Returns      : The long description
 */
string query_mirkwood_long()
{
    object nest = find_spider_nest();
    if (objectp(nest)) return nest->query_mirkwood_long();

    int light_level = query_light_level_for_living(this_player());
    switch(light_level)
    {
        case LIGHT_DUSKDAWN:
        case LIGHT_MIDDAY:
        case LIGHT_BRIGHT:
            return check_call(descriptions[light_level] + "\n", this_player());
        default:
            return "It's too dark to see.\n";
    }
}

/*
 * Function name: add_item
 * Description  : Overload for the normal add_item function that also takes
 *              : light levels as argument.
 * Arguments:     names: Alternate names for the item, 
 *                mixed desc: desc of the item (string or VBFC)
 *                mixed light_levels: Light levels at which this is visible
 */
int add_item_light(mixed names, mixed desc, mixed light_levels)
{
    add_item(names, desc);
    
    if(!pointerp(names)) 
    {
        names = ({ names });
    }
    
    if(!pointerp(light_levels)) 
    {
        light_levels = ({ light_levels });
    }
    
    foreach(int level : light_levels)
    {
        add_item_light_levels[level] += names;
    }
}
 
/*
 * Function name: item_id
 * Description  : Identify items in this room. Will take into account the 
 *              : light levels at which the item should be visible.
 * Arguments    : string str - the name to test.
 * Returns      : int 1/0 - is added with add_item() or not.
 */
public int item_id(string str)
{
    object nest = find_spider_nest();
    if (objectp(nest)) return nest->item_id(str);

    int light_level = query_light_level_for_living(this_player());
    if(member_array(str, add_item_light_levels[light_level]) != -1)
        return 1;
        
    return 0;
}


/*
 * Function name: long
 * Description:   Describe the room and possibly the exits
 * Arguments:     str: name of item or 0
 * Returns:       A string holding the long description of the room.
 */
public mixed long(string str)
{
    object nest = find_spider_nest();
    if (objectp(nest) && stringp(str) && strlen(str)) {
        if (!nest->item_id(str)) return 0;

        return nest->item_description(str);
    }

    if(stringp(str) && strlen(str) && !item_id(str))
        return 0;
    
    return ::long(str);
}

/*
 * Function name: set_mirkwood_location
 * Description  : Sets the position of this room in Mirkwood.
 * Arguments    : location - the location in mirkwood
 */
void set_mirkwood_location(int location) 
{
    mirkwood_location = location;
}

/*
 * Function name: query_mirkwood_location
 * Description  : Get the location of this room in mirkwood
 * Returns      : int
 */
int query_mirkwood_location() 
{
    return mirkwood_location;
}

/*
 * Function name: setup_mirkwood_herbs
 * Description  : Prepare the room for herb searching
 * Arguments    : fixed_herbs - the herbs that are always found 
 *                              in this room, will have an additional
 *                              set of random ones added 
 */
void setup_mirkwood_herbs(string *fixed_herbs = ({ })) {
    string *herbs_in_room = fixed_herbs;

    string *random_herbs = ({ 
        HERB_DIR + "attanar",
        HERB_DIR + "astaldo",
        HERB_DIR + "blueberry",
        HERB_DIR + "blung",
        HERB_DIR + "foxglove",
        HERB_DIR + "handasse",
        HERB_DIR + "hemlock",
        HERB_DIR + "holly",
        HERB_DIR + "laurel",
        HERB_DIR + "marigold",
        HERB_DIR + "myrtle",
        HERB_DIR + "redweed",
        HERB_DIR + "savory",
        HERB_DIR + "sumac",
        HERB_DIR + "suranie",
        HERB_DIR + "tuo",
        HERB_DIR + "ungolestel",
        SHIRE_HERB_DIR + "bilberry",
        SHIRE_HERB_DIR + "blackroot",
        SHIRE_HERB_DIR + "huckleberry",
        SHIRE_HERB_DIR + "goats_rue",
        SHIRE_HERB_DIR + "khuz",
        SHIRE_HERB_DIR + "maroea",
        SHIRE_HERB_DIR + "pawnrose",
        SHIRE_HERB_DIR + "treemushroom",
        KRYNN_HERB_DIR + "amanita",
        KRYNN_HERB_DIR + "blk_currant",
        KRYNN_HERB_DIR + "bunchberry",
        KRYNN_HERB_DIR + "bkd_sedge",
        KRYNN_HERB_DIR + "chantrelle",
        KRYNN_HERB_DIR + "chicory",
        KRYNN_HERB_DIR + "cladina",
        KRYNN_HERB_DIR + "dandelion",
        KRYNN_HERB_DIR + "fdlhead",
        KRYNN_HERB_DIR + "fireweed",
        KRYNN_HERB_DIR + "grey_willow",
        KRYNN_HERB_DIR + "hawthorn",
        KRYNN_HERB_DIR + "hazelnut",
        KRYNN_HERB_DIR + "horsetail",
        KRYNN_HERB_DIR + "lady_slipper",
        KRYNN_HERB_DIR + "poison_ivy",
        KRYNN_HERB_DIR + "raspberry",
        KRYNN_HERB_DIR + "sarsaparilla",
        KRYNN_HERB_DIR + "tangleshoot",
        KRYNN_HERB_DIR + "tiger_lily",
        KRYNN_HERB_DIR + "wild_plum"
    }) - fixed_herbs;

    while(sizeof(herbs_in_room) < 7) {
        string additional_herb = random_herbs[random(sizeof(random_herbs))];
        random_herbs -= ({ additional_herb });
        herbs_in_room += ({ additional_herb });
    }

    set_up_herbs(herbs_in_room);
} 

/*
 * Function name: set_max_spider_nest_size
 * Description  : Determine the maximum size of the spider nests that spawn in 
 *                this room.
 * Arguments    : size - the maximum size
 */
void set_max_spider_nest_size(int size) 
{
    max_spider_nest_size = size;
}

int query_max_spider_nest_size() 
{
    return max_spider_nest_size;
}

/*
 * Function name: set_spider_nest_chance
 * Description  : Sets a chance the spider nest will spawn in this room
 * Arguments    : chance
 */
void set_spider_nest_chance(int chance) 
{
    spider_nest_chance = chance;
}

int query_spider_nest_chance() 
{
    return spider_nest_chance;
}

int check_for_warning() 
{
    if (MIRKWOOD_MASTER->has_received_warning(this_player(), WARNING_FOREST)) 
        return 0;

    write("You hesitate a moment to enter the dark forest, for you "
        + "are certain that great danger lies within. If you decide "
        + "to enter, you might not return, so choose wisely.\n");
    MIRKWOOD_MASTER->set_received_warning(this_player(), WARNING_FOREST);
    return 1;
}

void add_forest_entrance(string path, string direction) 
{
    add_exit(path, direction, check_for_warning, 5, 1);
}

public void notify_change_prop(string prop, mixed val, mixed old)
{
    object ob = previous_object();

    if ((prop == OBJ_I_INVIS) && interactive(ob) && old && !val) {
        object nest = find_spider_nest();
        if (objectp(nest)) nest->notify_player_entered(ob);
    }
}

public void enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (objectp(ob) && interactive(ob) && !ob->query_invis()) {
        object nest = find_spider_nest();
        if (objectp(nest)) nest->notify_player_entered(ob);
    }
        if (!query_prop(ROOM_I_INSIDE)) 
    {
        remove_prop(ROOM_I_LIGHT);
        add_prop(ROOM_I_LIGHT,  calculate_mirkwood_light);
    }

    start_room_tells();
}