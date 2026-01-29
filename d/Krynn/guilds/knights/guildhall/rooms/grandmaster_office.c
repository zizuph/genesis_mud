/**********************************************************************
 * - Added the following:                                           - *
 * -   #include "/d/Krynn/solamn/vin/std/no_scry_room.c"            - *
 * -   add_prop(ROOM_M_NO_SCRY, query_no_scry);                     - *
 * -                                                                - *
 * - Modified by Damaris@Genesis 03/2005                            - *
 **********************************************************************/

#include "../../guild.h"
#include <filter_funs.h>
#include <composite.h>
#include <stdproperties.h>

inherit IN_BASE;
#include "./std/no_scry_room.c"

#undef ADMIN
#define ADMIN KADM+"admin"
#define MAILREADER_ID   "_reader_"
#define SWORD ADMIN->query_conclave("sword")

string query_crest_str();

mapping crest = ([ ]);
mapping members = ([ ]);

string query_crest_str()
{
    string gm_name = C((ADMIN)->query_grandmaster());

    restore_object(CREST);
    if (member_array(gm_name, m_indexes(members)) < 0)
	return "a majestic kingfisher";

    return crest[members[gm_name]];
}


string long_desc()
{
    return "Before you sits an ancient, dark wooden desk which spans nearly "+
    "the width of the entire room. A great banner adorns the wall behind "+
    "the desk, covered with intricate emblems and crests. At the top of "+
    "the banner is a golden crown, while a gleaming sword and red rose "+
    "trail down either side of the banner. In the center you see a crest "+
    "depicting "+query_crest_str()+". The east wall is covered with a large map "+
    "of Solamnia, detailed with the boundaries and positions of the "+
    "territories now occupied by the dragonarmies. There is also a window "+
    "through which you may view the balcony outside this office.\n";
}


void
create_vin_room()
{
    add_prop(ROOM_M_NO_SCRY, query_no_scry);
    set_short("Office of the Grand Master");
    set_long("@@long_desc");

    clone_object(VOBJ + "gm_b")->move(TO);

    AI("window", "This window provides a view of the waiting room.\n"+
      "To see into it, try to <view room>.\n");

}


string
wait_desc()
{
    object *inv, *live;
    string room_to_load;
    int i;

    (VROOM + "greathall_balcony")->foo_bar_load_me();

    inv = all_inventory(find_object(VROOM + "greathall_balcony"));

    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	if (sizeof(live) > 0)
	    return ("In that room you can see " +
	      COMPOSITE_LIVE(live) + ".\n");
    }
    return ("At present, the room appears to be empty.\n");
}

public void
init()
{
    add_action("do_view", "view");
    set_alarm(0.1,0.0,"do_write_welcome",TP);
    ::init();
}

int
do_view(string str)
{
    if (!str || str == "room" || str =="waiting room")
    {
	TP->catch_msg(wait_desc());
	return 1;
    }
    NF("View what?\n");
    return 0;
}


void
do_write_welcome(object who)
{
    object mr;
    string ro = (ADMIN)->query_conclave("rose"),
    sw = (ADMIN)->query_conclave("sword"),
    cr = (ADMIN)->query_conclave("crown"),
    gm = C((ADMIN)->query_granmaster());
    string *conclave = ({ });

    int a = (ADMIN)->check_can_perform_command(who);
    object p = P(CONCLAVE_OBJ, who);
    mixed c = !p;

    if (c && a)
    {
	who->catch_msg("In this room you have access to the conclave " +
	  "command object. Examine it to see your commands.\n");
	clone_object(CONCLAVE_CMD)->move(who,1);

	if (ro && stringp(ro) && ro != "")
	    conclave += ({ ro });
	if (sw && stringp(sw) && sw != "")
	    conclave += ({ sw });
	if (cr && stringp(cr) && cr != "")
	    conclave += ({ cr });
	if (gm && stringp(gm) && gm != "")
	    conclave += ({ gm });
    }

    if (a && !P(MAILREADER_ID, who))
    {
	mr = clone_object("/secure/mail_reader");
	if (conclave)
	    mr->set_alias("conclave", conclave);
	if (GUILDMASTERS)
	    mr->set_alias("guildmaster", GUILDMASTERS);
	mr->move(who, 1);
    }
}

void
leave_inv(object ob, object to)
{
    object reader;
    ::leave_inv(ob, to);

    reader = present(MAILREADER_ID, ob);
    if (reader)
	reader->remove_object();

    reader = present(CONCLAVE_OBJ, ob);
    if (reader)
        reader->remove_object();
}
