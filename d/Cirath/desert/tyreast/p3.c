inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/gcamp/defs.h"
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("gith",GITH_NPC+"gith1",1,1);
}


void
create_room()
 {
  set_short("Turn in Mountain Trail");
  set_long("The trail turns here, heading straight eastwards "
  	+"for a bit.  The ever present fanglike mountains angrily "
  	+"claw at the sky above you, while you attempt to make "
  	+"your way through the scattered rocks that litter the "
  	+"ground here like some ancient fossilized bones.\n");   
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
   add_exit(DESERT + "p2","west");
    add_exit(DESERT + "p4","northeast");
    set_alarm(1.0,0.0,"reset_room");
}

