/* The Octopus (Creature) - Coded 18/09/95, Tulix III                     */
/* Cloned by cave /d/Emerald/cave/well/water6f.c                          */
/* This octopus is required for the Emerald pearl quest.                  */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Emerald/tulix/t_defs.h"
#include "/d/Emerald/mountains/mtblack/cave/pearl_defs.h"

/* Define initial attacks and all hitloc ids. Six tentacles to fight with. */
#define A_TENT1 0
#define A_TENT2 1
#define A_TENT3 2
#define A_TENT4 3
#define A_TENT5 4
#define A_TENT6 5

#define H_HEAD 0
#define H_BODY 1
#define H_TENT 2

/* Prototype functions */
public int apply_ointment(object player);
public void metamorphosis(object player);
public void give_reward(object player);
public void swim_away();


public void
create_creature()
{
    set_name("artolmeus"); 
    set_race_name("octopus");
    set_short("large octopus");
    set_adj(({"large", "miserable" }));
    set_long("This is a large octopus (roughly human size), and is not " +
	    "really the kind of creature you would expect to find here. " +
	    "You get the impression that he is quite miserable.\n" +
	    "He appears to be holding something round with his back two " +
	    "tentacles.\n"  +
            "He is wearing the medal of the Solamnian Knighthood, " +
            "and he is a Lord Warrior.\n");

    /*           str, dex, con, int, wis, dis */
    set_stats(({ 190, 180, 160, 100, 100, 120 }));
    set_alignment(1200);   /* Most tough Knights have high alignments */
    refresh_mobile();

    set_skill(SS_DEFENCE, 150);
    set_skill(SS_SWIM, 100);

    set_attack_unarmed(A_TENT1, 30, 50, W_BLUDGEON, 90, "first tentacle");
    set_attack_unarmed(A_TENT2, 30, 50, W_BLUDGEON, 90, "second tentacle");
    set_attack_unarmed(A_TENT3, 30, 50, W_BLUDGEON, 90, "third tentacle");
    set_attack_unarmed(A_TENT4, 30, 50, W_BLUDGEON, 90, "fourth tentacle");
    set_attack_unarmed(A_TENT5, 30, 50, W_BLUDGEON, 90, "fifth tentacle");
    set_attack_unarmed(A_TENT6, 30, 50, W_BLUDGEON, 90, "sixth tentacle");
    
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_hitloc_unarmed(H_TENT, ({ 10, 15, 30, 20 }), 80, "tentacles");

    add_prop(MAGIC_I_BREATH_WATER, 100);
    add_prop(LIVE_I_QUICKNESS, 300);

    setuid();
    seteuid(getuid());

}

public int
special_attack(object enemy)
{
    object me;

    me = this_object();
    
    if (me->query_hp() <= (me->query_max_hp() * 2 / 3) )
    {
        ENV(TO)->set_reset_alarm();
	tell_room( ENV(TO), "The large octopus disappears in a cloud " +
	    "of ink.\n");
	TO->remove_object();          /* Not very sporting... */
    }

    return 0;
}

public int
apply_ointment(object player)
{
    tell_room( ENV(TO), "The large octopus starts to shake violently!\n");
    set_alarm( 4.0, 0.0, &metamorphosis(player) );

    return 1;
}
    
public void
metamorphosis(object player)
{
    tell_room( ENV(TO), "The large octopus suddenly undergoes a rapid " +
	"metamorphosis!\nSome of its tentacles wither away to nothing, " +
	"while four of them transform into the familiar forms of arms and " +
	"legs.\nIn fact, the large octopus now looks almost human....\n");

    set_long("This octopus does not look anything like an octopus. " +
	    "In fact, it looks more like a human! " +
	    "You get the impression that he is not quite as miserable " +
	    "as he was a few moments ago.\n" +
	    "He appears to be holding something round with his back two " +
	    "tentacles.\n"  +
            "He is wearing the medal of the Solamnian Knighthood, " +
            "and he is a Lord Warrior.\n");

    set_alarm( 8.0, 0.0, &give_reward(player) );

    return;
}

public void
give_reward(object player)
{
    object pearl;

    /* This monster will return in 10 minutes time. */
    ENV(TO)->set_reset_alarm();

    /* Has the player completing the quest foolishly left the room? */
    if (member_array( player, all_inventory( ENV(TO) ) ) == -1)
    {
	tell_room( ENV(TO), "The large octopus finishes its transformation " +
	    "into human form. Suddenly realising that he can no longer " +
	    "breathe the water, he makes a speedy departure for the fresh " +
	    "air in the caves.\nBefore he leaves, he mouths the phrase " +
	    "'free at last!'.\n");
	
	return;
    }
    
    tell_room( ENV(TO), "The large octopus completes its transformation " +
	"into human form. Suddenly realising that he can no longer " +
	"breathe the water, he decides on a speedy departure for the air " +
	"in the caves.\nHe winks, and mouths the phrase 'thank you!', " +
	"and so grateful that he gives what he was " +
	"carrying to his rescuer.\n");
    
    pearl = clone_object(PEARL);
    pearl -> move(player);

    player->catch_msg("The large octopus (oops!), rather, the human knight " + 
	"that you just freed gives you a pearl as a reward.\n");

    set_alarm( 2.0, 0.0, swim_away );

    if (player->test_bit( "emerald", PEARL_BIT[0], PEARL_BIT[1] ))
    {
	return;
    }
    else
    {
	if (player->query_exp() > (PEARL_QUEST_XP * 7) )
	{
	    player->set_bit(PEARL_BIT[0], PEARL_BIT[1]);
	    player->add_exp(PEARL_QUEST_XP);
    
	    player->catch_msg("You also get the pleasant feeling of being " + 
		"more experienced.\n");
	}
	else
	{
	    player->catch_msg("If you were bigger, you would have felt " + 
		"a bit more experienced.\n");
	}
	/* Honestly, if you've managed to do the quest, you'll get the xp! */
    }

    return;
}

public void
swim_away()
{
    tell_room( ENV(TO), "The human knight swims away.\nYou assume he will " +
	"think twice before attacking goblins in future.\n");

    TO->remove_object();
}
