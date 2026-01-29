/* 
 * /d/Ansalon/guild/society/room/po.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Kender Guild Post Office  
 * Gwyneth, June - September 1999 
 */
#include "/d/Ansalon/common/defs.h"
#include "../guild.h"
#include <macros.h>

inherit KENDERMORE_OUT;

#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"
#define KEN_GOT_TAGS "_ken_got_tags"

string messages, distraction;
int new_mail;
int feather_no = 0;

string borrow_feathers();
string long_descr();

void
create_room()
{
    set_short("A paper filled room");
    set_long(&long_descr());
    add_exit(KGROOM + "joinroom", "northeast", 0);
    add_exit(KGROOM + "courtyard", "east", 0);
    add_exit(KGROOM + "start", "south", 0);

    add_cmd_item("feathers", ({"borrow", "gather", "collect"}),
        &borrow_feathers());

    add_item(({"single table", "table"}), "It looks rather worn, " + 
        "having been exposed to the elements for quite a while. " + 
        "Paper, quills and ink lay scattered on the top.\n" +
        "Some nametags lie on a corner of the desk.\n");
    add_item("corner", "You " +
        "could probably get some nametags without anyone noticing.\n");
    add_item("top", "The table top is sturdy and covered with paper, " + 
        "quills and ink.\n");
    add_item(({"paper", "quills", "ink"}), "You can write letters " + 
        "with them.\n");
    add_item("roof", "The sky is your roof!\n");
    add_item(({"walls", "rough walls"}), "The walls don't look " + 
        "completely finished.\n");
    add_item("feathers", "They are scattered around on the ground. " + 
        "Perhaps you could borrow a few.\n");
}

void
reset_room()
{
    feather_no = 0;
}

string
borrow_feathers()
{
    switch(random(7))
    {
    case 0:
        distraction = "a sparkle in the corner";
        break;
    case 1:
        distraction = "a flash in the sky";
        break;
    case 2:
        distraction = "another kender running by";
        break;
    case 3:
        distraction = "something falling out of your pocket. Luckily you " + 
            "catch it and put it back";
        break;
    case 4:
        distraction = "the beautiful melody of a songbird";
        break;
    case 5:
        distraction = "a loud taunt coming from outside";
        break;
    case 6:
        distraction = "a loud crash from nearby";
        break;
    }

    if (feather_no)
    {
        return("You bend down to pick up a few feathers, but get distracted " + 
            "by " + distraction + ".\n");
    }

    say(QCTNAME(TP) + " bends down and picks something up from the ground, " + 
        "slipping it into " + HIS(TP) + " pocket.\n");
    clone_object(KOBJ + "w_feather")->move(TP);
    clone_object(KOBJ + "w_feather")->move(TP);
    clone_object(KOBJ + "w_feather")->move(TP);
    clone_object(KOBJ + "w_feather")->move(TP);
    feather_no = 1;
    return("You bend down and pick up a few feathers from the ground.\n");
}

string
long_descr()
{
    return(tod_descr() + season_descr() + " This room seems to have " + 
        "been half built. There is no roof, and the walls have a " + 
        "rough look to them. A single table decorates this room. Here " + 
        "you can write and send letters.\n");
}

int
get_tag(string str)
{
    object tag;

    if(!strlen(str))
        return 0;

    if(!parse_command(str, ({ }), "'nametag' / 'nametags' / 'tag' / " +
        "'tags' [from] [the] [single] [table]"))
        return 0;

    if(TP->query_prop(KEN_GOT_TAGS))
    {
        write("You've already taken plenty of nametags.\n");
        return 1;
    }

    write("You quietly take some nametags from the table.\n");
    tag = clone_object(KGOBJ + "nametag");
    tag->set_owner(TP);
    tag->move(TP);
    tag = clone_object(KGOBJ + "nametag");
    tag->set_owner(TP);
    tag->move(TP);
    tag = clone_object(KGOBJ + "nametag");
    tag->set_owner(TP);
    tag->move(TP);

    if(!TP->query_wiz_level())
        TP->add_prop(KEN_GOT_TAGS, 1);

    if(TP->query_kender_level_occ() > 3)
    {
        tag = clone_object(KGOBJ + "nametag");
        tag->set_owner(TP);
        tag->move(TP);
    }
    if(TP->query_kender_level_occ() > 7)
    {
        tag = clone_object(KGOBJ + "nametag");
        tag->set_owner(TP);
        tag->move(TP);
    }
    if(TP->query_kender_level_occ() > 10)
    {
        tag = clone_object(KGOBJ + "nametag");
        tag->set_owner(TP);
        tag->move(TP);
    }
    if(TP->query_kender_level_occ() > 15)
    {
        tag = clone_object(KGOBJ + "nametag");
        tag->set_owner(TP);
        tag->move(TP);
    }
    return 1;
}

void
init()
{
    object mr;

    ::init();
    if (!this_player()->query_wiz_level())
    {
        mr = clone_object("/secure/mail_reader");
        mr->move(TP, 1);
    }

    add_action(get_tag, "get");
}

void
leave_inv(object ob, object to)
{
    object reader;

    ::leave_inv(ob, to);
    reader = present(MAILREADER_ID, ob);

    if (reader &&
      !this_player()->query_wiz_level())
    {
	reader->remove_object();
    }
}

int
query_mail(int silent)
{
    string new;
    int mail;

    mail = MAILCHECKER->query_mail();

    if (!mail) return 0;

    if (silent) return 1;

    new = "";
    if (mail == 2) new = " NEW";
    if (mail == 3) new = " unread";

    write("\n" +
      "There is" + new + " mail for you in the " +
      "nearest post office.\n\n");

    return 1;
}

void
remove_ex_members(object who)
{
    if (present(who, this_object()))
    {
        who->catch_tell("A very large looking kender enters the room and " +
            "escorts you out of the guild.\n");
        say("A very large looking kender enters the room and escorts " +
            QTNAME(who) + " out of the guild.\n");
        tell_room(KGROOM + "joinroom", QCTNAME(who) + " is escorted out " +
            "of the guild by a very large looking kender.\n");
        who->move_living("M", KROOM + "joinroom", 0, 0);
        return;
    }
    return;
}

