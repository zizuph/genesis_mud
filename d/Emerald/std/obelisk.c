/*
 * Standard magical obelisk of the type used by the darklings for travel.
 * They enable teleportation between two obelisks.
 */

inherit "/std/object";

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <options.h>

#define OBELISK_ID "_emerald_obelisk_id"

public string destination = "";

public void
create_obelisk()
{
}

nomask void
create_object()
{
    set_name(({ "obelisk", OBELISK_ID }));
    set_adj("black");

    set_long("A plain, black obelisk set into the ground.  It bears no " +
        "markings whatsoever.\n");

    add_prop(OBJ_M_NO_GET, "It is immovable.\n");
    add_prop(OBJ_I_WEIGHT, 1000000);

    create_obelisk();
}

public void
set_destination(string dest)
{
    destination = dest;
}

public string
get_destionation()
{
   return destination;
}

public void
touch_obelisk()
{
    object dest, obelisk;
    string subl;

    if (!strlen(destination))
    {
        return;
    }

    LOAD_ERR(destination);
    if (!(dest = find_object(destination)))
    {
        return;
    }

    if (!(obelisk = present(OBELISK_ID, dest)))
    {
        return;
    }

    if (!this_player()->move_living("M", dest, 1, 1))
    {
        if (strlen(subl = obelisk->query_subloc()))
        {
            this_player()->move(dest, subl);
        }

	this_player()->do_glance(this_player()->query_option(OPT_BRIEF));
    }
}

/*
 * Shiva, this was badly bugged, and I noticed that the
 * code (or at least the docs) for emote_hook look to
 * have been recently changed/updated. Not sure if this
 * is a good solution, but since the vamps couldn't get
 * out of their startlocation, I took the liberty of
 * making this emergency change.
 *
 * Gorboth, June 25th, 2001
 */
public void
emote_hook(string emote, object actor, string adverb, object
*oblist, int cmd_attr, int target)
{
    if (cmd_attr & ACTION_CONTACT)
    {
        touch_obelisk();
    }
}



/*
public void
emote_hook(string verb, object actor, string adverb, int attrs)
{
    if (attrs & ACTION_CONTACT)
    {
        touch_obelisk();
    }
}
*/

public string
appraise_value(int num)
{
    return "an unknown amount";
}

public string
appraise_weight(int num)
{
    return "an unknown amount";
}

