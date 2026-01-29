inherit "/d/Emerald/std/emerald_monster";

#include <stdproperties.h>
#include <ss_types.h>

void
create_darkling()
{
    set_stats(({ 70, 100, 70, 100, 100, 85 }));

    set_skill(SS_AWARENESS, 70);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_SPELLCRAFT, 70);
    set_skill(SS_FORM_ABJURATION, 50);
    set_skill(SS_LANGUAGE, 50);
    set_skill(SS_UNARM_COMBAT, 40);
}

nomask void
create_emerald_monster()
{
    set_name("darkling");
    set_race_name("darkling");

    /* Darklings are small */
    add_prop(CONT_I_HEIGHT, 100 + random(30));
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_VOLUME, 30000);

    /* Darklings are magic resistant */
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_MAGIC, 40);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_POISON, 50);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_ILLUSION, 80);

    /* Darklings are quick */
    add_prop(LIVE_I_QUICKNESS, 50);

    /* Darklings have magically enhanced perception */
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 5);

    create_darkling();
}
