inherit "/d/Emerald/std/emerald_monster";

#include "../defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <options.h>
#include <macros.h>


public void
create_emerald_monster()
{
    set_name("necromance");
    set_living_name("necromance");
    set_race_name("human");

    set_long("A tall woman with piercing eyes and sunken cheeks. " +
      "Her gaunt face hints at a thin body, but the heavy robes " +
      "which enshroud her lend no clue to her true physique. Her " +
      "dull gray hair is twisted into a knot at the nape of her " +
      "neck, making her appear as though her skin is stretched " +
      "over her bones. Her shrivelled fingers end in thick, brittle " +
      "fingernails. Despite her withered physical appearance, " +
      " she seems to emanate power, and could be a dangerous foe. \n");
    set_stats(({ 100, 300, 250, 250, 225, 300 }));

    set_all_hitloc_unarmed(100);
    set_all_attack_unarmed(100, 100);

    set_gender(G_FEMALE);
    set_alignment(-1000);

    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENSE, 90);
    set_skill(SS_PARRY, 95);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_ELEMENT_DEATH, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_ABJURATION, 80);
    set_skill(SS_ELEMENT_EARTH, 80);
    set_skill(SS_ELEMENT_AIR, 80);
    set_skill(SS_ELEMENT_WATER, 80);

    add_prop(LIVE_I_SEE_INVIS, 100);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " doesn't accept gifts from mortals.\n");
    add_prop(LIVE_I_SEE_DARK,100);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_FIRE, 70);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_EARTH, 65);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_DEATH, 95);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_ELECTRICITY, 70);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_WATER, 20);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_ILLUSION, 100);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_POISON, 100);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_ACID, 70);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_MAGIC, 50);


    add_equipment(({
	MONASTERY_DIR + "wep/reaver_" + (random(2) ? "axe" : "scythe"), }));

    "intensely--its red eyes corruscating with demonic power.\n");

}

public int
