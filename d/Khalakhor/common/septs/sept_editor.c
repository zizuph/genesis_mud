/*
 * sept_editor.c
 *
 * Just an object that can be used to create info on a new
 * sept, or edit info on an existing sept.
 *
 * Khail - May 4/97
 */
#pragma strict_types

#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include <composite.h>
#include <std.h>

#define SEPT_SAVES(x) "/d/Khalakhor/common/septs/saves/"+x[0..0]+"/"+x

inherit "/std/object";

string sept,
       clan,
       race,
       alignment,
       region;
static int septclear_confirm,
           septreset_confirm,
           septdelete_confirm;

public void create_object();
public void init();
public int sept_help(string str);
public int sept_exists(string str);
public int sept_create(string str);
public int sept_edit(string str);
public int sept_race(string str);
public int sept_alignment(string str);
public int sept_region(string str);
public int sept_clan(string str);
public int sept_delete(string str);
public int sept_clear(string str);
public int sept_reset(string str);
public int sept_review(string str);
public int sept_close(string str);

public void
create_object()
{
    set_name("sept editor");
    add_name("septeditor");
    set_short("sept editor");
    set_long("This is the sept editor. It is used for the creation " +
        "of new septs, or the editing of existing septs. Use " +
        "'septhelp' for information on available commands.\n");

    add_prop(OBJ_I_NO_GIVE, 1);

    sept = "";
    clan = "";
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

    add_action(sept_create, "septcreate");
    add_action(sept_edit, "septedit");
    add_action(sept_race, "septrace");
    add_action(sept_clan, "septclan");
    add_action(sept_alignment, "septalignment");
    add_action(sept_region, "septregion");
    add_action(sept_clear, "septclear");
    add_action(sept_delete, "septdelete");
    add_action(sept_review, "septreview");
    add_action(sept_reset, "septreset");
    add_action(sept_close, "septclose");
    add_action(sept_help, "septhelp");
}

public int
sept_help(string str)
{
    write("The following commands are available via the sept " +
        "editor.\n\n");
    write("septcreate <name> -     Create a sept.\n" +
        "septedit <name> -       Edit an existing sept.\n" +
        "septrace <race> -       Set the dominant race of current\n" +
        "                        sept.\n" +
        "septalignment <align> - Set the dominant alignment of the\n" +
        "                        current sept. I.e. 'good', 'very\n" +
        "                        evil', etc.\n" +
        "septregion <region> -   Set the general region a sept is\n" +
        "                        located in. I.e. 'central highlands',\n" +
        "                        'lower southeast speir'.\n" +
        "septclan <clan> -       Set the clan to which this sept is\n" +
        "                        sworn.\n" +
        "septclear -             Clear all fields of the current\n" +
        "                        sept (except the sept name itself).\n" +
        "septreset -             Similar to septclear, except it\n" +
        "                        clears only the editor, not the\n" +
        "                        save file, and also clears the\n" +
        "                        sept name.\n" +
        "septclose -             Completes writing sept data to file\n" +
        "                        and resets all fields.\n" +
        "septdelete -            Completely remove this sept,\n" +
        "                        including data file.\n" +
        "septreview -            Print existing info on current sept.\n");
    write("\nThe race, alignment, region, and sept fields will also " +
        "take the argument 'clear' to clear that particular field.\n");
    write("Sept creation and deletions are logged.\n");
    return 1;
}

public int
sept_exists(string str)
{
    if (!str || !strlen(str))
        return 0;

    str = lower_case(str);

    if (file_size(SEPT_SAVES(str) + ".o") > -1)
        return 1;
    else
        return 0;
}

public int
sept_create(string str)
{
    if (!str || !strlen(str))
    {
        NF("You must specify a sept name.\n");
        return 0;
    }

    str = lower_case(str);

    if (str == "clear")
    {
        NF("You cannot clear a sept name, use 'septdelete' instead.\n");
        return 0;
    }

    if (sept_exists(str))
    {
        write("Sept " + capitalize(str) + " already exists.\n");
        return 1;
    }

    sept = str;
    reset_euid();
    save_object(SEPT_SAVES(str));
    write("Created Sept " + capitalize(str) + ".\n");
    log_file("clanadmin/sept_create", TI->query_real_name() +
        " created sept " + sept + " on " + ctime(time()) + ".\n");
    return 1;
}

public int
sept_edit(string str)
{
    if (!str || !strlen(str))
    {
        NF("You must specify a sept name.\n");
        return 0;
    }

    str = lower_case(str);

    reset_euid();
    if (!restore_object(SEPT_SAVES(str)))
    {
        write("Sept " + capitalize(str) + " does not exist.\n");
        return 1;
    }
    else
        write("Restored Sept " + capitalize(str) + ".\n");
    return 1;
}

