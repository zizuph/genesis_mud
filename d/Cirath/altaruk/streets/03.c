#include "../defs.h"

inherit ALT_STD + "room.c";
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("mekillot",ALT_NPC+"mekillot_tame",1,0);
   bring_room_mob("falkior",ALT_NPC+"beastmaster",1,1);
}

void
create_street()
{

    short_name("the outskirts of Altaruk.");
    extra_line("A tall wall surrounds the town as part of its" +
        " defense against frequent attacks by giants. The buildings" +
        " here are erratic, many of them are nothing more than" +
        " make-shift tents. People are running carrying wares from" +
        " the caravans.");
    last_line("A caravan.");

    add_item(({"wall", "town wall"}), "A fifteen-foot stone wall" +
        " rises to the north of you. Despite its heavy defenses," +
        " Altaruk is destroyed on a regular basis by giants from" +
        " the islands of the Forked Tongue Estuary.\n");
        
    add_item("caravan", "The caravan here is basically a huge wagon" +
        " pulled by two large mekillots. The wagon has arrow slits" +
        " and spikes extruding from its lower parts. Its like a" +
        " slow moving fortress able to carry a huge load of goods" +
        " across the dry wastes.\n");

    add_exit("02", "west", 0,1,0);
    add_exit("04", "southwest", 0,1,0);
    add_exit("05", "south", 0,1,0);
    
    reset_room();
}
