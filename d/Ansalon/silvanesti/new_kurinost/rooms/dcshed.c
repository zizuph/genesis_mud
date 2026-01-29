/*
 * dcshed.c
 *
 * Draconian camp  -  a small wooden shed.
 *
 * Copyright (C): Kellon, september 2012
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "local.h"

inherit INSIDEBASE;

// G L O B A L   V A R S
status gDoor_open = 0, gDoor_locked = 1;
object gSatchel, gDocument;
status gDocs_taken = 0;


// P R O T O T Y P E S
public string show_light();
public string show_longdesc();
public string show_shed();
public string show_window();
public string show_floor();
public string show_hole();
public string show_tower();
public int open_door();
public int unlock_door();
public int pick_lock();
public string search_hole(object who, string what);
public int set_search_time();
public void setup_tells();


// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_kurinost_room
 *  Arguments: None
 *  Returns  : Void
 * 
 *  create_room function that sets up descriptions and exits.
 *
 */
public void
create_kurinost_room()
{
    set_short("Small wooden shed");
    set_long(show_longdesc);

    add_item(({ "shed", "wooden shed", "small wooden shed",
        "small shed" }), show_shed);
    add_item(({ "walls", "wall" }), "Protesting loudly under the " +
        "pressure of weight, the walls of this small wooden shed " +
        "might not last much longer. Already several boards in " +
        "the southern end of the shed seem to be bending slightly " +
        "under the preassure. Crudely built with irrregular " +
        "wooden boards, that seems to be nothing more than thick " +
        "branches split in half down the middle, it seems obvious " +
        "that the builders did not have comfort in mind when they " +
        "built this shed.\n");
    add_item("ceiling", "Squarely set in the middle of the " +
        "ceiling is the only window in the shed, which is flanked " +
        "by two old shutters on half-broken hinges. The rest of " +
        "the ceiling is made up of the same wooden boards as the " +
        "rest of the shed.\n");
    add_item(({ "window", "shutters", "crude shutters" }),
        show_window);
    add_item(({ "door", "floor", "doorframe" }), show_floor);
    add_item(({ "hole", "gaping hole" }), show_hole);
    add_item(({ "boards", "branches", "wooden boards",
        "irregular boards", "irregular wooden boards",
        "thick branches" }), "Crude and irregular branches have " +
        "been split down the middle to create the boards that has " +
        "been used to create this shed. Protesting loudly under " +
        "the preassure of weight from the garbage pile ouside, " +
        "the shed was obviously not created to be strong and long " +
        "lasting.\n");
    add_item(({ "crack", "cracks", "large crack", "large cracks",
        "particular large cracks" }), "Irregular boards were used " +
        "to build this small shed and some of them are so " +
        "mismatching, that holes of various sizes appear in the " +
        "walls, the floor and the ceiling.\n");
    add_item(({ "garbage", "pile", "garbage pile" }), "Even " +
        "though you cannot see the garbage pile from here, you " +
        "can certainly smell it and you can hear the small wooden " +
        "shed groaning under the stress of the added weight from " +
        "the south side.\n");
    add_item(({ "tower", "slender tower", "slender white tower" }),
        show_tower);

    add_cmd_parse("[the] 'door' [with] [the] [small] [rusty] [iron] [key]",
        "unlock", unlock_door);

    add_cmd_parse("[the] 'lock' [on] [the] [door] [in] [the] [floor]",
        "pick", pick_lock);

    add_cmd_item(({ "door", "the door" }), "open", open_door);

    add_search(({ "hole", "gaping hole" }), set_search_time,
        "search_hole", 1);

    // We need to be able to clone stuff here, so set up the ID's.
    setuid();
    seteuid(getuid());

    setup_tells();
    KURINOSTMAP;
    
    add_exit(RSROOMS + "dcamp4x4", "out");
}


/*
 *  FUNCTION : reset_kurinost_room
 *  Arguments: None
 *  Returns  : Void
 * 
 *  Reset room functions. Close the door if it has been opened.
 *
 */
