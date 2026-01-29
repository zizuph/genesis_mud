// file name:    marsh70
// creator(s):   Ilyian (28 August, 1995)
// last update:  Lilith Aug 2021  added exit to new barrow area
//               Lilith Sep 2021  added statserv logging 
// purpose:      
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"
#include "/d/Avenir/smis/sys/statserv.h"


string exa_gap()
{
	return "Peering intently, you can finally see the gap between "
	   +"the north and west stones. It was very easy to miss and "
	   +"you privately congratulate yourself on noticing it.\n";
}

void
create_room()
{
    marsh_long(randmarsh[random(sizeof(randmarsh))]+" The marsh "
        +"ends abruptly to the east, where a steep dropoff "
        +"ends in the sea below, and to the north and west, "
        +"a large hill rises out from the swamp.");

    add_hill();

    AI(({"dropoff","cliff"}),"It falls quite steeply down into "
        +"the murky sea below. Fog from the marsh slowly rolls "
        +"over the edge.\n");
    AI(({"sea","ocean","water"}),"The great dark sea spreads out "
        +"to the east as far as you can see. Its gentle waves lap "
        +"softly against the side of the cliff.\n");
    AI(({"hill"}), "You can see that some massive stones stand to"
        +"gether to form the hill, the cracks between them filled "
        +"with dirt and obscured by mist.\n");
    AI(({"stones", "massive stones"}), "Time has covered these "
        +"old stones with lichen and dirt. They lean against each "
        +"other toward the northwest. Most of them are fitted "
        +"tightly together, but as the mist parts you think "
        +"you can see a gap in the stones.\n");
    AI(({"crack", "gap"}), "@@exa_gap");
    am("69","south");
    AE(HILL+"hill12","west",0,5);
    AE(HILL+"hill15","north",0,5);
    AE(BARROW +"barrow0","northwest"); 

    reset_room();
}
void
reset_room()
{
    set_searched(0);   marsh_reset();
}
		
		