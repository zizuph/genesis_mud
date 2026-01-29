/*
 * clan_editor.c
 *
 * Just an object that can be used to create info on a new
 * clan, or edit info on an existing clan.
 *
 * Khail - May 4/97
 */
#pragma strict_types

#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include <composite.h>
#include <std.h>

#define CLAN_SAVES(x) "/d/Khalakhor/common/clans/saves/"+x[0..0]+"/"+x

inherit "/std/object";

string clan,
       *septs,
       race,
       alignment,
       region;
static int clanclear_confirm,
           clanreset_confirm,
           clandelete_confirm;

public void create_object();
public void init();
public int clan_help(string str);
public int clan_exists(string str);
public int clan_create(string str);
public int clan_edit(string str);
public int clan_race(string str);
public int clan_alignment(string str);
public int clan_region(string str);
public int clan_septs(string str);
public int clan_delete(string str);
public int clan_clear(string str);
public int clan_review(string str);
public int clan_reset(string str);
public int clan_close(string str);

public void
create_object()
{
    set_name("clan editor");
    add_name("editor");
    add_name("claneditor");
    set_short("clan editor");
    set_long("This is the clan editor. It is used for the creation " +
        "of new clans, or the editing of existing clans. Use " +
        "'clanhelp' for instructions.\n");

    add_prop(OBJ_I_NO_GIVE, 1);

    clan = "";
    septs = ({});
    alignment = "";
    race = "";
    region = "";   
}

public void
init()
{
    ::init();
  /* Only add commands to people carrying the editor. */
    if (TP != environment(TO))
        return;
  /* Only add commands to Khalakhor wizards or arches. */
    if (SECURITY->query_wiz_rank(TI->query_real_name()) < WIZ_NORMAL &&
        SECURITY->query_wiz_dom(TI->query_real_name()) != "Khalakhor")
        return;

    add_action(clan_create, "clancreate");
    add_action(clan_edit, "clanedit");
    add_action(clan_race, "clanrace");
    add_action(clan_septs, "clansept");
    add_action(clan_alignment, "clanalignment");
    add_action(clan_region, "clanregion");
    add_action(clan_clear, "clanclear");
    add_action(clan_delete, "clandelete");
    add_action(clan_review, "clanreview");
    add_action(clan_reset, "clanreset");
    add_action(clan_close, "clanclose");
    add_action(clan_help, "clanhelp");
}

public int
clan_help(string str)
{
    write("The following commands are available via the clan " +
        "editor.\n");
    write("clancreate <name> -     Create a clan.\n" +
        "clanedit <name> -       Edit an existing clan.\n" +
        "clanrace <race> -       Set the dominant race of current clan.\n" +
        "clanalignment <align> - Set the dominant alignment of the\n" +
        "                        current clan. I.e. 'good', 'very\n" +
        "                        evil', etc.\n" +
        "clanregion <region> -   Set the general region a clan is\n" +
        "                        located in. I.e. 'central highlands',\n" +
        "                        'lower southeast speir'.\n" +
        "clansept <sept> -       Add a sept (family name) which is\n" +
        "                        allied to the clan.\n" +
        "clanclear -             Clear all fields of the current\n" +
        "                        clan (except the clan name itself),\n" +
        "                        both in the editor and the save file.\n" +
        "clanreset -             Similar to clanclear, except it\n" +
        "                        clears only the editor, not the\n" +
        "                        save file, and also clears the\n" +
        "                        clan name.\n" +
        "clandelete -            Completely remove this clan,\n" +
        "                        including data file.\n" +
        "clanclose -             Completes writing clan data to file\n" +
        "                        and resets all fields.\n" +
        "clanreview - Print existing info on current clan.\n");
    write("The race, alignment, region, and sept fields will also " +
        "take the argument 'clear' to clear that particular field.\n");
    write("Clan creation and deletions are logged.\n");
    return 1;
}

public int
clan_exists(string str)
{
    if (!str || !strlen(str))
        return 0;

    str = lower_case(str);

    if (file_size(CLAN_SAVES(str) + ".o") > -1)
        return 1;
    else
        return 0;
}

public int
clan_create(string str)
{
    if (!str || !strlen(str))
    {
        NF("You must specify a clan name.\n");
        return 0;
    }

    str = lower_case(str);

    if (str == "clear")
    {
        NF("You cannot clear a clan name, use 'clandelete' " +
           "or 'clanreset' instead.\n");
        return 0;
    }

    if (clan_exists(str))
    {
        write("Clan " + capitalize(str) + " already exists.\n");
        return 1;
    }

    clan = str;
    reset_euid();
    save_object(CLAN_SAVES(str));
    write("Created Clan " + capitalize(str) + ".\n");
    log_file("clanadmin/clan_create", TI->query_real_name() + 
        " created clan " + clan + " on " + ctime(time()) + ".\n");
    return 1;
}

public int
clan_edit(string str)
{
    if (!str || !strlen(str))
    {
        NF("You must specify a clan name.\n");
        return 0;
    }

    str = lower_case(str);

    reset_euid();
    if (!restore_object(CLAN_SAVES(str)))
    {
        write("Clan " + capitalize(str) + " does not exist.\n");
        return 1;
    }
    else
        write("Restored Clan " + capitalize(str) + ".\n");
    return 1;
}

