/*
 * /d/Gondor/rohan/edoras/npc/edoras_guard.c
 *
 * special edoras_soldier to guard Elfhelm.
 * only difference is code to make them go away when fighting over.
 * based on Elessar's ranger guards for the old ranger.
 *
 */
inherit "/d/Gondor/rohan/edoras/npc/edoras_soldier";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void	create_guard();
public void	test_fighting();

/*
 * Function name:	create_guard
 * Description	:	mask parent to set alarm for leaving again
 */
public void
create_guard()
{
    ::create_guard();
    default_config_npc(120);
    set_base_stat(SS_STR, 140);
    set_base_stat(SS_DEX, 135);
    set_base_stat(SS_CON, 145);
    add_name("_Rohirrim_guard");
    set_alarm(200.0, 0.0, test_fighting);
    add_prop(LIVE_I_SEE_DARK, 5);
} /* create_guard */

void
set_size(int n)
{
    default_config_npc(120 + (n * 10));
    set_base_stat(SS_STR, 140 + (n * 10));
    set_base_stat(SS_DEX, 135 + (n * 12));
    set_base_stat(SS_CON, 140 + (n * 10));
    set_skill(SS_WEP_SWORD, 90 + (n * 5));
    set_skill(SS_WEP_POLEARM, 90 + (n * 5));
    set_skill(SS_DEFENCE, 90 + (n * 5));
    set_skill(SS_PARRY, 90 + (n * 5));
}


/*
 * Function name:	test_fighting
 * Description	:	leave if fight is over
 */
public void
test_fighting()
{
    object	ob,
		env;
    if (!query_attack())
    {
        command("say " +
	    ONE_OF_LIST(({"I am heading out again.",
            "If there is more problems, just call out again.",
                 "I believe it's safe for me to leave now.",
		 "I will check by later!",})));
	if (file_name(env = ENV(TO)) == (EDORAS_DIR + "rooms/boffice2"))
	{
	    if (objectp(ob = find_living("elfhelm")))
	    {
		ob->set_guards_summoned(0);
	    }
            command("emote leaves east.");
	}
	else
	{
	    if (objectp(ob = present("hama", env)))
	    {
		ob->set_guards_summoned(0);
	    }
            command("emote leaves south.");
	}
        remove_object();
    }
    else 
    {
	set_alarm(200.0, 0.0, test_fighting);
    }
} /* test_fighting */


void
do_die(object killer)
{
    write_file("/d/Gondor/log/edoras_guard_kill", "Guard: Killed by " + 
	       killer->query_name() + " (" + 
	       killer->query_average_stat() + ") on " + ctime(time()) +
	       ".\n");  

    ::do_die(killer);
}

