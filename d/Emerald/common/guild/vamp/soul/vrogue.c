#include "../guild.h"

void catch_response(int resp, object who);

int
vrogue(string str)
{
    object yn_ob;

    if (strlen(str))
    {
        return 0;
    }

    if (this_player()->query_rogue_vampire())
    {
        write("You have already abandoned the coven.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    if (yn_ob = clone_object(YES_NO_OBJECT))
    {
        /* When yn_ob gets a "yes" or "no" answer, or it times out,
         * it reports back to this object with the answer
         */
        if (!yn_ob->get_answer(this_player(),
            &catch_response(, this_player()), 20.0))
	{
            // something failed in yn_ob...remove it.
            yn_ob->remove_object();
        }
        else
	{
            write("Are you sure you wish to become a rogue vampire!?! " +
                "(Yes/No)\n");
	}
    }

    return 1;
}

void
catch_response(int resp, object who)
{
    if (!who)
    {
        return;
    }

    if (resp == 0)
    {
        who->catch_tell("Ok.\n");
        return;
    }

    if (resp < 0)
    {
        who->catch_tell("No response.  Please try again if you wish to " +
            "continue.\n");
        return;
    }

    who->catch_tell("You abandon the coven.\n");

    who->set_vamp_coven(ROGUE_VAMPIRE);
}
