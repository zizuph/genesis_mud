/*
 * Invite to the Telberin Minstrel Guild
 * -- Arman, December 2019
 */

#pragma save_binary
#pragma strict_types

inherit "/std/scroll";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>

/*
 * Prototype
 */
varargs void read_book_at_page(int page, string verb);

string invite_name = "";

void
set_invite_name(string str)
{
    invite_name = str;
}

public string
query_invite_name()
{
    return invite_name;
}

/*
 * Function name: create_scroll
 * Description:   creates the general object
 * Arguments:
 */
nomask void
create_scroll()
{
    set_short("formal invitation");
    set_name("invitation");
    add_name("minstrel_invitation");
    add_adj("formal");
    set_long("A formal invitation written in neat elvish script.\n");

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 0);
}

int 
destroy_invite(string str)
{
    if(str == "invitation" || str == "formal invitation")
    {
        write("You discard the formal invitation.\n");
        say(QCTNAME(this_player())+ " discards a formal invitation.\n");
        remove_object();
        return 1;
    }

    return 0;
}

/*
 * Function name: init
 * Description:   initialise the commands
 * Arguments:
 */
void
init()
{
    ::init();
    add_action(destroy_invite, "rip");
    add_action(destroy_invite, "tear");
    add_action(destroy_invite, "destroy");
    add_action(destroy_invite, "discard");
}

string
query_auto_load()
{
    return MASTER + ":";
}

/*
 * Function name: read_it
 * Description:   If player wanted to do anything to this book we end up here.
 * Arguments:     verb - The verb the player had used
 */
void
read_it(string verb)
{
    switch (verb)
    {
        case "read":
        case "mread":
            say(QCTNAME(this_player())+" reads a formal invitation.\n");
            read_book_at_page(1, verb); break;
    }
}

string
make_string_from_list(string *names)
{
    int i, s = sizeof(names);
    string text = "";

    sort_array(names);

    if(!s) return "  ----";
    if(find_player(names[0])) text += "*";
    text += capitalize(names[0]);
    for(i = 1; i < s-1; i++)
    {
        if(find_player(names[i])) text += ", *";
        else text += ", ";
        text += capitalize(names[i]);
    }
    if(s > 1)
    {
        if(find_player(names[s-1])) text += " and *";
        else text += " and ";
        text += capitalize(names[s-1]);
    }
    return break_string(text, 60, 5);
}

/*
 * Function name: read_book_at_page
 * Description:   should be redefined in your book. is called from read_me
 * Arguments:     which - read the book at which page
 *        verb  - If the player wanted to read it, or mread it.
 *            To mread something, you can look how the scoll.c does
 *            it in read_it() if needed.
 */
varargs void
read_book_at_page(int which, string verb)
{
    string list_str, minstrel_name;

    setuid();
    seteuid(getuid());

    if(!strlen(query_invite_name()))
        minstrel_name = "Mysterious Performer";
    else
        minstrel_name = query_invite_name();

        list_str = "Invitation to the College of Music\n\n"+
                   "   Dear " +minstrel_name+ ",\n\n" +
                   "   The High Bards of Telan-Ri have noted with interest your\n" +
                   "   growing fame as a performer amongst the citizens of the\n" +
                   "   realms. As the masters of the esteemed College of Music\n" +
                   "   in Telberin, we invite you to our exclusive halls. As\n" +
                   "   a Minstrel of the Muses there is much we can do to expand\n" +
                   "   on your understanding of your history that may assist in\n" +
                   "   the performance of your Songs of Power.\n\n" +
                   "   In anticipation of your visit,\n\n" +
                   "   Master Provost of the College of Music.\n\n";

        list_str = generate_scroll_text(list_str, "Minstrel's Guild of Telberin");
        write(list_str);

        return 0;

}
