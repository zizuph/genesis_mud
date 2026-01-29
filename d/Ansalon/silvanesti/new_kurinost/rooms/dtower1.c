/*
 * dtower1.c
 *
 * Entrance to the broken elven tower near Kurinost 
 *
 * Copyright (C): Kellon, june 2013
 *                Poul Erik Jensen
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "local.h"
#include "/d/Krynn/guilds/wohs/defs.h"

// I N H E R I T E D   F I L E S
inherit INSIDEBASE;

// D E F I N I T I O N S
#define FOUND_THE_KEY "_kurinost_found_the_cabinet_key"

// G L O B A L   V A R S
int gTorch = 1;
int gMural_dusted = 0;
int gKey_found = 0;
string gDefacing = ONE_OF(({ "a huge black mustache on his face",
                "two great horns on his forehead",
                "large black fangs in his mouth",
                "a huge curly black hair and bushy eyebrows on his head",
                "a long black necktie around his throat",
                "a large smoking cigar in his mouth" }));

// P R O T O T Y P E S
public string show_longdesc();
public string show_tower();
public string show_floor();
public string search_floor(object who, string what);
public string show_entrance();
public string show_walls();
public string show_darkspot();
public int dust_mural();
public string show_mural();
public string show_sconce();
public string show_torch();
public void setup_tells();
public int leave_tower();
public int climb_stairs();
public string get_torch_from_sconce();
public string cast_detect_magic();

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : reset_kurinost_room
 *  Arguments: none
 *  Returns  : void
 * 
 *  Reset the room.
 *
 */
public void
reset_kurinost_room()
{
    gTorch = 1;
    gKey_found = 0;

    if (gMural_dusted)
    // if someone dusted the mural, only change the defacing
    // and cover it with dust on a 50% chance.
    {
        gMural_dusted = random(2);

        if (!gMural_dusted)
        {
            gDefacing = ONE_OF(({ "a huge black mustache on his face",
                "two great horns on his forehead",
                "large black fangs in his mouth",
                "a huge curly black hair and bushy eyebrows on his head",
                "a long black necktie around his throat",
                "a large smoking cigar in his mouth" }));
        }
    }
}


/*
 *  FUNCTION : create_kurinost_room
 *  Arguments: none
 *  Returns  : void
 * 
 *  Create the room.
 *
 */
public void
create_kurinost_room()
{
    set_short("the ruined entrance to an elven tower");
    set_long(show_longdesc);

    add_item(({ "tower", "broken tower", "room", "elven tower" }), 
        show_tower);
    add_item(({ "floor", "dust", "soot" }), show_floor);
    add_item(({ "entrance", "tower entrance", "ruined entrance" }), 
        show_entrance);
    add_item(({ "wall", "walls" }), show_walls);
    add_item(({ "spot", "dark spot", "large spot", "northern wall",
        "north wall", "large dark spot" }), show_darkspot);
    add_item(({ "sconce", "iron sconce", "rusty sconce",
        "rusty iron sconce" }), show_sconce);
    add_item(({ "torch", "small torch" }), show_torch);
    add_item(({ "mural", "painting" }), show_mural);

    add_item(({ "markings", "faint marking", "footprints" }),
        "Examining the faint markings more closely, you quickly " +
        "identify them as footprints leading from the entrance to " +
        "the staircase and back. You are unable to find similar " +
        "footprints in the rest of the entrance room.\n");
    add_item(({ "rubble", "pile", "pile of rubble", "eastern wall",
        "broken floortiles", "floortiles", "burned wood", "wood",
        "burnt wooden poles", "wooden poles", "poles", "wall blocks",
        "blocks" }), "Scattered " +
        "about on the floor, you find several piles of rubble " +
        "under a thick layer of dust and soot. Mostly the piles " +
        "seem to contain remains of broken floortiles, wall " +
        "blocks and burned wood.\n");
    add_item(({ "staircase", "dark staircase" }), "The entire " +
        "entrance room of the tower seems have been expertly " +
        "crafted to hide a staircase that leads from this lower " +
        "room up towards the top of the tower. Viewed from the " +
        "outside, the tower is perfectly round, but seen from in " +
        "here, it is slightly oblong, crafted to make room for " +
        "the staircase behind the eastern wall.\n");
    add_item(({ "door", "broken hinges", "hinges",
        "splintered remains" }), "Broken hinges mounted on the " +
        "wall at the entrance seems to suggest that there might " +
        "have been a door in the tower, but all you find are a " +
        "few splintered wooden remains.\n");

    // Calls to add_search will have stime increased by +5 seconds.
    // searching the floor takes 8 seconds.
    add_search(({ "floor", "dust", "soot" }), 3, "search_floor", 1);
    add_search(({ "mural", "painting" }), 3, "search_mural", 1);


    add_cmd_parse("[off] [the] [large] [dark] 'spot' / 'mural' / 'wall' ",
        ({ "dust", "clean" }), dust_mural);
    add_cmd_parse("[the] [small] 'torch' [from] [the] [sconce]",
        ({ "get", "take"}), get_torch_from_sconce);
    add_cmd_parse("'ickrakarcanis' [on] [the] 'mural' / 'painting' ",
        "cast", cast_detect_magic);

    add_exit(RSROOMS + "dcamp2x3", "out", leave_tower, 3);
    add_exit(RSROOMS + "dtower2", "up", climb_stairs, 5);

    setuid();
    seteuid(getuid());

    setup_tells();
    KURINOSTMAP;

    reset_room();
}


