inherit "/std/monster";
inherit "/std/act/action";

#include </d/Roke/common/defs.h>
#include <ss_types.h>
#include "/sys/wa_types.h"
#include <macros.h>
#include "/d/Roke/Cirath/defs.h"

int has_introduced=0,
    str = 0,
    dex = 0,
    con = 0,
    inti = 0,
    wis = 0,
    dis = 0,
    align = 0,
    ave = 0,
    wep = 0,
    named = 0;
string name = query_name();

void
create_monster ()
{
  str = 150 + random(40);
  dex = 160 + random(30);
  con = 160 + random(30);
  inti = 200 + random(50);
  wis = 180 + random(50);
  dis = 120 + random(30);

  ave = (str+dex+con+inti+wis+dis) / 6;
  wep = random(3);
  align = 1800;

  set_name("name");
  add_name("ruler");
  set_race_name("human");
  set_gender(0);

  set_adj("forceful");
  set_short("high inquisitor");
  add_adj("red-eyed");
  set_long("An forceful human that rules the Hole Temple Order.\n");
    
  call_out("arm_me",1);

  set_stats(({str,dex,con,inti,wis,dis}));

  set_skill(SS_WEP_CLUB, ave/2);
  set_skill(SS_WEP_AXE, ave/2);
  set_skill(SS_WEP_SWORD, ave/2);
  set_skill(SS_WEP_POLEARM, ave/2);

  set_skill(SS_BLIND_COMBAT, ave/2);
  set_skill(SS_DEFENCE, ave/2);
  set_skill(SS_PARRY, ave/2);
  set_skill(SS_AWARENESS, 65);
  set_alignment(align);

  set_act_time(10);
  add_act("emote eyes you suspiciously.\n");
  add_act("emote says: Don't leave the Holy way of living!.\n");

  set_cchat_time(6);
  set_chat_time(50);
  add_chat("Don't ever kill any good creatures?\n");
  add_chat("Tsk tsk tsk!\n");
  set_act_time(5);
  add_act("hmm");
  add_act("smile myst");
  add_cact("wield all");
  add_cact("Servants, they are attacking me");

  trig_new("%w 'introduces' %s", "react_introduce");
}

query_knight_prestige(){return -1*align/2;}

arm_me()
{
  seteuid(getuid(TO));
  clone_object(OBJ+"sacred_obj")->move(TO);
  
  command("wield all");
  command("wear all");
  command("wear brooch");
}

void
react_introduce()
{
  if (!has_introduced)
  {
    call_out("introduce_me", 4);
    has_introduced=1;
    call_out("remove_int",15);
  }
}

void
introduce_me()
{
  command("introduce myself");
}

void
remove_int()
{
  has_introduced=0;
}

string
query_title()
{
  return "The Master of The Holy Temple Order and Defender of Cirath";
}

string
query_konsonant()
{
  string s;
  int n;

  n = random(17);

  switch(n)
  {
    case 0:  s="b"; break;
    case 1:  s="c"; break;
    case 2:  s="d"; break;
    case 3:  s="f"; break;
    case 4:  s="g"; break;
    case 5:  s="h"; break;
    case 6:  s="j"; break;
    case 7:  s="k"; break;
    case 8:  s="l"; break;
    case 9:  s="m"; break;
    case 10: s="n"; break;
    case 11: s="p"; break;
    case 12: s="r"; break;
    case 13: s="s"; break;
    case 14: s="t"; break;
    case 15: s="v"; break;
    case 16: s="w";
  }

  return s;
}
string

query_vokal()
{
  string s;
  int n;

  n = random(6);

  switch(n)
  {
    case 0:  s="a"; break;
    case 1:  s="e"; break;
    case 2:  s="i"; break;
    case 3:  s="o"; break;
    case 4:  s="u"; break;
    case 5:  s="y";
  }

  return s;
}

string
query_end_name()
{
  string s;
  int n;

  n = random(9);

  switch(n)
  {
    case 0:  s="ton"; break;
    case 1:  s="ter"; break;
    case 2:  s="son"; break;
    case 3:  s="tan"; break;
    case 4:  s="er" ; break;
    case 5:  s="es" ; break;
    case 6:  s="gan"; break;
    case 7:  s="s"  ; break;
    case 8:  s="gon";
  }

  return s;
}

string
query_name()
{
  string str,ret;
  int n;

  if(!named)
  {
    str = query_konsonant();
    ret = capitalize(str);

    str = query_vokal();
    ret = ret + str;

    str = query_konsonant();
    ret = ret + str;

    str = query_end_name();
    ret = ret + str;

    named = 1;
    return ret;
  }

  return name;
}

