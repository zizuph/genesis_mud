
inherit "/std/room";
#include "/d/Terel/common/terel_defs.h";
#include <macros.h>
#include <stdproperties.h>

#define BS(s)	(break_string(s, 70))
#define TP	this_player()

create_room(){
set_short("Ground floor Gallery");
set_long(BS(
"You have entered the ground floor gallery.  Various " +
"landscapes and portraits adorn the walls.  Not only " +
"are there a large number of very expensive paintings " +
"in this room, but the ceiling has also been painted.\n"));

add_prop(ROOM_I_INSIDE, 1);

add_exit(MANSION + "grand", "north", 0);

add_item("ceiling", BS("This is an odd looking ceiling painting. " +
    "It depicts dark characters crowding around a large black " +
    "slab adorned with a strange symbol.  The sun can be seen " +
    "rising, yet the sky remains black.  You realise that "+
    "the artist must have indeed been a genius.\n"));

add_item("symbol", BS("You can not quite make out the symbol " +
    "from your place standing on the floor.  However, it is " +
    "clear that the symbol is a dark red colour.\n"));

add_item(({"painting", "portrait", "paintings"}),
   "The thick dust makes these paintings difficult to recognise.\n");

add_cmd_item(({"painting", "portrait", "paintings"}),
            ({"get", "take", "clean", "dust", "wipe"}),
      ({"@@getp", "@@getp", "@@cleanp", "@@cleanp", "@@cleanp"}));

add_item("signature","@@signaturedescrip");

add_cmd_item("signature","read","@@readsignature");

add_prop(OBJ_S_WIZINFO, BS("The small signatures on the paintings don't " +
		"mean anything at the moment.  I (Napture) was going to " +
		"write a book on the family artist at some stage, but " +
		"I can't see that's it's important at the mo.  But feel " +
		"free to do so, then change the signature to that of the " +
		"artist's name."));
}

signaturedescrip()
{
    return("The signature is still hard to identify, " +
           "but you can just\nabout make out the following :\n" +
           "\'..d.r.nm..a\'.\n");
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
    say(QCTNAME(TP) + " wipes away some of the dirt on one of the paintings.\n");
    write("Careful!  These paintings are valuable.\n" +
          "Cleaning away a quantity of dust reveals a small signature.\n");
    return 1;
}
