/* hall1.c in guild, made by Nick */
/* Modified by Mucalytic May the 20th '96. */

#include "local.h"
#include "guild.h"
#include <language.h>
#include "/d/Krynn/common/defs.h"

inherit INSIDE_BASE;

#define RNAME(ob)       ob->query_real_name()

#define IS_NPC(ob)      ob->query_npc()
#define IS_ALIVE(ob)    ob->query_prop(LIVE_I_IS)

#define LIVING(ob)      (IS_ALIVE(ob) & !IS_NPC(ob))

string *visitors = ({ });

void create_solace_room()
{
    set_short("A large empty hall");
    set_long("You are standing in a large empty hall. There is dust "+
        "everywhere and a strange, almost holy sense of tranquility pervades "+
        "the atmosphere. There seems to be nothing here @@footprints@@. To "+
        "the north, an archway leads to the entrance to this place and to "+
        "the west, another smaller archway leads to an old decrepit shop.\n");

    add_exit(ENTRANCE, "north", 0, 1);
    add_exit(TDIR + "shop", "west", 0, 1);

    add_prop(OBJ_S_WIZINFO, "Do 'Call here query_visitors' to get a list of "+
        "players that have entered here since the last reboot.\n");

    add_item("footprints", "@@footprint_desc@@");

    add_item("dust", "The dust seems to have collected over the many years "+
        "of neglect that this place has seen@@dust_footprints@@.\n");

    add_item("entrance", "The entrance to this hall. You reckon that it "+
        "would be easier to see if you actually walked in that direction.\n");

    add_item(({"archway", "archways"}), "Both of the archways are simple "+
        "curved doorways in their respective walls and provide exit to "+
        "different areas of this place.\n");

    add_item(({"shop", "old shop", "decrepit shop", "old decrepit shop"}),
        "You can't see much of it from here. Perhaps it would be best to "+
        "walk over and have a look first-hand?\n");
}

void enter_inv(object ob, object from)
{
    if(LIVING(ob))
        visitors += ({ RNAME(ob) });

    ::enter_inv(ob, from);
}

string *query_visitors()
{
    return visitors;
}

string dust_footprints()
{
    int size = sizeof(visitors);

    switch(size)
    {
        case 0:
            return "";

        case 1:
            return ". You seem to have left footprints in it";

        case 2..6:
            return ". You count "+LANG_WNUM(size)+" sets of footprints in it "+
                "where other travellers have passed by";

        default:
            return ". There are many sets of footprints in it, leading in "+
                "all directions";
    }
}

string footprints()
{
    int size = sizeof(visitors);

    switch(size)
    {
        case 0:
            return "of interest";

        case 1:
            return "but the footprints you have left on the floor";

        case 2..6:
            return "but "+LANG_WNUM(size)+" sets of footprints that passing "+
                "travellers have left on the floor";

        default:
            return "but many footprints left by a group of travellers that "+
                "seem to have been here recently";
    }
}

string footprint_desc()
{
    int size = sizeof(visitors);

    switch(size)
    {
        case 0:
            return "You find no footprints.\n";

        case 1:
            return "The footprints that you have made in the dust on the "+
                "floor.\n";

        default:
            return "The footprints the travellers to this place have made in "+
                "the dust on the floor when they passed.\n";
    }
}
