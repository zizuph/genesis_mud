/*
 * /d/Gondor/common/guild/obj/message.c
 *
 * The note delivered by pigeons.
 *
 * Original version by Elessar (?)
 *
 * Modification log:
 *  7-Dec-1996, Olorin: General revision.
 * 16-Mar-1998, Gnadnar: use parse_command() so can "read third message"
 */
#pragma save_binary
#pragma strict_types
 
inherit "/std/object.c";
 
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
 
private static string  gMessage,
                       gSender;
 
#if OLD_VERSION
// Where is this used?
public string
my_short()
{
    return "message";
}
#endif
 
public string
read_message()
{
   return ("The message says:\n" + gMessage);
}
 
public void
destruct_me()
{
    object room;
    if (living(room = environment()))
        room = environment(room);
    tell_room(room, "The message bursts into flames, leaving a wisp of smoke behind.\n");
    remove_object();
}
 
public void
do_destruct()
{
    if (query_verb() == "drop")
        set_alarm(2.0, 0.0, destruct_me);
    return 0;
}
 
public void
create_object()
{
    set_name("message");
    set_pname("messages");
#if OLD_VERSION
    set_short(my_short);
#endif
    set_short("message");
    set_pshort("messages");
    set_long(read_message);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_NO_DROP, do_destruct);
    gMessage = "Nothing.\n";
    gSender = "Someone";
}
 
public int
do_read(string str)
{
    object *ob;
    if (strlen(str) &&
        parse_command(str, all_inventory(this_player()), "%i", ob) &&
        sizeof(ob = NORMAL_ACCESS(ob, 0, 0)) &&
        ob[0] == this_object())
    {
        write(read_message());
        return 1;
    }
}
 
public void
init()
{
    add_action(do_read, "read");
}
 
public void
set_message(string str)
{
    gMessage = str;
}
 
public void
set_sender(string str)
{
    gSender = capitalize(str);
}
 
public string
query_sender()
{
    return gSender;
}
