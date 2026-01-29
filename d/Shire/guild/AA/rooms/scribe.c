/*
 * An office for the scribe to keep track of who is borrowing
 * or donating items to the racks.
 *
 * Varian - May 7, 2017
 */

//#pragma save_binary
//#pragma strict_types

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <filter_funs.h>
#include "../guild.h"

inherit SHIRE_ROOM;

#define NORTH_WINDOW   AA_DIR + ("rooms/store")
#define WEST_WINDOW    AA_DIR + ("rooms/store2")

public string exa_window(string desc, string room_file);
object r_book, r_book2;

void
create_room()
{
    set_short("Scribe's office");
    set_long("This is a small office set aside for the scribe of " +
        "Angmar's Army. There is really not much to see here, just " +
        "a small chair and desk crammed in the corner, positioned in " +
        "such a way that the scribe can easily peer through the " +
        "barred windows that open up through both the west and north " +
        "walls. The records have piled up here for the officers to " +
        "browse through if they so desire.\n");

    add_item(({"wall","walls"}),
        "The walls are made of stone here, with two barred openings " +
        "looking out through the north and west walls. A narrow " +
        "arch to the northwest leads back into the private room.\n");
    add_item(({"floor","down"}),
        "The floor is probably made of stone, although it is hard to " +
        "see through the layer of dirt covering it.\n");
    add_item(({"ceiling","up"}),
        "There is in fact a stone ceiling up above your head. It is " +
        "profoundly uninteresting.\n");
    add_item(({"dirt","grime"}),
        "It appears that years of dirt and grime have built up here, " +
        "perhaps because even the cleaning crew is not allowed near " +
        "these books!\n");
    add_item(({"chair","wooden chair"}),
        "This is a rather poorly crafted wooden chair. It appears to " +
        "be solid enough for the scribe to sit on, but it is certainly " +
        "not pretty!\n");
    add_item(({"desk","wooden desk", "table", "wooden table"}),
        "This is a small wooden table that serves as a desk for the " +
        "scribe. Several broken pieces of charcoal and loose sheets " +
        "of parchment lay scattered around as the scribe prepares his " +
        "books.\n");
    add_item(({"charcoal","broken charcoal","pieces"}),
        "Apparently the scribe uses charcoal to write his logs with. " +
        "Perhaps not the best writing material to use, but it should " +
        "last long enough for an officer to check the most recent " +
        "activity.\n");
    add_item(({"corner","southeast corner"}),
        "There is a desk and a chair crammed in the far corner, where " +
        "the scribe works recording all of the activity in the nearby " +
        "racks.\n");
    add_item(({"record","records"}),
        "The records are kept in the two books clearly visible here. " +
        "You could probably examine either of them a little closer.\n");
    add_item(({"parchment","sheet", "sheets"}),
        "The scribe uses some very expensive parchment to keep " +
        "the Army logs intact. It is really too bad that he uses " +
        "charcoal to write with.\n");
    add_item(({"arch","exit"}),
        "There is an exit to the northwest, a narrow arch that leads " +
        "back out to the private room of Angmar's Army.\n");
    add_item(({"window","windows","opening","barred opening","openings",
            "barred openings"}),
        "There are two openings here, both with iron bars running from " +
        "top to bottom, windows that peer out into rooms to the north " +
        "and west.\n");

    add_item( ({ "north window", "north opening", "northern window",
                 "northern opening"} ), "@@exa_window|" + "You look into "
          + "the north window.\n|" + NORTH_WINDOW + "@@");

    add_item( ({ "west window", "west opening", "western window",
                 "western opening"}), "@@exa_window|" + "You look into "
          + "the west window.\n|" + WEST_WINDOW + "@@");

    set_no_exit_msg(({"west","south","northeast","southeast","southwest"}),
        "Yup. That's a real wall, not a fake one. You will have to " +
        "try moving in another direction.\n");
    set_no_exit_msg(({"west","north"}),
        "You can't seem to fit yourself through the bars to get in " +
        "there. You will have to seek another way around!\n");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    r_book = clone_object(AA_DIR + "obj/rack_logging_book");
    r_book->move(TO);
    r_book2 = clone_object(AA_DIR + "obj/rack_logging_book2");
    r_book2->move(TO);

    add_exit(AA_DIR + "rooms/priv", "northwest");
    add_npc(AA_DIR  + "npc/gralme");

}

public string
exa_window(string desc, string room_file)
{
    object room = find_object(room_file),
    *in_room_p, *in_room_o;

    in_room_p = FILTER_LIVE(all_inventory(room));
    in_room_o = FILTER_DEAD(all_inventory(room));

    write((room_file)->short()+ "\n");
    write((room_file)->long());

    if (sizeof(in_room_p))
        this_player()->catch_msg(capitalize(COMPOSITE_LIVE(in_room_p))+ ".\n");

     if (sizeof(in_room_o))   
        this_player()->catch_msg(capitalize(COMPOSITE_DEAD(in_room_o))+ ".\n");

    tell_room(ENV(TP), QCTNAME(TP) + " gazes through the window.\n", TP);

    return "";
} 
