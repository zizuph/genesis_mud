inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/gcamp/defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Mountain Trail");
  set_long("You are deep inside the Ringing Mountains now.  The "
  	+"wind's screams echo through the air, keeping you on "
  	+"edge, tensed for battle.  Deep shadows fall across the "
  	+"trail, their blackness only amplified by the bright "
  	+"yellowed light that reflects off the mountain peaks "
  	+"around you.  You notice that the rocks that have covered "
  	+"the ground throughout the trail have been mostly pushed "
  	+"aside here, as if something travelled through here.\n");  
    add_item("shadows","Their inky blackness blankets the road here, "
    	+"as the mountains above you partially block out the "
    	+"powerful rays of Athas's twin suns.\n");
    add_item("trail","It winds serpentlike through the mountains, "
    	+"plunging deeper towards their heart.\n");
    add_item("cliffs","They tower above both sides of the trail, "
    	+"their hard granite eroded almost to a smooth surface "
    	+"by the constant winds.\n");
    add_item(({"mountains","mountain","ringing mountains","cliffs"}),
    	"This massive collection of mountains rises up all around "
    	+"you here.  There are tales of the creatures who "
    	+"live in these mountains.\n");
    add_item(({"dunes","dune"}),"The deep dunes ripple and writhe "
    	+"like struggling serpents in the harsh winds.  They make "
    	+"it impossible to go westwards.\n");
    add_item("rocks","They lay strewn about here, obvious remnants "
    	+"of the mountains breaking before the onslaught of the "
    	+"fierce desert winds.\n");
   add_exit(DESERT + "p3","southwest");
   add_exit(DESERT + "p5","east");
    set_alarm(1.0,0.0,"reset_room");
}

