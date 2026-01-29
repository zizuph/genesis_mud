#ifndef _SPELLS_H
#define _SPELLS_H
#include "../guild.h"
#include <tasks.h>
#include <ss_types.h>

#define SPELL_INHERIT     (SPELLS + "spell_inherit")
#define SPELL_INHERIT2     (SPELLS + "spell_inherit2")
#define SPELL_OBJECT      "/d/Genesis/newmagic/spell_effect_object"
#define SPELL_OBJECT_DIR  (SPELLS + "obj")
#define FIXEUID seteuid(getuid(this_object()))

#endif _SPELLS_H