/*
 *  FUNCTION : show_light
 *  Arguments:
 *  Returns  :
 * 
 *  Returns a string with the light that enters the tower.
 *
 */
public string
show_light()
{
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
        return "pale moonlight";

    case TOD_DAWN:
        return "faint sunlight";

    case TOD_DAY:
        return "glittering sunlight";

    case TOD_TWILIGHT:
        return "fading sunlight";
    }
}


/*
 *  FUNCTION : get_torch_from_sconce
 *  Arguments: none
 *  Returns  : string - what to tell the player when s/he takes
 *                      the torch.
 * 
 *  Handles the command to get the torch.
 *
 */
public string
get_torch_from_sconce()
{
    object small_torch;

    if (gTorch)
    {
        small_torch = clone_object(RSOBJS + "small_torch");
        small_torch->light_me();
        small_torch->move(TP, 1);

        say(QCTNAME(TP) + " reaches up and takes the small " +
            "burning torch from the rutsy iron sconce.\n");

        gTorch = 0;

        return "Reaching up, you take the small burning torch " +
            "from the rusty iron sconce on the northern wall.\n";
    }
    else
    {
        return "Take what? The rusty iron sconce is empty.\n";
    }
}

public string
search_mural(object who, string what)
{
    object key;

    if(who->query_prop(FOUND_THE_KEY) && (gKey_found == 0))
    {
        setuid();
        seteuid(getuid());

        key = clone_object(RSOBJS + "cabinet_key");
        key->move(who, 1);  
        who->remove_prop(FOUND_THE_KEY);
        gKey_found = 1;

        say(QCTNAME(who) + " thoroughly searches the mural on the " +
            "northern wall, and seems to have found something!\n");      
        return "You thoroughly search the mural hanging on the northern " +
            "wall, and manage to find a delicate crystal key sewn cunningly " +
            "near where the hilt of the noble elf's sword is. You pull it " +
            "out.\n";
    }

    say(QCTNAME(who) + " thoroughly searches the mural on the northern " +
        "wall, but does not find anything.\n");
    return "After a long and careful search of the mural, " +
        "you do not find anything of interest.\n";
}

void
detect_magic(object caster)
{
    if(gKey_found)
    {
        write("You do not detect any magical properties on the mural.\n");
        return;
    }

    write("The mural glows briefly with a faint blue aura, near the hilt " +
        "of the noble elf's sword, indicating something hidden behind the " +
        "mural has magical properties.\nIt would be worth searching the " +
        "mural to see if you can discover the item causing the glow.\n");
    say("The mural on the northern wall glows briefly with a faint blue " +
        "aura.\n");
    caster->add_prop(FOUND_THE_KEY, 1);
}

public string
cast_detect_magic()
{
    if(!WOHS_MANAGER->query_memorised_spell(TP,"ickrakarcanis_memorised") &&
       !TP->query_wiz_level())
    {
        return 0;
    }

    write("You open your hands wide and slowly move them over the " +
        "mural on the northern wall while chanting 'ickrak arcanis'.\n");
    say(QCTNAME(TP) + " opens " + TP->query_possessive() + 
        " hands wide and slowly moves them over the mural on the northern " + 
        "wall while chanting words of magic.\n");

    set_alarm(3.5, 0.0, &detect_magic(TP));

    return "";
}


/*
 *  FUNCTION : show_longdesc
 *  Arguments: None
 *  Returns  : String - the description.
 * 
 *  Show the longdescription of the room, based on time of day.
 *
 */
public string
show_longdesc()
{
    string entrance_light;

    if (gTorch)
    {
        entrance_light = "Soft flickering light from a small " +
            "burning torch";
    }
    else
    {
        entrance_light  = show_light() + " from the entrance";
    }

    return capitalize(entrance_light) + " does little to light up " +
        "this circular entrance of the tower. Black soot and grey " +
        "dust covers the entire floor and walls of this eight " +
        "meter wide circular entrance, and the bleak grey-black " +
        "semi-darkness seems to absorb all light in the room. " +
        "Piled up against the eastern wall, near the staircase, " +
        "you notice rubble from floortiles, parts of stone blocks " +
        "from the broken walls and several burnt wooden poles.\n";
}


