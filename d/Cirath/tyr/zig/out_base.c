/*   /d/Cirath/athas/a_tyr/merchant/zig/out/lev1.c                   */
/*                                                                   */
/*   The first outside level of the grand ziggurat.                  */
/*           Decius, December 1995                                   */
/*                                                                   */
/*                                                                   */

#pragma strict_types
#include "defs.h"
inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";

void create_room()
{
  ::create_room();
  set_long(
     "The mingling smells of sweat and human suffering are overwhelming "+
     "as you stand at the base of the grand ziggurat, surrounded by "+
     "toiling slaves.  Thousands of all races share in the "+
     "misery as they race to complete the massive pyramid, while "+
     "whip-wielding templars and their half-giant bodyguards enforce "+
     "the pace with cruel delight.  From here the ziggurat steps "+
     "lead upward, and a snaking path goes "+
     "westwards through the crowd.  Gigantic steel doors leading "+
     "east, into the ziggurat, stand closed and guarded.\n");


  set_short(
    "The base of the grand ziggurat");

        
  add_item(({"slaves","crowd"}),
     "Thousands of humans, dwarves, thri-keen, even elves and halflings "+
     "have been conscripted into the ziggurat's construction. Here at "+
     "the base, most of the slaves work to haul giant bricks from the "+
     "brickyards to the grand steps, where massive pulleys await. "+ 
     "Others scale unstable scaffolding to carve intricate inscriptions "+
     "into the pyramid walls.\n");

  add_item(({"priests","templars","bureaucrats"}),
     "These pale-faced priests of Kalak oversee the construction of the "+
     "ziggurat, wielding their barbed whips with sadistic glee.\n");

  add_item(({"half-giants","guards","brutes","half-giant guards"}),
     "These huge brutes accompany the templars, anxiously awaiting "+
     "any opportunity to bash slaves with their clubs.\n");

  add_item(({"ziggurat","pyramid"}),
     "Dominating the center of the city, the square-stepped tower rises "+
     "in sharp-edged splendor over the neighboring slums. For seventy "+
     "years, lash-striped slaves have borne massive blocks into place "+
     "and mortared them together with their own blood.\n");

  add_item(({"steps","staircase"}),
     "Mighty bastions flank this enormous staircase which runs straight "+
     "from base to summit along the west side of the ziggurat.\n");

  add_item(({"path","snaking path"}),
     "You can barely discern a small path through the milling crowd "+
     "of slaves, leading west.\n");

  add_item(({"baazrags","baazrag"}),
     "Up at the top of the ziggurat a handful of enormous baazrags, "+
     "closely watched by nervous templars, put their considerable "+
     "strength to work hauling bricks.\n");

  add_item(({"pulleys","pulley"}),
     "Huge pulleys manned by massive baazrags at the top of the ziggurat "+
     "use long cords of giant-hair rope to haul bricks up the steps.\n");

  add_item(({"walls","wall"}),
     "Gleaming violet walls at the base of the ziggurat are carved with "+
     "numerous inscriptions in one giant mural.\n");


  add_item(({"doors","door","steel doors","gigantic steel doors",
     "steel door","gigantic steel door"}),
     "Massive steel doors standing twenty feet tall guard the entrance "+
     "to the ziggurat.  Finely engraved with the same images and "+
     "writings as the violet walls, these doors alone would be worth "+
     "enough to buy a small city! What could they be protecting...?\n");

  add_item("scaffolding",
     "Poorly made and unstable scaffolding surrounds the ziggurat, "+
     "allowing those nimble enough to scale up and carve the walls.\n");

  add_item(({"blocks","bricks","block","brick"}),
     "Long lines of slaves drag green bricks from the brickyards to "+
     "the ziggurat steps.  So huge are these blocks that dozens of "+
     "slaves are required to move them even a few feet.\n");

  add_item(({"lines","line"}),
     "Coming from the brickyards to the north, these slaves struggle "+
     "mightily to push the gigantic bricks toward the steps.\n");

  add_item("humans",
     "Sunburned human slaves comprise the bulk of the ziggurat workforce. "+
     "While many die here, they are easily replaced by the templars, "+
     "who need simply to enter the warrens with a half-giant entourage, "+
     "and 'arrest' a few more.\n");

  add_item("dwarves",
     "Because of their incredible endurance, the dwarven slaves have "+
     "adapted fairly easily to the back-breaking labour here at the "+
     "ziggurat.  They work tirelessly and without complaint at even the "+
     "most difficult jobs.  In spite of this, or more likely because of "+
     "this, the templars take special pleasure in whipping them.\n");

  add_item(({"gith","giths"}),
     "Very few of this hunchbacked race populate the labor force. "+
     "Those gith that do find their way here tend to suffer unfortunate "+
     "accidents, much to the regret of no one.\n");

  add_item("muls",
     "There are surprisingly very few muls among the slaves, this is "+
     "presumably because of their value in the gladiatorial pits. "+
     "Those that are here seem fairly content with their lot, simply "+
     "happy to live without fear of brutal death in the arena.\n");

  add_item("elves",
     "Separated from their tribes and forced into menial labour, the "+
     "elven slaves are miserable, and entirely unproductive.  Many "+
     "elves disappear at night within the slave pits, coinciding with "+
     "the feeding routines of the thri-keen slaves.\n");

  add_item("halflings",
     "These diminutive barbarians, having been captured by Tyrian "+
     "hunters, are forced to labor on the ziggurat.  Given their "+
     "small stature and incredible climbing skills, they have the "+
     "task of carving murals into the walls.  Those who can't, or "+
     "won't, serve as kick-toys for the half-giant guards.\n");

  add_item(({"mural","murals","carving","carvings","image","images"}),
     "Intricate carvings cover the violet walls, depicting many "+
     "images. Scenes of battles fought long ago intertwine with "+
     "pictures of treasures lost and men forgotten. Strange "+
     "creatures dance over exotic landscapes to some mysterious, "+
     "unknown music. Examining the mural thoroughly, you "+ 
     "realize that one image in particular is repeated at regular "+
     "intervals along the wall, that of a pyramid.\n");

  add_item(({"writings","writing","hieroglyphics","inscriptions",
     "inscription","symbol","symbols"}),
     "Carven deeply into the violet walls are strange symbols, "+
     "completely foreign to you.  They seem to be of a language "+
     "which you do not recognize.\n");




  add_cmd_item(({"west","w"}),"look",
     "Staring down at you from the west are the windows of the trade "+
     "houses in the Merchant District.  Through the crowd, you can "+
     "only see the tops of the dull square buildings.\n");

  add_cmd_item(({"northwest","nw"}),"look",
     "The buildings of the noble quarters to the northwest lie hidden "+
     "from your view by the crowd.\n");

  add_cmd_item(({"southwest","sw"}),"look",
     "To the southwest, beyond the teeming crowd, lie the slums known "+
     "as the warrens.\n");

  add_cmd_item(({"east","southeast","northeast","e","se","ne"}),"look",
     "The enormous bulk of the ziggurat blocks your view to the east.\n");

  add_cmd_item(({"north","n"}),"look",
     "Beyond the crowds, to the north, are the brickyards and slave "+
     "pits.\n");

  add_cmd_item(({"south","s"}),"look",
     "Separated from you by thousands of slaves is shadow square to the "+
     "south.\n");

  add_cmd_item(({"up","u"}),"look",
     "Looking up, you see the indigo walls of the ziggurat's first "+
     "terrace.\n");

  add_cmd_item(({"down","d"}),"look",
     "Could it be...? Yes it is!  Dirt!!!\n");

  add_cmd_item(({"in any direction","around"}),"look",
     "You may look in any of the eight directions, as well as up, and "+
     "down.\n");

  add_cmd_item(({"scaffolding","ropes","framework"}),({"climb","scale"}),        
     "You walk over to the scaffolding with the intention of climbing "+
     "it, but after a quick examination you realize that if you tried, "+
     "you would probably fall off.  The framework is poorly made, and "+
     "a good shake would probably cause it to collapse.\n");

  add_cmd_item(({"scaffolding","ropes","framework"}),({"shake","rattle"}),
     "You grab the scaffolding and give it a good shake. "+
     "The scaffolding trembles violently, and suddenly you hear a "+
     "high-pitched scream of terror from above as a halfling climber "+
     "plummets to his death, landing in a broken heap beside you.\n");

  add_cmd_item(({"doors","door","steel doors","steel door",
     "gigantic steel doors","gigantic steel door"}),({"open","pull"}),
     "You walk over to the massive steel doors and attempt to pull them "+
     "open, unfortunately they are locked.\n");

  add_cmd_item(({"doors","door","steel doors","steel door",
     "gigantic steel doors","gigantic steel door"}),"unlock",
     "You try to figure out how to unlock the doors, but cannot. "+
     "They appear to be locked from the inside.\n");

  add_cmd_item(({"hieroglyphics","writings","inscriptions",
     "inscription","writing","carvings","carving"}),"read",
     "You try to interpret the hieroglyphics, but fail.\n");
  
  OUTSIDE 
  ADD_SUN_ITEM;
  add_exit(TYR_MERCHANT+"ironsqr5.c","west","@@gowest",1);
  add_exit(TYR_ZIG+"out_ter1.c","up","@@goup",8);
}

int goup()
{
  TP->catch_msg(
     "Templars watch you closely as you climb the steps of the ziggurat "+
     "towards the first terrace.\n");
  return 0;
}

int gowest()
{
  TP->catch_msg(
     "Jealous eyes follow your progress as you follow the snaking path "+
     "westward, and leave the wretched crowd.\n");
  return 0;
}






