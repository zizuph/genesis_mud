/*
 * The Common Room of Telseron   
 * The code was originally created by Xarguul
 * Modified by Finwe for Telseron, September 1996
 */
 
inherit "/std/room";
inherit "/doc/examples/new/room/common_room";
 
#include "/d/Emerald/defs.h"
 
void reset_room();
 
void
create_room()
 {
   ::create_room();
   set_short("The Common Room of the Pub");
   set_long("    The common room of the pub. Because the pub " +
        "gets too noisy for some residents, the pub owner bought " +
        "the abandoned building across the street. He turned it " +
        "into the Common Room where guests may come and enjoy a " +
        "peaceful atmosphere. This has resulted in becoming one " +
        "of the most popular places to discuss business privately " +
        "and exchange news. A few tables are spread around the " +
        "room for customers to sit at.\n\n");
 
   add_exit( TOWNSHIP_DIR + "rd16", "out");
 
}
 
void
reset_room()
{
}
