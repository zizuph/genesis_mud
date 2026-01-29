/*   Spell: Speedgrowth.   By Elessar, 1994. 
  This is a spell to speed the growth of herbs in a room. This is done by
   lowering or resetting the 'searched' variable in the room, which makes
   finding herbs the more difficult the higher it is.
   The spell will cost lots of mana, to ensure that it will be hard to
   get really many herbs out of one room.
 */

#pragma save_binary

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include <tasks.h>
#include "/d/Gondor/defs.h"
#define SG_SPELL_INGR    ({ "corpse of rat"})
#define SG_MANA_LIMIT      25 /* How much mana does it cost to cast this spell? */
#define SG_CAST_LIMIT      15 /* How wise and skilled must the caster be? */
#define SPELL_DIR	"/d/Gondor/common/guild/spells/" /* Where is our spell dir? */
#define RANGER_HAS_CAST_SPEEDGROWTH   "_ranger_has_cast_speedgrowth"

/* Function name: herbgrowth
 * Description:  Spell will make it easier to find herbs again in a room already searched.
 * Arguments:     none at low levels, higher levels or Gondorian Rangers
 * Returns:       1/0
 */
nomask mixed
do_speedgrow_spell(string str)
{
    object room, *ingr_arr;
    int success, esf_roll, no_ingr, power, is_wiz, fighting;
    room = ENV(TP);
    no_ingr = 0;
    power = TP->query_skill(SS_ELEMENT_LIFE) + 
      TP->query_skill(SS_FORM_CONJURATION);
    if (RNMAGIC(room)) /* Checks if prop ROOM_I_NO_MAGIC is set. */
        return "Some strange power in this place prevents you from casting the spell.\n";
    is_wiz = TP->query_wiz_level();
    if (TP->query_attack()) fighting = 1;
    if (this_player()->query_mana() < SG_MANA_LIMIT)
        return "You feel too weak to cast this spell.\n";
    ingr_arr = find_ingr(SG_SPELL_INGR, TP);
    if (sizeof(ingr_arr) < 1) no_ingr = 1;
    if (random(this_player()->query_stat(SS_WIS) +
        	this_player()->query_stat(SS_SPELLCRAFT)) < random(SG_CAST_LIMIT))
        return "Something breaks your concentration, and the spell fails!\n";
    esf_roll = random(SG_MANA_LIMIT/3 * (1 + no_ingr + fighting));
    if (esf_roll > power)
      {
	esf(esf_roll - power, SG_MANA_LIMIT);
	return 1;
      }
    write("You concentrate for a while, praying for Yavanna to bless this place\n"+
               "with fertile soil for the plants.\n");
    str = lower_case(str);
    if ((success = TP->resolve_task(TASK_ROUTINE,
	({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, SKILL_WEIGHT, 90,
        SKILL_AVG, TS_INT, TS_WIS, SKILL_END,
	     SS_FORM_CONJURATION, SS_ELEMENT_LIFE }))) <= 0)
      {
        TP->catch_msg("Your tongue fails to pronounce the spell, and the prayer goes astray.\n");
	tell_room(room,QCTNAME(TP)+" seems to lose "+POSSESSIVE(TP)+
		  " concentration.\n",TP);
	lose_random_ingr(ingr_arr);
	return 1;
      }
    TP->catch_msg(BSN("You concentrate for a while, praying for Yavanna, "+
      "Vala of Flowers, to bless this place."));
    tell_room(room,BSN(QCTNAME(TP)+" chants an ancient hymn to Yavanna, "+
      "Vala of Flowers, and then touches the ground with "+
		       POSSESSIVE(TP)+"."),TP);
    if (!is_wiz) {
      remove_ingr(ingr_arr);
      TP->add_mana(-SG_MANA_LIMIT);
    }
    if (room->query_searched()==0) {
      write("You feel that the prayer was not needed here though.\n");
      return 1;
    }
    if (room->query_prop(RANGER_HAS_CAST_SPEEDGROWTH)>3) {
      write("You sense that the prayer has no effect in this place anymore.\n");
      return 1;
      }
    room->set_searched(MAX(0,room->query_searched() - 
			   TP->query_skill(SS_ELEMENT_LIFE)/10));
    room->add_prop(RANGER_HAS_CAST_SPEEDGROWTH, 
		   room->query_prop(RANGER_HAS_CAST_SPEEDGROWTH) + 1);
    return 1;
}

/* Function name: 
 * Description:
 * Arguments:
 * Returns:
 */



