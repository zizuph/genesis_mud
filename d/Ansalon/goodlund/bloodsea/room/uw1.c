#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit BLOODSEA_OUT;
inherit "/d/Krynn/std/herbsearch";

#define HARD_TO_SWIM  55

string *herbs = HERB_MASTER->query_herbs( ({ "seabottom","intertide", }) );

void
reset_bloodsea_room()
{
    set_searched(random(2));
    { 
    if (random(2))
      return;
    }
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item("surface","Above you is the surface of the Bloodsea of Istar.\n");
    add_item(({"isle","mithas","isle of mithas"}),
        "You cannot see the isle from here, as your vision underwater is limited.\n");
    add_item(({"cathedral","spire","highest spire","ancient cathedral","entrance"}),
        "Not far from where you float is the tip of the highest spire of an ancient " +
        "cathedral that was long ago submerged beneath the waters of the Bloodsea. " +
        "Far beneath you amongst a forest of kelp you can just make out the entrance " +
        "to the cathedral. You could probably swim down to it.\n");
    add_item(({"kelp","sea kelp","forest"}),
        "Around the base of the cathedral has grown a forest of tall sea kelp. It silently " +
        "sways to and fro with the current.\n");

    add_invis_exit(BROOM +"4l", "up", 0, 2);
    add_invis_exit(BROOM +"uw2", "down", 0, 2);

    add_cmd_item(({"down","water","to ruin","to cathedral","ruin","cathedral"}),
         ({"dive","swim"}),"If you want to swim down, just head in that direction!\n");

    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER); 

   seteuid(getuid(TO));
   set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "kelp","sea","water" }), 4);

    reset_bloodsea_room();

}

void
set_sink_path(string sp)
{
    sink_path = BROOM + "uw2";
}

string
short_descr()
{
    return "close to the surface of the Bloodsea of Istar, near a sunken cathedral";
}
 
string
long_descr()
{
    return "You find yourself floating close to the surface of the Bloodsea of Istar " +
       "near the isle of Mithas. Just beneath you is the highest spire of an ancient " +
       "cathedral that was long ago submerged when the Bloodsea of Istar flooded these " +
       "lands. Down below you is the entrance to the cathedral, barely visible amongst " +
       "a forest of sea kelp.\n";
}