/*
   Asmodean, March 18 1995
   Lakeside Property Master file for the village of Almorel in
   the domain of Cirath.
   This file and all others in this directory are property of Cirath,
   and Cirath alone, with control of these files being in the hands
   of the liege of Cirath (currently Vladimir)
*/

#include <macros.h>
#include <stdproperties.h>
/* Feel free to add more random messages to the Lakes.h file */
#include "Lakes.h"

inherit "/std/room";

public void create_lakeside();
nomask void make_noise();
nomask int find_rooms(string roomstr);

void
create_room()
{
  /* Set some default properties of the rooms */
  add_prop(ROOM_I_INSIDE,0);
  add_prop(ROOM_I_LIGHT,3);
  add_prop(ROOM_I_HIDE,75);

  /* These should be re_defined! */
  set_short("Lakeside");
  set_long("You'll never see this, so there *pthbbbt*!\n");

  /* No room is a room without at least 10 add_items!! WooWoo! */
  add_item("snow",
	   "The snow is hard packed on the ground beneath your "+
	   "feet. Some patches of snow have been here for quite "+
	   "some time, judging from the amount of soot gathered "+
	   "on the mounds, while other patches of snow couldn't "+
	   "be more than a day or two old.\n");
  add_item("ice",
	   "There is ice everywhere. There are large spear-shaped "+
	   "icicles drooping from the overhangs of the small "+
	   "houses. Here near the lake there are patches of dangerously "+
	   "slick ice on the ground, well concealed by the newly fallen "+
	   "snow.\n");
  add_item(({"lake","river","tributaries","rivers","water"}),
	   "The lake is absolutely enormous. When you are able to peer "+
	   "through the heavy fog looming over The Lake of Mists, you "+
	   "can see that there are quite a few fishing boats out on "+
	   "the water almost all day. At the northwestern edge of "+
	   "the lake, you can make out the dark outlines of two of "+
	   "the Lake of Mists' tributaries.\n");
  add_item(({"fog","mist","steam"}),
	   "Despite the frigid air temperatures, the Lake of Mists "+
	   "remains at a warm temperature throughout the year, "+
	   "generating massive amounts of steam and fog on colder "+
	   "days, hence the name, 'Lake of Mists'. One local theory "+
	   "about the lake is that the underground forges and dwellings "+
	   "of the dwarves,who inhabit the earth underneath Almorel in "+
	   "unknown numbers, heats the bottom of the lake enough to keep "+
	   "it warm enough to avoid freezing. Fishermen thrive on the "+
	   "year-round crop of fish and plant life from the lake. "+
	   "Through the fog, out from the shore a ways stands a "+
	   "towering black structure. This is the tower of Raumkreml.\n");
  add_item(({"houses","huts","house","hut"}),
	   "The houses on the shore of the Lake of Mists are of  "+
	   "a slightly different design. The walls facing the lake "+
	   "are actually two walls. One wall made of thick logs with "+
	   "open spaces between, which is about a foot away from the "+
	   "actual wall. This is done to stop the harsh, strong winds "+
	   "before they get to the actual wall to prevent weather "+
	   "damage. The rooves are also designed differently. Where the "+
	   "houses in the rest of the village have symmetric angled "+
	   "rooves, these have a steep slant facing the lake; again "+
	   "to prevent weather damage.\n");
  add_item(({"ground","floor","dirt","down"}),
	   "The ground beneath your feet is packed with a mixture of "+
	   "ice, old snow, and recently fallen snow.\n");
  add_item(({"sky","air","up"}),
	   "The sky above Almorel seems to be eternally a mixture of "+
	   "dark blue and purple. The snow storms and blizzards are "+
	   "so frequent, and the climate so moist that the sun very "+
	   "rarely shines completely through the clouds. When it does "+
	   "however, it creates a dazzling prizmatic effect with all "+
	   "of the ice and snow in the village.\n");
  add_item(({"tower","raumkreml","Raumkreml","tower of raumkreml","spire"}),
	   "Through the massive bank of fog hanging over the Lake "+
	   "of Mists, you can see the shadowy outline of an enormous "+
	   "tower, possibly fifty to sixty meters in height. This tower "+
	   "is the central defensive station for the lake and the "+
	   "center for all government and law in Almorel.\n");

   
 /* This function is the one defined in the actual lake room,
     make sure this is defined!! */

  create_lakeside();
}
	
public void
create_lakeside()
{
  /* RE-DEFINE THIS IN YOUR OWN LAKESIDE ROOM! */
}

init()
{
  int rand;

  ::init();
 
  /* Create a 1 in 6 chance of seeing a nifty message when the
     room inits */
  rand=random(6);

  if (rand<2)
    {
      set_alarm(4.0,0.0,"make_noise");
    }
}

make_noise()
{
    filter(LAKEROOMS,"find_rooms",TO);
}

find_rooms(string roomstr)
{
  int msg;
  object room;

  msg=random(MAX_LAKE_MSGS);
  
  if (!LOAD_ERR(room=find_object("/d/Cirath/katakoro/almorel/"+roomstr)))
    tell_room(room,LAKE_MSGS[msg]);
  return 1;
}



