/*
 * The Shield and Club Warriors shadow 
 * by Milan
 */

/* shadow_who - which object are we shadowing */

#pragma save_binary

inherit "/std/guild/guild_occ_sh";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"
#include "guild_occ.h"
#include "s_c_shield.c"

#define TITLE_OBJ       (THIS_DIR+"s_c_titles")
#define SAVE_FILE       THIS_DIR+"MEMBER_KILLERS"
#define LOG_FILE        THIS_DIR+"LOG_MEMBER_KILLERS"
#define TIME_TO_FORGET  20000

/*
 * Global variables
 */
string s_c_level = "Servant";
int i_am_incognito = 0;
int is_member_killer;

public mixed query_guild_trainer_occ(){ return THIS_DIR+"train"; }

int
query_guild_tax_occ() { return GUILD_TAX; }

string
query_guild_style_occ() { return GUILD_STYLE; }

string
query_guild_name_occ() { return GUILD_NAME; }

string
query_s_c_level()
{
  return s_c_level;
}

void
set_s_c_level(string str)
{
  s_c_level = str;
}

int
query_s_c_stat()
{
  int a = 4*shadow_who->query_skill(SS_WEP_CLUB);

  a += 4*shadow_who->query_stat(SS_WIS);
  a += 2*shadow_who->query_stat(SS_DIS);
  a += shadow_who->query_stat(SS_STR);
  if(shadow_who->query_skill(SS_WEP_CLUB) > 90)
    a += 2*shadow_who->query_skill(SS_WEP_CLUB);
  return a - (shadow_who->query_alignment() / 5);
}

int
query_shield_level()
{
  int a = shadow_who->query_skill(SS_WEP_CLUB);

  a += shadow_who->query_skill(SS_SMASH);
  a += shadow_who->query_skill(SS_SHIELD);
  a += shadow_who->query_skill(SS_PARRY);
  a += shadow_who->query_skill(SS_DEFENCE);
  a += shadow_who->query_skill(SS_BLIND_COMBAT);
  a += shadow_who->query_stat(SS_WIS);
  a += shadow_who->query_stat(SS_DIS);
  a += shadow_who->query_stat(SS_STR);
  a = (a * sizeof(ADJ_LIST) / 1000) - 1;
  return MIN(MAX(0, a), sizeof(ADJ_LIST)-1);
}

int
query_incognito()
{
  return i_am_incognito;
}

void
set_incognito(int i)
{
  i_am_incognito = i;
}

string
query_guild_title_occ()
{
  string s, n, *c;

  if(query_incognito()) return "";
  s = ADJ_LIST[query_shield_level()]+" "+s_c_level;
  n = shadow_who->query_name();
  c = (THIS_DIR+"vote")->query_council();
  if(member_array(n,c) != -1) s += " and Final Judge";
  return s+" of the Army of Angmar";
}

int
query_guild_not_allow_join_occ(object player, string type, string style,
                               string name)
{
  if(player->query_wiz_level())
  {
    player->catch_msg("Lucky wizard! You can join anything...\n");
    return 0;
  }
  if (::query_guild_not_allow_join_occ(player, type, style, name))
    return 1;

  NF("Are you stupid? Rangers are our enemies!!!\n");
  if (style == "ranger")
    return 1;
  NF("No!!! No undead warrior in our army!\n");
  if (name == "Vampyr guild")
    return 1;

  return 0;
}

