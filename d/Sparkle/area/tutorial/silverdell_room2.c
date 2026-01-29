/*
 *  /d/Sparkle/area/tutorial/silverdell_room.c
 *
 *  This is the master file for rooms in Silverdell.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "defs.h"
#include <macros.h>  //for MASTER_OB

inherit "/std/room";
inherit LIB_DIR + "instance";
inherit LIB_DIR + "lib_sign";

#include <stdproperties.h>

/* prototypes */
public void        create_silverdell();
nomask void        create_room();
public void        init();
public int         do_modify(string arg);
public int         try_item(mixed names, mixed desc);
public void        add_outdoor_items();
public void        add_road_items();
public void        prevent_attacks();
public void        add_indoor_items();
public void        add_window_items();
public void        add_door_items();
public void        add_forest_items();
public void        add_river_items();
public void        add_mountain_items();
public void        add_cliffs_items();
public string      exa_sky();
public string      exa_cloud();
public string      exa_light();
public string      exa_silverdell();
public int         hint(string arg);
public string      exa_forest();
public string      exa_river();
public string      exa_mountains(int cliffs = 0);
public int         query_instance_id(object player);
public void        set_room_instance(int id);
public int         query_room_instance();
public object      load_room(int index);
//public object      query_instance(int id);
public object      query_instance(object player);
public varargs int moveto(string how, mixed to_dest, int dont_follow,
    int no_glance);


int                instance_id = -1;

/*
 * Function name:        create_silverdell
 * Description  :        a dummy function to be used by inheriting files
 */
public void
create_silverdell()
{
} /* create_silverdell */


/* 
 * Function name:        create_room
 * Description  :        set up the room
 */
nomask void
create_room()
{
    enable_reset(200);  /* make resets as fast as possible for grinding */
    add_prop(ROOM_S_MAP_FILE, "tutorial_map.txt");

    //By default, rooms are not instanced.
    instance_entrance = 1;

    create_silverdell();
} /* create_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_modify, "status");
    add_action(hint, "hint");
} /* init */


/*
 * Function name:        do_modify
 * Description  :        for testing purposes, allow wizards to set
 *                       their status as savior or destroyer of the
 *                       area. Usage:
 *                         <modify null>   - clear status
 *                         <modify good>   - set status to savior
 *                         <modify evil>   - set status to destroyer
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_modify(string arg)
{
    if (!this_player()->query_wiz_level() &&
         this_player()->query_real_name() != "gorbyjr")
    {
        return 0; /* wizards and my jrs only! */
    }

    switch(arg)
    {
        case "bunny":
            if (CHECK_TUTORIAL_BIT(BUNNY_BIT))
            {
                CLEAR_TUTORIAL_BIT(BUNNY_BIT);
                write("Bunny Bit: Cleared.\n");
            }
            else
            {
                SET_TUTORIAL_BIT(BUNNY_BIT);
                write("Bunny Bit: Set.\n");
            }
            break;
        case "null":
            CLEAR_TUTORIAL_BIT(SAVIOR_BIT);
            CLEAR_TUTORIAL_BIT(DESTROYER_BIT);
            write("Status cleared.\n");
            break;
        case "good":
            SET_TUTORIAL_BIT(SAVIOR_BIT);
            CLEAR_TUTORIAL_BIT(DESTROYER_BIT);
            write("Savior Status Set.\n");
            break;
        case "evil":
            CLEAR_TUTORIAL_BIT(SAVIOR_BIT);
            SET_TUTORIAL_BIT(DESTROYER_BIT);
            write("Destroyer Status Set.\n");
            break;
        default:
            write("Usage for testing:\n\n"
                + "\t<status null>   - clear status\n"
                + "\t<status good>   - set status to savior\n"
                + "\t<status evil>   - set status to destroyer\n\n");
            if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
            {
                write("Current status: Destroyer.\n");
            }
            else if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
            {
                write("Current status: Savior.\n");
            }
            else
            {
                write("Current status: None.\n");
            }
            break;
    }

    return 1;
} /* do_modify */


