/*
 * This is the autoloading shadow for the Solamnian Knight guild.
 *
 * Made by Nick (updated march 93 by Nick and Percy)
 *    updated query_ob_prestige() function 11/24/94  Grace
 */

inherit "/std/guild/guild_occ_sh";
#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <language.h>

#define SOL_SUB "solamnian_subloc"
#define MERCYFUL "_knight_mercyful"

/*
 * Prototypes
 */
int query_level_up(int stat, int level);
int query_level_down(int stat, int level);
int query_knight_level();

void change_prestige(int pres, int minusflag);

/*
 * Variables
 */
object *att_ob;/* Objects attacked by me first */
object *att_me;/* Objects that attacked me first */
mapping pres_loss;/* Objects I ran away from and lost prestige */
int evilcheckalarm = 0; /*alarm that runs when i'm evil*/


/* Function name: query_guild_train
 * Description:   Give all the training objects
 */
string *
query_guild_trainer_occ()
{
    return ({ VDIR + "train1", VDIR + "train2" });
}

/* Query_stat modification to enable Knight of the Rose ability to lead
* anyone by Morrigan Nov 96
*/

int
query_stat(int which_stat)
{
    if (which_stat != SS_DIS)
        return (shadow_who->query_stat(which_stat));

    if ((query_knight_level() == 5) && ((calling_function() == "join") ||
         (calling_function() == "team_join")))
        return 10000; /* This is stupid, but still */

    return shadow_who->query_stat(SS_DIS);
/*
    
        

    if (this_player() != shadow_who &&
        this_player()->query_prop("_rose_invite") == shadow_who->query_real_name())
    {
        this_player()->remove_prop("_rose_invite", shadow_who->query_real_name());
        return (this_player()->query_stat(SS_DIS)-10);
    }
    else
        return (shadow_who->query_stat(SS_DIS));
*/
}

/*
 * Function name: query_guild_tax
 * Description:   Set the initial tax
 */
int 
query_guild_tax_occ() 
{ 
return shadow_who->query_learn_pref(SS_OCCUP); 
}
     
/*
 * Function name: query_guild_style_occ
 * Description:  Return the style of the guild
 */
string 
query_guild_style_occ() 
{
 return "fighter"; 
}

/*
 * Function name: query_guild_name_occ
 * Description:  Query the name of the guild
 */
string 
query_guild_name_occ() 
{ 
return GUILD_NAME; 
}

/*
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 *  If we discover a goblin we will keep him, just to throw him
 *  out the proper way later.
 * Arguments:     ob - the player.
 * Returns:  1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    if (ob->query_guild_name_lay() == "Vampyr guild")
      return 0;
    
    ob->add_subloc(SOL_SUB, this_object());
    
    if (ob->query_alignment() < -20)
      {
	  write("You are evil, this will not be good for your prestige!\n");
	  if (!evilcheckalarm)
	    evilcheckalarm = set_alarm(180.0,0.0,"evil_check");
      }
    
    return 1;
}

/*
 * Function name: evil_check
 * Description:   This function is called now and then to see if the Knight is
 *  evil. If he is he will lose prestige, if he is a goblin he
 *  will be thrown out and banished from the guild. Non goblins
 *  will still have the chance to turn to the right path.
 */
void
evil_check()
{
    int loss;

    evilcheckalarm = 0;
    if (this_object()->query_alignment() < -20)
      {
	  loss = -1000 * (query_knight_level() - 1) + 500;
	  change_prestige(loss, 1);
	  if (this_object()->query_race_name() == "goblin")
	    ADMIN->goblin_leave(shadow_who);
	  else if (shadow_who->query_skill(SS_PRESTIGE_ACC) > 0)
	    evilcheckalarm = set_alarm(180.0,0.0,"evil_check");
      }
}

/*
 * Function name: set_alignment
 * Description:   Sets the alignment of a player, we will check if knights
 *  are closing evilness
 * Arguments:     a: The amount of points
 */
void
set_alignment(int a)
{
    int old_a;
    
    if ((old_a = shadow_who->query_alignment()) > -20 && a < ALIGN_WARNING && a < old_a)
      write("Your alignment is dropping dangerously low!\n");
    
    shadow_who->set_alignment(a);
    if (a < -20 && !evilcheckalarm)
      evilcheckalarm = set_alarm(20.0,0.0,"evil_check");
}

/*
 * Function name: query_guild_not_allow_join_occ
 * Description:  Check if we allow that the player joins another guild.
 * Arguments:     player - the player
 *  type, style, name - the type, style and name of the
 *intended guild.
 * Returns:  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_occ(object player, string type, string style,
			       string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
      return 1;
    
    NF("We brave fighters don't mess with magic.\n");
    if (style == "magic")
      return 1;
    
    NF("We brave fighters don't want thieves in our ranks.\n");
    if (style == "thief")
      return 1;
    
    
    NF("You cannot join that evil guild!\n");
    if (player->query_guild_name_lay() == "Vampyr guild")
      return 1;
    return 0;
}

/*
 * Function name: query_knight_level
 * Description:   What level have the knight achieved in the Knighthood ?
 * Returns:  the level
 */
