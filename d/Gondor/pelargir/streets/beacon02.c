/*
 * /d/Gondor/pelargir/rooms/beacon02.c
 *
 *
 * Copyright (C) 1999 by Cooper Sherry (Gorboth) and
 *	Nancy L. Mintz (Gnadnar)
 * 
 */

#pragma strict_types

inherit "/d/Gondor/pelargir/pelargir_room";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/pelargir_room.h"


public void	create_pelargir_room();



/*
 * Function name:	create_pelargir_room
 * Description	:	set up the room
 */
public void
create_pelargir_room()
{
    string sign_text;

    set_part(PART_NORTH);
    set_street_name(STREET_BEACON);
    set_room_type(TYPE_STREET);

    set_extra_desc("A row of quaint cottages lines the road to the north, " +
        "enjoying a respectable view of the river which courses in its " +
        "narrow channel. A particularly large building is visible just to " +
        "one side of the cottages, its finely crafted wooden sign swaying " +
        "lazily in the breeze. Down the street to the east, a lighthouse " +
        "looms in the distance.");


    add_item( ({ "cottage", "cottages", "row of cottages",
        "quaint cottage", "row of quaint cottages", "quaint cottages", }),
        BSN("The cottages are very similar in architecture and shape, " +
            "with square windows, and squat, rectangular doors. They " +
            "face the Sirith River which runs alongside the road to " +
            "the south."));
    add_item( ({ "window", "windows", "square window", "square windows", }),
        BSN("The windows are charmingly crafted, giving a look of warmth " +
            "and care to the cottages."));
    add_item( ({ "doors", "rectangular door", "rectangular doors", }),
        BSN("The door of each of the cottages is very clean, and reflects " +
            "a sense of simplicity and pride for one's dwelling place."));
    add_item( ({ "building", "large building", "storytellers", }),
        BSN("The building to the north is very large indeed. It looks " +
            "quite a bit different from the other dwellings along this " +
            "street. A large sign hangs from its front."));
    add_item( ({ "river", "river sirith", "sirith river", "water",
        "waters", }),
        BSN("The Sirith River courses in a narrow channel just to the " +
            "south of the street here."));
    add_item( ({ "channel", "narrow channel", }),
        BSN("A channel has been constructed to restrain the waters of " +
            "the river on its way through the northern parts of the " +
            "city, here."));
    add_item( ({ "lighthouse", "structure", "stone structure", }),
        BSN("A lighthouse is visible at the end of Beacon Street, a ways " +
            "off to the east."));


    /* door, sign for storytellers club */
    clone_object(STORYT_DIR + "obj/foyer_door_out")->move(TO);
    sign_text = read_file(STORYT_DIR + "misc/sign.txt");
    add_item( ({ "sign", "wooden sign", "carved sign", "carved wooden sign" }),
        sign_text);
    add_cmd_item( ({ "sign", "wooden sign", "carved sign", "carved wooden sign" }),
        "read",
        sign_text);

    add_exit((PELAR_DIR + "streets/beacon03"), "east", 0);
    add_exit((PELAR_DIR + "streets/beacon01"), "west", 0);

} /* create_pelargir_room */
