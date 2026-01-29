/*
 * clan_administration.c
 *
 * This room is for the general administration of the clans of
 * Khalakhor by it's wizards and arches.
 *
 * Khail - May 4/97
 */
#pragma strict_types
#include <std.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";

public int do_read(string str);
public int get_clan_editor(string str);
public int get_sept_editor(string str);

public string
exa_clan_roster()
{
    int i,
        k;
    string path,
           ret;
    string *arr,
           *names;

    path = "/d/Khalakhor/common/clans/saves/";
    names = ({});

    for (i = 0; i < strlen(ALPHABET); i++)
    {
        arr = get_dir(path + ALPHABET[i..i] + "/*.o");
        for (k = 0; k < sizeof(arr); k++)
        {
            names += ({capitalize(arr[k][0..strlen(arr[k])-3])});
        }
    }

    ret = "Clans of Khalakhor:\n";
    ret += sprintf("%-15@s\n", names);
    return ret + "\n";
}

public string
exa_sept_roster()
{
    int i,
        k;
    string path,
           ret;
    string *arr,
           *names;

    path = "/d/Khalakhor/common/septs/saves/";
    names = ({});

    for (i = 0; i < strlen(ALPHABET); i++)
    {
        arr = get_dir(path + ALPHABET[i..i] + "/*.o");
        for (k = 0; k < sizeof(arr); k++)
        {
            names += ({capitalize(arr[k][0..strlen(arr[k])-3])});
        }
    }

    ret = "Septs of Khalakhor:\n";
    ret += sprintf("%-15@s\n", names);
    return ret + "\n";
}
         
public void
create_khalakhor_room()
{
    set_short("Khalakhor clan administration");
    set_long("This is the Khalakhor clan administration room. From " +
        "here, arches and Khalakhor wizards can perform the various " +
        "tasks required to keep track of the different clans and " +
        "septs of Khalakhor. Two large rosters contain lists of " +
        "all clans and all septs in Khalakhor. A sign on the wall " +
        "has a list of available commands.\n");
    add_item(({"clan roster", "clans roster", "clans"}),
        VBFC_ME("exa_clan_roster"));
    add_item(({"sept roster", "septs roster", "septs"}),
        VBFC_ME("exa_sept_roster"));
    add_item(({"sign"}), "You can read it.\n");
}

public nomask int
has_authority(object who)
{
    string name;

    name = who->query_real_name();

    if (SECURITY->query_wiz_dom(name) == "Khalakhor")
        return 1;

    if (SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
        return 1;

    return 0;
}

public void
init()
{
    ::init();
    add_action(do_read, "read");
    add_action(get_clan_editor, "clan_editor");
    add_action(get_sept_editor, "sept_editor");
}

public int
do_read(string str)
{
    if (!str || !strlen(str))
    {
        NF("Read what, the sign?\n");
        return 0;
    }

    if (!parse_command(str, TP, "[the] 'sign'"))
    {
        NF("Read what, the sign?\n");
        return 0;
    }

    write("In the clan administration room, you can use these " +
        "commands:\n");
    write("clan_editor - This command will provide you with the\n" +
        "              clan editor, with which you can create new\n" +
        "              or edit information on existing clans.\n");
    write("sept_editor - This command will provide you with the\n" +
        "              sept editor, with which you can create new\n" +
        "              or edit information on existing septs.\n");
    return 1;
}

public int
get_clan_editor(string str)
{
    if (!has_authority(TI))
    {
        write("You have no business with a clan editor.\n");
        return 1;
    }

    reset_euid();
    write("Cloning clan editor.\n");
    clone_object("/d/Khalakhor/common/clans/clan_editor")->move(TI);
    return 1;
}

public int
get_sept_editor(string str)
{
    if (!has_authority(TI))
    {
        write("You have no business with a sept editor.\n");
        return 1;
    }

    reset_euid();
    write("Cloning sept editor.\n");
    clone_object("/d/Khalakhor/common/septs/sept_editor")->move(TI);
    return 1;
}
