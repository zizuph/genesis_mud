
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_castle_guard_3south"))
    {
        object guard;
	guard=clone_object(RHUN+"npc/castle_guard");
        guard->set_living_name("_castle_guard_3south");
        guard->move(TO);
    }
    if(!present("_rhosgobel_quest_silver_dust"))
    {
	    clone_object(RHUN+"castle/silver_dust")->move(TO);
    }
}

create_room()
{
    set_short("Guest room");
    set_long("This is a once-elegant guest chamber in the stone "+
	"castle.  But time has worn away at the curtains, the "+
	"fine rugs, the beautifully-crafted wooden furnishings, so "+
	"that now, little of its beauty and charm remains.  The only "+
	"exit is back into the wide hall to the northeast.\n");

    add_item(({"curtains", "curtain", "rug", "rugs"}), "The rugs "+
	"and curtains which lie and hang here, respectively, were "+
	"once very fine, but the passage of time has left them "+
	"tattered and old, no long interesting.\n");
    add_item(({"furnishings", "wood", "wooden", "furniture"}), 
	"A fine wooden desk and chair stand nearby, as well "+
	"as a large guest bed.  The all are intricately carved "+
	"and well-varnished, though now dirty and covered with "+
	"a thick layer of dust from disuse.\n");
			
    AE(RHUN+"castle/3east", "northeast");

    IN;

    reset_room();
    
}
