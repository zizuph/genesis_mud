
void
create_spell_consider(string arg)
{
    set_spell_element(SS_ELEMENT_LIFE, 5);
    set_spell_form(SS_FORM_DIVINATION, 3);
    set_spell_time(3);
    set_spell_mana_needed(2);
    set_spell_mana_fail(2);
    set_spell_allow_no_targets();
}

string
consider_mutter(mixed target)
{
    if (target)
      return "consider your value of " + target;
    return "consider my prestige";
}

mixed
do_consider(string str)
{
    int level, sublevel, stat, align;
    object ob, *arr;
    string st, pr, nr, tr, typ;
    
    level = TP->query_knight_level();
    sublevel = TP->query_knight_sublevel();
    stat = TP->query_skill(SS_PRESTIGE_ST);
	  
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 200)
      TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 200);
	  
    if (!str)
      {
	  if (level > 2)
	    {
		write("You are a " + TP->query_knight_title() + ".\n");
		write("You are " + TP->query_knight_subtitle() + ".\n");
		if (sublevel == 1)
		  write("You are close to becoming a Black Knight of the " +
			"Rose!\n");
		
		if (stat >= SS_LEVEL10)
		  {
		      if (TP->query_knight_sublevel() != 11)
			write("You have the prestige of a conclave member!\n");
		      if (level == 3)
			st = "crown";
		      if (level == 4)
			st = "sword";
		      if (level == 5)
			st = "rose";
		      if ((ADMIN)->query_conclave(st) == "")
			write("The position is currently vacant.\n");
		      if ((ADMIN)->query_conclave(st) != "" &&
			  TP->query_knight_sublevel() != 11)
			write("Unfortunatly the position is filled.\n");
		      return 1;
		  }
		
		if (sublevel < TP->query_level_up(stat + 1))
		  st = "You are very very close to advance";
		else if (sublevel < TP->query_level_up(stat + 2))
		  st = "You are very close to advance";
		else if (sublevel < TP->query_level_up(stat + 3))
		  st = "You are close to advance";
		else if (sublevel < TP->query_level_up(stat + 4))
		  st = "You are not too far away to advance";
		else if (sublevel > TP->query_level_up(stat - 1))
		  st = "You are very close to lower";
		else if (sublevel > TP->query_level_up(stat - 3))
		  st = "You are close to lower";
		else if (sublevel > TP->query_level_up(stat - 4))
		  st = "You are not very close to lower";
		else
		  st = "You are well suited for";
		
		write(st + " your rank.\n");
		
	    }
	  if (level == 5)
	    return 1;
	  if (level == 2)
	    {
		if (MEMBER(TP))
		  write("You are a Solamnian Squire.\n");
		else
		  write("You are a Sentry of Solamnia.\n");
		
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
	  if (level == 3 && MEMBER(TP))
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
	    }
	  if (level == 4 && MEMBER(TP))
	    {
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
	  if (LAYMAN(TP))
	    {
		write("You are a layman member of the guild.\n");
		if (sublevel > 8 && (ADMIN)->get_knight_squire(TP))
		  write("You have enough prestige to be an " +
			"independant sentry.\n");
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
		write("You are a layman member of the guild.\n");
		return 1;
	    }
	  return 1;
      }

    if (!targets || !sizeof(targets))
      return 0;

    ob = targets[0];
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
      TP->catch_msg("Paladine has no opinion about " + QTNAME(ob) + ".\n");
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
    
    if (align > 200)
      write("You feel good radiating from this " + typ + ".\n");
    else if (align < -200)
      write("You feel evil radiating from this " + typ + ".\n");
    
    return 1;
}

