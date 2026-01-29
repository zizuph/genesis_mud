/* Ogre for the Encampments by Crystalmir Lake
 * Splunge, 1/12/94
 * 
 *  The easiest monster in Crystalmir so far
 *  But he is somewhat amusing...:)
 *
 */

#include "/d/Krynn/solace/lake/local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit M_FILE


void
create_krynn_monster()
{
   
    NEVERKNOWN;

    set_name("ogre");
    set_adj("dumb");
    set_race_name("ogre");
    set_adj("hulking");
    set_long("This nasty looking pile of hair is about the " +
	     "stupidest looking creature you have ever seen. " +
	     "But what he lacks in smarts, he certainly makes " +
	     "up for in strength.\n");

    set_stats(({120,75,175,10,10,100}));
    set_skill(SS_DEFENCE, 45);
    set_skill(SS_WEP_CLUB, 60);

    ALIGN_ME
    PRESTIGE_ME

    set_act_time(5);
    add_act("emote grunts obnoxiously.");
    add_act("say Me kill you with club!");
    add_act("snort");
    add_act("say Yeah, yeah, I will kill anything dat make me mad...");
    add_act("grunt");
    add_act("say Me hit you over da head with me club...");
    add_act("say Fish! Bone! Club!");

    set_alarm(2.0,0.0,"arm_me");
}

arm_me()
{
    object wep;
    seteuid(getuid(this_object()));
    wep=clone_object("/d/Krynn/solace/lake/obj/ogre_club.c");
    wep->move(this_object());
    command("wield weapon");
    command("emote looks at his club with nothing short of utter joy.\n");
}
