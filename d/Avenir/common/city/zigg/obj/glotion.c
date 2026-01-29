// Glittery Lotion ("glotion.c")
// creator(s):   Zielia 2006
// last update:
// purpose:      Adds a sparkly subloc to players.
// note:
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include "zigg.h"

private static int count = (random(10) + 9), max_count = count;
private static string aps = "full", color = one_of_list(({

  "red", "dark red", "scarlet", "crimson", "pink", "orange", "peach",
  "yellow", "green", "jade", "light green", "dark green", "blue",
  "light blue", "sapphire", "dark blue", "indigo", "teal", "cerulean",
  "turquoise", "violet", "amethyst", "lavender", "purple", "white",
  "black", "onyx", "obsidian", "gold", "silver", "platinum", "copper",
  "bronze", "ruby", "emerald"

}));

public void
set_color(string str)
{
    remove_adj(({color,}));
    remove_adj(explode(color, " "));

    color = str;

    add_adj(explode(color, " "));

    set_short("small bottle of "+ color +" glittery lotion");
    set_pshort("small bottles of "+ color +" glittery lotion");
}

public void
set_aps(int num)
{
    int val = 100;

    remove_adj(({aps,}));
    remove_adj(explode(aps, " "));

    if (count != max_count)
    {
        float max, cur;

        cur = itof(count);
        max = itof(max_count);
        val = ftoi(100.0 - (((max - cur) / max) * 100.0));
    }

    switch(val)
    {
    case 91..100: aps = "full";			break;
    case 81..90:  aps = "quite full";		break;
    case 71..80:  aps = "rather full";		break;
    case 61..70:  aps = "somewhat full";	break;
    case 51..60:  aps = "about half full";	break;
    case 41..50:  aps = "about half empty";	break;
    case 31..40:  aps = "somewhat empty";	break;
    case 21..30:  aps = "rather empty";		break;
    case 11..20:  aps = "close to empty";	break;
    case  0..10:  aps = "nearly empty";		break;
    default:      aps = "deceptively full";	break;
    }

    add_adj(explode(aps, " "));
}

public int
configure_lotion(string str, int num)
{
    set_color(str);
    set_aps(num);
}

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"body glitter", "lotion", "bottle"}));
    set_adj(({"small", "glittery", "sybarun", "ziggurat"}));
    set_long("@@my_long");

    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 40);
    add_prop(OBJ_I_VALUE, 250);
    set_keep(1);

	if (IS_CLONE)
      set_item_expiration();  	

    configure_lotion(color, count);
}

public string
my_long(void)
{
    return "A small bottle of glittery lotion you can rub "+
	"onto your skin to make it soft and shimmery. Inside the bottle " +
	"you see a silky, "+ color +" sparkling cream. The bottle is "+
	aps +".\n";
}

public int
do_rub(string str)
{
    if (TP != environment(TO))
       return 0;

    if (!strlen(str))
	return notify_fail("Rub what onto your skin?\n");

    if (parse_command(str, ({}), " [body] 'lotion' / 'glitter' / 'cream' "+
	    "[on] / [onto] [my] [skin] "))
    {
	write("You pour some of the "+ color +" sparkling lotion into "+
	  "your hand and rub it onto your skin. The lotion slowly "+
	  "seeps into your skin with a cool tingle making it "+
	  "soft and glittery.\n");

	say(QCTNAME(TP)+" pours out a dollop of "+ color +" sparkling lotion "+
	  "into "+ HIS(TP) +" hand and rubs it onto "+ HIS(TP) +" skin making "+
	  "it soft and glittery.\n");

	if (count == 0)
	{
	    write("\nNoticing that the bottle is now empty, you discard it.\n");
	    set_alarm(0.0, 0.0, remove_object);
	}

	if (!present("body::glitter", TP))
	{
	    object glitter = clone_object(ZIG_OBJ +"bglitter");
	    glitter->set_glitter_color(color);
	    glitter->move(TP);
	}
	else
	{
	    present("body::glitter", TP)->set_glitter_color(color);
	}

	set_aps(count -= 1);
	return 1;
    }
}

public void
init(void)
{
    ::init();

    add_action(do_rub,  "rub");
}

public string
query_recover(void)
{
    return MASTER + ":"+ color +"#"+ count +"*"+ max_count +"*"+
           query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    sscanf(arg, "%s#%d*%d*%s", color, count, max_count, arg);

    configure_lotion(color, count);
}
