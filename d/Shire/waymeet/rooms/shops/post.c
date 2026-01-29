/*
 * The Bree post office
 * by Finwe, June 2002
 *
 * Now the Waymeet Post Office
 * Raymundo, Feb 2020
 */

inherit "/d/Shire/std/room";
#include "/sys/stdproperties.h"
#include "/d/Shire/sys/defs.h"

#include "/d/Shire/waymeet/defs.h"



string messages;
int new_mail;

create_room() 
{
    set_short("Waymeet Post Office");
    set_long("Although the Post Office is very plain, you can "
		+ "tell it receives a lot of use. There are many mailboxes "
		+ "here, many of them with mail awaiting pickup. The floor "
		+ "looks worn with foot traffic. A sign hangs on the wall.\n");
   
    add_item(({"mailboxes","mailbox","hole","holes","little holes", "boxes"}),
        "The little holes are mailboxes with little brass plaques " +
        "nailed below each one. Some of the mailboxes have letters " +
        "and mail in them, others are empty.\n");
    add_item(({"plaques", "small plaques", "little brass plaques"}),
        "The plaques are rectangular in shape and polished. " +
        "Engraved on them are the names of the mailbox owners, " +
        "probably people who live in and around Waymeet.\n");
	add_item("floor", "The floor is made of wood. You can see a well-worn "
		+ "path from the doorway to the mailboxes.\n");
	add_item("path", "It seems people walk here to get to their "
		+ "mailboxes!\n");
	add_item("ceiling", "The ceiling is made of wood and is painted "
		+ "white. There is a stain in the corner.\n");
	add_item( ({"stain", "corner"}), "The stain appears to be a "
		+ "discolored patch in the ceiling. It's likely water damage. "
		+ "The roof should be fixed before the post office molds!\n");
	add_cmd_item( "roof", "fix", "You can't fix the roof from inside!\n");
	add_item( ({"wall", "walls"}), "The walls hold up the roof and keep the "
		+ "inside separate from the outside. They are otherwise unremarkable "
		+ "except for the mailboxes they hold.\n");
	add_cmd_item( ({"plaque", "plaques", "small plaques", "small plaque", "little brass plaques"}), "read", "@@re_plaques@@");

    add_item("sign", "In contains important information for you to read.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");
   
    add_exit(WAYM_STREET_DIR + "street_10", "out");
	add_exit(WAYM_STREET_DIR + "street_10", "west", 0,0,1);

   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
}

void
init()
{
    ::init();

}


enter_inv(ob, from)
{
   object reader;
   object vote_room;
   string *masters;

   ::enter_inv(ob, from);

    if (!living(ob))
        return;
   if (present("mailreader", ob)) return;
   reader=clone_object("/secure/mail_reader");
   reader->move(ob, 1);
}

leave_inv(ob, to)
{
   object reader;
   
   ::leave_inv(ob, to);
   if(!TP->query_wiz_level())
   {
   reader = present("mailreader", ob);
   if (reader) reader->remove_object();
   }
}

query_mail(silent) {
   string name;
   string new;
   
   name = lower_case(this_player()->query_name());
   if (!restore_object("/d/Genesis/post_dir/"+name) || messages == "")
      return 0;
   if (silent)
      return 1;
   new = "";
   if (new_mail)
      new = " NEW";
   write("\n"+
      "********************************************************\n"+
      "There is"+new+" mail for you in the nearest post office.\n"+
      "********************************************************\n\n");
   return 1;
}

string read_sign()
{
    return "\n\nOn the sign you see etched in careful lettering the following " +
        "instructions:\n\n" +
    "Examine the mailreader for a list of different commands available " +
        "to you.\n\n" ;
}



string
re_plaques()
{
	return("You begin reading names on the plaques, when you come across "
		+ TP->query_name() + ". It seems you can get mail here as well!\n");
}

