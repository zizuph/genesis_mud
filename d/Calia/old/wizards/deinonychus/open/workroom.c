inherit "/std/room";

#include "dirs.h"
#include <macros.h>
#include <stdproperties.h>

#define	MAILREADER	"/d/Genesis/obj/mail_reader"

string	*invited;

void
create_room()
{
    object door;

    set_short("Zawion's workroom");
    set_long("This is a large office vith bookshelves and a large desk. On \n"+
	    "the south wall a there is a painting of Halgor, Zawions lost \n"+
	    "love, and on the east wall there is a portal; on the desk \n"+
	    "there is a note. ");

    add_item( ({ "portrait", "painting" }) ,"" +
          "Halgor's smile dazzles you. (You estimate the valueto be about \n" +
	  "400 platinum coins.\n");
    add_item( ({ "book", "book" }) , "The book read: Keep out of th maze.\n");
    add_item( ({ "note", "note" }) , "The note read: Finish the maze.\n");
    add_item( ({ "portal" }) , "To start 'playing' enter here.\n");
    add_item( ({ "desk", "large desk" }) , "It is a large workdesk, used by ancient architects.\n");

    add_exit("/d/Dville/glykron/palace/entrance", "start",0);
    add_exit("/d/Dville/glykron/palace/shop", "portal", 0);
    add_exit("/d/Genesis/start/human/town/tower", "human", 0);
    add_exit("/d/Genesis/wiz/entrance", "news", 0);
    add_exit("/d/Genesis/wiz/domain", "domain", 0);
    add_exit("/d/Genesis/wiz/idea", "idea", 0);
    add_exit("/d/Genesis/wiz/flame", "flame", 0);
    add_exit("/d/Genesis/wiz/discuss", "discuss", 0);
    add_exit("/d/Genesis/wiz/lpc", "lpc", 0);
    add_exit("/d/Genesis/wiz/infotool", "tool", 0);
    add_exit("/d/Genesis/wiz/admin", "admin", 0);
    add_exit("/d/Genesis/wiz/post", "post", 0);
    add_exit("/d/Dville/glykron/palace/post", "ppost", 0);
    add_exit("/d/Dville/workroom", "meet", 0);
    add_exit("/d/Dville/glykron/palace/stairs", "stair", 0);
    add_exit("/d/Dville/glykron/palace/guild", "guild", 0);
    add_exit("/d/Dville/common/entrance", "common", 0);
    add_exit( LODGE_DIR + "lodgent", "lodge", 0);
    add_exit( ROOM_DIR + "workout", "workout", 0);
    add_exit( ROOM_DIR + "sorry_Idletime", "idle", 0);
    add_exit( ROOM_DIR + "working_do_not_disturb", "coding", 0);


    add_prop(ROOM_I_INSIDE, 1);

    door=clone_object(ROOM_DIR + "doors/wrmdr_a");
    door->move(this_object());
    door->set_key(11097235378);

    invited=({ "zawion" });
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (interactive(ob))
	if (member_array(ob->query_real_name(),invited)<0) {
	    ob->catch_msg("You are unable to get in there. Try knocking on the door.\n");
	    ob->move(ROOM_DIR +  "entrance");
	    tell_room(ROOM_DIR + "entrance", QCTNAME(ob) + " " + ob->query_mm_in() + "\n", ob);
	    tell_room(this_object(), QCTNAME(ob) + " tried to enter the room "+
		      "without invitation.\n");
	    return;
	}
}

void
leave_inv(object ob,mixed to)
{
    object reader;

    ::leave_inv(ob,to);
    reader=present("mailread",ob);
    if (reader)
	reader->remove_object();
}

void
init()
{
    object reader;

    ::init();
    if (this_player()->query_real_name() == "zawion") {
	add_action("invite", "invite");
	add_action("uninvite", "uninvite");
	reader=clone_object(MAILREADER);
	if (!reader) {
	    write("No mailreader is available at this time.\n");
	    return;
	}
	reader->move(this_player());
    }
}

void
add_invite(string str)
{
    if (!str)
	return;
    log_file("workroom", "Added   invite of " + capitalize(str) + " at " + ctime(time()) + ".\n", -1);
    if (str == "zawion")
	return;
    if (member_array(str, invited)<0)
	invited += ({ str });
}

void
remove_invite(string str)
{
    if (!str)
	return;
    log_file("workroom", "Removed invite of " + capitalize(str) + " at " + ctime(time()) + ".\n", -1);
    if (str == "zawion")
	return;
    if (member_array(str, invited)>=0)
	invited -= ({ str });
}

int
clean_up()
{
    if (sizeof(invited) == 1)
	return ::clean_up();
    return 1;
}

int
invite(string str)
{
    notify_fail("Invite whom?\n");
    if (!str && str=="zawion")
	return 0;
    add_invite(str);
    write("Ok.\n");
    return 1;
}

int
uninvite(string str)
{
    notify_fail("Uninvite whom?\n");
    if (!str && str=="zawion")
	return 0;
    remove_invite(str);
    write("Ok.\n");
    return 1;
}
