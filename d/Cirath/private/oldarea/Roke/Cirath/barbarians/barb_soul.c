/*
 * The Mighty Soul of the Barbarians
 *
 */

inherit "/cmd/std/command_driver";

#include <ss_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"
#include <stdproperties.h>
#include "/d/Roke/Cirath/barbarians/skills.h"
#include "/d/Roke/common/qbits.h"
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"
#include <composite.h>
#include <formulas.h>

#define BARB_I_ATTACK      "_barb_i_attack"
#define WAIT               1
#define BOING              2
#define SLAY               3
#define YELL               4
#define PREPARATION        15
#define CHOP               5
#define STAB               6
#define Q_PS(xxx)          xxx->query_possessive()
#define Q_PR(xxx)          xxx->query_pronoun()
#define Q_OB(xxx)          xxx->query_objective()

#define B_CHOP_HIT(ob,ob2) ob->query_stat(SS_STR)*\
                           ob->query_skill(CHOPPING)
#define B_STAB_HIT(ob,ob2) ob->query_stat(SS_STR)*\
                           ob->query_skill(STABBING)
#define B_SLAY_HIT(ob,ob2) ob->query_stat(SS_STR)*\
                           ob->query_skill(SLAYING)
#define V_SLAY_HIT(ob,ob2) ob->query_stat(SS_STR)*\
                           ob->query_stat(SS_DEX)
#define SPEZIAL_HIT        1750

static mixed parse_this(string str, string form);

string get_soul_id()
{
    return "The Barbarian Herd";
}

int query_cmd_soul()
{
    return 1;
}
mapping
query_cmdlist()
{
    return ([
  "accept"      :"accept",

  "ban"         :"ban",
  "banger"      :"banger",
  "barblist"    :"bl",
  "bdrool"      :"bdrool",
  "bfist"       :"bfist",
  "bgrin"       :"bgrin",
  "bhail"       :"bhail",
  "bhug"        :"bhug",
  "bkiss"       :"bkiss",
  "blaugh"      :"blaugh",
  "blick"       :"blick",
  "bpeer"       :"bpeer",
  "bpunch"      :"bpunch",
  "bscream"     :"bscream",
  "bshake"      :"bshake",
  "bsmile"      :"bsmile",
  "bsniff"      :"bsniff",
  "bstomp"      :"bstomp",
  "bsulk"       :"bsulk",
  "btrack"      :"btrack",

  "check"       :"check",
  "chop"        :"chop",
  "combatcry"   :"combatcry",
  "crom"        :"crom",

  "demote"      :"demote",
  "disappointed":"disappointed",
  "dislike"     :"dislike",

  "elderlist"   :"elderlist",
  "endvote"     :"endvote",

  "gaze"        :"gaze",
  "greed"       :"greed",

  "headbut"     :"bonk",
  "help"        :"help",
  "hmpf"        :"hmpf",

  "impress"     :"impress",

  "joy"         :"joy",

  "newvote"     :"newvote",

  "pose"        :"pose",
  "pray"        :"praycrom",
  "promote"     :"promote",

  "reject"      :"reject",
  "refresh"     :"refresh",

  "slay"        :"slay",
  "stab"        :"stab",
  "swing"       :"swing",

  "ugh"         :"ugh",

  "vote"        :"vote",
  "voteresult"  :"voteresult",
  "votesubject" :"votesubject",

  "yell"        :"yell"
          ]);
}

void create()
{
    seteuid(getuid());
}

