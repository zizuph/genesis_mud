/*
 *  forest101.c
 *
 *  This is a room for the druid temple in Mithas,
 *  it is the entrance to the temple in fact. It
 *  has a check for banished enemies, who will not
 *  be able to log in until the property has been 
 *  removed.
 *
 *  Created by Carnak, January 2016
 */

#pragma save_binary

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"

inherit MITHAS_OUT;

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Krynn/common/herbsearch.h"

#define H1 "/d/Krynn/common/herbs/chantrelle"
#define H2 "/d/Krynn/common/herbs/amanita"
#define H3 "/d/Krynn/common/herbs/fdlhead"
#define H4 "/d/Krynn/common/herbs/solinaith"

#include "./local.h"

#define I_AM_BANISHED "_i_am_banished"

void
reset_mithas_room()
{
    set_searched(random(4));
}

create_mithas_room()
{
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
	
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);
	
    reset_mithas_room();
	
    set_short("Path to ancient temple");
    set_long("@@long_descr");

    add_exit("", "north", "@@open_gates", 0, 1);
	
    add_item(({"forest","surroundings"}),
    "The forest looks ancient. Old logs and branches fill the "+
    "forest floor and the strong smell of decay and moisture "+
    "fills the air. The forest consists of different sorts of "+
    "trees, a mixture of pines and oaktrees.\n");

    add_item(({"trees","oaktrees","pine trees", "pines"}),
    "The trees here consist of a mixture of pines and oaktrees.\n");

    add_item(({"underbrush","undergrowth"}),
    "The undergrowth doesn't look quite as dense here. You might "+
    "be able to enter it.\n");

    add_item(({"trail","path"}),
    "The forest trail twists itself further into the forest. "+
    "It's a bit overgrown with different plants and herbs "+
    "species.\n");
    
    add_item(({"canopy", "treetops"}),
    "The canopy above you looks thick, only a few sunrays are "+
    "able to enter the forest. You notice a few birds above you, "+
    "but they quickly vanish in the thick canopy.\n");

    add_item(({"leaves","branches","dirt"}),
    "The branches and leaves here, have almost decomposed into "+
    "dirt. Only a few of them looks fairly new, but they are "+
    "still covered with moss and fungus.\n");

    add_item(({"herbs","plants"}),
    "There are a lot of different herbs here, if you wish to "+
    "look at a specific one, perhaps you should search for it.\n");

    add_item(({"gates","gate","heavy gates"}),
    "The gates look extremely sturdy. Perhaps you should knock "+
    "on them if you want some attention.\n");

    add_item(({"temple","building","ruins","ruin","ancient temple",
	"structure"}),
    "This must be the temple of an ancient druid order that once "+
    "populated Mithas.\n");
    
    add_item(({"roof","wooden roof"}),
    "The wooden roof appears to be in pristine condition.\n");
    
    add_item(({"roots","wall","walls","stone walls","cracks"}),
    "The roots have found their way into the cracks between the "+
    "stones that make up the wall, seemingly reinforcing the "+
    "structural stability.\n");

    add_item(({"vegetation"}),
    "The vegetation that adorn the stone walls of the ruins "+
    "has grown with time to mask the presence of this "+
    "structure.\n");

    add_item(({"moss","fungi","fungus"}),
    "The moss and fungi grow widespread in this area.\n");

    add_item(({"stones"}),
    "The granite stones in the walls are encompassed in roots "+
    "and covered in patches of moss and fallen leaves.\n");
	 
    add_cmd_item(({"gate","gates"}),"open","@@open_gates");
    add_cmd_item(({"on gate","on gates","gate","gates"}),"knock",
    "@@knock_gates");
    add_cmd_item(({"underbrush","undergrowth"}),"enter",
    "@@enter_underbrush");   
}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+ 
    "You are standing on a narrow forest path which leads to "+
    "an ancient temple. The stone walls of the temple have been "+
    "overgrown with the surrounding vegetation, a coexistence "+
    "of roots and ruins attesting to the miraculous force of "+
    "nature. Though the temple has weathered with time and "+
    "merged with its surroundings, its wooden roof is in "+
    "seemingly pristine condition which indicates that it has "+
    "been well kept. Two heavy gates prevent strangers from "+
    "entering this holy place.\n";
}


int
open_gates()
{
    if (TP->query_prop(I_AM_BANISHED))
    {
        write("You pull on the gates without success.\n"+
        "A voice echoes in your head 'Your kind is not "+
        "welcome here.'\n");
        say(QCTNAME(TP) + " attempts to open the gates, but "+
        "fail.\n");
        return 1;
    }
    
    write("You pull the gates open with a creaking sound, and "+
    "enter the temple.\n");
    say("The gates creak as " + QTNAME(TP) + " leaves the "+
    "temple, closing the gates behind " + HIM(TP) + ".\n");
    
    TP->move_living("M",TDIR + "temple2.c", 1, 0);
    
    write("You close the gates behind you.\n");
    say(QCTNAME(TP) + " enters the temple, closing the doors "+
    "behind " + HIM(TP) + ".\n");
	
    if (file_size(TLOG + "entrylog") > 100000)
        rename(TLOG + "entrylog", TLOG + "entrylog.old");
	
    write_file(TLOG + "entrylog", ctime(time()) + " " +
	"*** " + TP->query_name() + " has entered the Temple ***"+
    " Average: " + TP->query_average_stat() +
    ", Race: " + TP->query_race_name() +
    ", Alignment: "+ TP->query_alignment() + "\n");
	
    return 1;
}


int
knock_gates()
{
    write("You knock on the gates.\n"+
    "You can hear someone moving around inside the temple. But "+
    "nothing happens.\n");
    say(QCTNAME(TP) + " knocks on the gates.\n");
    return 1;
}

int
enter_underbrush()
{
    write("You enter the underbrush.\n");
    say(QCTNAME(TP) + " enters the underbrush.\n");
    
    TP->move_living("M",MROOM + "forest81.c", 1, 0);
    
    say(QCTNAME(TP) + " arrives from within the underbrush.\n");
    return 1;
}