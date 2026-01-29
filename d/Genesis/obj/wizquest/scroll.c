/*  
   This is a special scroll that can be found by players. It indicates
   what you have to do to solve the wizard quest.
*/
#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

/*
 * Function name: init
 * Description:   Initialize commandverbs
 */
public void
init()
{
    add_action("read_scroll", "read");
}

void
create_object()
{
    add_prop(OBJ_I_WEIGHT, 10); /* 10 g */
    add_prop(OBJ_I_VOLUME, 10); /* 10 ml */
    add_prop(OBJ_I_VALUE, 0); /* 0 copper */
    add_prop(OBJ_M_NO_DROP, "@@slow_drop@@");
    set_name("scroll");
    set_short("scroll");
    set_long("@@my_long");
}

int
slow_drop()
{
    add_prop(OBJ_M_NO_GET, "There is no reason to get the scroll.\n");

    set_alarm(1.0, 0.0, "slow_destruct");

    return 0;
}

void
slow_destruct()
{
    if (living(environment()))
    {
	return;
    }

    tell_room(environment(),
	"The scroll self-destructs and evaporates completely.\n");

    remove_object();
}

string
my_long()
{
    return "A scroll made of finest linen.\n" +
	(this_player()->query_average_stat() >= 100 ?
	 "It is written in beautiful script with red ink.\n" :
	 "It appears to be empty.\n");
}


/*
 * Function name: read_scroll
 * Description:   Read the text
 */
static int
read_scroll(string str)
{
    if(!str || !id(str))
	return 0;
    if (this_player()->query_average_stat() >= 100)
	write(
"You may now apply for wizardhood. You do that making a formal\n" +
"application on the board in the room to the east of the bottom\n" +
"room in the tower of Realms.\n" +
"\n" +
"You will not be able to read the board, but you can make a posting\n" +
"on it. Specify clearly why you want to become wizard and leave your\n" +
"name as well as email address, if you have one. You will be contacted\n" +
"directly or by mail as soon as the archwizard council has time.\n");
    else
	write("You can see no text on the scroll.\n");
    return 1;
}
