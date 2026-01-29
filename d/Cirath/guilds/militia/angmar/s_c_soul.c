/*
 * The Shield and Club Warriors soul
 * by Milan
 * Altered by Ged 24/11/2001
 * Added pulping on/off options
 */

#pragma save_binary

inherit "/cmd/std/command_driver";

#include "defs.h"

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <formulas.h>
#include "/std/combat/combat.h"
#include "guild.h"

#define IS_LAYMAN(w) (w->query_guild_name_lay() == GUILD_NAME)

/* following two constants make layman reset time longer and damage
 * smaller so that we get efficiency 60% of occ member
 * This is only for scare  and smash as shield stuff is modified in
 * s_c_shield.c
 */
#define LAY_TIME 134
#define LAY_PEN   80

#define ANTI_DO_PROP "_anti_do_prop_"
/*
 * Modificator for 'defend' and 'focus' bonusses so we get right
 * combat aid.
 */
#define BONUS_MOD 130
#define DEBUG(x) find_player("ged")->catch_msg(x+"\n");

static mapping alarm = ([ ]);

/* The soul identification */
string get_soul_id(){ return GUILD_NAME; }
int query_cmd_soul() { return 1; }


/* *************************************************************
 * The list of verbs and functions.
 */

mapping query_cmdlist()
{
  seteuid(getuid());
  return([
           "help":"help",
          "focus":"focus",
         "defend":"defend",
          "break":"break_concentration",
          "scare":"scare",
          "smash":"smash",
           "free":"do_free",
  /*** special emotes will be in "s_c_emotes.c" ***/
         "signal":"signal",
      "incognito":"incognito",
          "aasay":"aasay",
        "pulping":"pulping",
        ]);
}


/***************************************************************/

void remove_relax(object who)
{
  int aaa;

  if(who->query_prop(ANTI_DO_PROP))
  {
    who->remove_prop(ANTI_DO_PROP);
    aaa = set_alarm(itof(TIME_TO_RELAX(who)), 0.0, "remove_relax", who);
    alarm[who->query_name()] = aaa;
    return;
  }

  who->remove_prop(SPEC_ATTACK_IS);
  who->catch_msg("You feel relaxed again.\n");
}

int kill_access(object ob)
{
  if((!living(ob)) || (ob->query_ghost()) || (ob == TP) ||
     (!ob->check_seen(TP)) || (ENV(ob) != ENV(TP)))
    return 0;
  return 1;
}

mixed get_one_target_from_string(string str)
{
  mixed *target, enemy;
  mixed tmp;

  if(!str)
  {
    if(!(enemy = TP->query_attack()))
    {
      NF("But you are not fighting anyone.\n");
      return 0;
    }
  }
  else
  {
    target = CMDPARSE_ONE_ITEM(str, "kill_access", "kill_access");
    if(sizeof(target) > 1)
    {
      NF("Be specific, you can't "+query_verb()+" "+COMPOSITE_LIVE(target)+
         " at the same time.\n");
      return 0;
    }
    else if(!sizeof(target))
    {
      NF("You find no such living creature.\n");
      return 0;
    }
    enemy = target[0];
  }

  if(tmp = ENV(enemy)->query_prop(ROOM_M_NO_ATTACK))
  {
    if(stringp(tmp))
      NF(tmp);
    else
      NF("Some magic force in the air prevents you from attacking.\n");
    return 0;
  }

  switch(TP->query_prop(SPEC_ATTACK_IS))
  {
    case RELAX:
      NF("You are too excited. Relax...\n");
      TP->add_prop(ANTI_DO_PROP, 1);
      return 0;
    case FOCUS:
      NF("You are concentrating on your defence now!\n");
      return 0;
    case SMASH:
      NF("You are preparing your smash right now!\n");
      return 0;
    case DEFEND:
      NF("You are defending "+QTNAME(TP->query_defend())+" now!\n");
      return 0;
  }
  if(tmp = enemy->query_prop(OBJ_M_NO_ATTACK))
  {
    if(stringp(tmp))
      NF(tmp);
    else
      NF("You feel a divine force protecting "+QTNAME(enemy)+".\n");
    return 0;
  }
  if(!F_DARE_ATTACK(TP, enemy))
  {
    NF("You don't dare to "+query_verb()+" "+QTNAME(enemy)+".\n"+
       "It may only made "+HIM(enemy)+" very angry.\n");
    return 0;
  }
  if((!TP->query_npc()) &&
     (TP->query_met(enemy)) &&
     (TP->query_prop(LIVE_O_LAST_KILL) != enemy) &&
     (member_array(enemy, TP->query_enemy(-1)) == -1))
  {
    NF(CAP(query_verb())+" " + enemy->query_the_name(TP) +
          "?!? Please confirm by trying again.\n");
    TP->add_prop(LIVE_O_LAST_KILL, enemy);
    return 0;
  }
  return enemy;
}

