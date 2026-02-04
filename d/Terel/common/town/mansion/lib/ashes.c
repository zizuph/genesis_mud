inherit "/std/object.c";

#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)    break_string(message, 70)
#define TP              this_player
#define TO              this_object
#define MY "/d/Terel/mecien/valley/guild/quest/"

#define MAX_ASH         1

static int nash=1;
int 	key_gone_flag = 0;

void
init()
{
	::init();
	add_action("do_collect","collect");
}

int
do_collect(string str)
{
    object ob;
    
    seteuid(getuid(TO()));
    if (str=="ash" || str =="bit of ash"||str== "ashes")
    {
        ob = clone_object(MY + "ash");
        if (ob->move(TP()) || nash > MAX_ASH)
        {
            ob->remove_object();
            notify_fail("You failed to collect any of the ashes.\n");
            return 0;
        }
        TP()->catch_msg("You collect a bit of ash.\n");
        nash++;
        return 1;
    }
    
}

create_object()
{
	seteuid(getuid(TO()));
	set_name("ashes");
	set_short("large pile of ashes");
	set_long(BS("Obviously the remnants of a fire, built from the many books and bookshelves "
		+ "that used to array this once-opulent room. It is a sobering find; you can not help "
		+ "but think of how much knowledge has been lost to the desperate needs of a moment.\n"));

	add_prop(OBJ_I_VALUE,0);
	add_prop(OBJ_M_NO_GET,BS("Well, it's just a big heap of ashes...not really something "
	+ "you can pick up and carry around! Perhaps you could collect a "
	+ "bit of ash, though.\n"));
	add_prop(OBJ_S_WIZINFO,BS("Searching the ashes should turn up a key to the desk in the index room\n"));
	add_prop(OBJ_S_SEARCH_FUN,"do_search");
}

/* function name: do_search
 * if key_gone_flag is false, clones index_room_key.c and sets 
 * key_gone_flag to true..reset_object() will set key_gone to 
 * false again...if key_gone is true when they search, print an
 * encouraging message to let them know they're on the right track.
 */
string
do_search()
{
	object 	key;

	if (!key_gone_flag)
	{
		key_gone_flag = 1;
          key = clone_object(MANSION+"lib/index_room_key.c");
		if (key->move(TP()))	/* if it DOESN'T work, put it in the room */
			key->move(environment(TP()));
		return "You uncover and pick up a small brass key, hidden in the ashes!\n";
		say(QCTNAME(TP())+" finds something in the ashes.\n");
		
	}
	else
		return BS("You don't find anything, but the ashes have been "
		+ "recently disturbed...as if someone else had searched them.\n");
}

void
reset_nash()
{
    nash = MAX_ASH;
}

reset_object()
{
	key_gone_flag = 0;
    reset_nash();
}
