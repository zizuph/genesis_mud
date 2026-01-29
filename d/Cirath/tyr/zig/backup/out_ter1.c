/* /d/Cirath/athas/a_tyr/merchant/zig/out/lev2.c                     */
/*                                                                   */ 
/* This is the second outside level of the grand ziggurat.           */
/*                 Decius, December 1995                             */

#pragma strict_types
#include "defs.h"
inherit "/std/room";


void create_room()
{
  ::create_room();
  set_long(
     "The indigo walls of the first terrace gleam with reflected sunlight "+
     "upon poorly constructed scaffolding as halflings scurry to complete "+
     "the intricate murals of the ziggurat.  Meanwhile, bored looking "+
     "templars stand idly, lashing their whips at any slave foolish enough "+
     "to come within reach.  A web of ropes descends from above, down to "+
     "the base, where green colored bricks await hauling. From your "+
     "position above the teeming swarm of slaves, it is much easier to "+
     "look around at your surroundings. \n"+
     "From here the staircase leads up and down.\n");

  set_short(
    "The first terrace of the grand ziggurat");



  add_item(({"ziggurat","pyramid"}),
     "Dominating the center of the city, the square-stepped tower rises "+
     "in sharp-edged splendor over the neighboring slums. For seventy "+
     "years, lash-striped slaves have borne massive blocks into place "+
     "and mortared them together with their own blood.\n");

  add_item(({"walls","wall"}),
     "The indigo walls of the first terrace are covered with numerous "+
     "inscriptions in one giant mural.\n");

  add_item(({"steps","staircase"}),
     "Mighty bastions flank this enormous staircase, which runs straight "+
     "from base to summit along the west side of the ziggurat.\n");

  add_item("slaves",
     "Dextrous halflings climb the scaffolding like spiders in order to "+
     "carve the indigo walls, while on the staircase groups of slaves "+
     "struggle to haul bricks upwards.\n");

  add_item("scaffolding",
     "Poorly made and unstable scaffolding surrounds the ziggurat, "+
     "allowing those nimble enough to scale up and carve the walls.\n");

  add_item(({"guards","half-giants","brutes","half-giant guards"}),
     "These huge brutes accompny the templars, anxiously awaiting "+
     "any opportunity to bash slaves with their clubs.\n");

  add_item(({"templars","priests","bureaucrats"}),
     "These pale-faced priests of Kalak oversee the construction of the "+
     "ziggurat, wielding their barbed whips with sadistic glee. Up here "+
     "though they have very few slaves to 'supervise', and seem terribly "+
     "bored.\n");

  add_item("halflings",
     "These savage looking little barbarians clamber on the scaffolding "+
     "all around you, carving murals, and coincidentally staying out of "+
     "whip reach of the nearest templars.\n");

  add_item(({"pulleys","pulley"}),
     "Huge pulleys manned by massive baazrags at the top of the ziggurat "+
     "use long cords of giant-hair rope to haul bricks up the steps.\n");

  add_item(({"ropes","web","rope","webs"}),
     "A giant chaotic web of ropes encompasses the first terrace. "+
     "Ropes dangle everywhere: some are attached to the scaffolding, "+
     "some to the pulley, and many seem to serve no purpose whatsoever.\n");

  add_item("surroundings",
     "You may look in any of the eight directions, as well as up and "+
     "down.\n");

  add_item(({"base","below","crowd"}),
     "Below you, thousands of slaves labor in wretched despair, hauling "+
     "bricks to the base of the staircase.\n");

  add_item(({"baazrags","baazrag"}),
     "Up at the top of the ziggurat, a handful of enormous baazrags, "+
     "closely watched by nervous templars, put their considerable "+
     "strength to work hauling bricks.\n");

  add_item(({"bricks","brick","groups","group"}),
     "Even aided by pulleys, dozens of slaves struggle to push the green "+
     "bricks up to the top of the ziggurat.\n");

  add_item(({"mural","murals","carving","carvings","image","images"}),
     "Intricate carvings cover the indigo walls, depicting many "+
     "images. Scenes of battles fought long ago intertwine with "+
     "pictures of treasures lost and men forgotten. Strange "+
     "creatures dance over exotic landscapes to some mysterious, "+
     "unknown music. Repeated regularly in the murals are images "+  
     "of ancient books and scrolls.\n");


  add_item(({"writings","writing","hieroglyphics","inscriptions",
     "inscription","symbol","symbols"}),
     "Carven deeply into the indigo walls are strange symbols, "+
     "completely foreign to you.  They seem to be of a language "+
     "which you do not recognize.\n");





  add_cmd_item("around","look",
     "You may look in any of the eight directions, as well as up and "+
     "down.\n");

  add_cmd_item(({"up","u"}),"look",
     "Above you, azure walls mark the second terrace of the ziggurat.\n");

  add_cmd_item(({"down","d"}),"look",
     "Below you, thousands of slaves labor in wretched despair, hauling "+
     "bricks to the base of the staircase.\n");

  add_cmd_item(({"east","northeast","southeast","e","ne","se"}),"look",
     "The enormous bulk of the ziggurat blocks your view to the east.\n");

  add_cmd_item(({"north","n"}),"look",
     "Looking to the north you see the ziggurat brickyards, and the walls "+
     "of the slave pits.\n");

  add_cmd_item(({"south","s"}),"look",
     "Directly to the south you see the pubs and inns of Shadow Square, "+
     "and beyond that the slums known as the Warrens.\n");

  add_cmd_item(({"southwest","sw"}),"look",
     "Squalid huts and hovels fill your vision as you look southwest "+
     "towards the Warrens.\n");

  add_cmd_item(({"northwest","nw"}),"look",
     "To the northwest you see the outer estates of the Noble Quarters. "+
     "Though considered poorer by noble standards, they still reek "+
     "of wealth.\n");

  add_cmd_item(({"west","w"}),"look",
     "Stark windows of the merchant buildings greet your gaze westwards. "+
     "Heavy curtains fill the windows, keeping out the ever present dust, "+ 
     "and lending an air of mystery to them.\n");

  add_cmd_item(({"scaffolding","ropes","framework"}),({"climb","scale"}),
     "You walk over to the scaffolding with the intention of climbing "+
     "it, but after a quick examination you realize that if you tried, "+
     "you would probably fall off.  The framework is poorly made, and "+
     "a good shake would probably cause it to collapse.\n");

  add_cmd_item(({"scaffolding","ropes","framework"}),({"shake","rattle"}),
     "You grab the scaffolding and give it a good shake. "+
     "The scaffolding trembles violently, and suddenly you hear a "+
     "high-pitched scream of terror from above as a halfling climber "+
     "plummets to his death, landing in a heap beside you.\n");

  add_cmd_item(({"hieroglyphics","writing","writings","carving",
     "carvings","inscription","inscriptions"}),"read",
     "You try to interpret the hieroglyphics, but fail.\n");

 
 OUTSIDE
 ADD_SUN_ITEM;

  add_exit(TYR_ZIG+"out_base.c","down","@@godown",3);
  add_exit(TYR_ZIG+"out_ter2.c","up","@@goup",8);

}


int godown()
{
  TP->catch_msg(
     "You walk down the steps towards the base of the ziggurat, carefully "+
     "dodging the upcoming bricks.\n");
  return 0;
}

int goup()
{
  TP->catch_msg(
     "Templars watch you closely as you climb the steps of the ziggurat "+
     "towards the second terrace.\n");
  return 0;
}




