/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village of Rust. */

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
    set_short("Home in the gnome village");

    set_long("You have entered a small hut. Any tall folk" +
        " would have walk bent over in here to avoid hitting the" +
        " ceiling. On one side of the room stands a table and" +
        " some chairs, in the other end a handful of beds, some" +
        " small and others smaller. The floor is made out of wooden" +
        " planks, and mostly covered by a blue rug. A fur covers the" +
        " opening to the outside.\n");

    add_item("ceiling","It's about a meter and a half up.\n");
    add_item(({"bed","beds"}), "They look like pretty soft beds," +
        " each with a fur to snuggle up against on a cold night.\n");
    add_item("fur", "It must have been well prepared, for it feels almost" +
        " like the fur of a live animal to the touch.\n");
    add_item("table","It's got four legs, and is probably big enough to" +
        " spread out a meal for an entire family.\n");
    add_item("chairs","These wooden chairs are obviously made for short" +
        " folk.\n");
    add_item(({"floor","planks"}),"The planks have been roughly cut, and" +
        " in some places weeds or grass grow out of the gaps between them." +
        "\n");
    add_item(({"rug","blue rug"}),"It's a finely woven rug, with a light blue" +
        " colour and black stripes in a diagonal pattern.\n");
    add_item(({"weeds","grass"}),"You would think the inhabitants would remove" +
        " these, but they obviously don't mind them.\n");

    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(VILLAGE+"village_path12","out",0,1);

    reset_room();
}
