// file name:        /d/Avenir/common/village/temple/90.c
// creator(s):       Avenir Wizards, 05/02
// revisions:
// purpose:          Garden on the grounds of the Temple of the Idrys.
// note:           
// bug(s):
// to-do:

#pragma strict_types

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/village/garth_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/village/village.h"  

#include "/sys/stdproperties.h"


void
reset_domain_room()
{
   
}

/* Now create the room.  */
void
create_garth_room()
{
    set_short("meditation garden");
    set_long("This small garden is bisected by a wide cobbled "+
             "walk, south is the entrance to the temple.\n");

    add_exit("13", "south", 0);
    //add_exit("pathnw", "northwest", 0);
    //add_exit("pathne", "northeast", 0);



    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */
  


}

