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
    add_action("sign_scroll", "sign");
}

/*
 * Function name: reset
 * Description:   Reset the scroll
 */
 void
create_object()
{
    add_prop(OBJ_I_WEIGHT, 10); /* 10 g */
    add_prop(OBJ_I_VOLUME, 10); /* 10 ml */
    add_prop(OBJ_I_VALUE, 0); /* 0 copper */
    set_name("scroll");
    set_short("scroll");
    set_long("@@my_long");
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
"You may begin the quest for wizardhood. However the illustrous\n" +
"order of wizards only accepts loyal and secretive members. By\n" +
"signing this scroll you promise not to betray the secrets of\n" +
"the quest, and if you succeed on your quest, the secrets of\n" +
"the order.\n");
    else
	write("You can see no text on the scroll.\n");
    return 1;
}

/*
 * Function name: read_scroll
 * Description:   Read the text
 */
static int
sign_scroll(string str)
{
    if(!str || !id(str))
	return 0;
    if (this_player()->query_average_stat() >= 100)
	write("When you sign the scroll the text on it changes. Now it reads:\n" +
	      "To the thirteen wizards of fame you go\n" +
	      "Stones to their honour are raised you know\n" +
	      "Polishing the surface to you will tell\n" +
	      "The secrets that underneath them dwell\n" +
	      "Put all your wits into learning the code\n" +
	      "For it takes you to the wizards abode\n\n" +
	      "Underneath you can see, written in small letters:\n" +
	      "This scroll will self destruct in 15 seconds.\n");
    else
	write("You put your signature on the scroll.\n");

    call_out("to_dust", 15);
    return 1;
}

void
to_dust()
{
    object *ob_arr, ob;
    int sz;

    seteuid(getuid(this_object()));
    ob = clone_object("/d/Genesis/obj/wizquest/dust");

    ob_arr = all_environment(this_object());
    sz = sizeof(ob_arr);
    if (sz <= 2)
    {
	if (sz == 1)
	    tell_room(ob_arr[sz - 1],
		      "The scroll suddenly turns into dust, which slowly falls to the ground.\n");
	else
	    tell_object(environment(this_object()),
			"The scroll suddenly turns into dust, which slowly falls to the ground.\n");
    ob->move(ob_arr[sz - 1]);
    }
    else
	ob->move(environment(this_object())); /* Silent */

    remove_object();
    
}
