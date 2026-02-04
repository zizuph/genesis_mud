#pragma strict_types

inherit "/std/object";

#include "../../guild.h"

#include <macros.h>
#include <stdproperties.h>

string Message;
string Sender;

public void
create_object(void)
{
    Message = "";
    Sender = "Nobody";

    set_name("message");
    set_pname("messages");
    set_short("@@my_short");
    set_pshort("@@my_pshort");
    set_long("@@my_long");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_NO_DROP, "@@do_destruct");
}

public void
set_sender(string str)		
{ 
    Sender = capitalize(str); 
}

public string query_sender()
{
    return Sender; 
}

public void set_message(string str)		
{
    Message = str; 
}

private string
read_message(void)
{

    say(QCTNAME(TP) + " reads over a message.\n");
    return ("The message reads:\n" +
	" ___________________________________\n" +
		Message + "\n" +
	" ___________________________________\n");
}

public string
my_short(void)
{
    return ("message from " + query_sender());
}

public string
my_pshort(void)
{
    return ("messages from " + query_sender());
}

public string
my_long(void)
{
    return read_message();
}


public int
do_read(string str)
{
    object ob;

    notify_fail("Read what?\n");
    if (!strlen(str))
    {
        return 0;
    }
	
	if (parse_command(str, all_inventory(TP), "%o", ob) &&
	    ob == TO)
    {
    	write(read_message());
	    return 1;
    }

    return 0;
}

public void
destruct_me(void)
{
    object room;

    if (living(environment(TO)))
	return;

    if (living(room = environment()))
	room = environment(room);

    tell_room(room, "The message blows away with the wind.\n");
    remove_object();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    set_alarm(5.0, 0.0, destruct_me);
}


public void
init(void)
{
    add_action(do_read, "read");
}
