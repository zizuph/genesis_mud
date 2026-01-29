inherit "/std/room";

#include "/d/Gondor/defs.h"

void create_room()
{
    set_long( "A dummy room for the steeds of the Nazgul.\n" );
    set_short( "Dummy room" );
}

public void enter_inv( object ob, object from )
{
    ::enter_inv( ob, from );

    if (!objectp( ob ) || !objectp( from ) || living( ob ))
	{
        return;
	}
    tell_room( from, "The "+ ob->short()+ " falls down through the "+
    	"clouds to the ground far below and is lost.\n" );
    ob->remove_object();
}

