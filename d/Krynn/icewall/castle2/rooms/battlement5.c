/* Navarre August 26th 2006 Changed "sucked in his" to "sucked in "+HIS(TP) */

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
    set_short("North battlement");
    set_long("@@long_descr");

    add_exit("battlement4","west");
    add_exit("battlement6","east");
    add_exit("hall1","down","@@down");

    add_item(({"ice","slick ice","slope"}),"It reaches just about to the " +
     "slit's bottom! You feel as if standing on the ground, and not " +
     "high on the battlements. To the north, the smooth ice surface " +
     "curves upwards, leading into the unknown heights of the " +
     "glacier. Only a kender or a daredevil would attempt to climb " +
     "that slope.\n");
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
     "This is the middle part off the north battlement. The corridor " +
     "extends to the east and west, spanning the width of the castle. " +
     "In the thick walls of the battlement, " +
     "that is to the north and south, narrow vertical archers' slits " +
     "slice the corridor open every few yards. Halfway between every " +
     "pair of slits stands a thick stone support of the roof. On " +
     "every arch, an iron-wrought torch holder has been bolted into " +
     "the stone, though not many of them hold a torch now. The " +
     "roofed battlement, though safe from dragons' breath and " +
     "small missile fire, seems oppressive and gloom. A staircase " +
     "located in the middle of the walkway leads down, " +
     "onto the castle's ground floor.\n");


     reset_room();
}


int
do_climb(string str)
{
    if(str == "slope")
      {
         write("Before you attempt that perilous task, you should get " +
           "out on the ice, and squeezing through the archers' slit " +
           "might not be all that easy!\n");
         say(QCTNAME(TP) + " looks thoughtfully at the icy slope.\n");
         return 1;
      }
    notify_fail("Climb what? The slope?\n");
    return 0;
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
    if(str == "through outward slit" || str == "through north slit")
      {

        if (TP->query_race_name() == "kender" || TP->query_race_name() == "hobbit")
          {
            write("Turning sideways, you smartly slip through the " +
              "narrow archers' slit onto the icy slope.\n");
            say("Turning sideways, " + QTNAME(TP) + " smartly slips " +
              "onto the icy slope.\n");

            tell_room(ROOMSK + "slope_bottom", "With the ease " +
              "of a small folk, " +
              QTNAME(TP) + " slips out from the archers' slit.\n");
      
            TP->move_living("through the archers' slit", ROOMSK + "slope_bottom",1,0);
            return 1;
          }

      write("Sucking in your proverbial gut, you twist and push " +
       "and scrape and groan and curse and finally manage to plop " +
       "onto the icy slope just outside the archers' slit.\n");
      say("Sucking in "+HIS(TP)+" proverbial gut, " + QTNAME(TP) + " twists " +
       "and pushes and scrapes and groans and curses but finally " +
       "manages to plop onto the icy slope just outside the archers' " +
       "slit.\n");
     tell_room(ROOMSK + "slope_bottom", "Twisting, pushing, scraping and " +
      "groaning, " + QTNAME(TP) + " plops out through the archers' slit.\n");
      
     TP->move_living("through the archers' slit", ROOMSK + "slope_bottom",1,0);
      return 1;
      }

    if(str == "through inward slit" || str == "through south slit")
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

    write("Squeeze through what?\n");
    return 1;
}


int
do_gaze(string str)
{
    if(str == "through outward slit" || str == "out through outward slit")
      {
         write("Looking out, all you can see is a massive, ice " +
           "covered tall range to the north, as the Icewall " +
           "Castle stands upon a rocky finger extending from the " +
           "mountains. A flowing mass of glacier's ice has " +
           "travelled from the mountains, and making progress through " +
           "the centuries, crept unnoticed against the northeastern " +
           "blank of the castle. Today, the ice is already six men " +
           "high, and to the east, ready to spill over the battlements " +
           "right into the castle's inner curtyard. Here, the slick ice " +
           "reaches just below the archers' slit you are glancing " +
           "through, flowing from up the mountain in a steep slope.\n");
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
    
     write("Gaze through which slit? The outward, or the " +
       "inward one?\n");
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
    add_action(do_climb, "climb");
    add_action(do_gaze, "gaze");
}       