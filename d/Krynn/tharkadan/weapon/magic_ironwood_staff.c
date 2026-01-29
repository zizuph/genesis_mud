inherit "/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_weapon()
{
    set_name("staff");
    set_adj("runed");
    add_adj("ironwood");
    set_short("runed ironwood staff");
    set_long("This is a staff made of the rare magical wood known as " +
        "ironwood. As hard as normal wood it is incredibly light, and " +
        "is usually only used in the creation of masterwork items. This " +
        "staff has a sharp black diamond shard held in place by four " +
        "silver prongs artistically shaped like a talon of an eagle. " +
        "The shaft of the staff is covered with runes also embossed in " +
        "silver.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This staff was created long before the " +
        "Cataclysm by a black-robed Wizard of High Sorcery battlemage. " +
        "Loving the thrill of hand-to-hand combat, he enchanted this " +
        "staff to draw on the holders magecraft and their skill with " +
        "the element of wind to empower the staff to be quick in the " +
        "hands, but powerful enough to fell a warhorse in a hit.\n", 15,
        "As thrilling as hand-to-hand combat was for the battlemage, " +
        "he did not forsake enchantments that also enhanced the power " +
        "of his spells when needed.\n", 25 }));
    add_prop(OBJ_S_WIZINFO, "This weapon gets a bonus to hit/pen " +
        "and spell power " +
        "depending on the holders SPELLCRAFT and ELEMENT_AIR skills, " +
        "/d/Krynn/tharkadan/living/ogre_magi.c The staff is also very " +
        "light.\n");

    set_wf(TO);
    set_default_weapon(10, 10, W_POLEARM, W_BLUDGEON | W_IMPALE, W_BOTH);
    set_magic_spellpower(10);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 1000);
}

void
decide_hitpen()
{
    int hit, pen, spellpen;
    object who = query_wielded();

    if (!objectp(who))
	return;

    who->catch_tell("The black diamond shard of the runed ironwood " +
       "staff pulses darkly as you wield it, and you feel a cold " +
       "presence interrogate your arcane skills and abilities.\n");
    tell_room(environment(who), "The black diamond shard of the runed " +
       "ironwood staff pulses darkly as " + QTNAME(who) + 
       " wields it.\n", ({ who }), who);

    hit = 10 + min(50, who->query_skill(SS_ELEMENT_AIR) / 2);
    pen = 10 + min(50, who->query_skill(SS_SPELLCRAFT) / 2);
    spellpen = 5 + min(50, who->query_skill(SS_SPELLCRAFT) / 2);
    set_hit(hit);
    set_pen(pen);
    set_magic_spellpower(spellpen);
    who->update_weapon(TO);
}
 
mixed
wield(object what)
{
    set_alarm(1.0, 0.0, decide_hitpen);
    return 0;
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}