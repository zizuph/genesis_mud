/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * e4.c
 * road from Dabaay
 *
 * Goldberry October 7, 1999 
 */

#include "/d/Terel/include/Terel.h"
#define  DAB_ROAD DABAAY_DIR + "road/"
#define  DAB_TOWN DABAAY_DIR + "town/"

inherit DAB_ROAD + "road";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("On a dirt path outside of a village");
    set_long(
        "You are making your way along a path that slopes down from the "+
        "west to the east. A small fishing village lies to the east of you. "+
        "Beyond the village to the east, you can see a deep blue ocean, with "+
        "white-capped waves breaking close by. To the west, you can see the "+
        "beginnings of a dense forest.\n" +
        "There is a battered wooden sign on a post beside the path.\n");
    
    add_item(({"forest","forests"}),
        "Trees and shrubs of various species, line the road to the west.\n");

    add_item(({"tree","trees"}),
        "You can see several different varieties of trees. From conifers "+
        "and pines, to old oaks and cedars, the forests seem to thrive with "+
        "ancient life.\n");

    add_item(({"shrub","shrubs","bush","bushes"}),
        "Various evergreens and leafy vines contend for the remaining "+
        "soil among the trees.\n");

    add_item(({"breeze","ocean breeze"}),
        "Strong hints of fish and saltwater float up from the east.\n");

    add_item(({"ocean","horizon","blue ocean","blue line"}),
        "Off to the east, you can make out a deep blue body of water. "+
        "You can see a line of white-capped waves breaking near by.\n");

    add_item(({"breakers","white-capped waves","waves"}),
        "The ocean waves appear to be breaking on something near by to "+
        "village. You cannot make out what they are hitting from this "+
        "distance.\n");

    add_item(({"village"}),
        "The village to your east, shows all the signs of a small fishing "+
        "community. Travellers of several races can be seen passing by on "+
        "the roads.\n");

    add_item(({"sign","wooden sign","battered sign","battered wooden sign"}),
        "This sign has all the appearances of once being a proud welcoming "+
        "to passers-by and visiting travellers. Now it is little more than "+
        "well-weathered wood boards nailed to a leaning post. The sign is "+
        "still perfectly legible though.\n");

    add_cmd_item("sign","read",
        " Welcome to the port city of Dabaay\n"+
        "\n"+
        "Enter and enjoy wares and delicacies\n"+
        "  from the finest local artisans!\n"+
        " Or sample exotic imports from all\n"+
        "        of the realms!\n"+
        "\n"+
        "                Mayor Drew Rolbladir\n");
    
    add_exit(DAB_ROAD + "e3", "west", 0);
    add_exit(DAB_TOWN + "square1_1", "east", 0);
}
