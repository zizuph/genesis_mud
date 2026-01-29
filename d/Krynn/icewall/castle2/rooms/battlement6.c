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
    set_short("Shadowy east end of the north battlement");
    set_long("@@long_descr");

    add_exit("battlement7","south");
    add_exit("battlement5","west");

    add_item(({"path","steep path"}),"Narrow, steep, and snow " +
     "covered. It hasn't been used in quite some time.\n");
    add_item("broken pole","Some force broke it, leaving only a " +
     "splintered woody stump sticking out from the deep snow.\n");
    add_item(({"campfires","campfire"}),"Just flickering lights " +
     "in the distance. You can see nearly a hundred of them, and " +
     "Gods know how many are hidden behind the mountain's width.\n");
    add_item(({"pole","poles","silhuette","silhuettes"}),"Dead, " +
     "frozen bodies have been nailed to the top of the poles " +
     "in a show of utter cruelty. You cannot make out the details " +
     "of the corpses, but they seem naked, and of various sizes.\n");
    add_item(({"glacier","finger"}),"Smooth and hard as ... " +
     "well, ice, the glacier's finger creeps steadily over the " +
     "this corner of the castle. In a score of years, " +
     "if the summer sun fails to halt its progress, it will " +
     "flow into the castle, beginning the stronghold's " +
     "destruction, for nothing can withstand the crush of a " +
     "walking carpet of ice.\n");
    add_item(({"slit","slits","archers' slits","narrow slits"}), "" +
     "Shaped like horizontal trapezoids with the shorter base " +
     "directed outward, the archers' slits allow " +
     "easy loosening of missiles on targets outside the castle, " +
     "while at the same time present " +
     "a minimal profile for enemy fire. The outward slits to the " +
     "north are covered by ice, but it is still possible to gaze " +
     "through the eastern ones.\n");
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
     "This is the east end of the north battlement. The corridor " +
     "turns here, leading to the eastern wall and far to the south" +
     "the enclosed blanks connect with the main building. " +
     "To the west, the battlements continue for the width of the " +
     "castle before turning south on the western wall. " +
     "In the thick walls on the outward sides of the battlements corner, " +
     "that is to the north and east, narrow vertical archers' slits " +
     "slice the corridor open every few yards. The slits to the " +
     "north, however, are blocked by ice and this area is " +
     "much more shadowy then the rest of the battlements. Halfway " +
     "between every " +
     "pair of slits stands a thick stone support of the roof. On " +
     "every arch, an iron-wrought torch holder has been bolted into " +
     "the stone, though not many of them hold a torch now. The " +
     "roofed battlement, though safe from dragons' breath and " +
     "small missile fire, seems oppressive and gloom. Staircases " +
     "located to the south and west lead down, " +
     "onto the castle's ground floor.\n");


     reset_room();
}

int
do_squeeze(string str)
{
    if(str == "through east slit" || str == "through east outward slit")
      {
      write("And what next? Fall down the steep, snowy cliff? " +
        "That would be DEATH.\n");
      say(QCTNAME(TP) + " appears to be having some suicidal thoughts " +
        "connected to the archers' slits.\n");
      return 1;
      }

    if(str == "through north slit" || str == "through north outward slit")
      {
      write("You wish! Its completely blocked by ice!\n");
      say(QCTNAME(TP) + " stares wistfully at the north archers' slit.\n");
      return 1;
      }

    if(str == "through slit")
      {
      write("Squeeze through which slit?\n");
      return 1;
      }

    return 0;
}

int
do_gaze(string str)
{
    if(str == "through north outward slit" || str == "out through north outward slit")
      {
     write("It is impossible to gaze out through one of the northern " +
           "slits as they are under the surface of the glacier! " +
           "Dark, icy depths is all you can see. The surface of " +
           "the ice is uneven, as if someone has chipped it away " +
           "from the slits in a desperate attempt to keep the " +
           "glacier from the inside of the battlements.\n");
         say(QCTNAME(TP) + " glances thoughtfully at the ice-blocked " +
           "northern slits.\n");
           return 1;
      }
    if(str == "through east outward slit" || str == "out through east outward slit")
      {
  write("Looking far out, you can make a flat and wide field " +
           "of snow, reaching as far as you can see. A few miles to " +
           "to the northeast, " +
           "though the view is partially blocked by the northern " +
           "range of mountain, you spot flickering lights - campfires. " +
           "Much closer, at the base of the snowy cliff the Castle " +
           "stands upon, tall wooden poles have been erected. Each of " +
           "them bears a dark, frozen silhuette on top. One of the " +
           "poles has been broken, and now lays covered by snow. Some " +
           "way to the south, a steep path leads up the cliff to " +
           "the castle's main gate.\n");
         say(QCTNAME(TP) + " glances out through an outward " +
           "archers' slit.\n");
           return 1;
      }
    if(str == "out through inward slit" || str == "through inward slit")
      {
         write("There is no inward slit here! You stand at the " +
          "northeast corner of the battlements!\n");
         say(QCTNAME(TP) + " for some reason, appears confused.\n");
           return 1;
      }
    
     write("Gaze through which outward slit? The north one, or the " +
       "east one?\n");
     return 1;
}

    
void
init()
{
    ::init();
   
    add_action(do_squeeze, "squeeze");
    add_action(do_gaze, "gaze");
}       