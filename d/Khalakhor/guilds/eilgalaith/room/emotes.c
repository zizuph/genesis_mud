/**********************************************************************
 * - emotes.c                                                       - *
 * - Allow free emotes in selected areas.                           - *
 * - Borrowed from mudlib emotes.                                   - *
 * - Created by Damaris@Genesis 08/2006                             - *
 **********************************************************************/

#include <macros.h>
#include <options.h>
#include <filter_funs.h>


/**********************************************************************
 * - emote - emote something                                        - *
 **********************************************************************/

static nomask string
cat_string(mixed org, string what, object pl, int up)
{
    if (objectp(pl))
        org[1] += (pl == org[0] ? (up == 1 ? "You" : "you") :
            (up == 1 ? QCTNAME(pl) : QTNAME(pl)));
    else
        org[1] += what;
    
    return org;
}

static nomask mixed
mk_item(object ob)
{
    return ({ ob, "" });
}

static nomask void
tell_them(object ob, mixed arg)
{
    arg[0]->catch_msg(QCTNAME(ob) + arg[1] + "\n");
}

nomask int
emote(string arg)
{
    object      pl, *pls;
    string      *args, *nms, oarg;
    int         i, sz, up;
    mapping     emap;

    pls = FILTER_LIVE(all_inventory(environment(this_player()))) -
        ({ this_player() });
    emap = mkmapping(pls, map(pls, mk_item));

    if (!stringp(arg))
    {
        notify_fail("Usage: : <emote string>, emote string can contain " +
            "names of present people enclosed in '|' characters, which " +
            "then will be identified by their met/nonmet names to observers. " +
            "e.g. ': smile fondly at |mrpr|.'\n");
        return 0;
    }

    /* Allows "emote 's head ..." -> "Mrpr's head ..." and yes the ''' does
     * look funny, but that's the syntax for getting the integer value of a
     * single quote.
     */
    if (arg[0] != ''')
    {
        arg = " " + arg;
    }

    oarg = arg;
    args = explode(arg, "|");

    emap = map(emap, &cat_string(, args[0], 0, 0));
    if ((sz = sizeof(args)) > 1)
    {
        for (i = 1 ; i < sz ; i ++)
        {
            nms = explode(args[i], " ");
            up = nms[0] == lower_case(nms[0]) ? 0 : 1;
            nms[0] = lower_case(nms[0]);
            if (objectp((pl = present(nms[0], environment(this_player())))))
            {
                emap = map(emap, &cat_string(, "", pl, up));
                if (sizeof(nms) > 1)
                {
                    arg = implode(nms[1..], " ");
                    emap = map(emap, &cat_string(, arg, 0, up));
                }
            }
            else if (i % 2)
                return notify_fail("You cannot see " + nms[0] + " here.\n");
            else
                emap = map(emap, &cat_string(, args[i], 0, up));
        }
    }

    map(emap, &tell_them(this_player(), ));

    if (this_player()->query_option(OPT_ECHO))
        write("You emote: |" + capitalize(this_player()->query_real_name()) +
            "|" + oarg + "\n");
    else
        write("Ok.\n");
    return 1;
}


nomask void
init_emotes()
{
	if (this_player()->query_wiz_level())
	return;
	
	add_action(emote, "emote");
	add_action(emote, ":", 2);
}
