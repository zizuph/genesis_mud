/*
 * dpost.c
 *
 * Dabaay's post office.
 * Goldberry July, 1999
 */

#include "/d/Terel/include/Terel.h"
#define DAB_TOWN DABAAY_DIR + "town/"

inherit DAB_TOWN + "town_room";

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
    set_short("Dabaay's Post Office");
    set_long(
        "A rustic shack which, judging from the various piles of letters " +
        "and the lazy feel of the place, must be the local post office.\n"+
        " You may:\n" +
        " read            Read from the mailbox.\n" +
        " mail <name>     Mail to player 'name'.\n" +
        " from            List all headers.\n");

    add_exit(DAB_TOWN + "square2_4", "north", 0);
    add_exit(DAB_TOWN + "square3_1", "east", 0);
}

leave_inv(object from, object to)
{
    object reader;
    reader = present("mailread", from);
    if (reader)
       reader->remove_object();
    ::leave_inv(from, to);   
}
