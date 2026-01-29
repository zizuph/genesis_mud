#pragma strict_types

inherit "/d/Ansalon/taman_busuk/sanction/std/i_room_base";

inherit "/d/Genesis/lib/post";

#include <files.h>
#include <mail.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

/*proto*/
int check_member();

void
create_sanction_room()
{
    set_short("main Dragonarmy dispatch office in Sanction");
    set_long("You stand in the main dispatch office of the dragonarmies " +
      "in Sanction. Here, mails and messages are scripted and sent via " +
      "wyvern to various people, ranging from demands to enemy leaders to " +
      "simple and inane greetings to distant companions.\n");

    add_item("wyvern","From here wyvern carry messages to other " +
      "dispatch and post offices.\n");

    add_exit(SCITY + "office","north",0);
    add_exit(SCITY + "meet","down",check_member);

    /*
	clone_object(SOBJ + "rack")->move(TO,1);
    */
}


int
check_member()
{
    if (TP->query_wiz_level())
    { 
	return 0;
    }

    if (!TP->query_guild_member("Priests of Takhisis") &&
     !(TP->query_dragonarmy_promotions())) {
	write("You cannot enter there.\n");
	return 1;
    }

    return 0;

}
void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

void
mail_message(string new)
{
    write("\nYou have" +new+ " mail for you in the " +
      "Iron Delving" +
      " post office.\n\n");
}
