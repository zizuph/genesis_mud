/* Tinne - a sick novice - a "prop" for a tour
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           6/21/98     Created
** Tapakah        08/2021     Refactored
*/

#include <stdproperties.h>

#include "defs.h"

inherit  SR_NPC+"knovice";

#define  VEST (({"robe","cincture","tonsure"}))

void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  set_name("tinne");
  string *adj = query_adj(1); // 1 means return list of all adjectives
  add_adj("sick");
  set_short("sick "+adj[0]+" novishagh");
  set_long("He is a "+adj[0]+" "+adj[1]+" "+(query_race_name())+", his habit "+
           "identifying him as a novice member of the Order of Sean-Rhian. "+
           "He looks rather sick.\n");
  add_prop(NPC_I_NO_LOOKS, 1);
  add_prop(NPC_M_NO_ACCEPT_GIVE,1);
  clear_act();
  set_act_time(30);
  add_act("emote mumbles a silent prayer.");
  add_act("emote puts his hands together prayerfully.");
  add_act("emote bows his head sickly.");
  add_act("cough");
  add_act("sneeze");
  add_act("cough");
  add_act("hiccup");
  add_act("cough");
  add_act("moan");

  set_alarm(0.1,0.0, &heal_hp(-(query_max_hp() / 3)));

}

void
heal_hp(int hp)
{
  if (environment() && hp > 0)
    return;

  ::heal_hp(hp);
}