static mixed parse_this(string str, string form)
{
  object   *oblist, *tmplist;
  int      i;

  tmplist = ({});
  if (!CAN_SEE_IN_ROOM(this_player()))
    return tmplist;

  if (!str || (!parse_command(lower_case(str), environment(this_player()),form,
    oblist)))
    return ({});

  oblist = NORMAL_ACCESS(oblist, 0, 0);

  if (!sizeof(oblist))
    return ({});

  for (i = 0; i < sizeof(oblist); i++)
  {
    if (objectp(oblist[i]) && living(oblist[i]) &&
      (this_player() != oblist[i]) &&
      CAN_SEE(this_player(), oblist[i]))
        tmplist = tmplist + ({ oblist[i] });
  }
  return tmplist;
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

int kolla(object ob)
{
  if(!living(ob))
    return 0;

  return 1;
}

remove_prepare(who)
{
  who->remove_prop(BARB_I_ATTACK);
  write("You feel the blood burning in your veins again.\n");
  say(QCTNAME(TP)+" gets back the violent stare that only "+
    "true barbarians have.\n");
}

int
bonk()
{
  object enemy;
  
  enemy=TP->query_attack();
  if (!enemy) 
  {
    NF("But you are not fighting anyone.\n");
    return 0;
  }
    
  if (TP->query_prop(BARB_I_ATTACK)==BOING)
  {
    write("You can't bonk two times at the same time.\n");
    return 1;
  }
  if (TP->query_prop(BARB_I_ATTACK)==WAIT)
  {
     write("You don't feel ready to bonk yet.\n");
     return 1;
  }
  if (TP->query_prop(BARB_I_ATTACK))
  {
    write("Sorry, you are about to crush your enemy in another way.\n");
    return 1;
  }

  TP->add_prop(BARB_I_ATTACK,BOING);

  TP->catch_msg("You start to fix at "+Q_OB(enemy)+"'s head.\n");
  call_out("do_special",7,TP);
  return 1;
}

do_special(object tp)
{
  
    tp->add_prop(LIVE_O_SPELL_ATTACK,TO);
    call_out("remove_prepare",PREPARATION,tp);
  
}

int
chop()
{
  object enemy;
  
  enemy=TP->query_attack();
  if (!enemy) 
  {
    NF("But you are not fighting anyone.\n");
    return 0;
  }
    
  if (TP->query_prop(BARB_I_ATTACK)==CHOP)
  {
    write("Easy now...you are already prepearing a nice chop.\n");
    return 1;
  }
  if (TP->query_prop(BARB_I_ATTACK)==WAIT)
  {
     write("You don't feel ready to chop anyone yet.\n");
     return 1;
  }
  if (TP->query_prop(BARB_I_ATTACK))
  {
    write("Sorry, you are about to crush your enemy in another way.\n");
    return 1;
  }

  TP->add_prop(BARB_I_ATTACK,CHOP);

  TP->catch_msg("You start to aim at "+Q_PS(enemy)+" neck.\n");
  call_out("do_special",5,TP);
  return 1;
}

int
slay()
{
  object enemy;
  
  enemy=TP->query_attack();
  if (!enemy) 
  {
    NF("But you are not fighting anyone.\n");
    return 0;
  }
    
  if (TP->query_prop(BARB_I_ATTACK)==SLAY)
  {
    write("Hold it! Hold it! You're preparing a slay already.\n");
    return 1;
  }
  if (TP->query_prop(BARB_I_ATTACK)==WAIT)
  {
     write("Pity, you don't feel ready to slay anyone yet.\n");
     return 1;
  }
  if (TP->query_prop(BARB_I_ATTACK))
  {
    write("Sorry, you are about to crush your enemy in another way.\n");
    return 1;
  }

  TP->add_prop(BARB_I_ATTACK,SLAY);

  TP->catch_msg("You start to glare at "+QTNAME(enemy)+"'s movements.\n");
  call_out("do_special",5,TP);
  return 1;
}

int
stab()
{
  object enemy;
  
  enemy=TP->query_attack();
  if (!enemy) 
  {
    NF("But you are not fighting anyone.\n");
    return 0;
  }
    
  if (TP->query_prop(BARB_I_ATTACK)==STAB)
  {
    write("Easy now...you are already prepearing to stab somebody already.\n");
    return 1;
  }
  if (TP->query_prop(BARB_I_ATTACK)==WAIT)
  {
     write("You don't feel ready to stab anyone yet.\n");
     return 1;
  }
  if (TP->query_prop(BARB_I_ATTACK))
  {
    write("Sorry, you are about to crush your enemy in another way.\n");
    return 1;
  }

  TP->add_prop(BARB_I_ATTACK,STAB);

  TP->catch_msg("You start to aim at "+Q_PS(enemy)+" stomach.\n");
  call_out("do_special",5,TP);
  return 1;
}

int
yell()
{
  object enemy;
  
  enemy=TP->query_attack();
  if (!enemy) 
  {
    NF("But you are not fighting anyone.\n");
    return 0;
  }
    
  if (TP->query_prop(BARB_I_ATTACK)==WAIT)
  {
     write("You don't feel ready to yell yet.\n");
     return 1;
  }
  if (TP->query_prop(BARB_I_ATTACK))
  {
    write("Sorry, you are preparing another way of hurting your enemy.\n");
    return 1;
  }

  TP->add_prop(BARB_I_ATTACK,YELL);

  write("You start to clear your throat for a terrifying yell.\n");
  call_out("do_special",3,TP);
  return 1;
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

string query_personal(object tp)
{

  if(TP->query_gender()==0)
    return "him";
  else if(TP->query_gender()==1)
    return "her";

  return "it";

}

string
query_clan_name(object ob)
{
  int sc,eld,clan;

  sc = ob->query_skill(BARB_SCORE);

  eld = sc / 10;
  clan = sc - (eld * 10);

  if(clan == 1)      return "White Eagle Clan";
  else if(clan == 2) return "Mammoth Clan";

  return "*no clan*";
}

int
query_clan_number(object ob)
{
  int sc,eld,clan;

  sc = ob->query_skill(BARB_SCORE);

  eld = sc / 10;
  clan = sc - (eld * 10);

  return clan;
}

void slayer(object me,object enemy)
{
  int ac,skill,pen,time,hit,damage;
  string ptxt,mtxt,etxt;
  mixed *hitresult;

    pen = F_PENMOD((me->query_stat(SS_CON)+me->query_stat(SS_STR))/4, me->query_skill(SLAYING)+50);
    hitresult = enemy->hit_me(pen,W_SLASH, me, -1);

    ptxt = QCTNAME(me)+" misses "+QTNAME(enemy)+".\n";
    mtxt = "You miss "+QTNAME(enemy)+".\n";
    etxt = QCTNAME(me)+" misses you.\n";

    if (hitresult[0] > 0)
    {
      ptxt = QCTNAME(me)+" tickles "+QTNAME(enemy)+".\n";
      mtxt = "You tickle "+QTNAME(enemy)+".\n";
      etxt = QCTNAME(me)+" tickles you.\n";
    }
    if (hitresult[0] > 15)
    {
      ptxt = QCTNAME(me)+" cuts "+QTNAME(enemy)+".\n";
      mtxt = "You cut "+QTNAME(enemy)+".\n";
      etxt = QCTNAME(me)+" cuts you.\n";
    }
    if (hitresult[0] > 30)
    {
      ptxt = QCTNAME(me)+" slashes "+QTNAME(enemy)+".\n";
      mtxt = "You slash "+QTNAME(enemy)+".\n";
      etxt = QCTNAME(me)+" slashes you.\n";
    }
    if (hitresult[0] > 50)
    {
      ptxt = QCTNAME(me)+" molest "+QTNAME(enemy)+".\n";
      mtxt = "You molest "+QTNAME(enemy)+".\n";
      etxt = QCTNAME(me)+" molests you .\n";
    }
    if (hitresult[0] > 75)
    {
      ptxt = QCTNAME(me)+" crushes "+QTNAME(enemy)+".\n";
      mtxt = "You crush "+QTNAME(enemy)+".\n";
      etxt = QCTNAME(me)+" crushes you.\n";
    }

  me->catch_msg(mtxt);
  enemy->catch_msg(etxt);
  tell_watcher(ptxt, me, enemy);
  return;
}

void
victim(object enemy,object me)
{
  int ac,skill,pen,time,hit,damage;
  string ptxt,mtxt,etxt;
  mixed *hitresult;

    pen = F_PENMOD((me->query_stat(SS_CON)+me->query_stat(SS_STR))/4, me->query_stat(SS_DEX)+50);
    hitresult = enemy->hit_me(pen,W_SLASH, me, -1);

    ptxt = QCTNAME(me)+" misses "+QTNAME(enemy)+".\n";
    mtxt = "You miss "+QTNAME(enemy)+".\n";
    etxt = QCTNAME(me)+" misses you.\n";

    if (hitresult[0] > 0)
    {
      ptxt = QCTNAME(me)+" tickles "+QTNAME(enemy)+".\n";
      mtxt = "You tickle "+QTNAME(enemy)+".\n";
      etxt = QCTNAME(me)+" tickles you.\n";
    }
    if (hitresult[0] > 15)
    {
      ptxt = QCTNAME(me)+" cuts "+QTNAME(enemy)+".\n";
      mtxt = "You cut "+QTNAME(enemy)+".\n";
      etxt = QCTNAME(me)+" cuts you.\n";
    }
    if (hitresult[0] > 30)
    {
      ptxt = QCTNAME(me)+" slashes "+QTNAME(enemy)+".\n";
      mtxt = "You slash "+QTNAME(enemy)+".\n";
      etxt = QCTNAME(me)+" slashes you.\n";
    }
    if (hitresult[0] > 50)
    {
      ptxt = QCTNAME(me)+" molests "+QTNAME(enemy)+".\n";
      mtxt = "You molest "+QTNAME(enemy)+".\n";
      etxt = QCTNAME(me)+" molests you.\n";
    }
    if (hitresult[0] > 75)
    {
      ptxt = QCTNAME(me)+" crushes "+QTNAME(enemy)+".\n";
      mtxt = "You crush "+QTNAME(enemy)+".\n";
      etxt = QCTNAME(me)+" crushes you.\n";
    }

  me->catch_msg(mtxt);
  enemy->catch_msg(etxt);
  tell_watcher(ptxt, me, enemy);
  return;
}

int
query_slay_death(object slayer,object victim)
{
  if( slayer->query_hp() <= 0)
  {
    slayer->catch_msg(
      QCTNAME(victim)+" slayed you into tiny, tiny bits.\n");
    victim->catch_msg(
      "You slayed "+QTNAME(slayer)+" into tiny, tiny bits.\n");
    tell_watcher(
      QCTNAME(victim)+" slayed "+QTNAME(slayer)+" into tiny, tiny bits.\n",
      slayer,victim);
    slayer->do_die(victim);
    return 1;
  }
  if( victim->query_hp() <= 0)
  {
    victim->catch_msg(
      QCTNAME(slayer)+" slayed you into tiny, tiny bits.\n");
    slayer->catch_msg(
      "You slayed "+QTNAME(victim)+" into tiny, tiny bits.\n");
    tell_watcher(
      QCTNAME(slayer)+" slayed "+QTNAME(victim)+" into tiny, tiny bits.\n",
      slayer,victim);
    victim->do_die(slayer);
    return 1;
  }

  return 0;
}

int
accept(string who)
{
  int clan;
  string cname;
  object ob;

  if(TP->query_skill(BARB_SCORE)>19)
  {
    clan = query_clan_number(TP);

    ob=find_living(who);
    ob->set_skill(BARB_SCORE,clan);

    clan = query_clan_number(TP);
    cname = query_clan_name(TP);

    write("You have accepted "+C(who)+" as a clanmember of "+
      "the "+cname+".\n");
    ob->catch_msg("You have been accepted as a clanmember of the "+
      cname+".\n");

    return 1;
  }

  NF("What?\n");
  return 0;
}

int ban(string person)
{
  object *a,ob;
  string str;
  int brute;

  brute = query_brutelevel(TP);

  if (!person || person == "all")
    {
      if (brute == 2)
      {
        write("You ban everyone in the room, they're wimps!\n");
        say(QCTNAME(TP)+" bans you because you're a wimp.\n");
      }
      else
      {
        write("You ban all these brutal beasts who only kill and "+
              "like blood and don't seem to understand the joy in "+
              "cleaning.\n");
        say(QCTNAME(TP)+"bans you all for being brutal and mind"+
            "less murderers who don't have understood the joy in "+
            "floor-cleaning.\n");
      }

      return 1;
    }
  
  a = CMDPARSE_ONE_ITEM(person,"kolla","kolla");

  NF("Ban who?\n");
  if(!sizeof(a))
    return 0;

  ob = a[0];

  if(ob == TP)
    {
      TP->catch_msg("Ban yourself? Why would you do that, you wimpy little snort.\n");
      return 1;
    }
  
  if (brute == 2)
  {
    TP->catch_msg(
      "You ban "+QTNAME(ob)+", cause you think "+Q_PR(ob)+" is a wimpy "+
       "little snort.\n");
    tell_watcher(QCTNAME(TP)+" bans "+QTNAME(ob)+" because "+Q_PR(ob)+
      " is a little wimpy snort.\n",TP,ob);
  
    ob->catch_msg(QCTNAME(TP)+" bans you because "+Q_PR(TP)+" thinks that "+
      "you are a little wimpy snort.\n");
  }
  else
  {
    TP->catch_msg(
      "You ban "+QTNAME(ob)+", because "+Q_PR(ob)+" prefer "+
      "killing and not floor-cleaning.\n");
    tell_watcher(QCTNAME(TP)+" bans "+QTNAME(ob)+" because "+Q_PR(ob)+
      "likes killing better than floor-cleaning.\n",TP,ob);
    ob->catch_msg(
      QCTNAME(TP)+" bans you because "+Q_PR(TP)+" thinks you "+
      "prefer killing more than floor-cleaning.\n");
  }

  return 1;
}

int banger()
{
  NF("What??\n");
  write("YAAAAAAAAARRRRRRGGGGGHHHHHH!!!!!!!!!!!!!\n");
  say(QCTNAME(TP)+" screams loudly in anger of being neglected to have the kill!\n");
  return 1;
}

int bdrool(string person)
{
  object *a,ob;

  if (!person || person == "all")
  {
    TP->catch_msg("You slime! You drool on all your buddies!\n");
    write(QCTNAME(TP)+" starts to drool as "+Q_PR(TP)+" sees all these easy kills!\n");
  }
  a = CMDPARSE_ONE_ITEM(person,"kolla","kolla");

  NF("Drool on who?\n");
  if(!sizeof(a))
    return 0;

  ob = a[0];

  if(ob == TP)
  {
    TP->catch_msg("You start drooling all over yourself as you see all these easy kills.\n");
    write(QCTNAME(TP)+" starts to drool all over "+Q_OB(TP)+"self as "+Q_PR(TP)+" sees all "+
      "these easy kills.\n");

    return 1;
  }

  TP->catch_msg("You start to drool on "+QTNAME(ob)+" as you see all these easy kills.\n");
  ob->catch_msg(QCTNAME(TP)+" starts to drool on you as "+Q_PR(TP)+" sees all these easy kills.\n");
  tell_watcher(QCTNAME(TP)+" starts to drool all over "+QTNAME(ob)+" as "+Q_PR(TP)+" sees "+
    "all these easy kills.\n",TP,ob);

  return 1;
}

int bfist(string person)
{
  object *a,ob;

  if (!person || person == "all")
  {
    TP->catch_msg("You raise your fist against your wimpy companions!\n");
    write(QCTNAME(TP)+" raises "+Q_PS(TP)+" huge fist at you! You feel threatened.\n");
  }
  a = CMDPARSE_ONE_ITEM(person,"kolla","kolla");

  NF("Bfist who?\n");
  if(!sizeof(a))
    return 0;

  ob = a[0];

  if(ob == TP)
  {
    TP->catch_msg("Raise your fist towards yourself? You're nuts!\n");
    return 1;
  }

  TP->catch_msg("You raise your fist towards "+QTNAME(ob)+" in a rather threatening way.\n");
  ob->catch_msg(QCTNAME(TP)+" raises his huge fist towards you in a rather threatening way.\n");
  tell_watcher(QCTNAME(TP)+" raises his huge fist towards "+QTNAME(TP)+" in a threatening way\n",TP,ob);

  return 1;
}

int bgrin()
{
  write("You show your sharpened teeth in a vicious grin.\n");
  say(QCTNAME(TP)+" shows his sharpened teeth in a vicious grin.\n");
  return 1;
}

int bhail(string person)
{
}

int bl(string str)
{
  object *players;
  string cnam;
  int i;

  players = users();
  write("\nThese are the mighty Barbarians that stalks Genesis:\n");
  write("----------------------------------------------------\n");
  for (i = 0; i < sizeof(players); i++)
    {
      if (players[i]->query_guild_member("The Barbarian Herd"))
      {
         cnam = query_clan_name(players[i]);
         write("- " + players[i]->query_name() + " " +
         players[i]->query_title() + " - " + cnam +"\n");
      }
    }

    write("\n");
    return 1;
}

int bhug(string person)
{
  object *a,ob;
  string str;
  int brute;

  brute = query_brutelevel(TP);

  if (!person || person == "all")
    {
      if (brute == 2)
      {
        write("You hug your companions the barbarian way. Hard and "+
              "brutal.\n");
        say(QCTNAME(TP)+" hugs you the barbarian way. Hard and "+
            "brutal.\n");
      }
      else
      {
        write("You hug your companions softly, like a whimp.\n");
        say(QCTNAME(TP)+" hugs you soft and tender. Like a whimp "+
            "does.\n");
      }

      return 1;
    }
  
  a = CMDPARSE_ONE_ITEM(person,"kolla","kolla");

  NF("Hug who?\n");
  if(!sizeof(a))
    return 0;

  ob = a[0];

  if(ob == TP)
    {
      TP->catch_msg("Hug yourself? Perhaps you need a teddy bear?\n");
      return 1;
    }
  
  if (brute == 2)
  {
    TP->catch_msg(
      "You hug "+QTNAME(ob)+" the barbarian way. Hard and brutal.\n");
    tell_watcher(QCTNAME(TP)+" hugs "+QTNAME(ob)+" the barbarian way. "+
                 "Hard and brutal.\n",TP,ob);
  
    ob->catch_msg(QCTNAME(TP)+" hugs you the barbarian way. It hurts.\n");
  }
  else
  {
    TP->catch_msg(
      "You hug "+QTNAME(ob)+" soft and gentle. Like a whimp.\n");
    tell_watcher(QCTNAME(TP)+" hugs "+QTNAME(ob)+" the whimpy way. "+
                 "Soft and gentle.\n",TP,ob);
    ob->catch_msg(
      QCTNAME(TP)+" hugs you softly. The way wimpies do.\n");
  }
  return 1;
}

int bkiss(string person)
{
  object *a,ob;
  string str;
  int brute;

  brute = query_brutelevel(TP);

  if (!person || person == "all")
  {
    write("Kiss all? What kind of a whimp are you?\n");
    return 1;
  }
  
  a = CMDPARSE_ONE_ITEM(person,"kolla","kolla");

  NF("Kiss who?\n");
  if(!sizeof(a))
    return 0;

  ob = a[0];

  if(ob == TP)
    {
      TP->catch_msg("Kiss yourself. You're STUPID!!!\n");
      return 1;
    }
  
  if (brute == 2)
  {
    TP->catch_msg(
      "You kiss "+QTNAME(ob)+" like a true barbarian. Hard and "+
      "intensive.\n");
    tell_watcher(QCTNAME(TP)+" kisses "+QTNAME(ob)+" like a true "+
      "barbarian. Hard and intensive.\n",TP,ob);
  
    ob->catch_msg(QCTNAME(TP)+" kisses you hard and intesive. You're "+
      " chocked by "+Q_PS(TP)+" barbarian behaviour.\n");
  }
  else
  {
    TP->catch_msg(
      "You kiss "+QTNAME(ob)+" very gentle on the cheek, like the "+
      "whimp you are.\n");
    tell_watcher(QCTNAME(TP)+" kisses "+QTNAME(ob)+" gently on the "+
      "cheek. "+Q_PR(TP)+" looks like a whimp.\n",TP,ob);
    ob->catch_msg(
      QCTNAME(TP)+" kisses your cheek very gentle. The whimpy way of "+
      "kissing.\n");
  }
  return 1;
}

int blaugh()
{
  write("You start to laugh and it seems you can not stop doing it.\n");
  say(QCTNAME(TP)+" starts to laugh, louder and louder.\n");
  return 1;
}

int blick()
{
  write("You start to lick your lips in pure exitement of possibilities of "+
    "unlimited slaying.\n");
  say(QCTNAME(TP)+" starts to lick "+Q_PS(TP)+" lips in excitement over the "+
    "possibilities of unlimited slaying.\n");
  return 1;
}

int bpeer(string person)
{
}

int bpunch(string person)
{
}

int
bscream(string str)
{
  string who,text;
  int member;
  object ob;

  if (!str || sscanf(str,"%s %s",who,text) != 2) 
  {
    NF("Bscream what?\n");
    return 0;
  }
  who = lower_case(who);
    
  if (!(ob=find_living(who)) || !query_ip_number(ob))
  {
    NF("Couldn't locate "+C(who)+".\n");
    return 0;
  }

  if (ob->query_guild_member("The Barbarian Herd"))
    member = 1;
  else
    member = 0;

  if (member==0)
  {
    write("You can only scream to true barbarians.\n");
    return 1;
  }
  if (TP->query_mana() < 10)
  {
    write("You are too exhausted to do that.\n");
    return 1;
  }

  TP->add_mana(-10);

  if (TP->query_get_echo())
    write("You screamed this to "+C(who)+": "+text+"\n");
  else
    write("Ok.\n");

  ob->catch_msg("You hear the brutal voice of "+
                C(TP->query_real_name())+" from a distance.\n"+
                C(Q_PR(TP))+" screams to you: "+
                text+"\n");
  return 1;
}    

int bshake(string person)
{
}

int bsmile()
{
  write("You smile in a true brutal way. You look dangerous.\n");
  say(QCTNAME(TP)+" smailes in a true brutal way. "+Q_PR(TP)+" looks dangerous.\n");
  return 1;
}

int bsniff()
{
  int brute;

  brute = query_brutelevel(TP);

  if (brute == 2)
  {
    write("You raise your arm and sniff in your armpit. It smells lovely.\n");
    say(QCTNAME(TP)+" sniffs in "+Q_PS(TP)+" armpit and looks pleased with the smell.\n");
  }
  else
  {
    write("You raise your arm and sniff in your armpit. It smells like chanel no 5.\n");
    say(QCTNAME(TP)+" sniffs in "+Q_PS(TP)+" armpit. It smells like chanel no 5..\n");
  }

  return 1;

}

int bstomp()
{
  write("STOMP!!!\n");
  say("STOMP!!! "+QCTNAME(TP)+" stomps hard in the ground causeing it to rumble.\n");
  return 1;
}

int bsulk()
{
  write("You get so disappointed not getting what you want and start to sulk like a spoiled child.\n");
  say(QCTNAME(TP)+" starts acting like a spoiled child and sulks because "+Q_PR(TP)+" didn't "+
    "get what "+Q_PR(TP)+" wanted.\n");
  return 1;
}

int btrack()
{
  write("You search the ground for tracks of slayable enemies.\n");
  say(QCTNAME(TP)+" starts to search the ground for tracks of slayable enemies.\n");
  return 1;
}

int
check(string str)
{
  int pclan,clan,align,brute,i;
  string cname,str1,str2;
  object *players;

  if(TP->query_skill(BARB_SCORE)>19 && str=="clan")
  {
    clan = query_clan_number(TP);
    cname = query_clan_name(TP);

    players = users();
    write("\n"+cname+" List\n\n");
    for (i = 0; i < sizeof(players); i++)
    {
      pclan = query_clan_number(players[i]);

      if (players[i]->query_guild_member("The Barbarian Herd") &&
         pclan == clan)
      {
         brute = query_brutelevel(players[i]);
         align = players[i]->query_align();

         if(brute == 2) str1="BRUTAL";
         else str1="WIMP";

         if(align < -550) str2="EVIL";
         else if(align > 550) str2="GOOD";
         else str2="NEUTRAL";

         write("- " + players[i]->query_name() + " " +
         players[i]->query_title() + " - " + str1 +" - " + str2 +"\n");
      }
    }

    write("\n");
    return 1;
  }
  else
  if(TP->query_skill(BARB_SCORE)>29 && str=="members")
  {
    write("\nBarbarian Check List\n\n");

    for (i = 0; i < sizeof(players); i++)
    {
      if (players[i]->query_guild_member("The Barbarian Herd"))
      {
         brute = query_brutelevel(players[i]);
         align = players[i]->query_align();

         if(brute == 2) str1="BRUTAL";
         else str1="WIMP";

         if(align < -550) str2="EVIL";
         else if(align > 550) str2="GOOD";
         else str2="NEUTRAL";

         write("- " + players[i]->query_name() + " " +
         players[i]->query_title() + " - " + str1 +" - " + str2 +"\n");
      }
    }

    write("\n");
    return 1;
  }

  NF("What?\n");
  return 0;
}

int combatcry(string str)
{
  if(str=="")
  {
      write("You raise your voice to a bloodfreezing combat cry.\n");
      say(QCTNAME(TP)+" raises "+Q_PS(TP)+" to a "+
          "blood_freezing combat cry.\n");
  }
  else
  {
      write("You raise your voice to a combat cry saying:\n"+str+"!\n");
      say(QCTNAME(TP)+" raises "+Q_PS(TP)+" voice to a combat "+
          "cry:\n"+str+"!\n");
  }

  return 1;
}

int crom()
{
  NF("What???\n");
  write("CROM!!\n");
  say(QCTNAME(TP)+" goes CROM!!\n");
  return 1;
}

int
demote(string str)
{
  if(TP->query_skill(BARB_SCORE)>29)
  {
    write("This Elder function isn't ready yet.\n");
    return 1;
  }

  NF("What?\n");
  return 0;
}

int disappointed(string str)
{
  write("This fuction's not ready yet...\n");
  return 1;
}

int dislike(string str)
{
  TP->catch_msg("You show with a vomitous grimace what you think of "+str+".\n");
  say(QCTNAME(TP)+" shows with a vomitous grimace what "+Q_PR(TP)+" thinks "+
      "of "+str+".\n");
  return 1;
}

int
elderlist()
{
  object *players;
  int i;

  if(TP->query_skill(BARB_SCORE)>9)
  {
  players = users();
  write("\nBarbarian Elders Logged On\n");
  write("--------------------------\n");
  for (i = 0; i < sizeof(players); i++)
    {
      if (players[i]->query_guild_member("The Barbarian Herd") &&
          players[i]->query_skill(BARB_SCORE)>9)
      {
         write("- " + players[i]->query_name() + " " +
         players[i]->query_title() + "\n");
      }
    }

    write("\n");
    return 1;
  }

  NF("What?\n");
  return 0;
}

int
endvoting(string str)
{
  if(TP->query_skill(BARB_SCORE)>29)
  {
    write("This Elder function isn't ready yet.\n");
    return 1;
  }

  NF("What?\n");
  return 0;
}

int gaze(string person)
{
  object *a,ob;

  if (!person || person == "all")
    {
      write("You gaze suspiciously at your companions. They look nasty.\n");
      say(QCTNAME(TP)+" gazes at you suspiciously. You feel uneasy.\n");
      return 1;
    }
  
  a = CMDPARSE_ONE_ITEM(person,"kolla","kolla");

  NF("Gaze at who?\n");
  if(!sizeof(a))
    return 0;

  ob = a[0];

  if(ob == TP)
    {
      TP->catch_msg("Gaze at yourself. You're STUPID!\n");
      return 1;
    }
  
  TP->catch_msg("You gaze suspiciously at "+QTNAME(ob)+", xx looks like a whimp.\n");
  tell_room(E(TP),QCTNAME(TP)+" gazes suspiciously at "+QTNAME(ob)+
            ", sure that "+Q_PR(ob)+" is a whimp.\n",({TP,ob}));
  
  ob->catch_msg(QCTNAME(TP)+" gazes at you. You feel uneasy.\n");
  return 1;
}  

int greed()

{
  write("This fuction's not ready yet...\n");
  return 1;
}

int help(string str)
{
  string clan;
  int no;

  if(str=="barbarian")
  {
    write("\nBARBARIAN EMOTES                                         (941010)\n"+
          "----------------\n\n"+
          "ban <person>           - ban somebody for being a whimpy snort.  \n"+
          "banger                 - scream in anger over a lost kill.       \n"+
          "bdrool <person>        - start drooling in exitement.            \n"+
          "bfist <person>         - raise your fist towards somebody.       \n"+
          "bgrin                  - grin in a brutal way.                   \n"+
          "bhail <person>         - hail a fellow barbarian.                \n"+
          "bhug <person>          - hug somebody the barbarian way.         \n"+
          "bkiss <person>         - kiss somebody the barbarian way.        \n"+
          "blaugh                 - laugh and laugh and laugh.              \n"+
          "blick                  - lick your lips in excitement.           \n"+
          "bpeer <person>         - peer at somebody.                       \n"+
          "bscream <person> <msg> - scream something over distances         \n"+
          "bsmile                 - smile the barbarian way.                \n"+
          "bsniff                 - sniff your armpit.                      \n"+
          "bstomp                 - stomp in the ground.                    \n"+
          "bsulk                  - sulk like a spoiled child.              \n"+
          "btrack                 - search for tracks of slayable enemies.  \n"+
          "combatcry <string>     - raise a combat cry.                     \n"+
          "crom                   - say CROM!, as you're impressed/surprised\n"+
          "                         by something.                           \n"+
          "disappointed  <person> - disappointed with a with a team mate.   \n"+
          "dislike <subject>      - dislike somebody or something.          \n"+
          "gaze <person>          - gaze at somebody.                       \n"+
          "help barbarian         - this command.                           \n"+
          "help barblevels        - the different levels.                   \n"+
          "hmpf                   - if somebody says anything against you.  \n"+
          "impress <person>       - impress somebody                        \n"+
          "joy                    - reveal how much joy you have in killing.\n"+
          "pray to crom           - pray to your mighty wargod, Crom.       \n"+
          "ugh <person>           - say 'ugh' to someone.                   \n"+
          "\n"+
          "Attacks:\n"+
	  "slay	                  - slaughter someone                       \n"+
          "headbut                - bonk someone in the head.               \n"+
          "yell                   - try to scare someone with a yell.       \n"+
	  "block                  - try to block someones move.             \n"+
          "chop                   - chop someones head off.                 \n"+
          "\n\n");

    return 1;
  }
  else if(str=="barblevels")
  {
    write("\nBARBARIAN LEVELS\n"+
          "----------------\n\n"+
          "newbie, puny, lousy, harmless, weak, poor, amateurish, average,  \n"+
          "known, good, well-known, brutal, feared, champion, excellent,    \n"+
          "genocidal, master, greater master, legend and guru.\n\n");
    return 1;
  }
  else if(str=="barbclan")
  {
    clan = query_clan_name(TP);
    no = query_clan_number(TP);

    write(clan + " Emotes\n\n");
    if(no == 1)
    {
      write("eaglepride\n"+
            "eaglehail\n"+
            "eaglebow\n"+
            "eagleswing\n"+
            "\n");
      return 1;
    }
    else
    {
      write("Sorry, but your clan leader have been too lazy to do "+
          "anything...\n(Propably been out drinking ale instead *nudge* *nudge*)\n");
      return 1;
    }
  }
/*  else if(str=="elder");
*  {
*    write("\nELDER COMMANDS\n"+
*          "--------------\n\n"+
*          "vote <option>      - place your vote (yes/no/blanc)\n"+
*          "voteresult         - the result of the voting\n"+
*          "votesubject        - what to vote about\n\n"+
*          "elderlist          - elders logged on\n\n");
*    if(TP->query_skill(BARB_SCORE)>19)
*      write("accept             - accept a player to join the clan\n"+
*            "check              - check applicants and clan members\n"+
*            "reject             - reject a players application to the clan\n\n");
*    if(TP->query_skill(BARB_SCORE)>29)
*      write("demote <player>    - demote an elder or a player\n"+
*            "endvote            - end voting session\n"+
*            "newvote <subject>  - new voting session\n"+
*            "promote <elder>    - promote an elder\n\n");
*
*    return 1;
*  }
*/
  return 0;
}

int hmpf()
{
  NF("What???\n");
  write("Hmpf!!\n");
  say(QCTNAME(TP)+" goes hmpf!!\n");
  return 1;
}

int impress(string person)
{
  object *a,ob;
  string str,str1,str2;
  int brute,obcon,tpcon;

  brute = query_brutelevel(TP);

  if (!person || person == "all")
  {
    write("Nah, you can't impress 'em all.\n");
    return 1;
  }
  
  a = CMDPARSE_ONE_ITEM(person,"kolla","kolla");

  NF("Impress who?\n");
  if(!sizeof(a))
    return 0;

  ob = a[0];

  if(ob == TP)
    {
      TP->catch_msg("You look at you big biceps and impress yourself.\n");
      return 1;
    }
  
  tpcon = TP->query_stat(SS_CON);
  obcon = ob->query_stat(SS_CON);

  if (brute == 2)
  {
    if(tpcon>obcon)
    {
      str1 == "You try to impress "+QTNAME(ob)+" by showing your "+
             "biceps. You succed.\n";
      str2 == QCTNAME(TP)+" tries to impress you by showing "+Q_PS(TP)+
             " biceps. "+C(Q_PR(TP))+" succeds. You "+
             " are impressed.\n";
      str == QCTNAME(TP)+" tries to impress "+QTNAME(ob)+" by showing "+
            Q_PS(TP)+" biceps. "+C(Q_PR(TP))+
            " seems to succed, because "+QTNAME(ob)+" looks very impressed "+
            "by the view.\n";
    }
    else if(tpcon<obcon)
    {
      str1 == "You try to impress "+QTNAME(ob)+" by showing your "+
             "biceps. "+C(Q_PR(ob))+" laughs at you.\n";
      str2 == QCTNAME(TP)+" tries to impress you by showing "+
             Q_PS(TP)+" biceps. You just laugh at "+
             Q_PS(TP)+" puny muscles.\n";
      str == QCTNAME(TP)+" tries to impress "+QTNAME(ob)+" by showing "+
            Q_PS(TP)+" biceps. "+C(Q_PR(ob))+
            " just laugh at "+Q_PS(TP)+" puny muscles.\n";
    }
    else
    {
      str1 == "You try to impress "+QTNAME(ob)+" by showing your "+
             "biceps. "+C(Q_PR(ob))+" doesn't "+
             "seem very impressed though.\n";
      str2 == QCTNAME(TP)+" tries to impress you by showing "+
             Q_PS(TP)+" biceps. You don't feel "+
             "very impressed though.\n";
      str == QCTNAME(TP)+" tries to impress "+QTNAME(ob)+" by showing "+
            Q_PS(TP)+" biceps. "+C(Q_PR(ob))+
            " doesn't look very impressed though.\n";
    }

    TP->catch_msg(str1);
    tell_watcher(str,TP,ob);
    ob->catch_msg(str2);
  }
  else
  {
    TP->catch_msg(
      "You try to impress "+QTNAME(ob)+" by showing your "+
      "biceps. "+C(Q_PR(ob))+" laughs at you.\n");
    tell_watcher(QCTNAME(TP)+" tries to impress you by showing "+
             Q_PS(TP)+" biceps. You just laugh at "+
             Q_PS(TP)+" puny muscles.\n",TP,ob);
    ob->catch_msg(
      QCTNAME(TP)+" tries to impress "+QTNAME(ob)+" by showing "+
      Q_PS(TP)+" biceps. "+C(Q_PR(ob))+
      " just laugh at "+Q_PS(TP)+" puny muscles.\n");
  }
  return 1;
}

int joy()
{
  NF("What???\n");
  write("You smile with all your face, showing how much joy there is in killing.\n");
  say(QCTNAME(TP)+" smiles with all "+Q_PS(TP)+" face, revealing how much joy "+
    "there is in killing.\n");
  return 1;
}

int
newvote(string str)
{
  if(TP->query_skill(BARB_SCORE)>29)
  {
    write("This Elder function isn't ready yet.\n");
    return 1;
  }

  NF("What?\n");
  return 0;
}

int pose()
{
  write("This fuction's not ready yet...\n");
  return 1;
}

int praycrom(string str)
{
  string txt;

  if(str=="to crom")
  {
    if(TP->query_gender()==0)
      txt = "him";
    else if(TP->query_gender()==1)
      txt = "her";
    else
      txt = "it";

    write("You kneel down and hold your precious weapon in front of "+
          "you, praying to your mighty warlord, Crom.\n");
    say(QCTNAME(TP)+" kneels down, holding "+Q_PS(TP)+
          " weapon in front of "+txt+
        ", praying to "+Q_PS(TP)+" mighty wargod, Crom.\n");
    return 1;
  }
  return 0;
}

int
reject(string str)
{
  if(TP->query_skill(BARB_SCORE)>19)
  {
    write("This Elder function isn't ready yet.\n");
    return 1;
  }

  NF("What?\n");
  return 0;
}

int refresh()
{
  TP->remove_prop(BARB_I_ATTACK);
  TP->catch_msg("<- RESTORED ATTACK ABILITY ->\n");

  return 1;
}

int swing()
{
  write("This fuction's not ready yet...\n");
  return 1;
}

int ugh()
{
  write("This fuction's not ready yet...\n");
  return 1;
}

int
vote(string str)
{
  if(TP->query_skill(BARB_SCORE)>9)
  {
    write("This Elder function isn't ready yet.\n");
    return 1;
  }

  NF("What?\n");
  return 0;
}

int
voteresult(string str)
{
  if(TP->query_skill(BARB_SCORE)>9)
  {
    write("This Elder function isn't ready yet.\n");
    return 1;
  }

  NF("What?\n");
  return 0;
}

int
votesubject(string str)
{
  if(TP->query_skill(BARB_SCORE)>9)
  {
    write("This Elder function isn't ready yet.\n");
    return 1;
  }

  NF("What?\n");
  return 0;
}

void 
spell_attack(object me, object enemy)
{
  int ac,skill,pen,time,hit,damage;
  string text,ptext,str,mtxt,etxt,ptxt;
  mixed *hitresult;
  object pe;

  if(enemy->query_gender()==0)
    str = "him";
  else if(enemy->query_gender()==1)
    str = "her";
  else
    str = "it";

  pe=TP->query_attack();
  if (pe) 
    if (me->query_prop(BARB_I_ATTACK)==BOING)
    {
      me->add_prop(BARB_I_ATTACK,WAIT);
	
      skill=me->query_skill(SS_WEP_CLUB);
      ac=enemy->query_combat_object()->query_hitloc(A_HEAD)[0][2];
      if (random(skill)>random(50))
      {
        pen=random(skill*2)-ac;
        text=C(Q_PR(enemy));
      if (pen<=0)
      {
        time=0;
        text+=" must have a head of cork because "+Q_PS(enemy)+" doesn't feel it at all.\n";
      }
        else if (pen<20)
      {
        time=4;
        text+=Q_PS(enemy)+" quite looks dizzy.\n";
      }
      else if (pen<50)
      {
        time=6;
        text+=Q_PR(enemy)+" falls down to the ground, almost unconcious.\n";
      }
      else
      {
        time=8;
        text+=Q_PR(enemy)+" falls down unconcious heavily bleeding from the head.\n";
      }
      me->catch_msg("BONK! You bonk "+QTNAME(enemy)+"'s head.\n"+text);
      enemy->catch_msg("BONK!!! "+QCTNAME(me)+" bonks you in the head.\n");
      tell_watcher("BONK!!! "+QCTNAME(me)+" bonks "+QTNAME(enemy)+" in the head.\n"+
                   text,me,enemy);
      if (time)
        enemy->add_attack_delay(time,0);
      }
      else
      {
        me->catch_msg("You try to bonk "+QTNAME(enemy)+
                      " in the head but you are too unconcentrated.\n");
        enemy->catch_msg(QCTNAME(me)+
                         "'s weapon passes your head...you can feel the draft.\n");
      }
    }	  
    else if(me->query_prop(BARB_I_ATTACK)==CHOP)
    {
      write("\nChop: [B_CHOP_HIT: ");
      write(B_CHOP_HIT(me,enemy));
      write("]\nChop: [SPEZIAL: 1750]\n");
      if (random(B_CHOP_HIT(me, enemy)) > random(SPEZIAL_HIT))
      {
        pen = F_PENMOD((me->query_stat(SS_DEX)+me->query_stat(SS_STR))/4, me->query_skill(CHOPPING)+50);
        hitresult = enemy->hit_me(pen,W_SLASH, me, -1);

        write("Chop: [Chop Result:");
        write(hitresult[0]);
        write("]\n\n");

        ptxt = QCTNAME(me)+" tries to chop "+QTNAME(enemy)+"'s head off, but misses completely.\n";
        mtxt = "You try to chop "+QTNAME(enemy)+"'s head off, but miss completely.\n";
        etxt = QCTNAME(me)+" tries to chop your head off, but misses you by an inch.\n";

        if (hitresult[0] > 0)
        {
          ptxt = QCTNAME(me)+" tries to chop "+QTNAME(enemy)+"'s head off, and gets a lousy hit.\n";
          mtxt = "You try to chop "+QTNAME(enemy)+"'s head off, and get a lousy hit.\n";
          etxt = QCTNAME(me)+" tries to chop your head off, and gets a lousy hit at your neck.\n";
        }
        if (hitresult[0] > 15)
        {
          ptxt = QCTNAME(me)+" tries to chop "+QTNAME(enemy)+"'s head off, and hits "+QTNAME(enemy)+"'s neck.\n";
          mtxt = "You try to chop "+QTNAME(enemy)+"'s head off, and get a average hit.\n";
          etxt = QCTNAME(me)+" tries to chop your head off, and hits your neck, it hurts.\n";
        }
        if (hitresult[0] > 30)
        {
          ptxt = QCTNAME(me)+" tries to chop "+QTNAME(enemy)+"'s head off, and hits "+QTNAME(enemy)+"'s neck with a nice swing.\n";
          mtxt = "You try to chop "+QTNAME(enemy)+"'s head off, and get a good hit.\n";
          etxt = QCTNAME(me)+" tries to chop your head off, and hits your neck, it hurts badly.\n";
        }
        if (hitresult[0] > 50)
        {
          ptxt = QCTNAME(me)+" tries to chop "+QTNAME(enemy)+"'s head off, and hits "+QTNAME(enemy)+"'s neck with a awesome swing.\n";
          mtxt = "You try to chop "+QTNAME(enemy)+"'s head off, and get a very good hit.\n";
          etxt = QCTNAME(me)+" tries to chop your head off, and almost succeds separating your head from your body.\n";
        }
        if (hitresult[0] > 75)
        {
          ptxt = QCTNAME(me)+" tries to chop "+QTNAME(enemy)+"'s head off, and massacres "+QTNAME(enemy)+"'s neck with a bloody splash.\n";
          mtxt = "You try to chop "+QTNAME(enemy)+"'s head off, and get a nice clean cut in "+QTNAME(enemy)+"'s neck.\n";
          etxt = QCTNAME(me)+" tries to chop you head off, and is close to separate your head from your body with a mighty smash.\n";
        }

        if (enemy->query_hp() > 0)
        {
          me->catch_msg(mtxt);
          enemy->catch_msg(etxt);
          tell_watcher(ptxt, me, enemy);
        }
        else  
        {
          me->catch_msg("You chop "+QTNAME(enemy)+"'s head off with a "+
            "beautiful swing.\n"+C(Q_PS(enemy))+
            " head bounces away on the ground. You grin will all your face.\n") ;


          tell_watcher(QCTNAME(me)+" chops "+QTNAME(enemy)+"'s head off. The body falls "+
            "to the ground and the head bounces a couple of times on the ground.\n"+
             QCTNAME(me)+" smiles with all "+Q_PS(me)+" face.\n",me, enemy);


          enemy->catch_msg(QCTNAME(me)+" chops your head of with a mighty swing.\nYou die.\n");
          enemy->do_die(me);
        }              
        me->add_prop(BARB_I_ATTACK,WAIT);
        return;
      }

      ptxt = QCTNAME(me)+" tries to chop "+QTNAME(enemy)+"'s head off, but misses completely.\n";
      mtxt = "You try to chop "+QTNAME(enemy)+"'s head off, but miss completely.\n";
      etxt = QCTNAME(me)+" tries to chop you head off, but misses you by an inch.\n";

      me->add_attack_delay(5,0);
      enemy->hit_me(0, W_SLASH, me, -1);
      me->catch_msg(mtxt);
      enemy->catch_msg(etxt);
      tell_watcher(ptxt, me, enemy);
      me->add_prop(BARB_I_ATTACK,WAIT);
      return;
    }
    else if(me->query_prop(BARB_I_ATTACK)==SLAY)
    {
      int mdex,edex,slay,awar,msup,esup,mhits,ehits,i,dead;

      write("SLAY!!!!!\n");
      mdex = me->query_stat(SS_DEX);
      slay = me->query_skill(SLAYING);
      edex = enemy->query_stat(SS_DEX);
      awar = enemy->query_skill(SS_AWARENESS);
  
      if (!awar) awar = 25;

      msup = (mdex * 2 * ((slay/2) + random(slay/2))) / 1000;
      esup = (edex * 2 * ((awar/2) + random(awar/2))) / 1000;

      mhits = random(msup) - random(esup/2);
      ehits = random(esup) - random(msup/2);

      if (mhits <= 0) mhits = 1;
      if (ehits < 0) ehits = 0;

      write("HITS: ");
      write(mhits);write(" : ");write(ehits);write("\n");

      for (i = 0; i < 20; i++)
      {
        if (mhits)
        {
          slayer(me,enemy);
          mhits = mhits - 1;
        }
        if (ehits > 0)
        {
          victim(me,enemy);
          ehits = ehits - 1;
        }

        dead = query_slay_death(me,enemy);

        if( dead==1 )
        {
          mhits = 0;
          ehits = 0;
        }
      }
      me->add_attack_delay(10,0);
      me->add_prop(BARB_I_ATTACK,WAIT);
      return;
    }
    else if(me->query_prop(BARB_I_ATTACK)==STAB)
    {
      write("\nStab: [B_STAB_HIT: ");
      write(B_STAB_HIT(me,enemy));
      write("]\nStab: [SPEZIAL: 1750]\n");
      if (random(B_STAB_HIT(me, enemy)) > random(SPEZIAL_HIT))
      {
        pen = F_PENMOD((me->query_stat(SS_CON)+me->query_stat(SS_STR))/4, me->query_skill(STABBING)+50);
        hitresult = enemy->hit_me(pen,W_IMPALE, me, -1);

        write("Stab: [Stab Result:");
        write(hitresult[0]);
        write("]\n\n");

        ptxt = QCTNAME(me)+" tries to stab "+QTNAME(enemy)+" in the stomach, but misses completely.\n";
        mtxt = "You try to stab "+QTNAME(enemy)+" in the stomach, but miss completely.\n";
        etxt = QCTNAME(me)+" tries to stab you in the stomach, but you avoid the attempt easily.\n";

        if (hitresult[0] > 0)
        {
          ptxt = QCTNAME(me)+" tries to stab "+QTNAME(enemy)+" in the stomach and manage to scratch "+
            Q_OB(enemy)+".\n";
          mtxt = "You try to stab "+QTNAME(enemy)+" in the stomach, but manage just to scratch "+
            Q_OB(enemy)+"\n";
          etxt = QCTNAME(me)+" tries to stab you in the stomach, luckily "+Q_PR(me)+" just "+
            "scratches you.\n";
        }
        if (hitresult[0] > 15)
        {
          ptxt = QCTNAME(me)+" tries to stab "+QTNAME(enemy)+" in the stomach, and cuts "+
            Q_OB(enemy)+" lightly.\n";
          mtxt = "You try to stab "+QTNAME(enemy)+" in the stomach, but cuts "+Q_OB(enemy)+
            " just lightly.\n";
          etxt = QCTNAME(me)+" tries to stab you in the stomach and manages to cut your skin lightly.\n";
        }
        if (hitresult[0] > 30)
        {
          ptxt = QCTNAME(me)+" tries to stab "+QTNAME(enemy)+" in the stomach, and makes a nice, clean cut.\n";
          mtxt = "You try to stab "+QTNAME(enemy)+" in the stomach, and manage to give "+Q_OB(enemy)+
            " a nice, clean cut.\n";
          etxt = QCTNAME(me)+" tries to stab you in the stomach, and manages to hit you. Blood starts to sip down your trousers.\n";
        }
        if (hitresult[0] > 50)
        {
          ptxt = QCTNAME(me)+" tries to stab "+QTNAME(enemy)+" in the stomach, and hits "+QTNAME(enemy)+" hard, causing a stream of blood.\n";
          mtxt = "You try to stab "+QTNAME(enemy)+" in the stomach, and get a very good hit. Blood's everywhere!\n";
          etxt = QCTNAME(me)+" tries to stab you in the stomach, and succeds. Your life-blood starts to stream down your pants.\n";
        }
        if (hitresult[0] > 75)
        {
          ptxt = QCTNAME(me)+" stab "+QTNAME(enemy)+" in the stomach, and "+QTNAME(enemy)+"'s inner parts suddenly decides "+
            "to leave "+QTNAME(enemy)+"'s body.\n";
          mtxt = "You stab "+QTNAME(enemy)+" in the stomach, and "+QTNAME(enemy)+"'s inner parts suddenly decides "+
            "to leave "+QTNAME(enemy)+"'s body.\n";
          etxt = QCTNAME(me)+" stabs you in the stomach, and you can feel how your inner parts want to leave through the bloody wound.\n";
        }

        if (enemy->query_hp() > 0)
        {
          me->catch_msg(mtxt);
          enemy->catch_msg(etxt);
          tell_watcher(ptxt, me, enemy);
        }
        else  
        {
          me->catch_msg("You stab "+QTNAME(enemy)+" in the chest and twist your arm to drag "+
            "out "+Q_PS(enemy)+" inner parts out. You succed. You can't stop "+
            "smiling.\n");


          tell_watcher(QCTNAME(me)+" stabs "+QTNAME(enemy)+" in the chest and twists "+Q_PS(me)+
             " arm to drag out "+QTNAME(enemy)+"'s inner parts. "+QCTNAME(me)+" succeds and seems to never stop "+
             "smiling.\n",me, enemy);

          enemy->catch_msg(QCTNAME(me)+" stabs you in the stomach and with a twist drags your inner parts out "+
            "of you body.\nYou die a painful death.\n");
          enemy->do_die(me);
        }              
        me->add_prop(BARB_I_ATTACK,WAIT);
        return;
      }
      ptxt = QCTNAME(me)+" tries to stab "+QTNAME(enemy)+" in the stomach, but misses completely.\n";
      mtxt = "You try to stab "+QTNAME(enemy)+" in the stomach, but miss completely.\n";
      etxt = QCTNAME(me)+" tries to stab you in the stomach, but you avoid the attempt easily.\n";

      me->add_attack_delay(5,0);
      enemy->hit_me(0, W_IMPALE, me, -1);
      me->catch_msg(mtxt);
      enemy->catch_msg(etxt);
      tell_watcher(ptxt, me, enemy);
      me->add_prop(BARB_I_ATTACK,WAIT);
      return;
    }
    else if(me->query_prop(BARB_I_ATTACK)==YELL)
    {
      me->add_prop(BARB_I_ATTACK,WAIT);
      skill = (random(me->query_stat(SS_CON))-random(enemy->query_stat(SS_DIS)))/2;
      if(skill <= 0)
      {
        skill = 0;
        me->catch_msg("You try to scare "+QTNAME(enemy)+" by yelling at "+str+", "+
                      Q_PR(enemy)+" looks confused by your behaviour.\n");
        enemy->catch_msg(QCTNAME(me)+" yells in your ear. You wonder why "+
             Q_PR(me)+"'s did that.\n");
        tell_watcher(QCTNAME(me)+" yells in "+QTNAME(enemy)+"'s ear. "+QTNAME(enemy)+
                     " looks rather confused.\n",me,enemy);
      }
      else
      {
        mtxt=C(Q_PR(enemy));
        if(skill < 10) mtxt=" looks a little scared.\n";
        if(skill >= 10 && skill < 20) mtxt+=" looks quite scared.\n";
        if(skill >= 20 && skill < 30) mtxt+=" looks really scared.\n";
        if(skill >= 30 && skill < 40) mtxt+=" looks terrified.\n";
        if(skill >= 40 && skill < 50) mtxt+=" looks very terrified.\n";
        if(skill >= 50 && skill < 60) mtxt+=" tremlbles in fear.\n";
        if(skill >= 60) mtxt+="fall down on "+Q_PS(enemy)+" knees in fear.\n" ;

        me->catch_msg("AAARRRGHHH!!! You yell in "+QTNAME(enemy)+"'s ear.\n"+mtxt);
        enemy->catch_msg("AAARRRGHHH!!! "+QCTNAME(me)+" yells in your ear.\n"+
                         "You feel scared.\n");
        tell_watcher("AAARRRGHHH!!! "+QCTNAME(me)+" yells in "+QTNAME(enemy)+"'s ear.\n"+
                     mtxt+".\n",me,enemy);

        enemy->add_panic(skill);
      }
    }
    else
    {
      me->catch_msg("Your enemy isn't there anymore *sulk* *snortle* *whime*!!!!\n");
      me->add_prop(BARB_I_ATTACK,WAIT);
      return;
    }

    me->add_prop(BARB_I_ATTACK,WAIT);
    return;
}
