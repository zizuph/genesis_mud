/*
 *  /d/Gondor/clubs/nisse/obj/hood.c
 *
 *  The hood for the Nisse hawks.
 *
 *  Deagol, April 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

void
create_object()
{
    ::create_object();
    
    set_name("hood");
    add_name(NISSE_HOOD_ID);
    set_adj("tiny");
    add_adj("black");
    set_short("tiny black hood");
    set_long("This tiny black hood is used for falconry, though the small " +
        "size of this hood makes it best suited to a small breed of hawk. " +
        "The black hood has laces on the back to secure it in place. You " +
        "should place this hood on your hawk to help it remain calm and " +
        "quiet while your are carrying it.\n");

    add_item("laces",
        "The laces on the hood are thin leather strips which are very " +
        "strong and meant to last through all sorts of weather.\n");

    add_prop(OBJ_I_VALUE, 60);
    
    setuid();
    seteuid(getuid());
}

/*
 *  Function name: wear_hood
 *  Description  : Wears a hood on a hawk's head. It's called by emotes.c.
 *  Returns      : always 1
 */
int
wear_hood()
{
    write("You put a " + short() + " on the head of your hawk.\n");
    say(QCTNAME(TP) + " puts a " + short() + " on the head of " +
        POSSESSIVE(TP) + " hawk.\n");
    present(NISSE_HAWK_ID, TP)->hood_hawk();
    TO->set_no_show();
    return 1;
}

/* 
 *  Function name: remove_hood
 *  Description  : Removes a hood from a hawk's head. It's called by emotes.c.
 *  Returns      : always 1
 */
int
remove_hood()
{
    present(NISSE_HAWK_ID, TP)->unhood_hawk();
    TO->set_no_show_composite(0);
    TO->unset_no_show(0);
    write("You remove a " + short() + " from the head of your hawk.\n");
    say(QCTNAME(TP) + " removes a " + short() + " from the head of " +
        POSSESSIVE(TP) + " hawk.\n");
    return 1;
}
