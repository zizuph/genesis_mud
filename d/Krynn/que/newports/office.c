/* This is one of the delivery offices in Krynn
 * Aridor, 05/95
 */

#include "local.h"
#include DELIVERY

//inherit PLAINS_BASE
inherit BASE_FILE;
inherit DELIVERY_OFFICE;

object ob;

void
create_room()
{
    set_short("Delivery Office");
    set_long("You are in a small office stacked with packets, parcels, " +
	     "boxes and containers of different sizes, shapes and forms. " +
	     "In the middle of the room is a small desk with a haughty human " +
	     "sitting behind it. A sign is hanging from the ceiling.\n");
    add_item(({"office","room"}),
	     "It stacked up to the ceiling with packets, boxes and other " +
	     "containers.\n");
    add_item(({"packets","parcels","boxes","containers"}),
	     "They're everywhere, and come in all sizes, shapes and forms.\n");
    add_item(({"desk"}),
	     "It's an ordinary wooden desk with a haughty human sitting " +
	     "behind it.\n");
    add_item(({"human","haughty human"}),
	     "This is a haughty human. He is sitting behind the desk and " +
	     "looks at you expectantly.\n");
    add_item(({"ceiling"}),
	     "You can barely see the ceiling as the packets and boxes are " +
	     "stacked all the way up to it. A sign is hanging from the " +
	     "ceiling.\n");
    add_item(({"sign"}),
	     "You read:\n" +
	     "Delivery Office Newports\n" +
	     "'ask for a delivery tour' if you wish to help out and earn a " +
	     "few coins.\n" +
	     " All you need to do with the packet you receive then is to " +
	     "bring it to\n" +
	     " its destination where you will also receive the payment. Use " +
	     "'deliver\n" +
	     " packet' to deliver your packet at its destination. 'return " +
	     "packet' is\n" +
	     " for packets which are not destined for this office and which " +
	     "do not \n" +
	     " have this office set as origin.\n");
    add_cmd_item(({"sign"}),"read",
		 "Delivery Office Newports\n" +
		 "'ask for a delivery tour' if you wish to help out and earn " +
		 "a few coins.\n" +
		 " All you need to do with the packet you receive then is to " +
		 "bring it to\n" +
		 " its destination where you will also receive the payment. " +
		 "Use 'deliver\n" +
		 " packet' to deliver your packet at its destination. '" +
		 "return packet' is\n" +
		 " for packets which are not destined for this office and " +
		 "which do not \n" +
		 " have this office set as origin.\n");
    add_exit(TDIR + "village","southwest");
    set_office("Newports",10);
}

void
init()
{
    init_office();
    ::init();
    if (ob = present("tour5", TP))
      ob->set_arr("delivery office");
}

void
reset_room()
{
    reset_office();
}

void
print_message(string str)
{
    write("The haughty human says: " + str + "\n");
}
