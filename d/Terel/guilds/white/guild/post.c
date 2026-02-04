/*
 * post.c
 *
 * Post office of the Order of the White
 */

#include "/d/Terel/include/Terel.h"
inherit WHITE + "guild/keep_room";

object door;

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
create_terel_room()
{
    ::create_terel_room();

    INSIDE;
    set_short("a study in the library");
    set_long("You are in a small study in the library. "+
          "\n"+
          "\n" +
          "\n" +
          "\n");

  

    door = clone_object(WHITE + "guild/post_door");
    door->move(TO);
}

leave_inv(object from, object to)
{
    object reader;
    reader = present("mailread", from);
    if (reader)
       reader->remove_object();
    ::leave_inv(from, to);   
}