/***************************************************************/
/* the functions. add them in the same order as in the cmdlist */

/********************** Pulping on/off *************************/

int pulping(string what)
{
 int pl;

 if(!what)
  {
   pl=TP->query_pulping();
   if(pl) write("You are currently a pulping machine!\n");
   else write("You are currently too lazy to produce any pulps.\n");
   return 1;
  }

 NF("Pulping on or off?!\n");
 if(what!="on" && what!="off") return 0;

 pl=(what=="on" ? 1 : 0);
 TP->set_pulping(pl);

 return 1;
}

/***********************  HELP  ***************************/
int help(string s)
{
  if((s == "shield and club") || (s == "angmar"))
  {
    write("Availible commands are:\n"+
     "focus on defence     : Focus on your defence with a shield.\n"+
     "defend [target]      : Focus on defending target with your shield.\n"+
     "break concentration  : You can stop focusing on defence (both above).\n"+
     "scare [target]       : Initiate a combat. Better if you are hidden.\n"+
     "smash [target]       : Try to smash target to a pulp.\n"+
     "free commands        : You can do this in case some of the above\n"+
     "                       commands got stuck for some reason.\n"+
     "signal <sign>        : Send smoke signal. <sign> can be any letter,\n"+
     "                       'HELP', 'HELLO', 'BYE', 'S.O.S.' or 'O.K.'.\n"+
     "pulping off/on       : Pulp your enemies with smash, or not.\n"+
     "signal off/on        : You can turn off/on receiving smoke signals.\n"+
     "incognito on/off     : When incognito you try to hide that you are\n"+
     "                       a member of the army.\n"+
     "aasay                : Say something in the language of Angmar.\n"+
     "plant rumour         : Please do 'help plant rumour' for more info.\n"+
     "\n"+
     "Command 'angmar emotes' will give you list of changed emotes. Have fun!\n"+
     ""  );
    return 1;
  }

  return 0;
}

/***********************  EMOTES  ***************************/

#include "s_c_emotes.c"

/***********************  DEFEND  ***************************/
int defend(string str)
{
  int a,aaa;
  mixed *target, who_defend;

  if(!TP->query_shield_worn())
  {
    NF("You need to wear some shield first!\n");
    return 0;
  }
  switch(TP->query_prop(SPEC_ATTACK_IS))
  {
    case RELAX:
      NF("You are too excited. Relax...\n");
      TP->add_prop(ANTI_DO_PROP, 1);
      return 0;
    case FOCUS:
      NF("You are concentrating on your defence now!\n");
      return 0;
    case SMASH:
      NF("You are preparing to smash your enemy now!\n");
      return 0;
    case DEFEND:
      NF("You are defending "+QTNAME(TP->query_defend())+" now!\n");
      return 0;
  }

  target = CMDPARSE_ONE_ITEM(str, "kill_access", "kill_access");
  if(sizeof(target) > 1)
  {
    NF("Be specific, you can't "+query_verb()+" "+COMPOSITE_LIVE(target)+
       " at the same time.\n");
    return 0;
  }
  if(!sizeof(target))
  {
    NF("You find no such living creature.\n");
    return 0;
  }
  if(member_array(target[0], TP->query_team_others()) == -1)
  {
    NF(QCTNAME(target[0])+" is not member of your team!\n");
    return 0;
  }
  if(!IS_MEMBER(target[0]))
  {
    NF(QCTNAME(target[0])+" is not member of Angmar's army!\n");
    return 0;
  }
  if(sizeof(target[0]->query_list_of_defenders())>1)
  {
    NF(QCTNAME(target[0])+" already has two defenders.\n");
    return 0;
  }
  who_defend = target[0];

  TP->add_prop(SPEC_ATTACK_IS, DEFEND);
  a = 1 + random(TP->query_skill(SS_SHIELD));
  TP->catch_msg("You start to defend "+QTNAME(who_defend)+".\n");
  TP->tell_watcher(QCTNAME(TP)+" starts to defend "+QTNAME(who_defend)+".\n");
  TP->set_shield_bonus(a*BONUS_MOD/100);
  who_defend->add_defender(TP, a);
  TP->set_defend(who_defend);
  aaa = set_alarm(itof(a), 0.0, "stop_defend", TP);
  alarm[TP->query_name()] = aaa;
  return 1;
}

