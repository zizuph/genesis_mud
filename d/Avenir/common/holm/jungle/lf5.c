// file name:        /d/Avenir/common/holm/jungle/lf5.c
// creator(s):       Lilith, Oct 96
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/jungle_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting herbs
 */
void reset_domain_room()
{
    set_searched(0);
    ::reset_domain_room();
}

/* Now create the room.  */
void
create_jungle_room()
{
    set_short("Following a narrow trail");
    set_long("This trail is very narrow and overhung by low "+
       "branches, as if made by small animals no taller than "+
       "your knee. You seem to have reached an intersection of "+
       "paths, one leading off into the bushes in the west, "+
       "and the other leading deeper south into the jungle. "+  
       "The bushes thin a bit to the northeast, allowing you "+
       "a glimpse of a wider, well-travelled trail."+
       "\n");

    add_exit(PJCON, "northeast", 0);
    add_exit("lf4", "west", 0);
    add_exit("lf8", "south", 0);

    add_item(({"trail", "path", "trails", "paths"}),
       "The trail going northwest intersects with two others "+
       "going west and south.\n");
    add_item(({"south", "south trail", "south path"}),
       "This path leads deeper into the jungle of this island's "+
       "center. It also seems to have a slight upward gradient.\n");
    add_item(({"west", "west trail", "west path"}),
       "This path leads west, toward the shore of the island. The "+
       "vegetation in this direction is thinner than to the south "+
       ".\n"); 

    add_cliff();
    add_seawall();
    add_fern();
    add_moss();
    add_atrack();
    reset_domain_room();
 

}
