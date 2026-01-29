
/*
 * post_office.c
 *
 * Post office for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/d/Genesis/lib/post";

#include <stdproperties.h>
#include <macros.h>
#include <mail.h>

#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

#define MAILREADER "/secure/mail_reader"
#define MAILCHECKER "/secure/mail_checker"

string messages;
int new_mail;

int
query_prevent_snoop()
{
    return 1;
}

void
create_room()
{
    set_short("Post office");
    set_long("You are in the postal chamber in the temple. This "+
        "chamber has many lamps lining the walls to brightly "+
        "light the entire area. There are several small booths "+
        "for people to enter and use the postal services that are "+
        "offered here. There is a small sign on the wall right near "+
        "the door where you entered.\n");

    add_item(({"wall","walls"}), "The walls are smooth to the touch "+
        "and painted bright white. There are several lamps lining "+
        "the walls.\n");
    add_item(({"lamp","lamps"}), "There are several lamps placed "+
        "all around the entire chamber so that there is sufficient "+
        "lighting for reading and writing.\n");
    add_item(({"booth","booths","small booths"}),"There are several small "+
        "booths here for people to enter and use the postal services "+
        "that are offered here. Each booth contains paper, a quill and "+
        "a bottle of ink.\n");
    add_item("paper", "You see paper in each of the booths.\n");
    add_item("quill", "You see a feather quill in each of the booths.\n");
    add_item(({"ink","bottle of ink","ink bottle"}), "You see a bottle of "+
        "ink in each of the booths.\n");
    add_item("floor", "The floor and ceiling are both constructed "+
      "with a grey stone and then smoothed and polished afterwards.\n");
    add_item("ceiling", "The floor and ceiling are both constructed "+
      "with a grey stone and then smoothed and polished afterwards.\n");
    add_item(({"sign","small sign"}),"The small sign on the wall "+
        "near the door where you entered reads:\n"+
        "The commands available here are:\n"+
        "   read             Read your mail.\n"+
        "   mail <name>      Mail to player 'name'.\n"+
        "   from             List all headers.\n"+
        "\n"+
        "If you wish to mail the council, you can do so by sending "+
        "mail to 'council', or if you wish the guildmaster to see "+
        "the mail, you can send it to 'guildmaster'.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");
    
    add_exit(SPIRIT_TEMPLE+"antechamber","north",0,1);
}

int
do_read(string str)
{
    if (!str)
    {
        NF("Read what? The sign? <read sign>\n");
        return 0;
    }

    if (str != "sign")
    {
        NF("Read what? The sign? <read sign>\n");
        return 0;
    }

    write("The small sign on the wall "+
        "near the door where you entered reads:\n"+
        "The commands available here are:\n"+
        "   read             Read your mail.\n"+
        "   mail <name>      Mail to player 'name'.\n"+
        "   from             List all headers.\n"+
        "\n"+
        "If you wish to mail the council, you can do so by sending "+
        "mail to 'council', or if you wish the guildmaster to see "+
        "the mail, you can send it to 'guildmaster'.\n");
    return 1;
}

int
do_enter()
{
    write("You do not need to enter a booth to read or write mail.\n");
    return 1;
}

void
init()
{
    object reader;

    ::init();

    add_action(do_enter, "enter");
    add_action(do_read, "read");
        
    reader = clone_object(MAILREADER);
    if(!reader)
    {
        write("There appears to be no booths empty at this time.\n");
        return;
    }
    reader->set_alias("guildmaster",({"jaacar"}));
    reader->set_alias("council", COUNCIL_CODE->query_council_members());
    reader->move(this_player(),1);    
}


void
leave_inv(object ob, object to)
{
    object reader;

    ::leave_inv(ob);

    if (reader = present("mailread", ob))
    {
        if (!(ob->query_wiz_level()))
        {
            reader->remove_object();
        }
    }
}

void
mail_message(string new)
{
    write("\nYou have" + new + " mail for you in the " + SPIRIT_GUILD_NAME +
        " post office.\n\n");
}

int
query_mail(int silent)
{
    string new;
    int mail;
    mail = MAILCHECKER->query_mail();
    if (!mail)
        return 0;

    if (silent) 
        return 1;
    
    new = "";
    
    if (mail>1)
    {
        new = " NEW";
    }
    
    write("             **####**            \n"+                       
          "          *##        ##*         \n"+
          "       *##    .-~~-.    ##*      \n"+
          "     *##    ,\",-\"\"-.\".    ##*    \n"+
          "   *##     | |      | |     ##*  \n"+
          "  *##    .-\"~~.  .-\"| |.     ##*        You have"+new+" mail\n"+
          " *##   ,\",-\"~- `\",-\" ,'.\".    ##*       waiting for you at\n"+
          " *##  | |     | |_,-'   | |   ##*       the postal chamber.\n"+
          " *##  | |     | |       | |   ##*\n"+
          "  *## \". `-._,\". `-._,-' .\"  ##* \n"+
          "   *##  `-.__,- `-.___,-'   ##*  \n"+
          "     *##                  ##*    \n"+
          "       *##              ##*      \n"+
          "          *##        ##*         \n"+
          "             **####**            \n"+
          "\n");
    return 1;
}