void stop_defend(object who)
{
  int aaa;

  /*** maybe concentration was broken? ***/
  if(who->query_prop(SPEC_ATTACK_IS) != DEFEND) /* for security we reset */
  {
    if(who->query_prop(SPEC_ATTACK_IS) != FOCUS) who->set_shield_bonus(0);
    if(who->query_defend()) (who->query_defend())->remove_defender(who);
    who->clear_defend();
    return;
  }

  who->catch_msg("You stop defending "+QTNAME(who->query_defend())+".\n");
  who->tell_watcher(QCTNAME(who)+" stops defending "+
                    QTNAME(who->query_defend())+".\n");
  who->add_prop(SPEC_ATTACK_IS, RELAX);
  who->set_shield_bonus(0);
  (who->query_defend())->remove_defender(who);
  who->clear_defend();
  aaa = set_alarm(itof(TIME_TO_RELAX(who)), 0.0, "remove_relax", who);
  alarm[who->query_name()] = aaa;
  return;
}

/***********************  FOCUS  ***************************/
int focus(string str)
{
  int a,aaa;

  if(str != "on defence")
  {
    NF("Focus on what? Defence???\n");
    return 0;
  }
  if (!TP->query_attack())
  {
    NF("But you are not fighting anyone.\n");
    return 0;
  }
  if(!TP->query_shield_worn())
  {
    ("You need to wear some shield first!\n");
    return 0;
  }
  switch(TP->query_prop(SPEC_ATTACK_IS))
  {
    case RELAX:
      NF("You are too excited. Relax...\n");
      TP->add_prop(ANTI_DO_PROP, 1);
      return 0;
    case FOCUS:
      NF("You are already concentrating on your defence.\n");
      return 0;
    case SMASH:
      NF("You are preparing to smash your enemy now!\n");
      return 0;
    case DEFEND:
      NF("You are defending "+QTNAME(TP->query_defend())+" now!\n");
      return 0;
  }
  TP->add_prop(SPEC_ATTACK_IS, FOCUS);
  a = 1 + random(TP->query_skill(SS_SHIELD));
  TP->catch_msg("You start to concentrate on your defence.\n");
  TP->tell_watcher(QCTNAME(TP)+" starts to concentrate on "+HIS(TP)+" defence.\n");
  TP->set_shield_bonus(a*BONUS_MOD/100);
  aaa = set_alarm(itof(a), 0.0, "end_focus_on_defence", TP);
  alarm[TP->query_name()] = aaa;
  return 1;
}

void end_focus_on_defence(object who)
{
  int aaa;

  /*** maybe concentration was broken? ***/
  if(who->query_prop(SPEC_ATTACK_IS) != FOCUS) /* reset for security */
  {
    if(who->query_prop(SPEC_ATTACK_IS) != DEFEND) who->set_shield_bonus(0);
    return;
  }

  who->catch_msg("You lost your concentration.\n");
  who->tell_watcher(QCTNAME(who)+" lost "+HIS(who)+" concentration.\n");
  who->add_prop(SPEC_ATTACK_IS, RELAX);
  who->set_shield_bonus(0);
  aaa = set_alarm(itof(TIME_TO_RELAX(who)), 0.0, "remove_relax", who);
  alarm[who->query_name()] = aaa;
  return;
}

