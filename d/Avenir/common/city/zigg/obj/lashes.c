// file name: ~lashes.c
// creator(s): Zielia
// last update:
// purpose: Object cloned by ~mascara.c, applies a subloc to a mortal
//     making her appear to have eyelashes. Adds emotes for the eyelashes.
// note: Also works with eyes from /d/Calia/gelan if the player has them.
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <adverbs.h>
#include "zigg.h"

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(({"eyelashes", "Zig::lashes"}));

    add_prop(OBJ_I_NO_DROP, 1);
}

public void
enter_env(object to, object from)
{
    object ob = present(EYES_NAME, to);

    ::enter_env(to, from);

    if (!objectp(ob))
    {
        ob = clone_object(EYES_OBJ);
        ob->move( to );
    }

    ob->add_ref("lashes");
}

/*  In case object is removed, makes sure subloc is removed first,       *
 *  and Calia eyes subloc replaced if applicable.                        */

public void
remove_object(void)
{
    if (IS_CLONE)
    {
	object ob = present(EYES_NAME, ENV());
	ob->rem_ref("lashes");
    }

    ::remove_object();
}

public int
do_remove(string str)
{
    if (TP != environment(TO))
	return 0;

    if (!strlen(str))
	return 0;

    if (str == "mesdemet" | str == "mascara")
    {
        if (TP->query_gender() == G_MALE)
        {
            write("You remove your mesdem and feel less smoulderingly "+
                "handsome.\n");
	        say(QCTNAME(TP)+" removes "+ HIS(TP) +" mesdemet and "+
                "isn't as smoulderingly handsome without it.\n");
				 
        }				 
		else
        {
	        write("You remove your mesdemet and feel less glamorous.\n");
     	    say(QCTNAME(TP)+" removes "+ HIS(TP) +
	            " mesdemet and looks a little less glamorous.\n");
        }
	set_alarm(0.0, 0.0, remove_object);
	return 1;
    }
}

public int
bat(string str)
{
    object *oblist;

    string *how = parse_adverb_with_space(str, "coyly", 1);

    oblist = parse_this(how[0], "[at] [the] %l",
	ACTION_VISUAL | ACTION_INGRATIATORY);

    if (!stringp(how[0]))
    {        
        if (TP->query_gender() == G_MALE)
        {
            how = parse_adverb_with_space(str, "coyly", 0);			   			
            write("You bat your smouldering dark eyelashes" + how[1] + ".\n");
            allbb(" bats "+ HIS(TP) +" smouldering dark eyelashes"+ how[1] + ".",
    	        how[1], ACTION_VISUAL | ACTION_INGRATIATORY );
    	}
        else
        {		
            how = parse_adverb_with_space(str, "coquettishly", 0);
	        write("You bat your long, dark eyelashes" + how[1] + ".\n");
    	    allbb(" bats "+ HIS(TP) +" long, dark eyelashes"+ how[1] + ".",
    	        how[1], ACTION_VISUAL | ACTION_INGRATIATORY );
        }
    	return 1;
    }

    if (sizeof(oblist) != 1)
    {
	notify_fail("Bat your eyelashes [how] at whom?\n");

	return 0;
    }

    if (TP->query_gender() == G_MALE)
    {
    actor("You bat your smouldering dark eyelashes" + how[1] + " at", oblist,".");

    all2actbb(" bats "+ HIS(TP) +" smouldering dark eyelashes"+ how[1] +
      " at", oblist,".", how[1], ACTION_VISUAL | ACTION_INGRATIATORY );

    targetbb(" bats "+ HIS(TP) +" smouldering dark eyelashes"+ how[1] +
      " at you.", oblist, how[1], ACTION_VISUAL | ACTION_INGRATIATORY );
    }
    else	
	{
    actor("You bat your long, dark eyelashes" + how[1] + " at", oblist,".");

    all2actbb(" bats "+ HIS(TP) +" long, dark eyelashes"+ how[1] +
      " at", oblist,".", how[1], ACTION_VISUAL | ACTION_INGRATIATORY );

    targetbb(" bats "+ HIS(TP) +" long, dark eyelashes"+ how[1] +
      " at you.", oblist, how[1], ACTION_VISUAL | ACTION_INGRATIATORY );
    }
    return 1;
}

public int
do_blink(string str)
{
    if (stringp(str))
    {
	notify_fail("Blink how?\n");
	return 0;
    }

    if (TP->query_gender() == G_MALE)
	{
    write("You blink your smouldering darkly-lashed eyes in disbelief.\n");
    allbb(" blinks "+ HIS(TP) +" smouldering darkly-lashed eyes in disbelief.", "",
      ACTION_VISUAL);
	}
    else
    {		
    write("You blink your darkly-lashed eyes in disbelief.\n");
    allbb(" blinks "+ HIS(TP) +" darkly-lashed eyes in disbelief.", "",
      ACTION_VISUAL);
    }
    return 1;
}

