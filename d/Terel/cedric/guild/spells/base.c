#pragma no_clone

// TODO: Move
inherit "/w/cotillion/open/template/template";

#include "../guild_defs.h"
#include <ss_types.h>

void
configure_minstrel_spell()
{
    this_object()->set_ability_group(GUILD_NAME);
    this_object()->set_spell_vocal(1);
    this_object()->set_spell_element(SS_ELEMENT_AIR, 40);
    this_object()->set_spell_form(SS_FORM_CONJURATION, 40);
}

