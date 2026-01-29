#pragma save_binary

#include "/d/Genesis/start/human/town/grid/b_post.c"

#define MAILREADER	"/secure/mail_reader"

string messages;
int new_mail;




create_room() {
    fixgrid_room();
}


init() {
    object reader;
    ::init();

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
    string name;
    string new;

    name = lower_case(call_other(this_player(), "query_name"));
    if (!restore_object("d/Genesis/post_dir/" + name) || messages == "")
       return 0;
    if (silent) return 1;
    new = "";
    if (new_mail)
	new = " NEW";
    write("\n\n********\nThere is" + new +
	" mail for you in Sparkle post office.\n"+
        "   (North end of the road just inside the village gate.)\n\n");
    return 1;
}

