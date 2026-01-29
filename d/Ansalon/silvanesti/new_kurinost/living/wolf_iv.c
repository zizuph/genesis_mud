/*
 * wolf_iv.c
 *
 * The dangerous attacking wolf in the muddy pit of the draconian camp.
 *
 * Copyright (C): Kellon, september 2012
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

/* Inherit the Krynn creature */
inherit C_FILE

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  1
#define A_CLAWS 2

#define H_HEAD 1
#define H_BODY 2
#define H_LEGS 4

// G L O B A L   V A R S
object gWolf;

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_creature
 *  Arguments: None
 *  Returns  : None
 * 
 *  Creates the wolf.
 *
 */
public void
create_creature()
{
    set_name("wolf");
    set_long("A pair of gleaming red eyes glare dangerously at " +
      "you from the shadows. As you approach the pile of rubble, " +
      "this large muscular wolf quickly rises from it's den and " +
      "bares it's huge white fangs at you in a vicious snarl. " +
      "Muscles ripple beneath it’s brown fur as it seems to " +
      "position itself between you and something in the pile of " +
      "garbage. Rising about 110 cm from the ground, the wolf is " +
      "powerful and broad and the fur is short and well tended.\n");

    set_race_name("wolf");
    add_adj("angry");
    add_adj("brown");
    add_name("iv");

    add_prop(CONT_I_HEIGHT, 110);
    add_prop(CONT_I_WEIGHT, 140000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    /*
	remove_prop(NPC_M_NO_ACCEPT_GIVE);
    */

    set_stats(({ 85, 80, 90, 10, 10, 90}));

    set_alignment(-250);
    set_knight_prestige(10);

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 60 + random(10));
    set_skill(SS_AWARENESS, 45);

    set_attack_unarmed(A_BITE, 30, 30, W_IMPALE, 75, "bite");
    set_attack_unarmed(A_CLAWS, 25, 25, W_SLASH, 25, "front legs");

    set_hitloc_unarmed(H_HEAD, 30, 30, "head");
    set_hitloc_unarmed(H_BODY, 40, 55, "body");
    set_hitloc_unarmed(H_LEGS, 25, 15, "legs");
}


/*
 *  FUNCTION : delay_drop
 *  Arguments: what - item that was given to the wolf.
 *  Returns  : void
 * 
 *  What to do if you give the wolf something.
 *
 */
public void delay_drop(object what)
{
    command("emote sniffs at the " + what->query_short() + ".");
    command("drop " + what->query_short());
}


/*
 *  FUNCTION : delay_run_off
 *  Arguments:
 *  Returns  :
 * 
 *  The wolf runs off with the bone.
 *
 */
public void delay_run_off(object what)
{
    string cmd = "emote howls with fury and takes off after the " +
    "angry brown wolf, trying to snatch the bone away from it!";
    command("emote growls at you!");
    command("emote runs off with the bone.");
    gWolf->command(cmd);

    gWolf->remove_object();
    what->remove_object();
    TO->remove_object();
}


/*
 *  FUNCTION : set_brother
 *  Arguments: object - the other wolf.
 *  Returns  : Void
 * 
 *  Let us know the object of the other wolf.
 *
 */
public void
set_brother(object wolf)
{
    gWolf = wolf;
}


/*
 *  FUNCTION : brother_died
 *  Arguments:
 *  Returns  :
 * 
 *  React to someone killing the other wolf, Iv.
 *
 *
public void
brother_died(object killer)
{
    killer->catch_msg();
    tell_room(({ TO, killer }), QTNAME(TO) + " howls in fury and throws itself viciously at " + QCTNAME(killer) + "!\n", 0);
    command("kill " + QTNAME(killer));
}
*/

/*
 *  FUNCTION : enter_inv
 *  Arguments: what - what was given to me
 *             from - who gave it to me.
 *  Returns  : void
 * 
 *  If you give something to the wolf, this is where we handle it.
 *
 */
/*
public void enter_inv(object what, object from)
{
    ::enter_inv(what, from);

    write("You gave me something!\nIt's a " + what->query_short() + ".\n");

    if (what->id(DC_BONENAME))
    {
	write("Lets run off with it!\n");
	set_alarm(2.0, 0.0, &delay_run_off(what));
    }
    else
    {
	write("Lets just drop it.\n");
	set_alarm(2.0, 0.0, &delay_drop(what));
    }
}
*/
