/*
 * A centauress scholar.
 */

#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

#pragma save_binary

inherit "/std/monster";
inherit STRINGLIB;

#define CENTAURESS_NAME ({ "centaur", "centauress", \
			   "widow wormwood", "widow Wormwod", \
                           "wormwood", "Wormwood", \
                           "the widow Wormwood" \
			   })
#define CENTAURESS_DESC \
  "She is elderly, with white hair and tail. Her eyes are pale blue and " + \
  "sharp-sighted, looking out from a tanned, sun-creased face with " +\
  "humour and intelligence. She is dressed in a slightly old-fashioned " +\
  "blouse and bodice, tied around her waist with a brightly patterned "+\
  "kerchief, as her lower body is unclad in the traditional centaur fashion.\n"



create_monster() {
  set_name(CENTAURESS_NAME);
  set_race_name("scholar");
  set_adj(({"centauress", "elderly"}));
  set_long(WRAP(CENTAURESS_DESC));

  set_gender(1);

  set_base_stat(SS_STR, 3);
  set_base_stat(SS_DEX, 5);
  set_base_stat(SS_CON, 4);
  set_base_stat(SS_INT, 3);
  set_base_stat(SS_WIS, 3);
  set_base_stat(SS_DIS, 25);
  set_hp(1000000);    /* Fill it up */

  set_alignment(70);
  set_appearance(65);
  add_prop(NPC_I_NO_LOOKS, 1);
  set_aggressive(0);
  set_attack_chance(0);
}
