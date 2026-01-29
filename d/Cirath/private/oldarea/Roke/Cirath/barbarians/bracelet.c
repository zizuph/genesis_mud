inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include "/d/Roke/Cirath/barbarians/skills.h"

#define BARB_SOUL BARBARIANS+"barb_soul"

string material;
int worn = 0;

query_auto_load()
{
  return MASTER;
}

void
create_object()
{
  if(TP->query_skill(BARB_SCORE)<10)
    material = "copper";
  else if(TP->query_skill(BARB_SCORE)<20)
    material = "silver";
  else if(TP->query_skill(BARB_SCORE)<30)
    material = "gold";
  else if(TP->query_skill(BARB_SCORE)<40)
    material = "adamant";
  else if(TP->query_skill(BARB_SCORE)>39)
    material = "nauseaus rubber";


  set_name("bracelet");
  add_name("barb_brac");
  set_short(material+" bracelet");
  set_adj(material);
  set_long("This is the bracelet that all true barbarians "+
           "have. It has no decorations "+
           "what so ever. If you want to know which commands "+
           "and emotes you have as a barbarian, just type "+
           "'help barbarian'.\n");

  add_prop(OBJ_I_WEIGHT, 250);
  add_prop(OBJ_I_VOLUME, 50);
  add_prop(OBJ_I_VALUE, 7500000);
  add_prop(OBJ_M_NO_DROP,1);
  add_prop(OBJ_I_NO_GIVE,1);
}

void
init()
{
  ::init();
  add_action("meditate", "meditate");
  add_action("sneak", "sneak");
  add_action("think", "think");
  add_action("ponder", "ponder");
  add_action("bsay","say");
  add_action("wear","wear");
  add_action("remove","remove");
  set_alarm(1.0, 0.0, "get_me_soul", TP);
  call_out("barbhail",3);
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
  string data;

  if (worn==1)
  {
    if (for_obj == on)
      data = "You are ";
    else
      data = capitalize(environment(this_object())->query_pronoun()) + " is ";

    data+="wearing the "+material+" bracelet on the right arm.\n";
    return data;
  }
}

enter_env(object dest,object old)
{
  remove_name("barb_brac");
  if(present("barb_brac",E(TO)))
  {
    tell_room(E(TO),"The bracelets melts together in some mysterical way.\n");
    remove_object();
    return;
  }
  add_name("barb_brac");
  if(living(E(TO)))
    dest->add_subloc("barb_brac", this_object());
}

public void
leave_env(object from, object to)
{
  this_player()->remove_subloc("barb_brac");
}

int
query_brutelevel(object tp)
{
  int cxp,qxp,txp;

  cxp = tp->query_exp_combat();
  txp = tp->query_exp();
  qxp = txp - cxp;

  if (cxp > 2*qxp) return 2;

  return 1;
}

string
query_barb_talk(string text)
{
  string *str,retmsg;
  int brute,len,i;

  brute = query_brutelevel(TP);

  str = explode(text," ");

  for(i = 0; i < sizeof(str); i++)
  {
    len = strlen(str[i]);

  if(brute == 2)
  {
    if(len < 4)
      str[i] = "Ugh";
    else if(len > 3 && len < 7)
      str[i] = "Ugga";
    else if(len > 6 && len < 10)
      str[i] = "Uggaugh";
    else
      str[i] = "Uggaughugh";
    }
    else
    {
     if(len < 4)
      str[i] = "ynk";
    else if(len > 3 && len < 7)
      str[i] = "ynka";
    else if(len > 6 && len < 10)
      str[i] = "ynkynk";
    else
      str[i] = "ynkaynkynk";
   }
  }

  retmsg = implode(str," ");

  return retmsg;
}

int meditate()
{
  write("What? A meditating barbarian? You maybe think you're "+
        "some kind of monk or something?\n");
  say(QCTNAME(TP)+" tries to meditate, but have you ever "+
        "seen a meditating barbarian.\n");
  return 1;
}

int bsay(string str)
{
  string btxt,way;
  object *oblist;
  int i,brute;

  btxt  = query_barb_talk(str);
  brute = query_brutelevel(TP);

  if(brute == 2)
    way = " roars: ";
  else
    way = " whines: ";

  if (!strlen(str))
  {
      NF("Say what?\n");
      return 0;
  }
  if (TP->query_get_echo())
    write("You say (changed): " + str + "\n");
  else
    write("Ok.\n");

  oblist = all_inventory(environment(TP));
  for (i=0; i < sizeof(oblist); i++)
  {
    if ((living(oblist[i]) && oblist[i] != TP))
    {
      if (oblist[i]->query_guild_member("The Barbarian "+
        "Herd") || oblist[i]->query_skill(SS_LANGUAGE) > 49)
        oblist[i]->catch_msg(QCTNAME(TP) + way +
          break_string(str + "\n", 70));
      else
        oblist[i]->catch_msg(QCTNAME(TP) + way +
          break_string(btxt + "\n", 70));
    }
  }

  return 1;

}

int sneak(string str)
{
  write("CLOMP! CLOMP! You really try to sneak but fail completely.\n");
  say("CLOMP! CLOMP! "+QCTNAME(TP)+" tries to sneak but fails.\n");
  return 1;
}

int think(string str)
{
  write("You try to think but fail.\n");
  say(QCTNAME(TP)+" tries to thing, but fails completely.\n");
  return 1;
}

int ponder(string str)
{
  write("You try to ponder but realize that you forgot how to.\n");
  say(QCTNAME(TP)+" tries to meditate but seems to forgotten how to.\n");
  return 1;
}

int wear(string str)
{
  if (str=="bracelet");
  {
    if (worn)
    {
      NF("You're already wearing your "+material+" bracelet.");
      return 0;
    }

    worn = 1;

    write("You wear your "+material+" bracelet on the right arm.\n");
    say(QCTNAME(TP)+" wears "+TP->query_possessive()+" "+material+
      " bracelet on the right arm.\n");

    return 1;
  }

  NF("Wear what?");
  return 0;
}

int remove(string str)
{
  if (str=="bracelet");
  {
    if (!worn)
    {
      NF("You're not wearing your "+material+" bracelet.");
      return 0;
    }

    worn = 0;

    write("You remove your "+material+" bracelet.\n");
    say(QCTNAME(TP)+" removes "+TP->query_possessive()+" "+material+
      " bracelet.\n");

    return 1;
  }

  NF("Remove what?");
  return 0;
}

void
get_me_soul(object ob)
{
  int i;
  string *souls;

  seteuid(getuid());
  souls = ob->query_cmdsoul_list();
  for (i = 0; i < sizeof(souls); i++)
    ob->remove_cmdsoul(souls[i]);

  ob->add_cmdsoul(BARB_SOUL);

  for(i = 0; i < sizeof(souls); i++)
    if((souls[i] != BARB_SOUL))
      ob->add_cmdsoul(souls[i]);
  ob->update_hooks();
}

int
barbhail()
{
  write("Hail Barbarian!!!\nHail Crom!!!\nLets kill and slay.\n"+
        "Lets chop and stab.\nMay your weapon stay wet and your armour "+
        "stained by blood.\nMay your enemies fall like grains in the "+
        "wind.\nMay the unfaithful suffer the eternal death!.\n\nMay Crom follow you at your struggle.\n\n"+
        "Hail true Barbarian!!!\n");
  return 1;
}
