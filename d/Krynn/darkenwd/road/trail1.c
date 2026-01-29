/* Trail1 coded by Teth
 * April 2, 1996
 * Last update Oct 26, 1996
 */

#include "local.h"

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );

void
reset_darkenwd_room()
{
    set_searched(random(2));
}

void
create_darkenwd_room()
{
    set_place(TRAIL);

    set_long_desc("This path extends to the various game trails and picnic " +
      "areas in the region north of Prayer's Eye Peak. Northwards, the " +
      "road between Solace and Haven can also be reached. This area is " +
      "covered with forest. One Crystalmir pine tree stands out amongst " +
      "the rest. This path leads both north and south.");
    AI(({"trail","path"}),"This path appears to be fairly well-used, as "+
        "little vegetation covers it.\n");
    AI(({"Prayer's Eye Peak","Peak","peak","prayer's eye peak"}),"From this "+
        "distance, all you can discern are the two folds of rock which make "+
        "the peak resemble two hands pressed together in prayer.\n");
    AI(({"game trails","trails","areas","picnic areas"}),"These are too far "+
        "away to see anything in particular.\n");
    AI(({"Crystalmir pine","crystalmir pine","pine","pine tree","tree"}),
        "This sentinel of the forest stands over 40 meters tall. The lowest "+
        "branches are far too high up for you to reach, so it isn't "+
        "climbable. However, the bark of the tree looks damaged.\n");
    AI(({"tree bark","bark"}),"Scrawled into the bark are words that read:\n"+
        "    Beware!\n    The dead walk in Darken Wo..\n");
    AI("forest","The forest surrounds you, watching you.\n");
    AI("cicada","You can't find him, but you know he's there!\n");

    add_exit(TDIR + "forest9", "north",0,3,1);
    add_exit(TDIR + "trail2", "south","@@closed",3,1);

    set_tell_time(120);
    add_tell("The sounds of the forest suddenly stop, then resume again.\n");
    add_tell("A cicada somewhere nearby emits a loud tzzz-tzzz-tzzz!\n");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({ "bushes", "herbs", }), 4);
       OUTSIDE;  /* An outside room */

    reset_darkenwd_room();

}

int
closed()
{
    write("Unfortunately, the game trail to Prayer's Eye Peak is " +
          "closed at the moment.\n");
    return 1;
}

void
enter_inv (object ob, object from)
{
  ::enter_inv(ob, from);
  if (interactive(ob))
    start_room_tells();
}

