/*
* Standard spells of Solamnian Knights
*/

inherit "/std/spells";  /* To inherit the standard spell function. */
#include "../local.h"
#include "../guild.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <cmdparse.h>"There is no prestige to be won by suicide.\n"

#define SPELL_DIR "/d/Krynn/solace/guild/spells/" /* To be used later. */

void
create_spells()
{
    set_name(SPELL_OB_NAME);
    set_no_show();
    
    /*         verb           function              name  */
    
    add_spell("consider",      "consider",       "consider <target>");
    add_spell("radiance",      "radiance",       "a simple light prayer.");
    add_spell("revive",        "revive",         "a minor cure prayer.");
    add_spell("fortify",       "fortify",        "a minor protection prayer.");
    
    
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
}

mixed
revive()
{
    int mana, level, healed, mxhp;
    object ob, room;
    
    room = environment(this_player());
    
    if (!(ob = P("pal_med", TP)))
      return "You have no medal, you should seek guidance.\n";
    
    if (RNMAGIC(room))
      return "Some force around you distracts you from your prayers.\n";
    
    mana = TP->query_mana();
    
    if (mana < 50)
      return "You are too mentally exhausted to pray correctly.\n";
    
    TP->add_mana(-50);
    if (random(TP->query_stat(SS_WIS)) < random(25))
      return "You pray but lose concentration\n";
    
    
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    
    write("You start to pray to Paladine and you feel much healthier.\n");
    say(QCTNAME(TP)+ " mumbles a prayer and " + TP->query_possessive() +
	" health seems slightly improved.\n");
    
    mxhp = TP->query_max_hp();
#if NEW_KNIGHTS
    /* this is the effect after the changeover */
    healed = mxhp / 10;
#else
    /* this is the effect before the changeover */
    healed = mxhp / 30;
#endif
    TP->heal_hp(healed);
    return 1;
}

mixed
fortify()
{
    int mana, level;
    object shieldobj, ob, room;
    
    room = environment(this_player());
    
    if (!(ob = P("pal_med", TP)))
      return "You have no medal, you should seek guidance.\n";
    
    if (present("shieldobj", TP))
      return "This prayer is already in operation!\n";
    
    if (RNMAGIC(room))
      return "Some force around you distracts you from your prayers.\n";
    
    mana = TP->query_mana();
    if (mana < 60)
      return "You are too mentally exhausted to pray correctly.\n";
    
    TP->add_mana(-60);
    if (random(TP->query_stat(SS_WIS)) < random(30))
      return "You pray but lose concentration\n";
    
    
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    
    write("You start to pray to Paladine and you feel the power of Paladines protection.\n");
    say(QCTNAME(TP) + " mumbles a prayer.\n");
    
    seteuid(getuid(TO));
    
    level = TP->query_knight_level();
    shieldobj = clone_object(OBJ + "shieldobj");
    shieldobj->set_duration(random(TP->query_stat(SS_INT) *2) + (level * 20));
    shieldobj->move(TO);
    TP->wear_arm(shieldobj);
    
    return 1;
}

mixed
radiance()
{
    int mana, level;
    object lightobj, ob, room;
    
    room = environment(this_player());
    
    if (!(ob = P("pal_med", TP)))
      return "You have no medal, you should seek guidance.\n";
    if (RNMAGIC(room))
      return "Some force around you distracts you from your prayers.\n";
    
    mana = TP->query_mana();
    if (mana < 5)
      return "You are too mentally exhausted to pray correctly.\n";
    
    TP->add_mana(-5);
    if (random(TP->query_stat(SS_WIS)) < random(15))
      return "You pray but lose concentration\n";
    
    
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
    
    
    write("You start to pray to Paladine and your medal begins to glow.\n");
    say(QCTNAME(TP) + " mumbles a prayer and " + TP->query_possessive() +
	" medal begins to glow!\n");
    
    seteuid(getuid(TO));
    level = TP->query_knight_level();
    lightobj = clone_object(OBJ + "lightobj");
    lightobj->set_duration(random(TP->query_stat(SS_INT) * 2) +
			   random(level * 20) + 245);
    lightobj->move(TP);
    return 1;
}

