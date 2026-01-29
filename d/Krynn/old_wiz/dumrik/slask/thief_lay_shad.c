/*
* This is the autoloading shadow for the Cabal of Hiddukel thief guild.
*
* originally taken from the Knights guild shadow by Nick
* Modified by Aridor
*/

inherit "/std/guild/guild_lay_sh";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <language.h>

#define THIEF_SUB "cabal_of_hiddukel_subloc"

int expl_alrm = 0;

/* Function name: query_guild_train
 * Description:   Give all the training objects
 */
string
query_guild_trainer_lay()
{
    return GUILDR + "train";
}

/*
 * Function name: query_guild_tax
 * Description:   Set the initial tax
 */
int 
query_guild_tax_lay() 
{
    return shadow_who->query_learn_pref(SS_LAYMAN); 
}

/*
 * Function name: query_guild_style_lay
 * Description:  Return the style of the guild
 */
string 
query_guild_style_lay() 
{
    return "thief"; 
}

/*
 * Function name: query_guild_name_lay
 * Description:  Query the name of the guild
 */
string 
query_guild_name_lay() 
{
    return GUILD_NAME; 
}

/*
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 * Arguments:     ob - the player.
 * Returns:  1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
  ob->add_subloc(THIEF_SUB, this_object()); 
  return 1;
}


/*
 * Function name: query_guild_not_allow_join_lay
 * Description:  Check if we allow that the player joins another guild.
 * Arguments:     player - the player
 *  type, style, name - the type, style and name of the
 *  intended guild.
 * Returns:  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_lay(object player, string type, string style,
			       string name)
{
    NF("You are already a member of another layman guild!\n");
    if (::query_guild_not_allow_join_lay(player, type, style, name))
      return 1;
    
    NF("Magic is very suspicious! We thieves don't mess with magic.\n");
    if (style == "magic")
      return 1;
    
    NF("We thieves don't want any other thieves in our ranks.\n");
    if (style == "thief")
      return 1;
    
    return 0;
}

/*
 * Function name: query_thief_level
 * Description:   What level has the thief achieved among the Cabal?
 * Returns:  the level
 */
int
query_thief_level()
{
   object ob;
   int newlevel, numlevels = sizeof(TAX);
   if (ob = present(THIEF_OBJ_ID, shadow_who))
     {
	 newlevel = (shadow_who->query_base_stat(SS_LAYMAN) * numlevels / 140);
	 return (((newlevel >= numlevels) ? (numlevels - 1) : newlevel));
     }
   return 0;
}


/*
 * Function name: query_thief_title
 * Description:   What is the title of this thief ?
 * Returns:  The thief title
 */
string
query_thief_title()
{
    object *players;
    int notch = 1;
    int i, j = shadow_who->query_stat(SS_LAYMAN);
    int lev = shadow_who->query_thief_level();
    players = users();
    if (shadow_who->query_wiz_level())
      return "Wizzed Burglar of the Cabal of Hiddukel";
    for (i = 0; i < sizeof(players); i++)
      {
	  if (players[i]->query_guild_name_lay() == GUILD_NAME &&
	      !players[i]->query_wiz_level() &&
	      players[i]->query_thief_level() == lev &&
	      players[i]->query_stat(SS_LAYMAN) > j)
	    notch++;
      }
    return C(LANG_WORD(notch)) + " " + C(LAY_TITLES[lev]) +
      " Burglar of the Cabal of Hiddukel";
}

/* Function name: query_guild_title_lay
 * Description:   give the guild title
 * Arguments:     none
 * Returns:       the guild title if shown
 */
string
query_guild_title_lay()
{
    if (!(P(THIEF_OBJ_ID,shadow_who)->query_show_title_on_intro()))
      return 0;
    else
      return query_thief_title();
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
    string str;
    int i, aware, hidden;
    object arm;
    
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
    
    if (subloc != THIEF_SUB)
      return shadow_who->show_subloc(subloc, me, for_obj);
    
    if (for_obj == me)
      str = "You have a tatoo of a broken balance on your neck.\n";
    else /*show the subloc to others only if they really can see it!*/
      {
	  aware = for_obj->query_skill(SS_AWARENESS);
	  hidden = me->query_skill(SS_HIDE);
	  if (arm = me->query_armour(TS_NECK))
	    hidden = hidden + (i = arm->query_ac()) + 5 * i + random(i);
	  if (for_obj->query_wiz_level() || (aware >= hidden) || MEMBER(for_obj))
	    str = capitalize(me->query_pronoun()) +
	      " has a tatoo of a broken balance on " + (me->query_possessive()) +
		" neck.\n";
      }
    return str;
}

/* CAN I DO THAT???? */
/* Mercade said to not shadow add_exp... */
void
add_exp(int e, int battle)
{
  object ob = P(THIEF_OBJ_ID, shadow_who);
  shadow_who->add_exp(e,battle);
  if (ob)
    ob->set_tax(0);
}

void
check_alignment_expel_if_necessary()
{
    if (shadow_who->query_alignment() > 120)
      (JOIN_ROOM)->expel_member_from_guild(shadow_who->query_real_name(),
					   " your alignment shows that you " +
					   "did not follow the path of " +
					   "Hiddukel for too long.");
}

void
set_alignment(int num)
{
    if (num > 100 && !expl_alrm)
      {
	  shadow_who->catch_msg("\nA shadow washes over you and settles " +
				"into your soul.\nThe shadow speaks and you " +
				"are certain this is Hiddukel, the patron " +
				"of the Cabal.\nHe tells you: Your " +
				"alignment is tilting too far to the holy " +
				"end of the scale! If you don't correct " +
				"this mistake, you will be expelled from " +
				"the guild.\nHe then withdraws from you " +
				"and disappears.\n\n");
          expl_alrm = set_alarm(200.0,0.0,"check_alignment_expel_if_necessary");
      }
    else if (num <= 100 && expl_alrm)
      {
	  remove_alarm(expl_alrm);
	  expl_alrm = 0;
      }
    shadow_who->set_alignment(num);
}

/*
 * Function name: query_guild_skill_name
 * Description:   When a players uses the skills command he should get the
 *  the skill names, not the 'special' string.
 * Arguments:     type - the number of the skill
 * Returns:  0 if no skill of mine, else the string. "" if skill not shown.
 */
mixed
query_guild_skill_name(int type)
{
    if (type = SS_SACRIFICE)
      return "";
    
    return 0;
}

int
hook_thief_steal_bonus()
{
    int sk = shadow_who->query_skill(SS_SACRIFICE);
    if (sk <= 0)
      return sk;
    sk = SACRIFICE_2_BONUS(shadow_who);
    if (sk > 500)
      return 500;
    return sk;
}

void
hook_thief_stolen_object(object what)
{
    int value = what->query_value(); /* in coppers */
    int sk = shadow_who->query_skill(SS_SACRIFICE);
    sk -= (value / 10);
    shadow_who->set_skill(SS_SACRIFICE, sk);

    /* I'd like to give out exp here if possible by all means.
     * It'd make sense according to the value gained, so it
     * could be:
     *      shadow_who->add_exp(value ,1);
     * I'd like this to be combat exp, though it's not combat,
     * I think it's kind of a replacement.
     *
     * THIS SHOULD BE IN THE SKILL (SOUL) RATHER THAN IN THE SHADOW
     * ONCE THE SKILLS GO INTO THE MUDLIB.
     */
}

