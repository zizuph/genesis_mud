/* 
 * A cape for the Union of the Warriors of Shadow.
 * It gets more dirty, and can be cleaned.
 *   Cirion 032696
 *
 * Revisions:
 * 	Lilith/Hannah, Jan 1999: Emotes added.
 *	Lilith, Jun 2002: Updated desc and recovery.
 *	Lucius, May 2009: Cleanups
 *	Lucius, Jul 2017: More Cleanups
 */
#pragma strict_types

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/commands";
inherit "/lib/keep";

inherit (LIB + "union_arm");

private int dirt_alarm;


public void 
create_object(void)
{
    allow_buff = 0;
    allow_clean = 1;

    set_name("cape");
    set_adj(({"white","shoulder"}));
    add_adj("union");
    add_adj("unworn");
    set_long("This cape is made of a thin material that billows "+
      "in the air and seems to capture shadows in its folds. "+
      "It is composed of two layers, with the inner layer being "+
      "ankle-length and the outer one draping the shoulders to "+
      "the elbow. It's function is more as a symbol of status within "+
      "Sybarus rather than as a form of protection against "+
      "the elements. It is fastened at one side with a thin "+
      "bronze clasp.@@my_long@@\n");

    add_item("label", "This label is sewn into the "+ short() +
      ". It says: There are several emotes associated with this cape.\n"+
      "     Back, bow, comfort, curtsey, and dance.\n"+
      "     The command <billow on/off> is also available.\n");
    add_item(({"clasp", "bronze clasp", "fastener"}),
      "It is a bronze clasp in the form of a long, thin dagger.\n");

    add_prop(OBJ_I_VOLUME,   957);
    add_prop(OBJ_I_WEIGHT,   964);
    add_prop(OBJ_I_VALUE,     89);

    set_keep(1);
    config_wearable_item(A_ROBE, 2, 20, this_object());

    if (IS_CLONE)
      set_item_expiration(); 
}

public mixed 
wear(object ob)
{
    if (TP != ENV(TO))
	return 0;

    write("You fasten "+LANG_THESHORT(TO)+" around "+
	"your neck and let it hang down over your shoulder.\n");
    say(QCTNAME(TP)+" fastens "+LANG_ASHORT(TO)+" around "+
	HIS(TP)+" neck, and it hangs down over "+
	HIS(TP)+" shoulder.\n");

    return 1;
}

public mixed 
remove(object ob)
{
    if (TP != ENV(TO))
	return 0;

    if (query_verb() != "remove" &&
	query_verb() != "drop" &&
	query_verb() != "give")
    {
	return 0;
    }

    if (!TP->query_wiz_level())
	TP->set_m_in("arrives");

    write("You unfasten "+LANG_THESHORT(TO)+" and remove it "+
	"from your shoulder.\n");
    say(QCTNAME(TP)+" unfastens "+HIS(TP)+" "+QSHORT(TO)+".\n");

    return 1;
}

public string 
my_long(void)
{
    string str = " It is ", str2;

    if (dirt < 0) dirt = 0;

    switch(dirt)
    {
    case 0: str += "bright white and perfectly clean."; break;
    case 1: str += "white and clean."; break;
    case 2: str += "starting to get a bit faded."; break;
    case 3: str += "rather worn and greyish."; break;
    case 4: str += "starting to get very dingy."; break;
    case 5: str += "very dirty."; break;
    case 6: str += "completely filthy with dirt and travel stains."; break;
    case 7: str += "tattered and covered in dirt."; break;
    default:str += "ragged and so filthy that it looks grey."; break;
    }

    switch(blood)
    {
    case 0 .. 99:    str2 = "";               break;
    case 100 .. 200: str2 = "blood-stained."; break;
    case 201 .. 350: str2 = "bloody.";        break;
    case 351 .. 500: str2 = "blood-covered."; break;
    default:         str2 = "blood-soaked.";  break;
    }

    if (strlen(str2))
	str += " It is also "+ str2;

    if (IS_MEMBER(TP))
	str += " A label has been sewn into the seam.";

    return str;
}

public void 
more_dirty(void)
{
    if (!living(ENV(TO)))
    {
	remove_alarm(dirt_alarm);
	dirt_alarm = 0;
    }
    else if (++dirt > 8) {
	dirt = 8;
    }
}

