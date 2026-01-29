/* For inclusion in all forest rooms (as opposed to the path) */
#include "defs.h"

#define GONDOR_HERB "/d/Gondor/common/herbs/"
#define KALAD_HERB "/d/Kalad/common/herbs/"

inherit SHADOWS_ROOM;
inherit LIB_DIR + "herbsearch";

string *herbs = ({
    KALAD_HERB +"darfern",
    KALAD_HERB +"numbis",
    KALAD_HERB +"nightshade",
    GONDOR_HERB +"madwort",
    GONDOR_HERB +"frostheal",
    GONDOR_HERB +"angurth",
});

string forest_intro = "You are surrounded by a dark forest, full of gloom " +
    "and deep shadows.";
string forest_features = " The trees and darkness continue in all directions.";
string forest_details = "";

void
create_room()
{
    ::create_room();
    set_short("Deep in a dark forest");
    set_long(forest_intro + forest_features + forest_details + "\n");
    set_alarm(30.0,0.0,"set_events");
    add_item(({"forest"}), "It is dark and gloomy.\n");
    add_item(({"trees"}), "Their twisted branches give you an eerie " +
            "feeling.\n"); 
    add_item(({"shadows"}), "They are deep and ominous.\n");
    add_prop(ROOM_S_DARK_LONG, "You are in a very dark forest and unable to " +
            "see much at all.\n");
    add_prop(ROOM_M_CANNOT_TELL_TIME, "The dense canopy obstructs your view " +
           "of the sky, making such a calculation unworkable.\n");
    
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_NO_TIME_DESC, 1);
    
    set_up_herbs(({herbs[random(sizeof(herbs))]}), ({"forest","trees"}));

    if (DAY)
        add_prop(ROOM_I_LIGHT, 0);
    else
        add_prop(ROOM_I_LIGHT, -1);

    CLOCK->add_event(this_object());
}

void
event_hook(int hour)
{
    if (DAY && query_prop(ROOM_I_LIGHT) == -1)
    {
        add_prop(ROOM_I_LIGHT, 0);
        tell_room(TO, "You notice the darkness of the forest " +
                "wane slightly.\n");
    }
    else if (!DAY && query_prop(ROOM_I_LIGHT) == 0)
    {
        add_prop(ROOM_I_LIGHT, -1);
        tell_room(TO, "The darkness of the forest appears " +
                "to deepen.\n");
    }
}

int
query_shadows_forest()
{
    return 1;
}

