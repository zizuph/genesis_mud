// ROOM:  base_side.c

    /*  Calia Domain

    HISTORY

    [99-07-01] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\INNER\GROUND\BASE_SID.DOC].

    PURPOSE

    This is the base for rooms at the sides at the ground level inside the
    Sanctimonian fortress.  The fortress is octagonal; there are 8 rooms at the
    corners, 8 at the sides, and 21 in the interior at this level.  The side
    rooms are dining, storage, or work areas except for the northeast side,
    which is the only door to the outside.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/bog/baseroom";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

// GLOBAL VARIABLES

object Fortress_Door;
string This_Location;

// FUNCTIONS

// Function:  check_door()

/*

Purpose:  check to see if the door mechanism has been successfully released.
The mechanism is a separate object, so all we have to do it query that object.

Arguments:  none.

Returns:  0 if the mechanism has been released (and thus the player may exit),
1 if it has not.

*/

int
check_door()

{

    if (Fortress_Door) return Fortress_Door->query_release();
    else return 1;

}

// Function:  hook_smelled(item)

/*

Purpose:  add smell characteristics to items in the room.

Arguments:  string indicating which item is being smelled.

Returns:  nothing.

*/

void
hook_smelled(string item)

{

    switch (item)

    {

        case "salt":
        case "bin":
        case "bins":

        write("You detect a sweet fragrance under the piquant" +
            " aroma of the salt.\n");

        break;

        case "smoke":
        case "crucible":

        write("The smoke has a spicy aroma, and it would likely be" +
            " pleasant if a bit were wafted in your direction by" +
            " a breeze, but at the concentration in this" +
            " room it numbs your sense of smell.\n");

        break;

    }

}

// Function:  enter_inv(object, from_object)

/*

Purpose:  register a player (or foreign npc) with the Sanctimonian control
room.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

{

    ::enter_inv(ob, from);

    if (living(ob) && !ob->sanctimonian()) register_player(ob);

}

// Function:  create_side(location, *adjacent_rooms, side)

/*

Purpose:  Create the room description and add standard attributes.  The control
code determines the contents of the room.

Arguments:  string containing the filename of this room, string array
containing filenames of adjacent rooms, string indicating which side of the
fortress this room is on.

Returns:  nothing.

*/

void
create_side(string location, string *adjacent_rooms, string side)

