/*
 * /d/Shire/herald/book.c
 *
 * The prayer book/spell object for the Heralds of the Valar
 *
 * Totally recoded by Igneous to work within the new Spellsystem.
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/magic/spellcasting";
inherit "/std/object";

// Now we inherit all the spells
inherit "/d/Shire/herald/spells/mel";
inherit "/d/Shire/herald/spells/ramar";
inherit "/d/Shire/herald/spells/palandir";
inherit "/d/Shire/herald/spells/khil";
inherit "/d/Shire/herald/spells/haetir";
inherit "/d/Shire/herald/spells/silme";
inherit "/d/Shire/herald/spells/vanahwesta";
inherit "/d/Shire/herald/spells/ondo";
inherit "/d/Shire/herald/spells/lissinen";
inherit "/d/Shire/herald/spells/lammen";
inherit "/d/Shire/herald/spells/engwagalad";

#include <stdproperties.h>
#include "/d/Shire/herald/herald.h"

public void
create_object()
{
    set_name("book");
    add_name("_Shire_herald_prayerbook_");
    add_adj(({"leather","prayer"}));
    set_short("leather prayer book");
    set_long("This is a leather prayer book, richly embossed with "+
      "fourteen powerful figures, one of which is wearing a crown.\n");

    add_spell("mel", "praise Lorien", create_mel_spell, 
      spell_target_caster_environment);
    add_spell("ramar", "summon a messenger", create_ramar_spell,
      spell_target_caster_environment);
    add_spell("palandir", "sense other Heralds", create_palandir_spell,
      spell_target_caster_environment);
    add_spell("khil", "divine one's alignment", create_khil_spell,
      spell_target_one_other_present_living);
    add_spell("haetir", "view someone from afar", create_haetir_spell,
      spell_target_one_distant_known_living, 1);
    add_spell("silme", "produce an aura of light", create_silme_spell, 
      spell_target_herald_robe);
    add_spell("vanahwesta", "decrease anger", create_vanahwesta_spell,
      spell_target_caster_environment, 1);
    add_spell("ondo", "robe of stone", create_ondo_spell,
      spell_target_herald_robe);
    add_spell("lissinen", "tend someones wounds", create_lissinen_spell,
      spell_target_one_present_living, 1);
    add_spell("engwagalad", "cure someone from poisoning",
      create_engwagalad_spell, spell_target_one_present_living, 1);
    add_spell("lammen", "speak with the voice of Manwe", create_lammen_spell,
      spell_target_caster);

    add_prop(OBJ_I_WEIGHT,   1200);           /* 1.2 kg        */
    add_prop(OBJ_I_VOLUME,    500);           /* Empty volume. */
    add_prop(OBJ_M_NO_SELL,     1);
    add_prop(OBJ_M_NO_STEAL,    1);
    add_prop(OBJ_I_NO_DROP,     1);
    add_prop(OBJ_M_NO_GIVE,     1);
    remove_prop(OBJ_I_VALUE);
}

mixed
command_read(int more)
{
    write("Your prayer book describes which ingredients are necessary "+
      "for each of your spells.\n\nThe prayer vanahwesta, to Orome, "+
      "requires a brown mushroom.\nThe lissinen prayer, to Lorien, "+
      "requires a huckleberry.\nThe prayer for engwagalad, to Este, "+
      "needs the herb athelas in order to be effective, using the herb "+
      "pawnrose in conjuction will boost the prayers effectiveness.\n"+
      "The haetir prayer is granted through Manwe and a parsley leaf.\n"+
      "The ondo spell of Aule needs a rock, his element, for success.\n"+
      "The prayers mel, silme, ramar, palandir, lammen and khil "+
      "need no ingredients.\n");
    return 1;
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (IS_MEMBER(env) || env->query_wiz_level())
	add_spell_object(env);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}

public int
query_recover()
{
    return 0;
}
