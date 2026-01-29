inherit "/lib/guild_support";
inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/annuminas/club/gobdefs.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/sys/macros.h"

/* Prototypes */
int do_touch(string str);
int do_begin(string str);
int do_stupid(string str);
int do_write(string str);

void
create_room()
{

    set_short("Cave room");
    set_long("The walls are covered with very crude maps in "+
      "this cave. Some small torches hang in various "+
      "corners, totally random corners. A bookshelf on "+
      "the floor coughs up its books from within. It is "+
      "damp and smelly in here. A small sign is planted "+
      "in the ground.\n");
    add_item("maps", "Dey look crude, don't touch dem!\n");
    add_item("torches", "Dey look hot, don't touch dem!\n");
    add_item("books", "Dey look important, don't touch dem!\n");
    add_item("bookshelf", "It looks big, don't touch it!\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT, 2);


    add_item("sign", "Try and read it buddy.\n");

    add_cmd_item("sign","read",
      "You may join our fine club of smart goblins by trying to "+
      "<begin learning>. Should you ever want to become a stupid, "+
      "and insignificant goblin again, you can just <be stupid>. "+
      "If you happen to lose your tome, and remember it happens "+
      "to the best of us, then use <write tome>.\n");


    add_exit("/d/Genesis/start/human/wild2/top4", "west");
    add_exit(ANNUM_DIR + "club/boardrm","east",0,1);

}

void
init()
{
    ::init();
    add_action("do_touch", "touch");
    add_action("do_begin", "begin");
    add_action("do_stupid", "be");
    add_action("do_write", "write");
}

int
do_touch(string str)
{ 
    notify_fail("Touch What?\n");
    if(!strlen(str))
	return 0;

    if(str == "bookshelf" || str =="books" || str =="torches" || str =="maps")
    {
	if(TP->query_race_name()!= "goblin")
	{
	    write("Go away scum!!!! Hmpf, and dey say Goblin stupid.\n");
	    TP->command("duh");
	    return 1;
	}
	else
	{
	    notify_fail("You CAN'T touch them!\n");
	    return 0;
	}
	write("Look stupid, cannot you read??\n");
	return 1;
    }
    return 0;
}

int
do_begin(string str)
{
    object tome;
    int i;

    if(str != "learning")
    {
	NF("Begin what?\n");
	return 0;
    }

    if (TP->query_race_name() != "goblin")
    {
	write("Go away!\n");
	return 1;
    }
    write("You are an officially intelligent goblin!\n");
    log_file("goblins",TP->query_real_name()+" joined "+
      extract(ctime(time()),4,15)+".\n");

    setuid(); seteuid(getuid());
    TP->add_cmdsoul(GOB_SOUL);
    TP->update_hooks();

    tome = present("_sciddy_", TP);
    if (!tome)
    {
	tome = clone_object(ANNUM_DIR+"club/tome");
	tome->move(TP,1);
	write("You get your tome from the mess on the floor.\n");
	say(QCTNAME(TP) + " becomes an enlightened goblin.\n");
    }
    return 1;
}

int
do_stupid(string str)
{
    object tome;
    int result;
    object soul;

    if (str!="stupid")
    {
	write("You wanna do what?????\n");
	return 1;
    }

    if (this_player()->query_race_name()!="goblin")
    {
	notify_fail("You not member anyway stupid!\n");
	return 0;
    }
    if (TP->remove_cmdsoul(GOB_SOUL))
    {
	write("You now dumb goblin!\n");
	tome = present("_sciddy_", TP);
	if (tome)
	{
	    tome->remove_object();
	    write("Your tome bursts into flames!\n");
	    say(QCTNAME(TP) + " leaves da club.\n");
	    log_file("goblins",TP->query_real_name()+" left   "+
	      extract(ctime(time()),4,15)+".\n");
	}

	TP->update_hooks();
    }
    else
	write("Because of an error, you remain with us.\n");
    return 1;
}

int
do_write(string str)
{
    object tome;

    if (str!="book" && str!="tome")
	return 0;
    if (TP->query_race_name()!="goblin")
    {
	write("But you not member of dis club. "+
	  "Only goblins can write books!\n");
	return 1;
    }
    tome = present("_sciddy_", TP);
    if (tome)
    {
	write("You already have one!\n");
	return 1;
    }
    setuid(); seteuid(getuid());
    tome = clone_object(ANNUM_DIR + "club/tome");
    tome -> move(TP);
    write("You get another tome from da mess.\n");
    say(QCTNAME(TP)+" grabs a book from the stack.\n");
    return 1;
}
void
soul(object ob)
{
    seteuid(getuid(TO));
    ob->add_cmdsoul(GOB_SOUL);
    ob->update_hooks();
}