mixed
consider(string str)
{
    int level, sublevel, stat, align;
    object ob, *arr;
    string st, pr, nr, tr, typ;
    
    write("You start to pray to Paladine.\n");
    say(QCTNAME(TP) + " mumbles a prayer.\n");
    if (!str)
      {
	  if (!(ob = P("pal_med", TP)))
	    return "You have no medal, you should seek guidance.\n";
	  level = TP->query_knight_level();
	  sublevel = TP->query_knight_sublevel();
	  stat = TP->query_skill(SS_PRESTIGE_ST);
	  
	  if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
	    TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
	  
	  if (level > 2)
	    {
		write("You are a " + TP->query_knight_title() + ".\n");
		write("You are " + TP->query_knight_subtitle() + ".\n");
		if (sublevel == 1)
		  write("You are close to becoming a Black Knight of the " +
			"Rose!\n");
				
		if (stat >= SS_LEVEL10)
		  {
		      write("You have the prestige of a conclave member!\n");
		      if (level == 3)
			st = "crown";
		      if (level == 4)
			st = "sword";
		      if (level == 5)
			st = "rose";
		      if ((ADMIN)->query_conclave(st) == "")
			write("The position is currently vacant.\n");
		      if ((ADMIN)->query_conclave(st) != "")
			write("Unfortunatly the position is filled.\n");
		      return 1;
		  }
		
                if (sublevel < TP->query_level_up(stat + 1))
                  st = "You are very very close to advancing";
                else if (sublevel < TP->query_level_up(stat + 2))
                  st = "You are very close to advancing";
                else if (sublevel < TP->query_level_up(stat + 3))
                  st = "You are close to advancing";
                else if (sublevel < TP->query_level_up(stat + 4))
                  st = "You are not too far away from advancing";
                else if (sublevel > TP->query_level_up(stat - 1))
                  st = "You are very close to lowering";
                else if (sublevel > TP->query_level_up(stat - 3))
                  st = "You are close to lowering";
                else if (sublevel > TP->query_level_up(stat - 4))
                  st = "You are not very close to lowering";
                else
                  st = "You are well suited to";

                write(st + " your rank.\n");
		
	    }
	  if (level == 4 || level == 5)
	    return 1;
	  if (level == 2)
	    {
		write("You are a Solamnian Squire.\n");
		
		nr = SQUIRE_TITLES[sublevel + 1];
		pr = SQUIRE_TITLES[sublevel - 1];
		tr = SQUIRE_TITLES[sublevel];
		if (sublevel < TP->query_level_up(stat + 1))
		  st = "You are very very close to rising to " + nr;
		else if (sublevel < TP->query_level_up(stat + 2))
		  st = "You are very close to rising to " + nr;
		else if (sublevel < TP->query_level_up(stat + 3))
		  st = "You are close to rising to " + nr;
		else if (sublevel < TP->query_level_up(stat + 4))
		  st = "You are not too far away to rising to " + nr;
		else if (sublevel > TP->query_level_up(stat - 1))
		  st = "You are very close to dropping to " + pr;
		else if (sublevel > TP->query_level_up(stat - 3))
		  st = "You are close to dropping to " + pr;
		else if (sublevel > TP->query_level_up(stat - 4))
		  st = "You are not very close to dropping to " + pr;
		else
		  st = "You are well suited as " + tr;
		write("You are " + tr + "\n");
		write(st + "\n");
		if (MEMBER(TP))
		  {
		      if (sublevel > 4)
			write("You have the prestige to join the Crown " +
			      "Order.\n");
		      else
			write("You do not have the prestige to join the " +
			      "Crown Order.\n");
		      if (TP->query_stat(SS_STR) > 10 &&
			  TP->query_stat(SS_DEX) > 8 && 
			  TP->query_stat(SS_CON) > 10 && 
			  TP->query_stat(SS_INT) > 7 &&
			  TP->query_stat(SS_WIS) > 10)
			write("You have the stats to join the Crown Order.\n");
		  }
	    }
	  if (level == 2) /* || level == 3 we don't allow upgrading currently*/
	    {
		if (MEMBER(TP))
		  {
		      if (sublevel > 6)
			write("You have the prestige to join the Sword " +
			      "Order.\n");
		      else
			write("You do not have the prestige to join the " +
			      "Sword Order.\n");
		      if (TP->query_stat(SS_STR) > 30 &&
			  TP->query_stat(SS_DEX) > 20 && 
			  TP->query_stat(SS_CON) > 30 && 
			  TP->query_stat(SS_INT) > 18 && 
			  TP->query_stat(SS_WIS) > 30)
			write("You have the stats to join the Sword Order.\n");
		      else
			write("You do not have the stats to join the Sword " +
			      "Order.\n");
		      
		      if (sublevel > 8)
			write("You have the prestige to join the Rose " +
			      "Order.\n");
		      else
			write("You do not have the prestige to join the " +
			      "Rose Order.\n");
		      if (TP->query_stat(SS_STR) > 50 &&
			  TP->query_stat(SS_DEX) > 30 &&
			  TP->query_stat(SS_CON) > 50 &&
			  TP->query_stat(SS_INT) > 38 &&
			  TP->query_stat(SS_WIS) > 50)
			write("You have the stats to join the Rose Order.\n");
		      else
			write("You do not have the stats to join the Rose " +
			      "Order.\n");
		      return 1;
		  }
		write("You are a layman knight within the guild.\n");
		if (sublevel > 8 && (ADMIN)->get_knight_squire(TP))
		  write("You have enough prestige to be an " +
			"independant squire.\n");
		return 1;
	    }
	  if (level == 1)
	    {
		if (MEMBER(TP))
		  {
		      if (sublevel < 1)
			write("You are very far from being reinstated.\n");
		      if (sublevel == 1)
			write("You are not very close from being reinstated.\n");
		      if (sublevel == 2)
			write("You are close to being reinstated.\n");
		      return 1;
		  }
		write("You are a layman knight within the guild.\n");
		return 1;
	    }
	  return 1;
      }

    arr = FIND_STR_IN_OBJECT(str, E(TP));
    if (!sizeof(arr))
      return "Couldn't find " + str + ".\n";
    ob = arr[0];
    if (!living(ob))
      return "That thing isn't alive.\n";
    if (ob == TP)
      return "There is no prestige to be won by suicide.\n";
    stat = TP->query_ob_prestige(ob);
    align = ob->query_alignment();
    typ = "creature";
    
    if (interactive(ob) && ob->query_race_name() != "goblin")
      {
	  stat = -1;
	  typ = "person";
      }
    
    if (stat == 0)
      TP->catch_msg("Paladine has not yet formed an opinion about " + QTNAME(ob) + ".\n");
    else if (stat > 1000)
      TP->catch_msg("Paladine would be very pleased if you killed " +
		    QTNAME(ob) + ".\n");
    else if (stat > 500)
      TP->catch_msg("Paladine would be pleased if you killed " +
		    QTNAME(ob) + ".\n");
    else if (stat > 100)
      TP->catch_msg("Paladine would approve if you killed " +
		    QTNAME(ob) + ".\n");
    else if (stat > 0)
      TP->catch_msg("Paladine would not become sad if you killed " +
		    QTNAME(ob) + ".\n");
    else  if (stat < -4)
      TP->catch_msg("Paladine would NOT be pleased if you killed " +
		    QTNAME(ob) + ".\n");
    else  if (stat < -2)
      TP->catch_msg("Paladine wouldn't like it at all if you killed " +
		    QTNAME(ob) + ".\n");
    else  if (stat < -0)
      TP->catch_msg("Paladine does not approve if you killed " +
		    QTNAME(ob) + ".\n");
    
    if (align > 0)
      write("You feel good radiating from this " + typ + ".\n");
    else if (align < -200)
      write("You feel evil radiating from this " + typ + ".\n");
    
    return 1;
}



void
give_knight_spells(int level)
{
    remove_spell("radiance");
    remove_spell("revive");
    remove_spell("fortify");
    
    if (level >= L_SWORD)
      {
	  add_spell("radiance", "radiance", "a simple light prayer.");
	  add_spell("revive", "revive", "a minor cure prayer.");
	  add_spell("fortify", "fortify", "a minor protection prayer.");
      }
    
    command_loaded = 0;
}


