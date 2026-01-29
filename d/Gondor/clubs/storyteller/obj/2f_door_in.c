/*
 * /d/Gondor/clubs/storytellers/obj/2f_door_in.c
 */
inherit "/std/door";
#include "/d/Gondor/defs.h"
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

void
create_door()
{
    set_short("polished cherrywood door");
    set_door_id("2nd_floor_door");
    set_pass_command(({"w","west"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(STORYT_DIR + "rooms/shallway");
    set_door_desc("The large door is made of polished wood. It leads "
      + "out of the private section of the club.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_key("_StoRyTelLer_kEy_");
}

void
give_close_message(object ob)
{
    tell_room(other_room, QCTNAME(ob)+" closes and locks the "+
	    short() + " behind " + ob->query_objective() + "self.\n", 
	    ob);
    tell_room(environment(this_object()), "The " +short() +" closes, and you "+
	    "hear a faint 'click' from the lock being thrown.\n");
    ob->catch_tell("You close and lock the "  + short() + " behind you.\n");
}

/*
 * Function name: pass_door
 * Description:   Pass the door.
 * Arguments:     arg - arguments given
 */
int
pass_door(string arg)
{
    int dexh;
    string verb;

    verb = query_verb();

    if (!other_door)
        load_other_door();

    if (IS_STORYTELLER(this_player()))
    {
        if (lock_status)
        {
            write("You unlock, then open, the " + short() + ".\n");
            tell_room(environment(this_object()),
                      QCTNAME(this_player()) +
                      " unlocks, then opens, the " +
                      short() + ".\n", this_player());
	    tell_room(other_room, "You hear a faint 'click' from the lock "+
		"and the " + short() + " swings open.\n");
        }
        else if (open_status)
        {
            write("You notice the " + short() +" is standing wide open.\n");
	}
        else if (!lock_status)
        {
            write("You notice the " + short() +" is not locked as you open it.\n");
	    tell_room(environment(this_object()),
		QCTNAME(this_player())+" opens the door.\n");
            tell_room(other_room, "The " + short() + " swings open.\n");
	}
           
        set_alarm(0.0, 0.0, &give_close_message(this_player()));
        this_player()->move_living(verb, other_room, 1);

        if (open_status)
	{
	    do_close_door("");
	    other_door->do_close_door("");
	}

        if (!lock_status)
	{
        do_lock_door("");
	    other_door->do_lock_door("");
	}

        return 1;
    }

    /*
        The times higher a player can be and still get through
    */
    dexh = 2 + (this_player()->query_stat(SS_DEX) / 25);

    if (open_status)
    {
        /* Lets say we arbitrarily can bend as dexh indicates.
           For something else, inherit and redefine.
         */
        if ((int)this_player()->query_prop(CONT_I_HEIGHT) > 
                        query_prop(DOOR_I_HEIGHT) * dexh) 
        {
            write("The " + door_name[0] + " is more than " + 
                  LANG_WNUM(dexh) + " times lower than you.\n" +
                  "You're too tall and " +
                  "not enough dexterous to get through.\n");
            return 1;
        }
        else if ((int)this_player()->query_prop(CONT_I_HEIGHT) > 
                        query_prop(DOOR_I_HEIGHT))
        {
            write("You bend down to pass through the " + short() + ".\n");
            tell_room(environment(this_object()),
                      QCTNAME(this_player()) +
                      " bends down to pass through the " +
                      short() + ".\n", this_player());
        }

        this_player()->move_living(verb, other_room);
    }
    else
        write(check_call(fail_pass));

    return 1;
}
