/*
 *  /d/Gondor/clubs/nisse/obj/scroll.c
 *
 *  The message from the Nisse Ohtar trainer (Neit). It is delivered always
 *  when a member is ready to challenge the trainer.
 *
 *  Deagol, March 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

/*
 *  Global variables
 */
string	text =
    "\t  __________________________________________________________\n" +
    "\t /_\\                                                        \\\n" +
    "\t//_\\|                                                        |\n" +
    "\t|\\_/___-_____-______/|______--___|\\_____-_____-__|\\___/\\____/\n" +
    "\t \\                                                         \\\n" +
    "\t  |                                                         |\n" +
    "\t  |    Greetings Sister!                                    |\n" +
    "\t  |                                                         |\n" +
    "\t  |    I consider your disposition worthy to spar with      |\n" +
    "\t  |    me. Please, visit me in the Nisse Ohtar camp and     |\n" +
    "\t  |    challenge me whenever you are ready.                 |\n" +
    "\t  |                                                         |\n" +
    "\t  |    Blessed be the winds of battle!                      |\n" +
    "\t  |                                                         |\n" +
    "\t  |    Regards,                                             |\n" +
    "\t  |    Neit, the trainer of Nisse Ohtar                     |\n" +
    "\t  |                                                         |\n" +
    "\t /                                                          /\n" +
    "\t/___ ____  ________ _______________  _____________ _______/\n" +
    "\t|/\\ -    |/        -               |/             -        \\\n" +
    "\t\\\\_|                                                        |\n" +
    "\t \\/_________________________________________________________/\n\n";

/*
 *  Prototypes
 */
string	long_desc();

void
create_object()
{
    ::create_object();

    set_name("scroll");
    set_adj("ornamented");
    set_short("ornamented scroll");
    set_long(&long_desc());
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

/*
 *  Function name: long_desc
 *  Description  : Gives a long description of this object. 
 */
string
long_desc()
{
    return text;
}

/*
 *  Function name: read_scroll
 *  Description  : Read the text on this scroll.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0/1
 */
int
read_scroll(string str)
{
    if (str != "scroll" && str != "ornamented scroll")
    {
        notify_fail("Read what?\n", 0);
        return 0;
    }
    
    write(text);
    return 1;
}

/*
 *  Function name: destruct_me
 *  Description  : Destructs this object.
 */
void
destruct_me()
{   
    object room;

    if (living(room = environment()))
    {
        room = environment(room);
    }

    tell_room(room, "The scroll blows away with the wind.\n");
    remove_object();
}

/*
 *  Function name: leave_env
 *  Description  : Calls destruct me routine when this object leaves the
 *                 inventory of the player.
 *  Arguments    : object from - the environment we are leaving
 *                 object to   - the environment we are entering
 */
void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    if (env)
    {
        set_alarm(0.5, 0.0, destruct_me);
    }
}

void
init()
{
    ::init();

    add_action(read_scroll, "read");
}