int
query_knight_level()
{
    object ob;
    
    if (ob = P("pal_med", shadow_who))
      return ob->query_knight_level();
    return 0;
}

/*
 * Function name: query_knight_level
 * Description:   What level has the knight achieved in the Knighthood ?
 * Returns:  the level
 */
set_knight_level(int level)
{
    object ob;
    
    if (ob = P("pal_med", shadow_who))
      ob->set_knight_level(level);
}

/*
 * Function name: query_knight_sublevel
 * Description:   What sublevel have the knight achieved in his Order ?
 * Returns:  the sublevel
 */
int
query_knight_sublevel()
{
    object ob;
    
    if (ob = P("pal_med", shadow_who))
      return ob->query_knight_sublevel();
    return 0;
}

/*
 * Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:  The new postoffice
 */
string 
query_def_post() { return "/d/Krynn/solamn/vkeep/post"; }
     
/*
 * Function name: set_high
 * Description:   Call it to promote the player to conclave member
 */
void
set_high(int lvl)
{
    object ob;
    int my_lev = query_knight_level();
    if (lvl != my_lev)
      return;
    if (!(ob = P("pal_med", shadow_who)))
      return;
    ob->set_knight_sublevel(11);
    if (my_lev == 3)
      {
	  if ((ADMIN)->query_conclave("crown") != "")
	    return;
	  if ((ADMIN)->crown_highest() == shadow_who->query_name())
	    (ADMIN)->set_crown_high(12, "none");
	  (ADMIN)->add_conclave(shadow_who->query_name(), "crown");
      }
    else if (my_lev == 4)
      {
	  if ((ADMIN)->query_conclave("sword") != "")
	    return;
	  if ((ADMIN)->sword_highest() == shadow_who->query_name())
	    {
		(ADMIN)->set_sword_high(12, "none");
	    }
	  (ADMIN)->add_conclave(shadow_who->query_name(), "sword");
      }
    else if (my_lev == 5)
      {
	  if ((ADMIN)->query_conclave("rose") != "")
	    return;
	  if ((ADMIN)->rose_highest() == shadow_who->query_name())
	    {
		(ADMIN)->set_rose_high(12, "none");
	    }
	  (ADMIN)->add_conclave(shadow_who->query_name(), "rose");
      }
    shadow_who->catch_msg("You have been promoted to the conclave!\n");
}

/*
 * Function name: clear_high
 * Description:   Call it to demote the player from conclave member
 */
void
clear_high(int lvl)
{
    object ob;
    
    if (!(ob = P("pal_med", shadow_who)))
      return;
    seteuid(getuid(ob));
    
    if (lvl == 3)
      (ADMIN)->remove_conclave("crown");
    if (lvl == 4)
      (ADMIN)->remove_conclave("sword");
    if (lvl == 5)
      (ADMIN)->remove_conclave("rose");
    
    ob->set_knight_sublevel(10);
    shadow_who->catch_msg("You have been demoted from the conclave!\n");
}

/*
 * Function nam: prefix_title
 * Description:  Find any additional titles (like Disgraced, Honoured, etc.)
 * Returns:      that additional title
 */
string
prefix_title()
{
    int disgr = 0;
    string award = 0;
    int tmp;
    object ob;
    string str = "";
    //return "";
    
    /* check disgraced */
    tmp = shadow_who->query_skill(SS_DISGRACED);
    if (tmp > REALAGE(shadow_who))
      disgr = 1;
    else
      shadow_who->remove_skill(SS_DISGRACED);
    
    /* check awards */
    award = (ADMIN)->query_my_awards(shadow_who);
    
    if (disgr && award)
      str = "Admonished ";
    else if (disgr)
      str = "Disgraced ";
    else if (award)
      str = "Honoured ";
    return str;
}

/*
 * Function name: query_knight_title
 * Description:   What is the title of this knight ?
 * Returns:  The Knight title
 */
/*
string
query_knight_title()
{
    return prefix_title() + KNIGHT_TITLES[query_knight_level()];
}
     
*/
string
query_knight_title()
{
if (query_knight_level() > 2 && query_knight_sublevel() == 11)
{
switch(query_knight_level())
{
case 5:
return prefix_title() + "High Justice of Solamnia, "+
"Knight of the Rose";
break;
case 4:
return prefix_title() + "High Clerist of Solamnia, "+
"Knight of the Sword";
break;
case 3:
return prefix_title() + "High Warrior of Solamnia, "+
"Knight of the Crown";
break;
}
}
else if (query_knight_level() > 2 && query_knight_sublevel() == 10)
{
switch(query_knight_level())
{
case 5:
return prefix_title() + "Lord Knight of the Rose";
break;
case 4:
return prefix_title() + "Lord Knight of the Sword";
break;
case 3:
return prefix_title() + "Lord Knight of the Crown";
break;
}
}

return prefix_title() + KNIGHT_TITLES[query_knight_level()];
}

