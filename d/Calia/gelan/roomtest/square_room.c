// ROOM:  square_room

    /* Calia Domain

    HISTORY

    coder(s):   Deinonychus

    Revision 1.2  1994/10/05  17:01:11  brambi
    School added

    [01-04-02] Revised by Uhclem from [C:\CALIA\GELAN\ROOMS\SQUARE_R.DOC] to
    add dragonfear suppression and limit the number of dragons that can land in
    a room in the square; entire file restructured at the same time (headers
    added, spacing and line breaks changed, etc.).

    Every living thing benefits from the magic in Caliana's statue.  Right now
    the only effect is to prevent "dragonfear," a paralysis inflicted by
    dragons from Ansalon/Krynn domains, from having any effect within sight of
    the statue.  My original intention was to prevent dragons from inflicting
    the dragonfear, but the dragon objects do not support a suppression
    function.  Therefore, everyone in the square gets the no_dragonfear
    property to achieve the same effect.  The accounting is a bit more
    complicated than it would be if I could simply block the dragonfear itself,
    since I have to recognize that some livings may already have a
    no_dragonfear property; those who don't need to have the statue-based
    property removed when they leave the square.

    PURPOSE (in Deinonychus' own words, but Uhclem added the punctuation)

    Centralization of items to add in a room of the square.
    This is an abstract room of the square in Gelan.
    Every room of the square is inheriting this room.
    */

// INCLUSIONS AND DEFINITIONS

#include <stdproperties.h>
#include <ss_types.h>
#include "room.h"
#pragma save_binary

    /*
     *  The live_i_no_dragonfear property isn't in the standard collection as 
     *  of this writing, so it has to be defined explicitly.  We need to keep
     *  track of what we add to players and roving NPCs, so I created another
     *  property, calia_as_room_props, which keeps a list of the properties
     *  this room has added to each living.  When the player leaves this room,
     *  all properties in this list are removed.  The same properties modified
     *  by this room may also be modified by other Calian objects; if they are,
     *  they are deleted from calia_s_room_props so we'll know that the room is
     *  no longer responsible for managing them.    
     */

#define LIVE_I_NO_DRAGONFEAR             "_live_i_no_dragonfear"
#define CALIA_AS_ROOM_PROPS              "_calia_as_room_props"
#define ROOM_M_DA_DRAGONSTEED_NO_LAND    "_room_m_da_dragonsteed_no_land"

inherit "/std/room";

// GLOBAL VARIABLES

mapping Square_Items =

    ([

    "blacksmith":
        ({
        ({ ({"house", "smithy", "forge", "blackened house"}),
        "blacksmith_house" }),
        ({ ({"sign", "sign at smithy"}), "blacksmith_sign" }),
        ({ ({"chimney", "chimney of smithy"}), "blacksmith_chimney" }),
        }),

    "bakery_e":
        ({
        ({ ({"gingerbread house","house","bakery"}), "bakery_house" }),
        ({ ({"sign"}), "bakery_sign" }),
        ({ ({"painting"}), "bakery_painting_e" }),
        }),

    "bakery_w":
        ({
        ({ ({"gingerbread house", "house", "bakery"}), "bakery_house" }),
        ({ ({"sign"}), "bakery_sign" }),
        ({ ({"painting"}), "bakery_painting_w" }),
        }),

    "bank":
        ({
        ({ ({"bank", "cube shaped building"}), "bank_house" }),
        }),

    "gate_north":
        ({
        ({ ({"gate"}), "gate_north" }),
        ({ ({"tower", "towers"}), "gate_towers" }),
        }),

    "grocery":
        ({
        ({ ({"entrance", "entrance of grocery"}), "grocery_entrance" }),
        ({ ({"grocery", "empire"}), "grocery_house" }),
        ({ ({"plant", "plants", "veggy", "veggies"}), "grocery_plants" }),
        }),

    "hairdresser":
        ({
        ({ ({"house", "giant bottle", "giant shampoo bottle", "hairdresser"}),
        "hairdresser_house"
        }),
        ({ ({"sign"}), "hairdresser_sign" }),
        }),

    "lavatory":
        ({
        ({ ({"lavatory", "blue building"}), "lavatory_house" }),
        }),

    "school":
        ({
        ({ ({"school"}), "school_house" }),
        }),

    "shop":
        ({
        ({ ({"shop"}), "shop_house" }),
        }),

    ]);

mapping Square_Cmd_Items =

    ([

    "blacksmith":
        ({
        ({ ({"sign", "sign at smithy"}), ({"read"}), "blacksmith_sign" })
        }),

    "school":
        ({
        ({ ({"inscription", "inscription on school"}), ({"read"}),
        "school_inscription"
        })
        }),

    ]);

// FUNCTIONS

// Function:  enter_inv(ob, where_from)

