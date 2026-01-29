inherit "/d/Gondor/minas/houses/citizens/suspect_home";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"


void
create_suspect_room()
{
    add_exit(MINAS_DIR + "houses/citizens/h8r2","west",0,0);
    add_exit(MINAS_DIR + "houses/citizens/h8r3","south",0,0);
    add_exit(MINAS_DIR + "houses/citizens/h8r4","up",0,0);

    set_door_id("MT_h8_alleycrc4");
    set_door_command(({"n","north"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(MINAS_DIR+"alleycrc4");
    set_door_desc(BSN(
        "This door is made of a white wood. It seems to have " +
        "been crafted recently, as the pine wood is still fragrant."));

    set_suspect(7);
    set_wealth(1);
    set_side("south");
    set_circle("Fourth Circle");

    set_short("foyer");
    set_long(BSN(
        "This is the foyer of a rather large house. The surroundings " +
        "are not indicative of any great wealth, but this seems " +
        "to be a larger residence than those in the lower circles, " +
        "and it is definitely much older. There is a staircase " +
        "leading up to the second floor, and doorways leading west " +
        "and south. A rug covers the floor and the door is flanked " +
        "by two vases. There is a window on the east wall and " +
        "an iron lamp mounted on the south wall above the doorway."));
    add_item(({"stairs","stairway","staircase"}), BSN(
        "The stairs are made of wood from the brethil tree. They " +
        "run straight south to the second floor and are flanked " +
       "by the wall and a brethil-wood banister."));
    add_item(({"banister","railing"}), BSN(
        "The banister supports a railing to protect those using " +
        "the stairs from falling. The wood is polished smooth."));
    add_item(({"doorway","passage"}), BSN(
        "Why don't you check it out?"));
    add_item(({"rug","carpet"}), BSN(
        "This large carpet covers most of the floor in this " +
        "foyer. It bears an ornate floral pattern and is very " +
        "beautiful."));
    add_item(({"vase","pot"}), BSN(
        "The large vases hold dried flora in a decorative " +
        "manner. You see brilliant mallos blooms, sweet-smelling " +
        "laurinique boughs, and even some galenas sprigs."));

    add_window("The window is tinted a bluish color.");
    add_walls("The walls are bare in this room.");
    add_ceiling("The ceiling is arched.");
    add_floor("The floor is mostly covered by a beautiful rug.");

    add_lamp();

}
