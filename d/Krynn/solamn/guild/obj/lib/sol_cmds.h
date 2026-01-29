/* 
 * This file contains Non-Emote-related Knight Commands:
 * break!, contact, expel, guildlist, leave, sponsorlist, knightlist
 */

/********************* break! ***********************************************/
int
breakup(string str)
{
    string *name, squirename, sponsorname;
    int lev, pos, i;
    
    pos = -1;
    NF("You are not a knight!\n");
    if ((lev = TP->query_knight_level()) < 2)
      return 0;
    NF("You have no sponsor!\n");
    if (lev == 2)
    {
	if (SPONSORED(TP->query_name()) == 0)
	    return 0;

	NF("You have no sponsor by that name!\n");
	name = (ADMIN)->get_knight_squire(TP);
	for (i = 0; i < sizeof(name); i++)
	{
	    sponsorname = L(name[i]);
	    if (sponsorname == L(str))
		pos = i;
	}
	if (pos == -1)
	    return 0;
	(ADMIN)->remove_squire_sponsorlist(TP->query_name());
	return 1;
    }
    
    NF("You have no squires!\n");
    if (SPONSOR(TP->query_name()) == 0)
      return 0;
    NF("You have no squire by that name!\n");
    name = (ADMIN)->get_squire_knight(TP);
    for (i = 0; i < sizeof(name); i++)
      {
	  squirename = L(name[i]);
	  if (squirename == L(str))
	    pos = i;
      }
    if (pos == -1)
      return 0;
    (ADMIN)->remove_squire_sponsorlist(C(str));
    return 1;
}

			
/********************* contact **********************************************/

int
contact(string str)
{
    object ob;
    string *name, name2, name3;
    int in, squires, i;
    
    squires = 0;
    if (!str)
      {
	  write("Use 'contact <msg>'.\n");
	  return 1;
      }
    name2 = TP->query_name();
    
    if (TP->query_knight_level() > 2)
      {
	  if ((ADMIN)->check_knightlist(name2))
	    {
		name = (ADMIN)->get_squire_knight(TP);
		for (i = 0; i < sizeof(name); i++)
		  if (ob = find_player(lower_case(name[i])))
		    {
			tell_object(ob, name2 + " prays: " + str + "\n");
			squires += 1;
		    }
		if (squires > 0)
		  {
		      write("You pray: " + str + "\n");
		      return 1;
		  }
		write("You have no squires currently logged on.\n");
		return 1;
	    }
	  write("You do not have any squires to contact!\n");
	  return 1;
      }
    
    
    if (TP->query_knight_level() < 3)
      {
	  if ((ADMIN)->check_squirelist(name2))
	    {
		name3 = (ADMIN)->get_knight_squire(TP);
		if (ob = find_player(lower_case(name3)))
		  {
		      tell_object(ob, name2 + " prays: " + str + "\n");
		      write("You pray: " + str + "\n");
		      return 1;
		  }
		write("Your knight currently isn't logged on.\n");
		return 1;
	    }			
	  write("You do not have a knight to contact!\n");
	  return 1;
      }
    
}


/********************* guildlist ********************************************/
int
guildlist(string str)
{
    string name;
    object ob;
    
    if (str)
      {
	  if (TP->query_wiz_level())
	    {
		name = C(str) + " is ";
		NF("No such player found.\n");
		if (!(ob = find_player(str)))
		  return 0;
	    } 
	  else 
	    {
		write("Curious aren't we?\n");
		return 1;
	    }
      } 
    else 
      {
	  ob = TP;
	  name = "You are ";
      }
    
    str = ob->list_mayor_guilds();
    if (str)
      write(name + "member of following guilds.\n" + str);
    else
      write(name + "not member of any guilds.\n");
    
    return 1;
}


/********************* leave ************************************************/
int
leave(string str)
{
    int i, num;
    string squire, knight;
    
    NF("Leave what? The Solamnian Knights?\n");
    if (str != "The Solamnian Knights")
      return 0;
    
    write("You leave the Solamnian Knights.\n");
    say("The world cries when " + QTNAME(TP) + " leaves the Solamnian " +
        "Knights.\n");
    
    if (TP->query_knight_level() > 2)
      {
	  knight = TP->query_name();
	  (ADMIN)->remove_knight_sponsorlist(knight);
      }
    
    if (TP->query_knight_level() < 3)
      {
	  squire = TP->query_name();
	  (ADMIN)->remove_squire_sponsorlist(squire);
      }
    
    LEAVE(TP);
    
    if (TP->query_default_start_location() == "/d/Krynn/solamn/vkeep/startroom"
	&& !TP->query_wiz_level())
      TP->set_default_start_location(TP->query_def_start());
    TP->remove_cmdsoul(KNIGHT_SOUL);
    if (P("pal_med", TP))
      P("pal_med", TP)->remove_object();
    TP->update_hooks();
    
    return 1;
}


