
inherit "/std/room";
#include "/d/Terel/common/terel_defs.h";
#include <macros.h>
#include <stdproperties.h>

#define BS(s)	(break_string(s, 70))
#define TP	this_player()

#define EAST_EXIT  MANSION + "second/gallery_e"
#define WEST_EXIT  MANSION + "second/gallery_w"
#define NORTH_EXIT MANSION + "second/landing_s2"

create_room(){
    set_short("Second floor Gallery");
    set_long(BS("You have entered the centre of an incredibly long " +
	"room, full of portraits of various people.  The room " +
	"continues both to the east and the west.  There is a thick, " +
	"plush burgandy carpet running along the centre, extending " +
    "into the further reaches of the room.\n"));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(EAST_EXIT, "east", 0);
    add_exit(WEST_EXIT, "west", 0);

    add_item(({"door", "doorway"}),
	"The doorway is odd, as there is no door.\n");

    add_item(({"carpet", "plush carpet"}), BS("The thick carpet covers " +
        "most of the floor except along the north and south walls " +
        "where you can see the highly polished floorboards.\n"));
        
    add_item(({"boards", "floorboards", "polished floorboards"}),
        "These boards are in very good condition and look quite slippery.\n");
	
    add_item(({"painting", "portrait", "paintings"}),
        "The thick dust makes these paintings difficult to recognise.\n");

    add_cmd_item(({"painting", "portrait", "paintings", "portraits"}),
        ({"get", "take", "clean", "dust", "wipe"}),
        ({"@@getp", "@@getp", "@@cleanp", "@@cleanp", "@@cleanp"}));

    add_item("signature","@@signaturedescrip");

    add_cmd_item("signature","read","@@readsignature");

    add_prop(OBJ_S_WIZINFO, 
		BS("The small signatures on the paintings don't " +
		"mean anything at the moment.  Though there are by " +
		"Geordio Palanen.  I (Napture) was going to " +
		"write a book on the family artist at some stage, but " +
		"I can't see that's it's important at the mo.  But feel " +
		"free to do so, then change the signature to that of the " +
		"artist's name."));
}

signaturedescrip()
{
    return("The signature is still hard to identify, " +
           "but you can just\nabout make out the following :\n" +
	   "\'G..r.i. .ala.e.\'\n");
}

readsignature()
{
    write(signaturedescrip());
    say(QCTNAME(TP) + " peers closely at one of the paintings.\n");
    return 1;
}

getp()
{
    write("The paintings are much to heavy to remove from the wall.\n");
    return 1;
}

cleanp()
{
    say(QCTNAME(TP) +
          " wipes away some of the dirt on one of the paintings.\n");
    write("Careful!  These paintings are valuable.\n" +
          "Cleaning away a quantity of dust reveals a small signature.\n");
    return 1;
}

north_exit()
{
    write("You pass through the open doorway.\n");
    return 0;
}
