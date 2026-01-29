/* 
 * Equipment for undeads
 */
inherit "/lib/unique";
inherit "/std/act/add_things";

#include "defs.h"

void
add_undead_armours()
{
    if (random(2))
        equip(({
          one_of_list(({
            COMMON_ARM_DIR + "rdplatemail", COMMON_ARM_DIR + "rtchainmail",
            COMMON_ARM_DIR + "rshelm",
          })),
          one_of_list(({
            COMMON_ARM_DIR + "rfgreavs", COMMON_ARM_DIR + "rcbracers",
            COMMON_ARM_DIR + "kwboots",
          })),
          one_of_list(({
            COMMON_ARM_DIR + "rdcloak", COMMON_ARM_DIR + "rbelt",
          })),
        }));
    else
        equip(({
          one_of_list(({
            COMMON_ARM_DIR + "kbplatemail", COMMON_ARM_DIR + "kbchainmail",
          })),
          clone_unique(COMMON_ARM_DIR + "kbbracers", 20, ({ 
            COMMON_ARM_DIR + "kwboots",
            COMMON_ARM_DIR + "ktcloak"
          })),
          clone_unique(COMMON_ARM_DIR + "kdgreavs", 20, ({ 
            COMMON_ARM_DIR + "kwboots", 
            COMMON_ARM_DIR + "kdhelm",
            COMMON_ARM_DIR + "ktgloves"
          }))
        }));
}