/***********************  BREAK CONCENTRATION  *************/
int break_concentration(string str)
{
  int aaa;

  if(str != "concentration")
  {
    NF("Break what? Concentration?\n");
    return 0;
  }

  if(TP->query_prop(SPEC_ATTACK_IS) == FOCUS)
  {
    end_focus_on_defence(TP);
    return 1;
  }
  if(TP->query_prop(SPEC_ATTACK_IS) == DEFEND)
  {
    stop_defend(TP);
    return 1;
  }
  NF("But you are not focusing on defence now!\n");
  return 0;
}

/***********************  SCARE  ***************************/
int scare(string str)
{
  mixed *hit, enemy = get_one_target_from_string(str);
  object weapon;
  string *text, wep = "arms";
  int bonus, eff_wis, ttt, aaa, pen, wpen = 5;

  if(!enemy) return 0;
  if((member_array(enemy, TP->query_enemy(-1)) != -1) ||
     (member_array(TP, enemy->query_enemy(-1)) != -1))
  {
    NF(CAP(HE(enemy))+" pays too much attention to you to be scared.\n");
    return 0;
  }

  if (enemy->query_prop("live_i_already_scared"))
  {
      NF(CAP(HE(enemy))+" is wary of your scare tactics.\n");
      return 0;
  }
  
  if(TP->query_prop(S_C_PUN) == 3)
  {
    write("You are banned from using scare!\n");
    return 1;
  }

  TP->add_prop(SPEC_ATTACK_IS, RELAX);
  ttt = TIME_TO_RELAX(TP);
  if(IS_LAYMAN(TP)) ttt = ttt * LAY_TIME / 100;
  aaa = set_alarm(itof(ttt), 0.0, "remove_relax", TP);
  alarm[TP->query_name()] = aaa;

  weapon = TP->query_weapon(W_RIGHT);
  if(!weapon || weapon->query_wt() != W_CLUB)
  {
    weapon = TP->query_weapon(W_BOTH);
    if(!weapon)
      weapon = TP->query_weapon(W_LEFT);
  }
  if(weapon && (weapon->query_wt() == W_CLUB))
  {
    wpen = weapon->query_pen();
    wep = weapon->short();
  }

  TP->catch_msg("You scream at "+QTNAME(enemy)+
                ", waving your "+wep+" dangerously.\n");
  enemy->catch_msg(QCTNAME(TP)+" screams at you"+
                ", waving "+HIS(TP)+" "+wep+" dangerously.\n");
  TP->tell_watcher(QCTNAME(TP)+" screams at "+QTNAME(enemy)+
             ", waving "+HIS(TP)+" "+wep+" dangerously.\n", enemy);

  pen = F_PENMOD(wpen, TP->query_skill(SS_SMASH));
  if(IS_LAYMAN(TP)) pen = LAY_PEN * pen / 100;

  eff_wis = TP->query_stat(SS_WIS);
  /* surprise bonus to wis when not seen */
  if (!TP->check_seen(enemy))
  {
    eff_wis = (120 * eff_wis) / 100;
  }
  bonus = (100 * random(eff_wis)) / (1+random(enemy->query_stat(SS_DIS)));
  if (bonus > 150)
  {
    bonus = 150;
  }
  pen = (pen * bonus) / 100;

  /* efficiency restricted - punishment */
  if(TP->query_prop(S_C_PUN) == 2) pen /= 2;

  hit = enemy->hit_me(pen, MAGIC_DT, TP, -1);

  TP->attack_object(enemy);

  if(enemy->query_hp() <= 0)
     text = ({" dies in terror of ",
              " die in terror of  ",
              "!\n" });
  else if(hit[0] == 0)
     text = ({" laughs at ",
              " laugh at ",
              " without any fear.\n" });
  else if(hit[0] < 4)
     text = ({" steps back, but otherwise ",
              " step back, but otherwise ",
              " didn't make big impression.\n" });
  else if (hit[0] < 8)
     text = ({ " jumps in fear of ",
               " jump in fear of ",
               ".\n" });
  else if (hit[0] < 16)
     text = ({ " loses "+HIS(enemy)+" breath, looking at ",
               " lose your breath, looking at ",
               " with fear.\n" });
  else if (hit[0] < 32)
     text = ({ " staggers in shock, gazing in fear at ",
               " stagger in shock, gazing in fear at ",
               ".\n" });
  else
     text = ({ " collapses in complete terror of ",
               " collaps in complete terror of ",
               ".\n" });
  TP->catch_msg(QCTNAME(enemy)+text[0]+"you"+text[2]);
  enemy->catch_msg("You"+text[1]+QTNAME(TP)+text[2]);
  TP->tell_watcher(QCTNAME(enemy)+text[0]+QTNAME(TP)+text[2], enemy);

/*
  log_file("scarelog", ctime(time()) + " " +
	   TP->query_name() + " scared " + enemy->query_name() +
	   " [" + file_name(enemy) + "].\n" +
	   enemy->query_name() + text[0] + TP->query_name() + text[2] +
           "wpen="+wpen + ", skill="+TP->query_skill(SS_SMASH) +
           ", pen="+pen + ", proc_hurt="+hit[0] + ", phit="+hit[2] +
           ", dam="+hit[3] + "\n\n");
*/

  if (enemy->query_hp() <= 0) enemy->do_die(TP);

  enemy->add_prop("live_i_already_scared", 1);

  return 1;
}

