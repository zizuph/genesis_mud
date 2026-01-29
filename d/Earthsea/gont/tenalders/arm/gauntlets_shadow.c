/*
 * Ckrik March 2004
 *  Shadow to increase pen of the gauntlet wearer
 *
 */

inherit "/std/shadow";

#include <wa_types.h>

public object gauntlets;


public void set_gauntlets_shadow_owner(object ob)
{
  gauntlets = ob;
}
/***** Changes for combat *****/
public string
cr_attack_desc(int aid)
{
  if (!objectp(gauntlets) || !objectp(gauntlets->query_worn()) ||
      gauntlets->query_worn() != shadow_who)
    {
      shadow_who->query_combat_object()->cb_configure();
      remove_shadow();
      return shadow_who->cr_attack_desc(aid);
    }
  
  /* Humanoids */
  if ((shadow_who->query_combat_file() == 
       "/std/combat/chumlock" ||
       shadow_who->query_combat_file() ==
       "/std/combat/chumanoid"))
    {
      switch(aid)
	{
	case W_RIGHT:
	  return "right jewel-studded black leather gauntlet";
	case W_LEFT:
	  return "left jewel-studded black leather gauntlet";
	default:
	}
    }
  return shadow_who->cr_attack_desc(aid);
}

public mixed
wield(object weapon)
{
  if (!objectp(gauntlets) || !objectp(gauntlets->query_worn()) ||
      gauntlets->query_worn() != shadow_who)
    {
      shadow_who->query_combat_object()->cb_configure();
      remove_shadow();
      return shadow_who->wield(weapon);
    }
  return "The jewels on the jewel-studded black leather gauntlets " +
    "glow and prevent you from wielding the " + weapon->query_short() +
    ".\n";
}
