/*
 * This file is put here so all rooms and the like can #include "defs.h" no
 * matter where they are put or moved to. This includes the real "defs.h"
 * so that can be left in the same place.
 */

#include "/d/Immortal/std/domain.h"

#define RICHCLUB        "/d/Immortal/rclub/"
#define HIS_HER(xxx)    xxx->query_possessive()
#define HIM_HER(xxx)    xxx->query_objective()
#define HE_SHE(xxx)     xxx->query_pronoun()
#define CAP             capitalize
#define ENV             environment
