inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Mountain Trail");
  set_long("A narrow trail winds itself careful through the peaks "
  	+"of the Ringing Mountains here.  Sheer cliffs rise up on "
  	+"either side of the path, creating a natural hallway that "
  	+"leads northeast and southwest.  Rocks cover the ground "
  	+"here, almost certainly remnants of some past avalanche.  "
  	+"A low roaring noise echoes through the canyon here, as "
  	+"the desert wind pours through the mountains.\n");   
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
    add_exit(DESERT + "d20","southwest");
    add_exit(DESERT + "p2","northeast");
}

