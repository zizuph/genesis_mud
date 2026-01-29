/*           R I C H   M E N S   C L U B
* 
* THE RMC PURSE, NPC VERSION
* (Captain of the Ship uses this)
*
* OK Tintin 95-02-08
*
* Made by Conan and Valeria 95-01-01
*
*
* Some more emotes added by Valeria 95-02-02
* Some wiz titles added by Conan   95-02-13
* Account funktions added by Valeria 95-02-15
* More active emotes Valeria 95-02-17
*
* Moved and Updated by Lunatari 05-12-14
*/

#pragma save_binary

inherit "/std/receptacle";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <money.h>

int thrown = 0;
string type;

void
create_container()
{
  string material,adjec;

  seteuid(getuid(TO));

  type = "purse";
  material = "leather";
  adjec = "small";

  set_name(type);
  add_name(PURSE_NPC_ID);
  set_adj(material);
  add_adj(adjec);
  set_short(adjec+" "+material+" "+type);
  set_long("This is a "+adjec+" "+material+" "+type+" that the "+
           "members of The Rich Men's Club have. It's "+
           "used to contain the huge amount of plats that "+
           "the members of this club has. There's an inscrition "+
           "on one side reading: Use <help rich> to get the "+
           "club emotes.\n");

  add_prop(CONT_I_WEIGHT, 100);
  add_prop(CONT_I_MAX_WEIGHT, 10000);
  add_prop(CONT_I_VOLUME, 150);
  add_prop(CONT_I_MAX_VOLUME, 10000);
  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_M_NO_DROP,1);
  add_prop(OBJ_I_NO_GIVE,1);
  add_prop(OBJ_I_NO_STEAL,1);
  add_prop(OBJ_M_NO_SELL,1);
}

enter_env(object dest,object old)
{
  ::enter_env(dest,old);
  remove_name("rich_purse");
  if(present("rich_purse",ENV(TO)))
  {
    tell_room(ENV(TO),"The purses melts together in some mysterical way.\n");
    set_alarm( 1.0, 0.0, "remove_me");
    return;
  }
  add_name("rich_purse");
  if(living(ENV(TO)))
    dest->add_subloc("rich_purse", this_object());
}

public void
leave_env(object from, object to)
{
  this_player()->remove_subloc("rich_purse");
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
  string data,title;
  int level;
  
  if (for_obj == on)
    data = "You are ";
  else
    data = capitalize(environment(this_object())->query_pronoun()) + " is ";

  seteuid(getuid(TO));
  data += "Member of The Rich Men's Club.\n";
  return data;
}

void init()
{
  ::init();
  
  add_action("rpat"      ,    "rpat");
  add_action("rsmile"    ,    "rsmile");
  add_action("rsmile2"   ,    "rsmile2");
  add_action("rdislike"  ,    "rdislike");
  add_action("rpoke"     ,    "rpoke");
  add_action("rgreet"    ,    "rgreet");
  add_action("roffer"    ,    "roffer");
  add_action("rdrop"    ,   "rdrop");
  add_action("rsulk"    ,   "rsulk");
  add_action("rpick"    ,   "rpick");
  add_action("rgrin"    ,   "rgrin");
  add_action("rconvince",   "rconvince");
  add_action("rassure"  ,   "rassure");
  add_action("rbusy"    ,   "rbusy");
  add_action("revaluate",   "revaluate");
  add_action("rsearch"  ,   "rsearch");
  add_action("rhold"    ,   "rhold");
}

int
rpat()
{
   write("You pat your "+type+" lovingly. It looks well filled.\n");
   say(QCTNAME(TP)+" pats "+HIS_HER(TP)+" "+type+" lovingly. It looks well filled.\n");
   return 1;
}

int
rsmile()
{
  write("You smile greedily over the big income of yours.\n");
  say(QCTNAME(TP)+" smiles so greedily over "+HIS_HER(TP)+" big income "+
     "that you almost feel sick.\n");
  return 1;
}

