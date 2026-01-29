/*
 *  /d/Gondor/clubs/nisse/obj/hawk_feed.c
 *
 *  The hawk feed. It's cloned when the Nisse Othar hawk is sent to hunt.
 *
 *  Deagol, March 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/*
 *  Global variables
 */
string	*all_prey = ({"mouse", "rat", "bird", "rabbit", "shrew", "mole"});
string  *all_adj = ({"brown", "small", "tiny", "bloodied", "mangled", "grey",
                 "squealing"});

void
create_object()
{
    ::create_object();

    string prey = one_of_list(all_prey);
    string adj = one_of_list(all_adj);

    set_name(({prey, "prey", "feed"}));
    set_adj(adj);
    add_name(HAWK_FEED_ID);
    set_short(adj + " " + prey);
    set_long("You look closer at the " + short() + ". It has been hunted " +
        "down by your hawk. You can feed the hawk with it by the " +
        "<nihawk feed> command.\n");

    setuid();
    seteuid(getuid());
}
