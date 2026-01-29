// file name: ~mascara.c
// creator(s): Zielia
// last update:
// purpose: Object mortals can buy to <apply> to themselves to get eyelashes.
// note: Clones ~lashes.c to player when they <apply>.
// bug(s):
// to-do:

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include "zigg.h"

private static int count;

static void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"mesdemet", "pot", "mascara"}));
    set_adj(({"dark", "black", "small", "sybarun", "ziggurat"}));
    set_short("small pot of mesdemet");
    set_pshort("small pots of mesdemet");
    set_long("@@my_long");
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 3);
    add_prop(OBJ_I_VOLUME, 3);
    add_prop(OBJ_I_VALUE, 500);
    count = 10;
	
    if (IS_CLONE)
      set_item_expiration();
}

public string
my_long(void)
{
    string aps;

    switch(count)
    {
    case 10: aps =  "full";             break;
    case 9:  aps =  "quite full";       break;
    case 8:  aps =  "rather full";      break;
    case 7:  aps =  "somewhat full";    break;
    case 6:  aps =  "about half full";  break;
    case 5:  aps =  "about half empty"; break;
    case 4:  aps =  "somewhat empty";   break;
    case 3:  aps =  "rather empty";     break;
    case 2:  aps =  "close to empty";   break;
    case 1:  aps =  "nearly empty";     break;
    default: aps =  "empty";            break;
    }


    return break_string("A small pot of dark, slightly sticky cream with a "+
      "small brush used to apply it to your eyelashes. It looks " + aps +
      ". In small print along the edge of the pot you see the "+
      "words 'lashtilt', 'lashtear', 'lashfly' and 'lashlower'.\n", 70);
}

public int
do_apply(string str)
{
    if (TP != environment(TO))
	return 0;

    if (!strlen(str))
	return notify_fail("Apply what?\n");

    if (str == "mesdemet" || str == "mascara")
    {
    if (TP->query_gender() == G_MALE)
    {		 
	write("You brush some of the mesdemet over your lashes, "+
	  "making your eyes look smoulderingly handsome.\n");

	say(QCTNAME(TP)+" applies mesdemet over "+ HIS(TP) +" eyelashes, "+
	  "making "+ HIS(TP) +" eyes look smoulderingly handsome.\n");
	}
    else
    {		
	write("You brush some of the mesdemet over your lashes, "+
	  "making them look long and glamorous.\n");

	say(QCTNAME(TP)+" applies mesdemet over "+ HIS(TP) +" eyelashes, "+
	  "making them look long and glamorous.\n");
    }
	if (!present("Zig::lashes", TP))
	{
	    object lashes = clone_object(ZIG_OBJ + "lashes");
	    lashes->move(TP);
	}

	count -= 1;

	if (count == 0)
	{
	    write("You discard the empty pot.\n");
	    set_alarm(0.0, 0.0, remove_object);
	}

	return 1;
    }

    return 0;
}

public void
init(void)
{
    ::init();
    add_action(do_apply,  "apply");
}

public string
query_recover(void)
{
    return MASTER + ":"+ count +"*" +
	query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    sscanf(arg, "%d*%s", count, arg);

}
