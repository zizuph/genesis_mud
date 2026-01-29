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

object leader, minotaur1, minotaur2, minotaur3, minotaur4;

void
reset_icewall_room()
{
    if (!minotaur1)
    {
    minotaur1 = clone_object(NPCK + "ice_mino");
    minotaur1->move_living("xx", TO);
    }
    if (!minotaur2)
    {
    minotaur2 = clone_object(NPCK + "ice_mino");
    minotaur2->move_living("xx", TO);
    }
    if (!minotaur3)
    {
    minotaur3 = clone_object(NPCK + "ice_mino");
    minotaur3->move_living("xx", TO);
    }
    if (!minotaur4)
    {
    if (random(2))
    {
    minotaur4 = clone_object(NPCK + "ice_mino");
    minotaur4->move_living("xx", TO);
    }
    }
    if (!leader)
    {
    leader = clone_object(NPCK + "m_ice_mino");
    leader->move_living("xx", TO);
    }

}  

void
create_icewall_room()
{
    set_short("West battlement");
    set_long("@@long_descr");

    add_exit("battlement3","north");
    add_exit("battlement1","south");

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
     "This is the west battlement. Further south the " +
     "enclosed blanks connect with the main building " +
     "while some distance to the north, the corridor turns " +
     "east. In the thick walls on both sides of the battlement, " +
     "that is to the east and west, narrow vertical archers' slits " +
     "slice the corridor open every few yards. Halfway between every " +
     "pair of slits stands a thick stone support of the roof. On " +
     "every arch, an iron-wrought torch holder has been bolted into " +
     "the stone, though not many of them hold a torch now. The " +
     "roofed battlement, though safe from dragons' breath and " +
     "small missile fire, seems oppressive and gloom. Two staircases, " +
     "one to the south and one to the north, lead down onto the " +
     "castle's ground floor.\n");


     reset_room();
}

int
do_squeeze(string str)
{
    if(str == "through outward slit" || str == "through west slit")
      {
      write("And what next? Fall down the steep, snowy cliff? " +
        "That would be DEATH.\n");
      say(QCTNAME(TP) + " appears to be having some suicidal thoughts " +
        "connected to the archers' slits.\n");
      return 1;
      }

    if(str == "through inward slit" || str == "through east slit")
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
         write("Looking far out, you can make out an enclosing range of snow " +
           "covered mountains, and some icy plains close to them. " +
           "Just outside the castle, a steep snowy cliff leads " +
           "straight down into an arctic canyon, making any " +
           "attack from this side suicidal, if not impossible.\n");
         say(QCTNAME(TP) + " glances out through an outward " +
           "archers' slit.\n");
           return 1;
      }
    if(str == "out through inward slit" || str == "through inward slit")
      {
         write("You lean forward, looking down into the Icewall " +
          "Castle's inner courtyard...\n\n");
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