/*
 * Function name:        try_item
 * Description  :        checks to see if an item already exists
 *                       within a given object, and if it does not, it 
 *                       then adds it as add_item() would.
 * Arguments    :        mixed names --  string or array of strings, the
 *                                       item name(s).
 *                       mixed desc -- string or function, the description.
 * Returns      :        int -- the number of items added
 */
public int
try_item(mixed names, mixed desc)
{
    int         i;
    string      *exists;

    if (pointerp(names)) 
    { 
        exists = ({});
        for (i = 0; i < sizeof(names); i++) 
        {
            if (item_id(names[i])) 
            {
                exists += ({ names[i] });
            }
        }
        names -= exists;
        if ((i = sizeof(names)))
        {
            add_item(names, desc);
        }
    } 
    else if (!this_object()->item_id(names))
    {
        add_item(names, desc);
        i = 1;
    }
    return i;   /* # of items added */
} /* try_item */


/*
 * Function name:        add_outdoor_items
 * Description  :        add_items that describe things present in
 *                       just about any outdoor room in Silverdell
 */
public void
add_outdoor_items()
{
    try_item( ({ "sky", "up", "blue sky" }), exa_sky);
    try_item( ({ "cloud", "clouds", "scattered clouds",
                 "puff", "puffs", "puffs of cloud", "filthy cloud",
                 "filthy clouds", "filthy black cloud", "black cloud",
                 "black clouds", "filthy black clouds",
                 "smoke", "dark smoke", "clouds of smoke",
                 "cloud of smoke", "smoke cloud", "dark cloud",
                 "dark clouds", "dark cloud of smoke",
                 "dark clouds of smoke", "twisting clouds",
                 "dark clouds", "twisting cloud", "twisting clouds",
                 "dark and twisting cloud", "dark and twisting clouds",
                 "white cloud", "white clouds" }),
        exa_cloud);
    try_item( ({ "sun", "sunlight", "rays", "rays of warmth",
                 "light", "illumination" }), exa_light);
    try_item( ({ "here", "area", "silverdell", "land", "lands",
                 "region", "domain" }), exa_silverdell);
    try_item( ({ "ground", "down", "floor", "pebble", "pebbles",
                 "dirt", "soil", "earth", "dust" }), one_of_list( ({
        "The ground here is solid beneath your feet.\n",
        "A few pebbles dot the ground, which is otherwise fairly"
      + " plain.\n",
        "You kick a bit at the dirt along the ground, testing the"
      + " earth with your foot.\n" }) ) );
    try_item( ({ "wind", "breeze", "smell", "stench" }), 
        "There is a bit of breeze here in the outdoors.\n");
} /* add_outdoor_items */


/*
 * Function name:        add_road_items
 * Description  :        add_items that describe the road
 */
public void
add_road_items()
{
    try_item( ({ "road", "path", "dirt road", "dirt path", "street",
                 "streets" }),
        one_of_list( ({
        "The road is well-worn, showing numerous ruts and grooves in"
      + " its surface.\n",
        "Dust blows along the road in the occasional breeze.\n",
        "Though the road is rough in places, it looks well used,"
      + " and appears to have been cared for by able hands.\n" }) ) );
    try_item( ({ "rut", "ruts", "groove", "grooves", "depression",
                 "depressions", "surface" }),
        "There are numerous depressions in the road which have been"
      + " caused by rain and the travelling foot and hoof.\n");
} /* add_road_items */


/*
 * Function name:        add_town_items
 * Description  :        try_items for the town streets
 */
