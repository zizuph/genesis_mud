
/* 
   Warning signal object for Calian guild, lets Calians know when 
   guild is under attack.

   Coded by Maniac.

   History:
           10/6/96      Corrected                     Maniac
           28.4.95         Created                    Maniac
*/

#include "/d/Calia/glykron/palace/specials/calian.h"

#define MINIMUM_TIME_DIFFERENCE 70 

/* Last attack time mapping for each Calian npc */ 
mapping last_attack = ([ ]); 

int
is_calian(object living)
{
    return living->query_guild_name_occ() == GUILD_NAME;
}


void
warn_calians(string npc_name, string message)
{
    int i;
    object *list = users();
    string s = (npc_name + " projects a thought to you:\n" +
                message + "\n");

    for (i = 0; i < sizeof(list); i++) 
        if (is_calian(list[i]) &&
            present("Calia_medallion", list[i]) &&
            !(list[i]->query_wiz_level())) 
           list[i]->catch_msg(s);
}


void
another_attack(string npc_name, string message)
{
   int tmp;

   tmp = time();
   if ((tmp - last_attack[npc_name]) >= MINIMUM_TIME_DIFFERENCE) {
      warn_calians(npc_name, message); 
      last_attack = m_delete(last_attack, npc_name); 
      last_attack += ([npc_name : tmp]);
   }
}

