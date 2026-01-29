#pragma save_binary

#include <stdproperties.h>
#include "default.h"

string messages;
int new_mail;

void
create_room() {
	change_prop(ROOM_I_LIGHT, 10);
	add_exit(THIS_DIR + "entrance", "west" );
	add_default_exits();
	set_short("The post office (wizards branch)");
	set_long("You are in the wizards post office.\n" +
	    "Examine the mail reader for information about the commands.\n");
}

init() {
	::init();
	clone_object("/secure/mail_reader")->move(this_player(), 1);
}

leave_inv(ob, to) {
    ::leave_inv(ob, to);

    if (!ob->query_wiz_level())
    {
        present("mailread", ob)->remove_object();
    }
}
