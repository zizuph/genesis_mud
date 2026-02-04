/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/room";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include "/secure/std.h"

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP             this_player()
#define TO             this_object()
#define NF(xx)         notify_fail(xx)
#define TOME_SUFFIX    ".tome"

public void
init()
{
    add_action("read", "read");
    ::init();
}

public void
create_room()
{
    set_short("Archive");
    set_long(
       "This ancient chamber is lined with shelves, upon which are many "
     + "arcane and dusty tomes. The arched ceiling is supported by carved "
     + "wooden arches, from which hang small silver lanthorns. In the "
     + "center of the chamber is a small table and a stand holding an old "
     + "open codex.\n");

    add_exit(GUILD_DIR + "library", "out", 0);
    add_item("table", "A dark wooden table, used for reading.\n");
    add_item("shelves", "Made of dark wood, they house the tomes.\n");
    add_item("tomes", "They are secure in the shelves.\n");
    add_item("arches", "Supporting the ceiling, these carved wooden " +
                       "arches bring beauty to this dark place.\n");
    add_item("carvings", "They are strange demonic figures.\n");
    add_item("lanthorns", "They are simple silver lanthorns, providing " +
                          "light for the archives.\n");
    add_item("stand", "It is a black marble stand, it holds a codex.\n");
    add_item("codex", "It is an ancient tome, resting on a stand.\n");
    add_cmd_item("codex", "read", "@@index");
}

public string *
get_tomes()
{
    int i;
    string *tomes = ({ });
    string foo;
    
    seteuid(getuid());
    
    tomes = get_dir(GUILD_DIR + "archive/*" + TOME_SUFFIX);
    
    for (i=0; i<sizeof(tomes); i++) {
        sscanf(tomes[i], "%s.tome", foo);
        tomes[i] = foo;
    }
    
    return tomes;
}

public string
get_tome(string tome)
{
    string *tomes = get_tomes();
    string text = "";
    int i;
    
    if (sizeof(tomes) == 0) return text;
    
    i = member_array(tome, tomes);
    
    if (i < 0) return text;
    
    seteuid(getuid());
    
    text = read_file(GUILD_DIR + "archive/" + tome + TOME_SUFFIX);
    return text;
}

public string
index()
{
    string *tomes = get_tomes();
    string indx = "You cannot read the index.";
    
    if (!MEMBER(TP)) return (indx + "\n");
    
    if (sizeof(tomes) == 0) {
        indx = "There are no tomes here at the moment.";
    } else if (sizeof(tomes) == 1) {
        indx = "There is a tome on the following subject: " +
               tomes[0] + ".";
    } else {
        indx = "There are tomes on the following subjects: " +
               COMPOSITE_WORDS(tomes) + ".";
    }
    return (indx + "\n");
}

public int
read(string str)
{
    string subject, text;
    
    NF("Read tome on what?\n");
    if (!str) return 0;

    if (sscanf(str, "tome on %s", subject) != 1 &&
        sscanf(str, "tome about %s", subject) != 1) return 0;

    if (TP->query_skill(SS_LANGUAGE) < 15 || !MEMBER(TP)) {
        write("Your linguistic skills are not strong enough.\n");
        return 1;
    }

    text = get_tome(subject);
    if (strlen(text) > 0) {
        write(text);
        say(QCTNAME(TP) + " reads from one of the ancient tomes.\n");
        return 1;
    }

    NF("There seems to be no tome on that subject.\n");
    return 0;
}
