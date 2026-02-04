/* File         : /d/Terel/silver_new/npc/nastya.c
 * Creator      : Pasqua	
 * Date         : April 2000         
 * Purpose      : Nastya the Evilminded
 * Related Files: 
 * Comments     : 
 * Modifications:
 */

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"	

inherit STDMONSTER;

#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

public void 
create_monster()
{
    ::create_monster();
    set_name("nastya");
    set_adj("twisted");
    set_adj("evil-minded");
    set_race_name("goblin");
    set_long("This sick, twisted, dark and evil goblin, who loves to torture animals " +
             "and people for the fun of it lives here in the Silver forest. She could " +
             "be described as having an air of danger and evil about her. By the first " +
             "glance she gives the impression that she's impossible to overcome. Still," +
             "with luck, it should be possible to defeat her.\n");


    set_stats(({130, 150, 120, 200 + random(50), 120 + random(30), 120 + random(20)}));
    set_alignment(-1000);
    set_gender(1);

    heal_hp(query_max_hp());

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

    set_act_time(20 + random(5));
    add_act("emote studies the forest, in search of something to torture.");
    add_act(({"say Where's those animals?", "peer", "laugh evil"}));
    add_act(({"say I just love to blind those birds and squirrels.",
	"laugh evil", "say And then send them into the cockatrice pit."}));		
    add_act("say That Regata is so damn weak!");
    add_act("laugh sarc");
}

public void
do_sequence(mixed *seq)
{
    command(seq[0]);

    seq -= ({ seq[0] });

    if (sizeof(seq))
    {
	float ival = 2.0;

	if (floatp(seq[0]))
	{
	    ival = seq[0];
	    seq -= ({ seq[0] });
	}

	if (sizeof(seq))
	    set_alarm(ival, 0.0, &do_sequence(seq));
    }
}

public void
be_mean(object who)
{
    /* critter or we have moved */
    if (!present(who, environment()))
	return;

    switch(who->query_race_name())
    {
    case "falcon":
	do_sequence(({ "chuckle",
	    "say With such wings that bend and curve allowing for perfect flight.",
	    "say A beak so sharp like a blade's edge with ease cuts through the night.",
	    "say With talons that pierce even the toughest and rawest hides.",
	    "say A majestic creature so rare it's scarcely seen far and wide.",
	    "say to "+ OB_NAME(who) +" But Now I Have To End Your Life!",
	}));
	break;

    case "bear":
    case "bearcub":
    default:
	do_sequence(({ "emote licks her lips readily!",
	    1.0, "kill "+ OB_NAME(who),
	}));
	break;
    }
}

public void
init_living(void)
{
    ::init_living();

    /* creatures are not humanoid */
    if (!this_player()->query_humanoid())
	set_alarm(1.5, 0.0, &be_mean(this_player()));
}

