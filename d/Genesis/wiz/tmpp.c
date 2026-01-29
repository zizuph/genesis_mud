#pragma save_binary

#include <stdproperties.h>
#include "default.h"

string messages;
int new_mail;

create_room() {
	change_prop(ROOM_I_LIGHT, 10);
	add_exit(THIS_DIR + "tmpc", "west" );
	set_short("The post office (wizards branch)");
	set_long("You are in the temporarily post office. Commands:\n" +
		"read            Read from the mailbox.\n" +
		"mail <name>     Mail to player 'name'.\n" +
		"from            List all headers.\n"
	);

    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
}

init() {
	::init();
	clone_object("/d/Genesis/obj/mail_reader")->move(this_player(), 1);
}

leave_inv(ob, to) {
    object reader;
    ::leave_inv(ob); /* , to); */

    reader = present("mailread", ob);
    if (reader) reader->remove_object();

}