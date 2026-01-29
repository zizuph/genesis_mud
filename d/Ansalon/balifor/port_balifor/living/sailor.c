/* Navarre 24th June 2006,
 * Changed the acts of this sailor
 * he was talking to william even if
 * william is dead. Same with the draconians.
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit AM_FILE

void
create_krynn_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("sailor");
   set_short("drunken sailor");
   set_long("This man is, like most sailors here in Balifor "+
      "out of work. Only the dragonarmy ships are "+
      "permitted to enter or leave the Bay of Balifor "+
      "now. Many of the sailors, instead of catering "+
      "to the dragonarmies, have just given up their "+
      "profession. \n");
   set_stats(({50,65,60,35,35,50}));
   
   set_skill(SS_UNARM_COMBAT, 70);
   set_skill(SS_DEFENCE, 50);
   
   set_alignment(300);
   set_knight_prestige(-80);
   
   set_act_time(0);
   add_act("hiccup");
   add_act("burp");
   add_act("say Another brandy!");
   add_act("emote tells a joke, hoping to draw laughter from "+
      "the crowd.");
   add_act("emote drinks his brandy in one long gulp.");
   add_act("say I really hate draconians.");
}
