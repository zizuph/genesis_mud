inherit "/std/guild/guild_occ_sh";

#include <ss_types.h>
#include <language.h>
#include <const.h>
#include <stdproperties.h>
#include "/d/Roke/Cirath/barbarians/skills.h"

#define GUILD_TYPE "occupational"
#define GUILD_NAME "The Barbarian Herd"
#define GUILD_STYLE "fighter"
#define BARB_SUB        "barb_subloc"

/*
 * Function name: query_guild_tax
 * Description  : Set the initial tax
 */
query_guild_tax_occ()
{
   return 12; /* Whatever you wish to set it to. */
}

/* Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 *                If we discover a fighter or thief, we will throw
 *                him out
 * Arguments:     ob - the player.
 * Returns:       1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    ob->add_subloc(BARB_SUB, this_object());

    return 1;
}

/* Function name: query_guild_not_allow_join_occ
 * Description:   Check if we allow that the player joins another guild.
 * Arguments:     player - the player
 *                type, style, name - the type, style and name of the
 *                intended guild.
 * Returns:       1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_occ(object player, string type, string style, string
name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    notify_fail("We Barbarians don't want mages in our ranks.\n");
    if (style == "magic")
        return 1;
    notify_fail("We Barbarians don't want Knights in our ranks.\n");
    if(name == "Solamnian Knights")
        return 1;

    return 0;
}

string
query_clan_name(object ob)
{
  int sc,eld,clan;

  sc = ob->query_skill(BARB_SCORE);

  eld = sc / 10;
  clan = sc - (eld * 10);

  if(clan == 1)      return "White Eagle Clan";
  else if(clan == 2) return "Mammoth Clan";

  return "*no clan*";
}

/* Function name: query_barbarian_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 */
int
query_barb_level()
{

 object who;
  int a,b,c,d,e,f,g;
  who=query_shadow_who();
  a = who->query_stat(SS_CON);
  b = who->query_stat(SS_STR);
  d = who->query_skill(SLAYING) + who->query_skill(BONKING);
  e = who->query_skill(CHOPPING) + who->query_skill(HOLDING) + who->query_skill(BLOCKING) + who->query_skill(STABBING);
  f = who->query_skill(SS_WEP_SWORD) + who->query_skill(SS_WEP_AXE);
  g = who->query_exp_combat();
  c = (a + b + (d/2) + (e/4) + (f/2)) / 25;

  if(c>10)
    c==10;

  return c;

}

string query_barb_align()
{
  object who;
  string str;
  int a;

  who = query_shadow_who();

  a = who->query_alignment();

  if(a < -100)
    return "Deathbringing";
  else if(a > 100)
    return "Bloodthirsting";
  else
     return "Brainbeating";
}

/*
 * Function name: query_guild_title_occ
 * Description:   Gives the guild title.
 * Returns:       Guess what.
 */
string query_guild_title_occ()
{
  object who;
  string str,gender,brute,align,cname;
  int stat,cxp,txp,qxp;

  stat = query_barb_level();

  who=query_shadow_who();

  cname = query_clan_name(who);

  if(who->query_gender()==1)    gender="Amazon";
  else if (who->query_gender()) gender="Transvestite";
  else                          gender="Beast";

  align = query_barb_align();

  txp = who->query_exp();
  cxp = who->query_exp_combat();
  qxp = txp - cxp;

  if(cxp<2*qxp)
    return "Wimpy Snort";
  else if(who->query_skill(BARB_SCORE)>9 && who->query_skill(BARB_SCORE)<20)
    return "Elder Barbarian of the "+cname;
  else if(who->query_skill(BARB_SCORE)>19 && who->query_skill(BARB_SCORE)<30)
    return cname + " Eldest of the Barbarian Herd";
  else if(who->query_skill(BARB_SCORE)>29 && who->query_skill(BARB_SCORE)<40)
    return "Eldest Barbarian";
  else
  {
    if(4*qxp>txp)
      brute = align + " Slayer";
    else
      brute = align + " Mass Murderer";

    switch(stat)
      {
        case 0: str="Newbie";break;
        case 1: str="Puny"; break;
        case 2: str="Lousy"; break;
        case 3: str="Harmless"; break;
        case 4: str="Weak"; break;
        case 5: str="Poor"; break;
        case 6: str="Amateurish"; break;
        case 7: str="Average"; break;
        case 8: str="Known"; break;
        case 9: str="Good"; break;
        case 10: str="Viscious"; break;
        case 11: str="Brutal"; break;
        case 12: str="Feared"; break;
        case 13: str="Champion"; break;
        case 14: str="Excellent"; break;
        case 15: str="Deadly"; break;
        case 16: str="Genocidal"; break;
        case 17: str="Master"; break;
        case 18: str="Legend"; break;
        case 19: str="Guru";
      }

    str+=" "+gender+" and "+brute+" of the Barbarian Herd";
    return str;
  }
}

#ifdef THIS_IS_OBSOLETE_NOW
/* Function name: query_title
 * Description:   We change the title of our members depending on their level
 * Returns:       The new title
 */
query_title()
{
   string o_title,title;
   o_title = shadow_who->query_title();
    title=query_guild_title_occ();

   /*
    * Wizards get to keep their own title
    */
   if (shadow_who->query_wiz_level())
        return title + "and "+o_title;

   if (strlen(o_title))
       return o_title + " and " + query_guild_title_occ();
   else
       return query_guild_title_occ();
}
#endif

mixed query_guild_skill_name(int type)
{
  if (type == SLAYING)         return "slaying";
  else if (type == BONKING)    return "headbut enemy";
  else if (type == BARB_SCORE) return "";
  else if (type == CHOPPING)   return "chop enemy";
  else if (type == BLOCKING)   return "block enemy";
  else if (type == HOLDING)    return "hold enemy";
  else if (type == STABBING)   return "stab enemy";

  return 0;
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != BARB_SUB)
        return shadow_who->show_subloc(subloc, me, for_obj);

    if (for_obj == me)
        str = "You smell ";
    else
        str = capitalize(me->query_pronoun())+" smells ";

    str += "like a true Barbarian.\n";

    if (me->query_skill(BARB_SCORE)>40)
    {
      if (for_obj == me)
          str += "You are ";
      else
          str += capitalize(me->query_pronoun()) + " is ";

      str += "a barbarian guild wizard.\n";
    }

    return str;
}

/*
 * Function name: query_guild_style_occ
 * Description:   Get the style of this guild
 * Returns:       String describing guild style
 */
string
query_guild_style_occ()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_occ
 * Description:   Get the name of this guild
 * Returns:       String naming guild
 */
string
query_guild_name_occ()
{
    return GUILD_NAME;
}
