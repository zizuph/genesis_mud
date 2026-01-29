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
set_long("Standing to the south here is the last thing you "
	+"expected to see, a large stone fortress.  With walls "
	+"standing about 15 feet high, and obviously thick, the "
	+"fortress is a very imposing site.  Where normally a "
	+"massive gate would be is nothing but but a tunnel "
	+"leading into the fortress.  You see two tall towers "
	+"stretching up against the massive cliff behind the "
	+"fortress, obviously lookout towers.\n");
add_item("fortress","A large stone fortress, most likely built "
	+"in the Age of Champions when war was the favored "
	+"pasttime of most of Athas's people.\n");
add_item("tunnel","A massive tunnel burrows through the wall and "
	+"into the compound.  Any remnants of a gate are gone.\n");
add_item(({"tower","towers","tall towers"}),
	"These towers rise high up above the fortress, clinging "
	+"to the cliff behind them liks some sort of parasitic "
	+"vine.\n");

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
    add_exit(DESERT + "p6","northwest");
    add_exit(CAMP + "campent","south");
    set_alarm(1.0,0.0,"reset_room");
}

