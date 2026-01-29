#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/std/boats/std_boat_defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit BLOODSEA_NEW_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "oceanfloat", }) );

void
reset_sea_room()
{
    set_searched(0);

    return;
}

void
create_sea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
        "a strange and reddish colour. Rumour has it that the colour "+
        "is the result of the blood of many victims who lost their "+
        "lives during Krynn's most terrible hour, though it "+
        "could be the clay stirred up from the sea bottom by the "+
        "maelstrom.\n");

    add_item(({"blood bay","bay","balifor","thick forests","forests"}),
        "You find yourself within a relatively calm body of " +
        "water sheltered between the wild coastline of the Ogrelands " +
        "and the thick forests of Balifor. Blood Bay is deep, " +
        "allowing ships of all sizes to escape from the rough " +
        "conditions of the Blood Sea.\n");

    add_row_exit(FROOM + "2c", "north", 0, 1);
    add_row_exit(FROOM + "1d", "east", 0, 1);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();

}

int
no_go()
{
    write("You try and sail in that direction, however the current and wind created by a " +
       "mighty storm agressively drives you back!\n");
    return 1;
}

void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}

string
short_descr()
{
    return bloodsea_short()+ ", within Blood Bay";
}
 
string
long_descr()
{
    return bloodsea_desc()+ "You find yourself within the protective confines " +
        "of Blood Bay, providing some respite from the worst of the weather. "
        +query_sailing_difficulty_desc()+ "\n";
}