public void 
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (query_interactive(to))
    {
	if (!dirt_alarm)
	    dirt_alarm = set_alarm(7200.0, 7200.0, more_dirty);
    }
    else if (dirt_alarm)
    {
	remove_alarm(dirt_alarm);
	dirt_alarm = 0;
    }
}

public void 
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);    

    if (!from->query_wiz_level())
	from->set_m_in("arrives");
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

public varargs string
short(object for_ob)
{
    string dirt_desc, blood_desc, str;

    switch(dirt)
    {
    case 0:  dirt_desc = "bright white";   break;
    case 1:  dirt_desc = "white";          break;
    case 2:  dirt_desc = "faded white";    break;
    case 3:  dirt_desc = "worn white";     break;
    case 4:  dirt_desc = "dingy white";    break;
    case 5:  dirt_desc = "dirty white";    break;
    case 6:  dirt_desc = "filthy white";   break;
    case 7:  dirt_desc = "tattered white"; break;
    default: dirt_desc = "ragged grey";    break;
    }

    switch(blood)
    {
    case 0 .. 99:    blood_desc = "";              break;
    case 100 .. 200: blood_desc = "blood-stained"; break;
    case 201 .. 350: blood_desc = "bloody";        break;
    case 351 .. 500: blood_desc = "blood-covered"; break;
    default:         blood_desc = "blood-soaked";  break;
    }

    if (strlen(dirt_desc) && strlen(blood_desc))
	str = dirt_desc + " " + blood_desc + " ";
    else if (strlen(dirt_desc))
	str = dirt_desc + " ";
    else if (strlen(blood_desc))
	str = blood_desc + " ";
    else
	str = "bright white ";

    return str + "shoulder cape";
}

public int
mask_arrive(string arg)
{
    if (!query_worn()) 
	return 0;

    if (TP->query_wiz_level())
    {
	notify_fail("You are a wizard, this will not work on you.\n");
	return 0;
    }

    if (!strlen(arg))
    {
	notify_fail("Do you want billow on or off?\n");
	return 0;
    }

    if (arg == "on")
    {
	string m_in = "strides in, "+HIS(TP)+" cape billowing "+
	    "behind "+ HIM(TP);

	TP->catch_msg("You adjust the cape so that when you enter a "+
	    "room, people see: "+ QCTNAME(TP) +" "+ m_in +".\n");
	TP->set_m_in(m_in);

	return 1;
    }

    if (arg == "off")
    {
	TP->catch_tell("You adjust your cape so that it no longer "+
	    "billows behind you.\n");
	TP->set_m_in("arrives");
	return 1;
    }    

    notify_fail("Billow on or billow off?\n");
    return 0;
}

/*
 * Add/mask emotions to make them more fun!
 */
public int
do_back(string str)
{
    string *how;
    object *oblist;

    if (!query_worn()) 
	return 0;

    how = parse_adverb_with_space(str, "slowly", 0);

    if (!strlen(how[0]))
    {
	write("You draw your "+ short() +" around you while " +
	    "backing" + how[1] + " away.\n");
	all(" draws "+ HIS(TP) +" "+ short() +" around "+
	    HIM(TP) +" and begins to back"+ how[1] +" away.");

	return 1;
    }

    oblist = parse_this(how[0], "[away] [from] [the] %i");
    if (!sizeof(oblist))
    {
	notify_fail("Back [how] away from whom?\n");
	return 0;
    }

    actor("You draw your "+ short() +" around you while " +
	"backing"+ how[1] +" away from", oblist);
    all2actbb(" draws "+HIS(TP)+" "+ short()+" around "+
	HIM(TP)+" and begins to back"+ how[1] +" away from",
	oblist, 0, how[1]);
    targetbb(" draws "+ HIS(TP) +" "+ short() +" around "+
	HIM(TP)+" and begins to back" + how[1] +" away from you.",
	oblist, how[1]);

    return 1;
}

