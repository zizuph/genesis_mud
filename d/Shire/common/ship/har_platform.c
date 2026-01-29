/*
 * Changed reset_room() to reset_deck() after the mudlib and GD change
 * Jan 19th 1995. Elessar.
 */
#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

void add_stuff();

void
create_deck()
{
  set_short("On a small raised platform");
  set_long("The platform is situated above the rest of the deck of "+
    "ship, providing anyone standing on it a commanding view of all "+
    "operations upon, and above, the deck. Mounted to "+
    "the platform is the ship's wheel, which provides direction to "+
    "the entire ship by controlling the rudders.\n");

  add_item(({"ship's wheel","wheel","shipwheel"}),
    "Lovingly carved from a single, circular section of timber, "+
    "the wheel has five elaborate spokes that connect the outside "+
    "ring and grips of the wheel to the hub, which in turn rotates "+
    "the shaft, allowing the entire mechanism to move the rudders as "+
    "needed. "+
    "The outer ring is carved to resemble a slightly stormy sea "+
    "with the grips being carved into large, rolling waves.\n");

  add_item(({"rudder","rudders"}),
    "The rudders, although mostly submerged in water, are obviously "+
    "huge constructs capable of forcing the ship through incredibly "+
    "tight turns and keeping it steady even in the worst "+
    "weather conditions.\n");

  add_item("crew","The vast majority of the crew spends its time "+
    "bustling about the ship, taking care of all the duties that "+
    "are required to ensure smooth sailing. Only the captain and "+
    "helmsman spend any appreciable amount of time on deck, instead "+
    "of in the rigging or up a mast.\n");

  add_item(({"spoke","spokes"}),
    "The spokes are carved into the shapes of five different trees, "+
    "each with highly detailed bark and leaves, accurate both in "+
    "detail and surprisingly, colour.\n");

    add_item("ship",
        "The ship is light and sleek and full of sails. It has three " +
        "masts which are full of sails. The ship is made of strong wood, " +
        "and looks able to outrun almost any ship it comes acrossed.\n");

  add_item(({"door","doors","doorway","doorways"}),
    "The door looks like it is crafted of the same blend of woods "+
    "that composes the rest of the ship.\n");

  add_item("deck","The deck, built of the same timber as the "+
    "rest of the ship, is spotlessly clean. Probably it is kept "+ 
    "in such good condition by newbie passengers who are forced "+
    "to work for their passage by swabbing the deck.\n");

  add_item("hull","The hull possesses the same blend of timbers "+
    "apparent in the rest of the ship. Near the prow, the hull forms "+
    "a sharp, nearly straight V shaped point, then it gently "+
    "slopes towards the stern of the ship, gaining a bulge in the "+
    "center like many a retired warrior before squaring up, "+
    "aside from the wings, in the stern, presenting a flat "+
    "backside to the world, much like the previously mentioned "+
    "warriors.\n");

  add_item(({"wood","woods","timber","timbers"}),
    "All wooden components of the ship seem to be formed of at least "+
    "one of three types of woods: lebethron, cedar, or pine. While "+
    "the masts are carved from a single tree, most of the ship "+
    "was crafted from strips of differing timber joined together. The "+
    "strips are joined so well that the ship seems to have been "+
    "carved from a single, huge piece of many shaded-wood, "+
    "and the shades blend from light to dark and back to "+
    "light, producing an almost hypnotic effect when combined with "+
    "the swaying of the ship.\n");

  add_item(({"stern","winged stern","wings"}),
    "It is extremely difficult to see any part of the wings except the "+
    "upper parts, since those same parts extend above the platform "+
    "and effectively block any view of the lower sections of the stern "+
    "unless one were to climb up to the edge and lean out, but that "+
    "would probably result in a bath and very close look at the "+
    "extreme bottom of the ship.\n");

  add_item(({"crews quarters","cabin","passenger cabin",
  "passenger's cabin","quarters","crews' cabin"}),
    "A solid door blocks the view into the cabin.\n");

  add_item("rigging","Consisting of all the various ropes and chains "+
    "needed for positioning and controlling the sails and masts of "+
    "the ship, the rigging also creates a serviceble pathway for "+
    "those hands that are capable enough to move around above deck.\n");

  add_item(({"mast","masts","foremast","main mast","midmast","aft mast",
  "rear mast","forward mast","fore mast"}),
    "All three masts sport brilliantly white sails that billow "+
    "out fully with the slightest breeze. Crew members swarm about "+
    "the masts and rigging, making many fine adjustments to ensure "+
    "maximum efficency from the sails. "+
    "The masts, polished by years of handling by hordes of sailors, "+
    "glisten wetly from the sea spray, making the sailors' antics "+
    "seem praiseworthy, since they never seem to fall or even slip.\n");

  add_item(({"sail","sails","foresail","main sail","mainsail","fore sail",
  "rear sail","aft sail","mid sail","white sail","white sails"}),
    "The sails all carry the same design, that of feathers embroidered "+
    "onto the material. Each sail is shaped like a huge pyramid, "+
    "billowing out towards the front of the ship with even the "+
    "slightest breeze.\n");

  add_item("platform","The platform is just a raised section of deck "+
    "that serves as a command post for the officers of the ship. "+
    "The only truly distinguishing feature of the platform is the "+
    "ship's wheel that is mounted to it.\n");

  add_exit(SHIP_DIR + "deck", "down", "@@move_down",1);

  enable_reset();
  add_stuff();
}


init()
{
  add_action("turn_wheel","turn");
  ::init();
}

int turn_wheel(string str)
{
  if(!(parse_command(str,TP,"[the] [ships] 'wheel' ")))
  {
    NFN0("Turn what?");
  }

  if(present("helmsman"))
  {
    WRITEN("As you reach for the wheel the helmsman grabs your hand "+
      "and pushes you away.");
    SAY(" reaches for the wheel, but the helmsman stops "+HIM_HER(TP)+".");
    return 1;
  }
  else
  {
    WRITEN("You firmly grasp the wheel, but can not budge it, no "+
      "matter how hard you try!");
    SAY(" grasps the wheel firmly, but is unable to move it at all.");
    return 1;
  }
}


int move_down()
{
  WRITE("You carefully begin to climb back down to the deck but "+
    "the ship lurches and you follow the first mate down in style.\n");
/*
  SAY(" starts climbing down to the deck below, but finishes with a "+
    "short scream and a loud thump.");
 */
  return 0;
}
/*
  return QCTNAME(TP) +" starts climbing down to the deck below,"+
    "but finishes with a short scream and a loud thump.";
*/


reset_deck()
{
  add_stuff();
}


void add_stuff()
{
  object helmsman;
  

  if(!present("helmsman"))
  {
    helmsman = clone_object(SHIP_DIR + "targon");
    helmsman->move(TO);
  }
}