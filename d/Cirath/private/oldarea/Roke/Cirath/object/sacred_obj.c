inherit "/std/object";
#include "/d/Roke/common/defs.h"       /* THE HOLY TEMPLE ORDER */
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>

int worn;
string title;

query_auto_load()
{
  return MASTER;
}

create_object()
{
  set_name("brooch");
  set_adj("ametist");
  add_name("sarcred_brooch");
  set_short("ametist brooch");
  set_long("When you examine the brooch you notice a text line: \n"+
  "This is the brooch of The Holy Temple order. Type 'help brooch'. \n");
  add_prop(OBJ_I_NO_DROP,"Do you REALLY want to leave this society? \n");
  worn = 0;
}

void
init()
{
 ::init();
 TP->add_prop(CIRATHCLUB,1);
 call_out("hail_temple",3);
 add_action("wear_brooch","wear");   
 add_action("remove_brooch","remove");   
 add_action("help","help");
 add_action("cbless","cbless");
 call_out("title",1);
}

help(string s)
{
    if(s!="brooch")

        return 0;
    
    TP->catch_msg("These commands are available:\n"+
                  "cbless <player> -  bless another player. \n"+
                  "cadvice <player> - advice someone. \n");
    return 1;
}
static void tell_watcher(string str, object me, object enemy)
{
  object *ob;
  int i;

  ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
  ob -= ({ enemy });
  for (i = 0; i < sizeof(ob); i++)
    if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}

int remove_brooch(string str)
{
  if(str != "brooch") return 0;

  NF("But you're not wearing it!\n");
  if(!worn)
    return 0;

  worn = 0;

  this_object()->set_no_show_composite(0);

  say(QCTNAME(TP) + " removes the ametist brooch of The Hole Temple Order.\n");
  TP->catch_msg("You remove your ametist brooch.\n");

  return 1;
}

int wear_brooch(string str)
{
  if(str != "brooch") return 0;

  NF("You're already wearing it!\n");
  if(worn)
    return 0;
    
  NF("You really wish you had that item, don't you?\n");
  if(E(TO)!=TP)
    return 0;

  worn = 1;
  this_object()->set_no_show_composite(1); 
  say(QCTNAME(TP) + " wears the ametist brooch of The Holy Temple Order.\n"); 
  TP->catch_msg("You wear your ametist brooch.\n");

  return 1;
}


enter_env(object dest,object old)
{
  remove_name("sarcred_brooch");
  if(present("sarcred_brooch",E(TO)))
    {
      tell_room(E(TO),"You fool, you can't have two brooches.\n");
      remove_object();
      return;
    }

  add_name("sarcred_brooch");
  if(living(E(TO)))
    dest->add_subloc("sarcred_brooch", this_object());
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
  string data;

  if (for_obj == on)
    data = "You are ";
  else
    data = capitalize(environment(this_object())->query_pronoun()) + " is ";

  data+="a "+title+" member of The Holy Temple Order.\n";

  if (worn)
  {
    if(for_obj == on)
      data += "You are ";
    else
      data += capitalize(environment(this_object())->query_pronoun()) + " is ";

    data += "wearing an ametist brooch.\n";
  }

  return data;

}
int
title()
{
  if (TP->query_alignment() < 0) title = "damned";
  else if (TP->query_alignment() < 1000) title = "disgraced";
  else if (TP->query_alignment() < 1100) title = "holy";
  else if (TP->query_alignment() < 1200) title = "most holy";
  else if (TP->query_alignment() < 1300) title = "sacred";
  else if (TP->query_alignment() < 1400) title = "most sacred";
  else if (TP->query_alignment() < 1500) title = "supreme";
  else if (TP->query_alignment() < 1600) title = "most supreme";
  else if (TP->query_alignment() < 1700) title = "incredible";
  else if (TP->query_alignment() < 2500) title = "divine";
}

public void
leave_env(object from, object to)
{
  this_player()->remove_subloc("sacred_brooch");
}
int
query_alignlevel(object tp)
{
  int cxp;

  cxp = tp->query_alignment();

  if (cxp > 1000 ) return 2;

  return 1;
}

int
hail_temple()
{
write("Hail Holy Brother, and welcome to a new day in the service.\n");
return 1;
}
int cbless(string person)
{
  object *a,ob;
  string str;
  int align;

  align = query_alignlevel(TP);

  if (!person || person == "all")
    {
      if (align == 2)
      {
        write("You bless your companions in a mysterial way. You feel the precence of a "+
              "divine power.\n");
        say(QCTNAME(TP)+" blesses you in a mysterial way. You feel"+
            " that the gods are with you.\n");
      }
      else
      {
        write("You try to bless, but you are disgraced.\n");
        say(QCTNAME(TP)+" tries to bless you but he is disgraced.\n");
      }

      return 1;
    }
  
  a = CMDPARSE_ONE_ITEM(person,"kolla","kolla");

  NF("bless who?\n");
  if(!sizeof(a))
    return 0;

  ob = a[0];

  if(ob == TP)
    {
      TP->catch_msg("Bless yourself?\n");
      return 1;
    }
  
  if (align == 2)
  {
    TP->catch_msg(
      "You bless "+QTNAME(ob)+" in a mysterial way. You feel the gods answer you.\n");
    tell_watcher(QCTNAME(TP)+" blesses "+QTNAME(ob)+" in a mysterial way. "+
                 "The air becomes very peaceful.\n",TP,ob);
  
    ob->catch_msg(QCTNAME(TP)+" blesses you in a mysterial way. You feel very good.\n");
  }
  else
  {
    TP->catch_msg(
      "You try to bless "+QTNAME(ob)+". But you are disgraced.\n");
    tell_watcher(QCTNAME(TP)+" tries to bless "+QTNAME(ob)+" but fails. "+
                 "He is disgraced.\n",TP,ob);
    ob->catch_msg(
      QCTNAME(TP)+" tries to bless you. But he fails because he is disgraced.\n");
  }
  return 1;
}
