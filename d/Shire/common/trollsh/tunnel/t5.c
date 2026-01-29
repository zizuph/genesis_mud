#include "../defs.h";
inherit "/d/Shire/room";

create_room()
{
    set_short("A tunnel under the Trollshaws");
    set_long(
    "As you climb down the smooth floored tunnel you are "+
    "reminded of all the worst smells you can think of. "+
    "Reddish water drips from the ceiling and you cannot "+
    "tell if it is red from blood or from the clay these "+
    "walls are dug from. Small puddles of this liquid have "+
    "formed at your feet and continue to flow deeper into "+
    "the tunnel. \n");
       
    add_item(({"puddle","puddles","liquid"}),
    "The puddles are filled with the same reddish liquid that "+
    "drips from the ceiling above. They are shallow and "+
    "you can see nothing in them.\n");
    add_item(({"floor","tunnel","ceiling","water","reddish water"}),
    "The floor is smooth, no bumps marring its surface, but "+
    "the ceiling is pocked in several places where the dripping "+
    "water has eaten away at the clay.\n");
    	
    add_item(({"smell","smells","worst smells"}),
    "The smell you can discern from below is one of death and "+
    "decay. Your conscience cries out to you to get away "+
    "from this place.\n");

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TROLLSH_DIR + "tunnel/t4", "south", 0, 2);
    add_exit(TROLLSH_DIR + "tunnel/t5", "north", 0, 3);
}