{

    /*
     *  The control code is a general-purpose randomly generated number from 0 
     *  to 999.  It is generated whenever the central bog control room is
     *  loaded and the same value is passed to all other bog rooms.  The
     *  northeast wall always contains the door to the outside.  Rooms against
     *  all other walls are assigned variable attributes depending on the
     *  control_code.    
     */

    object room = this_object();
    object ob;  /*  purpose varies depending on room contents.  */

    string *compass = ({"north", "northeast", "east", "southeast", "south",
        "southwest", "west", "northwest"});

    string pillar_text = "";
    int control_code = query_control_code();
    int k;
    int m;
    int n;

    This_Location = location;

    /*
     *  "uid" settings required for cloning objects.    
     */

    setuid();
    seteuid(getuid());

    /*
     *  EXITS PART 1    
     */

    /*
     *  Side rooms connect to the fortress interior only in cardinal compass 
     *  directions.  For rooms on diagonal walls (as seen with the map turned
     *  so that north is up), we can simply add exits to any rooms in cardinal
     *  directions.  For the others, we only add the exit opposite the outer
     *  wall.    
     */

    if ((member_array(side, compass) % 2))

    {

        if (adjacent_rooms[0]) add_exit(adjacent_rooms[0], compass[0], 0, 1);
        if (adjacent_rooms[2]) add_exit(adjacent_rooms[2], compass[2], 0, 1);
        if (adjacent_rooms[4]) add_exit(adjacent_rooms[4], compass[4], 0, 1);
        if (adjacent_rooms[6]) add_exit(adjacent_rooms[6], compass[6], 0, 1);

        pillar_text = " A massive pillar of rugged" +
            " timbers supports the structures overhead.";

    }

    else

    {

        n = (member_array(side, compass) + 4) % 8;
        add_exit(adjacent_rooms[n], compass[n], 0, 1);

    }

    if (side == "northeast")

    {

        /*
         * 
        Fortress_Door = clone_object(FORTRESS_DOOR);
        Fortress_Door->move(room);
        */

        set_short("By the fortress door");

        set_long("This small alcove is a passageway between the" +
            " door to the outside and the fortress interior. It" +
            " is free of clutter and furnished with a floor" +
            " of broad wooden planks." +
            pillar_text + "\n");

        add_item("door",
            "The door seems rather small for such an" +
            " imposing fortress, just barely high and wide enough" +
            " to allow one person at a time to pass through it.\n");

        add_item(({"alcove", "small alcove", "passageway", "fortress"}),
            "There's not much to look at here. The walls," +
            " ceiling, and floor are all made of wood and confine you" +
            " as if you had been placed in a box, although you" +
            " do have some obvious exits.\n");

        add_item(({"interior", "fortress interior", "structures"}),
            "Farther inside the fortress you can see some" +
            " structures built upn the wooden floor, but from" +
            " this distance you can make out no details.\n");

        add_item(({"floor", "wooden floor", "planks", "wooden planks"}),
            "The wooden planks are broad and well smoothed" +
            " to make walking easy. The floor begins at the" +
            " door and continues with no gaps into" +
            " the fortress interior.\n");

        /*
         *  EXITS PART 2    
         */

        add_exit(BOG_OUTER_GROUND + This_Location, "out", "@@check_door@@", 1);

    }

    else

    {

        /*
         *  Using the position of this side within the compass array (minus the 
         *  northeast door) to determine the room contents ensures that we get
         *  seven different rooms, and adding the control code ensures that the
         *  positions of these rooms are scrambled each time the fortress is
         *  rebuilt.    
         */

        compass -= ({"northeast"});
        n = (member_array(side, compass) + control_code) % 7;

        switch (n)

        {

            case 0:

            set_short("Salting and smoking room");

            set_long("Large open bins filled with salt line the" +
                " walls. In the center of the room a " +
                " stone crucible spews a steady stream of" +
                " fragrant smoke." + pillar_text + "\n");

            add_item(({"crucible", "stone crucible"}),
                "The crucible is round and made of grey" +
                " stone streaked with soot. It has a lid with" +
                " many small holes in it through which smoke" +
                " streams from a smoldering fire within.\n");

            add_item(({"smoke", "fragrant smoke", "fire", "smoldering fire"}),
                "The fire within the crucible only barely flickers" +
                " from time to time. Mostly it produces" +
                " dense but fragrant smoke that wafts up toward" +
                " the ceiling and lingers there awhile, then escapes" +
                " from the room to the " + query_exit_cmds()[0] + ".\n");

            add_item(({"bin", "open bin", "bins", "open bins",
                "salt", "wall", "walls"}),
                "The bins stand along the walls and are" +
                " filled with salt.\n");

            k = random(5) + 5;

            for (m = 0; m < k; m +=1)

            {

                ob = clone_object(BOG_OBJECTS + "ham_raw");
                ob->move(room);

            }

            break;

            case 1:

            set_short("Barrel room");

            set_long("Great barrels are stockpiled here, each" +
                " painted with a white diamond and the word AQUAVIT." +
                pillar_text + "\n");

            add_item(({"barrels", "great barrels", "barrel", "great barrel"}),
                "Barrel objects will be added later.\n");

            break;

            case 2:

            set_short("Woodworking area");

            set_long("Here are woodworking benches and tool racks." +
                pillar_text + "\n");

            add_item(({"benches", "bench", "rack", "tool rack",
                "racks", "tool racks"}),
                "This item will be added later.\n");

            break;

            case 3:

            set_short("Dining hall");

            set_long("This room is filled with long tables and" +
                " benches." +
                pillar_text + "\n");

            break;

            case 4:

            set_short("Pantry");

            set_long("Here general foodstuffs are stored," +
                " mostly on high shelves to protect them" +
                " from vermin and moisture on the ground." +
                pillar_text + "\n");

            add_item(({"foodstuffs", "general foodstuffs",
                "shelves", "high shelves", "shelf", "high shelf"}),
                "The shelves contain small sacks, some plain," +
                " some marked with words like FLOUR or" +
                " BEANS.\n");

            add_item(({"sacks", "small sacks", "sack", "small sack"}),
                "This item will be added later.\n");

            break;

            case 5:

            set_short("Washing area");

            set_long("This area has basins, sponges, drying" +
                " racks, and other equipment for washing" +
                " tableware and cooking utensils." +
                pillar_text + "\n");

            add_item(({"basins", "basin", "sponges", "sponge", "racks",
                "racks", "equipment", "other equipment"}),
                "This item will be added later.\n");

            break;

            case 6:

            set_short("Scrap heap");

            set_long("A large wooden bin stand here alone," +
                " filled with a variety of" +
                " wood and metal scraps." +
                pillar_text + "\n");

            add_item(({"bin", "wooden bin"}),
                "The bin is nearly as wide and deep as the entire" +
                " room, and it holds a ponderous heap of scraps.\n");

            add_item(({"heap of scraps", "heap", "scraps"}),
                "The scraps are small and irregularly shaped," +
                " not of any apparent use.\n");

            break;

        }

    }

    /*
     *  PROPERTIES    
     */

    add_prop(ROOM_I_HIDE, 50);  /*  Some hiding places. */
    add_prop(ROOM_I_LIGHT, 2);  /*  Moderate light. */

    /*
     *  SPECIAL FUNCTION    
     */

    /*
     *  Tell the Sanctimonian central control room that this room has been 
     *  loaded.  Function is found in /d/Calia/central/bog/baseroom.c.    
     */

    register_room();

}
