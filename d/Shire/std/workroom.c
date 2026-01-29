/*
 *  A Shire standard workroom for wizards
 *  Copyright (C) Chad Richardson  Feb 1997
 *  
 *  When you inherit this file you'll add a mailreader to whomever
 *  this workroom belongs to.  Also the room adds an exit to the Shire workroom
 */
inherit "/d/Shire/std/room";

#include "/d/Shire/common/defs.h"

static string gOwner = creator(this_object());

void
create_shire_workroom()
{
}

void
create_shire_room()
{
    set_short(gOwner +(extract(gOwner, -1) == "s" ? "'" : "'s")+ " Workroom");
    set_long("Workroom (long verson).\n");

    add_exit("/d/Shire/workroom","Shire","@@check_if_wiz@@");

    create_shire_workroom();
}

//   We clone a mailreader to the Owner of the Workroom
/*  Not nessacery since mailreaders are autoloadable for wizards.
void
init()
{
    ::init();

    if (TP->query_real_name() == gOwner && !present("_reader_", TP))
    {
	setuid(); seteuid(getuid());
	clone_object("/secure/mail_reader")->move(TP,1);
    }
}   
*/


//    To prevent mortals from entering certain areas
int
check_if_wiz()
{
    if (TP->query_wiz_level())
    {
	return 0;
    }
    write("You are forbidden to go that way!\n");
    return 1;
}
