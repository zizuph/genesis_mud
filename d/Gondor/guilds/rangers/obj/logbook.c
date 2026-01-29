/*
 * /d/Gondor/guilds/rangers/obj/logbook.c
 *
 * Based upon the faerie finder I coded for the kender guild with
 * assistance from Shiva.
 * 
 * Allows a log entry to be made for an apprentice or approved
 * apprentice. Call begin_entry(apprentice_name, writer_obj)
 * to start.
 *
 * Coded by Gwyneth, 24 March 2002
 */
inherit "/std/object";

#include <stdproperties.h>
#include "../rangers.h"

public void get_restriction(string str, string name, string who);
public void record_log(string text, string name, string who, int res);
public void confirm_entry(string confirm, string text, string name, string who, 
  int res);

void
create_object()
{
    set_name("logbook");
    set_short("logbook");
    set_long("This item shouldn't be visible. Please " +
        "submit a bug report if it is.\n");
    set_no_show();
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
}

public void
abort_entry()
{
    environment()->catch_tell("Perhaps another time then. You cease " +
        "your logbook entry.\n");
    set_alarm(0.1, 0.0, &remove_object());
    return;
}

public void
invalid_entry()
{
    environment()->catch_tell("You aren't allowed to write a log.\n");
    set_alarm(0.1, 0.0, &remove_object());
    return;
}

public void
leave_env(object from, object to)
{
    ::leave_inv(from, to);

    set_alarm(0.1, 0.0, &abort_entry());
}

public void
begin_entry(string name, object who)
{
    string writer = who->query_real_name();

    if (!MANAGER->query_ranger_level(writer))
    {
        invalid_entry();
        return;
    }

    set_this_player(who);
    writer = who->query_real_name();
    write("\nDo you want this to be readable by the " +
        "apprentice? (yes/no) or ~q to quit: ");
    input_to(&get_restriction(, name, writer));
}

public void
get_restriction(string str, string name, string who)
{
    if (!strlen(str))
    {
        write("You aren't very decisive. Enter yes, no or ~q to quit. ");
        input_to(&get_restriction(, name, who));
        return;
    }

    if (str == "~q")
    {
        abort_entry();
        return;
    }

    str = lower_case(str);
    if (str == "yes" || str == "y")
    {
        write("Enter ~q to quit or write a brief (256 characters or less) " +
            " log entry for " + capitalize(name) + ".\nHit enter when done.\n");
        input_to(&record_log(, name, who, 0));
        return;
    }
    else if (str == "no" || str == "n")
    {
        write("Enter ~q to quit or write a brief (256 characters or less) " +
            "log entry for " + capitalize(name) + ".\nHit enter when done.\n");
        input_to(&record_log(, name, who, 1));
        return;
    }
    else
    {
        write("You aren't very decisive. Enter yes, no or ~q to quit. ");
        input_to(&get_restriction(, name, who));
        return;
    }
}

public void
record_log(string text, string name, string who, int res)
{
    if (!strlen(text))
    {
        write("You aren't very decisive. Enter ~q to quit or write " +
            "a brief (256 characters or less) log entry for " + 
            capitalize(name) + ".\nHit enter when done.\n");
        input_to(&record_log(, name, who, res));
        return;
    }

    if (text == "~q")
    {
        abort_entry();
        return;
    }    

    if (strlen(text) > 256)
    {
        write("Please limit your comments to 256 characters or less! " +
            "Enter ~q to quit or write a brief log entry for " + 
            capitalize(name) + ".\nHit enter when done.\n");
        input_to(&record_log(, name, who, res));
        return;
    }
    
    write("Are you sure you wish to write " + text + "\nin the logbook " +
        "of " + capitalize(name) + "? (yes/no/~q) ");
    input_to(&confirm_entry(, text, name, who, res));
    return;
}

public void
confirm_entry(string confirm, string text, string name, string who, int res)
{
    if (!strlen(confirm))
    {
        write("You aren't very decisive. Enter yes, no or ~q to quit. ");
        input_to(&confirm_entry(, text, name, who, res));
        return;
    }

    if (confirm == "~q")
    {
        abort_entry();
        return;
    }

    confirm = lower_case(confirm);
    if (confirm == "yes" || confirm == "y")
    {
        MANAGER->add_apprentice_log(name, who, text, res);
        return;
    }
    else if (confirm == "no" || confirm == "n")
    {
        write("\nDo you want this to be an entry readable by the " +
            "apprentice? (yes/no) or ~q to quit: ");
        input_to(&get_restriction(, name, who));
        return;
    }
    else
    {
        write("You aren't very decisive. Enter yes, no or ~q to quit. ");
        input_to(&confirm_entry(, text, name, who, res));
        return;
    }

}
