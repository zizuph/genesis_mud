/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village of Rust. */

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>


object elite, guard1, guard2;

void
reset_room()
{
    seteuid(getuid());

    if (!objectp(guard1))
    {
        guard1 = clone_object(RUST_NPCS +"gnome_regular_guard");
        guard1->equip_me();
        guard1->move_living("in", TO);
    }
 
    if (!objectp(guard2))
    {
        guard2 = clone_object(RUST_NPCS +"gnome_regular_guard");
        guard2->equip_me();
        guard2->move_living("in", TO);
    }

    if (!objectp(elite))
    {
        elite = clone_object(RUST_NPCS +"gnome_elite_guard");
        elite->equip_me();
        elite->move_living("in", TO);
        elite->team_join(guard1);
        elite->team_join(guard2);
    }
}

create_room()
{
    set_short("Entrance to gnome village");

    set_long("This is the entrance to a small settlement" +
        " in the forest. The foliage around it is extraordinarily" +
        " thick; the only way to pass through is a small gap, a few" +
        " feet wide. There are a few of the great oaks inside the" +
        " perimeter, but not near as many as in the trackless forest" +
        " outside. A small hut has been placed to the east of the" +
        " opening, on the outside. You imagine sentries placed here" +
        " would be able to monitor all passage in and out.\n");

    add_item("settlement", "A small settlement is nestled inside.\n");
    add_item(({"foliage","perimeter"}), "It's very dense. You would" + 
        " need to be able to fly to get over it.\n");
    add_item(({"trees", "oaks"}), "It doesn't seem to be possible to" +
        " climb a tree here to get inside the village without passing" +
        " the guardpost. The nearest trees inside are too far away.\n");
    add_item(({"hut", "small hut"}), "The hut seeems to be made out of" +
        " oak branches, and looks functional. It doesn't have a door," +
        " instead a fur is draped across the entrance, preventing you" +
        " from seeing inside.\n");
    add_item("forest", "The great forest has a different feel in" +
        " this area, as if it has assumed some of the nature of" +
        " the people that dwell here.\n");
    add_item(({"fur"}), "It must have been well" +
        " prepared, for it feels almost like the fur of a live animal" +
        " to the touch.\n");
    add_item(({"gap","entrance"}), "It's pretty narrow. A couple of"  +
        " guards would be able to defend it well.\n");

    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VILLAGE+"village_path1","north",0,1);
    add_exit(VILLAGE+"village_guards_rest","in",0,1);
    add_exit(KEEP+"keep_path1","south",0,1);

    reset_room();
}
