/*
     The room where the masters of the smiths guild meet
     also the room where bores (/d/Shire/smiths/npc/bores.c) is placed
*/

#pragma save_binary;

inherit "/d/Shire/room";

#include "smiths.h"
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include <std.h>


int test_exit();
int leave(string str);
string leaving;

/*
* Function name: log_guild
* Description  : This function logs some actions of members of the guild.
*                It uses a larger cycle than basically coded.
* Arguments    : string text - the message to log.
*/
nomask private void
log_guild(string text)
{
   setuid();
   seteuid(getuid());
   
   if (file_size(SMITH_MEMBERSHIP_LOG) > MAX_MEMBERSHIP_LOG_SIZE)
      {
      rename(SMITH_MEMBERSHIP_LOG, (SMITH_MEMBERSHIP_LOG + ".old"));
   }
   
   write_file(SMITH_MEMBERSHIP_LOG, text);
}


void
create_room() {
    set_short("A room in the Smiths Guild");
    set_long("This room is mostly used by the masters of the Smiths Guild"+
      " and thus it is where Bores, the high master of the Smiths Guild,"+
      " can be found most often. Placed in the middle of the room is his"+
      " desk. It is covered with pieces of paper and books about the"+
      " history of the greatest"+
      " of smiths and of strange artifacts and alloys. Here also is a large"+
      " book bound in brown leather concerning the Smiths Guild which new"+
      " apprentices are expected to have read before joining "+
      "the guild. A sign is mounted on the wall here.\n");

    add_item("desk","It is a plain oak table.\n");
    add_item("sign", "It's a small iron sign mounted on the wall "+
      "by a wooden peg. Perhaps you should read it?\n");
    add_item("peg", "It is firmly secured into the wall and an "+
      "iron sign hangs from it.\n");
    add_cmd_item("sign", "read", "Current members of the "+
      "Smith's guild may pick up a new necklace "+
      "here should they ever lose theirs. Just "+
      "<get necklace> and Bores will help you out.\n");

    add_exit(SMITHSDIR_ROOMS+"improve","west","@@test_exit@@");
    add_exit(SMITHSDIR_ROOMS+"raw_shop","southwest","@@test_exit@@");
    add_exit(SMITHSDIR_ROOMS+"discus","east",0);

    if (!objectp("guild master")) room_add_object
	("/d/Shire/smiths/npc/bores", 1, QCTNAME(TO)+" arrives.\n");
    if (!objectp("brown book")) room_add_object
	("/d/Shire/smiths/obj/join_book", 1);

    add_prop(ROOM_I_INSIDE,1);
// safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 
}

init() {
    ::init();
    add_action("leave","leave");
    add_action("get","get");
}

int
test_exit() 
{
    seteuid(getuid());
    if ("/secure/master"->query_wiz_dom(TP->query_real_name()) == "Shire")
	return 0;
    if (!IS_MEMBER(TP)) 
    {
	write("Only smiths are allowed to go there.\n");
	return 1;
    }
    return 0;
}

int
get(string str) {
    object obj;

    if ((str=="new necklace") || (str=="necklace")) {
    if ((!present("smiths_necklace",TP)) && (IS_MEMBER(TP)))
    {
	    seteuid(getuid(this_object()));

	    if (!present("_bores_", TO))
		write("Try again later when Bores is around.\n");

	    else
	    {
		obj = clone_object(SMITHSDIR+"necklace");
		obj->add_adj("iron");
		obj->set_short("iron necklace");
		obj->move(TP);
		write("Bores hands you a new necklace.\n");
		tell_room(TO, "Bores give an iron necklace to "+
		  TP->query_name()+".\n", TP);
	    }
	}
	else {
	    write("You cannot get a necklace here.\n");
	}
	return 1;
    }
    return 0;
}

int
leave(string str) {
    string occu_guild,laym_guild;
    object necklace;

    notify_fail("Leave what? The smiths guild?");

    laym_guild=TP->query_guild_name_lay();

    if ((str!="guild") && (str!="smiths guild")) return 0;

    if (!IS_MEMBER(TP))
    {
	write("But you are not a member of the Smiths Guild!\n");
	return 1;
    }

    if (leaving!=TP->query_name()) {
	write("Are you sure you want to leave the guild? If so then please"+
	  " type <leave guild> again.\n");
	leaving=TP->query_name();
	return 1;
    }

    write("You explain to Bores that you no longer want to be a member of"+
      " the Smiths Guild.\n");


    while(objectp(necklace = present("iron necklace", TP)))
    {
	write("You hand back the iron necklace to Bores.\n");
	necklace->remove_object();
    }

    if (laym_guild==GUILD_NAME) {
	if ((TP->remove_guild_lay()) != 1)
	    write("Something is really wrong here.... You cannot leave.\n");
	TP->remove_cmdsoul(SMITHSDIR+"smiths_lay_soul");


    remove_smith_guild_member(TP);

    TP->set_guild_pref(SS_LAYMAN, 0);
    TP->clear_guild_stat(SS_LAYMAN);

    TP->update_hooks();
    TP->setup_skill_decay();

    write("You are now no longer a member of the Smiths Guild.\n");
    say(QCTNAME(TP)+" leaves the Smiths Guild.\n");
    log_guild(ctime(time()) + " " + WRITE_NAME(TP) + " left the " +
        "Blacksmiths.\n");

    return 1;
    }
}
