/*
 * post.c
 *
 * Calathin post office.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

string window();

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
create_room()
{
    ::create_room();

    INSIDE;
    set_short("Calathin post office");
    set_long("The post office has small mail boxes along the east "+
        "and south walls. Here you may:\n"+
          "read            Read from the mailbox.\n" +
          "mail <name>     Mail to player 'name'.\n" +
          "from            List all headers.\n");

    add_item(({"wall","walls"}),"On each side of the " +
       "door are two large windows.\n");
   
    add_item(({"window","large window","large windows",
               "windows"}),"The large windows provide " +
               "light into the room.\n");

    add_cmd_item(({"window","through window","out window",
                  }),({"jump","climb"}), "@@window");

    door = clone_object(CALATHIN_DIR + "obj/post_door");
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


string
window()
{
    write("You jump out the window.\n");
       TP->move_living("jumping out the window", 
       CALATHIN_DIR + "square4_4",1,0);
       return "";
   }

