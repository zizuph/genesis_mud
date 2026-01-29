#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

#include "/d/Krynn/common/herbsearch.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

#define H1 KRHERB + "cladina"
#define H2 KRHERB + "cladina"
#define H3 KRHERB + "cladina"
#define H4 KRHERB + "cladina"

/*  Added when implementing the chislev temple  */
#define TPATH         "/d/Ansalon/goodlund/nethosak/chislev_temple/"

int undergrowth_removed;

void
reset_mithas_room()
{
   set_searched(random(4));
}

create_mithas_room()
{
    set_search_places(({"underbrush","herbs",
                       "trail", "path", "ground"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);
   
    reset_mithas_room();
    set_short("Forest of Mithas");
    set_long("@@long_descr"); 

    add_exit(MROOM + "forest82","north",0,2,1);
    add_exit(MROOM + "forest80","west",0,2,1);

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
     "able to cut your way through it.\n");

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

    add_cmd_item(({"underbrush","undergrowth"}),"cut","@@cut_underbrush");
    add_cmd_item(({"underbrush","undergrowth"}),"enter","@@enter_underbrush");
   
}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+ 
    "You are standing on a small path within a "+
    "vast emerald-green forest. The narrow forest "+
    "path stretches itself into several directions "+
    "here.\n";
}


int
cut_underbrush()
{
    if(P("sword",TP) || P("axe",TP) || P("halberd",TP) ||
        P("chip-knife",TP))
    {
        write("With a couple of quick slashes with your weapon, you manage to remove some "+
              "of the undergrowth.\n");
        undergrowth_removed =  1;
        return 1;
    }

    write("Try cutting down the undergrowth with a sharp weapon.\n");
    return 1;
}


int
enter_underbrush()
{
    if (undergrowth_removed == 1)
    {
        write("You enter the underbrush.\n");
        say(QCTNAME(this_player()) + " enters the underbrush.\n");

        /* Added Chislev Temple*/
        TP->move_living("",TPATH + "forest101.c", 1, 0);
        return 1;
    }
    write("What ?\n");
    return 1;
}

