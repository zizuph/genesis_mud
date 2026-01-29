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
  str = 40 + random(50);
  dex = 50 + random(50);
  con = 50 + random(50);
  inti = 25 + random(50);
  wis = 25 + random(50);
  con = 50 + random(25);

  ave = (str+dex+con+inti+wis+dis) / 6;
  align = 100 + random(200);

  set_name("name");
  set_race_name("human");
  set_gender(0);

  set_adj("travelling");
  add_adj("tired");
  set_short("tired traveller");
  set_long(break_string(
    "This human is travelling the road between Tyr and Ciubori. "+
    "He looks rather tired, perhaps he has travelled a long way?\n",60));

  set_restrain_path(S_TRADE);
  set_random_move(3);

  call_out("arm_me",1);

  set_stats(({str,dex,con,inti,wis,dis}));

  set_skill(SS_WEP_CLUB, ave);
  set_skill(SS_DEFENCE, ave);
  set_skill(SS_PARRY, ave);
  set_skill(SS_AWARENESS, 30);

  set_alignment(align);

  set_act_time(10);
  add_act("emote smiles tiredly.\n");
  add_act("emote removes some dirt from his boots.\n");

  set_cchat_time(6);
  add_cchat("You naughty little swine!");
  add_cchat("You will die in the filth!");
  add_cchat("Your mother was a hamster and your father smelled of elderberries!");
  trig_new("%w 'introduces' %s", "react_introduce");

  set_title("Occupational Traveller");
}

query_knight_prestige(){return align/2;}

void
arm_me()
{
  seteuid(getuid(TO));

  clone_object(ARM+"t_helmet")->move(TO);
  clone_object(ARM+"t_mail")->move(TO);
  clone_object(ARM+"t_cloak")->move(TO);
  clone_object(ARM+"t_boots")->move(TO);
  clone_object(WEP+"t_club")->move(TO);

  command("wear all");
  command("wield all");
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

