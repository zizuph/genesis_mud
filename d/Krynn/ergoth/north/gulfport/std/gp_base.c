/* 
 * Street base file for Gulfport
 * Copytweaked from Haven town version
 * Tibbit, 30 April 1998
 *
 */

#include "../local.h"

inherit OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "urban", }) );

public void
reset_gulfport()
{

}

public void
reset_gulfport_room()
{
    set_searched(random(2));
    reset_gulfport();
}

public void
create_gulfport()
{

}

nomask void
create_gulfport_room()
{
    /* These generic descriptions should be adjusted and should be valid for
     * ALL outside/street rooms in Haven!
     */

    set_long_desc("You are in the town of Gulfport, home of the "+
        "emperor of Ergoth.");
    /* Additional long description valid for all outside rooms. */

    add_item("sky","It's above you.\n");

    set_tell_time(400);
    add_tell("You hear a church bell tolling from not far away.\n");
    
    OUTSIDE;
    
    seteuid(getuid(TO));
    set_up_herbs(({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs) }),
		 ({ "scraggly plants", "plant", "plants", }), 3);
    
    create_gulfport();
    reset_room();

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
      start_room_tells();
}

