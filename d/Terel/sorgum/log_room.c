#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public int do_read(string str);

#define MORE_OBJ    "/std/board/board_more"


/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
	::init();
	add_action(do_read,"read");
}

/*
 * Function name: do_read
 * Description:   Handle the read action
 * Returns:       1/0
 */
public int
do_read(string str)
{
    FIX_EUID;
    if (str == "log") {
	say(QCTNAME(TP)+" reads the log.\n");;
	clone_object(MORE_OBJ)->more(SORGUM_DIR + "open/balance.950806", 1);
	return 1;
    }
    else {
	NF("Read what?  You want 'read log'?\n");
	return 0;
    }
}

create_room()
{
    set_short("empty room");
    set_long("This empty room was created so that you could read " +
	     "the log from the balance meeting (with the command " +
	     "'read log')\n");
    add_exit("/d/Terel/common/town/t_hall", "hall", 0);
}

    
    
