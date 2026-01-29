/*
 * Road leading to Causeway from Great East Road
 * -- Finwe, March 2005
 */

#include "local.h"

inherit BASE_COMMON;
inherit EAST_ROAD;

string gate_check();

void
create_er_room()
{
    areadesc = "field";
    area = "west of";
    areaname = "the Brandywine river";
    land = "Eriador";
    areatype = 1;

    grass = "green";
    
    extraline = "The country lane runs north and south. It rises up " +
    "and joins a large causeway that runs north and south. The land " +
    "is drier here, and the village of Stock is to the west of the lane.";

    set_add_plains();
    set_add_brandywine();
    set_add_road();
    set_add_plants();
    set_add_causeway();

    add_item(({"causeway"}),
        "It is a raised road and crosses the fields to the south. The " +
        "causeway is as wide as the country lane and looks strong. It " +
        "is made of squared stone blocks, and stops the river when " +
        "it floods, drowning everything west of it.\n");
    add_item(({"village", "hobbit village", "stock"}),
        "The hobbit village is called Stock. It's a small village and " +
        "sits west of the lane. There is gate leading west. It is " + 
        gate_check() + " to visitors.\n");
    add_item(({"gate"}),
        "The gate is square and strong looking. It is made of iron and is " + 
        gate_check() + " to visitors.\n");
    add_item(({"stone blocks", "squared stone blocks", "blocks", 
            "stone block", "squared stone block", "block"}),
        "They are squared and look strong. They are stacked on top of " +
        "each other and form the strong causeway. The lower stones " +
        "have various water marks showing how high the river has flooded " +
        "in the past.\n");
    add_item(({"lower stone blocks", "lower squared stone blocks", 
            "lower blocks", "lower stone block", "lower squared stone block", 
            "lower block"}),
        "These stone blocks are square and strong looking, too. They " +
        "are often submerged when the river floods, so they look lighter " +
        "than the rest of the stone blocks. There are many watermarks " +
        "on them showing how high the water has risen.\n");
    add_item(({"mark", "marks", "watermarks", "watermark"}),
        "They are dark, horizontal marks on the causeway. They mark " +
        "how high the river has flooded in the past. Some are very dark from " +
        "when the water flooded to that level mulitiple times.\n");
        
    add_exit(EAST_R_DIR + "er21s4","north",0,2);
    add_exit(EAST_R_DIR + "cause01","south", "@@up_to_cause@@");
    add_exit(EAST_R_DIR + "cause01","up", "@@up_to_cause@@",2,1);
    add_exit(EAST_R_DIR + "stock_entr", "west","@@block_room@@",2,1);

}

string gate_check()
{
    int gate_status = 0;    // closed

    if(gate_status == 0)
        return "closed";
    else
        return "opened";
}

int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You cannot go there, the gate is closed.\n");
return 1;
}

void
init()
{
    ::init();

    add_action("skip_rock", "skip");
}


int skip_rock(string str)
{
    int skip_count = random(10);
    string skip_msg = "";

    if(skip_count < 1)
    {
        skip_count = 1;
        skip_msg = "splashes into the river with a 'plop' and sinks.";
    }
    else if(skip_count == 1)
    {
        skip_msg = "skips across the river one time and " +
        "sinks into the water.";
    }
    else if(skip_count >=7)
    {
        skip_msg = "skips across the river " + LANG_NUM2WORD(skip_count) + 
        " times and lands on the other side.";
    }
    else
    {
        skip_msg = "bounces across the river " + LANG_NUM2WORD(skip_count) +
        " times and sinks into the water.";
    }


    if(str == "rock" || str == "stone")
    {
        write("You scan the area for a flat rock.\n");
        write("You spy one and pick it up.\n");
        write("You wind up and toss it at the river.\n");
        write("It " + skip_msg + "\n");

        say(QCTNAME(TP) + " scans the area for a flat rock. " + 
        CAP(HE_SHE(TP)) + " spys one and picks it up. " + 
        CAP(HE_SHE(TP)) + " takes aim and tosses it at the river. It " + 
        skip_msg + "\n");
        return 1;
    }
    write("Skip what, a rock?\n");
    return 1;
        
}
