// file name:        /d/Avenir/common/holm/jungle/stump.c
// creator(s):       Lilith, Nov 96
// revisions:        Lilith, Jun 97
// purpose:
// note:
// bug(s):
// to-do

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/inherit/room";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"
#include "/d/Avenir/smis/sys/statserv.h"

#define ENTER  "/d/Avenir/common/holm/jungle/lf15"

int exit_check();

/* Now create the room.  */
void
create_domain_room()
{
    set_area("junglep");
    set_short("inside a rotted-out stump");
    set_long(
        "You stand inside the cathedral pillar of a rotting stump.\n"+
        "You can see mud tubes running up the sides of the trunk,\n"+
        "and more mud and detritus where you are standing.\n");

    add_item(({"stump", "pillar", "trunk", "sides"}), 
        "This is the rotting remains of a once-great tree. It "+
        "juts up into the air like a cathedral pillar, intri"+
        "cately scarred by the efforts of wood-destroying "+
        "insects. It is covered with mud-tubes.\n");
    add_item(({"mud", "mud tubes"}), "These mud tubes are all "+
        "uniform in size, though they zig and zag along the sides "+
        "of this stump.\n");
    add_item(({"detritus", "ground", "floor", "grubs", "nest" }),
        "There are lots of white grub-like things wiggling "+
        "around in the mud beneath your feet. Looks like you're "+
        "standing in the middle of a termite nest!\n");    
    add_exit(JUNG + "lf15", "up", exit_check);    
}

int
exit_check()
{
    write("You hoist yourself up out of the stump and "+
       "slide down it, onto the ground.\n\n");
    return 0;
}  

void
leave_inv(object ob, object from)
{
    ::leave_inv(ob, from);
    if (interactive(ob))
        ENTER->set_full(0);   
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob) &&
       (file_name(from) == ENTER))
        STATSERV_LOG_EVENT("holm", "Entered stump");
}


