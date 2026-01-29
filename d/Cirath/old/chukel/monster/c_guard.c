inherit "/std/monster";
inherit "/std/act/action";

#include <ss_types.h>
#include "/sys/wa_types.h"
#include <macros.h>
#include "/d/Cirath/chukel/defs.h"

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
  str = 70 + random(40);
  dex = 80 + random(30);
  con = 80 + random(30);
  inti = 55 + random(50);
  wis = 55 + random(50);
  con = 80 + random(30);

  ave = (str+dex+con+inti+wis+dis) / 8;
  wep = random(3);
  align = 200 + random(400);

  set_name("name");
  add_name("guard");
  set_race_name("human");
  set_gender(0);

  set_adj("cirathian");
  set_short("cirathian guard");
  set_long(break_string(
    "This is one of the guards that has the work to make Cirath a "+
    "safer place to live. He looks tough.\n",60));

  call_out("arm_me",1);

  set_stats(({str,dex,con,inti,wis,dis}));

  set_skill(SS_WEP_CLUB, ave);
  set_skill(SS_WEP_AXE, ave);
  set_skill(SS_WEP_SWORD, ave);
  set_skill(SS_WEP_POLEARM, ave);

  set_skill(SS_BLIND_COMBAT, ave/2);
  set_skill(SS_DEFENCE, ave);
  set_skill(SS_PARRY, ave);
  set_skill(SS_AWARENESS, 65);
  set_alignment(align);

  set_act_time(10);
  add_act("emote eyes you suspiciously.");
  add_act("emote says: Don't even think about it!.");

  set_cchat_time(6);
  add_cchat("HA! I will kill you like the slime you truly are related to!");
  add_cchat("Killkillkillkillkillkill!!!!!");
  trig_new("%w 'introduces' %s", "react_introduce");

  set_title("The Cirathian Guardian");
}

query_knight_prestige(){return align/2;}

void
arm_me()
{  
  clone_object(ARM+"cg_armour")->move(TO);
  clone_object(ARM+"cg_boots")->move(TO);
  clone_object(ARM+"cg_bracers")->move(TO);
  clone_object(ARM+"cg_gloves")->move(TO);
  clone_object(ARM+"cg_greaves")->move(TO);
  clone_object(ARM+"cg_helm")->move(TO);
  clone_object(ARM+"cg_robe")->move(TO);
  clone_object(ARM+"cg_shield")->move(TO);

  clone_object(WEP+"cg_weapon")->move(TO);

  command("wield all");
  command("wear all");
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