/*
 *  FUNCTION : show_tower
 *  Arguments: None
 *  Returns  : String - description of the tower.
 * 
 *  Show the description of the tower room.
 *
 */
public string
show_tower()
{
    string entrance_light;

    if (gTorch)
    {
        entrance_light = "Soft flickering light from a small torch";
    }
    else
    {
        entrance_light  = show_light() + " from the entrance";
    }

    return capitalize(entrance_light) + " does little to light up " +
        "the interior of this slightly oblong lower room of the " +
        "tower. Expertly crafted to hide a staircase behind the " +
        "eastern wall, the interior of this entrance room is " +
        "slightly oblong compared to the outside of the tower. " +
        "Rubble has been piled up near the eastern wall, making " +
        "it difficult to reach the staircase. Covered in black " +
        "soot and grey dust, the entire floor and most of the " +
        "walls absorb the light in room.\n";
}


/*
 *  FUNCTION : show_floor
 *  Arguments: None
 *  Returns  : String - description of the tower.
 * 
 *  Show the description of the floor in the tower room.
 *
 */
public string
show_floor()
{
    string entrance_light;

    if (gTorch)
    {
        entrance_light = "Soft flickering light from a small torch";
    }
    else
    {
        entrance_light  = show_light() + " from the entrance";
    }

    return capitalize(entrance_light) + " does little to light up " +
        "the thick layer of soot and dust on the floor, making it " +
        "somewhat difficult to notice any details. Rubble has " +
        "been piled up in several places, most notably near the " +
        "eastern wall, where a rather large pile of blackened " +
        "wooden logs and rocks block most of the entrance room.\n";
}


/*
 *  FUNCTION : search_floor
 *  Arguments: who/what are passed from the add_search function call.
 *  Returns  : string - description of the floor.
 * 
 *  Searching the floor reveals more info.
 *
 */
public string
search_floor(object who, string what)
{
    say(QCTNAME(who) + " finishes a long and careful search of " +
        "the tower floor.\n");

    return "After a long and careful search of the tower floor, " +
        "you notice some markings in the floor running between " +
        "the tower entrance and the dark staircase behind the " +
        "eastern wall.\n";
}


/*
 *  FUNCTION : show_entrance
 *  Arguments: None
 *  Returns  : String - description of the entrance.
 * 
 *  Show the description of the entrance in the tower room.
 *
 */
public string
show_entrance()
{
    string entrance_light = show_light();

    return capitalize(entrance_light) + " filters through the " +
        "entrance to the tower, but it does little to light up " +
        "the slightly oblong circular room. Entering from the " +
        "south side, you notice a large pile of rubble blocking " +
        "the direct path to a dark staircase leading up behind " +
        "the eastern wall. Broken hinges and splinters of wood " +
        "are the only remains of the door at the entrance.\n";
}


/*
 *  FUNCTION : show_walls
 *  Arguments: None
 *  Returns  : String - description of the walls.
 * 
 *  Show the description of the walls in the tower room.
 *
 */
public string
show_walls()
{
    string entrance_light, show_sconce;

    if (gTorch)
    {
        entrance_light = "Soft flickering light from a small " +
            "burning torch";
        show_sconce = "small burning torch mounted in a rusty " +
            "iron sconce";
    }
    else
    {
        entrance_light  = show_light() + " from the entrance";
        show_sconce = "rusty iron sconce";
    }

    return capitalize(entrance_light) + " does little to light up " +
        "the interior of this lower entrance room of the tower. " +
        "Expertly crafted walls make the room slightly oblong, " +
        "created to hide a dark staircase in the eastern wall " +
        "close to the entrance. Blackened with soot and dust, the " +
        "walls makes it difficult to notice any details about the " +
        "walls, but you manage to find a large dark spot right " +
        "next to a " + show_sconce + " on the north wall.\n";
}


/*
 *  FUNCTION : show_darkspot
 *  Arguments: None
 *  Returns  : String - description of the dark spot.
 * 
 *  Show the description of the dark spot in the tower room.
 *
 */
public string
show_darkspot()
{
    if (gMural_dusted)
    {
        return "Stepping closer to the northern wall, you are " +
            "able to see a very dirty mural hanging on the wall. " +
            "Someone has gone to great lengths to dust off the " +
            "mural, making it visible.\n";
    }
    else
    {
        return "Stepping closer to the northern wall, you are " +
            "certain there is something hanging on the wall, but " +
            "it is entirely covered in soot and dark grey dust. " +
            "It would take some work to dust off the wall to see " +
            "what the dark spot is.\n";
    }
}


