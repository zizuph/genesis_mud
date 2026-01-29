/* This is a very simple spell that adds 1 to the players ability to
 * see in the dark. The duration varies with the success of the casting,
 * and with the players wisdom. The skill in spellcraft is counted in.
 *
 * The formula is: duration = random(wis / 5) + random(skill / 3) + 35
 */

#pragma save_binary

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

#define MANA_LIMIT      10 /* How much mana does it cost to cast this spell? */
#define CAST_LIMIT      20 /* How wise and skilled must the caster be? */
#define SPELL_DIR	"/d/Gondor/common/guild/spells/" /* Where is our spell dir? */

/* Function name: nightvision
 * Description:   Will give the player 1 factor better ability to see in
 *                darkness. It costs equal mana on success or failure,
 *                but might also give even worse ability on failure.
 * Arguments:     none at low levels, higher levels or Gondorian Rangers
 *                may give second person as argument.
 * Returns:       1/0
 */
nomask mixed
nightvision(string str)
{
    object room, lighter;
    int dur;
    if (RNMAGIC(room)) /* Checks if prop ROOM_I_NO_MAGIC is set. */
        return "Some strange power in this place prevents you from casting the spell.\n";

    if (this_player()->query_mana() < MANA_LIMIT)
        return "You feel too weak to cast this spell.\n";

    this_player()->add_mana(-MANA_LIMIT);

    if (random(this_player()->query_stat(SS_WIS) +
        	this_player()->query_stat(SS_SPELLCRAFT)) < random(CAST_LIMIT))
        return "Something breaks your concentration, and the spell fails!\n";

    write("You concentrate for a while, praying for Orome to bless you\n"+
               "with better vision at night.\n");
    say(QCTNAME(this_player()) + " gestures a little, while mumbling something.\n",TP);
    str = lower_case(str);
    dur = (TP->query_skill(SS_SPELLCRAFT) + TP->query_skill(SS_FORM_CONJURATION) +
          TP->query_skill(SS_ELEMENT_LIFE) + random(TP->query_stat(SS_WIS))*50;
    if (!str || str == "myself" || str == "me" ||
    str == TP->query_race_name() || str == TP->query_real_name()) {
           TP->add_prop(LIVE_I_SEE_DARK,TP->query_prop(LIVE_I_SEE_DARK)+1);
           TP->add_prop(RANGER_NIGHTVISION,1);
           call_out("nightvision_end",dur);
           TP->catch_msg("Your eyes feel strange and perceptive.\n");
           say(QCTNAME(TP)+ "'s eyes glows green for a moment; then it passes.\n",TP);
           return 1;
           }
    TP->catch_msg("You feel that you are unable to cast Nightvision on\n"+
                       "anyone else but yourself.\n");
    return 1;
}

/* Function name:
 * Description:
 * Arguments:
 * Returns:
 */
