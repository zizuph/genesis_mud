// -*-C++-*-
// file name: /d/Avenir/common/clubs/dance/veil"
// creator(s):  Grace
// last update: Lilith 27 March 1997
// purpose:     The guild object for the minor guild
//                    The Dancers of Veils 
//              in Bazaar, City of Sybarus, Avenir
//
// note:        Autoloadable. Go to clubs/dance/clubroom to restore it.
// bug(s):
// to-do:     
#pragma strict_types

#include <wa_types.h>
#include "/d/Avenir/common/clubs/dance/dance_club.h"

inherit "/std/object";
inherit "/lib/wearable_item";

public string
query_auto_load(void)	{ return MASTER + ":"; }

// cannot be both recoverable and autoloadable
public string
query_recover(void)	{ return 0; }

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("veil");
    add_name(VEIL);
    add_adj(({"translucent","silk"}));
    set_short("translucent silk veil");
    set_long("This lovely veil is as light as air and nearly as "+
        "transparent. It is rather small, and is usually worn over "+
	"the face. It will enhance your appearance and add to your "+
	"mystique as a Dancer of Veils.\n"+
	"For more information about being a Dancer of Veils, try "+
	"<dhelp>, <danhelp>, or <dancehelp>.\n");

    set_slots(A_EYES); 
  
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_DROP,"Oddly enough, you can't seem to"+
        " do that.\n");
    add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
	"for you to simply give it away.\n");
    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
}


private void
add_dancer_soul(object ob)
{
    ob->add_cmdsoul(DANCE_SOUL);
    ob->add_subloc(DANCE_SUBLOC, TO);
    ob->add_prop(DANCE_PROP, 1);
    ob->set_appearance_offset(-50);
    ob->update_hooks();
}

private void
reject_dancer_soul(object ob)
{
    ob->catch_tell("Only a Dancer of the Veil may have a veil!\n" + 
	"The translucent silk veil is caught in a "+
	"sudden breeze and blows away.\n");
    remove_object();
} 

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (dest->query_gender() == G_MALE ||
        (RACE == "hobbit" || RACE == "goblin" || RACE == "dwarf"))
        set_alarm(3.0, 0.0, &reject_dancer_soul(dest));
    else
        set_alarm(3.0, 0.0, &add_dancer_soul(dest));
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);

    from->remove_cmdsoul(DANCE_SOUL);
    from->remove_subloc(DANCE_SUBLOC);
    from->remove_prop(DANCE_PROP);
    from->update_hooks();
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - the subloc string
 *		  on      - the wearer
 *		  for_obj - the one looking
 * Returns:	  The string that is to be seen (subloc)
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != DANCE_SUBLOC)
        return "";
  
    if (for_obj == on)
        return "You have about you an aura of feminine mystique.\n";
    else
        return "She has about her an aura of feminine mystique.\n";
}


public int
dlower(string str)
{
    if (str) 
    {
        notify_fail("Dlower "+ str+ " cannot be done.\n");
        return 0;
    }

    if (!query_worn()) 
    {
        write("You need to be wearing the veil, first.\n");
        return 1;
    }

    write("You lower your veil in a coquettish display of modesty.\n");
    say(QCTNAME(TP) +" lowers a translucent silk veil over her face in a "+
        "coquettish display of modesty.\n");
    return 1;
}

public void
init(void)
{
    ::init();
    add_action(dlower, "dlower");
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