public void
reset_kurinost_room()
{
    // If the door has been opened, close and lock it!
    gDoor_open = 0;
    gDoor_locked = 1;

    // If someone has already taken the documents out of the hole,
    // we need to reset it for other players.
    gDocs_taken = 0;
}


/*
 *  FUNCTION : init
 *  Arguments: none
 *  Returns  : void
 * 
 *  Reset players actions in this room.
 *
 */
public void
init()
{
    ::init();
}


/*
 *  FUNCTION : set_search_time
 *  Arguments: None
 *  Returns  : Int - the search time.
 * 
 *  Returns the time it will take to search the hole.
 *
 */
public int
set_search_time()
{
    if (!gDoor_open)
    {
        return -4;
    }

    return 0;
}


/*
 *  FUNCTION : search_hole
 *  Arguments: None
 *  Returns  : string - description of what player finds.
 * 
 *  Handles the search command, search hole.
 *
 */
public string
search_hole(object who, string what)
{
    object *satchel;

    if (!gDoor_open)
    {
        // The door is not open, so lets search some other holes.
        return "There are too many small holes in the small " +
            "wooden shed to search all at once.\n";
    }

    if (gDoor_open)
    {
        // Has the player already found the satchel and
        // has it in inventory?
        satchel = filter(all_inventory(who), &->id(DC_SATCHEL));

        // Player has the satchel or someone took the satchel recently.
        // Not making a new one!
        if (sizeof(satchel) || gDocs_taken)
        {
            say(QCTNAME(who) + " steps down through the doorframe " +
                "and into the hole beneath the small wooden shed. " +
                "After searching around for a few moments, " +
                HE(who) + " climbs up out of the hole.\n");

            return "Stepping down through the doorframe and into " +
                "the garbage under the small wooden shed, you " +
                "quickly look around. Besides some nasty looking " +
                "broken weapons that you decide to leave in the " +
                "garbage, you find nothing useful and you climb " +
                "back out of the hole.\n";
        }

        // Player did not have the satchel, so lets make
        // him/her a new one.
        say(QCTNAME(who) + " steps down through the doorframe and " +
            "into the hole beneath the small wooden shed. After " +
            "searching around for a few moments, " + HE(who) +
            " picks something up and climb up out of the hole.\n");

        gSatchel = clone_object(RSOBJS + "dc_satchel");
        gDocument = clone_object(RSOBJS + "dc_document");

        gDocument->move(gSatchel, 1);
        gSatchel->move(TP, 1);

        gDocs_taken = 1;

        return "Stepping down through the doorframe and into the " +
            "garbage under the small wooden shed, you quickly " +
            "look around. Well hidden beneath a nasty looking " +
            "broken chainmail, you find a " + gSatchel->short() +
            ". You lift it out of the garbage.\n";
    }
}


/*
 *  FUNCTION : open_door
 *  Arguments: None
 *  Returns  : int - 0/1 - did we succeed in handling the action?
 * 
 *  Handles the command, open door
 *
 */
public int
open_door()
{
    if (gDoor_open)
    {
        NF("Smashed and broken, the door lies next to the " +
            "doorframe on the floor. It is not possible to open " +
            "it any further.\n");

        return 0;
    }

    if (gDoor_locked)
    {
        write("You pull at the doorknob, but the door does not move. " +
            "It appears to be locked.\n");

        return 1;
    }
    
    write("Tugging at the doorknob, you try to open the door, but " +
        "it is stuck! Maybe the doorframe has been twisted too " +
        "much, jamming the door in place.\nSetting your feet " +
        "firmly against the doorframe, you tug as hard as you can " +
        "on the door. Groaning under the strain, the door finally " +
        "comes loose and smashes open! Violently, it breaks off, " +
        "hinges flying left and right and the door lands in a " +
        "half-broken heap next to the doorframe.\n");

    say(QCTNAME(TP) + " tugs hard at the doorknob, but the door " +
        "does not open. Setting " + HIS(TO) + " legs firmly " +
        "against the doorframe, " + HE(TO) + " pulls as hard as " +
        HE(TO) + " can and finally in a rush of movement, the " +
        "door flies open and breaks apart. The door lands in a " +
        "half-broken heap on the floor next to the doorframe.\n");

    gDoor_open = 1;

    return 1;
}


