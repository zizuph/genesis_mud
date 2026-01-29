/* Traveltell to all travellers.
 */

inherit "/std/object";

#include <options.h>
#include <stdproperties.h>
#include <macros.h>
#include "../guild.h"

void
create_object()
{
    set_name("stick");
    set_short("odd looking stick");
    add_adj("odd");
    add_name("microphone");
    add_prop(OBJ_M_NO_DROP, 1);
    set_long("This oddly shaped stick appears to "+
        "be a microphone of some sort. You can use it to talk to "+
        "all members of the Travellers at once. Just use "+
        "\"trtell <msg>\" or \"travtell <msg>\"\n");
}
 
int
query_recover()
{
    return 0;
}

string
query_auto_load() { return MASTER + ":"; }
 
void
enter_env(object env, object from)
{
    ::enter_env(env, from);
 
    if (!living(env) || !env->query_wiz_level())
    {
        remove_object();
    }
}
 
int
trtell(string str)
{
    object *ppl;
    mixed prop;
    int i, cnt = 0;
 
    if (!this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!strlen(str)) 
    {
        notify_fail("Tell them what?\n");
        return 0;
    }
 
    ppl = users();
    for (i = 0; i < sizeof(ppl); i++)
    {
        if (!ppl[i]->query_guild_member(GUILD_NAME))
	{
            continue;
	}

        if (ppl[i]->query_wiz_level() &&
            (ppl[i]->query_prop(WIZARD_I_BUSY_LEVEL) & (2 | 8 | 16 | 128)))
        {
             continue;
        }

        cnt++;

        ppl[i]->catch_tell("\n"+
                "*+*+*+*\n" + (this_player()->query_name()) + " tells all "+
                "Travellers:\n"+ str + "\n*+*+*+*\n");

        prop = ppl[i]->query_prop(PLAYER_AS_REPLY_WIZARD);
        if (pointerp(prop))
	{
	    prop += ({ this_player()->query_real_name() });
	}
        else
	{
	    prop = ({ this_player()->query_real_name() });
        }

        ppl[i]->add_prop(PLAYER_AS_REPLY_WIZARD, prop);

    }

    if (this_player()->query_option(OPT_ECHO))
    {
        write("\nYou tell the Travellers:  " + str + "\n\n");
    }

    write(cnt + " received your message.\n");

    return 1;
}
 
void init()
{
    ::init();
    add_action(trtell, "trtell");
    add_action(trtell, "travtell");
}
