//  A draggable wounded soldier coded by Morbeche
//  There is a small chance (2 in 20) that the dragger
//  Will be ambushed by a hoarde of Uruks ..Muhahaha!!
//  Copyright Nov 1999
#pragma strict_types

inherit "/d/Gondor/std/monster";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>


int drag_me(string str);
public void hurt_me();
public void i_stay_hurt();


public void
create_gondor_monster()
{
    set_name("soldier");
    add_name(({"gondorian","Gondorian"}));
    set_race_name("human");
    set_short("wounded soldier of Gondor");
    set_pshort("wounded soldiers of Gondor");
    set_adj(({"wounded","dying","Gondorian","gondorian"}));
    set_long(BSN("This is one of the soldiers of Gondor, apparently " +
	"wounded while protecting his land from the armies of the evil one.  " +
	"His face is pale and his hair is matted with blood, he may well have " +
	"fought his last battle.  " +
	""));
    default_config_npc(random(10)+45);
    set_base_stat(SS_CON, random(10)+55);
    set_skill(SS_WEP_SWORD, random(10)+70);
    set_skill(SS_PARRY,85);
    set_skill(SS_DEFENCE,85);
    set_skill(SS_AWARENESS,70);
    set_alignment(150);
    set_chat_time(20);
    add_chat("Looks like the War is over for me.");
    add_chat("What are you hanging around here for?");
    add_chat("I'll never make it back to the city!");
    add_chat("How could I have been foolish enough to fight Him!");
    add_chat("The Enemy is on the move!");
    add_chat("I fear I am beaten by the Evil One.");
    add_chat("Tell my son I am sorry.");
    add_chat("If only someone could drag me to safety.");

    set_equipment( ({ (ARM_DIR + "gchainmail"), (ARM_DIR + "ghelmet"), }) );
    set_alarm(1.0, 950.0,i_stay_hurt);
    arm_me();
    seteuid(getuid());
}

public void
i_stay_hurt()
{

    if (TO->query_hp() > 120)
    {
	TO->set_hp(120);
    }
    return;
}

public void
init_living()
{
    ::init_living();
    add_action(drag_me,"drag");
}


int
drag_me(string str)
{
    mixed *result;
    string dir, Old_m_in, Old_m_out;
    int ran = random(20);

    if (!strlen(str))
    {
	notify_fail("Drag whom?\n");
	return 0;
    }

    notify_fail("Drag whom where?\n");
    if (!parse_command(str, ({ TO }), " %l %w ", result, dir))
	return 0;

    // Did we try to drag this object?
    if (result[result[0]] != this_object())
    {
	return 0;
    }

    // Are we hidden?
    if (TP->query_prop(OBJ_I_HIDE) > 0)
    {
	notify_fail("You cannot drag anyone while hiding!\n");
	return 0;
    }
    // Does the soldier trust us?
    if (TP->query_alignment() < -200)
    {
	notify_fail("The soldier refuses your help, evil one!\n");
	return 0;
    }


    // Is the soldier fighting?
    if (objectp(TO->query_attack()))
    {
	notify_fail("The soldier is engaged in combat!\n");
	return 0;
    }


    // Is dir among the possible exits in this room? 
    if (member_array(dir, environment(TP)->query_exit()) >= 0)
    {

	// Set enter env message.
	Old_m_in = TP->query_m_in();
	Old_m_out = TP->query_m_out();
	TP->set_m_out("drags the wounded Gondorian soldier");
	TP->set_m_in("arrives dragging a wounded Gondorian soldier");

	// Move the player
	this_player()->command(dir);
	write("You drag the wounded soldier with you.\n");

	//Can't sneak while dragging someone!
	TP->reveal_me(1);

	// Remove enter env message.
	TP->set_m_out(Old_m_out);
	TP->set_m_in(Old_m_in);

	// Move the soldier
	this_object()->move(environment(TP));

	// Did we hurt the soldier?
	if (ran > 18)
	{
	    set_alarm(1.0, 0.0, hurt_me);
	}
	return 1;
    }
    return 0;
}

public void
hurt_me()
{
    object Orc1, Orc2, Orc3;

    write("You accidentally injure the Gondorian soldier!\n");
    say(TPQN + " accidentally hurts the Gondorian soldier!\n");
    TO->command("scream");
    tell_room(environment(TO),"The soldier was bait!\n" +
      "It is an ambush by mordor orcs!\n",0,TO);
    Orc1 = clone_object(CAMP_NPC_DIR + "ithil_uruk");
    Orc1->arm_me();
    Orc1->move_living("M", environment(TO));
    Orc1->set_aggressive(1);
    Orc1->command("kill " + TP->query_real_name());
    Orc1->command("kill gondorian soldier");
    Orc1->notify_ob_attacked_me();

    Orc2 = clone_object(CAMP_NPC_DIR + "ithil_uruk");
    Orc2->arm_me();
    Orc2->move_living("M", environment(TO), 0, 1);
    Orc2->set_aggressive(1);
    Orc2->command("kill gondorian soldier");
    Orc2->command("kill " + TP->query_real_name());

    Orc3 = clone_object(CAMP_NPC_DIR + "ithil_soldier");
    Orc3->arm_me();
    Orc3->move_living("M", environment(TO));
    Orc3->set_aggressive(1);
    Orc3->command("kill " + TP->query_real_name());
    Orc3->command("kill gondorian soldier");


    TO->heal_hp(-500);
    TO->command("cry softly");
    TO->do_die(Orc1);
}