/*
 *  FUNCTION : show_light
 *  Arguments: None
 *  Returns  : String - the description.
 * 
 *  Returns a word that shows the light that is reflected from
 *  the elven tower.
 *
 */
public string
show_light()
{
    switch (GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
        case TOD_TWILIGHT:
            return "moonlight";

        case TOD_DAWN:
        case TOD_DAY:
            return "sunlight";
    }
}


/*
 *  FUNCTION : unlock_door
 *  Arguments: None
 *  Returns  : Int - 0/1 - did we succeed in solving the command?
 * 
 *  Handles the added action, unlock door.
 *
 */
public int
unlock_door()
{
    object *temp_key;
    object first_key;

    if (gDoor_open)
    {
        NF("The door is already lying open on the floor with a " +
            "key stuck fast in the keyhole. You cannot unlock it " +
            "any further.\n");

        return 0;
    }


    temp_key = filter(all_inventory(TP), &->id(DC_KEYNAME));

    if (sizeof(temp_key))
    {
        first_key = temp_key[0];

        write("Inserting the " + first_key->short() + " into the " +
            "keyhole, you try to turn it gently. Click!\n\nYou " +
            "managed to unlock the door without breaking the key. " +
            "Pulling gently on the " + first_key->short() + " does " +
            "nothing, however. It appears to be stuck quite " +
            "firmly inside the lock. After pulling at it a few " +
            "times you finally have to give up getting it back.\n");

        say(QCTNAME(TP) + " inserts a " + first_key->short() +
            " into the keyhole of the door and turns it gently. " +
            "Click!\n");

        first_key->remove_object();
        gDoor_locked = 0;

        return 1;
    }

    NF("Unlocking the door without the proper key does not seem " +
        "possible. Having been soaked down into the garbage pile, " +
        "the lock seems very rusty and dirty.\n");

    return 0;
}


/*
 *  FUNCTION : pick_lock
 *  Arguments: None
 *  Returns  : int 0/1 - did we succeed in handling the command?
 * 
 *  Handles the added action, pick the lock on the door.
 *
 */
public int
pick_lock()
{
    // Return a description of why the lock cannot be picked and
    // then finish off the command by returning 1.
    write("Unlocking the door without the proper key does not seem " +
        "possible. Having been soaked down into the garbage pile, " +
        "the lock seems very rusty and dirty and any attempt to " +
        "tamper with the lock will surely damage it.\n");

    return 1;
}


/*
 *  FUNCTION : show_shad
 *  Arguments: none
 *  Returns  : string - the description.
 * 
 *  Returns a description of the shed.
 *
 */
public string
show_shed()
{
    string add_desc = "";

    if (gDoor_open)
    {
        add_desc = "Lying broken on the floor, next to a gaping " +
            "hole, is the remains of a door. ";
    }

    return "Creaking and groaning loudly under the weight of the " +
        "garbage pile outside, the small wooden shed might not " +
        "last much longer. Already several of the boards holding " +
        "it together seem to be bending under the pressure, as " +
        "the garbage pile leans down over the shed from the " +
        "southern side. Crudely built with irregular wooden " +
        "boards, that seems to be nothing more than some thick " +
        "branches split in half down the middle, it seems obvious " +
        "that the builders of the shed did not have comfort in " +
        "mind. " + add_desc + "In several places, in the walls, " +
        "the floor and in the ceiling, the boards match so badly " +
        "that you could get a hand through a few of the larger " +
        "cracks.\n";
}


