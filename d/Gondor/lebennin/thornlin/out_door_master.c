/*
--------------------------------------------------
 This file was last edited :
-----------------05-02-95 00.05-------------------
 This is a master file for the village Thornlin
 in Lossarnach, Gondor.
 The file is for out door areas.
 the file name is out_door_master.c and should be
 located in the THORN_DIR defined in ~Gondor/defs.h
 This file was coded by :
 ^Sir Boromir Feb. 95
- - - - - - - - - - - - - - - - - - - - - - - - -
 Thanks to Olorin and Elessar for help and
 the field.c file and area_room.c
- - - - - - - - - - - - - - - - - - - - - - - - -
 Wishes and additions should be stated below along
 with reasson, please. Thanks :-)

    DATE -    WHO    -             REASSON
    15-feb-95 Olorin               changed inheritance to area_room
				   updated copied functions

    03-oct-95 Gorboth              changed so that athelas has a 1/5
				   chance of being selected by each
				   ONE_OF_LIST(LOSSARNACH_HERBS) check
    September 28, 2001, Serif: Fixed typos (missing newlines).
----------------- WISHES : -----------------------

------------------ ADDED : -----------------------

--------------------------------------------------
*/
#include "/d/Gondor/defs.h"
inherit (LIB_DIR + "area_room");

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "locals.h"
#include "lossarnach_herbs.h"


/* global variables in area_room:
static int     areatype,       //  1 = Grass, 2 = Trees, 3 = Farmland, 
			       // 4 = road, 5= Barren

static string  area,            // eg "northern"
	       areadesc,        // eg "green field", "forest"
	       areaname,        // eg "Anorien", "Lebennin", "Rohan"
	       land,            // "Gondor"
	       grass,           // (1), (2), (3): eg "soft green"
	       extraline,       // additional room description
	       treetype;        // (3), (7): eg "oak"
*/


static string     cityname,       // eg. "Thornlin"
crop,           // (3),(5) -  eg. "barley","wheat","oat crop"
//                "rye"
whereis;        // eg. "in","near"


void    set_cityname(string str)    { cityname = str;     }
void    set_crop(string str)        { crop = str;         }
void    set_whereis(string str)     { whereis = str;      }

string
short_desc()
{
    string desc;
    switch  (areatype)
    {
    case 1:
	if (!item_id("field"))
	    add_item("field", "The field is covered by " + grass + 
	      " grass all over.\n");
	if (!item_id("grass"))
	    add_item(({grass+" grass","grass"}),
	      "The " + grass + " grass grows all over the field.\n");

	desc = "a grassy " + areadesc + " " + whereis + " " + cityname + 
	" in the province of " + areaname + " in " + land;
	set_up_herbs( ({ ONE_OF_LIST(LOSSARNACH_HERBS),
	    ONE_OF_LIST(LOSSARNACH_HERBS),
	    ONE_OF_LIST(LOSSARNACH_HERBS), }),
	  ({ areadesc, "grass", "field", grass+" grass", "ground", }),
	  4 );
	break;
    case 2:
	if (!item_id(areadesc))
	    add_item(areadesc, "Below some tall trees, on the " + areadesc + 
	      " some " + grass + " grass is growing.\n");
	if (!item_id("trees"))
	    add_item(({"trees","tall trees", treetype, treetype + " trees"}),
	      "Some tall " + treetype + " trees are growing all over " + 
	      "this place, almost covering the sky.\n");

	desc = LANG_ADDART(areadesc) + " with tall trees " + whereis + 
	" the village of " + cityname + " in the province " + areaname +
	" in " + land;
	set_up_herbs( ({ ONE_OF_LIST(LOSSARNACH_HERBS),
	    ONE_OF_LIST(LOSSARNACH_HERBS),
	    ONE_OF_LIST(LOSSARNACH_HERBS), }),
	  ({ areadesc, "ground", }),
	  4 );
	break;
    case 3:
	if (!item_id("field"))  
	    add_item(({"field","fields"}), VBFC_ME("exa_field"));

	desc = LANG_ADDART(areadesc) + " field " + whereis + 
	" the village of " + cityname + " in the province " + areaname +
	" in " + land;
	set_up_herbs( ({ ONE_OF_LIST(LOSSARNACH_HERBS),
	    ONE_OF_LIST(LOSSARNACH_HERBS),
	    ONE_OF_LIST(LOSSARNACH_HERBS), }),
	  ({ areadesc, "field", "fields", "ground", }),
	  4 );
	break;
    case 4:
	if (!item_id("road"))
	    add_item(({areadesc + " road", "road"}), "You are on " +
	      LANG_ADDART(areadesc) + " road in " + areaname + ", " + 
	      land + ". You aren't sure where it leads though.\n");
	if (!item_id("ground"))
	    add_item("ground", "You are on a " + areadesc + " road.\n");

	desc = "this is "+LANG_ADDART(areadesc)+" road in the "+ 
	"province "+areaname+" in "+land;
	break;
    case 5:
	if (!item_id(areadesc))
	    add_item(({areadesc,"barren "+areadesc}), "It is a barren " + 
	      areadesc + " in " + land + ".\n");
	if (!item_id("ground"))
	    add_item("ground", "The ground is quite barren, so there is " +
	      "not much growing here.\n");
	desc = "a barren " + areadesc + " " + whereis + " the village of " + 
	cityname + " in the province of " + areaname + " in " + land;
	break;
    default:
	desc = LANG_ADDART(areadesc) + " " + whereis + " in the province " +
	"of " + areaname + " in " + land;
	break;
    }
    return desc;
}

string
exa_field()
{
    object  clock = find_object(CLOCK);
    string  desc = "You find yourself standing in the midst of a field.";

    switch (clock->query_season())
    {
    case "spring":
	desc += " The field have been tilled recently and are " +
	"obviously newly sown. You probably shouldn't " +
	"walk around in it.";
	break;
    case "summer":
	desc += " There are different crops growing on the fields, " +
	"you see some " + crop + " growing all around you.";
	break;
    case "autumn":
	desc += " The fields are full with ripe crops. On the field " +
	"the " + crop + " is curved with the weight of full ears.";
	break;
    case "winter":
	desc += " All the fields are harvested and lie barren for the winter.";
	break;
    default:
	break;
    }
    return (desc + "\n");
}

void
add_mountains()
{
    add_item(({"mountain", "mountains", "mindolluin", "white mountains", 
	"ered nimrais"}), "To the north, you can see the snow-covered " +
      "tops of the Ered Nimrais, the White Mountains, running from " +
      "west to east. The eastern spur of the White Mountains is the " +
      "Mindolluin, the great mountain west of Minas Tirith.\n");
}

/*
-----------------05-02-95 00.02-------------------
 Ones more Thanks to Elessar and Olorin for _LOTS_
 of help.
 EOF - hope it works !!!
--------------------------------------------------
*/