/*
 * Function name: query_knight_subtitle
 * Description:   What is the subtitle of this knight ?
 * Returns:  The Knight subtitle
 */
string
query_knight_subtitle() 
{ 
    int gend;
    gend = shadow_who->query_gender();
    if (query_knight_level() == 1)
      {
	  return "a Black knight of the Rose";
      }
    if (query_knight_level() == 2)
      {
	  return SQUIRE_TITLES[query_knight_sublevel()];
      }
    if (query_knight_level() == 3)
      {
	  if (gend == 0)
	    return CROWN_TITLES[query_knight_sublevel()]; 
	  else
	    return FCROWN_TITLES[query_knight_sublevel()]; 
      }
    if (query_knight_level() == 4)
      {	
	  if (gend == 0)
	    return SWORD_TITLES[query_knight_sublevel()];
	  else
	    return FSWORD_TITLES[query_knight_sublevel()];
      }
    if (query_knight_level() == 5)
      {
	  if (gend == 0)
	    return ROSE_TITLES[query_knight_sublevel()]; 
	  else
	    return FROSE_TITLES[query_knight_sublevel()]; 
      }
    return "without a title";
}

/*
 * Function name: query_guild_title_occ
 * Description:   Find the occupational title of the knight.
 * Returns:       The occupational knight title.
 */
string
query_guild_title_occ()
{
  return query_knight_title();
}


/*
 * Function name: query_guild_skill_name
 * Description:   When a players uses the skills command he should get the
 *  the skill names, not the 'special' string.
 * Arguments:     type - the number of the skill
 * Returns:  0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    if ((type >= SS_PRESTIGE_ACC && type <= SS_CHARITY) ||
	type == SS_DISGRACED)
      return "";
    
    if ((type < SS_RESCUE) || (type > SS_BLOCK))
      return 0;
    
    return KNIGHT_SKILL_DESC[type - SS_RESCUE];

/*    switch(type)
    {
        case SS_RESCUE:
            return "rescue";
            break;
        case SS_KATTACK:
            return "kattack";
            break;
        case SS_BLOCK:
            return "block";
            break;
        default:
            return 0;
            break;
    } */
}

/*
 * Function name: q_att_ob
 * Description:  Keeps track of objects I attacked first
 */
object *
q_att_ob()
{
    if (!att_ob)
      att_ob = ({});
    
    return att_ob;
}

/*
 * Function name: q_att_me
 * Description:  Objects that attacked me first
 */
object *
q_att_me()
{
    if (!att_me)
      att_me = ({});
    
    return att_me;
}

/* Function name: check_charity
 * Description:  Check the players charity pts to see if high enough
 * Arguments:  val = value of the object being compared
 * Returns:  0 if fails else 1
 */
int
check_charity(int val)
{
    int total;
    
    total = shadow_who->query_skill(SS_CHARITY);
    total -= val;
    if (total < 0)
      return 0;
    return 1;
}

/* Function name: add_charity
 * Description:  adds on charity pts
 * Arguments:  val = value of the object being added
 */
void
add_charity(int val)
{
    int oldskill;
    
    oldskill = shadow_who->query_skill(SS_CHARITY);
    oldskill += val;
    shadow_who->set_skill(SS_CHARITY, oldskill);
    
}

/* Function name: sub_charity
 * Description:  subtract charity pts
 * Arguments:  val = value of the object being subtracted
 */
void
sub_charity(int val)
{
    int oldskill;
    
    oldskill = shadow_who->query_skill(SS_CHARITY);
    oldskill -= val;
    shadow_who->set_skill(SS_CHARITY, oldskill);
    
}

/*
 * Function name: sub_prestige
 * Description:   subtract xp prestige
 * Arguments:     amount - the amount to subtract
 */
void
sub_prestige(int amount)
{
    int olda;
    
    olda = shadow_who->query_skill(SS_PRESTIGE_ACC);
    olda -= amount;
    shadow_who->set_skill(SS_PRESTIGE_ACC, olda);
    shadow_who->change_prestige(0,1);
    shadow_who->set_skill(SS_PRESTIGE_ST,
			  shadow_who->exp_to_stat(shadow_who->query_skill(SS_PRESTIGE_ACC)));
}

/*
 * Function name: query_ob_prestige
 * Description:   Check for the prestige of the object.
 * Arguments:     ob - the object to look at
 * Returns:  pres - the prestige
 *  Note:
 *  The prestige penelty for killing players has been reduced (I had
 *  raised it in Nov 94) seeing as players will have the Disgraced
 *  property added to them when they kill. IF Conclave feel more
 *  prestige should be lost, they can remove it themselves, or ask
 *  us to raise the penelty.     (Grace 12 Feb 95)
 */