/*
 *  FUNCTION : dust_mural
 *  Arguments: None
 *  Returns  : int - did we succeed in finishing the command?
 * 
 *  Returns description of the action of dusting off the mural.
 *
 */
public int
dust_mural()
{
    string add_desc = "After a few moments the room is covered in " +
        "a thick cloud of dust.\nAs the dust settles, you notice " +
        "a large mural on the wall.\n";

    say(QCTNAME(TP) + " takes a deep breath and begins dusting " +
        "off the large dark spot on the northern wall. " + add_desc);
    write("Taking a deep breath, you begin dusting off the large " +
        "dark spot. " + add_desc);

    gMural_dusted = 1;

    return 1;
}


/*
 *  FUNCTION : show_mural
 *  Arguments: None
 *  Returns  : String - description of the mural.
 * 
 *  Show the description of the mural in the tower room.
 *
 */
public string
show_mural()
{
    if (gMural_dusted)
    {
        return "Nearly three by two meters, the wall painting " +
            "shows a very dirty picture of a muscular noble elf " +
            "in a dignified pose, wielding a slender longsword " +
            "victoriously above his head, his foot solidly placed " +
            "on the body of his enemy. Black markings along the " +
            "edges of the mural seems to be burn marks from a " +
            "recent fire that did not really catch. Only the " +
            "edges have been burned. It seems like someone has " +
            "defaced the noble elf, by painting " + gDefacing +
            " with a piece of charcoal.\n";
    }
    else
    {
        return "Covered in a thick layer of dust and black soot, " +
            "you are unable to see any details unless you take " +
            "the time to dust it off properly.\n";
    }
}


/*
 *  FUNCTION : show_sconce
 *  Arguments: None
 *  Returns  : String - description of the sconce.
 * 
 *  Show the description of the sconce in the tower room.
 *
 */
public string
show_sconce()
{
    string torch_desc = "";

    if (gTorch)
    {
        return "Mounted in a simple and very rusty sconce on the " +
            "northern wall, a small burning torch tries to light " +
            "up the soot- and dustcovered room without much " +
            "succes. Made from a flat iron plate, the sconce has " +
            "a 5 cm wide cuplike buttom to hold the torch and a " +
            "short chain at the top that holds the torch away " +
            "from the wall itself.\n";
    }
    else
    {
        return "Hanging unused on the northern wall, you notice a " +
            "simple and very rusty iron sconce. It appears to be " +
            "a simple, flat iron plate with a 5 cm wide cuplike " +
            "hole in the buttom and a short iron chain at the " +
            "top, probably made to hold a torch away from the " +
            "wall.\n";
    }
}


/*
 *  FUNCTION : show_torch
 *  Arguments: None
 *  Returns  : String - description of the torch on the wall.
 * 
 *  Show the description of the torch in the tower room.
 *
 */
public string
show_torch()
{
    if (gTorch)
    {
        return "Mounted in a simple and very rusty sconce on the " +
            "northern wall, a small torch tries to light up the " +
            "soot- and dustcovered room without much succes. Made " +
            "from a flat iron plate, the sconce has a 5 cm wide " +
            "cuplike buttom to hold the torch and a short chain " +
            "at the top that holds the torch away from the wall " +
            "itself.\n";
    }
    else
    {
        return "Looking around in the tower entrance room, you " +
            "are unable to find any torch.\n";
    }
}


/*
 *  FUNCTION : setup_tells
 *  Arguments: none
 *  Returns  : void
 * 
 *  Sets the basic tells of the rocky shores of Silvanesti.
 *
 */
public void
setup_tells()
{
    set_tell_time(400);

    add_tell("Faint wailings of seagulls carry through the " +
        "entrance to the tower.\n");

    add_tell("Pale light from the entrance send streaks of light " +
        "through the dusty air in the tower.\n");

    add_tell("A distant scream from the camp outside carries " +
        "through the tower entrance.\n");

    add_tell("A gentle breeze blows through the entrance, " +
        "carrying the stench of decay and smoke into the tower.\n");
}


/*
 *  FUNCTION : leave_tower
 *  Arguments: none
 *  Returns  : int - 0, always allow move.
 * 
 *  Called when you leave the tower. Show additional description
 *  of the path.
 *
 */
public int
leave_tower()
{
    write("Carefully walking around the piles of rubble, you " +
        "leave the broken tower and step out into the shadow " +
        "of the camp.\n");

    return 0;
}

/*
 *  FUNCTION : climb_stairs
 *  Arguments: none
 *  Returns  : int - 0, always allow move.
 * 
 *  Called when you climb the stairs. Show additional description
 *  of the path.
 *
 */
public int
climb_stairs()
{
    write("Carefully you climb across a large pile of rubble and " +
        "reach the dark staircase behind the eastern wall. You " +
        "climb it towards the top.\n");

    return 0;
}

