/*
 * /d/Gondor/common/dwarf_guild/bear/showcase.c
 *
 * The cabinet for the bears, with display case for their honey.
 *
 * Copyright (C) Mercade - 1 January 2006
 */

inherit "/std/container";

#include "bear.h";
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

string
long_description()
{
    int num = BEAR_HOME->query_num_honeys();
    string text = "The antique oak show case is narrow and tall. The upper part of " +
        "the cabinet has glass doors and is meant for displaying artifacts " +
        "or other precious possessions such as a honey collection. The lower " +
        "part of the cabinet is meant for hanging clothes.";

    text += (num ? " The honey collection contains " + LANG_WNUM(num) +
        " specimen of honey.\n" : " The honey collection is empty.\n");

    if (IN_ARRAY(this_player()->query_real_name(), ({ "mercade", "stern" }) ))
    {
        text += "Commands: addhoney, listhoney, removehoney\n";
    }
    return text;
}

string
honey_collection_description()
{
    string *honeys = BEAR_HOME->query_honeys();
    int    num = sizeof(honeys);
    string text = "The upper part of the antique oak show case shows " +
        "precious possessions safely behind glass doors.";
    
    text += (num ? " The honey collection contains " + LANG_WNUM(num) +
        " specimen of honey:\n - " + implode(honeys, "\n - ") :
        " The honey collection is empty.");

    return text + "\n";
}

void
create_container()
{
    set_name("showcase");
    add_name(SHOWCASE_ID);
    add_name("case");
    set_pname("showcases");
    set_adj("antique");
    add_adj("oak");
    add_adj("show");
    set_short("antique oak showcase");
    set_pshort("antique oak showcase");
    set_long(long_description);

    add_item( ({ "collection", "honey collection" }) ,
        honey_collection_description);

    set_no_show_composite(1);

    add_prop(CONT_I_CLOSED,          1);
    add_prop(CONT_I_MAX_VOLUME, 260000);
    add_prop(CONT_I_MAX_WEIGHT, 260000);
    add_prop(CONT_I_VOLUME,      60000);
    add_prop(CONT_I_WEIGHT,     100000);

    add_prop(OBJ_I_NO_GET, 1);

    setuid();
    seteuid(getuid());
}

int
add_honey(string str)
{
    if (!strlen(str))
    {
        notify_fail("Syntax: addhoney <honey>\n");
        return 0;
    }

    BEAR_HOME->add_honey(str);
    write("Added: " + str + "\n");
    return 1;
}

int
list_honey(string str)
{
    string *honeys = BEAR_HOME->query_honeys();
    int found;

    if (!strlen(str))
    {
        notify_fail("Syntax: listhoney <pattern>     (*asterisks added automagically*)\n");
        return 0;
    }

    str = "*" + str + "*";
    foreach(string honey: honeys)
    {
        if (wildmatch(str, lower_case(honey)))
        {
            write(" - " + honey + "\n");
            found = 1;
        }
    }
    if (!found)
    {
        write("Nothing found with pattern " + str + "\n");
    }
    return 1;
}

int
remove_honey(string str)
{
    if (!strlen(str))
    {
        notify_fail("Syntax: removehoney <honey>\n");
        return 0;
    }

    BEAR_HOME->remove_honey(str);
    write("Removed: " + str + "\n");
    return 1;
}

void
init()
{
    ::init();
    
    add_action(add_honey, "addhoney");
    add_action(list_honey, "listhoney");
    add_action(remove_honey, "removehoney");
}
