#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <stdproperties.h>

#define COURTYARD \
({  \
      ROOMSK + "inner_courtyard", \
      ROOMSK + "courtyard_north", \
})

inherit ICEINROOM;


void
create_icewall_room()
{
    set_short("West end of the north battlement");
    set_long("@@long_descr");

    add_exit("battlement3","south");
    add_exit("battlement5","east");

    add_item(({"glacier","finger"}),"Smooth and hard as ... " +
     "well, ice, the glacier's finger creeps steadily over the " +
     "northeastern corner of the castle. In a score of years, " +
     "if the summer sun fails to halt its progress, it will " +
     "flow into the castle, beginning the stronghold's " +
     "destruction, for nothing can withstand the crush of a " +
     "walking carpet of ice.\n");
    add_item(({"slit","slits","archers' slits","narrow slits"}), "" +
     "Shaped like horizontal trapezoids with the shorter base " +
     "directed outward, the archers' slits allow " +
     "easy loosening of missiles on targets outside the castle, " +
     "while at the same time present " +
     "a minimal profile for enemy fire. It is possible to gaze " +
     "through a slit.\n");
    add_item(({"arch","support"}),"Thick stone arches support the " +
     "roof of the battlement. Judging by their size, they must have " +
     "have been designed to carry quite a weight.\n");
    add_item(({"holders","torch holders","holder","torch holder"}), "" +
     "The iron torch holders were most likely wrought by a master " +
     "blacksmith. In ages past, painted and filled, they must have " +
     "reassured the troops with the illumination provided. Today, " +
     "rusted and empty, they are a sorry sight.\n");
    add_item("roof","How thick it is, you cannot guess. Probably enough " +
     "to shield the garrison from attacking dragons and wizardly " +
     "fireballs.\n");

    set_tell_time(800);

    add_tell("A gust of icy wind blows through the archers' " +
     "slits, chilling you a bit.\n");
    add_tell("A nearby torch smolders. The stench of tar " +
     "spreads quickly.\n");

    reset_room();
}

void

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}                  

string

long_descr()

{ return ("" +
     "This is the west end of the north battlement. The corridor " +
     "turns here, leading to the western wall and far to the south" +
     "the enclosed blanks connect with the main building. " +
     "To the east, the battlements continue for the width of the " +
     "castle before turning south on the eastern wall. " +
     "In the thick walls on the outward sides of the battlements corner, " +
     "that is to the north and west, narrow vertical archers' slits " +
     "slice the corridor open every few yards. Halfway between every " +
     "pair of slits stands a thick stone support of the roof. On " +
     "every arch, an iron-wrought torch holder has been bolted into " +
     "the stone, though not many of them hold a torch now. The " +
     "roofed battlement, though safe from dragons' breath and " +
     "small missile fire, seems oppressive and gloom. Staircases " +
     "located to the south and east lead down, " +
     "onto the castle's ground floor.\n");


     reset_room();
}

int
do_squeeze(string str)
{
    if(str == "through west slit" || str == "through west outward slit")
      {
      write("And what next? Fall down the steep, snowy cliff? " +
        "That would be DEATH.\n");
      say(QCTNAME(TP) + " appears to be having some suicidal thoughts " +
        "connected to the archers' slits.\n");
      return 1;
      }

    if(str == "through north slit" || str == "through north outward slit")
      {
      write("And what next? Fall down all the way to the rocks? " +
        "That would HURT.\n");
      say(QCTNAME(TP) + " appears to be having some suicidal thoughts " +
        "connected to the archers' slits.\n");
      return 1;
      }

    if(str == "through slit")
      {
      write("Squeeze through which slit? The north, or the west " +
        "one?\n");
      return 1;
      }

    return 0;
}

int
do_gaze(string str)
{
    if(str == "through north outward slit" || str == "out through north outward slit")
      {
         write("Looking out, all you can see is a massive, ice " +
           "covered tall range to the north, as the Icewall " +
           "Castle stands upon a rocky finger extending from the " +
           "mountains. A flowing mass of glacier's ice has " +
           "travelled from the mountains, and making progress through " +
           "the centuries, crept unnoticed against the northeastern " +
           "blanks of the castle. Today, the ice is already six men " +
           "high, and ready to spill over the battlements right into " +
           "the castle's inner curtyard.\n");
         say(QCTNAME(TP) + " glances out through an outward " +
           "archers' slit.\n");
           return 1;
      }
    if(str == "through west outward slit" || str == "out through west outward slit")
      {
      write("Looking far out, you can make a range of snow " +
           "covered mountains, and some icy plains close to them. " +
           "Just outside the castle, a steep snowy cliff leads " +
           "straight down, into a what you see as a dead-end, deep " +
           "arctic canyon. Any attack from this side suicidal, if not " +
           "impossible.\n");
         say(QCTNAME(TP) + " glances out through an outward " +
           "archers' slit.\n");
           return 1;
      }
    if(str == "out through inward slit" || str == "through inward slit")
      {
         write("There is no inward slit here! You stand at the " +
          "northwest corner of the battlements!\n");
         say(QCTNAME(TP) + " for some reason, appears confused.\n");
           return 1;
      }
    
     write("Gaze through which outward slit?\n");
     return 1;
}

   
void
init()
{
    ::init();

    add_action(do_squeeze, "squeeze");
    add_action(do_gaze, "gaze");
}       