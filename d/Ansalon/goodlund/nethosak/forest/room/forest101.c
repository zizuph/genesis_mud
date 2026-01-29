#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>


create_mithas_room()
{
    set_short("Path to ancient temple");
    set_long("@@long_descr"); 

    add_item(({"forest"}),
     "The forest looks ancient. Old logs and branches "+
     "fill the forest floor and the strong smell of "+
     "decay and moisture fills the air. The forest "+
     "consists of different sorts of trees, a "+
     "mixture of pines and oaktrees.\n");

    add_item(({"trees","oaktrees","pine trees", "pines"}),
     "The trees here consist of a mixture of pines "+
     "and oaktrees. Some of them look quite old "+
     "while others are fairly young.\n");

    add_item(({"underbrush","undergrowth"}),
     "The undergrowth doesn't look quite as dense here. You might be "+
     "able to enter it.\n");

    add_item(({"trail","path"}),
     "The forest trail twists itself further into "+
     "the forest. It's a bit overgrown with different "+
     "plants and herbs.\n");

    add_item(({"canopy", "treetops"}),
     "The canopy above you looks thick, only a few sunrays "+
     "are able to enter the forest. You notice a few birds "+
     "above you, but they quickly vanish in the thick canopy.\n");

    add_item(({"leaves","branches"}),
     "The branches and leaves here, have almost decomposed "+
     "into dirt. A few of them look alive, but "+
     "they are still covered with moss and fungus.\n");

    add_item(({"herbs","plants"}),
     "There are a lot of different herbs here! If you want to "+
     "look at a specific one, perhaps you should search for "+
     "it.\n");

    add_item(({"gates","gate"}),
     "The gates looks extremely sturdy. Perhaps you should knock on them "+
     "if you want some attention.\n");

    add_item(({"temple","building"}),
     "This must be the temple of an ancient druid order that once populated Mithas.\n");

    add_cmd_item(({"gate","gates"}),"open","@@open_gates");
    add_cmd_item(({"gate","gates"}),"knock","@@knock_gates");
    add_cmd_item(({"underbrush","undergrowth"}),"enter","@@enter_underbrush");   
}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+ 
    "You are standing on a narrow forest path which leads to an ancient temple. "+
    "The temple has been made out of pure white crystal with a wooden roof. Two heavy gates prevents "+
    "strangers from entering the holy place.\n";
}


int
open_gates()
{
    write("You try to open the gates, but fail. You must be too weak.\n");
    say(QCTNAME(this_player()) + " tries to open the gates, but fail.\n");
    return 1;
}


int
knock_gates()
{
    write("You knock on the gates.\n"+
        "You can hear someone moving around inside the temple. But nothing happens.\n");
    say(QCTNAME(this_player()) + " knocks on the gates.\n");
    return 1;
}

int
enter_underbrush()
{
        write("You enter the underbrush.\n");
        say(QCTNAME(this_player()) + " enters the underbrush.\n");
        TP->move_living("",MROOM + "forest81.c", 1, 0);
        return 1;
}

