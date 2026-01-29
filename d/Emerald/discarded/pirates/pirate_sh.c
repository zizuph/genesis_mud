/*                          The Pirate Shadow.                              */


inherit "/std/guild/guild_occ_sh";
#include "defs.h"
#include "/d/Emerald/common/guild/pirates/pirates_defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "guild.h"

/* ************************************************************************
* The Pirates guild titles.
*/


#define PIRATE_RANK_MALE ({ "Cabin Boy", "Yeoman","Deck Seaman" \
      , "Apprentice Seaman", "Seaman","Shipmate","Coxswain's Mate" \
      , "Coxswain","Boatswain's Mate", "Boatswain", "Helmsman" \
      , "Master at Arms","Sail Master","Quartermaster","First Mate" \
      , "Captain" })
#define PIRATE_RANK_FEMALE ({ "Cabin Girl", "Yeoman","Deck Seaman" \
      , "Apprentice Seaman", "Seaman","Shipmate","Coxswain's Mate" \
      , "Coxswain","Boatswain's Mate", "Boatswain", "Helmsman"  \
      , "Master at Arms","Sail Master","Quartermaster","First Mate" \
      , "Captain" })



/* ************************************************************************                  
* Set the tax for the guild.
*/

query_guild_tax_occ()
{
   return GUILD_TAX;
}

/* ************************************************************************
* Do we want this player to join our guild?
*/

query_guild_not_allow_join_occ(player, type, style, name)
{
   if (::query_guild_not_allow_join_occ(player, type, style, name))
      return 1;
   
   return 0;
}


query_guild_keep_player(player)
{
   if (player->query_guild_name_occ())
      {
      write("You are already a member of an occupational guild.\n");
      return 0;
   }
   
   return 1;
}

/* ************************************************************************
* Get the players guild level, based on DEX, INT, SS_OCCUP.
*/

int
query_pirate_level()
{
   return (2*(shadow_who-> query_base_stat(SS_OCCUP)) +
      shadow_who-> query_base_stat(SS_INT)    +
      shadow_who-> query_base_stat(SS_DEX))/25 - 2;
}

/* ************************************************************************
* Give the player a title that is dependent on thier level.
*/

query_guild_title_occ()
{
   int stat;
   string p_title;
   p_title = shadow_who-> query_guild_title_occ();
   /* Wizards keep thier old title. */
   if (shadow_who-> query_wiz_level())
      return p_title;
   stat = query_pirate_level();
   if (stat <= 0)
      stat = 0;
   if (stat >= 15)
      stat = 15;
   if(shadow_who->query_gender() == G_FEMALE)
      {
      if (strlen(p_title))
         return p_title + " and " + PIRATE_RANK_FEMALE[stat] + " of "+
      "the Pirates of el Diablo";
      else
         return  PIRATE_RANK_FEMALE[stat] + " of the Pirates of el Diablo";
   }
   else
      if (strlen(p_title))
      return p_title + " and " + PIRATE_RANK_MALE[stat] + " of "+
   "the Pirates of el Diablo";
   else
      return  PIRATE_RANK_MALE[stat] + " of the Pirates of el Diablo";
}

/* ************************************************************************
* Get the style of the guild.
*/

string
query_guild_style_occ()
{
   return GUILD_STYLE;
}

/* ************************************************************************
* Get the name of the guild. 
*/

string
query_guild_name_occ()
{
   return GUILD_NAME;
}


mixed
query_guild_skill_name(int type)
{
   if(type != 70005)
      return 0;
   return PIRATE_SKILL_DESC[0];
}

int
query_stat(int stat)
{
   int value, v1, v2, m, i;
   
   v1 = shadow_who->query_stat(stat);
   v2 = v1 * 115 / 100;
   m = shadow_who->intoxicated_max() * 8 / 10;
   i  = shadow_who->query_intoxicated();
   
   if(stat == SS_STR || SS_DIS)
      {
      if(i > 0)
         value = (i*i*(v1-v2)/m)/m + 2*i*(v2-v1)/m + v1;
      else
         value = v1 * 9 / 10;
   }
   else
      value = v1;
   return value;
}

string
wield(object wep)
{
   int i, j, k;
   string type, short, *words;
   
   if(!wep->query_wt() == W_SWORD)
      shadow_who->wield(wep);
   else
      {
      short = wep->query_short();
      words = explode(short," ");
      k = 0;
      j = sizeof(words);
      for( i = 0; i < j; i++)
      {
         type = words[i];
         if(type == "rapier" || type == "cutlass")
            k++;
      }
      if(!k)
         {
         return "Something in your pirate blood resists your attempt "+
         "to wield this type of sword.\n";
      }
      else
         return query_shadow_who()->wield(wep);
   }
}

