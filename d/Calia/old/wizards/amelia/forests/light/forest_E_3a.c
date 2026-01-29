/*
*	by Amelia, for use in the Light Forest
*/
inherit "/std/room";
#include "room_tell.c"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h"

void
create_room()
{
       set_short("A path in the light forest");
       set_long("This is a path that leads through the forest.  "+
                "Sunlight filters through the bower of leaves and "+
                "feels warm on your face.  A squirrel chatters noisily "+
                "on a branch high above your head.\n");

      set_tell_time(60);
       add_tell("A small bird flits from branch to bough overhead "+
                "and chirps cheerfully.\n");
       add_tell("A fresh breeze wafts to your nostrils the scent "+
                "of wildflowers.\n");
       add_tell("The squirrel chatters angrily.\n");

       add_item((({"sunlight", "light"})),
            ("The light makes everything appear bathed in a warm "+
		"and golden glow.  It makes you feel invigorated.\n"));
       add_item((({"bird", "small bird"})),
            ("The small black-and-white bird is amazingly agile "+
             "and makes cheerful chirping sounds that tell you its "+
             "name is a chickadee.\n"));
       add_item((({"path", "paths"})),
		("There is a path somewhat obscured by an overgrowth "+
		"of grass and moss.\n"));
       add_item((({"branch", "branches", "tree", "trees", "forest",
                   "leaf", "leaves"})),
		("Surrounding the path are various types of trees, "+
		"including oak, maple and pine trees.\n"));
	add_item((({"leaf", "leaves"})),
		("The leaves of maple and oak trees "+
		"give a little shade from the warm sun.\n"));
	add_item((({"squirrel", "grey squirrel"})),
		("The grey squirrel appears somewhat upset that you have "+
		"invaded its territory, but remains high up out of "+
		"reach.\n"));
	add_item((({"flower","flowers","wildflower","wildflowers"})),
		("Wild violets, daisies and primroses grow all "+
		"along the path.\n"));

       add_exit((FPATH+"forest_E_1a"), "west", 0, 0);
       add_exit((FPATH+"nearp"), "east", 0, 0);
       add_exit((FPATH+"forest_E_4a"), "southeast", 0, 0);

       add_prop(ROOM_I_LIGHT, 1);
       add_prop(ROOM_I_IS, 1);
       add_prop(ROOM_I_INSIDE, 0);
}

void
enter_inv(object ob, object from)
{
   start_room_tells();
	::enter_inv(TP, TO);
}
void
leave_inv(object ob, object to)
{
	remove_alarm(tell_alrm);
}
