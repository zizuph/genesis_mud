// Old Fogey's club, borrowing from Vladimir and Dunstable's
// Smart Goblin club, Dunstable 12/94. 

inherit "/lib/guild_support";
inherit "/d/Shire/room";

#include "/d/Shire/sys/defs.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/sys/macros.h"
#include "/d/Shire/bits.h"

/* Prototypes */
int do_limp(string str);
int do_hasty(string str);
int do_cane(string str);

#define RACE this_player()->query_race_name()
#define FOGEY_LOG       "/d/Shire/log/fogeys"
#define FOGEY_SOUL      "/d/Shire/common/obj/club/fogey_soul"
#define OBJ_DIR         "/d/Shire/common/obj/"

string title;

void
create_room()
{
    set_short("Clearing with a tree");
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
      "either human, hobbit, halfling, or dwarven. Sorry, no goblins, elves or "+
      "gnomes! To join, type <limp now>, and you will begin the process "+
      "of becoming a true Old Fogey. Should you ever lose your cane, you "+
      "can get a new one by typing <cane me> here.  If you ever become hasty "+
      "and wish to be like the young folk again, type <become hasty> here.\n"+
      "Members may <start here>.\n");

    add_prop(ROOM_I_LIGHT, 2);
    add_exit("/d/Shire/common/gondorlink","southeast",0,1);
    reset_room();
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

    if(!(TP->test_bit("Shire",FOURTH_GROUP,FOGEY_BIT)))
    {
	write("You're not an Old Fogey! You can't do that!\n");
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
	write("Limp when?\n");
	return 0;
    }
    if (TP->query_gender() != G_MALE)
    {
	write("Only males can be old fogeys, sorry.\n");
	return 1;
    }

    if(RACE != "hobbit" && RACE != "human" && RACE != "dwarf" && RACE != "halfling")
    {
	write("Only halflings, humans, and dwarves can be Old Fogeys.\n");
	return 1;
    }

    if(TP->test_bit("Shire",FOURTH_GROUP,FOGEY_BIT))
    {
	write("You're already an Old Fogey!\n");
	return 1;
    }

    write("You are now an Old Fogey!\n");
    write_file(FOGEY_LOG, TP->query_name()+ " joined " +
      extract(ctime(time()), 4, 15) + "\n");      

    seteuid(getuid(TO));
    TP->set_bit(FOURTH_GROUP,FOGEY_BIT);
    cane = present("_fogey_cane_", TP);
    if (!cane)
    {
	cane = clone_object(OBJ_DIR +"club/cane");
	cane->move(TP,1);
	write("You get your cane from a nook in the tree.\n");
	say(QCTNAME(TP) + " becomes an Old Fogey.\n");
    }
    return 1;
}

int
do_hasty(string str)
{
    object cane;
    int result;
    object soul;

    if (str !="hasty")
    {
	write("Become what ? Hasty ?\n");
	return 1;
    }

    if(!(TP->test_bit("Shire",FOURTH_GROUP,FOGEY_BIT)))
    {
	write("You aren't an Old Fogey!\n");
	return 1;
    }
    write("Fine, go be hasty then! See if we care!\n");
    cane = present("_fogey_cane_", TP);
    if (cane)
    {
	cane->remove_object();
	write("Your cane disintegrates into dust!\n");
    }
    say(QCTNAME(TP) + " leaves the Old Fogeys.\n");
    write_file(FOGEY_LOG, TP->query_name()+" left "+
      extract(ctime(time()), 4, 15) + "\n");
    TP->clear_bit(FOURTH_GROUP,FOGEY_BIT);
    TP->remove_prop(LIMP_PROP);

    TP->remove_cmdsoul(FOGEY_SOUL);
    TP->update_hooks();

    return 1;
}

int
do_cane(string str)
{
    object cane;

    if (str != "me")
	return 0;

    if (!(TP->test_bit("Shire",FOURTH_GROUP,FOGEY_BIT)))
    {
	write("Only Old Fogeys may cane themselves here.\n");
	return 1;
    }

    cane = present("_fogey_cane_", TP);

    if (cane)
    {
	write("You already have one!\n");
	return 1;
    }
    cane = clone_object(OBJ_DIR + "club/cane");
    cane -> move(TP,1);
    write("You grab a cane from one of the nooks in the tree.\n");
    say(QCTNAME(TP)+" grabs a cane from a tree-nook.\n");
    return 1;
}

void
soul(object ob)
{
    int i;
    string *souls;

    seteuid(getuid(TO));
    souls = ob->query_cmdsoul_list();
    for (i = 0; i < sizeof(souls); i++)
	ob->remove_cmdsoul(souls[i]);
    ob->add_cmdsoul(FOGEY_SOUL);
    for (i = 0; i < sizeof(souls); i++)
	if (souls[i] != FOGEY_SOUL)
	    ob->add_cmdsoul(souls[i]);
    ob->update_hooks();
}


void
reset_room()
{
/*
    object birds_nest;

        if (!present("_shire_birds_nest_",TO))
    {
        birds_nest = clone_object("/d/Shire/scav_hunt/birds_nest");
        birds_nest->move(TO);
    }
*/
}
