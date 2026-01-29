/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village of Rust.*/

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>

object jessup;

void
reset_room()
{
    seteuid(getuid());
    if (!objectp(jessup))
    {
        jessup=clone_object(RUST_NPCS+"old_gnome_jessup");
        jessup->equip_me();
        jessup->move_living("in",TO);
    }
}


create_room()
{
    set_short("Home in the gnome village");

    set_long("This hollowed tree is big enough to be the home of" +
        " a great family, but appears to have fallen into disrepair." +
        " A layer of dust has settled on most items here, and the" +
        " ladders up to the sleeping compartments look as if they" +
        " haven't been used for years. A great salmon has been" +
        " mounted on the wall in a display case. A fur across the" +
        " the opening still keeps the cold outside.\n");

    add_item(({"ladders","ladder"}),"They would probably snap if they" +
        " had to carry any weight, as they are almost rotted through.\n");
    add_item(({"compartments","sleeping compartments"}),"The furs in" +
        " them have all rotted away.\n");
    add_item(({"salmon","great salmon"}),"It looks like it's been there" +
        " for years and years. It must have been expertly prepared by a" +
        " taxidermist.\n");
    add_item(({"case","display case"}),"It's made out of glass and" +
        " pretty dusty.\n");
    add_item("fur","It's seen better days.\n");
    add_item(({"chair","rocking chair"}),"It's a rickety old rocking" +
        " chair.\n");

    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(VILLAGE+"village_path11","out",0,1);
    reset_room();
}
