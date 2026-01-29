/* 
 * This is a spell to preserve herbs from decaying.
 * The success depends on the FORM_TRANSMUTATION skill and the
 * ELEMENT_LIFE skill of the caster.
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

/* Function name: herbpreserve
 * Description:   Will try to preserve one herb from decaying.
 */
nomask mixed
herbpreserve(string str)
{
    object herb;
    int success;
    room = ENV(TP);
    if (RNMAGIC(room)) /* Checks if prop ROOM_I_NO_MAGIC is set. */
        return "Some strange power in this place prevents you from casting the spell.\n";

    if (this_player()->query_mana() < MANA_LIMIT)
        return "You feel too weak to cast this spell.\n";

    this_player()->add_mana(-MANA_LIMIT);
    if (!str) return "You discover you forgot to direct the spell at a herb!\n"+
                "The spell fades into space.\n");
    herb = present(TP,str);
    if (!herb || !function_exists(herb,"create_herb"))
      return "You discover that "+str+" was not a herb!\n");
    if (random(this_player()->query_stat(SS_WIS) +
        	this_player()->query_stat(SS_SPELLCRAFT)) < random(CAST_LIMIT))
        return "Something breaks your concentration, and the spell fails!\n";

    write("You concentrate for a while, praying for Yavanna to preserve your\n"+
               "herb.\n");
    say(QCTNAME(this_player()) + " gestures a little, while mumbling something.\n",TP);
    str = lower_case(str);
    success = (TP->query_skill(SS_SPELLCRAFT) + TP->query_skill(SS_FORM_TRANSMUTATION) +
          TP->query_skill(SS_ELEMENT_LIFE) + random(TP->query_stat(SS_WIS)))*50
          - random(3000);
    if (success < 0) {
      TP->catch_msg("Your spell doesn't seem to work.\n");
      if (!random(10)) herb->decay();
      return 1;
      }
    herb->set_dried();
    TP->catch_msg("The herb glows very briefly, and is suddenly dried.\n");
    return 1;
}

/* Function name:
 * Description:
 * Arguments:
 * Returns:
 */
