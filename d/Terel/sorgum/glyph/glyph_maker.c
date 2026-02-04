#include "/d/Terel/include/Terel.h"

inherit STDOBJECT;

#define GLYPH_FILE SORGUM_DIR + "glyph/glyph"

public void
init()
{
    add_action("do_scrawl", "scrawl");
    ::init();
}

public void
create_object()
{
    set_name("glyph maker");
    set_long("A prototype of a glyph maker.\n");
    set_short("glyph maker");
}

public int
do_scrawl(string str)
{
    string what, where;
    mixed exits;
    object room;
    int index;
    object glyph;
    
    NF("Scrawl what?\n");

    if (!strlen(str))
	return 0;

    if (sscanf(str, "glyph on %s exit", where) != 1)
	return 0;

    room = ETP;

    exits = room->query_exit();

    if ((index = member_array(where, exits)) == -1) {
	NF("This room does not have an exit named " + where + "\n");
	return 0;
    }

    if ((index % 3) != 1) {
	NF("You can not scrawl a glyph there. (index = " + index + "\n");
	return 0;
    }

    index--;
    
    if (strlen(exits[index+2])) {
	NF("There is already some kind of glyph on the " + where + " exit\n");
	return 0;
    }

    glyph = clone_object(GLYPH_FILE);
    glyph->move(room);
    glyph->set_no_show();
    
    room->remove_exit(where);
    room->add_exit(exits[index],where, "@@trigger:" + file_name(glyph) + "@@");

    glyph->set_glyph(where, room);
    glyph->set_owner(TP);
    
    TP->catch_msg("You scrawled a glyph on the " + where + " exit.\n");
    return 1;
    

    
}

