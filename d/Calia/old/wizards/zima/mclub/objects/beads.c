

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <const.h>
#include "/d/Calia/domain.h"

#define MCLUB_SUBLOC "mclub_neck"


int worn = 0;
string inscription;

#include "defs.h"

int
is_worn()
{
    return worn;
}

int
remove(string str)
{
    object this, tp;
    if (str != "beads")
       return 0;
    this = THIS;
    tp = TP;
    if (!present(this, tp))
    {
       NF("You don't have them!\n");
       return 0;
    }
    if (!worn)

    {
       NF("You are not wearing them!\n");
       return 0;
    }
    tp->remove_subloc(MCLUB_SUBLOC);
    worn = 0;
    write("You remove the string of prayer beads.\n");
    say(QCTNAME(tp) + " removes a string of prayer beads.\n");
    set_no_show_composite(0);
    return 1;
}

void
leave_env(object old, object dest)
{
    if (worn) {
       if (living(old)) {
           if (member_array(MCLUB_SUBLOC, old->query_sublocs()) > -1)
              old->remove_subloc(MCLUB_SUBLOC);
           old->catch_msg("You remove the string of prayer beads.\n");
           tell_room(environment(old), QCTNAME(old)+" removes a "+
               "string of prayer beads.\n",old);
        }
        set_no_show_composite(0);
        worn = 0;
    }
    ::leave_env(old, dest);
}


void
init()
{
    ::init();
    add_action("wear","wear");
    add_action("remove","remove");
    set_alarm(1.0, 0.0, "crumble_check");
    set_alarm(1.5,0.0,"greet");
    add_action("inscribe","inscribe");
}

void
greet()
{
    string *soul_list;
    object e = environment(this_object());

    if (!living(e))
        remove_object();

    soul_list = e->query_cmdsoul_list();
    if (member_array(MCLUB_SOUL, soul_list) == -1) {
        e->add_cmdsoul(MCLUB_SOUL);
        e->update_hooks();
    }
    e->catch_msg("Glory the memory of the Ancients.\n");
}

void
init_arg(string str)
{
  if(!strlen(str))
     inscription = "a Seeker of Mystery";
  else
    inscription = str;
}

string
query_auto_load()
{
    if (!query_prop(OBJ_M_NO_DROP))
    {
       add_prop(OBJ_M_NO_DROP, 1);
       set_alarmv(1.0, 0.0, "remove_prop",({OBJ_M_NO_DROP}));
    }
    return MASTER+":"+inscription;
}


int
inscribe(string str)
{
  if(!strlen(str))
    {
   notify_fail("Inscribe what?\n");
   return 0;
    }

  if(TO->is_worn())
    {
    NF("You cannot properly inscribe the beads while wearing them.\n");
    return 0;
    }
  if(!strlen(inscription))
    {
    write("You carefully inscribe "+str+" on the beads.\n");
    tell_room(environment(TP),QCTNAME(TP)+" carefully inscribes "+
      "something on the beads.\n",TP);
    inscription = str;
    return 1;
    }

  else
    {
    notify_fail("The beads have already been inscribed.\n");
    return 0;
    }
}

string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (subloc == MCLUB_SUBLOC)
    {
       if(on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
         return "";

       if (for_obj != on)
          data = capitalize(on->query_pronoun()) + " is wearing a "+
            "string of prayer beads around "+on->query_possessive()+
            " neck.\n"+capitalize(on->query_pronoun())+" is "+inscription+
            ".\n";
       else
             data = "You are wearing a string of prayer beads around "+
               "your neck.\nYou are "+inscription+".\n";
       return data;
    }
}

string
long_func()
{
    string l;

   l = "They are a string of old stone prayer beads inscribed " +
       "with ancient runes. ";

   if (inscription)
       l += "The inscription reads: " + inscription + ". ";
   
   l += "The word \"mclist\" is also inscribed.\n";

   return l;
}

void
create_object()
{
    set_name(({"beads","mclub_beads",MCLUB_BEADS}));
    set_adj("stone prayer");
    set_short("string of stone prayer beads");
    set_pshort("strings of stone prayer beads");
    set_long("@@long_func");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_M_NO_SELL,"You cannot bring yourself to part with the "+
      "beads.\n");
    add_prop(OBJ_M_NO_DROP,"You cannot bring yourself to part with the "+
      "beads.\n");
}


/* Crumble if alignment less than 0 */
void
crumble_check()
{
    object e = environment(this_object());

    if (living(e) && (e->query_alignment() <0))
    {
        e->catch_msg("Your beads crumble to dust.\n");
        remove_object();
    }
}


int
wear(string str)
{
    object this, tp;
    if (str != "beads")
       return 0;
    this = THIS;
    tp = TP;
    if (!present(this, tp))
    {
       NF("You don't have them!\n");
       return 0;
    }
    if (worn)
    {
       NF("You are already wearing them!\n");
       return 0;
    }
    TP->add_subloc(MCLUB_SUBLOC, this);
    worn = 1;
    write("You wear the string of prayer beads.\n");
    say(QCTNAME(tp) + " wears a string of prayer beads.\n");
    this_object()->set_no_show_composite(1);
    return 1;
}

