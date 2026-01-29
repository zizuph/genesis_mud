#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include "local.h"
inherit GRAVE_STD;

create_solace_room()
{
    set_short("Old Graveyard");
    set_long(BS("This is more of the old graveyard. The grounds keeper shou" +
		"ld really cut back those brambles that block the south. " +
		"A young" +
		" maple tree has managed to win out over the brambles and gro" +
		"ws between two of the old gravestones. An old, peeling, wr" +
		"ought iron fence runs from west to east along the northern " +
		"side of these graves.", 70));

    add_item("brambles", BS(
               "The brambles are very thick and full of huge very sharp thor" +
               "ns. They make all movement in that direction impossible." +
               "", 70));
    add_item(({"young maple", "young maple tree", "maple", "maple tree", 
              "tree"}), BS("This young maple tree is very healthy and very g" +
              "reen. It is just big enough to lean comfortably against. Al" +
              "l of a sudden you feel the weariness of your adventuring and " +
              "feel so tired. This really does look like a good place to sn" +
              "ooze.", 70));
    add_item(({"fence", "old fence", "wrought iron fence"}), BS(
        "This is the fence that divides the new grave from the old one.  It" +
        " is in bad need of repair and painting. It is fairly free of vines" +
        " and brambles here.", 70));
    add_item(({"flowers", "flower", "pretty flowers"}),("\n" +
             "There are a dozen long stemed roses.\n"));
    add_item(("roses"), ("They are red and look freshly cut.\n"));

    add_cmd_item(({"the", "fence"}), "jump", "@@over_fence");
    add_cmd_item("fence", "climb", "@@over_fence");
    add_cmd_item("roses", "smell" , "They smell wonderful!!\n");

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "o_grave2", "east", "@@east_msg");
    add_exit(TDIR + "o_grave0", "west", "@@block");

    set_alarm(10.0,0.0,"windsay");
}

string
over_fence() 
{    
    return "The fence proves too much a challenge to climb.\n";
}

void
windsay()
{
     tell_room(TO, "Chaos and death draw you closer to nothingness !!\n");
}

block()
{
    if(this_player()->query_skill(SS_TRACKING) > 20)
    {
        write("You manage to find a small track through the brambles " +
            "you can push through.\n\n");
        return 0;
    }
    write("You walk a few steps west but find that the brambles grows " +
	"too thick. You cannot seem to find a path through them!\n");
    return 1;
}
