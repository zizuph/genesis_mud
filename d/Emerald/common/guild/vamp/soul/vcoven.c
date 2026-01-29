#include "../guild.h"

void prompt_name();
void get_name(string str);
void prompt_member1(string cname);
void get_member1(string cname, object cmaster, string str);
void prompt_member2(string cname, object member1);
void get_member2(string cname, object cmaster, object member1, string str);
varargs void mkcoven(string cname, object member1, object member2);

int
vcoven(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    prompt_name();
    return 1;
}

void
prompt_name()
{
    write("What is the name of your coven?\n");
    input_to(get_name);
}

void
get_name(string str)
{
    if (str == "~q" || !strlen(str))
    {
        return;
    }

    if (sizeof(explode(str, " ")) > 1)
    {
        write("Please use only one word.\n");
        prompt_name();
        return;
    }

    if (strlen(str) > 15)
    {
        write("Name too long.  Try fewer than 15 characters.\n");
        prompt_name();
        return;
    }

    str = capitalize(str);    
    if (member_array(str, MANAGER->query_covens()) >= 0)
    {
        write("There is already a coven of that name.\n");
        prompt_name();
        return;
    }

    if (this_player()->query_wiz_level())
    {
        mkcoven(str);
        return;
    }

    prompt_member1(str);
}

void
prompt_member1(string cname)
{
    write("What is the name of the first member of your coven?\n");
    input_to(&get_member1(cname, this_player()));
}

void
catch_resp(int resp, object asker, object responder, function f)
{
    if (!responder || !asker)
    {
        return;
    }

    set_this_player(asker);

    if (resp == 0)
    {
        write(responder->query_The_name(asker) +
            " denied you.\n");
        responder->catch_tell("Ok.\n");
        return;
    }

    if (resp < 0)
    {
        write(responder->query_The_name(asker) +
            " failed to respond.\n");
        responder->catch_tell("No response.  Please try again if you wish to " +
            "continue.\n");
        return;
    }

    write(responder->query_The_name(asker) +
        " joined your coven.\n");
    responder->catch_tell("Ok.\n");

    f(responder);
}

void
get_member(string str, function f)
{
    object who, yn_ob;

    if (str == "~q" || !strlen(str))
    {
        return;
    }

    str = lower_case(str);

    if (!(who = present(str, environment(this_player()))) ||
        !CAN_SEE_IN_ROOM(this_player()) || !CAN_SEE(this_player(), who))
    {
         write("You can't see that person here.\n");
         return;
    }

    if (who->query_vamp_coven() != ROGUE_VAMPIRE)
    {
        write(capitalize(str) + " is not a valid candidate.\n");
        return;
    }

    setuid();
    seteuid(getuid());

    if (yn_ob = clone_object(YES_NO_OBJECT))
    {
        /* When yn_ob gets a "yes" or "no" answer, or it times out,
         * it reports back to this object with the answer
         */
        if (!yn_ob->get_answer(who,
            &catch_resp(, this_player(), who, f), 20.0))
	{
            // something failed in yn_ob...remove it.
            write("For some strange reason, you are unable to bring " +
                "yourself to ask " + who->query_the_name(this_player()) +
                "to join.\n");
            yn_ob->remove_object();
        }
        else
	{
    	    write("You ask " + who->query_the_name(this_player()) +
    		" if " + who->query_pronoun() + " will join your coven.\n");
    	    who->catch_tell(this_player()->query_The_name(who) +
    		" has accepted you into " + this_player()->query_possessive() +
    		" coven.  Do you wish to join? (Yes/No)\n");
	}
    }
}

void
get_member1(string cname, object cmaster, string str)
{
    set_this_player(cmaster);
    get_member(str, &prompt_member2(cname));
}

void
prompt_member2(string cname, object member1)
{
    write("What is the name of the second member of your coven?\n");
    input_to(&get_member2(cname, this_player(), member1));
}
    
void
get_member2(string cname, object cmaster, object member1, string str)
{
    set_this_player(cmaster);
    get_member(str, &mkcoven(cname, member1));
}

varargs void
mkcoven(string cname, object member1, object member2)
{
    if (!this_player()->query_wiz_level() && (!member1 || !member2))
    {
        write("You seem to have lost one of your potential coven members!\n");
        return;
    }

    setuid();
    seteuid(getuid());
   
    if (!MANAGER->add_coven(cname))
    {
        write("Failed to create a new coven!\n");
        return;
    }

    MANAGER->set_guild_titles(cname, ({ "Covenmaster of the " + cname + " Coven",
        "Vampire of the " + cname + " Coven" }));

    ({ this_player(), member1, member2 })->set_vamp_coven(cname);

    MANAGER->set_covenmaster(this_player());

    this_player()->add_cmdsoul(VAMP_COVENMASTER_CMDSOUL);
    this_player()->update_hooks();    
}