int
query_ob_prestige(object ob)
{
    int pres;

    pres=0;
    pres = ob->query_knight_prestige();
    if (pres>0)
      {
          if (ob->query_average_stat()>70)
            pres=490+(pres/5);
      }
    if (!ob->query_npc() && member_array(ob, q_att_ob()) >= 0)                 
     {                                                                         
         if (MEMBER(ob) || LAYMAN(ob))                                         
           pres = -20;
         else if (ob->query_race_name() == "goblin")                           
           pres = -1; /* No big deal killing a goblin player */                
         else if (ob->query_alignment() < 0)                                   
           pres = -1; /* Penelty not so big if player is evil. */
         else                                                                  
           pres = -5;
     }          
    
    if (!pres)
      {
	  if (ob->id("gargoyle"))
	    pres = 150;
	  else if (ob->id("goblin"))
	    pres = 140;
	  else if (ob->id("dragon"))
	    pres = 600;
      }
    
    if (pres < 0 && member_array(ob, q_att_me()) >= 0)
      pres = 1;
    
    if (!pres && ob->query_alignment() < 0)
      pres = -(ob->query_alignment() / 10);
    
    return pres;
}

int
in_team_with_non_knight()
{
    object *tm = shadow_who->query_team_others();
    int *klvl = tm->query_knight_level();
    klvl -= ({ 1,2,3,4,5,6 });
    if (klvl && sizeof(klvl))
      return 1;
    return 0;
}

/*
 * Function name: notify_you_killed_me
 * Description:  This is called each time the knight kills something.
 * Arguments:     ob - the object that was killed
 */
void
notify_you_killed_me(object ob)
{
    string str;
    int pres;
    object para, *ene;

    if (P("pal_med",shadow_who)->query_generous())
      {
	  seteuid(getuid(TO));
	  para = clone_object(OBJ + "no_die_paralyze");
	  para->set_remove_time(query_knight_level() * 20 +
				query_knight_sublevel() * 2 + 1);
	  para->move(ob,1);
	  ob->add_subloc("unconscious_subloc",para);
	  ob->set_all_knight_generous(1);

	  ene = ob->query_enemy(-1);
	  ene->stop_fight(ob);
	  ob->stop_fight(ene);
	  pres = query_ob_prestige(ob);
	  if (pres > 0)
	    {
		if (ob->query_prop(MERCYFUL))
		  {
		      shadow_who->catch_msg("No prestige on the second time.\n");
		      pres = 0;
		  }
		else if (!in_team_with_non_knight())
		  pres = pres * 3 / 2;
	    }
	  else
	    pres /= 4;
	  ob->add_prop(MERCYFUL, shadow_who);
	  shadow_who->set_alignment(shadow_who->query_alignment() +
				    F_KILL_ADJUST_ALIGN(shadow_who->query_alignment(),
							ob->query_alignment()));
	  set_alarm(1.0,0.0,"change_prestige", pres);
	  return;
      }

    shadow_who->notify_you_killed_me(ob);
    if (interactive(ob))
      {
	  KILLED(shadow_who, ob);
	  if ((MEMBER(ob) || LAYMAN(ob)) &&
	      member_array(ob, q_att_ob()) >= 0 &&
	      ob->query_race_name() != "goblin")
	    {
		BANISH(shadow_who, "killing a fellow Solamnian Knight");
		return;
	    }
/*
 * The following line wre added by Grace to prevent Disgrace
 *  of Solamnians who kill players in defence of Solamnia
 */
        str = file_name(environment(ob));
        if (str[..15] == "/d/Krynn/solamn/")
        {
            shadow_who->catch_msg("\nYour actions in defence of Solamnia "+
                "have been Honourable. You will not be Disgraced.\n\n");
            return;
        }

	  DISGRACE(shadow_who, "killing another player");
      }
    if (ob->query_prop(MERCYFUL))
           shadow_who->catch_msg("No prestige on the second time.\n");
    else
      {
	  pres = query_ob_prestige(ob);
	  if (pres < 0 && !random(10))
	    pres = pres * 20;
	  set_alarm(1.0,0.0,"change_prestige", pres);
      }
}

/*
 * Function name: change_prestige
 * Description:   When a player has killed something or should change the 
 *                prestige for some other reason, call this function.
 * Arguments:     pres - the prestige to add.
 */
