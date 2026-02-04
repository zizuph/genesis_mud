/*
 * Explorer guild item
 * 
 * Tomas -- Dec. 1999
 *
 * CLUB CLOSED BY NERULL, 2019
 */


#include "/d/Terel/include/Terel.h"
inherit "/std/armour";

#include <composite.h>
#include <std.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Terel/clubs/explorer/include/explorer_club.h"
// #include "/w/tomas/clubs/explorer/include/explorer_club.h"

#define E_CLONE_LOG "/d/Terel/clubs/explorer/ring_clone_log"
#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 5000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#pragma save_binary
#pragma strict_types

private void add_explorer_soul(object ob);
private void reject_explorer_soul(object ob);

string query_auto_load() { return MASTER + ":"; }

/* cannot be both recoverable and autoloadable */
string query_recover() { return 0; }

void
create_armour()
{
    if (!IS_CLONE)
        return;

    set_name(EXPLORER_RING);
    add_name(({"signet", "explorers signet", "explorer's signet","ring",
               "explorers ring","explorer's ring","_leader_ring"}));
    add_adj(({"mithril","ring"}));
    set_short("mithril signet ring");

    set_long("The signet ring bears the seal of the Terellian Explorers " +
        "of Arcanum. The ring looks like it was forged from the finest mithril " +
        "available by a master craftsman., try <exphelp>.\n");

   
    set_ac(1 + random(3));
    set_slots(A_ANY_FINGER);
    set_looseness(0);
    set_wf(TO);
    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 15);
    add_prop(OBJ_M_NO_DROP,"Oddly enough, you can't seem to "+
        "do that.\n");
    add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
        "for you to simply give it away.\n");
    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
    seteuid(getuid());
    SCROLLING_LOG(E_CLONE_LOG, capitalize(TP->query_real_name()) +
            " was cloned leader ring. <--");
   
}


mixed
wear(object ob)
{
   //TP->add_subloc(EXPLORER_SUBLOC, TO);
   //TP->add_prop("_wearing_exp_ring",1);
   //TP->update_hooks();
   return 0;

}


mixed
remove(object ob)
{
   // TP->remove_subloc(EXPLORER_SUBLOC);
    //TP->remove_prop("_wearing_exp_ring");
    return 0;
}



public void
enter_env(object dest, object old)
{
    set_alarm(3.0, 0.0, &add_explorer_soul(dest));
    ::enter_env(dest, old);
}


private void
add_explorer_soul(object ob)
{
    //ob->add_cmdsoul(EXPLORER_SOUL);
    //ob->add_prop(EXPLORER_PROP, 1);
    //ob->add_prop(LEADER_PROP,1);   /* Leader of the Explorers */
    //ob->update_hooks();
	
	ob->catch_msg("Unfortunately, the Genesis administration have decided "
	+"to close the Explorers club. You are no longer an "
	+"Explorer of the Arcane anymore!\n" + 
    "The "+ short() +" falls to the ground shattering into " +
    "several small pieces.\n");
		
	remove_object();
	
}

void
reject_explorer_soul(object ob)
{
    ob->catch_msg("You are not a Explorer of the Arcane!\n" + 
        "The "+ short() +" falls to the ground shattering into " +
        "several small pieces.\n");
    remove_object();
} 

void
leave_env(object from, object to)
{
    int app;
  
    if (!from) 
    {
        ::leave_env(from, to);
        return;
    }
    
    from->remove_cmdsoul(EXPLORER_SOUL);
    from->update_hooks();

    if (from->query_prop(EXPLORER_PROP))
        from->remove_prop(EXPLORER_PROP);  
    if (from->query_prop(LEADER_PROP))
        from->remove_prop(LEADER_PROP);     
    if (!from->query_wiz_level())


    ::leave_env(from, to);
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - the subloc string
 *                on      - the wearer
 *                for_obj - the one looking
 * Returns:           The string that is to be seen (subloc)
 */
string
show_subloc(string subloc, object on, object for_obj)
{
   
    if (subloc != EXPLORER_SUBLOC)
        return this_player()->show_subloc(subloc, on, for_obj);
  
    if (for_obj == on)
        return "You are the leader of the Explorers of Arcane.\n";
    else
        return capitalize(PRONOUN(on)) +" is the leader" +
               " of the Explorers of the Arcanum.\n";
}




void
init()
{
    ::init();
}

