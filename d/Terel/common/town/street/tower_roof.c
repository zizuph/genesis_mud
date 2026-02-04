inherit "/std/room";

#include <macros.h>

void
create_room()
{
    set_short("Roof of the tower");
    set_long("Standing on the roof of the tower provides you with an " +
        "excellent view of the surrounding land, including the nearby " +
        "city of Calathin.\n");

    add_item("roof", "The roof of the tower is formed of the same " +
        "light-coloured stones which make up the walls.  Toward the " +
        "north side of the tower, several stones have fallen in, " +
        "leaving a hole open to the inside of the tower.\n");

    
    setuid();
    seteuid(getuid());
    clone_object("/d/Terel/common/town/street/tower_cont")->move(this_object(), 1);
	
	add_prop(ROOM_I_NO_CLEANUP, 1);

}

int
climb(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    if (str != "down")
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    write("You quickly climb down the wall to the ground.\n");
    say(({ METNAME + " climbs down the wall to the ground.\n",
           ART_NONMETNAME + " climbs down the wall to the ground.\n",
           "" }));

    this_player()->move_living("X",
        "/d/Terel/common/town/street/west_tower", 1);

    say(({ METNAME + " climbs down the wall to the ground.\n",
           ART_NONMETNAME + " climbs down the wall to the ground.\n",
           "" }));

    return 1;
}
    
void
init()
{
    ::init();
    add_action(climb, "climb");
}