varargs void
change_prestige(int pres, int minusflag)
{
    int level, new_level, truelevel, tmp;
    object ob, me_ob;
    
    if (!(ob = P("pal_med", shadow_who)))
      return;
    
    level = query_knight_sublevel();
    truelevel = query_knight_level();
    
    if (pres > 0 || minusflag)
      {
	  /*if (truelevel == L_BROSE && pres > 0)
	    pres = 5 * pres / shadow_who->query_average_stat();
	    the requirements are now done further down! */

	  if (truelevel == L_SQUIRE &&
	      (SPONSORED(shadow_who->query_name()) == 0) && pres > 0)
	    pres = pres / 3;

	  shadow_who->set_skill(SS_PRESTIGE_ACC,
				shadow_who->query_skill(SS_PRESTIGE_ACC) +
				pres);
	  shadow_who->set_skill(SS_PRESTIGE_ST, 
				shadow_who->exp_to_stat(shadow_who->query_skill(SS_PRESTIGE_ACC)));
	  new_level = query_level_up(shadow_who->query_skill(SS_PRESTIGE_ST),
				     level);
      } 
    else if (pres == 0)
      {
	  shadow_who->set_skill(SS_PRESTIGE_ACC,
				shadow_who->query_skill(SS_PRESTIGE_ACC) - level);
	  shadow_who->set_skill(SS_PRESTIGE_ST, 
				shadow_who->exp_to_stat(shadow_who->query_skill(SS_PRESTIGE_ACC)));
	  new_level = query_level_up(shadow_who->query_skill(SS_PRESTIGE_ST), level);
      }
    else
      {
	  shadow_who->set_skill(SS_PRESTIGE_ST,
				shadow_who->query_skill(SS_PRESTIGE_ST) + pres);
	  shadow_who->set_skill(SS_PRESTIGE_ACC, 
				shadow_who->stat_to_exp(shadow_who->query_skill(SS_PRESTIGE_ST)));
	  new_level = query_level_up(shadow_who->query_skill(SS_PRESTIGE_ST),
				     level);
      }

    if (C(ADMIN)->crown_highest() == shadow_who->query_name() &&
	truelevel != 3)
      (ADMIN)->set_crown_high(12,"none");
    if (C(ADMIN)->sword_highest() == shadow_who->query_name() &&
	truelevel != 4)
      (ADMIN)->set_sword_high(12,"none");
    if (C(ADMIN)->rose_highest() == shadow_who->query_name() &&
	truelevel != 5)
      (ADMIN)->set_rose_high(12,"none");
      
    /* wizzes can't be conclave */
    if ((shadow_who->query_wiz_level() || truelevel < 3) && 
	new_level > 10)
      new_level = 10;
    else if (truelevel == 3)
      {
	  if (new_level == 11 &&
	      (ADMIN)->query_conclave("crown") != shadow_who->query_name())
	    {
		/* no conclave and i'm the runner-up */
		if ((ADMIN)->query_conclave("crown") == ""  && 
		    C((ADMIN)->crown_highest()) == shadow_who->query_name() &&
		    ((ADMIN)->query_conclave("sword") == "" || (ADMIN)->query_conclave("rose") == ""))
		  set_high(3);
		/* conclave and i'm the runner-up */
		else if (shadow_who->query_skill(SS_PRESTIGE_ACC) > (ADMIN)->query_crown_high())
		  {
		      if (extract(shadow_who->query_name(),-2) != "jr")
			(ADMIN)->set_crown_high(shadow_who->query_skill(SS_PRESTIGE_ACC), 
						shadow_who->query_name());
		      new_level = 10;
		  }
		/* conclave and i'm the runner-up but got prestige reduced */
		else if (shadow_who->query_skill(SS_PRESTIGE_ACC) < (ADMIN)->query_crown_high() && 
			 shadow_who->query_name() == C((ADMIN)->crown_highest()))
		  {
		      (ADMIN)->set_crown_high(shadow_who->query_skill(SS_PRESTIGE_ACC), 
					      shadow_who->query_name());
		      new_level = 10;
		  }
		/* all other cases */
		else
		  new_level = 10;
	    }
	  if (level == 11 && new_level == 10)
	    {
		/* I was conclave but my prestige dropped too much */
		if ((ADMIN)->query_conclave("crown") == shadow_who->query_name())
		  clear_high(3);
		/* I was runner-up, but my prestige dropped too much */
		else if (C((ADMIN)->crown_highest()) == shadow_who->query_name())
		  (ADMIN)->set_crown_high(12,"none");
	    }
      }
    else
      if (truelevel == 4)
	{
	    if (new_level == 11 &&
		(ADMIN)->query_conclave("sword") != shadow_who->query_name())
	      {
		  /* no conclave and i'm the runner-up */
		  if ((ADMIN)->query_conclave("sword") == ""  && 
		      C((ADMIN)->sword_highest()) == shadow_who->query_name() &&
		      ((ADMIN)->query_conclave("crown") == "" || (ADMIN)->query_conclave("rose") == ""))
		    {
			set_high(4);
		    }
		  /* conclave and i'm the runner-up */
		  else if (shadow_who->query_skill(SS_PRESTIGE_ACC) > (ADMIN)->query_sword_high())
		    {
			if (extract(shadow_who->query_name(),-2) != "jr")
			  (ADMIN)->set_sword_high(shadow_who->query_skill(SS_PRESTIGE_ACC), 
						  shadow_who->query_name());
			new_level = 10;
		    }
		  /* conclave and i'm the runner-up but got prestige reduced */
		  else if (shadow_who->query_skill(SS_PRESTIGE_ACC) < (ADMIN)->query_sword_high() && 
			   shadow_who->query_name() == C((ADMIN)->sword_highest()))
		    {
			(ADMIN)->set_sword_high(shadow_who->query_skill(SS_PRESTIGE_ACC), 
						shadow_who->query_name());
			new_level = 10;
		    }
		  /* all other cases */
		  else
		    new_level = 10;
	      }
	    if (level == 11 && new_level == 10)
	      {
		  /* I was conclave but my prestige dropped too much */
		  if ((ADMIN)->query_conclave("sword") == shadow_who->query_name())
		    clear_high(4);
		  /* I was runner-up, but my prestige dropped too much */
		  else if (C((ADMIN)->sword_highest()) == shadow_who->query_name())
		    (ADMIN)->set_sword_high(12,"none");
	      }
	}
      else
	if (truelevel == 5)
	  {
	    if (new_level == 11 &&
		(ADMIN)->query_conclave("rose") != shadow_who->query_name())
	      {
		  /* no conclave and i'm the runner-up */
		  if ((ADMIN)->query_conclave("rose") == ""  && 
		      C((ADMIN)->rose_highest()) == shadow_who->query_name() &&
		    ((ADMIN)->query_conclave("sword") == "" || (ADMIN)->query_conclave("crown") == ""))
		    set_high(5);
		  /* conclave and i'm the runner-up */
		  else if (shadow_who->query_skill(SS_PRESTIGE_ACC) > (ADMIN)->query_rose_high())
		    {
			if (extract(shadow_who->query_name(),-2) != "jr")
			  (ADMIN)->set_rose_high(shadow_who->query_skill(SS_PRESTIGE_ACC), 
						 shadow_who->query_name());
			new_level = 10;
		    }
		  /* conclave and i'm the runner-up but got prestige reduced */
		  else if (shadow_who->query_skill(SS_PRESTIGE_ACC) < (ADMIN)->query_rose_high() && 
			   shadow_who->query_name() == (ADMIN)->rose_highest())
		    {
			(ADMIN)->set_rose_high(shadow_who->query_skill(SS_PRESTIGE_ACC), 
					       shadow_who->query_name());
			new_level = 10;
		    }
		  /* all other cases */
		  else
		    new_level = 10;
	      }
	    if (level == 11 && new_level == 10)
	      {
		  /* I was conclave but my prestige dropped too much */
		  if ((ADMIN)->query_conclave("rose") == shadow_who->query_name())
		    clear_high(5);
		  /* I was runner-up, but my prestige dropped too much */
		  else if (C((ADMIN)->rose_highest()) == shadow_who->query_name())
		    (ADMIN)->set_rose_high(12,"none");
	      }
	  }
	else
	  new_level == 10;
    
    me_ob = P("pal_med", ob);
    if (truelevel == 2 && new_level == L_0 && shadow_who->query_race_name() == "goblin")
      {
	  ADMIN->goblin_leave(shadow_who);
      }
    
    if (truelevel == 2)
      {
	  if (level > new_level)
	    {
		if (new_level == 0)
		  {
		      shadow_who->catch_msg("Paladine disapproves of your " +
					    "actions as a squire. You have " +
					    "disgraced the squirehood! " +
					    "You will now be a black knight " +
					    "of the rose until you have " +
					    "proven yourself worthy to once " +
					    "again be a squire!\n");
		      (ADMIN)->remove_squire_sponsorlist(shadow_who->query_name());
		      seteuid("Krynn");
		      shadow_who->set_bit(1, 3);
		      truelevel = 1;
		      shadow_who->set_skill(SS_PRESTIGE_ST, 10);
		      shadow_who->set_skill(SS_PRESTIGE_ACC, 
					    shadow_who->stat_to_exp(shadow_who->query_skill(SS_PRESTIGE_ST)));
		  }
		
	    }
      }
    
    if (truelevel == 1)
      {
	  if (level < new_level)
	    {
		if (new_level == 0) 
		  new_level = 1;

		tmp = shadow_who->query_average_stat() / 25 + 2;
		if (tmp>9) tmp=9;

		if (new_level >= 3)
		  {
		      shadow_who->catch_msg("Paladine approves of your actions " + 
					    "and you have been reinstated to " +
					    "the Knight orders. Congratulations!\n");
		      seteuid("Krynn");
		      shadow_who->clear_bit(1, 3);
		      if (shadow_who->test_bit("Krynn",1,4) ||
			  shadow_who->test_bit("Krynn",1,5))
			{
			  truelevel = 3;
			  shadow_who->catch_msg("You are now once again"
					    + " a Knight of the Crown!\n");			  
			  shadow_who->clear_bit(1, 4);
			  shadow_who->set_bit(1, 5);
			}
		      else
			{
			  truelevel = 2;
			  shadow_who->catch_msg("You are now once again"
						+ " a Squire of Solamnia!\n");
			  shadow_who->clear_bit(1, 4);
			  shadow_who->clear_bit(1, 5);
			}
		      new_level = 1;


		      ob->set_knight_level(truelevel);
		      shadow_who->set_skill(SS_PRESTIGE_ST, 10);
		      shadow_who->set_skill(SS_PRESTIGE_ACC, 
					    shadow_who->stat_to_exp(shadow_who->query_skill(SS_PRESTIGE_ST)));
		      if (me_ob)
			{
			  me_ob->give_spells(ob);
			  me_ob->set_tax(0);
			}
		      ob->set_knight_sublevel(new_level);
		      ob->add_subloc("solamnian_subloc", this_object());
		  }
	    }
      }
    
    if (truelevel > 2) 
      {
	  if (level > new_level)
	    {
		if (new_level != 0)
		  {
		      shadow_who->catch_msg("Paladine does not approve of " +
					    "your actions. Your prestige has " +
					    "lowered too much. Your rank " +
					    "has lowered.\n");
		      ob->set_knight_sublevel(new_level);
		  }
		if (new_level == 0)
		  {
		      if (truelevel >= 3) 
			{
			    shadow_who->catch_msg("You have disgraced your order" +
						  " with your lack of prestige. " +
						  "You will now become a black knight " +
						  "until you have sufficiently " +
						  "atoned for your deeds.\n");
			    (ADMIN)->remove_knight_sponsorlist(shadow_who->query_name());
			    seteuid("Krynn");
			    shadow_who->set_bit(1, 3);
			    truelevel = 1;
			    shadow_who->set_skill(SS_PRESTIGE_ST, 10);
			    shadow_who->set_skill(SS_PRESTIGE_ACC, 
						  shadow_who->stat_to_exp(shadow_who->query_skill(SS_PRESTIGE_ST)));
			    shadow_who->add_subloc("solamnian_subloc", this_object());
			}
		  }
		
		if (me_ob)
		  {
		    me_ob->give_spells(ob);
		    me_ob->set_tax(0);
		  }
		ob->set_knight_sublevel(new_level);
		ob->add_subloc("solamnian_subloc", this_object());
	    }
	  
	  else if (level < new_level) 
	    {
		if (me_ob)
		  {
		    me_ob->give_knight_spells(truelevel);
		    me_ob->set_tax(0);
		  }
		shadow_who->catch_msg("Your prestige has raised to " +
				      "enough to let you get a higher " +
				      "rank. Congratulations.\n");
		ob->set_knight_sublevel(new_level);
		ob->add_subloc("solamnian_subloc", this_object());
	    }
      }
    
    if (new_level == 0) 
      new_level = 1;
    
    ob->set_knight_sublevel(new_level);
    ob->set_knight_level(truelevel);
    
    ob->add_subloc("solamnian_subloc", this_object());
    
    if (new_level == L_1 && truelevel == L_BROSE &&
	shadow_who->query_race_name() == "goblin")
      ADMIN->goblin_leave(shadow_who);
}