public void
add_town_items()
{
    try_item( ({ "town", "small town", "village", "small village",
                 "greenhollow", "area", "quiet town",
                 "quiet village", "town of greenhollow",
                 "village of greenhollow", "greenhollow village" }),
        "Simple and rather rustic buildings run alongside the"
      + " streets of this quiet town. From the look of them, it seems"
      + " clear that the residents of Greenhollow experience few, if any,"
      + " real hardships.\n");
    try_item( ({ "buildings", "building", "rustic building",
                 "rustic buildings", "simple building",
                 "simple buildings", "shop", "shops" }),
        "The buildings which line the streets of Greenhollow are"
      + " a statement to the simple and peaceful lives of the"
      + " townsfolk. The doors contain no locks and the"
      + " architecture is simple and unassuming.\n");
    try_item( ({ "roof", "roofs", "rooftop", "rooftops" }),
        "The buildings of Greenhollow are layered with thick"
      + " cedar shingles which have greyed over time and gleam"
      + " in the bright sunlight.\n");
    try_item( ({ "architecture", "doors", "door", "lock", "locks" }),
        "Everything about the architecture of Greenhollow speaks of"
      + " simplicity and ease. This must truly be a joyful place to"
      + " call home.\n");
} /* add_town_items */

/*
 * Function name:        prevent_attacks
 * Description  :        Lars has given protection from harm to the town
 *                       of Silverdell, making combat impossible
 */
public void
prevent_attacks()
{
    add_prop(ROOM_M_NO_ATTACK, "Powerful magic prevents combat here.\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "Powerful magic prevents combat"
      + " here.\n");
} /* prevent_attacks */


/*
 * Function name:        add_indoor_items
 * Description  :        generic items for indoor rooms
 */
public void
add_indoor_items()
{
    try_item( ({ "down", "floor", "ground", "board", "boards",
                 "floorboard", "floorboards", "floor board",
                 "floor boards" }),
        "The floorboards gleam with a beautiful finish.\n");
    try_item( ({ "finish", "beautiful finish", "oil finish" }),
        "The caretaker of this establishment certainly takes good"
      + " care of the place. Even the floorboards have been given"
      + " an oil finish.\n");
    try_item( ({ "up", "roof", "ceiling" }),
        "Wooden beams support the ceiling of this building. There are"
      + " no signs of cobwebs or even the odd spider. Clearly, this"
      + " place is well cared for.\n");
    try_item( ({ "beam", "wooden beam", "beams", "wooden beams",
                 "wood beam", "wood beams" }),
        "The beams of wood are dark and aged material. They are quite"
      + " beautiful, actually.\n");
    try_item( ({ "wall", "walls" }),
        "The walls of the room are panelled with knotty pine strips"
      + " which have been polished to a fine sheen.\n");
    try_item( ({ "pine", "strip", "pine strip", "pine strips",
                 "knotty pine", "knotty pine strip",
                 "knotty pine strips", "panel", "panels",
                 "panelling" }),
        "The panelling is tightly fit, and has been carved by expert"
      + " hands. It gives the room a comfortable natural look.\n");
} /* add_indoor_itmes */


/*
 * Function name:        add_window_items
 * Description  :        add items for a window
 */
public void
add_window_items()
{
    try_item( ({ "window", "window pane" }),
        one_of_list( ({
            "Bright sunlight streams in through the open window,"
          + " illuminating the dust particles that dance in the"
          + " room.\n",
            "The window looks onto the street outside. It looks"
          + " as if it has been washed recently.\n",
            "The window is glazed with many small panes which are"
          + " extremely handsome.\n" }) ) );
    try_item( ({ "sunlight", "light", "sun" }),
        "The sun is not visible from indoors. However, generous"
      + " amounts of sunlight stream in through the window.\n");
    try_item( ({ "dust", "particle", "particles", "dust particle",
                 "dust particles", "ray", "rays", "ray of sunlight",
                 "rays of sunlight", "ray of sun", "rays of sun" }),
        "The dust is lit up by the rays of sunlight streaming in"
      + " through the window.\n");
    try_item( ({ "street", "outside", "street outside" }),
        "The street is visible through the window. Occasionally,"
      + " a citizen or traveller will pass by.\n");
} /* add_window_items */


