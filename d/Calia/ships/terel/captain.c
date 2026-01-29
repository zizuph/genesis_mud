/* Captain for the crystalline ship from Gelan to Terel.

   Coded by Maniac & Jaacar, 27/11/95
 */

#pragma save_binary

inherit "/d/Genesis/ship/captain";
#include "ship.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <const.h>

int intro = 0;

object ship;

int
set_ship(object s)
{
	ship = s;
}


void
create_monster()
{
    set_name("ida");
    add_name("_ida_");
    add_name("captain");
    set_race_name("elf");
    set_gender(G_FEMALE);
    add_adj("sea-loving");
    add_adj("graceful");
    set_title("the Farseeing");
    set_stats(({ 80, 80, 80, 65, 82, 120}));
    add_prop(NPC_I_NO_LOOKS,1);
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENSE, 60);
    set_skill(SS_AWARENESS, 100);
    heal_hp(10000);

    set_act_time(6);
    add_act("emote smiles as she looks out to sea, her pastel lips in " +
           "delicate poise.");
    add_act("say This ship will ride any storm, the sea will not harm it.");
    add_act("emote sighs like an ocean wave.");
    add_act("emote gazes out to sea with an intensity in her grey eyes.");
    add_act("emote calmly brushes her hair back as the sea wind catches it.");
    add_act(VBFC_ME("admire")); 

    add_prop(OBJ_M_NO_ATTACK,
             "You sense this woman is under the protection "+
	     "of the Caliana.\n");

    add_prop(OBJ_M_NO_MAGIC_ATTACK, "You are blasted by Caliana!\n");
    set_ticket(TICKET);
    set_price(PRICE);
}

string
admire()
{
    return ("emote proudly admires the " + ship->short() + ".");
}

int
buy(string str)
{
    if (this_player()->query_average_stat() < 20)
    {
	notify_fail("Nahh...little shrimps travel for free! "+
		"You don't need any ticket.\n");
	return 0;
    }

    return ::buy(str);
}

void
add_introduced(string person)
{
    if (!intro)
      intro = set_alarm(2.0,0.0,"introduce_me");
}

void
introduce_me()
{
    command("introduce me");
    intro = 0;
}

