#include "spells.h"

inherit SPELL_INHERIT;

void
do_mel_spell(object caster, object *targets, int *resist, int result)
{
    caster->catch_tell("You kneel and sing an elven song to please Lorien.\n" +
        "When you arise, you notice a beautiful flower has started to grow " +
        "here, as a sign of Lorien's approval of your song. Its star-shaped " +
        "bud opens up slowly, glowing slightly from your powerful song.\n");
    tell_room(targets[0], QCTNAME(caster) + " starts to "+
        "sing an ancient song.\nWhile "+HE_SHE(caster)+ " sings, a "+
        "beautiful flower appears from nowhere.\n"+
        "The star-shaped bud slowly opens, glowing slightly from "+ 
        HIS_HER(caster) + " powerful song.\n" +
        "You gasp in astonishment!\n", ({caster}));

    FIXEUID;
    make_spell_effect_object(query_spell_object(), caster, targets,
      resist, result);
}

public int
create_mel_spell(object caster, object *targets, string args)
{
    args = lower_case(args);
    if (args != "lorien" && args != "for lorien")
    {
	caster->catch_tell("Cast mel for whom?\n");
	return 1;
    }
    default_herald_spell_config();
    set_spell_mana(10);
    set_spell_task(TASK_SIMPLE - (caster->query_stat(SS_LAYMAN) / 4) );
    set_spell_ingredients(0);
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_CONJURATION, 10);
    set_spell_effect(do_mel_spell);
    set_spell_object(SPELL_OBJECT_DIR + "flower");
    return 0;
}
