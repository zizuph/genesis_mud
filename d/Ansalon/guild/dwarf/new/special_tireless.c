/*
 * Neidar Tireless
 * 
 * Neidar never run out of fatigue while actively in combat.
 *
 * Petros Nov 2008
 *
 */
 
#pragma strict_types 

/**
 * Always return a value if we're actively in combat.
 */
public int
query_fatigue()
{
   int fatigue_value, max_fatigue;
   fatigue_value = shadow_who->query_fatigue(); 
   if (!shadow_who->query_attack())
   {
       // Tireless ability only works when in combat
       return fatigue_value;
   }

   max_fatigue = shadow_who->query_max_fatigue();

   return max(fatigue_value, max_fatigue / 4);   
}

