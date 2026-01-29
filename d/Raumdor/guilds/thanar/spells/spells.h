#ifndef _SPELLS_H
#define _SPELLS_H
#include "../guild.h"
#include <tasks.h>
#include <ss_types.h>

#define SPELL_INHERIT     (SPELLS + "spell_inherit")
#define SPELL_OBJECT      ("/d/Genesis/newmagic/spell_effect_object")
#define FIXEUID seteuid(getuid(this_object()))

#endif _SPELLS_H
