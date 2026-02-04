    set_short("In the well");
    set_long("@@long_desc");
    add_prop(ROOM_I_INSIDE,1);
    add_item("basket","@@desc_basket");
    add_item("rope","@@desc_rope");
    add_item("loam","You had better not touch that disgusting dried loam..\n");
    add_item("stones","Those stones are scattered on the shaft of the well.\n");
    add_item("ledge","This is a very narrow ledge, so you better take care.\n");
    add_item(({"shaft","well"}),
	break_string("This seems to be the shaft of a very deep " +
	"well. Above you can make out some light, while downwards the shaft " +
	"there's only darkness. You can hear the echo of your own " +
	"breathing...\n",70));