int
query_level_up(int stat, int level)
{
    if (stat >= SS_LEVEL10)
      return L_11;
    if (stat >= SS_LEVEL9)
      return L_10;
    
    if (stat >= SS_LEVEL8)
      return L_9;
    
    if (stat >= SS_LEVEL7)
      return L_8;
    
    if (stat >= SS_LEVEL6)
      return L_7;
    
    if (stat >= SS_LEVEL5)
      return L_6;
    
    if (stat >= SS_LEVEL4)
      return L_5;
    
    if (stat >= SS_LEVEL3)
      return L_4;
    
    if (stat >= SS_LEVEL2)
      return L_3;
    
    if (stat >= SS_LEVEL1)
      return L_2;
    
    if (stat > SS_LEVEL0)
      return L_1;
    
    return L_0;
}

int
query_level_down(int stat, int level)
{
    return level;
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *  me      - I
 *  for_obj - The looker
 * Returns:  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str, subtitle, aw_str;
    string awards, bear;
    object ob;

    subtitle = query_knight_subtitle();
    
    if (subloc != SOL_SUB)
      return shadow_who->show_subloc(subloc, me, for_obj);

    ob = P("pal_med", me);
    if (!ob)
      return "";
    
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "You are wearing the medal of the Solamnian Knighthood.\n";

    if (for_obj == me)
      {
	  str = "You are ";
	  bear = "You bear ";
      }
    else
      {
	  str = C(PRONOUN(me)) + " is ";
	  bear = C(PRONOUN(me)) + " bears ";
      }
    
    awards = (ADMIN)->query_award_nice(shadow_who);
    if (awards && awards != "")
      aw_str = bear + awards + ".\n";

    str = str + "wearing the medal of the Solamnian Knighthood, and " +
      L(str) + subtitle + ".\n";
    if (aw_str)
      str += aw_str;
    
    return str;
}

