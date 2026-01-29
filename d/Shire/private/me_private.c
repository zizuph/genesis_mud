#include "/d/Shire/sys/defs.h"
#include <std.h>
#include <language.h>

inherit SHIRE_ROOM;

#define ME_DOMAINS ({"Gondor", "Shire"})
#define TRUSTED ({"igneous"})

void
create_shire_room()
{
    set_short("Middle-Earth Private Discussions Room");
    set_long("This is "+LANG_THESHORT(TO)+" used by the "+
      "mighty immortals of Middle-Earth to discuss private matters of the "+
      "domains which make of the lands of Middle-Earth.  "+
      "The walls of the room are completely barren with the exception "+
      "of a few tapestries.\n");

    add_item(({"tapestry","tapestries","wall","walls"}),
      "The tapestries cover the east and west walls.\n");

    add_item(({"west wall","western tapestry"}),
      "The tapestry is covered with the emblem of the White Tree of Gondor.\n");

    add_item(({"east wall","eastern tapestry"}),
      "The tapestry is covered with the emblem of the Red eye of Mordor.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(SHIRE_DIR + "workroom", "south");

    reset_shire_room();
}

nomask private int query_prevent_snoop() {return 1;}

void
reset_shire_room()
{
    if (!present("_ME_private_board", TO))
    {
	setuid(); seteuid(getuid());
	clone_object("/d/Shire/private/board")->move(TO,1);
    }
}

void
enter_inv(object ob, object from)
{
    string dom, pre;
    int rank;

    ::enter_inv(ob,from);
    if (!interactive(ob))
	return;

    rank = SECURITY->query_wiz_rank(ob->query_real_name());
    pre =  SECURITY->query_wiz_pretitle(ob);

    if (rank >= WIZ_ARCH)
    {
	// Like we need to inflate the egos of the arches even more ;-)
	ob->catch_tell("Welcome to "+LANG_THESHORT(TO)+", oh great "+
	  pre +" of Genesis.\n");
	return;
    }
    if (member_array(dom = SECURITY->query_wiz_dom(ob->query_real_name()),
	ME_DOMAINS) != -1)
    {
	if (rank == WIZ_NORMAL)
	    pre = "Wizard";
	else if (rank == WIZ_MAGE)
	    pre = "Honourable wizard";

	ob->catch_tell("Welcome to "+LANG_THESHORT(TO)+", "+
	  pre + " of "+ (dom == "Shire" ? "the Shire" : dom) + ".\n");
	return;
    }

    if (member_array(ob->query_real_name(), TRUSTED) != -1)
    {
	ob->catch_tell("Welcome to "+LANG_THESHORT(TO)+", "+
	  " trusted Wizard of "+ dom +".\n");
	return;
    }
    // Not an arch or a ME wizard so they aren't allowed here.
    ob->catch_tell("You are not allowed in there.\n");
    ob->move(from, 1);
}
