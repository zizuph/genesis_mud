/*
 * calathin1/entry.c
 *
 * Lilith, Nov 2021
 *
 */

#pragma strict_types

#include "h1.h"

// Can't inherit housebase, it will throw people out before
// they get to the door.
inherit "/std/room";

void 
create_room()
{
    add_exit(MAIN_ACCESS, "south");

    room_add_object(DOOR +"h1_out", 1);

    set_short("front stoop");
    set_long("This is the front stoop of the townhouse. "+
      "It provides just enough shelter from the weather to "+
      "allow those letting themselves inside to do so without "+
      "bringing snow and wind in with them. "+
	  "This townhouse, like all the others in the row, is made "+
      "of stacked silver pine logs with white clay chinking "+
      "between the logs.\n");

    add_cmd_item("sign", "read", "@@sign_desc@@");
    add_item(({"sign", "small sign", "rectangle"}), "@@sign_desc@@");
    add_item(({"east"}), "There is a townhouse to the east.\n");
    add_item(({"west"}), "There is another townhouse to the west.\n");
    add_item(({"north"}), "The large door to the townhouse is "+
       "the glossy red color of holly berries.\n");
    add_item(({"south"}), "The West Road is south of here.\n");
    add_item(({"stoop", "front stoop"}), "This is the small "+
       "area where people stand when letting themselves into "+
       "and out of the townhouse.\n");
    add_item(({"air", "breeze", "wind"}), "The wind claws with icy "+
        "fingers. It smells of woodsmoke and pine.\n");
    add_cmd_item(({"air", "breeze", "wind"}), ({"smell", "sniff"}),
        "The air smells of a mixture of woodsmoke and pine sap.\n");
    add_item( ({"sky", "up"}), 
        "The sky is a clear, deep blue with no sign of dragons.\n");				
    add_item(({"townhouse", "walls", "logs"}), 
        "This is a two-story townhouse built of silver pine logs, "+
        "with pretty white-clay chinking.\n");
    add_item(({"chinking", "chink", "clay", "white clay"}), 
        "The chinks between the logs have been filled in with a "+
        "mixture of white clay and straw.\n");
    add_item(({"view", "surroundings"}),
        "To the west is a stunning view of jagged, snow-capped "+
        "mountains. South is a river flowing sluggishly east. "+
        "The town square lies east, while north is dense forest.\n");
    add_item(({"north", "forest", "dense forest", "silver pine forest"}),
        "Calathin has slowly encroached upon the forest of silver "+
        "pines that lies north of the river and extends all the "+
        "way up into the high hills of the icy mountains. The "+
        "forest here has been cut back and thinned out, as "+
        "evidenced by the numerous stumps scattered throughout.\n");
    add_item(({"tree stumps", "stumps"}), "Trees have been logged "+
        "extensively in this section of Calathin, and numerous "+
        "stumps can be seen.\n");
    add_item(({"river", "south" }), "Some distance south of here, "+
        "a river makes it's way to the east, carrying water from "+
        "the mountains to the sea.\n");		
    add_item(({"mist", "ice mist"}), 
        "The mist is just the effect of the chill weather on the "+
        "water vapor in the air.\n");
    add_item(({"ground", "floor", "down"}),
        "The ground is covered in a thin layer of ice and snow. "+
        "It never seems to warm up enough to completely melt.\n");
    add_item(({"ice", "snow"}), "It is ubiquitous. Ice and snow "+
	    "everywhere. It wouln't be Calathin without it.\n");
    add_item(({"west", "mountains", "mountain range"}),
        "These mountains are beautiful.  Snow capped and majestic.  "+
        "Breathtaking. And terrifying.\n");
    add_item(({"east", "town", "town square", "building", "buildings"}), 
        "The number of buildings increases toward the east, where the "+
        "center of town lies.\n");	
    add_item(({"terrace", "stone terrace", "slate terrace", "slate"}), 
        "The terrace is made of pieces of slate fitted together "+
        "with a handspace between.\n");


}

string
sign_desc()
{
    return
    "Gold letters have been painted on a black-lacquered "+
    "rectangle of wood:\n\n"+
    "     T O W N H O U S E   O N E    	\n";		
    "\n";
}
