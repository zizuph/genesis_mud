/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village of Rust.*/

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>

object child;
object male;
object housewife;

void
reset_room()
{
    seteuid(getuid());


    if (!objectp(housewife))
    {
        housewife = clone_object(RUST_NPCS +"gnome_housewife");
        housewife->equip_me();
        housewife->move_living("in", TO);
    }
 
    if (!objectp(child))
    {
        child = clone_object(RUST_NPCS +"gnome_child");
        child->equip_me();
        child->move_living("in", TO);
    }

    if (!objectp(male))
    {
        male = clone_object(RUST_NPCS +"gnome_male_adult");
        male->equip_me();
        male->move_living("in", TO);
        male->team_join(housewife);
        male->team_join(child);
    }
}

create_room()
{
    set_short("A home in the gnome village"); 

    set_long("You have entered a hollow tree. The ceiling is fairly" +
        " high up, so" +
        " even a human can stand straight. A low table and some chairs" +
        " stand on one side of the room. Compartments for sleeping" +
        " have been chiseled out far above the ground, a ladder" +
        " leading up to each. A fur covers the opening to the outside," +
        " and furs are also spread around the room for warmth and" +
        " comfort.\n");

    add_item("ceiling","It's about 10 feet up.\n");
    add_item(({"compartment","compartments"}), "They're big enough for" +
        " a gnome to fit, but any taller folks would be rather cramped.\n");
    add_item("ladder","It's wooden, with many steps, so easy to climb" +
        " even for a child.\n");
    add_item("fur", "It must have been well prepared, for it feels almost" +
        " like the fur of a live animal to the touch.\n");
    add_item("table","It's got four legs, and is probably big enough to" +
        " spread out a meal for an entire family.\n");
    add_item("chairs","These wooden chairs are obviously made for short" +
        " folk.\n");

    add_cmd_item("ladder","climb","You climb a couple of steps up the" +
        " ladder, and look into one of the sleeping compartments. It's" +
        " empty, so you climb down again.\n");
    
    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(VILLAGE+"village_path7","out",0,1);

    reset_room();
}
