#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <money.h>

inherit "/d/Krynn/std/monster";

#define WEP_STAFF       "/d/Ansalon/balifor/flotsam_forest/obj/weapon/staff"
#define VEST            "/d/Krynn/haven/town/arm/vest"
#define HERB_POUCH      "/d/Gondor/common/obj/herbpouch"
#define SATCHEL         "/d/Gondor/common/potions/satchel"
#define BOOTS           "/d/Ansalon/taman_busuk/neraka/arm/boots1"
#define BREECHES        "/d/Ansalon/taman_busuk/neraka/arm/breeches"
#define BELT            "/d/Ansalon/taman_busuk/neraka/arm/lbelt"

#define M1   MONEY_MAKE_GC(40)->move(TO);
#define M2   MONEY_MAKE_SC(40)->move(TO);
#define M3   MONEY_MAKE_PC(10)->move(TO);

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

void get_me_soul();
void arm_me();

int soul_id;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("antimodes");
    set_living_name("antimodes");
    set_title("of Balifor, High Mage of the Order of the White Robes");
    set_race_name("human");
    set_adj("thoughtful");
    add_adj("black-bearded");
    set_gender("G_MALE");
    set_long("Before you stands a fairly unassuming well-tailored man, " +
             "who you would normally think to be a successful merchant if "+
             "not for his white-robes and aura of power surrounding him, " +
             "indicating he is a wizard of the Orders of High Sorcery.\n");

    set_stats(({160,160,400,300,300,160}));
    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(OBJ_M_NO_ATTACK,"A powerful magic shield protects him " +
             "from being attacked.\n");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_FORM_ENCHANTMENT, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_DIVINATION, 100);
    set_skill(SS_FORM_ABJURATION, 100);
    set_skill(SS_FORM_ILLUSION, 100);
    set_skill(SS_FORM_TRANSMUTATION, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_EARTH, 100);
    set_skill(SS_ELEMENT_WATER, 100);
    set_skill(SS_ELEMENT_AIR, 100);

    add_prop(OBJ_I_RES_POISON, 100);

    set_all_hitloc_unarmed(90);

    clone_object(MANA_SHADOW)->shadow_me(TO);

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    set_alarm(1.0, 0.0, arm_me);



    set_alignment(1200);
}

void
arm_me()
{
    object robe;

    clone_object(WEP_STAFF)->move(TO,1);
    command("wield all");
    clone_object(WOHS_GUILD_OBJECT)->move(TO, 1);
    robe = clone_object(WOHS_ROBE);
    robe->set_robe_colour("white");
    robe->move(TO, 1);
    clone_object(VEST)->move(TO,1);
    clone_object(BREECHES)->move(TO,1);
    clone_object(BELT)->move(TO,1);
    clone_object(HERB_POUCH)->move(TO,1);
    clone_object(SATCHEL)->move(TO,1);
    command("wear all");
    command("wear hood");
    command("tie pouch");
    command("tie satchel");
    M1
    M2
    M3
}

void
get_me_soul()
{
    add_cmdsoul(WOHS_SOUL);
    add_cmdsoul(SOHM_DIR + "souls/common_spell_soul");
    add_cmdsoul(SPELL_MANAGER_SOUL);
    add_cmdsoul(WOHS_SPELLS + "acid_arrow");
    update_hooks();
    remove_alarm(soul_id);
}

string
query_wohs_order_colour()
{
    return "white";
}

string
query_guild_name_occ()
{
    return "Wizards of High Sorcery";
}

int
query_guild_level_occ()
{
    return 12;
}

public int
can_ignore_ingredients(object caster)
{
    return 1;
}

/* Added so that special attack function manages the spell rotations */
public int
no_repeat_harm_spell()
{
    return 1;
}

int
query_cantrip_spells_max()
{
    return 4;
}

int
query_minor_spells_max()
{
    return 4;
}

int
query_lesser_spells_max()
{
    return 4;
}

int
query_greater_spells_max()
{
    return 4;
}