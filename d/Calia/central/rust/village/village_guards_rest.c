/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village that doesn't have a name, yet;) */

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>

object elite, guard1, guard2, ggroup;

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
        elite = clone_object(RUST_NPCS +"gnome_elite_guard2");
        elite->equip_me();
        elite->move_living("in", TO);
        elite->team_join(guard1);
        elite->team_join(guard2);
        (RUST_SPECIALS + "guard_rescue.c")->add_guard(elite); 
    }
}

create_room()
{
    set_short("Guard resting room");
    
    set_long("You've entered a small hut. A lamp fastened to a" +
        " wall casts the room in dim light. There are two wooden" +
        " benches and a low table. A fur is covering the opening" +
        " you entered through, and serves to keep what little warmth" +
        " there is here inside. You surmise that this is a room" +
        " where the entrance guards rest between shifts.\n");
    
    add_item("lamp","It's an oil lamp that's been secured to the" +
        " wall.\n");
    add_item(({"wall","walls"}), "They're made of oak branches, and" +
        " seem sturdy.\n");
    add_item(({"bench","benches"}), "The benches are made out of wood" +
        " and don't look too comfortable to sit on for any length of" +
        " time.\n");
    add_item("table", "The wooden table would only reach the knees" +
        " of a grown human, but is just right for small folk.\n");
    add_item(({"fur","opening","entrance"}), "It must have been well" +
        " prepared, for it feels almost like the fur of a live animal" +
        " to the touch.\n");

    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(VILLAGE+"village_entrance","out",0,1);

    reset_room();
}