static int
query_guild_keep_player(object tp)
{
  string race = tp->query_race_name();

  if(tp->query_wiz_level())
  {
    tp->catch_msg("Lucky wizard! No restrictions for you.\n");
    return 1;
  }
  if(member_array(race, ({"goblin","human","dwarf"})) == -1)
  {
    if(race == "elf")
      tp->catch_msg("We hate elves! Get lost!!!\n");
    else
      tp->catch_msg("You puny "+race+" can't swing club properly!\n");

    tp->remove_skill(SS_SHIELD);
    tp->remove_skill(SS_SMASH);
    tp->set_skill(SS_PARRY, tp->query_skill(SS_PARRY)/2);
    tp->set_skill(SS_DEFENCE, tp->query_skill(SS_DEFENCE)/3);
    tp->set_skill(SS_BLIND_COMBAT, tp->query_skill(SS_BLIND_COMBAT)/2);
    if(tp->query_skill(SS_WEP_CLUB)>30) tp->set_skill(SS_WEP_CLUB,30);
    if(tp->query_skill(SS_AWARENESS)>50) tp->set_skill(SS_AWARENESS,50);
    if(tp->query_skill(SS_APPR_MON)>50) tp->set_skill(SS_APPR_MON,50);

    tp->set_default_start_location(tp->query_def_start());

    TITLE_OBJ->remove_entry(tp->query_real_name());
    return 0;
  }
  return 1;
}

public mixed
query_guild_skill_name(int type) 
{
  if(type == SS_SHIELD) return SHIELD_NAME;
  if(type == SS_SMASH) return SMASH_NAME;
}

void
init_occ_shadow(string arg)
{
  string name;
  mapping member_killers;

  set_alarm(4.0, 0.0, "get_me_soul");

  seteuid(getuid());
  member_killers = restore_map(SAVE_FILE);
  if(!member_killers) return;

  name = shadow_who->query_name();
  if(member_array(name, m_indexes(member_killers)) == -1)
    return;  

  if(member_killers[name][1])
  {
    is_member_killer = 2;
    return;
  }

  if(TIME_TO_FORGET + member_killers[name][0] < shadow_who->query_age())
  {
    member_killers = m_delete(member_killers, name);
    save_map(member_killers, SAVE_FILE);
    return;
  }
  is_member_killer = 1;
}

int
query_alignment()
{
  return shadow_who->query_alignment();
}

void
get_me_soul()
{
  string name = shadow_who->query_name();
  string text = shadow_who->query_race_name();
  string *list = shadow_who->query_cmdsoul_list();
  int i;

  if(shadow_who->query_wiz_level()) return;

  seteuid(getuid());

  for(i=0; i<sizeof(list); i++)
    shadow_who->remove_cmdsoul(list[i]);

  shadow_who->add_cmdsoul(SOUL_RUMOUR);
  shadow_who->add_cmdsoul(SOUL);
  shadow_who->add_cmdsoul(SOUL_E_NEW);
  for(i=0; i<sizeof(list); i++)
    if((list[i] != SOUL) && (list[i] != SOUL_RUMOUR) && 
       (list[i] != SOUL_E_NEW) && (list[i] != SOUL_E_OLD+text))
       shadow_who->add_cmdsoul(list[i]);

  shadow_who->update_hooks();

  if(explode(name+"#", "jr#")[0]+"jr" != name)
    s_c_level = TITLE_OBJ->update_entry(shadow_who);

  clone_object(THIS_DIR+"objects/s_c_tabd")->move(shadow_who);
  switch(s_c_level)
  {
    case "Standard Bearer": clone_object(THIS_DIR+"objects/s_c_standard")->move(shadow_who);
                            break;
    default: break;
  }

  if(is_member_killer)
  {
    shadow_who->catch_msg("\n"+
      "   Hello "+name+", the "+s_c_level+" of the Army of Angmar...\n"+
    "Hope you stoped killing our warriors! Otherwise you may regret it!\n\n");
    return;
  }
  shadow_who->catch_msg("\n"+
    "   Welcome "+name+", the "+s_c_level+" of the Army of Angmar!\n"+
  "May your shield be like a rock and your club smashing every time!\n\n");

  (THIS_DIR+"vote")->set_up_punishments(shadow_who);
}

string
query_def_post()
{
  return THIS_DIR+"post";
}

