#ifndef _RANGER_SPELL_DEFS_H
#define _RANGER_SPELL_DEFS_H

#include <tasks.h>
#include <ss_types.h>

#define RANGER_SPELL_DIR   "/d/Gondor/common/guild/newspells/"
#define GENESIS_SPELL_DIR  "/d/Genesis/newmagic/"


#define SPELL_INHERIT   (RANGER_SPELL_DIR +"spell_inherit")

#define SPELL_OBJECT    (GENESIS_SPELL_DIR + "spell_effect_object")
#define SPELL_LIB       (GENESIS_SPELL_DIR + "spell")
#define SPELLBOOK       (RANGER_SPELL_DIR + "spellbook")


#define SPELL_OBJ_DIR      RANGER_SPELL_DIR + "obj/"
#define RANGER_SPELL_TXT   RANGER_SPELL_DIR + "txt/"

#define COPY_SCROLL     (SPELL_OBJ_DIR + "copy_scroll")

#define SPELL_WHISTLE      1
#define SPELL_HEAL         2
#define SPELL_REST         4
#define SPELL_CLEANSE      8
#define SPELL_NIGHTVISION 16
#define SPELL_ELBERETH    32
#define SPELL_SPEEDGROW   64

#ifndef SS_RANGER_SPELL_LIST
#define SS_RANGER_SPELL_LIST  118214
#endif
#ifndef SS_RANGER_DISFAVOUR
#define SS_RANGER_DISFAVOUR   118215
#endif

#endif
