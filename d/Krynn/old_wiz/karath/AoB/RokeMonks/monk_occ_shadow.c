#pragma save_binary

inherit "/std/guild/guild_occ_sh";

#include <ss_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"
#include "../guild.h"
#include "/d/Roke/common/qbits.h"

#define SW shadow_who
 
int banished;
string *train = ({ MONKS + "occtrain1", MONKS + "train", MONKS + "dark1" });

public mixed query_guild_trainer_occ()
{
  return (QDONE(GROUP1, GURUQUEST) ? train + ({ MONKS + "occtrain2" }) :
     train);
}

int query_guild_tax_occ() 
{
  return (banished ? OCC_TAX * 2 : OCC_TAX);
}

void
set_monk_banished(int ban)
{
  if (banished == ban) return;

  banished = ban;

  SW->set_guild_pref(SS_OCCUP, query_guild_tax_occ());
}

int
query_monk_banished()
{
  return banished;
}

int
query_guild_keep_player(object ob)
{
  setuid();
  seteuid(getuid());
  if ((SECRET)->is_banished(ob->query_real_name()))
  {
    banished = 1;
    ob->catch_msg("You have been banished by the Kaheda council.\n");
  }

  return 1;
}

string query_guild_style_occ()
{
  return GUILD_STYLE;
}

string query_guild_name_occ()
{
  return GUILD_NAME;
}

int
query_monk_level()
{
  object who;
  int lev, wis, ucb, bcb, foc;

  who = query_shadow_who();

  wis = who->query_stat(SS_WIS);
  ucb = who->query_skill(SS_UNARM_COMBAT);
  foc = who->query_skill(SS_FOCUS);
  bcb = who->query_skill(SS_BLIND_COMBAT)+who->query_skill(SS_WEP_POLEARM);
  lev = (wis + 2 * ucb + 2 * foc + bcb) / 50; 
  return MIN(13, lev);
}

string
query_guild_title_occ()
{
  object who = query_shadow_who();
  string gen_title;
  
  if (COUNCIL_MEMBER(who->query_real_name()))
  {
    gen_title = "Bishop";
  }
  else
  {
    gen_title = ({ "Priest", "Priestess", "Something" })[who->query_gender()];
  }

  if ((SECRET)->is_banished(who->query_real_name()))
  {
    return "Banished " + gen_title + " of Kaheda";
  }

  switch (query_monk_level())
  {
    case 0:  return "Hopeful " + gen_title + " of Kaheda";
    case 1:  return "Novice " + gen_title + " of Kaheda";
    case 2:  return "Studious " + gen_title + " of Kaheda";
    case 3:  return gen_title + " of Kaheda";
    case 4:  return "Respected " + gen_title + " of Kaheda";
    case 5:  return "Very Respected " + gen_title + " of Kaheda";
    case 6:  return "Admired " + gen_title + " of Kaheda";
    case 7:  return "Greatly Admired " + gen_title + " of Kaheda";
    case 8:  return "Adored " + gen_title + " of Kaheda";
    case 9:  return "Much Adored " + gen_title + " of Kaheda";
    case 10: return "Beloved " + gen_title + " of Kaheda";
    case 11: return "Dedicated " + gen_title + " of Kaheda";
    case 12: return "Truly Devout " + gen_title + " of Kaheda";
    case 13: return "Enlightened " + gen_title + " of Kaheda";
  }
 
  return gen_title + " of Kaheda";
}

mixed query_guild_skill_name(int type)
{
  if (type == SS_FOCUS) 
  {
    return "focus";
  }
   
  return 0;
}


/*+*+*+*+*+*+*+*+ Added by Shiva *+*+*+*+*+*+*+*+*+*/

void 
poll_banish()
{
  (SECRET)->check_banish(SW);
  if (banished)
    set_alarm(600.0, 0.0, poll_banish);
}

mixed
query_alarms()
{
  mixed a = SW->query_alarms();
  mixed b = get_all_alarms();
  if (!pointerp(a)) a = ({});
  if (!pointerp(b)) b = ({});

  return a+b;
}
  
void delay_init_monk()
{
#ifdef MONK_SOUL
  SW->add_cmdsoul(MONK_SOUL);
  SW->update_hooks();
#endif

#ifdef GUILD_EMBLEM
  /*
  setuid();
  seteuid(getuid());
  clone_object(GUILD_EMBLEM)->move(SW, 1);
  */
#endif
  (SECRET)->check_boot(SW);
  (SECRET)->check_banish(SW);
/* Some code to get all kaheda members into the member data base
 * in the servers directory... as soon as the shadow gets loaded
 * the player will be added to the list
 * code : Fysix
 */
  MEMBER_SERVER->add_member(TP->query_name());

  if (banished)
    set_alarm(600.0, 0.0, poll_banish);
}

void init_occ_shadow(string arg)
{
#ifdef GUILD_CLOSED
  SW->clear_guild_stat(SS_OCCUP);
  remove_guild_occ();
  return;
#endif

  set_alarm(1.0, 0.0, delay_init_monk);
}

int add_monk_shadow(object who)
{
  int ret = shadow_me(who, "occupational", GUILD_STYLE, GUILD_NAME);
 
  if (ret == 1)
  {
    set_alarm(1.0, 0.0, &init_occ_shadow(0));
  }

  return ret;
}

void kick_out_monk()
{
#ifdef GUILD_EMBLEM_ID
  object ob;

  while (ob = present(GUILD_EMBLEM_ID, SW))
  {
    ob->remove_object();
  }
#endif

#ifdef MONK_START
  if (SW->query_default_start_location() == MONK_START)
  {
    SW->remove_default_start_location();
  }
#endif

#ifdef MONK_SOUL
  SW->remove_cmdsoul(MONK_SOUL);
  SW->update_hooks();
#endif

  setuid();
  seteuid(getuid());

  log_file("monk_leave", extract(ctime(time()), 4, 15) + "  " +
      SW->query_real_name() + " left Kaheda.\n");

  SW->remove_skill(SS_FOCUS);
  SW->add_exp(-SW->query_exp_combat() / 6, 1);
  SW->clear_bit(KAHEDA_GROUP, KAHEDA_MEMBER);
  SW->clear_bit(KAHEDA_GROUP, KAHEDA_OCCUP);
  SW->clear_guild_stat(SS_OCCUP);
  remove_guild_occ();
}
