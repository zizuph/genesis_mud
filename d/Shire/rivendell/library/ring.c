/*
 * This ring designates the wearer as a librarian of the Rivendell library.
 * Those who have it can maintain the library.
 *
 * To make a mortal a librarian/biblosoph of the library clone this ring 
 * into the environment so the mortal can pick it:
 *
 *      clone -e /d/Shire/rivendell/library/ring.c
 *
 * Finwe, Jan 2019
 */


inherit "/std/armour";

#include <composite.h>
#include <std.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Shire/sys/defs.h"
#include "local.h"

#pragma save_binary
#pragma strict_types

//#define LIBRARIAN   "_riv_librarian"
#define LIB_SUBLOC  "_riv_librarian_subloc"

//private void add_explorer_soul(object ob);
//private void reject_explorer_soul(object ob);

string query_auto_load() { return MASTER + ":"; }

/* cannot be both recoverable and autoloadable */
string query_recover() { return 0; }

int throw_it();

void
create_armour()
{
    if (!IS_CLONE)
        return;

    set_name(LIBRARIAN);
    add_name(({"signet", "ring", "polished sapphire ring", "polished ring"}));
     set_short("polished sapphire ring");
    set_long("This ring is made of white gold and has a large sapphire set " +
        "in the center. The ring is polished and the gem sparkles in " +
        "the light. The ring is given to those who are a Bibliosoph " +
        "of the Library of Imladris. Some words are inscribed inside the ring.\n");

    set_ac(1 + random(3));
    set_slots(A_ANY_FINGER);
    set_looseness(0);
    set_wf(TO);
    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 15);
    add_prop(OBJ_M_NO_DROP,"You are unable to drop the ring. If you " +
        "want to get rid of it, read the words inscribed inside the ring.\n");
    add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
        "for you to simply give it away.\n");
    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
    seteuid(getuid());

    add_item(({"words", "inscription"}), 
        "They are instructions inscribed inside the ring.\n");
    add_cmd_item(({"inscriptions","words"}), 
        "read", "@@read_words@@");
}


mixed
wear(object ob)
{
   TP->add_subloc(LIB_SUBLOC, TO);
   TP->add_prop("_wearing_riv_lib_ring",1);
   return 0;
}


mixed
remove(object ob)
{
    TP->remove_subloc(LIB_SUBLOC);
    TP->remove_prop("_wearing_riv_lib_ring",1);
    return 0;
}


public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
  remove_name(LIBRARIAN);
  if(present(LIBRARIAN,E(TO)))
    {
      tell_room(E(TO),"You throw the duplicate " + short() + " away.\n");
      remove_object();
      return;
    }

  add_name(LIBRARIAN);
  if(living(E(TO)))
    dest->add_subloc(LIBRARIAN, this_object());
}

void
leave_env(object from, object to)
{
    if (!from)
    {
        ::leave_env(from, to);
        return;
    }


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

    if (subloc != LIB_SUBLOC)
        return this_player()->show_subloc(subloc, on, for_obj);

    if (for_obj == on)
        return "You are a Bibliosoph of the Library of Imladris.\n";
    else
        return capitalize(HE_SHE(on)) +" is a Bibliosoph of the Library of Imladris.\n";
}

int
libdrop(string s)
{
    if(s !="ring")
    {
        NF("Drop what, the " + short() + "? When you drop the " + short() + 
            ", you will no longer be a Bibliosoph of the Library of Imladris.\n");
        return 0;
    }
    else
    {
        TP->catch_msg("You drop the " + short() + ". It falls to the " +
            "ground and explodes. You are no longer a Bibliosoph of the Library of Imladris.\n");
        say(QCTNAME(TP)+ " drops a " +short()+ ". It falls to the " +
            "ground and explodes.\n"); 
        set_alarm(4.5, 0.0, &throw_it());
        return 1;
    }
}


int
throw_it()
{
    TO->remove_object();
    return 1;
}

string read_words()
{
    return "Inside the ring you read:\n\n" + 
        "    libdrop ring - Drop the ring. This will remove you as a Bibliosoph.\n\n";
}

void
init()
{
    ::init();
    add_action("libdrop", "libdrop");
}
