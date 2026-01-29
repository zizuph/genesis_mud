inherit "/std/armour";
 
#include "/d/Rhovanion/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
 
#include "fr_ring.h"
 
string person,inscription;
 
void
create_armour()
{
  set_name(({"ring", RING_ID }));
  set_adj(({"green","jade","ornamented"}));
  set_short(RING_NAME);
  set_long("@@long_desc");
  set_ac(0);
  set_at(A_ANY_FINGER);
 
  add_prop(OBJ_I_VOLUME, 50);
  add_prop(OBJ_I_VALUE,5000000);
  add_prop(OBJ_M_NO_SELL,"The shopkeeper stares at you "+
                         "with disdain and refuses to buy the "+short()+
                         ".\n");
  add_prop(OBJ_M_NO_DROP,"If you REALLY want to get rid of the "+
                         RING_NAME+" don't just drop it!\n");
  add_item("ornament","The intricate golden ornament, which runs "+
           "on the surface of this "+RING_NAME+" features a "+
           "dragon. You feel that if you are an owner of the "+
           "ring, and have a friend, you can command dragon "+
           "to help you communicate the friend even over long "+
           "distances.\n");
}
 
int set_person(string arg)
{
  if (arg)
  {
    person=arg;
    return 1;
  }
  return 0;
}
 
int set_inscription(string arg)
{
  if (arg)
  {
    inscription=arg;
    return 1;
  }
  return 0;
}
 
string query_inscription()
{
    return inscription;
}
 
string query_person()
{
   return person;
}
 
string long_desc()
{
    if (!person)
       return "This is a "+RING_NAME+" with a golden ornament running "+
              "around it.\n";
    return "This is a "+RING_NAME+" with a golden ornament running "+
           "around it. The ring has an inscription: "+
           inscription+"\n"+
           "To get help on commands available, enter: "+
           "help friendship ring .\n";
}
 
int
tell_friend(string arg)
{
    object ob,rob;
 
    NF("Tell your friend what?\n");
    if (!arg)
      return 0;
    NF("You don't have a friend whom you could communicate "+
       "using this ring.\n");
    if (!person)
      return 0;
    NF("You must wear your ring in order to be able to use it "+
       "properly!\n");
    if (!TO->query_worn())
      return 0;
    ob = find_player(person);
    NF("The ornament on the ring moves for a moment, "+
                "but the dragon seems to be unable to locate "+
                CAP(person)+".\n");
    if (!ob || ob->query_linkdead())
      return 0;
    if (TP->query_mana() < TELL_COST) {
     NF("You command the dragon to help you "+
        "contact your friend, but feel mentally too weak "+
        "to be able to send the message.\n");
     return 0;
    }
    rob=present(RING_ID,ob);
    if (rob->query_worn())
    {
     TP->add_mana(-TELL_COST);
    tell_room(ENV(ob),QCTNAME(ob)+" closes his eyes for a moment.\n",ob);
     ob->catch_msg("You close your eyes for a moment, as you "+
                  "sense an apparition of a small golden dragon "+
                  "in your mind. It tells you a message from "+
                  QCTNAME(TP)+": "+arg+"\n");
     if (TP->query_get_echo())
      TP->catch_msg("You command the ornament on the ring to find and "+
                    "tell "+QTNAME(ob)+": "+arg+"\n");
     TP->catch_msg("Ok.\n");
     tell_room(ENV(TP),QCTNAME(TP)+" closes his eyes for a moment... "+
              "\nYou think you notice something like a golden halo "+
              "around his hand, but the vision fades "+
              "immediately.\n",TP);
     return 1;
    }
    TP->add_mana(-TELL_COST/2);
    TP->catch_msg("You command the ornament on the ring to find and "+
                  "tell "+CAP(person)+" a message, but you feel that "+
                  HE(ob)+" did not receive it.\n");
    return 1;
}
 
void init_arg(string arg)
{
  sscanf(arg,"%s!%s",person,inscription);
}
 
string
query_auto_load()
{
  return MASTER+":"+ person+"!"+inscription;
}
 
void init()
{
    ::init();
    add_action("tell_friend","ftell");
    add_action("ring_help","help");
    add_action("f_hug","hug");
    add_action("f_mourn","fmourn");
    add_action("f_kill","fkill");
 
}
int f_hug(string arg)
{
  object ob;
 
    if (!TO->query_worn())
       return 0;
    if ((!person) || (LOW(arg) != person))
       return 0;
    NF("Hug whom?\n");
    ob=present(person,ENV(TP));
    if (!ob) return 0;
 
    TP->catch_msg("You give your best friend "+CAP(person)+
                  "a mighty bearhug out of pure joy of seeing "+
                  HIM(ob)+"!\n");
    ob->catch_msg("Your best friend "+QTNAME(TP)+" gives you a "+
                  "mighty bearhug out of pure joy!\n");
 
    tell_room(ENV(TP),QCTNAME(TP)+" gives "+QTNAME(ob)+
             "a mighty bearhug out of pure joy!\n",({ TP, ob }));
 
    return 1;
 
}
 
int f_mourn()
{
    NF("You must wear the ring in order to be able to use this "+
       "emotion.\n");
    if (!TO->query_worn())
       return 0;
    NF("Looking at the ring, you notice that it bears no "+
       "name... Hence you don't know whom to mourn.\n");
    if (!person)
       return 0;
 
    write("You mourn the loss of your best friend.\n");
    say(QCTNAME(TP)+" mourns the loss of his best friend.\n");
 
    return 1;
}
 
int f_kill()
{
    NF("You must wear the ring in order to be able to use this "+
       "emotion.\n");
    if (!TO->query_worn())
       return 0;
 
    write("You clench your fists and swear to gain the "+
          "vengeance on those who want to harm your friend!\n");
    say(QCTNAME(TP)+" clenches "+HIS(TP)+" fists and swears "+
        "to gain vengeance on the people who dared to harm his "+
        "friend!\n");
 
    return 1;
}
 
int
ring_help(string arg)
{
    string str;
 
    if (!arg || arg!="friendship ring") return 0;
 
    if (!person)
      write("This ring can be used to communicate a friend of "+
          "yours over long distances. "+
          "However, to be able to "+
          "do that, you must first engrave it with the name "+
          "of your friend.\n");
    else
    write("This magical ring lets you communicate your friend "+
          CAP(person)+" over great distances. The available "+
          "commands are:\n"+
          "              ftell <message>      - try to send your "+
          "friend a message.\n"+
          "              hug <friend>         - give your friend a "+
          "mighty bearhug!\n"+
          "              fmourn               - mourn the death of "+
          "your friend.\n"+
          "              fkill                - swear to gain "+
          "vengeance upon those who dared to attack your friend!\n"+
          "              help friendship ring - get this help.\n");
    return 1;
}
 
query_recover() { return 0; }
 
