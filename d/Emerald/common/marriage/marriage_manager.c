/*
 * marriage_manager.c
 *
 * A tiny little object trying to keep track of all the married couples of
 * Genesis.
 *
 * Copyright (C): Lugdush 1995
 *
 * Last updated: 1995-10-20
 *
 */

#pragma no_clone
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <std.h>

#define MARRIAGE_SAVE           "/d/Emerald/common/marriage/marriages"
#define MARRIAGE_CHEAT          "people_who_wanted_to_be_logged"
#define MARRIAGE_LOG            "marriages"

private mapping marriages = ([ ]);

void
create_room()
{
    set_short("Marriage Manager");
    set_long("This is the marriage manager.  Here you may:\n" +
        "\twed <player> and <player> <band material>\n" +
        "\tdivorce <player>\n" +
        "\tlist <player>\n" +
        "\trestore <player>\n");

    setuid();
    seteuid(getuid());

    marriages = restore_map(MARRIAGE_SAVE);
}

int
query_married(string name)
{
    return marriages[lower_case(name)] != 0;
}

string
query_spouse(string name)
{
    string data = marriages[lower_case(name)];

    if (data != 0) {
        return explode(data, " ")[0];
    }
    else {
        return 0;
    }
}

string
query_material(string name)
{
    string data = marriages[lower_case(name)];

    if (data != 0) {
        return explode(data, " ")[1];
    }
    else {
        return 0;
    }
}

string
query_time(string name)
{
    string data = marriages[lower_case(name)];

    if (data != 0) {
        return explode(data, " ")[2];
    }
    else {
        return 0;
    }
}

int
wed(string name1, string name2, string matrl)
{
    name1 = lower_case(name1);
    name2 = lower_case(name2);
    
    if (marriages[name1] != 0)
        return 1;

    if (marriages[name2] != 0)
        return 2;
    
    marriages[name1] = name2 + " " + matrl + " " + time();
    marriages[name2] = name1 + " " + matrl + " " + time();
    
    log_file(MARRIAGE_LOG, ctime(time()) + " " + name1 + " married "
             + name2 + " " + matrl + "\n");

    save_map(marriages, MARRIAGE_SAVE);

    return 0;
}

int
ring_wed(string name1, string name2, string matrl)
{
    name1 = lower_case(name1);
    name2 = lower_case(name2);
    
    if (marriages[name1] != 0)
        return 1;

    marriages[name1] = name2 + " " + matrl + " " + time();
    
    log_file(MARRIAGE_LOG, ctime(time()) + " " + name1 + " RING married "
             + name2 + " " + matrl + "\n");

    save_map(marriages, MARRIAGE_SAVE);

    return 0;
}

int
divorce(string name)
{
    string data; 
    string spouse = "";

    name = lower_case(name);
    
    data = marriages[name];
    if (data == 0)
        return 1;

    spouse = explode(data, " ")[0];

    marriages = m_delete(marriages, name);
    marriages = m_delete(marriages, spouse);

    log_file(MARRIAGE_LOG, ctime(time()) + " " + name + " divorced "
             + spouse + "\n");
    
    save_map(marriages, MARRIAGE_SAVE);

    return 0;
}

int
remove_entry(string name)
{
    string data; 

    name = lower_case(name);
    
    data = marriages[name];
    if (data == 0)
        return 1;

    marriages = m_delete(marriages, name);

    log_file(MARRIAGE_LOG, ctime(time()) + " " + name + " was removed\n");
    
    save_map(marriages, MARRIAGE_SAVE);

    return 0;
}

static int
do_wed(string str)
{
    string who1, who2, material;
    int ret;

    if (!parse_command(str, ({}), "%w [and] %w %w", who1, who2, material))
    {
        notify_fail("Usage: " + query_verb() + " <player> and <player> <band material>.\n");
        return 0;
    }

    who1 = lower_case(who1);
    who2 = lower_case(who2);
    material = lower_case(material);

    if ((ret = wed(who1, who2, material)) == 1)
    {
        write(capitalize(who1) + " is already married!\n");
        return 1;
    }
   
    if (ret == 2)
    {
        write(capitalize(who2) + " is already married!\n");
        return 1;
    }

    log_file(MARRIAGE_LOG, capitalize(this_interactive()->query_real_name()) +
        "forced a wedding.\n");

    write("Ok.\n");
    return 1;
}

static int
do_divorce(string str)
{
    if (!strlen(str))
    {
         notify_fail("Usage: " + query_verb() + " <player>.\n");
         return 0;
    }
   
    str = lower_case(str);

    if (divorce(str))
    {
        write(capitalize(str) + " is not married!\n");
        return 1;
    }

    log_file(MARRIAGE_LOG, capitalize(this_interactive()->query_real_name()) +
        "forced a divorce.\n");

    write("Ok.\n");
    return 1;
}
 
void
desc_marriage(string who, string data)
{
    string time, spouse, material, *arr;

    arr = explode(data, " ");
    spouse = capitalize(arr[0]);
    material = arr[1];
    time = ctime(atoi(arr[2]));
    
    write(sprintf("Couple: %-12s %-12s  Time: " + time + "  Ring: %-8s\n",
        capitalize(who), spouse, material));
}

int
do_list(string str)   
{
    if (strlen(str))
    {
        if (!marriages[str])
	{
            write(capitalize(str) + " is not married.\n");
            return 1;
	}

        desc_marriage(str, marriages[str]);
        return 1;
    }

    notify_fail("Usage: " + query_verb() + " <player>.\n");
    return 0;
}

public int
do_restore(string str)
{
    string *arr;
    string data;
    object target, ring;

    if (!strlen(str))
    {
        notify_fail("Usage: " + query_verb() + " <player>\n");
        return 0;
    }

    if (!(target = find_player(str)))
    {
        write(capitalize(str) + " is not logged in.\n");
        return 1;
    }

    if (!(data = marriages[str]))
    {
        write(capitalize(str) + " is not married.\n");
        return 1;
    }

    arr = explode(data, " ");
    ring = clone_object("abc");
    ring->set_person(arr[0]);
    ring->set_material(arr[1]);
    ring->move(target, 1);
    write("Ok.\n");
}

void
init()
{
    ::init();

    add_action(do_wed, "wed");
    add_action(do_divorce, "divorce");
    add_action(do_list, "list");
    add_action(do_restore, "restore");
}
