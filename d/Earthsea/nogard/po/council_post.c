/*  Coded by Amelia
 *  4/5/98
 */
inherit "/std/room";
inherit "/d/Genesis/lib/post";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Roke/common/defs.h"
#include "/d/Roke/common/gont/monks/guild.h"
#include "/d/Roke/common/gont/monks/mail_defs.h"

void
reset_room()
{
}

void
add_aliases(object reader)
{
    reader->set_alias("council", MONKS_COUNCIL );
    reader->set_alias("elders", MONKS_ELDERS );
}

void
create_room()
{
    set_short("The Kahedan Council Post Office");
    set_long(break_string("This is a small quiet alcove "+
	"where you can send and receive mails in peace. "+
	"There are now aliases here for council and elders, "+
	"as in <mail elders> or <mail council>. "+
	get_std_use(), 70));
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "I don't think so!\n");
    reset_room();

    add_exit("/d/Roke/common/gont/monks/secret", "east");
}

void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob,to);
    post_leave_inv(ob,to);
}

void
mail_message(string new)
{
    write("\nThere is "+ new + " mail for you in the post office "+
      "of the Kahedan guild council.\n");

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
	if (COUNCIL_MEMBER(TP->query_real_name()) ||
	  (SECURITY->query_wiz_rank(ob->query_real_name())>= WIZ_ARCH)
	  || (SECURITY->query_wiz_dom(ob->query_real_name()) == "Earthsea") ||
	  (SECURITY->query_wiz_dom(ob->query_real_name()) == "Cirath"))
	    return;

	// getting the nasty boot

	ob->catch_msg("\nYou are not allowed there! Begone!\n\n");
	seteuid(getuid());
	ob->move(ob->query_def_start());
    }
    return;
}
