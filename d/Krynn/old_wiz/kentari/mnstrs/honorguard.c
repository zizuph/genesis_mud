/* Tunnel Honor guards for the Museum and Tomb in the Spur
 * -Kentari 12/96
 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/guild/guild.h"
#include "/d/Krynn/solamn/guild/local.h"
#include <macros.h>

inherit "/d/Krynn/common/monster/knight_base";

#define OUTKEEP    VDIR + "outkeep"

int i_am_alarmed = 0;
int cloned;

void
create_knight_npc()
{
	int i;
	set_name("ronin");
	add_name("guard");
	add_name("honor-guard");
	add_name("sentinel");
	set_living_name("ronin");
	set_title("Dragonbane, Honor-Guard of the Solamnian Knights");
	set_gender(0);
	set_introduce(1);
	set_short("knight honor-guard");
	set_long("This is an honor-guard on duty, silently watching " +
		"over the sacred rooms of the Knighthood. He looks " +
		"to be very vigilant as he serves as a Sentinel of " +
		"Honor.\n");
	set_alignment(1100);
	set_knight_prestige(-1200);
	add_prop(OBJ_I_WEIGHT, 2);
	add_prop(OBJ_I_INVIS, 1);
	add_prop(LIVE_I_SEE_INVIS, 1);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
        add_prop(NPC_I_NO_LOOKS, 1);
	add_prop(CONT_I_HEIGHT, 190);
        add_prop(CONT_I_WEIGHT, 70100);
	for (i = 0; i < 6; i++)
		set_base_stat(i, 90 + random(10));
        set_stat_extra(2, 55);
        set_all_attack_unarmed(75, 75);
        set_all_hitloc_unarmed(75);
        set_skill(SS_DEFENCE, 90 + random(10));
        add_cact("@@do_heal");
	set_alarm(2.0, 0.0,"enter_tunnel");	
}

void
do_heal()
{
      command("smile joy");
      TO->heal_hp(150+random(50));
}

public void
attacked_by(object ob)
{
   ::attacked_by(ob);
   command("emote prays to Paladine for the strength to overcome and defeat " +
	"this new enemy.\n");
}  

void
enter_tunnel()
{
	command("emote emerges from the shadows as your presence is noted");
	command("introduce myself");
	command("bow humbly");
	command("say Please forgive my watchful silence, I am on duty");
	command("emote melts back into the deep shadows and resumes his post");
}
