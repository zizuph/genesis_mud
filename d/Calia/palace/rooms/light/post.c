/* Original File: /d/Genesis/start/human/town/post.c 

   History:
           4/1/2000   won't remove mailer from wizard         Maniac
           6/4/96     tidied up kroug handling                Maniac
           12/12/95    vandalism possibility added            Maniac
           22/9/95     kroug raid code installed              Maniac
           17.7.95     desc changed                           Maniac
           20.4.95     Aliases for council/recruiters added   Maniac
*/
#pragma save_binary

inherit "/d/Calia/std/kroug_palace_room";
#include <stdproperties.h>
#include "defs.h"
#include COUNCIL_HEADER
#include RECRUITER_HEADER
#include "/d/Calia/std/vandalism.c"

#define MAILREADER       "/secure/mail_reader"

string messages;
int new_mail;

init()
{
    object reader;
    string *r;
    ::init();

    init_vandalism();

    seteuid(getuid());
    reader = clone_object(MAILREADER);
    if(!reader)
    {
	write("No mailreader is available at this time.\n");
	return;
    }
    reader->set_alias("council", COUNCIL_CODE->query_council_members());
    r = RECRUITER_CODE->query_recruiters();
    if (member_array(this_player()->query_name(), r) > -1) 
        reader->set_alias("applicants", RECRUITER_CODE->query_applicants());
    reader->set_alias("recruiters", r);
    reader->move(this_player());
}


/* Take away the mailreader and inform the kroug room code */
void
leave_inv(object ob, object to)
{
    object reader;
    ::leave_inv(ob, to);

    if (!ob->query_wiz_level() &&
        objectp(reader = present("mailread", ob))) {
        reader->remove_object();
    }
}


int
query_mail(int silent)
{
    string name, new, sp;

    name = lower_case(call_other(this_player(), "query_name"));
    if (!restore_object("d/Genesis/post_dir/" + name) || messages == "")
       return 0;
    if (silent) return 1;
    new = ""; sp = "    ";
    if (new_mail) {
	new = " NEW";
	sp = "";
    }
    write("\n"+
        "     +---------------------------------------------------------+\n"+
        "     ! There is" + new + " mail for you in the palace post office. "+
        sp +" !\n"+
/*      "     ! (North end of the road just inside the village gate.)   !\n"+ */
        "     +---------------------------------------------------------+\n");
    return 1;
}

void
create_room()
{
 
    set_short("The post office");

    set_long(
	"You are in the post office, a small trapezoidal room with north " +
        "and west walls slanting away from you to the southeast. A large " +
        "wooden desk sits at its centre. " +
        "Here you may use the mail aliases `council' to reach the Calian " +
        "Council, and `recruiters' to reach the Calian Recruitment " +
        "Officers. ROs may contact current applicants with the alias " +
        "`applicants'.\n"+
        "Commands are:\n"+
        "    read            Read your mail.\n"+
        "    mail <name>     Mail to player 'name'.\n"+
        "    from            List all headers.\n"+
        "");

    add_exit(ROOM("light_hall"), "west", 0);
    add_exit(ROOM("light_lightroom"), "north", 0);

    add_item(({"desk", "wooden desk"}), "A large wooden desk intended for " +
              "use in the sorting, reading and writing of mail. It is in " +
              "fine condition.\n");
    add_item_possible_vandalism("desk", "A large wooden desk intended for " +
              "use in the sorting, reading and writing of mail.",
                            ({"dent", "break", "smear", "scratch"}), 60);
    add_item(({"walls","wall" }),"");
    add_item(({"room" }),"");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

