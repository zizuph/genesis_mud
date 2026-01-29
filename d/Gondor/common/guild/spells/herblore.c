/*  
 */

#pragma save_binary

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include "/d/Gondor/common/guild/spells/rparse.h"
#include "/d/Gondor/defs.h"

#define MANA_LIMIT      15 /* How much mana does it cost to cast this spell? */
#define CAST_LIMIT      10 /* How wise and skilled must the caster be? */
#define SPELL_DIR	"/d/Gondor/common/guild/spells/" /* Where is our spell dir? */
object is_herb(string str);

/* Function name: Herblore
 * Description:   Will give the player a better chance to identify a herb.
 *                      On success, it gives the id_long description of the herb.
 * Arguments:     the herb to identify
 *                
 */
nomask mixed
do_herblore_spell(string str)
{
    object room, herb;
    int success;
    if (RNMAGIC(room)) /* Checks if prop ROOM_I_NO_MAGIC is set. */
        return "Some strange power in this place prevents you from casting the spell.\n";

    if (this_player()->query_mana() < MANA_LIMIT)
        return "You feel too weak to cast this spell.\n";

    this_player()->add_mana(-MANA_LIMIT);

    if (random(this_player()->query_stat(SS_WIS) +
        	this_player()->query_stat(SS_SPELLCRAFT)) < random(CAST_LIMIT))
        return "Something breaks your concentration, and the spell fails!\n";
    if (!(herb = is_herb(lower_case(str)))) return "Too late you remember that you should have cast\n"+
	"the spell on a herb! Now you have spent mana on naught.\n";
    write("You concentrate for a while, praying for Yavanna to help identify your herb.\n");
    say(QCTNAME(this_player()) + " gestures a little, while mumbling something.\n",TP);
    success = (TP->query_skill(SS_SPELLCRAFT) + TP->query_skill(SS_HERBALISM) +
          TP->query_skill(SS_FORM_DIVINATION) + random(TP->query_stat(SS_WIS))/2 
          - herb->query_id_diff());
    if (success > 0) {
      write("Suddenly you feel enlightened:\n");
      write(herb->query_id_long());
      return 1;
      }
    TP->catch_msg("You feel just as wise as before.\n");
    return 1;
}

/* Function name:
 * Description:
 * Arguments:
 * Returns:
 */

object
is_herb(string str)
{
  object *ob;
  int n;
  if (!str) return 0;
  ob = parse_this(str, "%l");
  if (!sizeof(ob)) return 0;
  while (n < sizeof(ob)) {
     if (function_exists("create_herb",ob[n]))
       return ob[n];
     n++;
     }
  return 0;
}