/********************* sponsorlist **********************************************/
int
sponsorlist(string str)
{
    string name, *names, knight;
    int level, i;
    object ob;
    
    if (str)
      return 0;
    level = TP->query_knight_sublevel();
    name = TP->query_name();
    if (TP->query_knight_level() > 2)
      {		
	  write("You are allowed a maximum of ");
	  if (level == 11)
	    write("2 squires");
	  else if ((ADMIN)->is_assistant(TP->query_name()))
	    write("1 squire");
	  /* maybe assistants to the conclave will have 2 squires in the future, too?
	   */
	  else
	    write("1 squire");
	  write(" at this sublevel.\n");
	  if (TP->query_wiz_level() &&
	      member_array(TP->query_name(), GUILDMASTERS) >= 0)
	    write("However as Guildmaster this restriction is lifted.\n");
	  
	  if ((ADMIN)->check_knightlist(name))
	    {
		write("Currently you have the following squires:\n");
		write("(a * means they are logged on.)\n\n");
		names = (ADMIN)->get_squire_knight(TP);
		for (i = 0; i < sizeof(names); i++)
		  {
		      write(names[i] + " ");
		      if (ob = find_player(lower_case(names[i])))
			write(ob->query_title() + "  *\n");
		      else write("\n");
		  }
		return 1;
	    }
	  write("You have no squires!\n");
	  return 1;
      }
    if (TP->query_knight_level() < 3)
      {
	  if ((ADMIN)->check_squirelist(name))
	    {
		write("Your knight sponsorer is ");
		knight = (ADMIN)->get_knight_squire(TP);
		write(knight + "\n");
		if (ob = find_player(lower_case(knight)))
		  write(knight + " is currently logged on.\n");
		return 1;
	    }
	  write("You have no knight sponsorer!\n");
	  return 1;
      }
    return 0;
}

/********************* knightlist *******************************************/
int
is_knight(object ob)
{
    return ob->query_guild_member(GUILD_NAME) ||
      ob->query_guild_member(GUILD_NAME_LAY);
}

int
is_black_knight(object ob)
{
    return (ob->test_bit("Krynn",1,3));
}

int
is_lay_knight(object ob)
{
    return (ob->query_guild_name_lay() == GUILD_NAME_LAY &&
	    ob->query_guild_name_occ() != GUILD_NAME);
}

int
is_occ_knight(object ob, int lvl)
{
    return ob->query_guild_name_occ() == GUILD_NAME && 
      ob->query_knight_level() == lvl;
}

int
lex_greater(object ob1, object ob2)
{
    if (ob1->query_name() > ob2->query_name())
      return 1;
    else if (ob1->query_name() == ob2->query_name())
      return 0;
    else
      return -1;
}

int
knightlist(string str)
{
    object *players, *lay, *occ2, *occ3, *occ4, *occ5, *black;
    string txt = "", tmp;
    int i, wwidth = TP->query_option(1);
    int all = 0;

    if (wwidth < 11)
      wwidth = 78;
    
    if (str && (str == "v" || str == "verbose"))
      all = 1;

    players = filter(users(), "is_knight", this_object());
    lay = filter(players, "is_lay_knight", this_object());
    lay = sort_array(lay, "lex_greater");
    occ2 = filter(players, "is_occ_knight", this_object(),2);
    occ2 = sort_array(occ2, "lex_greater");
    occ3 = filter(players, "is_occ_knight", this_object(),3);
    occ3 = sort_array(occ3, "lex_greater");
    occ4 = filter(players, "is_occ_knight", this_object(),4);
    occ4 = sort_array(occ4, "lex_greater");
    occ5 = filter(players, "is_occ_knight", this_object(),5);
    occ5 = sort_array(occ5, "lex_greater");
    black = filter(players, "is_black_knight", this_object());
    black = sort_array(black, "lex_greater");

    players = occ5 + occ4 + occ3 + occ2 + lay + black;

    write("The following knights are currently logged on:\n");
    for (i = 0; i < sizeof(players); i++)
      {
	if (players[i]->query_invis() == 0 &&
	    extract(players[i]->query_name(), -2) != "jr")
	  {
	    if (all)
	      txt += break_string(players[i]->query_name() + " " +
				  players[i]->query_title() + "\n",wwidth-10,5)[5..];
	    else
	      {
		tmp = players[i]->query_guild_title_race();
		if (!players[i]->query_guild_family_name())
		  tmp = 0;
		txt += break_string(players[i]->query_name() + " " +
				    (tmp && stringp(tmp) && strlen(tmp) ? tmp + ", " : "") +
				    (players[i]->query_wiz_level() ? players[i]->query_title() :
				     "the " + players[i]->query_knight_title()) + "\n",
				    wwidth-10,5)[5..];
	      }
	  }
      }
    write(txt);
    return 1;
}

