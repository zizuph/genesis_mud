inherit "/d/Genesis/lib/post";
inherit "/std/room";
inherit "/d/Cirath/ak_wela/inherit/room_tell";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("Ak Wela message service");
    set_long("This is Ak Wela's message service. A templar stands by the "+
             "door conjuring mailreaders for people, which converts letters " +
             "to speech or speech to letters, as reading and writing is strictly " +
             "forbidden. He also reads the messages of the people so that they "+
             "do not contain any forbidden information.\n");
    
    add_exit(AK_WELA_DIR + "szun_moon8", "south", 0, 2);

    add_item("templar","The templar looks utterly bored, and has "+
             "no doubt been assigned postal duty as a punishment from "+
             "some higher ranked templar.\n");
  
}


void enter_inv(object what , object from)
{
	start_room_tells(what);
	::enter_inv(what,from);
}

void leave_inv(object what,object to)
{
	::leave_inv(what,to);
	post_leave_inv(what,to);
}

void init()
{
        ::init();
	post_init();

}
