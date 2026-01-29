/*
 * Original version by Elessar (?)
 *
 * Modification log:
 *  7-Dec-1996, Olorin: General revision.
 * 16-Mar-1998, Gnadnar: use parse_command() so can "read third message"
 * Modified for hobbit messengers in Frogmorton
 * -- Finwe, February 2002
 * 
 * Updated for faerie chipmunk messengers
 * Updated to use the new message standard base, Petros, December 2008
 */
#pragma save_binary
#pragma strict_types
 
inherit "/std/message";
 
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
 
public string
message_description()
{
    string sender, text, output;
    
    sender = query_sender();
    text = query_message();
    
    output = "This is a message from " + sender + ". When you are finished " +
        "with it, simply drop it to destroy it. The message says:\n" +
        "---------------------------------------------------------"+
        "----------------------\n\n"+
        text + "\n"+
        "========================================================"+
        "=======================\n\n";

    return output;
}

public void
create_message()
{
    add_name("note");
}