/*
 * Function name:        add_door_items
 * Description  :        add items for a door
 */
public void
add_door_items()
{
    try_item( ({ "door", "doorway" }),
        one_of_list( ({
            "The doorway leads back outside.\n",
            "The doorway is framed by large oak trim boards.\n",
            "The doorway supports a heavy wooden door leading back"
          + " outside.\n" }) ) );
    try_item( ({ "heavy door", "wooden door", "heavy wooden door" }),
        "The door is dark in color, and has been painted "
      + one_of_list( ({ "blue", "red", "brown", "green" }) )
      + ".\n");
} /* add_door_items */


/*
 * Function name:        add_forest_items
 * Description  :        add items for rooms with a view of the forest
 */
public void
add_forest_items()
{
    try_item( ({ "forest", "sterling forest", "wood", "woods",
                 "tree", "trees", "green tree", "green trees",
                 "sterling woods", }),
        exa_forest);
} /* add_forest_items */


/*
 * Function name:        add_river_items
 * Description  :        add items for rooms with a view of the river
 */
public void
add_river_items()
{
    try_item( ({ "river", "silverdell river", "river silverdell",
                 "water", "waters", "ravine", "thorns",
                 "thorn-choked ravine" }), exa_river);
} /* add_river_items */


/*
 * Function name:        add_mountain_items
 * Description  :        add items for rooms with a view of the mountains
 */
public void
add_mountain_items()
{
    try_item( ({ "mountain", "mountains", "peak", "peaks",
                 "mountain peaks", "mountain peak" }), exa_mountains);
} /* add_door_items */


/*
 * Function name:        add_cliffs_items
 * Description  :        add items for rooms that are in the cliffs
 */
public void
add_cliffs_items()
{
    try_item( ({ "road", "trail", "path", "down", "ground" }),
        "The trail is not as well worn here as it was on the road."
      + " It is somewhat narrow, and carefully navigates the somewhat"
      + " treacherous terrain of these cliffs.\n");
    try_item( ({ "cliff", "cliffs" }),
        "You are travelling among the cliffs here. They loom both"
      + " above and below you, and always rise to the west.\n");
    try_item( ({ "rock", "rocks", "rock wall", "slope", "slopes",
                 "steep slope", "steep slopes", "rock walls" }),
        "The steep slopes of the cliffs are comprised of rock walls"
      + " which rise in most cases several hundred feet or more before"
      + " levelling off at some unseen plateau.\n");
    try_item( ({ "mountain", "mountains", "peak", "peaks",
                 "mountain peaks", "mountain peak" }),
        exa_mountains(1));
} /* add_cliffs_items */


/*
 * Function name:        exa_sky
 * Description  :        provide a bit-dependant description for an
 *                       add_item
 * Returns      :        string - the appropriate description
 */
public string
exa_sky()
{
    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return one_of_list( ({
        "The sky above is dark and foreboding with occasional black"
      + " clouds drifting past.\n",
        "Filthy black clouds hang over the sky, allowing little if"
      + " any sunlight to filter down to the ground.\n",
        "The sky is a dark grey, coiled with dark and twisting"
      + " clouds of black smoke.\n" }) );
    }

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        return "The sky above is brilliantly blue, echoing the health"
          + " and vibrancy which has come to all of Silverdell. Warm"
          + " sunshine beams down through shimmering white clouds to"
          + " cheer your worthy heart.\n";
    }

    return one_of_list( ({
        "Though blue and beautiful, the sky overhead is occasionally"
      + " darkened by dark and foreboding clouds which drift past.\n",
        "The dim sunlight peers through a few dark clouds, sending rays"
      + " of slight warmth down around the area.\n",
        "The deep blue of the sky is somewhat spoiled by dark clouds"
      + " of what appears to be smoke.\n" }) );
} /* exa_sky */


