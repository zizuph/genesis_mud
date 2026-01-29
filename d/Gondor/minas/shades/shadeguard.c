/*
 *	/d/Gondor/minas/shades/shadeguard.c
 * 
 *	A strong Shade guarding the quarters... 
 *
 *	Modification log:
 *	20-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

static int fight_intruder(object pl);
static int is_smuggler(object pl);

public void
create_gondor_monster()
{
    set_name(({"thief","fellow","man","guard"}));
    set_race_name("human");
    set_short("dark-robed guard of the Shades");
    set_long(BSN("This man is clad in black clothes, and he watches " +
		 "your every move. His hand is resting on the hilt " +
		 "of a dagger in his belt.") + 
	     "You assume he is a guard.\n");
    default_config_npc(80);
    set_skill(SS_WEP_KNIFE, 85);
    set_skill(SS_DEFENCE,   65);
    set_skill(SS_PARRY,     65);
    set_skill(SS_AWARENESS, 35);
    set_skill(SS_BLIND_COMBAT, 55);
    set_alignment(-200 - random(101));
    set_chat_time(10);
    add_chat("Business is bad here in Minas Tirith now because of all the guards.");
    add_chat("Don't hang around too long, ok?");
    add_chat("Power will be with the Shades!");
    set_cchat_time(7);
    add_cchat("You won't beat the Shades!");
    add_cchat("Hey, stop it! What have I ever done to hurt you??");
    add_cchat("Help! I'm innocent!");
    add_cchat("I didn't do it! Nobody saw me! Can't prove anything!");
    add_cchat("Leave me alone! I'm a peaceful man!");

    set_equipment( ({ SHADES_DIR + "obj/poisoned_dagger", 
		      SHADES_DIR + "obj/ablackcloak",
		      SHADES_DIR + "obj/atunic",
		      SHADES_DIR + "obj/atrousers", 
		  }) );
}

public void
init_attack()
{
    if (!is_smuggler(TP)) 
    {
	set_alarm(3.0, 0.0, &fight_intruder(TP));
	return;
    }
}

static int
fight_intruder(object pl)
{
    command("shout A spy from the cityguards!  Alert!");
    command("kill "+pl->query_real_name());
    return 1;
}

static int
is_smuggler(object pl)
{
    if (!objectp(pl)) 
	return 1;
    if (pl->query_prop("_gondor_quest_is_smuggler")) 
	return 1;
    if (pl->test_bit("Gondor", GONDOR_GROUP, HERB_SMUGGLER_BIT))
	return 1;
    return 0;
}

public int query_knight_prestige() { return 300; }
