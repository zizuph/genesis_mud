inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <macros.h>

#define MAILREADER	"/d/Genesis/postmaster/mail_reader"
#define MAILCHECKER "/d/Genesis/postmaster/mail_checker"

create_room() {
	set_short("Commoners post office");
	set_long(BSS("You have entered the Commoners post "+
		"office in Tyr. There is a counter here where "+
		"you can deliver or pick up mail. Behind the "+
		"counter there is a small plaque on the wall. "+
		"You can see the exit out south leading out "+
		"to the Main Gate Road.\n"));

	add_item("counter", BSS(
		"This is a very plain counter, visibly worn "+
		"by the sand blowing in through the door "+
		"during the fierce sand storms that roam the "+
		"area most times of the year.\n"));

	add_item(({"road","main gate road","Main Gate Road"}), BSS(
		"This street looks just like most other streets "+
		"in Tyr, partially covered by sand and dirt.\n"));

	add_item("plaque", BSS(
		"There is some writing on the plaque, giving you "+
		"instructions on how to use this post office. "+
		"Though you will need to read it to get the "+
		"information.\n"));

	add_exit(MGR_STR+"road6","south",0);

    add_prop(ROOM_I_INSIDE, 1);
}

init() {

    object reader;
    ::init();
	add_action("do_read","read");

    reader = clone_object(MAILREADER);
    if (!reader) {
	write("No mailreader is available at this time.\n");
	return;
    }
    reader->move(this_player());
}

leave_inv(ob, to) {
    object reader;
    ::leave_inv(ob); /* , to); */

    reader = present("mailread", ob);
    if (reader) reader->remove_object();

}

query_mail(silent) {
    string new;
    int mail;

    seteuid(getuid());
    mail = MAILCHECKER->query_mail();
    if (!mail)
      return 0;
    if (silent) return 1;
    new = "";
    if (mail > 1) 
	new = " NEW";

    write("\n"+
    "There is"+new+" mail for you in your local post office.\n\n");
    return 1;
}
int
do_read(string str)
{    
    if (!str)
    return 0;

    if (str != "plaque")    {
	    notify_fail("Read what? The plaque??\n");
	    return 0;
	}
	write("You read:\n"+BSS(
		"Here are some instructions to use the post "+
		"office.\n")+
		"     read #             Read your mail.\n"+
		"     mail <player>      Mail to another player by 'name'.\n"+
		"     from               List all incoming mail by header.\n"+
		"\n\nWe hope you enjoy your stay in our small town.\n");
	say(QCTNAME(this_player())+" reads the plaque.\n");
    return 1;
}
