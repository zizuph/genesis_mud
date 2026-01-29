// file name:        port2.c
// creator(s):       Ilyian
// revision history: Denis, Sep'96: Changes due to the port inheritance recode.
//                   Lilith Sep 2021: Updated wall desc for Shrine quest.
// purpose:
// note:
// bug(s):
// to-do:

# pragma strict_types
# include "port.h";
inherit PORT_ROOM;
inherit "/d/Avenir/inherit/sair_wall";

static void
create_port_room()
{
    set_short("Eastern side of port cavern");
    set_long("You are on a wide ledge separating the waters of the port " +
             "to the west from a terrifying dropoff to the east. The noise " +
             "in the cavern is deafening, as winds buffet the walls and " +
             "churn the water. The whole area is lit by an unearthly white " +
             "glow that seems to come from the rocks above, but the grey " +
             "mist that hangs in the air prevents you from seeing very far " +
             "in any direction. The ledge continues to the north and the " +
             "south.\n");

    IN
    LIGHT

    add_exit("port1", "north");
    add_exit(PORT+"port3", "south");

    add_view_items();
    add_rift_no_see_item();
    add_no_swim_cmditems();

	add_item(({"wall", "walls"}),
            "This wall was hewn from the natural rock. It is wet "
		    +"from the mist and spray of the stormy port, and rivulets of "
			+"water run down it to the floor.\n");

 	add_sair_wall();
	set_sair_dest(({LEDGE+"ledge4", PORT +"port4", OUTPATH+"n4"}));


}

void init()
{
    sair_init();
    ::init();
}

