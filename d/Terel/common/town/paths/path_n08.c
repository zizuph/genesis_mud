/*  Standard path for the town of Calathin, in the Terel domain

    Original room coded by Vader on 7/21/92

    eventually, there will be 25 path rooms in Calathin, connecting to
    various things such as the ruined manor, houses, farms, and such.

 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>
#define FOUND_ROOF "_found_roof"
#define CAN_CLIMB "_can_climb"

public void
create_room()
{

    set_short("A small path");
    set_long("This small path heads into a light forest area.  " +
         "There aren't many trees here, but the few that are are high and " +
         "healthy looking.  The path continues to the west, and " +
         "there are houses to your west and northeast.\n");

    add_item(({"tree", "trees"}), "These tall pines really do well in " +
                              "this weather.  They are covered\nin snow.\n");

    add_item(({"snow"}), "The snow reflects the sunlight off the top of " +
                                    "the trees, giving it\na silver color.\n");

    add_item(({"house", "houses"}), "They look deserted, but you can hear " +
                              "sounds from the one to the \nnortheast.\n");

    add_item(({"path"}), "This path hasn't seen much use, other than by " +
                                   "animals.\n");
    add_item("roof","The house to northeast has a small "+
                    "window near the roof.\n");

    add_exit("/d/Terel/common/town/houses/house5", "west", 0);
    add_exit("/d/Terel/common/town/houses/house6", "northeast", 0);

    add_prop(OBJ_S_SEARCH_FUN, "search_roof");
    add_prop(OBJ_I_SEARCH_TIME, 1);
    add_cmd_item("roof","climb","@@climb");

}

int
climb()
{
    if(TP->query_prop(CAN_CLIMB))
    {
        write("You find a hand hold and climb to the roof "+
                  "entering a small window.\n");
        TP->move_living("up",
                      "/d/Terel/common/town/houses/house6_roof");
        return 1;
    }
    write("What?\n");
    return 1;
}


string 
search_roof(object me, string arg)
{
    if(arg != "roof")
    {
        return "";
    }
    if(TP->query_prop(FOUND_ROOF) > 1)
    {
        TP->add_prop(CAN_CLIMB, 1);
        return "You've found a small hand hold in the wall "+
                  "that will let you climb to the window.\n";
    }
    TP->add_prop(FOUND_ROOF, TP->query_prop(FOUND_ROOF) + 1);
    return "Your search reveals nothing special.\n";
}

