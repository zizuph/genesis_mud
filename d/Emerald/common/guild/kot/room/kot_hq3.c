/*
 * KOT_HQ3.c
 * Keepers of Telberin Guild Hall - Warrior's Training Room
 * - Alaron January 1997
 */

#include "../guild.h"
#include <ss_types.h>
#include <stdproperties.h>

inherit "/std/room";
inherit "/lib/skill_raise";

void
create_room()
{
    set_short("Training Room");
    set_long("   The mahogany-paneled room is wide with a low ceiling. The "+
	     "room is sparsely decorated, with the center being open and "+
	     "unobstructed by furniture. Hanging from centered spots on "+
	     "each of the walls are enormous, silver-bladed axes of "+
	     "all shapes, sizes and styles. The blades gleam brilliantly "+
	     "in the flickering glow cast onto the room from the rows "+
	     "of candles resting on small tables in the middle of each "+
	     "wall. There are cushioned pads hanging from several places "+
	     "along each of the walls. The pads are marred and cut and "+
	     "look like they have taken quite a bit of abuse. Around "+
	     "the pads you notice slash marks and cuts in the finely "+
	     "polished mahogany walls. This looks to be a training "+
	     "or sparring room of some kind.\n\n");
    
    add_prop(ROOM_I_INSIDE, 1);
  
    add_item( ({"panels", "walls", "mahogany", "wood", "mahogany panels",
		  "ceiling"}),
	      "The mahogany-paneled walls are finely polished and it looks "+
	      "as though a great deal of care and consideration goes "+
	      "into maintaining them. However, you notice several sections "+
	      "of the wall, mostly near the pads, which bear scrape and "+
	      "slash marks. The slashes are probably waiting to be "+
	      "repaired.\n");
  
    add_item( ({"axes", "silver-bladed axes", "enormous axes",
		  "enormous silver-bladed axes", "silver axes", "axe"}),
	      "Huge, silver-bladed axes hang from centered points along "+
	      "each of the walls. Each one is a masterpiece of "+
	      "smithing and craftsmanship. Each handle is ornately carved "+
	      "wood, sealed and treated with a shiny, translucent "+
	      "material which even makes the wood reflect the glow of "+
	      "the candles. Despite the obvious ceremonial significance "+
	      "of these weapons, you're sure that they would be "+
	      "extremely formidable in combat as well.\n");
  
    add_item( ({"blades", "silver blades", "silver"}),
	      "The silver blades of the axes are incredibly impressive. "+
	      "Each blade is made of shining silver, honed and shaped "+
	      "to a point so sharp you're sure it could split hairs.\n");
  
  
    add_item( ({"candles", "tables", "small tables"}),
	      "There are several small tables pushed up against the walls "+
	      "bearing rows of thick, white candles. The candles provide "+
	      "far more light than you would expect. Additionally, you "+
	      "notice that there is no pile of melted wax at the base "+
	      "of each candle ... odd.\n");
  
    add_item( ({"pads", "cushioned pads"}),
	      "There are cushioned pads hanging from various places "+
	      "along the walls. They have seen better days, from "+
	      "the looks of them. Their surfaces are pocked with "+
	      "slashes and circular puncture wounds, no doubt from "+
	      "constant training and practicing with actual weapons.\n");
   
    create_skill_raise();
    sk_add_train(SS_WEP_SWORD, "fight with swords", 0, 0, 40);
    sk_add_train(SS_WEP_KNIFE, "fight with knives", 0, 0, 35);
    sk_add_train(SS_HERBALISM, "forage for and identify herbs", 0, 0, 35);
    sk_add_train(SS_TRACKING, "follow and identify tracks", 0, 0, 50);
    sk_add_train(SS_LANGUAGE, "understand foreign and archaic languages",
        0, 0, 50);
    sk_add_train(SS_APPR_MON, "assess the abilities of an opponent", 0, 0, 50);

    add_exit("kot_hq1", "southeast");
    add_exit("kot_common", "northeast");
}

void
init()
{
    init_skill_raise();
    ::init();
}