/*

Purpose:  detect when someone enters the room and apply appropriate magic
effects due to proxmity of statue and fountain.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object where_from)

{

    ::enter_inv(ob, where_from);

    /*
     *  There are no effects applied to nonliving objects, and wizards are 
     *  exempt from this process.    
     */

    if (!living(ob) || ob->query_wiz_level())

    {

        return;

    }

    /*
     *  Add the no_dragonfear property and record it in the list of 
     *  room-controlled properties only if it is not already present.    
     */

    if (!ob->query_prop(LIVE_I_NO_DRAGONFEAR))

    {

        ob->add_prop(LIVE_I_NO_DRAGONFEAR, 1);

        if (!ob->query_prop(CALIA_AS_ROOM_PROPS))

        {

            ob->add_prop(CALIA_AS_ROOM_PROPS, ({LIVE_I_NO_DRAGONFEAR}));

        }

        else

        {

            ob->add_prop(CALIA_AS_ROOM_PROPS,
                ob->query_prop(CALIA_AS_ROOM_PROPS) +
                ({LIVE_I_NO_DRAGONFEAR}));

        }

    }

}

// Function:  leave_inv(ob, where_to)

/*

Purpose:  remove all room-applied properties from the player as he leaves.

Arguments:  object leaving the room, object destination.

Returns:  nothing.

*/

void
leave_inv(object ob, object where_to)

{

    string *prop_list = ob->query_prop(CALIA_AS_ROOM_PROPS);

    ::leave_inv(ob, where_to);

    /*
     *  There are no effects applied to nonliving objects, wizards are exempt 
     *  from this process, and there's no need to do anything if no properties
     *  have been added.    
     */

    if (!living(ob) || ob->query_wiz_level() || !prop_list)

    {

        return;

    }

    while (sizeof(prop_list))

    {

        ob->remove_prop(prop_list[0]);
        prop_list -= ({prop_list[0]});

    }

    ob->remove_prop(CALIA_AS_ROOM_PROPS);

}

// Function:  dragon_check()

/*

Purpose:  allow or deny a dragon landing rights in the room depending on the
total volume of objects already present.  It would be nice to query the volume
of the approaching dragon to perform a really meaningful measurement, but
that's not supported by the Dragonarmy code.

Arguments:  none.

Returns:  0 if landing is allowed, string if denied.

*/

string
dragon_check()

{

    /*
     *  Here's the inside scoop on Krynn/Ansalon dragons, courtesy of Milan: 
     *  --------------------------------------------------------------------
     *  16.10.98
     *  - fixed height, weight and volume
     *     height: 100 200 400 420 420 430 (that's height, not length ;-)
     *     weight: 40000 300000 600000 620000 650000 700000
     *           volume = weight * 1.5;
     *     modifiers according to color
     *     red 100%, blue 90%, green 75%, black 65%, white 50%
     *     gold 105%, silver 100%, copper 75%, bronze 90%, brass 65%
     *  --------------------------------------------------------------------

     *  My aim is to allow at least one dragon - even the biggest - to land in
     *  an uncrowded room in the square.  I figure that most humanoids will get
     *  out of the way of a descending dragon, but a squad of armed guards or
     *  warriors might pose a problem.  According to the numbers above, the
     *  largest gold dragon should have a volume of 1102500.  I'll round the
     *  limit up to 1150000 so that a couple of mortals and perhaps a Knight's
     *  steed or two can be in the same room.    
     */

    string message;

    if (query_prop(OBJ_I_VOLUME) > 1150000)

    {

        message = "There's no room here for a dragon to land.\n";

    }

    return message;

}

// Function:  create_square_room()

/*

Purpose:  add appropriate descriptive elements to a room in the town square.

Arguments:  none

Returns:  nothing

*/

void
create_square_room()

{

    add_item(({"road","floor","ground"}), DESC("floor"));
    add_item(({"marble","pieces"}), DESC("marble"));
    add_item("square", DESC("square"));
    add_item("fountain", DESC("fountain"));
    add_item("statue", DESC("fountain_statue"));
    add_item(({"building", "buildings"}), DESC("buildings"));

    add_prop(ROOM_M_DA_DRAGONSTEED_NO_LAND, "@@dragon_check@@");

}

// Function:  add_square_items(str)

/*

Purpose:  add appropriate items to a room in the town square.

Arguments:  string indicating what's available in this location.

Returns:  nothing

*/

void
add_square_items(string str)

{

    int i;
    mixed *items = Square_Items[str];

    if (items)

    {

        for (i = 0; i < sizeof(items); i++)

        {

            add_item(items[i][0], DESC(items[i][1]));

        }

    }

    items = Square_Cmd_Items[str];

    if (items)

    {

        for (i = 0; i < sizeof(items); i++)

        {

            add_cmd_item(items[i][0], items[i][1], DESC(items[i][2]));

        }

    }

}
