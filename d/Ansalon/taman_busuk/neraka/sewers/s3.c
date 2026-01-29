/* Ashlar, 21 Aug 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <ss_types.h>

inherit SEWER_BASE;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "This is a tunnel in the sewers beneath Neraka. " +
    "The tunnel is wide enough for four men to walk abreast, and it " +
    "is just as high. " + water_desc() + "The tunnel leads east and " +
    "west. A stone portal is set in the south wall, looking out of " +
    "place.\n";
}

void
create_neraka_room()
{
    set_short("in the sewers");
    set_long("@@long_descr");

    add_lsewer_items();
    add_item(({"portal","stone portal"}),"It is a portal of black stones, " +
    "framing an opening which leads south.\n");
    add_item("opening","The opening is framed by a stone portal, and it " +
    "leads south.\n");
    add_item(({"stones","black stones"}),"The black stones of the portal " +
    "are inscribed with runes.\n");
    add_item("runes","@@runes");
    add_cmd_item("runes","read","@@runes");

    add_lsewer_herbs();
    remove_prop(ROOM_I_LIGHT);

    reset_room();

    add_exit(NSEWER + "s2", "west");
    add_exit(NSEWER + "s4", "east");
    add_exit(NSEWER + "stair1", "south");
}

string
runes()
{
    switch(TP->query_skill(SS_LANGUAGE))
    {
        case 0..20:
            return "You do not recognize the runes.\n";
        case 21..40:
            return "You think you know the type of runes used, but " +
            "you cannot deduce any meaning behind the words.\n";
        case 41..60:
            return "The meaning is not altogether clear, but it " +
            "seems to be a sort of greeting.\n";
        default:
            return "It is part of an ancient prayer for the dead, " +
            "translated it means something like: 'As the world of " +
            "the living say farewell, may peaceful rest be with " +
            "you in the life beyond.'\n";
    }
}
