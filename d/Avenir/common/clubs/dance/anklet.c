// -*-C++-*-
// file name: 	  /d/Avenir/common/clubs/dance/anklet
// creator(s):	  Gracie&Tep	
// last update:	  Lilith March 26, 1997
// purpose:       The guild object for the minor guild
//                       The Dancers of Veils 
//                in Bazaar, City of Sybarus, Avenir
// note:  
// bug(s):
// to-do:


#include <composite.h>
#include "/d/Avenir/common/clubs/dance/dance_club.h"
#define ANKLET_SUBLOC "_anklet_subloc"

#pragma save_binary

inherit "/std/object";

private void reject_anklet(object ob);
private void do_jingle(object ob);

string
query_auto_load() { return MASTER + ":"; }

string
query_recover() { return 0; }

void
create_object()
{
    set_name("anklet");
    add_name(ANKLET);
    add_name(({"ankle bells", "anklets"}));
    set_short("pair of ankle bells");
    set_long("A pair of anklets with dozens of little silver "+
        "bells attached. These ankle bells are vital to proper "+
	"execution of many dances. Typing <bells on> will make "+
        "you wear them, and <bells off> will remove them.\n");

    add_item(({"bells", "bell"}),
	"These silver bells have a soft, high tone. They jingle with "+
	"every step. There are dozens of them on each anklet.\n");
    add_cmd_item("bells", "remove", "You have to type <bells off>.\n");
    add_cmd_item("bells", "wear", "You have to type <bells on>.\n");

    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP,"Oddly enough, the ankle bells cannot "+
        "be dropped.\n");
    add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
	"for you to simply give it away.\n");
    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
    seteuid(getuid());

}

void
init()
{
    ::init();
    add_action("do_bells", "bells");
    add_action("jingle_me", "djingle");
}

/*
 * This function makes the bells wearable w/o taking up an entire
 * armour slot. When worn, the subloc is shown and the object is
 * set_no_show_composite true, so it doesn't show in inventory.
 * When removed, the opposite occurs.
 */
int
do_bells(string arg)
{
    notify_fail("Do what with the ankle bells?\n");
    if (!arg) return 0;

    if (arg == "on")
    {
        TP->catch_msg("You wear the ankle bells around your ankles.\n");
        say(QCTNAME(TP) +" wears bells on "+ TP->query_possessive() +
            " ankles.\n");
        TP->add_subloc(ANKLET_SUBLOC, TO);
        set_no_show_composite(1); 
        if (!TP->query_wiz_level())
            TP->set_m_in("arrives with bells jingling");
        return 1;
    }
    if (arg == "off")
    {
        TP->catch_msg("You remove the ankle bells from around your ankles.\n");
        say(QCTNAME(TP) +" removes ankle bells from "+ TP->query_possessive() +
          " ankles.\n");
        TP->remove_subloc(ANKLET_SUBLOC, TO);
        set_no_show_composite(0);     
        if (!TP->query_wiz_level())
            TP->set_m_in("arrives");
        return 1;
    }    
}

void
enter_env(object dest, object old) 
{
    if (dest->query_gender() == G_MALE ||
        (RACE == "hobbit" || RACE == "goblin" || RACE == "dwarf"))
        set_alarm(4.0, 0.0, &reject_anklet(dest)); 
    else 
        set_alarm(4.0, 0.0, &do_jingle(dest));  
    ::enter_env(dest, old);    
}

void
leave_env(object from, object to)
{
  
    if (!interactive(from)) 
    {
        ::leave_env(from, to);
        return;
    }

    if (!from->query_wiz_level())
    {
        from->set_m_in("arrives");
        from->set_m_out("leaves");
    }
    ::leave_env(from, to);
}


private void
reject_anklet(object ob) 
{
    ob->catch_msg("Only a Dancer of the Veil may have the ankle bells!\n" +
        "The anklets with silver bells disintegrate before "+
        "your eyes! A sudden breeze blows the dust away.\n");
    remove_object();
}

private void
do_jingle(object ob)
{
    ob->catch_msg("The silver ankle bells jingle merrily.\n");    
}

static int
jingle_me(string str)
{
    notify_fail("Djingle "+ str+ " cannot be done.\n");
    if (str && str != "ankle bells")    
        return 0;

    TP->catch_msg("You jingle your ankle bells.\nThe dozens of small silver"+
        " bells make a delightful cascade of tinny sound.\n");
    say(QCTNAME(TP) +" jingles her ankle bells. They make a delightful "+
        "cascade of tinny sound.\n");
    return 1;
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (subloc == ANKLET_SUBLOC)
    {
        if (for_obj != on)
	    data = capitalize(on->query_pronoun()) + 
	           " is wearing ankle bells.\n";
        else
	    data = "You are wearing ankle bells.\n";
        return data;
    }
}
