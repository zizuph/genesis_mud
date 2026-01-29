
#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "identify";

#include <ss_types.h>

public void
config_identify_spell()
{
    /* Override the difficulty and the ingredients */
    set_spell_element(SS_ELEMENT_AIR, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
}

public string *
query_identify_ingredients(object caster)
{
    return ({ "identify_scroll", "white_pearl" });
}
