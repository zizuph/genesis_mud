/*
 * This is a standard corpse, modified so that
 * I can set props in the leftovers for the
 * uruk quest in Rohan
 *
 * Olorin, March 1993
 */

inherit "/std/corpse";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>

/*
 * Function name: get_leftover
 * Description:   Get leftovers from the body.
 */
public int
get_leftover(string arg)
{
    mixed       corpses, leftovers;
    object      *found, *weapons, theorgan;
    int         i, slash;
    string      organ, vb, fail;

    if (this_player()->query_prop(TEMP_STDCORPSE_CHECKED))
        return 0;

    vb = query_verb();

    notify_fail(capitalize(vb) + " what from what?\n");  /* access failure */
    if (!arg)
        return 0;

    if (!parse_command(arg, environment(this_player()), "%s 'from' %i",
                organ, corpses))
        return 0;

    found = VISIBLE_ACCESS(corpses, "find_corpse", this_object());

    if (sizeof(found) == 1)
    {
        switch(vb)
        {
        case "cut":
            slash = 0;
            weapons = this_player()->query_weapon(-1);
            for (i = 0 ; i < sizeof(weapons) ; i++)
                if (weapons[i]->query_dt() & W_SLASH)
                    slash = 1;
            break;

        case "tear":
        default:
            slash = 0;
            break;
        }

        if (vb == "cut" && slash == 0)
        {
            notify_fail("@@get_fail:" + file_name(this_object()) +
                "|Better find something sharper than _that_ to cut with.\n@@");
            return 0;
        }

        leftovers = query_leftover(organ);
        if (!sizeof(leftovers) || leftovers[2] == 0)
        {
            notify_fail("@@get_fail:" + file_name(this_object()) +
                "|There's no such thing to get from the corpse.\n@@");
            return 0;
        }

        if (leftovers[5] && slash == 0)
        {
            notify_fail("You can't just tear this loose, use a knife or " +
                        "something...\n");
            return 0;
        }

        if (strlen(leftovers[3]))
            fail = check_call(leftovers[3]);

        if (strlen(fail))
        {
            notify_fail("@@get_fail:" + file_name(this_object()) + "|" +
                fail + ".\n@@");
            return 0;
        }

        if(leftovers[2]-- == 0)
            remove_leftover(leftovers[1]);

        say(QCTNAME(this_player()) + " " + vb + "s " + LANG_ADDART(organ) +
            " from " + QSHORT(found[0]) + ".\n");
        write("You " + vb +" " + LANG_ADDART(organ) + " from a corpse.\n");

        theorgan = clone_object(leftovers[0]);
        theorgan->leftover_init(leftovers[1], query_prop(CORPSE_S_RACE));

        // these lines added for quest prop - Olorin
        if (this_player()->query_prop("_elfhelm_uruk_quest"))
        {
            theorgan->add_prop("_elfhelm_uruk_quest_leftover",1);
        }
        if (theorgan->move(this_player(), 0))
	{
	    write("You cannot carry the " + organ + ".\n");
	    theorgan->move(environment(this_player()), 0);
	}
        return 1;
    }

    set_alarm(1.0, 0.0, &(this_player())->remove_prop(TEMP_STDCORPSE_CHECKED));
    this_player()->add_prop(TEMP_STDCORPSE_CHECKED, 1);
    if (sizeof(found))
        notify_fail("@@get_fail:" + file_name(this_object()) +
            "|Please try to be more specific with what corpses you choose.\n@@");
    else
        notify_fail("@@get_fail:" + file_name(this_object()) +
            "|There is no such corpse lying around here.\n@@");
    return 0;
}

public int
find_corpse(object ob)
{
    string  master = MASTER_OB(ob);

    if (((master == "/std/corpse") || master == ("/d/Gondor/rohan/npc/urukcorpse")) &&
        (environment(ob) == this_player() ||
         environment(ob) == environment(this_player())))
        return 1;

    return 0;
}