/*
 * Function name:        exa_cloud
 * Description  :        provide a bit-dependant description for an
 *                       add_item
 * Returns      :        string - the appropriate description
 */
public string
exa_cloud()
{
    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        return "The clouds which dot the sky are white and beautiful."
          + " They calm your senses as they drift lazily past.\n";
    }

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return "Filthy and dreadful clouds of black smoke completely"
          + " cover the sky. You grin to yourself, knowing the part"
          + " you have played in ruining these lands.\n";
    }

    return "A few dark clouds of smoke drift across the sky, partially"
      + " blotting out the light of the sun. There is something ominous"
      + " about these clouds.\n";
} /* exa_cloud */


/*
 * Function name:        exa_light
 * Description  :        provide a bit-dependant description for an
 *                       add_item
 * Returns      :        string - the appropriate description
 */
public string
exa_light()
{
    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        return "The sun shines brightly in the sky. Once in a while, a"
          + " cloud will drift in front of it, giving a bit of shade.\n";
    }

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return "The sun has been completely obscured by the dark"
          + " clouds of smoke which boil through the sky overhead.\n";
    }

    return "The light which falls across the land is somewhat dim. The"
      + " dark clouds overhead partially block its efforts to illuminate"
      + " the area.\n";
} /* exa_light */


/*
 * Function name:        exa_silverdell
 * Description  :        provide a bit-dependant description for an
 *                       add_item
 * Returns      :        string - the appropriate description
 */
public string
exa_silverdell()
{
    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        return "Thanks to you, Silverdell is a land of beauty and"
          + " opportunity once more. You pause a moment to take in the"
          + " ambiance.\n";
    }

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return "Thanks to you, Silverdell is a land of gloom and"
          + " despair. You chuckle to yourself, thinking how easy it"
          + " was to achieve such widespread devastation.\n";
    }

    return "Silverdell is a land of uncertainty these days. There is a"
      + " sense of potential for both good or terrible evil to befall"

      + " these lands, perhaps at your hands.\n";
} /* exa_silverdell */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("A hint? Here are some general tips at least. Be sure to make"
      + " maps as you explore. If you do get lost, you can always use your"
      + " <home> command to get back to the hillside.\n");
 
    return 1;
} /* hint */


/*
 * Function name:        exa_forest
 * Description  :        provide a bit-dependant description for an
 *                       add_item
 * Returns      :        string - the appropriate description
 */
public string
exa_forest()
{
    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        return "The Sterling Woods are visible in the distance to"
          + " the east. Sunlight shines down on the shimmering"
          + " treetops, which stand majestically against the"
          + " horizon. Redeemed by your good deeds, the forest is"
          + " now a place of beauty and tranquility.\n";
    }

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return "The twisted and barren trunks which now comprise the"
          + " Sterling Woods are visible against the bleak horizon"
          + " in the distance. Bereft of all natural beauty, the"
          + " forest has become a place of terror and death.\n";
    }

    return "The tall green trees of the Sterling Woods are visible"
      + " in the distance to the east. Though beautiful and rather"
      + " majestic, the forest is a place of uncertainty and danger"
      + " these days.\n";
} /* exa_forest */


/*
 * Function name:        exa_river
 * Description  :        provide a bit-dependant description for an
 *                       add_item
 * Returns      :        string - the appropriate description
 */
public string
exa_river()
{
    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        return "The Silverdell River flows peacefully along some"
          + " distance to the east. Even from here, you can see"
          + " the sunlight glinting off the now pure and crystal"
          + " clear waters - yet another reminder of your redemption"
          + " of these troubled lands.\n";
    }

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return "A thorn-choked ravine is all that remains of the"
          + " once beautiful Silverdell River. To the east, you can"
          + " see its length tracing the land like a great black"
          + " scar.\n";
    }

    return "A ways to the east you can see glimpses of the Silverdell"
      + " River. Though not as pure as they once were, its waters are"
      + " yet an important asset to these lands, offering vitality"
      + " to the plants and animals along its length.\n";
} /* exa_river */