int
rsmile2()
{
  write("You smile wealthily.\n");
  say(QCTNAME(TP)+" smiles wealthily.\n");
  return 1;
}
int 
rdislike()
{
  write("You show, with an evil grin, how much you hate poor and greedy people.\n");
  say(QCTNAME(TP)+" shows you how much "+HE_SHE(TP)+" dislikes people as poor as you.\n");
  return 1;
}

int
rpoke()
{
  write("You poke everybody in the room, showing how much joy there is in money.\n");
  say(QCTNAME(TP)+" pokes you as "+HE_SHE(TP)+" shows you how much joy there is in money.\n");
  return 1;
}

int
rgreet(string s)
{
  object *a,ob, *obs;
  string str;
  int align, i;

  if (!s || s == "all")
  {
    write("You greet everyone even though they are poor and miserable creatures.\n");
    say(QCTNAME(TP)+" greets you even though "+HE_SHE(TP)+" knows you are poor "+
        "compared to "+HIM_HER(TP)+".\n");
    return 1;
  }

  if (s == "me")  
  {
    write("Greet yourself?\n");
    say(QCTNAME(TP)+" greets "+HIM_HER(TP)+"self because "+HE_SHE(TP)+" is so rich.\n");
    return 1;
  }
    
  NF("Greet who?\n");

  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  if (!sizeof(obs))  return 0;

  for (i=0; i<sizeof(obs); ++i)  
  {
    obs[i]->catch_msg(QCTNAME(TP)+" greets you although "+HE_SHE(TP)+" knows you are poor and miserable.\n");
    write("You greet "+COMPOSITE_LIVE(obs)+" even though "+HE_SHE(obs[i])+" is poor and miserable.\n");
  }
  tell_room(ENV(TP), QCTNAME(TP)+" greets "+QCOMPLIVE+
           " even though "+HE_SHE(TP)+" knows "+COMPOSITE_LIVE(obs)+" is poor and miserable.\n",({TP})+obs);

  return 1;
}

int
roffer(string s)
{
  object *a,ob, *obs;
  string str;
  int align, i;

  if (!s || s == "all")
  {
    write("You offer everyone a loan with a HUGE interest.\n");
    say(QCTNAME(TP)+" offers everyone a loan with HUGE interest.\n");
    return 1;
  }

  if (s == "me")  
  {
    write("Offer yourself?\n");
    say(QCTNAME(TP)+" offers "+HIM_HER(TP)+"self a loan with no interest.\n");
    return 1;
  }
    
  NF("Offer to whom?\n");

  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  if (!sizeof(obs))  return 0;
    
  for (i=0; i<sizeof(obs); ++i)  
  {
    obs[i]->catch_msg(QCTNAME(TP)+" offers you a loan with HUGE interest, "+
      "because "+HE_SHE(TP)+" thinks you need it badly.\n");
  }

  write("You offer "+COMPOSITE_LIVE(obs)+" a loan with HUGE interest. "+COMPOSITE_LIVE(obs)+
        " seems to need it badly.\n");
  tell_room(ENV(TP), QCTNAME(TP)+" offers a loan to "+QCOMPLIVE+
              " to a HUGE interest. "+COMPOSITE_LIVE(obs)+" looks happy.\n",({TP})+obs);

  return 1;
}

