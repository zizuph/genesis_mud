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
    set_short("South end of the east battlement");
    set_long("@@long_descr");

    add_exit("battlement8","north");
    add_exit("south_guard","down","@@down");

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
    add_item(({"stairway","stairs"}),"A circular stone staircase " +
     "situated at the south end of the battlements leads down, " +
     "towards the ground level of the building.\n");
    add_item(({"slit","slits","archers' slits","narrow slits"}), "" +
     "Shaped like horizontal trapezoids with the shorter base " +
     "directed outward, the archers' slits allow " +
     "easy loosening of missiles on targets outside the castle, or " +
     "in the castle's courtyard, while at the same time present " +
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
     "This is the south end of the eastern battlement. Here, the " +
     "enclosed blanks connect with the main building situated to " +
     "the south. In the thick walls on both sides of the battlement, " +
     "that is to the east and west, narrow vertical archers' slits " +
     "slice the corridor open every few yards. Halfway between every " +
     "pair of slits stands a thick stone support of the roof. On " +
     "every arch, an iron-wrought torch holder has been bolted into " +
     "the stone, though not many of them hold a torch now. The " +
     "roofed battlement, though safe from dragons' breath and " +
     "small missile fire, seems oppressive and gloom. A staircase " +
     "located at the south wall leads down, onto the castle's ground " +
     "floor.\n");


     reset_room();
}


int
down()
{ 
  write("Trudging down the stone steps, you descend the stairway.\n");
  say(QCTNAME(TP) + " trudges down the stone steps.\n");
  return 0;
}

int
do_squeeze(string str)
{
    if(str == "through outward slit" || str == "through east slit")
      {
      write("And what next? Fall down the steep, snowy cliff? " +
        "That would be DEATH.\n");
      say(QCTNAME(TP) + " appears to be having some suicidal thoughts " +
        "connected to the archers' slits.\n");
      return 1;
      }

    if(str == "through inward slit" || str == "through west slit")
      {
      write("And what next? Fall down all the way to the courtyard? " +
        "That would HURT.\n");
      say(QCTNAME(TP) + " appears to be having some suicidal thoughts " +
        "connected to the archers' slits.\n");
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
    if(str == "through outward slit" || str == "out through outward slit")
      {
         write("Looking far out, you can make a flat and wide field " +
           "of snow, reaching as far as you can see. A few miles to " +
           "to the northeast, " +
           "though the view is partially blocked by the northern " +
           "range of mountain, you spot flickering lights - campfires. " +
           "Much closer, at the base of the snowy cliff the Castle " +
           "stands upon, tall wooden poles have been erected. Each of " +
           "them bears a dark, frozen silhuette on top. One of the " +
           "poles has been broken, and now lays covered by snow. A " +
           "bit to the north, a steep path leads up the cliff to " +
           "the castle's main gate.\n");
         say(QCTNAME(TP) + " glances out through an outward " +
           "archers' slit.\n");
           return 1;
      }
    if(str == "out through inward slit" || str == "through inward slit")
      {
         write("You lean forward, looking down into the Icewall " +
          "Castle's inner courtyard...\n");
         set_alarm(2.0,0.0,"courtyard_desc");
         say(QCTNAME(TP) + " glances out through an inward " +
           "archers' slit.\n");
           return 1;
      }
    
     write("Gaze through which slit? The inward one, or the outward " +
       "one?\n");
     return 1;
}


int
courtyard_desc()
{

    string *roomfiles;
    object *inv, *live, *dead, room;
    int i;

    roomfiles = COURTYARD;
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
	if ((room = find_object(roomfiles[i])) != 0)
	  inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	dead = FILTER_DEAD(inv);
	if (sizeof(live) > 0 && sizeof(dead) > 0)
	  write ("Down at the snow covered courtyard, you can see " +
		  COMPOSITE_LIVE(live) + ", as well as " +
		  COMPOSITE_DEAD(dead) + ".\n");
	else if (sizeof(live) > 0)
	  write ("Down at the snow covered courtyard, you can see " +
		  COMPOSITE_LIVE(live) + ".\n");
	else if (sizeof(dead) > 0)
	  write ("Down at the snow covered courtyard, you can see " +
	   COMPOSITE_DEAD(dead) + ".\n");
        return 1;	
    }
    write ("The courtyard, barring fresh snow, is completely " +
      "empty.\n");

return 1;

}
    
void
init()
{
    ::init();

    add_action(do_squeeze, "squeeze");
    add_action(do_gaze, "gaze");
}       