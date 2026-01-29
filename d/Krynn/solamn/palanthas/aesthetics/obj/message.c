/*
 * Based on carrier pigeon's ~Krynn/solamn/vin/obj/message.c
 * Credit to Tricky, Elessar, Nick, Olorin, and Aridor
 * for their work on that file.
 *
 * Page hired out as messenger in Aesthetics quarter of
 * Palanthas.  This is the message object they deliver.
 *
 * Mortis 05.2006
 *
 * Modified to use /std/message - 12/26/2008 - Petros
 */

#include "../../local.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

inherit "/std/message";

public string
message_description()
{
    string sender, text, output;
    
    sender = query_sender();
    text = query_message();

	output = "The message from " + sender + " reads:\n" 
	    + text + "\n\n(You may <tear> it up "
	    + "when finished.)\n";
    
    return output;
}

public void
create_message()
{
	set_short("@@my_short");

	add_prop(OBJ_I_WEIGHT,  30);
	add_prop(OBJ_I_VOLUME, 100);
	add_prop(OBJ_I_NO_SELL, "This vendor does not purchase personal notes.");
}

init()
{
    ::init();
	ADA("tear");
}

string
my_short()
{
	return ("message from " + query_sender());
}

int
tear(string str)
{
	NF("Tear what up?  Your message?\n");
	if (!str)
		return 0;

	if (str != "message" && str != "up message" && str != "message up")
		return 0;

	write("You tear up your message into tiny bits that float away "
	+ "with the wind.\n");
	say(QCTNAME(TP) + " tears up a message into tiny bits that float "
	+ "away with the wind.\n");
	remove_object();
	return 1;
}
