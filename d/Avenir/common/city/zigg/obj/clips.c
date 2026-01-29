/*
 *  file name:   ~hair_clips.c
 *  creator(s):  Zielia
 *  last update:
 *  purpose:     Object mortals can buy which they can wear to decorate
 *               their hair. Adds a subloc to mortal long description.
 *  note:        Works with hair from /d/Calia/gelan if the mortal has it.
 *  bug(s):
 *  to-do:
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "zigg.h"
#include "hair.h"

#define SUBLOC "_hair_clips_"
#define HAIRSTYLE_SUBLOC "hairstyle"
#define VAR_ADJS ({x, y})
#define VAR_NAMES ({z, "handful", "clip", "barrette"})
#define CLIPS x +" "+ y +" "+ z
#define A_CLIPS y +" "+ z

private static object hair_sub;
private static int worn = 0;
private static string *sparkle = ({
  "crystal", "emeralds", "fire-opals", "gems", "iridescent", "jewels",
  "moonstones", "rubies", "sapphires", "scintillating", "shimmering",
  "shiny", "sparkling"
});

private static int box = 1;
public static string x = "plain";
public static string y = "hair";
public static string z = "clips";

/*
 *  The clips at first appear to be a box, the appearance changes
 *  once the box is opened.
 */

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"box"}));
    set_adj(({"small", "plain", "sybarun", "ziggurat", "custom"}));
    set_short("@@my_short");
    set_pshort("@@my_shorts");
    set_long("@@my_long");

    set_keep(1);

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 500);
	
	if (IS_CLONE)
      set_item_expiration();  	
}

/*  Descriptions.  */

public string
short_name(void)
{
    return CLIPS;
}

public string
my_short(void)
{
    if (box == 1) return "small gold box";

    else return "handful of "+ short_name();
}

public string
my_shorts(void)
{
    if (box == 1) return "small gold boxes";

    else return "handfuls of "+ short_name();
}

public string
my_long(void)
{
    if (box == 1)
    {
	return "It is a small box made of thick gold vellum. The top "+
	"of the box is stamped with a dark, leafy green vine twisting "+
	"and turning itself into the name of the shop from which it "+
	"comes: Tangles.\n";
    }
    else
    {
	return "A handful of "+ short_name() +
	" which can be woven into your hair to adorn it.\n";
    }
}

/*  Called during ordering to set variables adjectives and names for clips.  */

public void
set_desc(string str1, string str2, string str3)
{
    x = str1;
    y = str2;
    z = str3;

    if(x == y)    { x = "very"; }
}

/*  Transforms the box into the ordered clips and resets adjs and names.  */

public int
open_box(string str)
{
    if (box == 0)
	return 0;

    if (str == "box" || str == "gold box" ||
	str == "small box" || str == "small gold box")
    {
	box = 0;

	remove_adj(query_adjs());
	set_adj(VAR_ADJS);

	remove_name(query_names());
	set_name(VAR_NAMES);

	write("You open the small gold box. Inside you find a "+
	  my_short() +". You remove the contents and discard the box.\n");

	say(QCTNAME(TP) +" opens the small gold box. "+ capitalize(HE(TP)) +
	  " then removes the contents and discards the box.\n");

	return 1;
    }

    return 0;
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
    string amt;

    if (IN_ARRAY(z, ({"ribbons","ropes","twigs","sticks","spiderwebs",
	  "bones","spikes","strings","strips","chains"})))
    {
	amt = "Several ";
    }
    else
    {
	amt = "Dozens of ";
    }

    /* String for subloc if they have Calia/gelan hair else if they do not. */

    if (for_obj == carrier)
    {
	str = amt+ CLIPS +" are woven into your"+ HAIR(carrier) +".\n";
    }
    else
    {
	str = amt + CLIPS +" are woven into "+
	    HIS(carrier) + HAIR(carrier) +".\n";
    }

    return str;
}

/*  Wear clips  */

