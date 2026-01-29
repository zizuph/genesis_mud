/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads south and north, flanked on east " +
        "side by the tall city walls, and on the west side by a taller " +
        "tower, which has a door leading out to the street.");

    add_item_citywalls();
    add_item_street1();

    add_exit(NINNER + "r36", "north");
    add_exit(NINNER + "r38", "south");
    add_exit(NINNER + "tower", "west", "@@enter_tower@@");

    add_item(({"tower","tall tower","taller tower"}),
    "The stone tower is much taller than the city walls, in fact, it could " +
    "be said to tower above you. A door, of no particular remark, connects " +
    "this tower to the street.\n");

    add_item("door","The door is of wood, and very sturdy.\n");
}

int
enter_tower()
{
    if (this_player()->query_wiz_level())
    {
        write("Being the wiz that you are, which is, a wiz of no " +
        "small means, you kick the door open and stride into the " +
        "tower.\n");
        return 0;
    }
    else if (this_player()->query_dragonarmy_promotions() > 1)
    {
        write("You knock softly upon the door, and it is opened from " +
        "within, letting you in.\n");
        say(QCTNAME(this_player()) + " knocks softly upon the door, " +
        "and it opens to let " + HIM(this_player()) + " in.\n");

        return 0;
    }
    else if (this_player()->query_guild_name_occ() == "Priests of Takhisis" &&
        this_player()->query_priest_level() > 0)
    {
        /* At least Priest in PoT */
        write("You knock heavily upon the door and call out: Open up in the " +
        "name of the Queen of Darkness!\nGrudgingly, the door opens and " +
        "you boldly enter the tower.\n");

        say(QCTNAME(this_player()) + " knocks heavily upon the door and " +
        "calls out: Open up in the name of the Queen of Darkness!\n" +
        "Grudgingly, the door opens, and " + QTNAME(this_player()) +
        " enters the tower.\n");
        return 0;
    }
    else
    {
        write("The door will not budge, it seems to be securely latched " +
        "from the inside. As you bang upon the door, a voice from " +
        "within shouts: Away with you!\n");
        say(QCTNAME(this_player()) + " bangs upon the door, but a voice " +
        "from within shouts: Away with you!\n");
        
        return 1;
    }
}
