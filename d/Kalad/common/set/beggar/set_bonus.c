 /*****************************************************************************
*  /d/Kalad/common/set/beggar/set_bonus.c
*
*  set_bonus File for Beggars Set
*
*  Created Oct 20th 2020, Greneth
*
*  Info  : Contains function(s) to check for and apply set bonuses
*          according to properties set in the player. The set items
*          check to see if the set is complete, then call use these
*          to apply the correct bonus based on the set.
*
*  Credit: Mirandus, Shanoga
 *****************************************************************************/

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include <ss_types.h>

 /*****************************************************************************
*  Function name: check_set_bonus
*  Description  : Checks if all pieces are worn and apart of the Beggars Set
 *****************************************************************************/
int
check_set_bonus(object player, string set)
{
    
   int stat, skills, skills2;
    
   if (player->query_prop("_live_i_" + set) == 1)
   {
      if (set == "beggars_set")
      {
			stat = player->query_stat_extra(SS_STR);
			player->set_stat_extra(SS_STR,stat + 10);

			skills = player->query_skill_extra(SS_SNEAK);
			player->set_skill_extra(SS_SNEAK,skills + 25);

			skills2 = player->query_skill_extra(SS_HIDE);
			player->set_skill_extra(SS_HIDE,skills2 + 25);
            
         player->add_prop("_live_i_" + set + "_bonus", 1);
            
         return 1;
      }
   }
   else
   {
      if (set == "beggars_set")
      {
         if (player->query_prop("_live_i_" + set + "_bonus", 1))
         {
			stat = player->query_stat_extra(SS_STR);
			player->set_stat_extra(SS_STR,stat - 10);

			skills = player->query_skill_extra(SS_SNEAK);
			player->set_skill_extra(SS_SNEAK,skills - 25);

			skills2 = player->query_skill_extra(SS_HIDE);
			player->set_skill_extra(SS_HIDE,skills2 - 25);
                
         player->remove_prop("_live_i_" + set + "_bonus");
         }
            
         return 0;
      }
   }
    
}