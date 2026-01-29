/*
* Post Office in the City of Palanthas.
* From Rastlin's 950523 Balifor PO.
*
* Mortis 11.2005 
*
* Modification History:
*   - Changed to support the thematic idea that the Necromancers have placed
*     invisible spirits here that allow this Post Office to be used by
*     their own guild in a way that only they can see. (Gorboth, Nov 2014)
*/

//#include "/d/Krynn/guilds/necro/defs.h"
#include "../local.h"
#include CLOCKH
#include <filter_funs.h>
#include <macros.h>

inherit CITY_BASE;

#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"

string
query_to_jail()
{
  return "north";
}

string messages;
int new_mail;

void
create_palan_room()
{
    set_short("Post Office of Palanthas");
    set_long("The post office of Palanthas is one of the older and more "
	+ "modest buildings in the inner city.  The entrance foyer is polished "
	+ "translucent marble leading to a carved marble exit.  Dark maroon "
	+ "carpet leads to the marble counter behind which city postal workers "
	+ "sort and distribute the mail.  The building extends through back "
	+ "rooms to the south further than you can view.\n");

	ITEM("carpet", "The carpet is short, firm to walk on, and dark maroon."
	+ "\n");
	ITEM("exit", "The exit door is a modest sized oak door.  It is set in "
	+ "an ornate, carved marble frame.\n");
	ITEM("frame", "The translucent marble frame around the oaken exit door "
	+ "has been carved in curving ornate patterns with intricate inset "
	+ "details.\n");
	ITEM("details", "Carved into the marble frame around the exit door are "
	+ "tiny and very intricate pictures of mounted knights, their lowered "
	+ "lances chasing satchel-laden riders atop swiftly running horses.\n");
	ITEM("ceiling", "The ceiling is vaulted and roomy.  There is no second "
	+ "floor here.\n");
	ITEM("floor", "The floor of the foyer is polished and reflective, "
	+ "translucent marble.  Dark maroon carpet covers the rest of the "
	+ "floor as it approaches the counter to the south.\n");
	ITEM(({"wall", "walls"}), "The walls of the post office are translucent "
	+ "marble.  They are fairly unadorned.\n");
	ITEM("counter", "The counter runs the width of the building separating "
	+ "you from the business section of the post.  It is a thin slab of "
	+ "polished, translucent marble atop dark stained wood.\n");

    EXIT(ROOM + "plaza", "north", 0, 0);
}

void
init()
{
    object mr;
    string *conclave;

    ::init();

    mr = clone_object("/secure/mail_reader");


    mr->move(TP, 1);
}

void
leave_inv(object ob, object to)
{
	if (TP->query_wiz_level()) { return 0;}

	else {

    object reader;

    ::leave_inv(ob, to);

    reader = present(MAILREADER_ID, ob);

    if (reader)
	reader->remove_object();
	}
}

int
query_mail(int silent)
{
    string new;
    int mail;

    mail = MAILCHECKER->query_mail();

    if (!mail) return 0;

    if (silent) return 1;

    new = "";
    if (mail == 2) new = " NEW";
    if (mail == 3) new = " unread";

    write("\n" +
      "You have" + new + " mail in the nearest post office.\n\n");

    return 1;
}