int
rtease(string s)
{
  object *a,ob, *obs;
  string str;
  int align, i;

  if (!s || s == "all")
  {
    write("You tease everyone because you think you are much richer than them. \n");
    say(QCTNAME(TP)+" teases you because "+HE_SHE(TP)+" thinks you are a poor one "+
        "compared to "+HIM_HER(TP)+".\n");
    return 1;
  }

  if (s == "me")  
  {
    write("Tease yourself?\n");
    say(QCTNAME(TP)+" teases "+HIM_HER(TP)+"self.\n");
    return 1;
  }
    
  NF("Tease who?\n");

  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  if (!sizeof(obs))  return 0;    
  {
    for (i=0; i<sizeof(obs); ++i)  
    {
      obs[i]->catch_msg(QCTNAME(TP)+" teases you because "+HE_SHE(TP)+" thinks you "+
        "are poorer than "+HE_SHE(TP)+" is.\n");
    }

    write("You tease "+COMPOSITE_LIVE(obs)+" because you think you are richer than "+COMPOSITE_LIVE(obs)+".\n");
    tell_room(ENV(TP), QCTNAME(TP)+" teases "+QCOMPLIVE+
          " because "+HE_SHE(TP)+" thinks "+HE_SHE(TP)+" is the richest around.\n",({TP})+obs);
  }
  return 1;
}

int
rcheck()
{
  write("You check your pockets for plats.\n");
  say(QCTNAME(TP)+" checks "+HIS_HER(TP)+" pockets for plats.\n");
  return 1;
}

int
rthink()
{
  write("You think hard about going on a money hunt.\n");
  say(QCTNAME(TP)+" looks like "+HE_SHE(TP)+" is thinking hard about going on a money hunt.\n");
  return 1;
}

int
rdrop()
{
  object ob;
  NF("You haven't got any coppers!\n");
  if (ob = present("copper coin",TP)) /* MAKE SURE YOU DROP A COPPER COIN */
  {
    write("You yawn and drop one copper coin just to make sure the worth of money.\n");
    say(QCTNAME(TP)+" yawns and smiles coldly as "+HE_SHE(TP)+" drops one copper coin.\n");
    ob->split_heap(1);
    ob->move(ENV(TP));
    return 1;
  }
  return 0;
}

int
rsulk()
{
  write("You sulk in the corner since your purse doesn't carry all your platinum coins coins.\n");
  say(QCTNAME(TP)+" sulks in the corner since the purse doesn't carry all "+HIS_HER(TP)+" coins.\n");
  return 1;
}

int
rtoss()
{
  
  int styrka;
  object ob;

  NF("You haven't got any lovely plats!\n");
  if (ob = present("platinum coin",TP))
  {
    if (thrown)
    {
      write("You already have one coin in the air.\n");
      return 1;
    }
    else
    {
      styrka = TP->query_stat(SS_STR)/40;
      write("You toss a platinum coin high up in the air.\n");
      say(QCTNAME(TP)+" tosses a platinum coin high up in the air.\n");
      thrown = 1;
      set_alarm(itof(styrka), 0.0, "catch_coin");
      return 1;
    }
    return 0;
  }
}

int
catch_coin()
{
  int dexxy,strength;
  object ob;
  dexxy = TP->query_stat(SS_DEX)/10 + random(20);
  strength  = TP->query_stat(SS_STR)/10;

  if (ob = present("platinum coin",TP))
    {
    if (dexxy < strength )
      {
        write("You fumble and the platinum coin falls down on the ground.\n");
        say("Suddenly a platinum coin falls down from above.\n"+
        QCTNAME(TP)+" fumbles with the platinum coin and it falls down to the ground.\n");
        TP->command("sigh");
        ob->split_heap(1);
        ob->move(ENV(TP));
        thrown = 0;
        return 1;
      }
    write("You catch the platinum coin without any problem.\n");
    say("Suddenly a platinum coin falls down from above.\n");
    say(QCTNAME(TP)+" caught it without any problem\n");
    TP->command("cheer");
    thrown = 0;
    return 1;
    }
  return 1;
}

int 
rpick()
{
  write("You feel the smell from gold and platinum coins here.\n");
         set_alarm(3.0, 0.0, "getta_coins");
  say(QCTNAME(TP)+" stops as if "+HE_SHE(TP)+" is smelling something.\n");
  return 1;
}

int
getta_coins(object ob)
{
  TP->command("get coins");
  write("You giggle.\n");
  say(QCTNAME(TP)+" giggles greedily.\n");
  return 1;
}

