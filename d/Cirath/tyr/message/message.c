inherit "/std/object";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"

string gMessage, gSender;

create_object() {
    set_name("message");
    set_pname("messages");
    set_short("@@my_short");
    set_pshort("messages");
    set_long("@@read_message");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_NO_DROP, "@@do_destruct");
    gMessage = "Nothing.\n";
    gSender = "Someone";
}

init() {
    add_action("do_read", "read",0);
}

my_short() {
    return ("message from " + query_sender());
}

do_read(str) {
    if (str == "message" || str == my_short())
    {
	write(read_message());
	return 1;
    }
}

read_message() {
    return ("The message reads:\n" + gMessage);
}

do_destruct() {
    call_out("destruct_me",2);
    return 0;
}

set_message(str) {
    gMessage = str;
}

set_sender(str) {
    gSender = capitalize(str);
}

query_sender() {
    return gSender;
}

destruct_me() {
    object room;
    if (living(room = environment()))
	room = environment(room);
    tell_room(room, "The message blows away with the wind.\n");
    remove_object();
}