public int
do_fly(string str)
{
    if (stringp(str))
    {
	notify_fail("Just lashfly will do.\n");
	return 0;
    }

    write("You capture a buzzing fly with your long, dark lashes then "+
      "pluck it free again.\n");
    allbb(" captures a buzzing fly with "+ HIS(TP) +" long, dark lashes "+
      "then plucks it free again.", "", ACTION_VISUAL);
    return 1;
}

public int
do_tear(string str)
{
    if (strlen(str))
    {
	notify_fail("Just 'lashtear' will do.\n");
	return 0;
    }
    if (TP->query_gender() == G_MALE)
	{
    write("Glistening droplets cling to the lashes of your smouldering "+
      "eyes as you blink back tears.\n");

    say("Glistening droplets cling to the lashes of "+ QCTNAME(TP) +"'s "+
      "smouldering eyes as "+ HE(TP) +" blinks back tears.\n");
    }
    else
    {
    write("Glistening droplets cling to your long, dark eyelashes "+
      "as you blink back tears.\n");

    say("Glistening droplets cling to "+ QCTNAME(TP) +"'s long, dark "+
      "eyelashes as "+ HE(TP) +" blinks back tears.\n");
    }
    return 1;
}

public int
do_lower(string str)
{
    string *how;

    if (TP->query_gender() == G_MALE)
    {
        how = parse_adverb_with_space(str, "respectfully", 0);

        if (!stringp(how[0]))
        {
	        write("You lower the long lashes of your smouldering eyes"+ how[1] +".\n");

	        allbb(" lowers the long lashes of "+ HIS(TP) +" smouldering eyes"+ how[1] + ".",
	            how[1], ACTION_VISUAL);
	    }
	}
    else
    {		
        how = parse_adverb_with_space(str, "demurely", 0);

        if (!stringp(how[0]))
        {
	        write("You lower your long, dark eyelashes"+ how[1] +".\n");

	        allbb(" lowers "+ HIS(TP) +" long, dark eyelashes"+ how[1] + ".",
	            how[1], ACTION_VISUAL);
        }
    }
	return 1;
}

public int
do_tilt(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "flirtatiously", 0);

    if (!stringp(how[0]))
    {
    if (TP->query_gender() == G_MALE)
	{
	write("You tilt your head to look"+ how[1] +" from beneath "+
	  "your smouldering eyelashes.\n");

	allbb(" tilts "+ HIS(TP) +" head to look"+ how[1] +" from "+
	  "beneath "+ HIS(TP) +" smouldering eyelashes.", how[1],
	  ACTION_VISUAL | ACTION_INGRATIATORY );
    }	
    else
    {		
	write("You tilt your head to look"+ how[1] +" from beneath "+
	  "your long, dark eyelashes.\n");

	allbb(" tilts "+ HIS(TP) +" head to look"+ how[1] +" from "+
	  "beneath "+ HIS(TP) +" long, dark eyelashes.", how[1],
	  ACTION_VISUAL | ACTION_INGRATIATORY );
    }
	return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l",
      ACTION_VISUAL | ACTION_INGRATIATORY );

    if (sizeof(oblist) != 1)
    {
	notify_fail("Tilt your head and look [how] [at whom]?\n");
	return 0;
    }
    if (TP->query_gender() == G_MALE)
    {
    actor("You tilt your head to look"+ how[1] +" at", oblist," from "+
      "beneath your smouldering darkened eyelashes.");

    all2actbb(" tilts "+ HIS(TP) +" head and looks at", oblist,
      how[1] +" from beneath "+ HIS(TP) +" smouldering, dark eyelashes.",
      how[1], ACTION_VISUAL | ACTION_INGRATIATORY );

    targetbb(" tilts "+ HIS(TP) +" head and looks at you"+ how[1] +
      " from beneath "+ HIS(TP) +" smouldering, dark eyelashes.", oblist,
      how[1], ACTION_VISUAL | ACTION_INGRATIATORY );
    }
    else
    {
    actor("You tilt your head to look"+ how[1] +" at", oblist," from "+
      "beneath your long, dark eyelashes.");

    all2actbb(" tilts "+ HIS(TP) +" head and looks at", oblist,
      how[1] +" from beneath "+ HIS(TP) +" long, dark eyelashes.",
      how[1], ACTION_VISUAL | ACTION_INGRATIATORY );

    targetbb(" tilts "+ HIS(TP) +" head and looks at you"+ how[1] +
      " from beneath "+ HIS(TP) +" long, dark eyelashes.", oblist,
      how[1], ACTION_VISUAL | ACTION_INGRATIATORY );
    }
    return 1;
}

public string
query_recover(void)	{ return 0; }

public void
init(void)
{
    ::init();

    add_action( do_remove, "remove"    );
    add_action(       bat, "bat"       );
    add_action(  do_blink, "blink"     );
    add_action(    do_fly, "lashfly"   );
    add_action(   do_tilt, "lashtilt"  );
    add_action(   do_tear, "lashtear"  );
    add_action(  do_lower, "lashlower" );
}
