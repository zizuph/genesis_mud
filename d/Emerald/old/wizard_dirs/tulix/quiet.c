/* This room attempts to keep players from executing noisy commands. */
/* Coded by Tulix 26/09/96. This room uses code from the chair in    */
/* the examples.                                                     */

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/tulix/t_defs.h"

/* Some handy defines to make things easier */
#define SOCIAL "/cmd/live/social"
#define STATE  "/cmd/live/state"
#define INFO   "/cmd/live/info"
#define THINGS "/cmd/live/things"

/* Prototype functions */
public int no_command();
public int do_all_commands(string str);

public void
create_room()
{
    set_short("A quiet room");
    set_long("This is a quiet room. Wizards can do what they want in " +
        "here, but mortals cannot do much to disturb them, such as " +
        "speak, or use guild emotes. At least, that is the theory.\n");
    
    add_prop(ROOM_I_INSIDE, 1);
}

public void
init()
{
    ::init();
    add_action("do_all_commands" , "", 1);    
}

/*
 * Function name:   do_all_commands
 * Description:     check to see if player can use a particular command
 * Arguments:       string str: arguements to the command
 * Returns:         1 if command is not allowed, 0 otherwise.
 */
public int
do_all_commands(string str)
{
    int i;    

    string verb;
    string *not_allowed, *soul_list;
    mapping command_mapping;

    /* Wizards can do as they please, naturally. */
    if (TP->query_wiz_level())
        return 0;
       
    /* First we check for commands which are specifically banned. */
    not_allowed=({"say","introduce"});

    verb = query_verb();

    if (member_array(verb, not_allowed) == -1)
        return 0;
    else 
        return no_command();
    
    /* These souls contain commands which are mostly allowable */
    soul_list = ({ SOCIAL, STATE, INFO, THINGS });

    for (i = 0; i < sizeof(soul_list); i++)
    {
        command_mapping = find_object(soul_list[i])->query_cmdlist();
        if (command_mapping[verb] > " ")
            return 0; /* If the command is in the mapping, allow it. */
    }

    /* Do not allow the command if it was not in the above souls. */
    return no_command();

    return 1; /* Should never happen. */ 
}
     
public int
no_command()
{
    write("Alas, that is not possible in here.\n");
    return 1;
}