void
notify_you_killed_me(object who) 
{

  string name;
  mapping member_killers;

  shadow_who->notify_you_killed_me(who);

  if(!who->query_guild_member(GUILD_NAME)) return; /* we don't care */

  seteuid(getuid());
  member_killers = restore_map(SAVE_FILE);
  if(!member_killers) member_killers = ([ ]);

  name = shadow_who->query_name();
  if(member_array(name, m_indexes(member_killers)) == -1)
  {
    member_killers += ([ name : ({shadow_who->query_age(),0}) ]);
    shadow_who->catch_msg("\n\nSomething tells you that you can "+
		"have big troubles in army for this!\n\n\n");
    is_member_killer = 1;
  }
  else
  {
    member_killers[name] = ({shadow_who->query_age()+TIME_TO_FORGET,1});
    shadow_who->catch_msg("\n\nYou again! Now you are in a BIG "+
			"trouble!!!\n\n\n");
    is_member_killer = 2;
  }
  save_map(member_killers, SAVE_FILE);

  write_file(LOG_FILE, name+" killed "+who->query_name()+" "+
			ctime(time())+"\n");
}

int
query_member_killer()
{
  return is_member_killer;
}

void
make_him_pay()
{
  object tp = shadow_who;
  int *skills, i, j;
  mapping member_killers;
  string name = shadow_who->query_name();

  seteuid(getuid());

  if(is_member_killer != 2)
  {
    write_file(THIS_DIR+"PUNISH_ERR", name+": wrong call make_him_pay() "+
			ctime(time())+"\n");
    return;
  }

  write_file(THIS_DIR+"PUNISH_LOG", name+" punished "+ctime(time())+"\n");

  tp->add_exp(-tp->query_exp_combat()/9,1);

  tp->catch_msg("\nSuddenly Dark Lord appears and points at you.\n"+
	"Dark Lord says: This one is killing my warriors! Punnish "+HIM(tp)+
	"!!!\n"+"\nMany angry warriors jump at you "+
       "and beat you with their nasty clubs...\n"+
      "Fortunatelly you lose consciousness so you don't feel every hit.\n\n"+
     "When you wake up you notice that you have terrible headache "+
    "and that you feel less skillful.\n\n\n");
  tell_room(ENV(tp), "\nSuddenly Dark Lord appears and points at "+
	QTNAME(tp)+".\n"+
	"Dark Lord says: This one is killing my warriors! Punnish "+HIM(tp)+
	"!!!\n"+"\nMany angry warriors jump at "+
      QTNAME(tp)+" and beat "+HIM(tp)+" with their nasty clubs...\n"+
      QCTNAME(tp)+" is soon knocked down but the cruel warriors continue "+
      "beating "+HIM(tp)+", aiming mainly for "+HIS(tp)+" head.\n"+
      "After they are satisfied they leave, leaving "+
      QTNAME(tp)+" laying on the floor...\n\n"+
      "After a long time "+QTNAME(tp)+" regains his sense and touches "+HIS(tp)+
      " sore head. "+CAP(HE(tp))+" sure regrets what "+HE(tp)+
      " has done!\n\n\n", tp);
  tp->set_max_headache(MAX(1000, tp->query_max_headache()));
  tp->set_headache(tp->query_max_headache());

  skills = tp->query_all_skill_types();
  for(i=0; i<sizeof(skills); i++)
  {
    if((skills[i]<1000) || (skills[i]==138000) || (skills[i]==138001))
    {
      j = tp->query_skill(skills[i]);
      tp->set_skill( skills[i], j - random(MIN(j,20)) );
    }
  }

  is_member_killer = 1;

  seteuid(getuid());
  member_killers = restore_map(SAVE_FILE);
  if(!member_killers) return;

  if(member_array(name, m_indexes(member_killers)) == -1) return;  

  member_killers[name][1] = 0;
  save_map(member_killers, SAVE_FILE);
}
 