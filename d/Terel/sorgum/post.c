/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * post.c
 *
 * Calathin post office.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: init
 * Description:   Get the player a mailreader.
 */
public void
init()
{
    ::init();
    clone_object("/secure/mail_reader")->move(TP, 1);    
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();

    INSIDE;
    set_short("Calathin post office");
    set_long("The post office is still under construction, but even so, " +
	     "you may:\n" +
	     "read            Read from the mailbox.\n" +
	     "mail <name>     Mail to player 'name'.\n" +
	     "from            List all headers.\n");
}

leave_inv(object from, object to)
{
    object reader;
    reader = present("mailread", from);
    if (reader)
	reader->remove_object();
    ::leave_inv(from, to);   
}
