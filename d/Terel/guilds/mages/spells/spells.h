#ifndef _SPELL_DEFS_H
#define _SPELL_DEFS_H

#include "../lib/mages.h"
#include <tasks.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define SPELL_INHERIT   (MAGES_SPELLS +"spell_inherit")
#define SPELL_OBJECT   "/d/Genesis/newmagic/spell_effect_object"
#define GEN_SPELL_DIR  "/d/Genesis/newmagic/spells/"
#define SPELL_BOLT      (GEN_SPELL_DIR + "bolt") 
#define SPELL_HARM     (GEN_SPELL_DIR + "harm")
#define SPELL_LIB         "/d/Genesis/newmagic/spell"
#define SPELL_OBJ_DIR      MAGES_SPELLS + "object/"

#define HIS_HER(ob)  ob->query_possessive()
#define HIM_HER(ob)  ob->query_objective()
#define HE_SHE(ob)   ob->query_pronoun()
#define POSSESSIVE(x)   (x->query_possessive())
#define ENV(arg)   environment(arg)

#define CAP(x)     capitalize(x)

#endif