public int
do_bow(string str)
{
    object *oblist;

    if (!query_worn())
	return 0;

    if (!strlen(str))
    {
	write("You spread wide the folds of your "+ short() +
	    " and bow with the languid grace of a shadow warrior.\n");
	allbb(" spreads wide the folds of "+ HIS(TP) +" "+
	    short() +" and bows with the languid grace of "+
	    "a shadow warrior.");

	return 1;
    }

    oblist = parse_this(str, "[to] / [before] [the] %i");
    if (!sizeof(oblist))
    {
	notify_fail("Bow to <whom>?\n");
	return 0;
    }

    actor("You spread wide the folds of your "+ short() +
	" and bow to", oblist, " with the languid grace "+
	"of a shadow warrior.");
    all2actbb(" spreads wide the folds of "+ HIS(TP) +" "+ short() +
	" and bows to", oblist, " with the languid grace of a "+
	"shadow warrior.");
    targetbb(" spreads wide the folds of "+ HIS(TP) +" "+ short() +
	" and bows before you with the languid grace of a "+
	"shadow warrior.", oblist);

    return 1;
}

public int
do_comfort(string str)
{
    object *oblist;

    if (!query_worn()) 
	return 0;

    if (!strlen(str))
    {
	write("You comfort yourself within the folds of your "+
	    short() +".\n");
	all(" comforts "+HIM(TP)+"self within the folds of "+
	    HIS(TP) +" "+ short() +".");

	return 1;
    }

    oblist = parse_this(str, "[the] %i");  
    if (!sizeof(oblist))
    {
	notify_fail("Comfort whom?\n");
	return 0;  
    }

    actor("You comfort", oblist, " within the folds of your "+
	short()+".");
    all2act(" comforts", oblist, " within the folds of "+ HIS(TP) +
	" "+ short()+".");
    target(" comforts you within the folds of "+HIS(TP) +" "+
	short()+".", oblist);

    return 1;
}

public int
do_curtsey(string str)
{
    string *how;
    object *oblist;

    if (!query_worn()) 
	return 0;

    how = parse_adverb_with_space(str, "languidly", 0);

    if (!strlen(how[0]))
    {
	write("You curtsey"+how[1]+", lifting the edges of " +
	    "your "+ short() +" daintily as you do so.\n");
	all(" curtseys"+how[1]+", lifting the edges of "+HIS(TP) +
	    " "+ short()+" daintily as "+HE(TP)+" does so.");
	return 1;
    }

    oblist = parse_this(how[0], "[to] / [before] [the] %i"); 
    if (!sizeof(oblist))
    {
	notify_fail("Curtsey [how] to whom?\n");
	return 0;
    }

    actor("You curtsey"+how[1]+" to", oblist, ", lifting the edges "+
	"of your "+short()+" daintily as you do so.");
    all2actbb(" curtseys"+how[1]+" to", oblist,", lifting the edges "+
	"of "+HIS(TP)+" "+short()+" daintily as "+HE(TP) +
	" does so.");
    targetbb(" curtseys"+how[1]+" to you, lifting the edges "+
	"of "+HIS(TP)+" "+ short() +" daintily as "+HE(TP) +
	" does so.", oblist);

    return 1;
}

public int
do_dance(string str)
{
    object *oblist;

    if (!query_worn())
	return 0;

    if (!strlen(str))
    {
	write("You dance with a sinuous, weaving motion, causing your "+
	    short() +" to swirl and sway around you.\n");
	all("'s "+ short() +" swirls about "+ HIM(TP) +" as "+
	    HE(TP) +" dances with a sinuous, weaving motion.");
	return 1;
    }

    oblist = parse_this(str, "[with] [before] [the] %i");
    if (!sizeof(oblist))
    {
	notify_fail("Dance before whom?\n");
	return 0;
    }

    actor("You dance before", oblist, " with a sinuous, weaving motion "+
	"that causes your "+ short() +" to swirl around you.");
    all2act(" dances before", oblist, " with a sinuous, weaving motion "+
	"that causes "+ HIS(TP) +" "+ short() +" to swirl around "+
	HIM(TP) +".");
    target(" dances before you with a sinuous, weaving motion that "+
	"causes "+ HIS(TP) +" "+ short() +" to swirl around "+
	HIM(TP) +".", oblist);

    return 1;
}

public void
init(void)
{
    ::init();

    init_union_arm();

    if (!IS_MEMBER(TP))
	return;

    add_action(do_back,    "back");
    add_action(do_bow,     "bow");
    add_action(do_comfort, "comfort");
    add_action(do_curtsey, "curtsey");
    add_action(do_dance,   "dance");
    add_action(mask_arrive,"billow");
}


public string
query_recover(void)
{
    return MASTER + ":" + query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);

}

