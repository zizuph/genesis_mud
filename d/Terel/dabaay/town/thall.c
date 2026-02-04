/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 *
 * Town Hall of Dabaay
 * Goldberry November, 1999 
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#define DAB_TOWN DABAAY_DIR + "town/"
#define DAB_NPC  DABAAY_DIR + "npc/"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    set_short("Inside the Town Hall");
    set_long(
        "You are inside of the Town Hall of Dabaay. This is a fairly "+
        "simple, yet functional center for the village's activities. "+
        "Around you can be seen a wooden table with several chairs "+
        "next to it, a large rug, and a warm fireplace. There is also "+
        "a poster hung up on one wall.\n");
 
    add_item(({"table","wooden table"}),
        "A large, polished table, with several chairs set next to "+
        "it. It looks large enough to hold a meeting for a fair "+
        "number of people.\n");

    add_item(({"chair","chairs"}),
        "Simple, yet comfortable looking chairs made of wood.\n");

    add_item(({"rug","large rug"}),	
        "A large brown and gold colored rug takes up most of the "+
        "floor of the room. The design on it is simplistic yet "+
        "attractive.\n");
    
    add_item(({"fireplace"}),	
        "A large fireplace, made of stone and mortar, emits a pleasant "+
        "warmth from the back wall.\n");

    add_item(({"poster","visitors guide","guide"}),
        "A large poster, attached to one wall. It appears to be a "+
        "visitor's guide for the town.\n");

    add_item(({"wall","walls","floor"}),
        "The walls and floor and made of rough-sawn planks, nailed "+
        "edge to edge.\n");

    add_cmd_item(({"poster","guide","visitors guide"}),"read",
        "  Welcome to visitors of Dabaay!\n"+
        "---------------------------------\n"+
        "Enjoy your peaceful stay here\n"+
        "in our open and friendly village.\n"+
        "We have big-town amenities\n"+
        "without all the big-town fuss.\n"+
        "If you are looking for passage\n"+
        "overseas, you will find our docks\n"+
        "out past the eastern edge of town.\n"+
        "For inland travellers, the town\n"+
        "of Calathin lies out north and\n"+
        "west.\n"+
        "---------------------------------\n"+
        "Mayor: Drew\n"+
        "Population: 60\n");
    
    add_exit(DAB_TOWN + "square1_5", "east", 0);
    INSIDE;
    reset_room();
}
