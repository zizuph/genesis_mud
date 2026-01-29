/*
 *  file name:   ~pomade.c
 *  creator(s):  Zielia and Lucius 2006
 *  note:       Based on the pomades coded by Amelia in 1997 in Earthsea,
 *		but recoded to add color options/flavors and emotes.
 *		Also provides fancier versions of some emotes including
 *		dancer emotes. For now these are available to all, but
 *		"hidden" (not listed in the help).
 * Revisions:
 * 	Lucius, Sep 2017: Fixed errors in 'pmark'.
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";
inherit "/lib/keep";

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <adverbs.h>
#include "zigg.h"

#define HERS(x) ({ "his", "hers", "its" })[x->query_gender()]

#define TINTED	tints[tint][0]
#define ADJ	tints[tint][1]
#define ADJS	tints[tint][2]
#define COLOR	tints[tint][3]
#define FLAVOR	tints[tint][4]
#define PART	place[size - 1]

#define SUBLOC	"_rosey_lips_"
#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))


private static string *where = ({
  "right cheek", "left cheek", "right hand", "left hand",
  "neck", "forehead", "nose", "bottom", "lips", "chin", "mouth",
});

private static mapping tints = ([

  "azure"	: ({ "blue-tinted", "demure", "demure and bluish",
		"blue", "blueberry", }),

  "blood-red"	: ({ "crimson-tinted", "voluptuous", "blood red",
		"crimson", "cherry", }),

  "carmine"	: ({ "red-tinted", "thickly coated", "thick smearing "+
		"of a bright-red", "bright red", "tangerine", }),

  "clear"	: ({ "glistening", "lustrous", "lustrous shiny",
		"shiny", "honey", }),

  "ebon"	: ({ "ebon-tinted", "bold", "bold, charcoal",
		"black", "licorice", }),

  "plum"	: ({ "plum-tinted", "pouty", "deep plum",
		"purple", "fruit", }),

  "pink"	: ({ "pink-tinted", "soft", "soft pink",
		"pink", "raspberry", }),

  "rose"	: ({ "rose-tinted", "luscious", "luscious rose",
		"red", "strawberry", }),

  "silver"	: ({ "silver-tinted", "silverish", "silverish "+
		"glittery", "glittery", "dew", }),

  "scarlet"	: ({"scarlet-tinted", "satiny", "satiny scarlet",
		"scarlet", "candy", }),

  "umber"	: ({ "umber-tinted", "warm", "warm umber",
		"umber", "chocolate", }),

  "wine"	: ({ "wine-tinted", "sensual", "wine red",
		"dark", "berry", }),

]);

private static string tint = one_of_list(m_indices(tints));

public string
query_tint(void)        { return tint; }

public string *
query_tints(void)       { return m_indices(tints); }

public int
set_tint(string str)
{
    remove_adj(tint);
    remove_adj(TINTED);

    tint = str;

    add_adj(tint);
    add_adj(TINTED);

    set_short("tiny jar of "+ tint +" pomade");
    set_long("A tiny jar filled with "+ tint +" pomade, which "+
      "can be applied to the lips to make them appear more "+
      ADJ +" and beautiful. You notice some small writing "+
      "around the edge of the jar.\n");

    return 1;
}

private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_keep(1);
    set_name(({"jar", "pomade", "gloss"}));
    set_tint(tint);
    
    add_adj(({"sybarun", "ziggurat"}));    

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 150);
    add_prop(OBJ_M_NO_SELL, 1);

    add_item(({"writing"}),
	"The writing simply says <remove pomade>, <pkiss>, <pmark> and "+
	"<pcry>.\n");
    add_cmd_item(({"writing", "writing on jar"}), ({"read"}),
	"The writing simply says <remove pomade>, <pkiss>, <pmark> and "+
	"<pcry>.\n");
	
    if (IS_CLONE)
      set_item_expiration();  
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (for_obj == carrier)
    {
	str = "Your full lips have a "+ ADJS +" tint.\n";
    }
    else
    {
	str = capitalize(HIS(carrier)) +" full "+
	"lips have a "+ ADJS +" tint.\n";
    }

    return str;
}

public int
is_pomade(void)         { return 1; }

public int
f_apply(string str)
{
    object obj;
    object *obs;

    if (!strlen(str))
	return notify_fail("Apply what to what?\n");

    obs = filter(all_inventory(TP), &->is_pomade());

    if (parse_command(str, obs, "%o [to] / [onto] [my] [lips]", obj) &&
      (obj == TO))
    {
	if (objectp(TP->query_subloc_obj(SUBLOC)))
	{
	    write("You should really remove the pomade you are already "+
	      " wearing first, you don't want to look like a trollop.\n"+
	      "If you really do, however, we suggest the 'carmine' tint.\n");

	    return 1;
	}

	write("You delicately apply a touch of "+ tint +" pomade "+
	  "to your lips, and instantly you feel more beautiful.\n"+
	  "You use up the small container of pomade and discard it.\n");

	say(QCTNAME(TP) +" applies a touch of "+ tint +
	  " pomade to "+ HIS(TP) +" lips, making them appear "+ ADJ +
	  " and "+ COLOR +".\n");

	set_no_show();
	add_prop(OBJ_I_NO_DROP, 1);
	TP->add_subloc(SUBLOC, TO);

	return 1;
    }

    return 0;
}

/*  In case object is removed, makes sure subloc is removed first.  */