public int
sept_race(string str)
{
    if (!sept || !strlen(sept))
    {
        NF("You must have a sept open for editing first.\n");
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
        write("Clearing the race of sept " + capitalize(sept) +
            ".\n");
        race = "";
    }
    else
    {
        write("Setting dominant race of sept " + capitalize(sept) + 
            " to " + race + ".\n");
    }

    reset_euid();
    save_object(SEPT_SAVES(sept));
    return 1;
}

public int
sept_alignment(string str)
{
    if (!sept || !strlen(sept))
    {
        NF("You must have a sept open for editing first.\n");
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
        write("Clearing the alignment of sept " + capitalize(sept) +
            ".\n");
        alignment = "";
    }
    else
    {
        write("Setting dominant alignment of sept " + capitalize(sept) + 
            " to " + alignment + ".\n");
    }

    reset_euid();
    save_object(SEPT_SAVES(sept));
    return 1;
}

public int
sept_clan(string str)
{
    string temp;

    if (!sept || !strlen(sept))
    {
        NF("You must have a sept open for editing first.\n");
        return 0;
    }

    if (!str || !strlen(str))
    {
        NF("You must specify a sept.\n");
        return 0;
    }

    clan = lower_case(str);

    if (clan == "clear")
    {
        write("Clearing the clan of sept " + capitalize(sept) +
            ".\n");
        clan = "";
    }
    else
    {
        write("Setting clan " + capitalize(clan) + " as the sworn " +
            "clan of " + capitalize(sept) + ".\n");
    }

    reset_euid();
    save_object(SEPT_SAVES(sept));
    return 1;
}

public int
sept_region(string str)
{
    if (!sept || !strlen(sept))
    {
        NF("You must have a sept open for editing first.\n");
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
        write("Clearing the region of sept " + capitalize(sept) +
            ".\n");
        return 1;
    }
    else
    {
        write("Setting dominant general region of sept " +
            capitalize(sept) + " to " + region + ".\n");
    }

    reset_euid();
    save_object(SEPT_SAVES(sept));
    return 1;
}

public int
sept_clear(string str)
{
    if (!sept || !strlen(sept))
    {
        NF("You must create or edit a sept before using this " +
            "command.\n");
        return 0;
    }

    if (!septclear_confirm)
    {
        write("Are you sure you want to clear all info on sept " +
            capitalize(sept) + "? Use septclear again to confirm.\n");
        septclear_confirm = 1;
        return 1;
    }

    write("Clearing info on sept " + capitalize(sept) + ".\n");
    septclear_confirm = 0;
    race = "";
    alignment = "";
    region = "";
    clan = "";
    reset_euid();
    save_object(SEPT_SAVES(sept));
    return 1;
}

public int
sept_reset(string str)
{
    if (!sept || !strlen(sept))
    {
        NF("You must create or edit a sept before using this " +
            "command.\n");
        return 0;
    }

    if (!septreset_confirm)
    {
        write("Are you sure you want to reset all info on sept " +
            capitalize(sept) + "? Use septreset again to confirm.\n");
        septreset_confirm = 1;
        return 1;
    }

    write("Resetting info on sept " + capitalize(sept) + ".\n");
    septreset_confirm = 0;
    sept = "";
    clan = "";
    race = "";
    alignment = "";
    region = "";
    return 1;
}

public int
sept_delete(string str)
{
    if (!sept || !strlen(sept))
    {
        NF("You must create or edit a sept before using this " +
            "command.\n");
        return 0;
    }

    if (!septdelete_confirm)
    {
        write("Are you sure you want to delete all info on sept " +
            capitalize(sept) + "? Use septdelete again to " +
            "confirm.\n");
        septdelete_confirm = 1;
        return 1;
    }

    write("Deleting file on sept " + capitalize(sept) + ".\n");
    reset_euid();
    if (!rm(SEPT_SAVES(sept) + ".o"))
    {
        write("Could not delete " + SEPT_SAVES(sept) + ".o for " +
            "some reason.\n");
        return 1;
    }
    log_file("clanadmin/sept_delete", TI->query_real_name() +
        " deleted sept " + sept + " on " + ctime(time()) + ".\n");
    septdelete_confirm = 0;
    sept = "";
    clan = "";
    race = "";
    region = "";
    alignment = "";
    return 1;
}

public int
sept_review(string str)
{
    if (!sept || !strlen(sept))
    {
        NF("You must create or edit a sept before using this " +
            "command.\n");
        return 0;
    }

    write("Info on sept " + capitalize(sept) + ":\n");
    write("Race: " + race + "\n");
    write("Alignment: " + alignment + "\n");
    write("Region: " + region + "\n");
    write("Clan: " + clan + "\n");
    return 1;
}

public int
sept_close(string str)
{
    if (!sept || !strlen(sept))
    {
        NF("You must create or edit a sept before using this " +
            "command.\n");
        return 0;
    }

    write("Completed writing to sept " + capitalize(sept) + ".\n");
    reset_euid();
    save_object(SEPT_SAVES(sept));
    clan = "";
    sept = "";
    region = "";
    race = "";
    alignment = "";
    return 1;
}
