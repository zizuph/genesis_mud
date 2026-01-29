#pragma strict_types
// name: Amyras   /d/Avenir/common/ships/sparkle/amyras.c
// creator(s):   Tepisch  DEC 1994
// purpose:      Guardian of Staek, Capt. of the Melancholy
// last update:  Boriska, Mar 22, special attack fixes, code cleanup
//
// * Sirra Oct 2002: made gender neutral as requested by player
// * Lucius May 2009: Cleanups.
//
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

#define POS "its"

private string *randadj = ({
	"three-headed", "half-serpent", "flaming", "winged", "monstrous"
}); 
private string *randrace = ({
    "tempest", "elemental", "djinn", "guardian", "spirit"
}); 
private string *randlong = ({
    "Nothing could have prepared you for the wrath of this Being.\n"+
	"It would seem to be a powerful ally to the captain.\n",
    "You stare in stupification at this wrathful creature, aware only "+
	"of a desire to flee.\nYou get the feeling that fighting it "+
	"may not be a good idea.\n",
    "The stench of sulfur emanates from it, reminding you of "+
	"rotten eggs.\nIts barbed tail looks like it will do "+
	"serious damage.\n",
    "It ripples and shifts before your eyes, not quite solid.\n"+
	"Certainly it is not of this mortal plane of existence.\n"
});

public void
help_staek(object staek)
{
    if (!staek)
	return;

    foreach(object foe : staek->query_enemy(-1))
    {
	if (environment(foe) == environment(staek))
	    command("$kill "+ OB_NAME(foe));
    }
}

public void
create_creature(void)
{
    set_name("amyras");
    set_title("Soultaker");
    set_race_name(one_of_list(randrace));
    set_long(one_of_list(randlong));
    set_adj(one_of_list(randadj));
    set_gender(2); //Gender is neutral.

    set_stats(({ 100+random(20), 100+random(20), 100+random(20),
	100+random(10), 100+random(10), 100+random(10) }));

    set_alignment(-500);

    set_attack_unarmed(1, 30, 28, W_SLASH,  50, "left claw");
    set_attack_unarmed(2, 25, 40, W_IMPALE, 50, "razor-sharp teeth");
    set_attack_unarmed(4, 35, 28, W_BLUDGEON , 50, "right claw");
    set_attack_unarmed(8, 25, 27, W_BLUDGEON, 50, "barbed tail");

    set_hitloc_unarmed(1, 60, 10, "torso");
    set_hitloc_unarmed(2, 20, 10, "left leg");
    set_hitloc_unarmed(4, 60, 10, "abdomen");
    set_hitloc_unarmed(8, 20, 10, "right leg");
    set_hitloc_unarmed(16,20, 10, "tail");

    set_skill(SS_DEFENCE, 90);
    set_skill(SS_UNARM_COMBAT, 90);

    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop(MAGIC_I_RES_FIRE, 100);
    add_prop(MAGIC_I_RES_DEATH, 50);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_act_time(5);
    add_act("smile cruel");

    set_cact_time(1);
    add_cact("emote tries to scratch your face with "+POS+" claws.");
    add_cact(({"emote booms: Kneel and I will have mercy upon you...",
	"emote booms: Thou shalt die quickly by decapitation, rather "+
	"than slowly at the hands of my brethren."}));
    add_cact("cackle joy");
    add_cact("emote booms: Death is meaningless! Kill this body, and "+
      "I will conjure another!");
    add_cact(({"emote booms: Leave now, young Infidel.", "emote booms: "+
	"Cease this sacriledge at once!"}));
    add_cact(({"emote booms: I've other forms I'm eager to try. Quickly!",
	"Quickly now! Kill this body. I will shed it for another!"}));
}

public int
query_knight_prestige(void)	{ return 100; }

public int
special_attack(object victim)
{
    /* normal attack */
    if (random(3))
	return 0;

    switch(random(2))
    {
    case 0:
	victim->catch_msg(QCTNAME(this_object()) +
	  " tears at you with with "+POS+" ichor-stained claws!\n");
	tell_watcher(QCTNAME(this_object()) + 
	  " tears into " + QCTNAME(victim) +
	  " with "+POS+" ichor-stained claws!\n", victim);
	victim->heal_hp(-70);
	command("bounce maniac"); 
	break;
    case 1:
	victim->catch_msg( QCTNAME(this_object()) +
	  " grazes your back with "+POS+" barbed tail!\n");
	tell_watcher(QCTNAME(this_object())+ " grazes " + QCTNAME(victim) +
	  "'s back with "+POS+" barbed tail!\n", victim);
	victim->heal_hp(-80);
	command("cackle loud");
    }
    return 1;
}