/***********************  SMASH  ***************************/
int smash(string str)
{
  mixed enemy = get_one_target_from_string(str);
  int ttt, aaa;

  if(!enemy) return 0;

  if(TP->query_prop(S_C_PUN) == 3)
  {
    write("You are banned from using smash.\n");
    return 1;
  }

  TP->add_prop(SPEC_ATTACK_IS, SMASH);
  TP->catch_msg("You prepare to smash "+QTNAME(enemy)+".\n");
  ttt = TIME_TO_SMASH(TP);
  if(IS_LAYMAN(TP)) ttt = ttt * LAY_TIME / 100;
  aaa = set_alarmv(itof(ttt), 0.0, "do_smash", ({TP, enemy}));
  alarm[TP->query_name()] = aaa;
  return 1;
}

void do_smash(object who, mixed target)
{
  int aaa, i, skill, e_skill, pen, ttt;
  string *text, weapon_short, enemy_race;
  mixed *hit;
  object enemy, weapon, pulp;

  if(target && objectp(who) && present(target, ENV(who)))  enemy = target;

  who->add_prop(SPEC_ATTACK_IS, RELAX);
  ttt = TIME_TO_RELAX(who);
  if(IS_LAYMAN(who)) ttt = ttt * LAY_TIME / 100;
  aaa = set_alarm(itof(ttt), 0.0, "remove_relax", who);
  alarm[who->query_name()] = aaa;

  if(!enemy)
  {
    who->catch_msg("Your target has escaped.\n");
    return;
  }

  weapon = who->query_weapon(W_RIGHT);
  if (!weapon || weapon->query_wt() != W_CLUB)
  {
    weapon = who->query_weapon(W_BOTH);
    if (!weapon)
      weapon = who->query_weapon(W_LEFT);
  }
  if(!weapon || weapon->query_wt() != W_CLUB)
  {
    who->catch_msg("Too late you realized that you have no club to "+
                   "smash your enemy with.\n");
    return;
  }

  weapon_short = weapon->short();

  if(ENV(enemy)->query_prop(ROOM_M_NO_ATTACK))
  {
    who->catch_msg("You swing your "+weapon_short+" towards "+
            QTNAME(enemy)+"'s head but some magic presence stops you "+
            "from crushing it.\n");
    enemy->catch_msg(QCTNAME(who)+" swings "+HIS(who)+" "+weapon_short+
            " towards your head but some magic presence stops "+
            HIM(who)+" from crushing it.\n");
    who->tell_watcher(QCTNAME(who)+" swings "+HIS(who)+" "+weapon_short+
            " towards "+QTNAME(enemy)+"'s head but some magic presence stops "+
            HIM(who)+" from crushing it.\n", enemy);
    return;
  }

  skill = ((who->query_skill(SS_SMASH)+who->query_skill(SS_WEP_CLUB))/2)+
          who->query_stat(SS_DEX);

  if(sizeof(enemy->query_weapon(-1)))
    e_skill = enemy->query_skill(SS_PARRY);
  else
    e_skill = enemy->query_skill(SS_UNARM_COMBAT) / 2;
  e_skill += enemy->query_skill(SS_DEFENCE) + enemy->query_stat(SS_DEX);

  if(member_array(enemy, who->query_enemy(-1)) == -1)
    who->attack_object(enemy);

  /***  will we hit?  ***/
  if(random(2 * skill) > random(2 * e_skill / 3))
  {
    pen = F_PENMOD(weapon->query_pen()+25, who->query_skill(SS_SMASH));

    if(IS_LAYMAN(who)) pen = LAY_PEN * pen / 100;
    /* efficiency restricted - punishment */
    if(who->query_prop(S_C_PUN) == 2) pen = pen / 2;

    hit = enemy->hit_me(pen, W_BLUDGEON, who, -1);

    if (enemy->query_hp() <= 0)
     {
      if(who->query_pulping())
        text = ({" smashed ", " to a pulp!\n"});
      else text = ({" smashed ", " breaking "+enemy->query_possessive()+
        " skull, splattering the brain around!\n"});
    }
    else if (hit[0] == 0)
       text = ({ " only scared ", ".\n" });
    else if (hit[0] < 5)
       text = ({ " bonked ", " on the head.\n" });
    else if (hit[0] < 10)
       text = ({ " got good swing at ", ", BOING!!!\n" });
    else if (hit[0] < 25)
       text = ({ " skillfully hit ", " with great damage.\n" });
    else if (hit[0] < 50)
       text = ({ " smashed the head of ", " with powerful swing.\n" });
    else
       text = ({ " smashed ", " nearly to a pulp.\n" });
    who->catch_msg("You"+text[0]+QTNAME(enemy)+" with your "+
                   weapon_short+text[1]);
    enemy->catch_msg(QCTNAME(who)+text[0]+"you with "+HIS(who)+" "+
                   weapon_short+text[1]);
    who->tell_watcher(QCTNAME(who)+text[0]+QTNAME(enemy)+" with "+HIS(who)+" "+
                   weapon_short+text[1], enemy);

    if (enemy->query_hp() < 1)
    {
      if (!enemy->query_prop(LIVE_I_NO_CORPSE) && who->query_pulping())
      {
        enemy->add_prop(LIVE_I_NO_CORPSE, 1);
        enemy_race = enemy->query_race_name();
        i = enemy->query_prop(CONT_I_WEIGHT);

        enemy->do_die(who);
        setuid();
        seteuid(getuid());
        pulp = clone_object("/std/leftover");
        pulp->set_amount(i);
        pulp->leftover_init("pulp", enemy_race);
        pulp->set_adj(({"bloody",enemy_race}));
        pulp->set_short("bloody "+enemy_race+" pulp");
        pulp->set_long("This is the pulp that is left after you thoroughly "+
		       "smash "+LANG_ADDART(enemy_race)+".\n");
        pulp->move(environment(who), 0);
      }
      else
        enemy->do_die(who);
    }

    return;
  }
  who->catch_msg("You try to smash "+QTNAME(enemy)+" with your "+
                 weapon_short+" but miss.\n");
  enemy->catch_msg(QCTNAME(who)+" tries to hit you with "+HIS(who)+" "+
                   weapon_short+" but misses.\n");
  who->tell_watcher(QCTNAME(who)+" tries to hit "+QTNAME(enemy)+" with "+HIS(who)+
               " "+weapon_short+" but misses.\n", enemy);
}
/************************************************************************/

/***********************  FREE SMASH  ***********************************/

int do_free(string arg)
{
  if(arg != "commands")
  {
    NF("Free what?\n");
    return 0;
  }

  if(get_alarm(alarm[TP->query_name()]) || !TP->query_prop(SPEC_ATTACK_IS))
  {
    NF("Your commands are not stuck! Relax...\n");
    return 0;
  }

  TP->remove_prop(SPEC_ATTACK_IS);
  write("Be free...\n");

  return 1;
}

/************************************************************************/

void test() {write("test\n");}
