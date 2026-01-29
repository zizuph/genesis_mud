// This file is from Krynn/open, made by Nick.
// It has the knight prestige functions in it,
// as well as a couple of other nifty functions.
// Use it in *non-humanoid* creatures you want to 
// affect the prestige of Solamnian Knights.
// -/Tepisch         

inherit "/std/creature";
inherit "/std/combat/unarmed";
#include <macros.h>

int prestige; /* The prestige changing variable */

void   add_emote();

/*
 * Function name: create_creature
 * Description:   The standard create, do ::create_creature() to get these
 *                features
 */

create_creature()
{
    if (IS_CLONE)
        set_alarm(2.0, 0.0, add_emote);
    stats_to_acc_exp(); /* Set up correct xp */
    add_fatigue(30000); /* Not tired when starting */
    set_hp(50000); /* Fully healed when starting */
    set_mana(50000); /* Mana also full */
}

/*
 * Function name: emote
 * Description:   Creatures should know how to emote
 * Arguments:     str - string to emote
 * Returns:       1
 */
emote(str)
{
    write("You " + str + "\n");
    say(QCTNAME(this_object()) + " " + str + "\n");
    return 1;
}

/*
 * Function name: add_emote()
 * Description:   obvious
 */
add_emote()
{
    set_this_player(this_object());
    add_action("emote", "emote"); /* A creature must emote ofcourse :) */
}

/*
 * Function name: set_knight_prestige
 * Description:   Set the prestige changing value in the mobile
 * Arguments:     pres - the prestige, if > 0 it will add to the acc, if < 0
 *                       it will add to the stat.
 */
set_knight_prestige(pres) { prestige = pres; }

/*
 * Function name: query_knight_prestige
 * Description:   Return the prestige this monster will affect a knight.
 * Returns:       The prestige.
 */
query_knight_prestige() { return prestige; }



