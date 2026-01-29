#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>


inherit BLOODSEA_OUT;

#include "/d/Krynn/common/herbsearch.h" 

#define HARD_TO_SWIM  55

#define KRHERB "/d/Krynn/common/herbs/"
#define H1 KRHERB + "bull_kelp"
#define H2 KRHERB + "elkhorn_kelp"
#define H3 KRHERB + "laminaria"
#define H4 KRHERB + "sea_bubble"

void
reset_bloodsea_room()
{
   set_searched(random(2));
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item("surface","Above you is the surface of the Bloodsea of Istar.\n");
    add_item(({"isle","mithas","isle of mithas"}),
        "You cannot see the isle from here, as your vision underwater is limited.\n");
    add_item(({"wooden doors","doors"}),
        "You can find no wooden doors. They long ago rotted away.\n");
    add_item(({"ancient cathedral","entrance","darkness","temple"}),
        "To your east is the sunken ruins of a once grand cathedral. Back before the cataclysm, " +
        "this was a holy temple to one of the old gods, standing tall and proud for all to see. " +
        "Now it is forgotten and hidden beneath the waters of the Bloodsea from all but the " +
        "occasional sea creature. The entrance to the cathedral is open before you, its doors having " +
        "rotted long ago. You could probably enter it into the inner darkness of this temple.\n");
    add_item(({"kelp","sea kelp","forest"}),
        "A forest of kelp surrounds you, swaying gently with the current. It seems the only direction " +
        "you can swim through it is either up or to your northwest.\n");

    add_invis_exit(BROOM +"uw1", "up", 0, 2);
    add_invis_exit(BROOM +"uw3", "northwest", 0, 2);
    add_swim_exit(BROOM + "cathedral","in", 0, 2);


    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
 
    seteuid(getuid(TO));
    set_search_places(({"kelp","sea","herbs"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);

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
    return "in a forest of kelp at the bottom of the Bloodsea of Istar, near the " +
       "entrance to a sunken cathedral";
}
 
string
long_descr()
{
    return "You find yourself floating at the bottom of the Bloodsea of Istar " +
       "surrounded by a forest of kelp. To your east is the sunken ruins of a " +
       "cathedral to the old gods, still impressive even after all these years " +
       "submerged at the bottom of the sea. Its great wooden doors long ago " +
       "rotted away, its entrance opening up like the maw of a sea beast, leading " +
       "inside into darkness. To your northwest the sea kelp opens up somewhat. You " +
       "could probably swim in that direction too.\n";
}