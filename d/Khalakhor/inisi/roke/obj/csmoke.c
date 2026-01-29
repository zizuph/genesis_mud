/*
 * csmoke.c
 *
 * Used in obj/cigar.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

void
create_object()
{
    set_no_show();
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (for_obj == on)
        data = "You are ";
    else
        data = capitalize(environment(this_object())->query_pronoun()) +
               " is ";

    data += "stinking of disgusting cigar smoke.\n";

    return data;
}

void
enter_env(object dest,object old)
{
    dest->add_subloc("eckelsmoke", this_object());
    set_alarm(600.0, 0.0, &remove_object());
}

public void
leave_env(object from, object to)
{
    this_player()->remove_subloc("eckelsmoke");
}
