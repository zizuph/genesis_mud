/*
 * Base file for Bree Orc Camp
 * Based on the Greenfields orc camp tent file
 * By Finwe, July 2000
 */

#include "/d/Shire/sys/defs.h"
#include "local.h"
//#include "/d/Shire/common/bree/orc_camp/camp.h"
inherit AREA_ROOM;
inherit CAMP_DIR + "evendim_orcs"; 
inherit "/d/Shire/std/room/room_tell";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define LATE_NIGHT      0..3        /* 12am -  3am */
#define EARLY_MORNING   4..7        /*  4am -  7am */
#define MORNING         8..10       /*  8am - 10am */
#define NOON            11..13      /* 11am -  1pm */
#define AFTERNOON       14..17      /*  2pm -  5pm */
#define EVENING         18..21      /*  6pm -  9pm */
#define EARLY_NIGHT     22..24      /* 10pm - 12am */

//void reset_shire_room();
void create_camp_room() {}
static string extra_wall   = ""; 
 
public void
create_area_room()
{
    set_area("in the hills of Evendim in");
    set_areaname("the orc camp");
    set_land("Eriador");
    set_areatype(0);
    set_areadesc("track");
    set_grass("sparse, dry");
    set_treetype("broken");

    add_item(({"tent","tents"}), 
      "These tents are all alike, crudely patched together from scraps "+ 
      "of uncured hide, canvas, and leather.  Their basic shape is a "+ 
      "large A-frame, made of four support poles and a center ridge "+ 
      "pole.  The tents have large gaps between the poorly attached "+ 
      "materials, and most likely do a terrible job of keeping out the "+ 
      "weather.\n"); 
    add_item(({"ground","dirt"}), 
      "The ground here alternates between hard, packed dirt and a "+ 
      "thick, sticky stew where things have been spilt or left out to "+ 
      "rot in the air.  It is fairly obvious this area receives regular "+ 
      "traffic from many booted feet that care not what they trample. "+ 
      "Little vegetation has survived the occupation, with sparse clumps "+ 
      "of grass and weeds poking up through the debris occasionally.\n");  
    add_item(({"trash","debris","rubbish","stew", 
        "puke","fecal matter","food","flesh","materials"}), 
      "This is a morass of fecal matter, puke, food, shreds of flesh "+ 
      "and many other types of materials all churned into the ground "+ 
      "by the occupying forces.  The stench is horrible.\n"); 
    add_item(({"vegetation","grass","weeds","weed"}), 
      "What little there is of it barely survives off what little "+ 
      "sunlight, water, and nutrients reach it here. The vegetation is "+ 
	  "sparse and in patches.\n");
    add_item(({"fire","campfire","fires","campfires"}),
      "Small campfires are scattered throughout the campsite, "+
      "providing some light in the heavy mist.  However, they also "+
      "cause lots of dancing shadows to confuse the eyes.\n");
    add_item(({"skulls", "heads"}),
        "They are human, elf, and, dwarf heads, impaled on top " +
        "of the standards.\n");
    add_item(({"human heads", "elf heads", "dwarf heads"}),
        "They are decapitated heads impaled onto the large standard.\n");
    add_item(({"standards","pole","poles"}), 
    "They are sturdy poles set into the ground and surround the " +
    "tents. The poles have various black flags attached to them " +
    "and on top of the poles are orc trophies from their many " +
    "raids, the grim remains of human, elven and dwarven skulls. " +
    "Many of the skulls are leathery from exposed weather and " +
    "have been picked clean by scavangers. Strands of hair blow " +
    "from the skulls in the occasional breeze.\n");

    create_camp_room();
	reset_shire_room();

}

/*
void create_room()
{
    ::create_room();
    create_camproom();
}
*/

int
block_way()
{
    if(present("_invading_orc_"))
    {
	write("The orc won't let you past!\n");
	return 1;
    }
    return 0;
}