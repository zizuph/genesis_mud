// file name: /d/Avenir/common/dead/obj/spectral_war_fan.c
// creator(s): Lilith & Zizuph, Aug 2021  
// purpose:    Spectral Guardian gear + defensive aid
// note:       Based on Japanese War Fans (tessen/gunbai/dansen uchiwa)
//             which were used to evade attacks, ward off arrows and darts
//             like a shield, distract and disarm opponents, signal allies, etc.
//                 When held, has "signal" ability and +defense skill bonus
// updates: 
// todo:     Get Ziz to help with a special ability that "signals"
//           an ally(teammate) that they should "relieve you", which
//           switches enemies to the indicated ally, kind of like
//           a rescue or move behind. Good for squishy players in
//           situations where npcs focus on the little guy.
//           Will have cooldown period.
//
//           If the Balance team objects to "signal" ability for some 
//           reason, then set higher boost to a defensive skill when held.

inherit "/std/object";
inherit "/lib/keep";
inherit "/lib/item_expiration";
#include "../dead.h"
#include "/d/Avenir/include/basic.h"


void
create_object()
{
    set_name("fan");
	set_adj(({"spectral", "war", "glowing"}));
	set_short("spectral war fan");
	set_pshort("spectral war fans");
    set_long("You hold in your hand something rarely seen in this world, "
	    +"the war fan of a spectral guardian. It is not useful as "
		+"a weapon, but when held, it is a defensive aid in combat.\n"
		+"It has a faint spectral-green glow that blurs any further "
		+"details you try to focus on.\n"); 
	add_item(({"glow", "green glow", "spectral glow"}), 
	    "There is an aura of spectral energy surrounding the fan.\n");
    add_prop(OBJ_I_VALUE, 1200);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 500);
 //	add_prop(OBJ_S_WIZINFO,   /*Will fill this in when it is finalized */);
//	add_prop(MAGIC_AM_ID_INFO, ({ /*Will fill this in when it is finalized */})); 
    set_keep(1);
	set_item_expiration();

}

string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
}
 
void
init_recover(string arg)
{
      init_item_expiration_recover(arg);
}

/* Zizuph:

when held do set_skill_extra in defense --- not sure how many levels to boost.

When first holding the fan, give message to player about the signal 
ability: "As you hold the spectral war fan in your hands you realize
that you can use it to <signal teammate> that you need them to 
step in and relieve you of your attacker."

signal, no target: "Signal who that you need to be relieved?"
signal target, not a teammate: "You can only <signal> someone on your team."
signal target teammate: check teammate's health. 
 if their health < 70% // No getting teammates killed.
    "You start to signal to Teammate that you need relief 
   from your attacker(s) but realize their health is getting low, too."
 if teammate health > 70% it succeeds:
   "You signal to Teammate with your spectral war fan that you need
   relief from your attacker(s). Teammate steps in to relieve you, "
   taking on Enemy."
   Target sees: 
   "Actor uses his/her spectral war fan to signal that he/she needs
    relief from his/her attackers. Without further thought you jump in
	between him/her and Enemy."
	<force enemy off of Actor and onto Target.>
   Room sees: 
   "Actor flashes his/her spectral war fan at Target, who steps in 
   between Actor and Enemy."
   
Cooldown period of a minute before the player can use it again?


*/