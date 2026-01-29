/* wizstat_vamp.c created by Shiva@Genesis.
 * This file is meant to give some guild-related info on a vampire.
 * This is a subpart of the vampire guild shadow.
 */

#include "../guild.h"
#include <ss_types.h>
#include <state_desc.h>

#define SW shadow_who

/*
 * Function name: stat_vamp
 * Description:   Returns a string giving various bits of information
 *                about the vampire statistics of this vampire.
 * Returns:       See above.
 */
string stat_vamp()
{
  return sprintf(
      "Name: %12s(%-12s  Race: %-10s   Gender: %-8s\n" +
      "Vamp age: %8d Sire: %-12s File: %-31s\n" +
      "-----------------------------------------------------" +
      "---------------------\n" +
      "Exp: %-7d    Expquest: %-7d   Hp: %4d(%4d) " +
      " Mana: %4d(%4d)\n" +
      "Fatigue: %7d(%7d)\n\n" +
      "Stats:     %@7s\n" +
      "    Val:   %@7d\n" +
      "    Max:                                             " +
      "       %7d\n" +
      "    Base vamp:                                       " +
      "       %7d\n" +
      "    Offset:                                          " +
      "       %7d\n" +
      "    Vamp:                                            " +
      "       %7d\n" +
      "    Effective:                                       " +
      "       %7d\n\n" +
      "Thirst:            %4d(%4d)\n" +
      "Thirst modifier:   %4d\n" +
      "Thirst rate:       %4d\n" +
      "Sunlight res:      %4d\n" +
      "Sunlight damage:   %4d\n" +
      "Sunlight modifier: %4d\n" +
      "Mana drain:        %4d\n"
      ,
      SW->query_name(), SW->query_real_name() + ")",
          SW->query_race_name(), SW->query_gender_string(),
      query_vamp_age(), query_sire() + "", file_name(SW),
      SW->query_exp(), SW->query_exp() - SW->query_exp_combat(),
          SW->query_hp(), SW->query_max_hp(),
      SW->query_mana(), SW->query_max_mana(),
      SW->query_fatigue(), SW->query_max_fatigue(),
      SD_STAT_DESC,
      ({ SW->query_stat(SS_STR), SW->query_stat(SS_DEX),
         SW->query_stat(SS_CON), SW->query_stat(SS_INT),
         SW->query_stat(SS_WIS), SW->query_stat(SS_DIS),
         SW->query_stat(SS_RACE), SW->query_stat(SS_OCCUP),
         SW->query_stat(SS_LAYMAN) }),
      query_max_vamp_stat(),
      query_base_vamp_stat(),
      query_power_offset(),
      query_vamp_stat(),
      query_effective_vamp_stat(),
      query_thirst(), query_max_thirst(),
      query_thirst_modifier(),
      query_thirst_rate(),
      sunlight_res(),
      SUNLIGHT_DAMAGE(query_sunlight_level()),
      query_sunlight_modifier(),
      query_mana_drain());
}
