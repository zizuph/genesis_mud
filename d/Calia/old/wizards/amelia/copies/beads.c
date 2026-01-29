

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "/d/Calia/domain.h"

#define MCLUB_CMDSOUL "/d/Calia/digit/mclub/mclub"
#define MCLUB_SUBLOC "mclub_neck"


int worn = 0;
string inscription;

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
leave_env(object dest, object old)
{
    object tp = this_player();

    if (worn) {
       if (member_array(MCLUB_SUBLOC, tp->query_sublocs()) > -1)
          tp->remove_subloc(MCLUB_SUBLOC);
       tp->catch_msg("You remove the string of prayer beads.\n");
       tell_room(environment(tp), QCTNAME(tp)+" removes a "+
          "string of prayer beads.\n",tp);
       this_object()->set_no_show_composite(0);
       worn = 0;
    }
    ::leave_env(dest,old);
}

void
init()
{
    object tp = this_player();

    ::init();
    add_action("wear","wear");
    add_action("remove","remove");
    set_alarm(1.5,0.0,"greet");
    add_action("inscribe","inscribe");
}

void
greet()
{
    this_player()->catch_msg("Glory the memory of the Ancients.\n");
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
       call_out("remove_prop",1,OBJ_M_NO_DROP);
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
    return
        "They are a string of old stone prayer beads inscribed "+
        "with ancient runes." +
       "\n";
}

void
create_object()
{
    set_name(({"beads","mclub_beads"}));
    set_adj("stone prayer");
    set_short("string of stone prayer beads");
    set_pshort("strings of stone prayer beads");
    set_long("@@long_func");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
}

void
crumble_check()
{
    string *soul_list;
    object e = environment(this_object());
    soul_list = environment(this_object())->query_cmdsoul_list();
    if (living(e) && (e->query_alignment() <0))
    {
        e->catch_msg("Your beads crumble to dust.\n");
        remove_object();
    }
    if (member_array(MCLUB_CMDSOUL,soul_list) == -1)
    {
        e->catch_msg("Your beads crumble to dust.\n");
        remove_object();
    }
}

void
enter_env(object dest, object old)
{
    object *obs;
    int i, change;
    set_alarm(1.0,0.0,"crumble_check");
    obs = all_inventory(dest);
    change = 0;
    for (i=0; i < sizeof(obs); i++)
    {
       if (obs[i]->id("mclub_beads") && obs[i] != this_object() &&
          obs[i]->is_worn() == is_worn())
       {
          obs[i]->remove_object();
          change++; 
       }
    }
    if (change)
       environment()->catch_msg("The strings combine into one!\n");
    ::enter_env(dest,old);
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

