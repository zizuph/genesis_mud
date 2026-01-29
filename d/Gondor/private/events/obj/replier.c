inherit "/std/object";

#include <flags.h>
#include <stdproperties.h>
#include <time.h>

void
create_object()
{
    set_name("replier");
    set_short("piece of junk");
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(PLAYER_I_SEE_ERRORS, 1);
    set_no_show();
}
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
 
    if (!living(dest))
    {
        remove_object();
    }
}
#include <macros.h>

object
redirect(object person)
{
    int i, size;
    object *oblist;

    oblist = users();

    i = -1;
    size = sizeof(oblist);
    while(++i < size)
    {
        if (oblist[i]->query_possessed() == person->query_real_name())
        {
            return oblist[i];
        }
    }

    return 0;
}

int
wiz_mess(string str)
{
    int idle;
    string name, message;
    object person, new_person, who = environment();

    if (!strlen(str))
    {
        notify_fail("Who do you want to tell what?\n");
        return 0;
    }
    sscanf(str, "%s %s", name, message);
    person = find_living(lower_case(name));
    name = capitalize(name);

    if (!objectp(person))
    {
        notify_fail("That player is not in the game.\n");
        return 0;
    }
    else if (person->query_prop(WIZARD_I_BUSY_LEVEL) & BUSY_F)
    {
        write(name + " seems to be busy at the moment. " +
            "If you want to be contacted when " + person->query_pronoun() +
            " is available again, use the 'audience' command.\n");
        return 1;
    }
    else if (!interactive(person))
    {
        new_person = redirect(person);
        if (objectp(new_person))
        {
            new_person->catch_tell(who->query_name() +
                (strlen(who->query_possessed()) ?
                ("(" + capitalize(who->query_possessed()) + ")") : ("")) +
                " tells you: " + message + "\n");
            if ((idle = query_idle(new_person)) > 300)
            {
                write(name + " is idle for " +
                    CONVTIME(idle) + " and may not react instantly.\n");
            }
            write("You tell " + name + "(" +
                new_person->query_name() + "): " + message + ".\n");
            return 1;
        }
        else
        {
            notify_fail(name + " is linkdead.\n");
            return 0;
        }
    }
    else
    {
        person->catch_tell(who->query_name() +
            (strlen(who->query_possessed()) ?
            ("(" + capitalize(who->query_possessed()) + ")") : ("")) +
            " tells you: " + message + "\n");
        if ((idle = query_idle(person)) > 300)
        {
            write(name + " is idle for " +
                CONVTIME(idle) + " and may not react instantly.\n");
        }
        write("You tell " + name + ": " + message + ".\n");
        return 1;
    }
}
int
esay(string str)
{
    tell_room(environment(this_player()), QCTNAME(this_player()) +
        " says: " + str + "\n");
    return 1;
}                                                                               

void
init()
{
    add_action(esay, "esay");
    add_action(wiz_mess, "tell");
    add_action(wiz_mess, "etell");
}
