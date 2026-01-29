

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "defs.h"
#include WORSHIP_HEADER
#include COUNCIL_HEADER

#define MAILREADER "/secure/mail_reader"
#define MAILCHECKER "/secure/mail_checker"
#define FEATHER "/d/Calia/worshippers/objects/feather"
#define PIGEON "/d/Genesis/obj/pigeon"

string messages;
int new_mail;

int
query_prevent_snoop()
{
    return 1;
}

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}

int
collect(string str)
{
    object feather;
    int num;

    if (str != "feathers")
    {
        notify_fail("Collect feathers maybe?\n");
        return 0;
    }

    feather = clone_object(FEATHER);
    num = 3 + random(6);
    feather->set_heap_size(num);
    if (!feather->move(this_player()))
    {
        write("You quietly collect "+num+" feathers from the ground.\n");
        return 1;
    }

    write("You didn't manage to collect any feathers.\n");
    return 1;
}

int
hire(string str)
{
    object pigeon;

    if (str != "pigeon")
    {
        notify_fail("Hire pigeon perhaps?\n");
        return 0;
    }

    if (present("pigeon",this_player()))
    {
        notify_fail("Why would you need more than one pigeon?\n");
        return 0;
    }

    if (MONEY_ADD(this_player(),-24))
    {
        pigeon = clone_object(PIGEON);
        pigeon->move(this_player());
        write("You quietly hire a messenger pigeon.\n");
    }
    else
        write("Hmm, not enough money perhaps?\n");

    return 1;
}

void
init()
{
    object reader;

    ::init();

    add_action(hire, "hire");
    add_action(hire, "buy");
    add_action(collect, "collect");

    /*
      Disabling the mail functionality, Petros April 2015

    reader = clone_object(MAILREADER);
    if(!reader)
    {
        write("There appears to be no booths empty at this time.\n");
        return;
    }
    reader->set_alias("guildmaster",({"bishop"}));
    reader->set_alias("council", COUNCIL_CODE->query_council_members());
    reader->move(this_player());
    */
}


void
leave_inv(object ob, object to)
{
    object reader;

    ::leave_inv(ob);

    if (objectp(ob) && ob->query_wiz_level())
    {
        // Wizards shouldn't have their mail readers destroyed
        return;
    }

    /*
    if (reader = present("mailread", ob)) 
        reader->remove_object();
    */
}


int
query_mail(int silent)
{
    string new, sp;
    int mail;
    mail = MAILCHECKER->query_mail();
    if (!mail)
        return 0;

    if (silent) return 1;
    new = "";
    sp = "    ";
    if (mail>1)
    {
        new = " NEW";
        sp = "";
    }
    write("\n"+
        "    +------------------------------------------------------+\n"+
        "    !   There is"+new+" mail for you at the postal chamber.   "+sp+"!\n"+
        "    +------------------------------------------------------+\n");
    return 1;
}

void
create_room()
{
    set_short("Postal chamber");
    set_long("You have entered a small alcove here in the "+
        "temple. The grass is very short here, just barely "+
        "colouring the ground green. There are several small "+
        "booths along the southern wall. There is a skylight of sorts "+
        "in the ceiling through which you can see the bright sun "+
        "above you. This appears to be "+
        "a postal chamber of sorts, no longer in active use. To the east you see a "+
        "chamber with some beds in it.\n\n"+
        "You notice that pigeons are available for <hire> here, "+
        "at the cost of 24 coppers each. There are lots of "+
        "feathers on the ground.\n"+
        "");

    add_item(({"booth","booths"}),"The booths are seperated by "+
        "smooth rocks.\n");

    add_item("feathers","There are lots of them on the ground, "+
        "as one would expect because of all the pigeons. You "+
        "could try collecting them.\n");
    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(WOR_TEMPLE+"s_chamber","northeast",0,1);
    add_exit(WOR_TEMPLE+"startroom","east","@@check_worship",1);
}

int
check_worship()
{
    // Only worshippers and wizards can access the start room
    object player = this_player();
    if (player->query_wiz_level()
        || is_worship(player))
    {
        return 0;
    }

    write("A voice echoes through your mind: 'Only those who "+
        "follow the Elemental ways may pass.'\n");
    return 1;
}
