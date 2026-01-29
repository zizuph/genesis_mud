// file name: /d/Avenir/common/clubs/mummer/mum_cap"
// creator(s):  Lilith, October 1996
// last update: Lilith 27 Aug 1997
// 		Lucius, Sep 2016: Converted to clothing instead of armour.
//
// purpose:     The guild object for the minor guild
//                    The Mummers of Sybarus 
//              in Bazaar, City of Sybarus, Avenir
//
// note:        Autoloadable. Go to clubs/mummer/clubroom to restore it.
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "mummer_club.h"

#ifndef TP
# define TP this_player()
#endif


public string
query_auto_load(void)	{ return MASTER + ":"; }

/* cannot be both recoverable and autoloadable */
public string
query_recover(void)	{ return 0; }

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name(({ MUMMER_CAP, "cap" }));
    add_adj(({ "pronged", "multi-cloured", "fabulous" }));

    set_short("multi-colored two-pronged cap with bells");
    set_long("This fabulous cap has two prongs, each one with a "+
        "bell on the tip. When the cap is worn, the prongs dangle "+
        "down over your ears and come to rest on your shoulders. "+
        "It is decorated in a jewel-toned diamond pattern, and is "+
        "worn exclusively by the Mummers of Sybarus.\n"+ 	
        "For information about mummery, try <mumhelp>.\n");

    add_item(({"bell","bells","prong","prongs"}),
	"There are two bells, one on the tip of each prong of "+
	"this cap. They tinkle a bit when you move.\n");
    add_item(({"pattern", "diamond", "diamond pattern", "color"}),
        "This is a multi-coloured pattern of diamond-shapes in dark "+
        "jewel tones.\n");

    set_slots(A_HEAD); 
  
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_M_NO_DROP,"Oddly enough, you can't seem to "+
        "do that.\n");
    add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
        "for you to simply give it away.\n");
    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
}

private void
add_mummer_soul(object ob)
{
    ob->add_subloc(MUMMER_SUBLOC, this_object());
    ob->add_prop(MUMMER_PROP, 1);
    ob->add_cmdsoul(MUMMER_SOUL);
    ob->update_hooks();
}

private void
reject_mummer_soul(object ob)
{
    ob->catch_tell("You are not a Mummer of Sybarus!\n" + 
        "The "+ short() +" falls to the ground and bursts into "+
        "flame at your feet.\n");

    remove_object();
} 

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!dest->query_wiz_level() && (dest->query_gender() == G_FEMALE ))
	set_alarm(3.0, 0.0, &reject_mummer_soul(dest));
    else
	set_alarm(1.0, 0.0, &add_mummer_soul(dest));
}

public void
leave_env(object from, object to)
{
    if (objectp(from))
    {
	from->remove_cmdsoul(MUMMER_SOUL);
	from->remove_subloc(MUMMER_SUBLOC);
	from->update_hooks();

	if (from->query_prop(MUMMER_PROP))
	    from->remove_prop(MUMMER_PROP);

	if (!from->query_wiz_level())
	    from->set_m_in("arrives");
    }

    ::leave_env(from, to);
     wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != MUMMER_SUBLOC)
        return this_player()->show_subloc(subloc, on, for_obj);
  
    if (for_obj == on)
	subloc = "You are ";
    else
	subloc = capitalize(on->query_pronoun()) +" is ";

    switch(on->query_race_name())
    {
        case "drow":     subloc += "a humble";       break;
        case "dwarf":    subloc += "a proficient";   break;
        case "half-elf": subloc += "a highly adept"; break;
        case "elf":      subloc += "a humble";       break;
        case "human":    subloc += "a fabulous";     break;
        case "gnome":    subloc += "an agile";       break;
        case "goblin":   subloc += "an adequate";    break;
        case "kender":   subloc += "a proficient";   break;
        default:         subloc += "a";              break;
    }

    return subloc + " Mummer of Sybarus.\n";
}

public int
mwalk(string arg)
{
    if (arg == "on")
    {
	if (!TP->query_wiz_level())
	{
	    TP->set_m_in("arrives walking on "+
		TP->query_possessive() +" hands");        
	}

        write("You stand upon your hands with practiced "+
	    "ease and prepare to walk around on them.\nWhen you "+
	    "enter a room now, others will see:\n\t"+
	    capitalize(TP->query_real_name()) +" "+ TP->query_m_in() +"\n");
        say(QCTNAME(TP) +" balances upon "+ TP->query_possessive() +
	    " hands and prepares to walk around on them.\n");

        return 1;
    }
   
    if (arg == "off")
    {
	if (!TP->query_wiz_level())
	    TP->set_m_in("arrives");

        write("You flip back over onto your feet. When you "+
	    "enter a room, others will now see:\n\t"+
	    capitalize(TP->query_real_name()) +" "+ TP->query_m_in() +"\n");
	say(QCTNAME(TP) +" forsakes walking upon "+ TP->query_possessive() +
	    " hands and flips back over onto "+ TP->query_possessive() +
	    " feet.\n");

        return 1;
    }

    write("At present, when you enter a room others see:\n\t"+
	capitalize(TP->query_real_name()) +" "+ TP->query_m_in() +"\n"+
	"Try \""+ query_verb() +"\" 'on' / 'off' to toggle.\n");

    return 1;
}

public void
init(void)
{
    ::init();

    add_action(mwalk, "mwalk");
    add_action(mwalk, "mumwalk");
}
