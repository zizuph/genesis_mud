/* A camp entrance. Mortricia 920927 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define CAMP_DIR        MORTRICIADIR + "camp/"

void
reset_room()
{
    object guard;

    if (!present("guard", TO)) {
        guard = clone_object(CAMP_DIR + "guard");
        guard -> move(TO);
    }
}

void
create_room()
{
    set_short("Camp entrance");
    set_long(BSN(
        "This is the entrance to the gypsy camp. They have " +
        "turned their camp into a small amusement park. To the west " +
        "you see many people walking between tents and carriages. " +
        "There is a signpost standing at the entrance."
    ));
    
    add_item(({"sign"}), BSN(
        "It's an ordinary sign with readable letters on it."
    ));
    add_item(({"signpost"}), BSN(
        "It's a wooden signpost."
    ));

    add_cmd_item(({"sign", "signpost"}), "read",
        "The sign reads:\n" +
        "          WELCOME!\n"
    );

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(CAMP_DIR + "camp_01", "west", 0);
    add_exit("/d/Terel/calathin/roads/road_s11","east", VBFC_ME("check_race"));

    reset_room();
}

check_race()
{
    /* The gypsies are not allowed to leave the camp */

    if (TP -> query_race_name() == "gypsy") {
        return 1;
    } else {
        return 0;
    }
}
