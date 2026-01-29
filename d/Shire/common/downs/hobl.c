inherit "/std/room";


#include "defs.h"
#include "/sys/stdproperties.h"

create_room() {
    set_short("Path");
    set_long(break_string(
	  "You have entered a part of the land that is not dangerous. "
	+ "There's peace in the air."
        + "A huge sign stands here.\n",70));

    add_exit("/d/Genesis/start/hobbit/v/bw_road7", "west");

    
}

init() {
    ::init();
    add_action( "do_read", "read");
    add_action( "do_read", "exa");	
    add_action( "short", "enter");
}

do_read(str) {
	if(str == "sign")
    write(
	  "The sign says:"
	+ "East of here the Brandyland lies.\n"
	+ "It is not yet opened..\n"	
        + "but you may take a shortcut through to the old forest,\n"
       + "by typing enter shortcut.\n");
	return 1;
	}
short(str) {
	if(str == "shortcut");

	    this_player()->move_living("shortcut.", "/d/Shire/common/bree/forest1m");
    return 1;
}

/* inherit "/std/room"; *** why twice ? is it a filesystem fuckup ???  Dain. ****/

//#include "defs.h"
//#include "/sys/stdproperties.h"

//create_room() {
//    set_short("Path");
//    set_long(break_string(
//	  "You have entered a part of the land that is not dangerous. "
//	+ "There's peace in the air."
//        + "A huge sign stands here.\n",70));

//    add_exit("/d/Genesis/start/hobbit/v/bw_road7", "west");
//    add_exit("/d/Shire/common/buckland/buckr1.c", "@@my_west", );

    
//}

//init() {
//    ::init();
//    add_action( "do_read", "read");
//    add_action( "do_read", "exa");	
//    add_action( "short", "enter");
//}

//do_read(str) {
//	if(str == "sign")
//    write(
//	  "The sign says:"
//	+ "East of here the Brandyland lies.\n"
//	+ "It is not yet opened..\n"	
//        + "but you may take a shortcut through to the old forest,\n"
//       + "by typing enter shortcut.\n");
//	return 1;
//	}
//short(str) {
//	if(str == "shortcut");

//	    this_player()->move_living("shortcut.", "/d/Shire/common/bree/forest1m");
//    return 1;
//}

my_west()
{
    if(TP->query_wiz_level() > 1) 
	return 1;
    else return 0;
}
