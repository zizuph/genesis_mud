 
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
#define GOB_LOG      "/d/Shire/log/gobbos"
string title;
 
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


    add_item("sign", "Perhaps you could read it?\n");

    add_cmd_item("sign","read",
         "You may join our fine club of smart goblins by trying to "+
         "<begin learning>. Should you ever want to become a stupid, "+
         "and insignificant goblin again, you can just <be stupid>. "+
         "If you happen to lose your tome, and remember it happens "+
         "to the best of us, then use <write tome>.\n");
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
if(str != "bookshelf" && str !="books" && str !="torches" && str !="maps")
    {
    write("Touch what?\n");
    return 0;
    if(TP->query_race_name()!= "goblin")
    {
    write("Go away scum!!!! Hmpf, and dey say Goblin stupid.\n");
    TP->command("duh");
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
    string *souls;

    if(str != "learning")
    {
    write("Begin what?\n");
    return 0;
    }
    if (TP->query_race_name() != "goblin")
        {
            write("Go away!\n");
            return 1;
        }
        write("You are an officially intelligent goblin!\n");
		    write_file(GOB_LOG, TP->query_real_name() + " joined " + 
			   extract(ctime(time()), 4, 15) + "\n");      

        seteuid(getuid(TO));
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

    if (str !="stupid")
    {
        write("You wanna do what?????\n");
        return 1;
    }

    if (this_player()->query_race_name()!="goblin")
    {
        notify_fail("You not member anyway stupid!\n");
        return 1;
    }
    if (TP->remove_cmdsoul(GOB_SOUL))
    {
        write("You now dumb goblin!\n");
        tome = present("_sciddy_", TP);
        if (tome)
        {
            tome->remove_object();
            write("Your tome disintegrates into dust!\n");
            say(QCTNAME(TP) + " leaves da club.\n");
		        write_file(GOB_LOG, TP->query_real_name() + " joined " + 
			      extract(ctime(time()), 4, 15) + "\n");

        }
    
       TP->update_hooks();
    }
    else
        write("Are you sure you were a member in the first place?\n");
    return 1;
}
 
int
do_write(string str)
{
    object tome;

   if (str!="book" && str!="tome")
        return 0;
    if (TP->query_race_name() != "goblin")
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
    tome = clone_object(ANNUM_DIR + "club/tome");
    tome -> move(TP);
     write("You get another tome from da mess.\n");
     say(QCTNAME(TP)+" grabs a book from the stack.\n");
     return 1;
}

void
soul(object ob)
{
    object spells;
    int i;
    string *souls;

    seteuid(getuid(TO));
    souls = ob->query_cmdsoul_list();
    for (i = 0; i < sizeof(souls); i++)
        ob->remove_cmdsoul(souls[i]);
    ob->add_cmdsoul(GOB_SOUL);
    for (i = 0; i < sizeof(souls); i++)
        if (souls[i] != GOB_SOUL)
            ob->add_cmdsoul(souls[i]);
    ob->update_hooks();
}
