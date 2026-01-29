/*
 * The Bree post office
 * by Finwe, June 2002
 */

inherit "/d/Shire/std/room";
#include "/sys/stdproperties.h"
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#define I_PENNED_RANGER_COUNCIL   ("_i_penned_ranger_council")

string messages;
int new_mail;

create_room() 
{
    set_short("Post Office of Bree");
    set_long("@@my_long");
   
    add_item(({"mailboxes","mailbox","hole","holes","little holes", "boxes"}),
        "The little holes are mailboxes with little brass plaques " +
        "nailed below each one. Some of the mailboxes have letters " +
        "and mail in them, others are empty.\n");
    add_item(({"plaques", "small plaques", "little brass plaques"}),
        "The plaques are rectangular in shape and polished. " +
        "Engraved on them are the names of the mailbox owners, " +
        "probably people who live in and around Bree.\n");

    add_item("sign", "In contains important information for you to read.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");
   
    add_exit(ROAD_DIR + "broad08","out",0,1,1);
    add_exit(ROAD_DIR + "broad08","south");
    add_exit(TOWN_DIR + "notary","up");

   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
}

void
init()
{
    ::init();

    add_action("pen_council", "pen");
}


my_long() 
{
    string long;
    
    long = "You have entered a hobbit-hole with many little boxes on " +
        "the wall. Mail from all the Shire comes and is sorted out for " +
        "people in Bree. Special deliveries are sent and received to " +
        "people in far away lands. Upstairs is the local notary office " +
        "for the people of Bree and its visitors. There is a sign hanging " +
        "on the wall.\n";

    return long;
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
   reader = present("mailreader", ob);
   if (reader) reader->remove_object();
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
        "to you.\n\n" + 
    "If you need to contact the Ranger Council, you may do so from here. " +
        "You get one chance so be sure your message is correct before " +
        "sending it.\n\n" +
    "To send the message do <pen [message]>. This will notify a sentry who " +
        "will then deliver it to the Council for you.\n\n";
}


/*
 * Gives non-rangers the ability to contact the Ranger Council
 * Finwe, February 2005
 */
pen_council(string str)
{
    string message;

    if (TP->query_prop(I_PENNED_RANGER_COUNCIL))
    {
        NF("You have already contacted the Ranger Council, and your last " +
        "message has been sent to them. Thank you.\n");
        return 0;
    }

    if (!strlen(str))
    {
        NF("Please read the sign for more information.\n");
        return 0;
    }

    message = str;
    write("Your message has been sent to the Ranger Council. Thank you.\n");
    MANAGER->rlog("messages", "From the Bree Post Office by " 
        + capitalize(TP->query_real_name()) + ":\n\n"
        + message + "\n"
        + "     ---------------------------------------------     \n");
    TP->add_prop(I_PENNED_RANGER_COUNCIL, 1);
    return 1;
}