public void
remove_object(void)
{
    if (IS_CLONE)
	ENV()->remove_subloc(SUBLOC);

    ::remove_object();
}

public int
f_remove(string str)
{
    if (TP->query_subloc_obj(SUBLOC) != TO)
    {
	notify_fail("You must be wearing some pomade first.\n");
	return 0;
    }

    if (id(str))
    {
	write("You remove the pomade from your lips, wiping it "+
	    "off delicately.\n");
	say(QCTNAME(TP) +" delicately wipes the pomade from "+
	    HIS(TP) +" lips.\n");

	set_alarm(0.0, 0.0, remove_object);
	return 1;
    }

    return 0;
}

public int
f_pkiss(string str)
{
    object *oblist;
    string *how;

    if (TP->query_subloc_obj(SUBLOC) != TO)
    {
	notify_fail("You must be wearing some pomade first.\n");
	return 0;
    }

    how = parse_adverb_with_space(str, "sweetly", 1);

    if (!stringp(how[0]))
    {
	notify_fail("Kiss who [how]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[the] %l", ACTION_CONTACT | ACTION_INTIMATE);

    if (sizeof(oblist) != 1)
    {
	notify_fail("Kiss who [how]?\n");
	return 0;
    }

    actor("You press your "+ TINTED +" lips to", oblist,"'s"+
      how[1] +" in a "+ FLAVOR +" flavored kiss.");

    all2act(" presses "+ HIS(TP) +" "+ TINTED +" lips to",
      oblist, "'s "+ how[1] +" in a scrumptious looking kiss.",
      how[1], ACTION_CONTACT | ACTION_INTIMATE);

    target(" presses "+ HIS(TP) +" "+ TINTED +" lips to yours"+
      how[1] +" in a "+ FLAVOR +" flavored kiss.", oblist, how[1],
      ACTION_CONTACT | ACTION_INTIMATE);

    return 1;

}

public int
f_bite(string str)
{
    if (TP->query_subloc_obj(SUBLOC) != TO)
    {
	notify_fail("You must be wearing some pomade first.\n");
	return 0;
    }

    if (stringp(str))
    {
	notify_fail("Bite what?\n");
	return 0;
    }

    write("You bite on your "+ TINTED +" bottom lip.\n");

    allbb(" bites on "+ HIS(TP) +" "+ ADJ +" bottom lip.", "",
      ACTION_VISUAL);

    return 1;
}

public int
f_pcry(string str)
{
    string eyes;
    string *how;

    if (TP->query_gelan_eyes_shadow())
	eyes = TP->query_eyes() +" eyes";
    else
	eyes = "eyes";

    if (TP->query_subloc_obj(SUBLOC) != TO)
    {
	notify_fail("You must be wearing some pomade first.\n");
	return 0;
    }

    how = parse_adverb_with_space(str, BLANK_ADVERB, 0);

    write("Your "+ TINTED +" bottom lip trembles"+ how[1] +" as tears "+
      "fill your "+ eyes +".\n");

    allbb("'s "+ TINTED +" bottom lip trembles"+ how[1] +" as tears "+
      "fill "+ HIS(TP) +" "+ eyes +".", "", ACTION_VISUAL);

    return 1;
}

public int
f_dchew(string str)
{
    string *how;

    if (TP->query_subloc_obj(SUBLOC) != TO)
    {
	notify_fail("You must be wearing some pomade first.\n");
	return 0;
    }

    how = parse_adverb_with_space(str, "thoughtfully", 0);

    if (!stringp(how[0]))
    {
	write("You chew"+ how[1] +" on your "+ FLAVOR +
	  " flavoured bottom lip.\n");

	allbb(" chews"+ how[1] +" on "+ HIS(TP) +" "+ COLOR +
	  " bottom lip.", how[1], ACTION_VISUAL);

	return 1;
    }

    return 0;
}

public int
f_pout(string str)
{
    object *oblist;
    string *how;

    if (TP->query_subloc_obj(SUBLOC) != TO)
    {
	notify_fail("You must be wearing some pomade first.\n");
	return 0;
    }

    how = parse_adverb_with_space(str, "petulantly", 0);

    if (!stringp(how[0]))
    {
	write("You purse your "+ TINTED +" lips and pout"+ how[1] +".\n");

	allbb(" purses "+ HIS(TP) +" "+ TINTED +" lips and pouts"+
	  how[1] +".", how[1], ACTION_VISUAL);

	return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l", ACTION_VISUAL);

    if (sizeof(oblist) != 1)
    {
	notify_fail("Pout [how] [at whom]?\n");
	return 0;
    }

    actor("You purse your "+ TINTED +" lips and pout"+
      how[1] +" at", oblist,".");

    all2actbb(" purses "+ HIS(TP) +" "+ TINTED +" lips and pouts"+
      how[1] +" at", oblist,".", how[1], ACTION_VISUAL);

    targetbb(" purses "+ HIS(TP) +" "+ TINTED +" lips and pouts"+
      how[1] +" at you.", oblist, how[1], ACTION_VISUAL);

    return 1;
}

public int
f_lick(string str)
{
    object *oblist;
    string *how;

    if (TP->query_subloc_obj(SUBLOC) != TO)
    {
	notify_fail("You must be wearing some pomade first.\n");
	return 0;
    }

    how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 1);

    if (!stringp(how[0]))
    {
	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("in anticipation");

	write("You lick your "+ FLAVOR +" flavored lips" + how[1] +".\n");

	allbb(" licks "+ HIS(TP) +" "+ ADJ +" lips"+ how[1] +".",
	  how[1], ACTION_VISUAL);

	return 1;
    }

    return 0;
}

public int
f_pmark(string str)
{
    object mark;
    object *oblist;
    string *how;
    string *place;
    int size;
    string name;

    if (!stringp(str))
    {
	notify_fail("Kiss <who> [how] <where>?\n");
	return 0;
    }

    if (TP->query_subloc_obj(SUBLOC) != TO)
    {
	notify_fail("You must be wearing some pomade first.\n");
	return 0;
    }

    place = explode(str, " ");
    size = sizeof(place);

    if (size > 1)
    {
	if (PART == "cheek" || PART == "hand")
	{
	    if (place[(size - 2)] == "left" | place[(size - 2)] == "right" )
	    {
		PART = place[(size - 2)] + " " + PART;
		place[(size - 2)] = "";
	    }
	    else
	    {
		notify_fail("Kiss the right "+ PART +" or left?\n");
		return 0;
	    }
	}

	if (IN_ARRAY(PART, where))
	{
	    if ((place[0] == "the") && (size > 3))
		str = implode(place[..(2)], " ");
	    else if (size > 2)
		str = implode(place[..(1)], " ");
	    else
		str = place[0];

	    how = parse_adverb_with_space(str, "gently", 1);

	    oblist = parse_this(how[0], "[the] %l [on]",
		ACTION_CONTACT | ACTION_INTIMATE);

	    if (sizeof(oblist) != 1)
	    {
		notify_fail("Kiss <who> [how] <where>?\n");
		return 0;
	    }

	    if (PART == "mouth")
	    {
		PART = "lips";
	    }

	    name = "pomade::" + PART;

	    if (PART != "lips" && PART != "mouth")
	    {
		actor("You kiss", oblist, how[1] + " on the "+ PART +
		  ", your lips lingering for a moment, leaving behind a "+
		  TINTED +" kiss mark.");

		all2act(" kisses", oblist, how[1] + " on the "+ PART +", "+
		  HIS(TP) +" lips lingering for a moment, leaving behind a "+
		  TINTED +" kiss mark.", how[1],
		  ACTION_CONTACT | ACTION_INTIMATE);

		target(" kisses you"+ how[1] + " on the "+ PART +", "+
		  HIS(TP) +" lips lingering for a moment, leaving behind a "+
		  TINTED +" kiss mark.", oblist, how[1],
		  ACTION_CONTACT | ACTION_INTIMATE);

		if (!present(name, oblist[0]))
		{
		    mark = clone_object(ZIG_OBJ +"pmark");
		    mark->set_vars(TINTED, COLOR, PART);
		    mark->move(oblist[0]);

		    return 1;
		}
		else
		{
		    present(name, oblist[0])->set_vars(TINTED, COLOR, PART);
		    return 1;
		}
	    }
	    else
	    {
		actor("You pull", oblist, " against you and press your "+
		  COLOR +" lips"+ how[1] +" to "+ HIS(oblist[0]) +
		  " for a long moment before releasing "+ HIM(oblist[0]) +
		  ", leaving "+ HIM(oblist[0]) +" reeling in a "+
		  FLAVOR +" flavored haze.");

		all2act(" pulls", oblist, " against "+ HIM(TP) +" and presses "+
		  HIS(TP) +" "+ COLOR +" lips"+ how[1] + " to "+
		  HERS(oblist[0]) +" for a long moment before releasing "+
		  HIM(oblist[0]) +", leaving "+ HIM(oblist[0]) +" reeling.",
		  how[1], ACTION_CONTACT | ACTION_INTIMATE);

		target(" pulls you against "+ HIM(TP) +" and presses "+
		  HIS(TP) +" "+ COLOR +" lips"+ how[1] +" to yours for a "+
		  "long moment, leaving you breathless and reeling, the "+
		  "taste of "+ FLAVOR +" clinging to your lips.", oblist,
		  how[1], ACTION_CONTACT | ACTION_INTIMATE);

		if(!present(name, oblist[0]))
		{
		    mark = clone_object(ZIG_OBJ +"pmark");
		    mark->set_vars(TINTED, COLOR, PART);
		    mark->move(oblist[0]);
		}
		else
		{
		    present(name, oblist[0])->set_vars(TINTED, COLOR, PART);
		}

		return 1;
	    }
	}
	else
	{

	    notify_fail("Kiss <who> [how] <where>?\n");
	    return 0;
	}
    }

    notify_fail("Kiss <who> [how] <where>?\n");
    return 0;
}

public int
f_dansm(string str)
{
    object *oblist;

    if (!str)
    {
	write("Your "+ TINTED +" lips curls upward in a small, enigmatic "+
	  "smile.\n");
	allbb("'s "+ TINTED +" lips curls upward in a small, enigmatic "+
	  "smile.", "", ACTION_VISUAL);
	SOULDESC("looking enigmatic");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l", ACTION_VISUAL);

    if (!sizeof(oblist))
    {
	NF("Dsmile at who?\n");
	return 0;
    }

    actor("You look at", oblist, " and a small, enigmatic smile "+
      "curls your "+ COLOR +" lips.");
    all2actbb(" looks at", oblist, ", and a small, enigmatic "+
      "smile curls "+ HIS(TP) +" "+ COLOR +" lips.", "", ACTION_VISUAL);
    targetbb(" looks at you, and a small, enigmatic smile curls "+
      HIS(TP) +" "+ COLOR +" lips.", oblist, "", ACTION_VISUAL);
    SOULDESC("looking enigmatic");
    return 1;
}

public int
f_dlean(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	notify_fail("Dlean against who?\n");
	return 0;
    }

    oblist = parse_this(str, "[on] [against] [the] %l",
	ACTION_CONTACT | ACTION_INTIMATE);

    if (!sizeof(oblist))
    {
	notify_fail("Dlean against who?\n");
	return 0;
    }

    actor("You lean your body against", oblist, ", offering "+
      "your "+ ADJ +" mouth for a kiss.");
    all2actbb(" leans against", oblist,", offering "+ HIS(TP) +
      " "+ ADJ +" mouth for a kiss.", "", ACTION_CONTACT | ACTION_INTIMATE);
    target(" leans her warm, fragrant body against yours "+
      "and offers "+ HIS(TP) +" "+ ADJ +" mouth to be kissed.", oblist,
      "", ACTION_CONTACT | ACTION_INTIMATE);
    return 1;
}

public int
f_dmouth(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You moisten your "+ COLOR +" lips with the tip of your tongue "+
	  "in a blatant invitation to be kissed.\n");
	allbb(" runs the tip of her tongue along her "+ COLOR +" lips, "+
	  "leaving you with the impression that she wants to be kissed.",
	  "", ACTION_INGRATIATORY);
	return 1;
    }

    oblist = parse_this(str, "[for] [the] %l", ACTION_INGRATIATORY);

    if (!sizeof(oblist))
    {
	notify_fail("Dmouth for who?\n");
	return 0;
    }

    if (sizeof(oblist) == 1)
	str = (string)oblist[0]->query_objective();
    else
	str = "them";

    actor("You slowly trace the contours of your "+ TINTED +" mouth with the "+
      "tip of your tongue, blatantly inviting", oblist, " to "+
      "kiss you.");
    all2actbb(" seems to invite", oblist, " to kiss her by looking "+
      "steadily at "+str+ " while slowly "+
      "tracing the contours of her "+ TINTED +" mouth with the tip of her "+
      "tongue.", ACTION_INGRATIATORY);
    targetbb(" slowly traces the contours of her "+ TINTED +" mouth "+
      "with the tip of her tongue in a blatant invitation "+
      "to be kissed!", oblist, ACTION_INGRATIATORY);
    return 1;
}

public void
init(void)
{
    ::init();

    if (environment() != TP)
	return;

    add_action(   f_apply, "apply"    );
    add_action(  f_remove, "remove"   );
    add_action(   f_pkiss, "pkiss"    );
    add_action(    f_bite, "bite"     );
    add_action(    f_pcry, "pcry"     );
    add_action(    f_pout, "pout"     );
    add_action(    f_lick, "lick"     );
    add_action(   f_dchew, "dchew"    );
    add_action(   f_pmark, "pmark"    );
    add_action(   f_dansm, "dansm"    );
    add_action(   f_dansm, "dsmile"   );
    add_action(   f_dansm, "dsmi"     );
    add_action(   f_dansm, "dansmile" );
    add_action(   f_dlean, "dlean"    );
    add_action(  f_dmouth, "dmouth"   );
}

public string
query_recover(void)
{
    if (query_no_show())
	return 0;

    return MASTER + ":"+ tint +"*" +
	query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    string old;

    init_item_expiration_recover(arg);
    sscanf(arg, "%s*%s", old, arg);

    set_tint(old);
}
