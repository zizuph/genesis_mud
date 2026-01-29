/*
 * /d/Gondor/pelargir/npc/pelargir_guard.c
 *
 * special pelargir_soldier to guard carastur, londhir.
 * only difference is code to make them go away when fighting over.
 * based on Elessar's ranger guards for the old ranger.
 *
 */
inherit "/d/Gondor/pelargir/npc/pelargir_soldier";

#include <macros.h>
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
    add_name("_pelargir_guard");
    set_alarm(200.0, 0.0, test_fighting);
    add_prop(LIVE_I_SEE_DARK, 5);
} /* create_guard */


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
                 "I believe it's safe for me to leave now.",
		 "I will check by later!",})));
	if (file_name(env = ENV(TO)) == (PELAR_DIR + "misc/pel_office"))
	{
	    if (objectp(ob = present("carastur", env)))
	    {
		ob->set_guards_summoned(0);
	    }
            command("emote leaves south.");
	}
	else
	{
	    if (objectp(ob = present("londhir", env)))
	    {
		ob->set_guards_summoned(0);
	    }
            command("emote leaves east.");
	}
        remove_object();
    }
    else 
    {
	set_alarm(200.0, 0.0, test_fighting);
    }
} /* test_fighting */
