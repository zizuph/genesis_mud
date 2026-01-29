inherit "/std/object";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

/* Global variables */
string gMessage, gSender;
int gOpen = 0;

public void
create_object()
{
    set_name("scroll");
    set_short("crumpled scroll");
    set_adj("crumpled");
    set_long("This is a delicate piece of parchment, crumpled by the beast "
    + "that delivered it. If you wish, you may 'tear' it or 'destroy' it.\n");
}

public void
set_message(string message)
{
    gMessage = message;
}

public string
query_message()
{
    return gMessage;
}

public void
set_sender(string sender)
{
    gSender = capitalize(sender);
}

public string
query_sender()
{
    return gSender;
}

public int
read_scroll(string str)
{
    mixed *scroll = FIND_STR_IN_OBJECT(str, this_player());

    if (!sizeof(scroll))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    if (scroll[0] == this_object())
    {
        if (!gOpen)
        {
            write("You unroll " + LANG_THESHORT(this_object()) + ".\n");
            gOpen = 1;
        }

        write(capitalize(LANG_THESHORT(this_object())) + " reads:\n");
        write(gMessage);
        say(QCTNAME(this_player()) + " looks over " + 
        LANG_THESHORT(this_object()) + ".\n");
        return 1;
    }
    else
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
}

private int
tear_scroll(string str)
{
    mixed *scroll = FIND_STR_IN_OBJECT(str, this_player());

    if (!sizeof(scroll))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    if (scroll[0] == this_object())
    {
        if (!gOpen)
        {
            write("Are you sure you wish to tear this scroll without " +
                "reading it first? If so, try again.\n");
            gOpen = 1;
            return 1;
        }

        write("You tear up the " + short() + " and discard it.\n");
        set_alarm(0.1, 0.0, &remove_object());
        return 1;
    }
    else
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
}

public void
init()
{
    ::init();

    add_action(read_scroll, "read");
    add_action(read_scroll, "study");
    add_action(tear_scroll, "tear");
    add_action(tear_scroll, "destroy");
}