#include "../defs.h";
inherit "/d/Shire/common/lib/room";
inherit "/d/Shire/std/room/room_tell";


create_room()
{
    add_prop(ROOM_S_MAP_FILE, "trollshaws2.txt");

    set_short("Tunnel");
    set_long(
        "You have entered a tunnel which leads down, underneath the " +
        "Trollshaws. The light fades as you look deeper down into the t" +
        "unnel. It is moist and there and a foul smell floats in the air. " +
        "Water trickles down from the roof and down deeper into the tunnel. " +
        "Looking up is the bush you entered to get down here, and down, " +
        "only darkness.\n");
       
    add_item("tunnel","The tunnel is dark further down, the bushes covering this tunnel "
    		     +"is not letting much light down here.\n");
    add_item("water","The water looks dirty and you should not try to drink it. Would "
    		    +"most likely give you a bad stomach.\n");
    add_item("roof","The roof of the tunnel is quite high, almost 7 feet.\n");
    add_item(({"wall","walls"}),
    		"The walls are dark, and moisty, making the air moisty too. Soft they are, "
    		+"and it is really amazing that they have been able to stand the time, without "
    		+"falling apart, closing the entire tunnel.\n");
    add_item(({"bush","bushes"}),
    		"It is behind these bushes that you will find the trollshaws, where you "
    		+"came from.\n");
    	
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    set_room_tell_time(30+random(60));
    add_room_tell("A dripping sound echoes in the distance.");
    add_room_tell("A large rat scampers past you.");
    add_room_tell("Some odd sounds echo in the distance.");
    add_room_tell("Something rancid smelling drifts past you.");
    add_room_tell("Water drips on you from above.");
    add_room_tell("A bloodcurdling scream echoes from somewhere " +
        "in the distance.");


    add_exit(TROLLSH_DIR + "tunnel2", "down", 0, 3);
    add_exit(TROLLSH_DIR + "shaws6", "out", 0, 3);

    add_exit(TROLLSH_DIR + "tunnel/ta24", "east", 0, 3);
    add_exit(TROLLSH_DIR + "tunnel/ta23", "west", 0, 3);

//    add_exit(TROLLSH_DIR + "tunnel/ta24", "east", "@@block_me@@");
//    add_exit(TROLLSH_DIR + "tunnel/ta23", "west", "@@block_me@@");
}


int
block_me()
{
    if (this_player()->query_wiz_level()) return 0;

        write("Large rocks and boulders block the entrance, " +
        "preventing you from going there. Snuffying and terrible " +
        "sounds echo out from between the rocks.\n");
    return 1;
}
