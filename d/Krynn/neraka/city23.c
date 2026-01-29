/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object baaz1, baaz2;

reset_tantallon_room()
{
    if(!objectp(baaz1))
        {
         baaz1 = clone_object("/d/Krynn/std/baaz");
         baaz1->set_color("red");
         BAAZ_COIN1->move(baaz1);
         BAAZ_COIN2->move(baaz1);
         baaz1->move(TO);
    }

    if(!objectp(baaz2))
        {
         baaz2 = clone_object("/d/Krynn/std/baaz");
         baaz2->set_color("red");
         BAAZ_COIN1->move(baaz2);
         BAAZ_COIN2->move(baaz2);
         baaz2->move(TO);
    }
}

create_tantallon_room()
{
    object door;

    set_short("Dirty place");
    set_long(BS(
    	"You are at a dirty place. West is a road and it seems to be the " +
	"only clean spot around. There are two tents here, one to the " +
	"north and the other is east. Mud is to the south but northeast " +
    "the ground seems a little more dry.", SL));

    add_item("tent",
        "Which tent do you mean, the north tent or the east tent?\n");
    add_item("north tent",BS(
    	"It's grey and rather big. Ten people could at least stand up in it. " +
    	"There is a lot of noise coming from it. You can see no entrance " +
	"though.", SL));
    add_item("east tent",BS(
    	"It's a small black tent. You see no entrance nor do you hear any " +
    	"sounds from it but it radiates evil.", SL));
    add_item("mud",
    	"Yuck, who would like to go there?\n");
    add_item("road",
    	"Seems like the most reasonable place to go to.\n");

    add_exit(TDIR + "city20", "northeast", 0);
    add_exit(TDIR + "city22", "west", 0);
    add_exit(TDIR + "city25", "south", 0);

    door = clone_object(OBJ + "d_city23_a");
    door->move(TO);
    door->set_key(K_CITY23);

    reset_tantallon_room();
}