/*
 * Function name:        exa_mountains
 * Description  :        provide a bit-dependant description for an
 *                       add_item
 * Arguments    :        int cliffs - true only if this is called
 *                                    from a cliffs room. default
 *                                    is 0.
 * Returns      :        string - the appropriate description
 */
public string
exa_mountains(int cliffs = 0)
{
    string  extra = "\n";

    if (cliffs)
    {
        extra = " Here among the cliffs, the mountains are closer"
          + " than ever.\n";
    }

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        return "Now free from the influence of Baron von Krolock,"
          + " the mountains are majestic and beautiful to behold."
          + " They frame the western skyline with their mighty"
          + " peaks." + extra;
    }

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return "With Baron von Krolock now in control of these lands,"
          + " the mountains positively glow with malevolent evil."
          + " Ghastly clouds of black smoke pour from their peaks,"
          + " covering all the land in darkness." + extra;
    }

    return "Looming over the landscape to the west, the mountains have"
      + " a look of malevolence to them. Dark, smoke-like clouds drift"
      + " occasionally across the sky from the direction of their"
      + " gloomy peaks." + extra;
} /* exa_mountains */


/*
 * Function name:        query_instance_id
 * Description  :        Get the instance number for a player
 */
public int
query_instance_id(object player)
{
    if (instance_id > 0)
        return instance_id;
    return (TUTORIAL_DIR + "instance_master")->get_instance(player);
} /* query_instance_id */


/*
 * Set the instance number for this room
 */
public void
set_room_instance(int id)
{
    instance_id = id;
} /* set_room_instance */


/*
 * Get the instance number for this room
 */
public int
query_room_instance()
{
    return instance_id;
} /* query_room_instance */


/*
 * This is where the work is done.
 * Override standard room loading.
 */
object
load_room(int index)
{
    string file;
    object room, instance;
    function f;
    int x = -1;

    room = load_room_clone(index);
    //dump_array(room);

    if (!objectp(room))
        return room;

    file = MASTER_OB(room);

    if (instance_rooms[file])
        return instance_rooms[file];

    if (this_player()->query_leader())
    {
        while (calling_function(x))
        {
            if (calling_function(x) == "follow_leader")
            {
                (TUTORIAL_DIR + "instance_master")->follow(this_player());
                break;
            }
            x--;
        }
    }

    //instance = room->query_instance(query_instance_id(this_player()));
    instance = room->query_instance(this_player());

    if (instance_id != instance->query_room_instance())
        write("Reality trembles slightly as you move in that direction.\n");

    /* If this is an ordinary exit just let the player leave */
    if (!objectp(instance))
        return room;
    
    return instance;
} /* load_room */

/*
 * Return or clone the room for an instance id
 */  
object
//query_instance(int id)
query_instance(object player)
{
    object room;
    int id;

    if (instance_entrance)
        return this_object();
    
    if (instance_id > 0)
        id = instance_id;
    else
        id = query_instance_id(player);
    if (instance_rooms[id])
        return instance_rooms[id];

    room = clone_object(file_name(this_object()));
    room->set_room_instance(id);
    instance_rooms[id] = room;
    
    return room;
} /* query_instance */

/*
 * This is a replacement for this_player->move_living, taking account of 
 * instances. Arguments same as move_living.
 */
varargs int
moveto(string how, mixed to_dest, int dont_follow, int no_glance)
{
    object room = to_dest;
    int inst = query_instance_id(this_player());
    if (instance_id != inst)
        write("Reality trembles slightly.\n");
    this_player()->move_living(how,
//        room->query_instance(inst), dont_follow,
        room->query_instance(this_player()), dont_follow,
        no_glance);
} /* moveto */
