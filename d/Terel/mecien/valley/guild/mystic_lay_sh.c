/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * Mystic guild lay shadow
 */
inherit "/std/guild/guild_lay_sh";

#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define ENV environment

query_not_attack_me(object who, int aid){

object watcher;
object me = query_shadow_who();
object weapon = who->query_weapon(aid);

  watcher = present("divine_watcher", me);
  if(!watcher) return 0;
  if(watcher){
   if(random(100) < 10){
      who->catch_msg("A shadowy hand appears from a mist about " + QCTNAME(me) + 
      " and wards off your attack.\n");
   me->catch_msg("A powerful spirit wards off the attack of " + QCTNAME(who) + ".\n");
   return 1;
   }
    tell_room(ENV(me), "Mysterious shadows writhe about " + QCTNAME(me) + 
   ", enshrouding " + me->query_objective() + " in a dreadful glory.\n", me);
   }
  if(random(100) > 95){
   set_alarmv(4.0, -1.0, "voices", ({ me, who, aid }));
   if(!weapon) return 0;
   who->catch_msg("Your " + weapon->query_short() + " strikes against some mysterious power!\n");
  return 1;
  }

}

voices(object me, object who, int aid){
  tell_room(ENV(who), "Someone says: I am a Watcher of the Twelve, " + QCTNAME(who) + ", my powers protect " + QCTNAME(me) + "\n");
   who->add_panic(100);
}


/*
 * Function name: query_guild_tax_lay
 * Description:   What is the tax to pay at this guild?
 * Returns:       The guild tax for this guild
 */
public int
query_guild_tax_lay() { return LAY_TAX; }

/*
 * Function name: query_guild_style_lay
 * Description:   What style is this guild?
 * Returns:       string - holding the style of guild
 */
public string
query_guild_style_lay() { return LAY_STYLE; }

/*
 * Function name: query_guild_name_lay
 * Description:   Returns the name of the guild this shadow represents
 * Returns:  The name of the guild
 */
public string
query_guild_name_lay() { return LAY_NAME; }

/*
 * Function name: query_guild_title_lay
 * Description:
 * Returns:
 */
public string
query_guild_title_lay()
{
   int office;
   object who = query_shadow_who();
   string title = "";
   
   office = who->query_mystic_office();
   if (office <= 0 || office > sizeof(OFFICES)) return "";
   
   if (office == OFFICE_NOVICES) {
       if (who->query_gender() == 1)
           title = "Mistress";
       else
           title = "Master";
   }
   title += OFFICE_TITLE[office-1];
   
   return title;
}


/*
int
wear_arm(object what)
{
   object who = query_shadow_who();
   
   if (what->query_prop(MYSTIC_ARMOUR) < 1) {
      who->catch_msg("You feel more distant from the spirits.\n");
      who->set_piety((who->query_piety() - 1));
   }
   return who->wear_arm(what);
}
*/

