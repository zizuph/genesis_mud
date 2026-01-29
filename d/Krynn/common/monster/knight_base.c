/* The normal guards by Percy. */
/* base file to inherit for all knight npc's by Aridor, 09/94 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/guild/guild.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>

inherit M_FILE

int sublevel, level;
string subtitle, title;

string
set_my_title()
{
    if (!level)
      {
	  level = random(2) + 2;
	  sublevel = random(5) + 3;
      }
    if (level == 3)
      {
	  subtitle = CROWN_TITLES[sublevel];
	  return "Knight of the Crown";
      }
    else
      {
	  subtitle = SQUIRE_TITLES[sublevel];
	  return "Squire of Solamnia";
      }
}

void
create_knight_npc()
{
    set_my_title();
}

void
create_krynn_monster()
{
    int i;
    add_name("knight");
    set_adj("knight");
    set_extra_long("He is a " + set_my_title() + ".\n" +
		   "He is wearing the medal of the Solamnian " +
		   "Knighthood and he is " + subtitle + ".\n");
    set_race_name("human");
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_PARRY, 90 + random(10));
    set_skill(SS_DEFENCE, 80 + random(10));
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_AWARENESS,50);
    set_act_time(random(2) + 1);
    add_act("@@do_rescue");
    set_cact_time(random(2) + 1);
    add_cact("@@do_rescue");
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop("_knight_npc", 1);
    set_alignment(500);
    set_knight_prestige(-2);
    create_knight_npc();
    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me");
}

void
arm_me()
{
    seteuid(geteuid(this_object()));
    clone_object(VOBJ + "towguard_arm")->move(TO);
    clone_object(VOBJ + "towguard_wep")->move(TO);
    command("wear armour");
    command("wield weapon");
}

int
query_knight_level() { set_my_title(); return level; }

int
query_knight_sublevel() { return sublevel; }

void
attacked_by(object ob)
{
    if (QREALRACE(ob) != "draconian")
      TO->do_rescue();
    ::attacked_by(ob);
}

string
do_rescue()
{
    /* rescue a fellow knight who is currently under attack */
    object *who = FILTER_LIVE(all_inventory(E(TO)));
    object *ene, *good = ({ }), *bad = ({ });
    object person;
    int i;
    who -= ({ TO, 0 });
    ene = who->query_attack();
    for(i = 0;i<sizeof(ene);i++)
      if (who[i] != TO  && (who[i]->id("knight") || MEMBER(who[i]) ||
	  LAYMAN(who[i])) && ene[i] && !ene[i]->id("knight") &&
	  !MEMBER(ene[i]) && !LAYMAN(ene[i]))
	{
	    good += ({ who[i] });
	    bad += ({ ene[i] });
	}
    if (!good || !sizeof(good))
      return "";
    i = random(sizeof(bad));
    if (!good[i]->id("knight") || random(5))
      {
	  if (good[i]->query_hp() < query_hp())
	    {
		attack_object(bad[i]);
		bad[i]->attack_object(TO);
		tell_room(E(TO),"The knight human heroically rescues " +
			  QTNAME(good[i]) + ".\n");
	    }
      }
    else
      {
	  if (E(TO)->not_called_for_help_yet() &&
	      QREALRACE(bad[i]) != "draconian")
	    E(TO)->call_for_help(TO,good[i],bad[i]);
      }
    return "";
}

/* these guards have the knights special attacks,
 * bash and ckick, too!
 */
int 
do_bash(object enemy)
{
    object  me = this_object();
    mixed *hitresult;
    string  how;
    
    if (E(TO) == E(enemy))
      {
	  tell_room(E(TO), QCTNAME(me) + " looks at " + QTNAME(enemy) +
		    " with murder in " + me->query_possessive() + 
		    " eyes.\n", enemy);
	  enemy->catch_msg(QCTNAME(TO) + " looks at you with murder in " +
			   TO->query_possessive() + " eyes.\n");
	  
	  hitresult = enemy->hit_me(150 + random(50), W_BLUDGEON, me, -1);
	  
	  /* me->catch_msg("You send "+capitalize(enemy->query_possessive())+
	   *               " sprawling with a wonderful bash.\n");
	   */
	  enemy->catch_msg(QCTNAME(me)+" sends you sprawling with a " +
			   "wonderful bash!\n");
	  tell_room(E(TO), QCTNAME(me)+" sends "+QTNAME(enemy) + 
		    " sprawling with a wonderful bash!\n",enemy);
    
	  if(enemy->query_hp() <=0)
	    enemy->do_die(me);
	  return 1;
      }
}

int 
do_ckick(object enemy)
{
    object  me = this_object();
    mixed *hitresult;
    string  how;
    
    if (E(TO) == E(enemy))
      {
	  tell_room(E(TO), QCTNAME(me) + " looks at " + QTNAME(enemy) +
		    " with rage in " + me->query_possessive() + 
		    " face.\n", enemy);
	  enemy->catch_msg(QCTNAME(TO) + " looks at you with rage in " +
			   TO->query_possessive() + " face.\n");
	  
	  hitresult = enemy->hit_me(100 + random(50), W_BLUDGEON, me, -1);
	  
	  /* me->catch_msg("You kick "+capitalize(enemy->query_possessive())+
	   *               " with a bonecrushing sound.\n");
	   */
	  enemy->catch_msg(QCTNAME(me)+" kicks you hard! You can hear" +
			   " your bones crunch!\n");
	  tell_room(E(TO), QCTNAME(me)+" kicks "+QTNAME(enemy) +
		    " with a bonecrushing sound!\n",enemy);
	  
	  if(enemy->query_hp() <=0)
	    enemy->do_die(me);
	  return 1;
      }
}                 

int 
special_attack(object enemy)
{
    int i;
    
    if(random(4))
      return 0;
    
    switch(random(2))
      { 
	case 0:
	  do_bash(enemy); 
	  break;
	case 1:
	  do_ckick(enemy);
	  break;
      }
    return 0;
}
