/*
 *  /d/Gondor/clubs/nisse/obj/jesses.c
 *
 *  The jesses for the Nisse hawks.
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
    
    set_name("jesses");
    add_name(NISSE_JESSES_ID);
    set_adj("small");
    add_adj("pair");
    add_adj("of");
    add_adj("leather");
    set_short("pair of small leather jesses");
    set_pshort("pairs of small leather jesses");
    set_long("These small leather straps are strong and resiliant. They " +
        "are made especially for falconry and are used to secure your hawk " +
        "or falcon to your arm. You need to attach them to your hawk or " +
        "falcon in order to keep the bird from randomly taking flight.\n");

    add_prop(OBJ_I_VALUE, 20);
    
    setuid();
    seteuid(getuid());
}

/*
 *  Function name: attach_hawk
 *  Description  : Attaches a hawk to a player's glove. It's called by
 *                 emotes.c.
 *  Returns      : always 1
 */
int
attach_hawk()
{
    write("You attach a " + short() + " on the tarsi of your hawk.\n");
    say(QCTNAME(TP) + " attaches a " + short() + " on the tarsi of " +
        POSSESSIVE(TP) + " hawk.\n");
    present(NISSE_HAWK_ID, TP)->attach_hawk();
    TO->set_no_show();
    return 1;
}

/*
 *  Function name: release_hawk
 *  Description  : Releases a hawk from a player's glove. It's called by
 *                 emotes.c.
 *  Returns      : always 1
 */
int
release_hawk()
{
    present(NISSE_HAWK_ID, TP)->release_hawk();
    TO->set_no_show_composite(0);
    TO->unset_no_show(0);
    write("You release a " + short() + " from the tarsi of your hawk.\n");
    say(QCTNAME(TP) + " releases a " + short() + " from the tarsi of " +
        POSSESSIVE(TP) + " hawk.\n");
    return 1;
}