/* 
 * Function name:   restore_prestige_loss
 * Description:     Restore lost prestige when continuing a fight.
 * Arguments:       who: the enemy
 */
void
restore_prestige_loss(object who)
{
    if (member_array(who, m_indexes(pres_loss)) >= 0)
      {
	  change_prestige(pres_loss[who]);
	  pres_loss = m_delete(pres_loss, who);
      }
}


/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       ob: The attacker
 */
void
attacked_by(object ob)
{
    object sh;

    if (member_array(ob, q_att_ob()) == -1 &&
	member_array(ob, q_att_me()) == -1)
      {
	  if (!att_me)
	    att_me = ({});
	  else
	    att_me -= ({ 0 });
	  
	  att_me += ({ ob });
      }
    restore_prestige_loss(ob);
    seteuid(getuid(TO));
    sh = clone_object(OBJ + "no_die_shadow");
    if (!sh->shadow_me(ob))
      sh->remove_object();

    shadow_who->attacked_by(ob);
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
void
attack_object(object ob)
{
    object sh;

    if (member_array(ob, q_att_ob()) == -1 &&
	member_array(ob, q_att_me()) == -1)
      {
	  if (!att_ob)
	    att_ob = ({});
	  else
	    att_ob -= ({ 0 });
	  
	  att_ob += ({ ob });
      }
    restore_prestige_loss(ob);
    seteuid(getuid(TO));
    sh = clone_object(OBJ + "no_die_shadow");
    if (!sh->shadow_me(ob))
      sh->remove_object();

    shadow_who->attack_object(ob);
}

/*
 * Function name: my_reduce_prestige_on_move
 * Description:   Walking away from the fight you started will reduce prestige.
 */
void
my_reduce_prestige_on_move()
{
    int level = query_knight_level();
    int pres = 10 * level * level * level;
    object ene = shadow_who->query_attack();
    if (ene && att_ob && member_array(ene, att_ob) > -1)
      {
	  change_prestige(-pres, 1);
	  if (!pres_loss)
	    pres_loss = ([ ]);
	  pres_loss += ([ ene:pres ]);
      }
}

/*
 * Function name: adjust_combat_on_move
 * Description:   Called to let movement affect the ongoing fight. This
 *                is used to print hunting messages.
 * Arguments:	  True if leaving else arriving
 */
void
adjust_combat_on_move(int leave)
{
    if (leave)
      my_reduce_prestige_on_move();
    shadow_who->adjust_combat_on_move(leave);
}

#if 1
/* calc the summed stats of 'who' and its team. */
int
calc_odds(object who)
{
    int i;
    int sum = who->query_average_stat();
    object *team = who->query_team_others();

    for(i=0;i<sizeof(team);i++)
      sum += team[i]->query_average_stat();
    return sum;
}

/*
 * Function name: do_die
 * Description:   Called from enemy combat object when it thinks we died.
 * Arguments:     killer: The enemy that caused our death.
 */
void
do_die(object killer)
{
    int knight_odds, opponent_odds, ratio;

    /* The knight gains prestige when he dies in an honorable fight! */
    if (shadow_who->query_hp() <= 0 && killer && living(killer))
      {
	  knight_odds = calc_odds(shadow_who);
	  opponent_odds = calc_odds(killer);
	  ratio = knight_odds * 100 / opponent_odds;
	  /* If the knight (+team) was fighting against overwhelming odds
	   * give a lot of prestige
	   */
	  if (ratio <= 95)
	    change_prestige(20000);
	  /* If the knight was fighting against equal odds, give some
	   *  prestige
	   */
	  if (ratio > 95 && ratio < 110)
	    change_prestige(5000);
	  /* If the knight fought against weaker opponent(s), or anything
	   * else, no prestige
	   */
      }
    shadow_who->do_die(killer);
}
#endif

/*
 * Function name: set_whimpy
 * Description:   Redefine the wimpy level for the knights. Knights are not
 *                allowed to set high wimpy levels.
 * Arguments:     flag, the wimpy level to set at.
 */
void
set_whimpy(int flag)
{
    int lim = WIMPY_LIMIT[query_knight_level()] +
              WIMPY_LIMIT2[query_knight_sublevel()];
    if (lim > 99)
      lim = 99;
    if (flag > lim)
      shadow_who->catch_msg("This wimpy level is not allowed for a Knight of " +
			    "Solamnia!\n");
    else
      lim = flag;
    shadow_who->set_whimpy(lim);
}


/*
 * Function name: 
 * Description:   
 * Arguments:
 * Returns:  
 */
