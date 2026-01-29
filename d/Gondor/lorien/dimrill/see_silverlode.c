/* 
* /d/Gondor/lorien/dimrill/rooms/see_silverlode.c
* On the road south of Durins Stone, where the head of the Silverlode
* can be seen.  Road between Moria to the northwest and the forest 
* of Lothlorien in the east.
*
*Mona 2020
*/
#pragma strict_types

#include "../../lorien_defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit LORIEN_STD_DIR + "dimrill_base";

void 
create_dimrill_room()
{
    set_items_all_dimrill();
    set_items_near_dimrill();
    set_items_fauna_1();
    set_tells_silverlode_road();
    //set_tells_dimrill(); change tells here at silverlode
    //do not add stream descritipn functions to this file it is different
    set_short("Along the road near a stream");
    set_long(" The road continues upward as it travels northward and "+
    "westward through the valley, and towards the entrance to Moria, " +
    "which glares down from atop a mountain to the northwest. The road " +
    "eastward begins to be bordered to the north here by a stream that " +
    "flows out from amongst the rocks. The stream continues to tumble and " +
    "flow alongside the road, as it winds it's way southward and eastward " +
    "towards the low lands, where road and stream are lost in a golden " +
    "haze.\n");

    add_item( ({"rocks", "rock", "stream head", "head of stream"}),
        "The rocks appear to be basalt, smoothed and formed by the long " +
        "slow flow of time and the ages. There is a pool in the center of " +
        "a large half-buried boulder, from which an underground well of " +
        "water spills-over, forming a swiftly flowing stream. The air is " +
        "crisp and quite cool here. The water makes a soft scraping purr " +
        "as it rushes triumphantly down a steep rocky channel.\n");
    add_item( ("air"), "You can't SEE the air.\n");
    add_item( ({"water", "stream"}), 
        "The water is crystal clear, sparkling in the " +
        VBFC("light_type") + " where it emerges and spills over the lip " +
        "of the boulder. The water from this underground well is icy " +
        "and cold, noticable from the crisp coolness of the air here. " +
        "The well is a strong source, and the water flows swiftly, and " +
        "strong of current. It gurgles and crashes down the rocky channel," +
        " surging and foaming and turing white over the rapids.\n");
    add_item( ({"pool", "well", "source", "opening", "underground well"}),
        "The force of the water rising seems to have litterally worn " +
        "it's way through the rock on it's way to the surface.  The edges " +
        "of the pool are warn smooth, and soft and rounded.\n");
    add_item( ({"boulder", "big rock", "large boulder", "large rock",
        "half-buried boulder", "large half-buried boulder"}),
        "The deep-black rock of the boulder appears to be basalt. It has " +
        "been smoothed and and rounded by the passage of time. The water " +
        "rises from a well in the center. The force of the water rising " +
        "from underground seems to have literally worn its way through the " +
        "boulder on its way to the surface.\n");
    add_item( ({"edge", "edges", "lip"}), "The stone is smooth and clean " +
        "at the lip of the opening.  THe momentum of the water does not " +
        "allow the growth of algae.  The water is crystal clear.\n");
    add_item( ({"white water", "rapids"}),
        "The rapids are white water that occurs as water crashes, " +
        "frothing and foaming against obstacles.\n");
    add_item( ({"obstacles", "debris"}),
        "It is hard to see exactly because the water froths white around " +
        "the obstacles.  There are river rocks and debris, old logs, " +
        "and the like.\n");
    add_item( ({"logs", "old logs", "log"}),
        "You can tell much about them from here.  They are mostly " +
        "covered by the water, which froths white around them.\n");
    add_item( ({"river rocks", "river rock"}),
        "You can tell much about them from here.  They have been worn " +
        "smooth by the passage of time and water.  They are mostly covered " +
        "by the water, which froths white around them.\n");
    add_item( ({"channel", "rocky channel", "deep channel", 
        "rocky channel", "narrow channel"}),
        "The black rock of the narrow channel appears to be basalt.  It " +
        "has been cut deep into the rock by the passage of water, as " +
        "it tumbles and crashes past obstacles on it's way east.\n");
    add_item( ({"entrance", "entrance moria", "entrance to moria",
        "moria entrance"}),
        "You can see the great gates from here.\n");
//tells talk about sun moon make them exaable in base file
//  fix the below
    add_item( ("road"), "Mona needs to add the road desc to the base file.\n");

    add_exit(DIMRILL_DIR_RM + "road8", "north", 0, 3, 0);
    add_exit(DIMRILL_DIR_RM + "road8", "south", 0, 2, 0);
}