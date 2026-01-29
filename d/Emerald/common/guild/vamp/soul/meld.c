/* meld.c created by Shiva@Genesis.
 * This file contains the code for the "earthmeld" command.
 * This is part of the vampire guild soul.
 */

#include "../guild.h"
#include "abilities.h"
#include <macros.h>
#include <tasks.h>

#define ROOM_I_EARTH_FLOOR "_room_i_earth_floor"

public int earthmeld2(object meld_cont, object where);

static mixed
earthmeld(string arg)
{
    object env, meld_cont;
  
    if (strlen(arg))
    {
        return CMD_SYNTAX_FAILURE;
    }
  
  

    if (this_player()->query_attack())
    {
        notify_fail("You can't manage it while in the middle of combat.\n");
        return CMD_SYNTAX_FAILURE;
    }
  
  
    if (MASTER_OB(env = environment(this_player())) == MELD_CONT)
    {
    	write("You are already deep within the earth.\n");
    	return CMD_FAIL_WITHOUT_COST;
    }
  
    if (!levels_test())
    {
	return CMD_FAIL_WITHOUT_COST;
    }
  
    if (QP(env, ROOM_I_INSIDE) && !QP(env, ROOM_I_EARTH_FLOOR))
    {
    	write("You can't seem to penetrate the surface.\n");
    	return CMD_FAIL_WITH_COST;
    }
  
    setuid();
    seteuid(getuid());
    if (!(meld_cont = clone_object(MELD_CONT)))
    {
    	write("Your powers mysteriously fail you.\n");
    	return CMD_FAIL_WITHOUT_COST;
    }
  
    allbb(" lies down upon the ground, " +  POS(this_player()) +
	" body seeming to dissolve into the earth.\n");
    write("You lie down upon the ground, your body beginning to meld " +
	"with the hard earth beneath.\n");
  
    return &earthmeld2(meld_cont, env);
}

int earthmeld2(object meld_cont, object where)
{
    object sh;
  
    if (environment(this_player()) != where)
    {
    	meld_cont->remove_object();
    	return 0;
    }

    if (!IS_WIZ(this_player()) && (sh = this_player()->query_vamp_shadow()) &&
	this_player()->resolve_task(TASK_ROUTINE - 150 -
	SUNLIGHT_DAMAGE(this_player()->query_sunlight_level()),
	(&operator(-)(, this_player()->query_thirst_modifier()) @ 
	&sh->query_vamp_stat())) <= 0)
    {
    	write("You can't seem to focus your power sufficiently.\n");
    	meld_cont->remove_object();
    	return 0;
    }

    meld_cont->earthmeld(this_player());
    return 1;
}

int
stop_earthmeld(object who)
{
    if (query_cmd_in_progress(who, "vmeld"))
    {
        who->catch_tell("Ok.\n");
        stop_vamp_cmd_execution(who);
        return 1;
    }

    notify_fail("You aren't earthmelding, though!\n");
    return 0;
}

int
break_earthmeld(object who)
{
    who->catch_tell("Your concentration is broken; you cannot earthmeld.\n");
    return 1;
}