int
rsearch()
{
  write("You start to turn your "+type+" inside out realizing that you spent way too much "+
        "money at the pub last night.\n");
  say(QCTNAME(TP)+" turns "+HIS_HER(TP)+" "+type+" inside out realizing that "+
      HE_SHE(TP)+" spent way too much money at the pub last night.\n");
  return 1;
}

int
rgrin()
{
  write("You grin as you think of the amount of money you have.\n");
  say(QCTNAME(TP)+" shows with a wealthy grin that "+HE_SHE(TP)+" got lots of plats.\n");
  return 1;
}

int
rconvince(string s)
{
  object *a,ob, *obs;
  string str;
  int align, i;

  if (!s || s == "all")
  {
    write("You can't convince them all, try one at a time.../n");
    return 1;
  }

  if (s == "me")  
  {
    write("Convince yourself?\n");
    return 1;
  }
    
  NF("Convince who?\n");

  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  if (!sizeof(obs))  return 0;    
  {
    for (i=0; i<sizeof(obs); ++i)  
    {
      obs[i]->catch_msg(QCTNAME(TP)+" tries to convince you that the only thing that is important is money.\n");
    }

    write("You try to convince "+COMPOSITE_LIVE(obs)+" that the only thing that is important is money.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" tries to convince "+QCOMPLIVE+
          " that the only thing that is important is money.\n",({TP})+obs);
  }
  return 1;
}

int
rassure(string s)
{
  object *a,ob, *obs;
  string str;
  int align, i;

  if (!s || s == "all")
  {
    write("You assure your companions that the future will be good for the market./n");
    say(QCTNAME(TP)+" assures you that the future will be good for the market.\n");
    return 1;
  }

  if (s == "me")  
  {
    write("Assure yourself? Are you that insecure about the future?\n");
    return 1;
  }
    
  NF("Assure who?\n");

  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  if (!sizeof(obs))  return 0;    
  {
    for (i=0; i<sizeof(obs); ++i)  
    {
      obs[i]->catch_msg(QCTNAME(TP)+" assures you that the future will be good for the market.\n");
    }

    write("You assure "+COMPOSITE_LIVE(obs)+" that the future will be good for the market.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" assures "+QCOMPLIVE+
          " that the future will be good for the market.\n",({TP})+obs);
  }
  return 1;
}

int
rbusy()
{
  write("You tell the audience that you are busy making money.\n");
  say(QCTNAME(TP)+" are busy collecting plats.\n");
  return 1;
}

int
revaluate()
{
  write("You announce your inner feelings about how you evaluate other people.\n");
  say(QCTNAME(TP)+" announces that the only way to evaluate a person is to check that person's bank account!\n");
  return 1;
}

int
rwalk()
{
  int dex,con;
  object ob;
  
  dex = TP->query_stat(SS_DEX);
  con = TP->query_stat(SS_CON);

  NF("You don't have any plats!\n");
  if(ob = present("platinum coin",TP))
  {
    write("You let a platinum coin walk across your knuckles, ");
    say(QCTNAME(TP)+" walks a coin across his knuckles, ");

    if (((dex/2)+(random(dex/2)))>random(con))
    {
       write("you succeed and smile proudly.\n");
       say("and smiles proudly as "+HE_SHE(TP)+" succeeds.\n");
       return 1;
    }
    write("you fail and full of shame you see the coins fall to the floor.\n");
    say(HE_SHE(TP)+" fails and looks ashamed as the coin fall to the floor.\n");
    ob->split_heap(1);
    ob->move(ENV(TP));
    return 1;
  }
  return 0;
}

int
rhold()
{
   write("You hold your "+type+" close to your body, in case that someone would "+
     "make an attempt to steal it from you, and all the lovely plats that it holds.\n");
   say(QCTNAME(TP)+" holds "+HIS_HER(TP)+" "+type+" close to "+HIS_HER(TP)+" body, "+
     "in case someone would try to steal it and its contents from "+HIM_HER(TP)+"\n");
}
