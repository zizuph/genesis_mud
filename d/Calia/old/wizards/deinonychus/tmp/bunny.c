/* 	this is an easter bunny :-)

    coder(s):   Deinonychus

    purpose:    fun

    weapons:    none
    armours:    none

    objects:    eggs

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/monster";
#include <stdproperties.h>
#include <macros.h>

#define EGG "/d/Dville/deinonychus/tmp/intact_egg"

create_monster()
{

    /* descritpion */

    set_name("easter-bunny");
    set_race_name("bunny");

    set_short("easter-bunny");
    set_pshort("easter-bunnies");
    set_long(break_string("How cute, an Easter-bunny. On its back it's " +
	"wearing a bag with colored Easter-eggs in it. Taking an egg " +
	"from its bag would surely make it happy. =;-)\n",70));

    set_gender(2);

    set_alignment(1000);

    /* stats and skills */

    default_config_npc(7);

    /* actions */

    set_random_move(15);

}

void
init_living()
{
    add_action("take", "take");
    add_action("take", "get");
}

int
take(string what)
{
    object egg, bunny;
    string of_what;
    int result;

    if(parse_command(what, environment(this_player()),
	" 'egg' 'from' [bag] [of] %o", bunny))
    {
        if(bunny == this_object())
        {
	    seteuid(getuid());
            egg = clone_object(EGG);
            egg->move(this_player());
            write("You take an egg from the bag of the Easter-bunny.\n");
            say(QCTNAME(this_player()) + " takes an egg from the bag of " +
                "the Easter-bunny.\n", this_player());
            return 1;
        }
        else
	{
	    notify_fail("Take egg from bag of what?\n");
	    return 0;
	}
    }
    else
    { 
	notify_fail("Take what?\n");
	return 0;
    }
}

/*
 * Function name:
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
