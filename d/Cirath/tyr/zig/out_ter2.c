/*  /d/Cirath/athas/a_tyr/zig/lev3.c               */
/*  The third outside level of the grand ziggurat  */
/*        Decius, January  1996                    */
/*    2021-11-05 Meton Changed Lyden load dir.     */

#pragma strict_types
#include "defs.h"
inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";

object bigglad;

void
reset_room()
{
    if(bigglad) return;
    bigglad=clone_object("/d/Cirath/tyr/zig/lyden/npc/lyden.c");
    bigglad->set_random_move(5);
    bigglad->move_living("into the room", TO);
}

void create_room()
{
  ::create_room();
  set_long("Harsh sunlight reflects off the azure walls of the second "+
     "terrace of the grand ziggurat, leaving no shadows.  Hundreds of "+
     "sunburned slaves toil here hauling bricks, as well as carving "+
     "the murals and the staircase up.  There are also dozens of "+
     "templars here, closely supervising the slaves and the huge "+
     "simian baazrags working the pulleys above.\n"+
     "From here the staircase leads down.\n");

  set_short("The second terrace of the grand ziggurat");

  add_item("slaves","Hundreds of humans and dwarves are at work hauling "+
     "green bricks up to the third terrace, as well as carving murals and "+ 
     "the staircase up. A few halflings are also here, serving "+
     "refreshments to the templars and guards.\n");

  add_item(({"humans","dwarves"}),
     "These slaves seem to be particularly tough and strong, "+
     "probably because the weak ones die quickly.\n"); 
     
  add_item(({"shadow","shadows","shade"}),
     "There are no shadows to be seen, direct sunlight covers "+
     "everything.\n");

  add_item(({"steps","staircase"}),
     "Mighty bastions flank this enormous staircase, which runs straight "+
     "from base to summit along the west side of the ziggurat.\n");

  add_item(({"templars","priests","bureaucrats"}),
     "There are quite a few templars here, attentively watching the "+
     "slaves from beneath the hoods of their cossacks.\n");

  add_item(({"guards","half-giants","brutes","half-giant guards"}),
     "These giant brutes stand around bored, with little to do. "+
     "Occasionally one will amuse himself by punting a halfling or "+
     "two over the edge of the terrace.\n");

  add_item(({"brick","bricks","green brick","green bricks","block",
     "block","green block","green blocks"}),
     "These bricks are huge, requiring dozens of slaves each to move "+
     "them to the top of the ziggurat.\n");

  add_item("halflings","A few halflings ferry between here and the "+
     "base of the ziggurat, bearing cold drinks and hot food for the "+
     "templars. Occasionally one is unfortunate enough to stand beside "+
     "a bored guard for too long...\n");

  add_item(({"pulleys","pulley","ropes"}),
     "Giant-hair ropes lead from the pulleys down to the bricks, "+
     "pulling them upwards to the third terrace.  Huge baazrags, "+
     "closely watched by nervous templars, turn the handles.\n");


  add_item(({"baazrag","baazrags","huge baazrag","huge baazrags", 
     "huge simian baazrag", "huge simian baazrags", 
     "simian baazrag", "simian baazrags" }),
     "From here you can see the baazrags much better.\n"+
     "These creatures are huge, and at their full hight would be " +
     "over nine feet tall if they didn't habitually walk on " +
     "knuckles as well as their feet. A relative of the Athasian " +
     "sloth, they are covered in fur save for their faces and " +
     "chests, and have an enormous hump for storing extra water. " +
     "While only dimly intelligent their 600 pounds of muscle " +
     "make them excellent candidates for use as slave labor. " +
     "Oddly they share the same name with a type of chitin " + 
     "covered vermin, but there is no other likely relation.\n");

  add_item(({"wall","walls","azure wall","azure walls"}),
     "The azure walls of the second terrace stand almost bare to "+
     "the sun, with few inscriptions and no scaffolding to cover "+
     "them.\n");

  add_item("scaffolding","No scaffolding has been put up yet.\n");

  add_item(({"carvings","murals","mural","carving","images","image"}),
     "The slaves have only very recently started work carving here, "+
     "so few inscriptions grace the azure walls. You can see the chalk "+
     "outline of the future murals though, which the slaves use as "+
     "guidance.\n");

  add_item(({"outline","outlines","chalk outline","chalk outlines"}),
     "Chalk outlines cover the azure walls, depicting many "+
     "images. Scenes of battles fought long ago intertwine with "+
     "pictures of treasures lost and men forgotten. Strange "+
     "creatures dance over exotic landscapes to some mysterious, "+
     "unknown music. Most of the scenes are similar to those of "+ 
     "the lower levels, except for one thing. Many of them "+
     "now include the image of a dark circle, or orb.\n");

  add_item(({"writings","writing","hieroglyphics","inscriptions",
     "inscription","symbol","symbols"}),
     "Chalk outlined on the azure walls are strange symbols, "+
     "completely foreign to you.  They seem to be of a language "+
     "which you do not recognize.\n");

  add_cmd_item(({"in any direction","around"}),"look",
     "You may look in any of the eight directions, as well as up and "+
     "down.\n");

  add_cmd_item(({"north","n"}),"look",
     "Northwards you see the ziggurat brickyards, the slave pits, "+
     "and beyond them the city walls of Tyr.\n"); 
     
  add_cmd_item(({"northeast","ne","east","e","southeast","se"}),"look",
     "The enormous bulk of the ziggurat blocks your view to the east.\n");

  add_cmd_item(({"south","s"}),"look",
     "Directly south and below you lies Shadow Square. Further south, "+
     "are the Sarrens and the city walls of Tyr.\n");

  add_cmd_item(({"southwest","sw"}),"look",
     "Looking to the southwest, you see the sprawling hovels of the "+
     "Sarrens, and beyond them, the city walls of Tyr.\n");

  add_cmd_item(({"west","w"}),"look",
     "You look down onto the barren rooftops of the merchant houses to "+
     "the west.\n");

  add_cmd_item(({"northwest","nw"}),"look",
     "To the northwest you see the lavish homes of the Noble District, "+
     "from the modest villas close the ziggurat to the ostentatious "+
     "mansions nearer the city walls.\n");

  add_cmd_item(({"up","u"}),"look",
     "Above you, green bricks mark what will be the third terrace "+
     "of the grand ziggurat.\n");

  add_cmd_item(({"down","d"}),"look",
     "Scaffolding blocks the view of the first terrace, below you.\n");

  add_cmd_item(({"outlines","writing","writings","hieroglyphics",
     "chalk outline","chalk outlines","chalk writing",
     "chalk writings"}),"read",
     "You try to interpret the hieroglyphics, but fail.\n");

  add_cmd_item(({"up","u"}),"climb",
     "Guards stop you from climbing upwards.\n");

  OUTSIDE
  ADD_SUN_ITEM;
  add_prop(ROOM_I_NO_CLEANUP,1);

  add_exit(TYR_ZIG+"out_ter1.c","down","@@godown",3);

  reset_room();
}

int godown()
{
  TP->catch_msg(
     "You walk down the steps towards the first terrace, "+
     "carefully dodging the upcoming bricks.\n");
  return 0;
}


