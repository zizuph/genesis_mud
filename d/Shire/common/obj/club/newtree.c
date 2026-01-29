// Old Fogey's club, borrowing from Vladimir and Dunstable's
// Smart Goblin club, Dunstable 12/94. 

inherit "/lib/guild_support";
inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/sys/macros.h"

/* Prototypes */
int do_limp(string str);
int do_hasty(string str);
int do_cane(string str);

#define RACE this_player()->query_race_name()
#define FOGEY_LOG      	"/d/Shire/log/fogeys"
#define FOGEY_SOUL    	"/d/Shire/common/obj/club/fogey_soul"

string title;
 
void
create_room()
{
    set_short("Clearing with tree");
    set_long("A clearing just off the Greenway south of Bree. A large, "+
    "gnarled oak stands defiantly where it seems no other tree would "+
    "dare.  A ring of trees encloses this glen from the outside world, "+
    "only a slight path leads back east to the Greenway. The tall oak "+
    "tree seems to have a sign affixed to it.\n");

    add_item(({"trees","ring of trees","pines"}),
    "The ring of pine trees seem younger than the gnarled old oak standing in "+
    "the middle of the glen. They are tightly bunched and impenetrable.\n");

    add_item(({"oak","tree","gnarled oak","gnarled old oak","tall oak"}),
    "The tall gnarled oak tree towers above the younger ring of pines. "+
    "It has many nooks and crannies, likely a good hiding spot for secrets. "+
    "It has an old withered sign attached near the base, probably it is still "+
    "readable.\n");

    add_item(({"nook","cranny","nooks","crannies"}),
    "There is no telling what is in these dark places.\n");

    add_item("sign", "Perhaps you could read it?\n");

    add_cmd_item("sign","read",
    "You may become an Old Fogey if you are qualified to do so.\n"+
    "Here are the qualifications: You must be male, and of race "+
    "either human, hobbit or dwarven. Sorry, no goblins, elves or "+
    "gnomes! To join, type <limp now>, and you will begin the process "+
    "of becoming a true Old Fogey. Should you ever lose your cane, you "+
    "can get a new one by typing <cane me> here.  If you ever become hasty "+
    "and wish to be like the young folk again, type <become hasty> here.\n"+
    "Members may <start here>.\n");

    add_prop(ROOM_I_LIGHT, 2);
    add_exit("/d/Shire/common/gondorlink","east",0,1);

}

void
init()
{
    ::init();
    add_action("do_limp", "limp");
    add_action("do_hasty", "become");
    add_action("do_cane", "cane");
    add_action("start","start");

}

int start(string s)
{
  object ob;

  if(!(ob=present("_fogey_cane_",TP)))
     {
       write("You're not an Old Fogey!\n");
       return 1;
     }
  NF("Start where?\n");
  if(s!="here") return 0;


  TP->set_default_start_location(OBJ_DIR + "club/tree");
     write_file("/d/Shire/log/fogeys",TP->query_name()+" chose the "
     + "Fogeys Club as permanent starting location on "
     + ctime(time()) + ".\n");

     write(BS("Ok, you start here now.\n"));
  return 1;
}



int
do_limp(string str)
{
    object cane;
    int i;
    string *souls;

	if(str != "now")
	{
    	NF("Limp when?\n");
    	return 0;
	}
    
	if (TP->query_gender() != 0)
	{
		NF("Only males can be old fogeys, sorry.\n");
		return 0;
	}

	if(RACE != "hobbit" && RACE != "human" && RACE != "dwarf")
	{
		NF("Only hobbits, humans and dwarves can be Old Fogeys.\n");
		return 0;
	}

	write("You are now an Old Fogey!\n");
	write_file(FOGEY_LOG, TP->query_real_name() + " joined " + 
		extract(ctime(time()), 4, 15) + "\n");      

	seteuid(getuid(TO));
	cane = present("_fogey_cane_", TP);
	if (!cane)
	{
		clone_object(OBJ_DIR +"club/newcane")->move(TP,1);
		write("You get your cane from a nook in the tree.\n");
		say(QCTNAME(TP) + " becomes an Old Fogey.\n");
		return 1;
	}
    return 1;
}
 
int
do_hasty(string str)
{
    object cane;
    int result;
 

    if (str !="hasty")
    {
        NF("Become what ? Hasty ?\n");
        return 0;
    }

    if (this_player()->query_gender() != 0 &&
    RACE != "hobbit" && RACE != "human" && RACE != "dwarf")
    {
        NF("You aren't an Old Fogey!\n");
        return 0;
    }
    if (TP->remove_cmdsoul(FOGEY_SOUL))
    {
        write("Fine, go be hasty then! See if we care!\n");
        cane = present("_fogey_cane_", TP);
        if (cane)
        {
            cane->remove_object();
            write("Your cane disintegrates into dust!\n");
            say(QCTNAME(TP) + " leaves the Old Fogeys.\n");
		        write_file(FOGEY_LOG, TP->query_real_name() + " left " + 
			      extract(ctime(time()), 4, 15) + "\n");
        }
    
       TP->update_hooks();
    }
    else
	{
        NF("Are you sure you were a member in the first place?\n");
        return 0;
	}
}
 
int
do_cane(string str)
{
    object cane;

   if (str != "me")
        return 0;
    if (TP->query_gender() > 0 || RACE == "gnome" || RACE == "goblin" || RACE == "elf")
    {
        NF("Only Old Fogeys may cane themselves here.\n");
        return 0;
    }

    cane = present("_fogey_cane_", TP);

    if (cane)
    {
      NF("You already have one!\n");
        return 0;
    }
     clone_object(OBJ_DIR + "club/newcane")->move(TP,1);
     write("You grab a cane from one of the nooks in the tree.\n");
     say(QCTNAME(TP)+" grabs a cane from a tree-nook.\n");
     return 1;
}

