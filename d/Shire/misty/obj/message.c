inherit "/std/object";
#include "/d/Shire/sys/defs.h"

string gMessage, gSender;

// Prototypes
string query_sender();
string read_message();
void destruct_me();

void
create_object()
{
    set_name("message");
    set_short("@@my_short");
    set_pshort("messages");
    set_long("@@read_message");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_NO_DROP, "@@do_destruct");
    gMessage = "Nothing.\n";
    gSender = "Someone";
}

void
init()
{
    ::init();
    add_action("do_read", "read",0);
}

string
my_short()
{
    return ("message from " + query_sender());
}

int
do_read(string str)
{
    if (str == "message" || str == my_short())
    {
	write(read_message());
	return 1;
    }
}

string
read_message()
{
    return ("The message reads:\n" + gMessage);
}

int
do_destruct()
{
    set_alarm(2.0,0.0,"destruct_me");
    return 0;
}

void
set_message(string str)
{
    gMessage = str;
}

void
set_sender(string str)
{
    gSender = capitalize(str);
}

string
query_sender()
{
    return gSender;
}

void
destruct_me()
{
    object room;
    if (living(room = environment()))
	room = environment(room);
    tell_room(room, "The message blows away with the wind.\n");
    remove_object();
}
