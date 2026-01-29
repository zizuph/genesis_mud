#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"

inherit BLOODSEA_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

string *herbs = HERB_MASTER->query_herbs( ({ "intertide", }) );

void
reset_bloodsea_room()
{
    set_searched(0);
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"pier","wooden pier","small pier","small wooden pier", "piers"}), 
               "To your east you can wade to a very old and wooden pier.\n");
    add_item(({"bay","horned bay","bloodsea","blood sea"}), "The Horned Bay "+
               "stretches itself towards the northwest where it meets the Bloodsea.\n");
    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. Rumour has it that the colour "+
               "is the result of the blood of many victims who lost their "+
               "lives during Krynn's most terrible hour, though it "+
               "could be the clay stirred up from the sea bottom by the "+
               "maelstrom.\n");
    add_item(({"mithas", "isle", "village", "nethosak"}), "The great Imperial "+
             "city of Nethosak, home of the minotaurs of Ansalon, lies to the "+
             "east. This great city is the home of the Emperor of the Minotaurs "+
             "and the Great Arena, where minotaurs and other lucky 'volunteers' "+
             "fight against each other, sometimes to the death. This is also the "+
             "place of the Temple of the Stars, where the High Priest of the "+
             "minotaurs performs rituals to their god. A strong smell of "+
             "smoke and sweat fills the air.\n");

    add_row_exit(BROOM + "1f", "north", 0, 1);
    add_row_exit(BROOM + "2e", "west", 0, 1);
    add_row_exit(BROOM + "1d", "south", 0, 1);
    add_wade_exit(BROOM + "1f", "north", "@@swim_off", 1);
    add_wade_exit(BROOM + "1d", "south", "@@swim_off", 1);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_bloodsea_room();

}

int
swim_off()
{
   write("You swim along the side of the pier.\n");
   return 0;
}

void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}

string
short_descr()
{
    return "Horned Bay near the Nethosak piers";
}
 
string
long_descr()
{
    return "You are near the piers of Horned Bay, where the minotaurs " +
    "of Nethosak dock. " +bloodsea_desc()+
    "\n";
}