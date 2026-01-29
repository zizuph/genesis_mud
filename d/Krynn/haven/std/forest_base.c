/* Forest base file for Haven.
* By Teth, Feb 97
*/

#include "../local.h"

inherit OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );

public void
reset_haven_room()
{
    set_searched(random(2));
}

public void
create_forest()
{

}

nomask void
create_haven_room()
{
    set_place(FOREST);
    set_long_desc("You travel through a mixed woods forest, to the west of " +
      "the city.");

    add_item(({"forest","woods", "mixed woods", "mixed woods forest"}),
      "The mixed woods forest contains both coniferous and deciduous "+
      "trees.\n");
    add_item("tree","There are many trees in a forest. If one falls, and " +
      "there is no one around, does it make a sound?\n");
    add_item("trees","The trees are of two types, coniferous and " +
      "deciduous. They support a fair amount of herb growth beneath them.\n");
    add_item(({"herb growth","growth"}),"There may be useful herbs if you " +
      "search here.\n");
    add_item(({"coniferous trees","conifers"}),"The coniferous trees " +
      "add an aura of mystery to the forest, as they stand tall and " +
      "silent.\n");
    add_item("deciduous trees","The deciduous trees lend shades of grey " +
      "and white to the forest level around you, with their different " +
      "colours of bark.\n");
    add_item("bark","None of the bark on the trees looks remarkable.\n");
    add_item("sky","It's above you.\n");


    set_tell_time(500);
    add_tell("The forest has a near mystical air about it.\n");
    add_tell("Forest sounds surround you.\n");
    add_tell("The clamour of the Haven market can be dimly heard far to " +
      "the east.\n");

    OUTSIDE;

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({ "growth", "herb growth", }), 3);

    create_forest();
    reset_room();

}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

