/* This is the main Traveller guild room. Here you can join, leave and list.  */

inherit "/lib/guild_support";
inherit "/std/room";
#include "/d/Roke/defs.h"
#include "/d/Roke/common/defs.h"
#include "/d/Roke/varl/atuan/cape/guild/default.h" 
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/d/Roke/common/qbits.h"
#include "/sys/macros.h"


string title;
object badge;
        object spells;
        int i;
        string *souls;

void
create_room()
{

    set_short("Travellers Room");
    set_long(BS("This is a large room, well lit by torches"
	+ " and a huge fire against the far wall. A number of"
	+ " chairs rest against the walls, and look very comfy."
	+ " A large sign hangs above the fireplace.",70));

    INSIDE;

    add_exit(CAPE + "guild/balcony", "south", 0);

    add_item(({"sign"}),"Here you can "
	+ "join or leave the Travellers guild. "
	+ "Use <enter> or <leave> guild. You can also do "
	+ "<update membership>. Members can"
	+ " receive a <badge> to allow others to"
	+ " join.\n");

    add_cmd_item("sign","read","Here you can"
	+ " join or leave the Travellers guild."
	+ "Use <enter> or <leave> guild. You can also do "
	+ "<update membership>. Members can"
	+ " receive a <badge> to allow others to"
	+ " join.\n");
}

void
init()
{
    ::init();
    add_action("join", "enter");
    add_action("my_leave", "leave");
    add_action("ask", "ask");
    add_action("list", "list");
    add_action("badge","badge");
    add_action("update","update");
}


join(str)
{
    object shadow,insignia;

    if(str == "guild")
    {
	
	if (TP->query_race_name() != "human")
	{
	    notify_fail("You are not human, you can't join.\n");
	    return 0;
	}

	if (!(badge = present("badge", TP))){
	    write("You have not been authorized, and cannot join.\n");
	    return 1;
	}
	
	if (TP->query_guild_member(GUILD_TYPE))
	{
	    notify_fail("You can't be a member of two racial guilds!\n");
	    return 0;
	}
	shadow = clone_object(GUILD_SHADOW);
	notify_fail("How odd. For some reason you cannot join us.\n");
	if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
			      GUILD_NAME)!=1)
	{
	    shadow->remove_object();
	    return 0;
	}
	TP->set_bit(TRAV_GROUP, TRAV_MEMBER);
	write("You are now a Traveller.\n");
	
	log_file("travellers",TP->query_real_name()+" joined "+
		 extract(ctime(time()),4,15)+".\n");
	
	
	if (badge = present("badge", TP)){
	    badge->remove_object();
	}

	TP->add_cmdsoul(TRAV_SOUL); 

        seteuid(getuid(TO));
        souls = TP->query_cmdsoul_list();
        for (i = 0; i < sizeof(souls); i++)
	    TP->remove_cmdsoul(souls[i]);
        TP->add_cmdsoul(TRAV_SOUL);
        for (i = 0; i < sizeof(souls); i++)
	    if (souls[i] != TRAV_SOUL)
		TP->add_cmdsoul(souls[i]);
	
	
	TP->update_hooks();
	
	insignia = present("insignia", TP);
	if (!insignia)
	{
	    insignia = clone_object(CAPE + "guild/insignia");
	    insignia -> move(TP);
	    write("You receive the Traveller insignia.\n");
	    say(QCTNAME(TP) + " joins the Travellers Guild.\n");
	}
	return 1;
    }
    return 0;
}

my_leave(str)
{
    object insignia;
    int result;
    object sould;
    


    if (str!="guild")
    {
        write("What do you wish to leave?\n");
        return 1;
    }
    
    if (this_player()->query_guild_name_race()!=GUILD_NAME)
    {
        notify_fail("You can't leave a guild you are not a member of.\n");
        return 0;
    }
    if (TP->remove_guild_race())
    {
        write("You are no longer a member of the Travellers Guild.\n");
        this_player()->clear_bit(TRAV_GROUP,TRAV_MEMBER);
        insignia = present("insignia", TP);
        if (insignia)
        {
            insignia->remove_object();
            write("Your insignia is taken from you.\n");
            say(QCTNAME(TP) + " leaves the guild.\n");
	    log_file("travellers",TP->query_real_name()+" left   "+
		     extract(ctime(time()),4,15)+".\n");
        }
        TP->remove_cmdsoul(TRAV_SOUL);
	TP->update_hooks();
    }
    else
        write("Because of an error, you remain with us.\n");
    return 1;
}

int
list()
{
    
    string str;

    str = this_player()->list_major_guilds();
    if (str)
        write("You are a member of the following guilds.\n" + str);
    else
        write("You are not a member of any important guilds.\n");
    
    return 1;
}

int
ask(string str)
{
    object insignia;

    if (str!="insignia" && str!="for insignia")
        return 0;
    if (TP->query_guild_name_race()!=GUILD_NAME)
    {
        write("But you are not a member of this guild. "
	      + "Only Travellers get an insignia.\n");
        return 1;
    }
    insignia = present("insignia", TP);
    if (insignia)
    {
        write("You already have an insignia.\n");
        return 1;
    }
    insignia = clone_object(ATUAN + "/cape/guild/insignia");
    insignia -> move(TP);
    write("You are presented a brand new insignia.\n");
    say("Somebody is given a new insignia.\n");
    return 1;
}

badge()
{
    if (IS_MEMBER(TP)){
	clone_object(CAPE + "obj/badge")->move(TP);
	write("You receive a badge of authorization.\n");
	return 1;
    }
    write("You are not a member.\n");
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
    ob->add_cmdsoul(TRAV_SOUL);
    for (i = 0; i < sizeof(souls); i++)
	if (souls[i] != TRAV_SOUL)
	    ob->add_cmdsoul(souls[i]);
    ob->update_hooks();
}

int 
update(string str)
{
    object shadow;

    if (!str || str != "membership")
    {
	notify_fail("Update what?\n");
	return 0;
    }

    if (!IS_MEMBER(TP) && TP->query_guild_name_race()!=GUILD_NAME)
    {
	write("You are not a member of this guild.\n");
	return 1;
    }
    
    if (!IS_MEMBER(TP))
    {
	write("Updating bit.\n");
	TP->set_bit(TRAV_GROUP, TRAV_MEMBER);
	if (TP->test_bit("Roke",2,19))
	    if (TP->query_guild_name_occ() != "Gladiator guild")
		TP->clear_bit(2,19);
    }

    if (TP->query_guild_name_race()!=GUILD_NAME)
    {
	write("Updating shadow.\n");
	shadow = clone_object(GUILD_SHADOW);
	if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
			      GUILD_NAME)!=1)
	{
	    write("Couldn't update your shadow. Please contact a wizard about this.+n");
	    shadow->remove_object();
	}
    }
    
    write("Done!\n");
    return 1;
}