/*
 *  FUNCTION : show_floor
 *  Arguments: None
 *  Returns  : string - the description.
 * 
 *  Returns a description of the floor.
 *
 */
public string
show_floor()
{
    if (gDoor_open)
    {
        return "As you look across the small shed, you quickly " +
            "notice the broken and battered door and the hole in " +
            "the floor! Broken and useless, the door lies on the " +
            "floor next to a gaping hole that used to be the " +
            "doorframe. Obviously the door must have been torn " +
            "out of its frame with some force.\n";
    }

    return "As you look across the small shed, you quickly notice " +
        "the door. A nice wooden doorframe and a decent door with " +
        "nicely matching boards and a small doorknob and keyhole. " +
        "The only problem is that the door is in the floor and " +
        "not in any of the walls! Opening it, would turn it up " +
        "into the room.\n";
}


/*
 *  FUNCTION : show_longdesc
 *  Arguments: None
 *  Returns  : String - the description
 * 
 *  Returns the long description of the room.
 *
 */
public string
show_longdesc()
{
    return "Only lit by the reflected " + show_light() + " from " +
        "the slender white tower seen through the window in the " +
        "ceiling, this small wooden shed is shrouded in shadows, " +
        "much like the camp outside. Irregular wooden boards have " +
        "been used in the construction of every part of the shed, " +
        "the walls, the floor and ceiling. The only obvious way " +
        "out seems to be the window in the ceiling.\n";
}


/*
 *  FUNCTION : show_window
 *  Arguments: None
 *  Returns  : string - the description.
 * 
 *  Returns a description of the window in the ceiling.
 *
 */
public string
show_window()
{
    return "Faint reflected " + show_light() + " seep through the " +
        "window in the ceiling into the small wooden shed, barely " +
        "lighting up the interior. Crude shutters on rusty hinges " +
        "are attached to the inside of the ceiling, one of them " +
        "dangling half-broken and useless down, next to the " +
        "window.\n";
}


/*
 *  FUNCTION : show_tower
 *  Arguments: none
 *  Returns  : string - the description.
 * 
 *  Description of the tower with reflected light.
 *
 */
public string
show_tower()
{
    return "Rising high above you, the slender white tower is " +
        "visible through the window in the ceiling of the small " +
        "shed. Reflecting the " + show_light() + " from the sky, " +
        "it is the only light that seems to enter this dark shed.\n";
}


/*
 *  FUNCTION : show_hole
 *  Arguments: none
 *  Returns  : string - the description.
 * 
 *  Returns a description of the hole in the floor, if it is there.
 *
 */
public string
show_hole()
{
    if (gDoor_open)
    {
        return "As you look across the small shed, you quickly " +
            "notice the broken and battered door and the hole in " +
            "the floor! Broken and useless, the door lies on the " +
            "floor next to a gaping hole that used to be the " +
            "doorframe. Obviously the door must have been torn " +
            "out of its frame by some force. Garbage fills the " +
            "hole, as if the shed had been built on top of the " +
            "garbage pile outside.\n";
    }

    return "You find no hole, except from the small cracks in the " +
        "irregular boards of the shed and the window in the " +
        "ceiling.\n";
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
    set_tell_time(450);

    add_tell("Creaking with stress under the pressure of weight, " +
        "the small wooden shed seems to shift in position. " +
        "Somehow the walls manages to hold the weight.\n");
    add_tell("A silent breeze carries the stench of garbage piles " +
        "from the outside of the small wooden shed.\n");
    add_tell("Piercing the thick air of the camp, the scream from " +
        "a dying hobgoblin is followed by the hoarse laughter of " +
        "draconians.\n");
    add_tell("Shadows move about in the small wooden shed, as a " +
        "cloud passes over the window in the ceiling, momentarily " +
        "blocking out the fainy light.\n");
    add_tell("Gunk! Gunk! Falling heavily, something lands on the " +
        "ceiling of the small wooden shed.\n");
}