public int
clan_race(string str)
{
    if (!clan || !strlen(clan))
    {
        NF("You must have a clan open for editing first.\n");
        return 0;
    }

    if (!str || !strlen(str))
    {
        NF("You must specify a dominant race.\n");
        return 0;
    }

    race = lower_case(str);

    if (race == "clear")
    {
        write("Clearing the race of clan " + capitalize(clan) +
            ".\n");
        race = "";
    }
    else
    {
        write("Setting dominant race of clan " + capitalize(clan) + 
            " to " + race + ".\n");
    }

    reset_euid();
    save_object(CLAN_SAVES(clan));
    return 1;
}

public int
clan_alignment(string str)
{
    if (!clan || !strlen(clan))
    {
        NF("You must have a clan open for editing first.\n");
        return 0;
    }

    if (!str || !strlen(str))
    {
        NF("You must specify a dominant alignment.\n");
        return 0;
    }

    alignment = lower_case(str);

    if (alignment == "clear")
    {
        write("Clearing the alignment of clan " + capitalize(clan) +
            ".\n");
        alignment = "";
    }
    else
    {
        write("Setting dominant alignment of clan " + capitalize(clan) + 
            " to " + alignment + ".\n");
    }

    reset_euid();
    save_object(CLAN_SAVES(clan));
    return 1;
}

public int
clan_septs(string str)
{
    string temp;

    if (!clan || !strlen(clan))
    {
        NF("You must have a clan open for editing first.\n");
        return 0;
    }

    if (!str || !strlen(str))
    {
        NF("You must specify a sept.\n");
        return 0;
    }

    temp = lower_case(str);
    septs += ({temp});

    if (temp == "clear")
    {
        write("Clearing the septs of clan " + capitalize(clan) +
            ".\n");
        septs = ({});
    }
    else
    {
        write("Adding " + capitalize(temp) + " as a sept sworn to " +
            "clan " + capitalize(clan) + ".\n");
    }

    reset_euid();
    save_object(CLAN_SAVES(clan));
    return 1;
}

public int
clan_region(string str)
{
    if (!clan || !strlen(clan))
    {
        NF("You must have a clan open for editing first.\n");
        return 0;
    }

    if (!str || !strlen(str))
    {
        NF("You must specify a general region.\n");
        return 0;
    }

    region = lower_case(str);

    if (region == "clear")
    {
        write("Clearing the region of clan " + capitalize(clan) +
            ".\n");
        return 1;
    }
    else
    {
        write("Setting dominant general region of clan " +
            capitalize(clan) + " to " + region + ".\n");
    }

    reset_euid();
    save_object(CLAN_SAVES(clan));
    return 1;
}

public int
clan_clear(string str)
{
    if (!clan || !strlen(clan))
    {
        NF("You must create or edit a clan before using this " +
            "command.\n");
        return 0;
    }

    if (!clanclear_confirm)
    {
        write("Are you sure you want to clear all info on clan " +
            capitalize(clan) + "? Use clanclear again to confirm.\n");
        clanclear_confirm = 1;
        return 1;
    }

    write("Clearing info on clan " + capitalize(clan) + ".\n");
    clanclear_confirm = 0;
    race = "";
    alignment = "";
    region = "";
    septs = ({});
    reset_euid();
    save_object(CLAN_SAVES(clan));
    return 1;
}

public int
clan_reset(string str)
{
    if (!clan || !strlen(clan))
    {
        NF("You must create or edit a clan before using this " +
            "command.\n");
        return 0;
    }

    if (!clanreset_confirm)
    {
        write("Are you sure you want to reset all info on clan " +
            capitalize(clan) + "? Use clanreset again to confirm.\n");
        clanreset_confirm = 1;
        return 1;
    }

    write("Resetting info on clan " + capitalize(clan) + ".\n");
    clanreset_confirm = 0;
    clan = "";
    race = "";
    alignment = "";
    region = "";
    septs = ({});
    return 1;
}

public int
clan_delete(string str)
{
    if (!clan || !strlen(clan))
    {
        NF("You must create or edit a clan before using this " +
            "command.\n");
        return 0;
    }

    if (!clandelete_confirm)
    {
        write("Are you sure you want to delete all info on clan " +
            capitalize(clan) + "? Use clandelete again to " +
            "confirm.\n");
        clandelete_confirm = 1;
        return 1;
    }

    write("Deleting file on clan " + capitalize(clan) + ".\n");
    reset_euid();
    if (!rm(CLAN_SAVES(clan) + ".o"))
    {
        write("Could not delete " + CLAN_SAVES(clan) + ".o for " +
            "some reason.\n");
        return 1;
    }
    log_file("clanadmin/clan_delete", TI->query_real_name() +
        " deleted clan " + clan + " on " + ctime(time()) + ".\n");
    clandelete_confirm = 0;
    clan = "";
    septs = ({});
    race = "";
    region = "";
    alignment = "";
    return 1;
}

public int
clan_review(string str)
{
    if (!clan || !strlen(clan))
    {
        NF("You must create or edit a clan before using this " +
            "command.\n");
        return 0;
    }

    write("Info on clan " + capitalize(clan) + ":\n");
    write("Race: " + race + "\n");
    write("Alignment: " + alignment + "\n");
    write("Region: " + region + "\n");
    write("Septs: " + COMPOSITE_WORDS(septs) + "\n");
    return 1;
}

public int
clan_close(string str)
{
    if (!clan || !strlen(clan))
    {
        NF("You must create or edit a clan before using this " +
            "command.\n");
        return 0;
    }

    write("Completed writing to clan " + capitalize(clan) + ".\n");
    clan = "";
    septs = ({});
    region = "";
    race = "";
    alignment = "";
    return 1;
}
