
 /* Digit 06 JUN 95 */

inherit "/std/room";
inherit "/d/Calia/walkers/specials/water_walk";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"
#include FIRE_HEADER

int
is_fire(object living)
{
    return living->query_guild_name_occ() == GUILD_NAME;
}

void
create_room()
{
    set_short("In a well lit chamber");
    set_long("You are standing in a beautiful chamber in this deep "+
        "cavern in Mt. Pyros.  This chamber seems to have been carved "+
        "out carefully from the rock as opposed to the tunnels "+
        "above leading to this place.  The chamber is glowing in a "+
        "bright orange light from a flame off to the north.  On the "+
        "west wall you see a golden door set into the stone.  East of "+
        "you can be heard the bubbling of the river as it flows off away "+
        "from you.\n");
    add_item("walls","The walls have been carefully carved out "+
        "to form this chamber.  The walls and floor come to an "+
        "almost perfect corner as does the walls and ceiling far "+
        "above you.\n");

    add_item("river","The river looks very hot indeed as steam "+
        "is rising from it and you see bubbles rising throughout "+
        "the water.\n");

    add_item("flame","It is difficult to make any details out "+
        "about the flame as it is still quite far north from "+
        "here.\n");

    add_item(({"door","golden door"}),"The door appears to made of solid "+
        "gold, and it set into the western basalt wall of this chamber.\n");

    add_item(({"orange light","light"}),"The orange light is coming from "+
        "the flame north of here.\n");

    add_exit(CAVE+"room60","north");
    add_exit(CAVE+"startroom","west","@@west");
    add_exit(CAVE+"room58","east","@@water_walk");

}

int
west()
{
    if (!is_fire(TP))
    {
        write("You feel a magical force blocking your way.\n");
        return 1;
    }
    write("You leave through the door.\n");
    say(QCTNAME(TP) + " leaves through the door to the west.\n");
    tell_room(CAVE+"startroom",QCTNAME(TP)+" enters through the door.\n");
    TP->move_living("M",CAVE+"startroom");
    return 1;
}
