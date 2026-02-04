#include "/d/Terel/include/Terel.h"
inherit WHITE + "guild/keep_room";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include "/secure/std.h"
#define TOME_SUFFIX    ".tome"

object door, door2;
public void
init()
{
    add_action("read", "read");
    ::init();
}

public void
create_terel_room()
{
    ::create_terel_room();
    set_short("the library of the keep");
    set_long("This is the library of the keep.\n\n\n");


    add_item("table", "A stained wooden table, used for reading.\n");
    add_item("shelves", "Made of sturdy wood, they house the tomes.\n");
    add_item("tomes", "They are secure in the shelves.\n");
    add_item("carvings", "They are strange demonic figures.\n");
    add_item("candles", "They are simple cables, providing " +
                          "light for the library.\n");
    add_item("stand", "It is a white stone stand, it holds a codex.\n");
    add_item("codex", "It is an ancient tome, resting on a stand.\n");
    add_cmd_item("codex", "read", "@@index");

    door = clone_object(WHITE + "guild/lib_door");
    door->move(TO);
    door2 = clone_object(WHITE + "guild/post_door2");
    door2->move(TO);
    
}

public string *
get_tomes()
{
    int i;
    string *tomes = ({ });
    string foo;
    
    seteuid(getuid());
    
    tomes = get_dir(WHITE + "archive/*" + TOME_SUFFIX);
    
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
    
    text = read_file(WHITE + "archive/" + tome + TOME_SUFFIX);
    return text;
}

public string
index()
{
    string *tomes = get_tomes();
    string indx = "You cannot read the index.";
    
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


    text = get_tome(subject);
    if (strlen(text) > 0) {
        write(text);
        say(QCTNAME(TP) + " reads from one of the ancient tomes.\n");
        return 1;
    }

    NF("There seems to be no tome on that subject.\n");
    return 0;
}
