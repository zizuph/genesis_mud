inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"
#define TP           this_player()
#define TO           this_object()

#define WRECK        "/d/Terel/port/wreck/"
#define BEACH        "/d/Terel/port/beach/"

#define MAST         WRECK + "mast"
#define CABIN        WRECK + "cabin"

public int do_climb(string str);
public int do_jump(string str);

public void
reset_room()
{
}

public void
init()
{
    ::init();
    add_action("do_climb", "climb");
    add_action("do_jump",  "jump");
}

public void
create_room()
{
    set_short("on the deck");
    set_long("You are standing on the deck of an old wreck. " +
             "You can probably climb down or jump to reach the stones. " +
             "Some distance to the north you see a beach. " +
             "There is a mast here and west you can enter some " +
             "sort of cabin. You can also go east.\n");

    add_item(({"water", "sea"}), "It looks very cold.\n");

    add_item(({"beach"}), "It looks safer than this wreck.\n");

    add_item(({"wreck"}), "It was a sailing ship. It looks very old, " +
                          "but it seems to be fairly intact.\n");
                          
    add_item(({"mast"}), "It looks climbable.\n");
    
    add_item(({"cabin"}), "It is in pretty bad condition.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(WRECK + "for",    "east", 0);
    add_exit(CABIN,  "west", 0);

    reset_room();
}

public int
do_climb(string str)
{
    int climb;
    
    notify_fail(capitalize(query_verb()) + " what?\n");
    if (str != "mast" && str != "down") return 0;
    
    if (str == "down") return do_jump(str);
    
    climb = TP->query_skill(SS_CLIMB);
    climb = (climb + random(climb))/2;

    if (climb <= 20) {
        write("You don't manage to climb the mast.\n");
        say(QCTNAME(TP) + " fails to climb the mast.\n");
        return 1;
    }
    
    write("You climb up the mast.\n");
    TP->move_living("by climbing up the mast", MAST);
    
    return 1;
}

public int
do_jump(string str)
{
    notify_fail(capitalize(query_verb()) + " where?\n");
    if (str != "down") return 0;
    
    write("You leave the wreck.\n");
    TP->move_living("the wreck", BEACH + "wreck");
    
    return 1;
}