public int
do_weave(string str)
{
    if (TP != environment(TO))
	return 0;

    if (box == 1)
	return 0;

    if (worn == 1)
    {
	notify_fail("You already wear the "+ z +".\n");
	return 0;
    }

    if (!strlen(str))
    {
	notify_fail("Weave what? The "+ z +"?\n");
	return 0;
    }

    if (query_prop(OBJ_I_BROKEN))
    {
      notify_fail("The " + z + " are broken and cannot be used.\n");
      return 0;
    }

    if (str == z || str == "clips")
    {
	/*  Bald people can't wear us   */
	if (IN_ARRAY(STYLE(TP), missing))
	{
	    return notify_fail("You don't seem to have enough hair.\n");
	}

	if (IN_ARRAY(SUBLOC, TP->query_sublocs()))
	{
	    write("There isn't room to weave anything more.\n");
	    return 0;
	}

	set_no_show();

	/*  Remember original hair   */

	if (TP->query_hair_colour())
	{
	    hair_sub = TP->query_subloc_obj(HAIRSTYLE_SUBLOC);
	    TP->remove_subloc(HAIRSTYLE_SUBLOC);
	}

	write("You intricately weave the "+ CLIPS +
	  " into your"+ HAIR(TP) +".\n");

	say(QCTNAME(TP)+ " intricately weaves dozens of "+
	  CLIPS +" into "+ HIS(TP) + HAIR(TP) +".\n");

	TP->add_subloc(SUBLOC, TO);
	worn = 1;

	return 1;
    }

    notify_fail("Weave what? The "+ z +"?\n");
    return 0;
}

/*
 *  In case object is removed, makes sure subloc is removed first,
 *  and Calia hair subloc replaced if applicable.
 */
public void
remove_object(void)
{
    if (IS_CLONE)
    {
	ENV()->remove_subloc(SUBLOC);
	if (ENV()->query_hair_colour())
	    ENV()->add_subloc(HAIRSTYLE_SUBLOC, hair_sub);
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

    if (box == 1)
	return 0;

    if (str == z || str ==  "clips" || str == "barrettes")
    {
	if (worn == 0)
	{
	    notify_fail("You aren't wearing the "+ z +".\n");
	    return 0;
	}

	unset_no_show();
	set_no_show_composite(0);

	ENV()->remove_subloc(SUBLOC);
	if (ENV()->query_hair_colour())
	    ENV()->add_subloc(HAIRSTYLE_SUBLOC, hair_sub);

	write("You gently pull the "+ CLIPS +" out of your"+
	  HAIR(TP) +".\n");

	say(QCTNAME(TP) +" gently pulls the "+ CLIPS +" out of "+
	  HIS(TP) + HAIR(TP) +".\n");

	worn = 0;
	return 1;
    }

    return 0;
}

public void
leave_env(object from, object to)
{
    if (worn)
    {
	worn = 0;
	unset_no_show();
	set_no_show_composite(0);
    }

    ::leave_env(from, to);
}

/*  Emotes   */

public int
do_toss(string str)
{
    if (box == 1)
	return 0;

    if (!strlen(str) || str == "hair")
    {
	if (worn == 0)
	{
	    notify_fail("You must be wearing the "+ z +".\n");
	    return 0;
	}

	if (z == "bells")
	{
	    write("You toss your"+ HAIR(TP) +" back making the many "+
	      A_CLIPS +" tinkle musically.\n");

	    say(QCTNAME(TP) +" tosses "+ HIS(TP) + HAIR(TP) +
	      " back, causing the many "+ A_CLIPS + " to tinkle musically.\n");

	    return 1;
	}
	else if (environment(TP)->query_prop(ROOM_I_LIGHT) > 0)
	{
	    if (IN_ARRAY(x, sparkle) || IN_ARRAY(y, sparkle) ||
		IN_ARRAY(z, sparkle))
	    {
		write("You toss your"+ HAIR(TP) +" back making the many "+
		  A_CLIPS +" glitter and sparkle in the light.\n");

		say(QCTNAME(TP) +" tosses "+ HIS(TP)+
		  HAIR(TP) +" back, causing the many "+ A_CLIPS +
		  " to glitter and sparkle in the light.\n");

		return 1;
	    }

	    else
	    {
		write("You toss back your"+ HAIR(TP) +" with the "+
		  A_CLIPS +" woven into it.\n");

		say(QCTNAME(TP) +" tosses back "+ HIS(TP)+
		  HAIR(TP) +" with the "+ A_CLIPS +" woven into it.\n");

		return 1;
	    }
	}
	else
	{
	    write("You toss your"+ HAIR(TP) +", but doubt anyone notices "+
	      "in the dark.\n");

	    return 1;
	}
    }
}

public void
init()
{
    ::init();

    add_action(   do_toss,  "toss"  );
    add_action(   do_toss,  "htoss"  );
    add_action(  do_weave,  "weave"  );
    add_action( do_remove,  "remove" );
    add_action(  open_box,  "open" );
}

public string
query_recover(void)
{
    return MASTER + ":"+ box +"#"+ x +"#"+ y +"#"+ z+"*" +
	query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    sscanf(arg, "%d#%s#%s#%s*%s", box, x, y, z, arg);

    set_desc(x, y, z);

    if (box == 0)
    {
	remove_adj(query_adjs());
	set_adj(VAR_ADJS);

	remove_name(query_names());
	set_name(VAR_NAMES);
    }

}
