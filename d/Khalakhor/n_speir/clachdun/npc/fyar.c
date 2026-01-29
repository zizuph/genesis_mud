#include "local.h"
#include "/d/Khalakhor/sys/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>

inherit "/d/Khalakhor/std/npc/human";
inherit "/d/Genesis/magic/spellcasting";

// Now we inherit the spells.
inherit (SPELL_DIR + "sunburst");
inherit (SPELL_DIR + "lightningbolt");
inherit (SPELL_DIR + "curse");
inherit (SPELL_DIR + "freeze");
inherit (SPELL_DIR + "barrier");
inherit (SPELL_DIR + "heal");
inherit (SPELL_DIR + "icestorm");

// Prototypes
void arm_me();

void
create_khalakhor_human()
{
    int xtra = random(5 + 11);

    set_name("f'yar");
    add_name("clachdun_mage_");
    set_title("of the Order of the Wise, High Advisor of Clach Dun");

    add_adj(({"stone-faced", "grey-bearded"}));
    set_gender(G_MALE);

    set_stats(({80, 100, 110 + xtra, 180 + (2 * xtra), 140 + xtra, 125}));

    set_skill(SS_DEFENCE, 65);
    set_skill(SS_PARRY, 20);
    set_skill(SS_WEP_POLEARM, 65);

    set_skill(SS_APPR_MON, 50);
    set_skill(SS_APPR_OBJ, 70);
    set_skill(SS_AWARENESS, 90);

    set_skill(SS_ELEMENT_FIRE, 40);
    set_skill(SS_ELEMENT_DEATH, 75);
    set_skill(SS_ELEMENT_AIR, 80);
    set_skill(SS_ELEMENT_LIFE, 100);
    set_skill(SS_ELEMENT_EARTH, 50);
    set_skill(SS_ELEMENT_WATER, 90);

    set_skill(SS_FORM_ABJURATION, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_TRANSMUTATION, 80);
    set_skill(SS_FORM_ILLUSION, 70);
    set_skill(SS_FORM_ENCHANTMENT, 70);

    // Now we configure our spells
    add_spell("sunburst", "create a burst of sunlight", create_sunburst,
      spell_target_caster_environment);
    add_spell("lightningbolt", "create a bolt of lightning",
      create_lightning_bolt, spell_target_one_present_living);
    add_spell("curse", "mass curse", create_curse,
      spell_target_non_team_members);
    add_spell("freeze", "freeze another living solid", create_freeze,
      spell_target_one_present_enemy);
    add_spell("barrier", "create a magical barrier of water", create_barrier,
      spell_target_caster_environment);
    add_spell("heal", "heal another with your life energy", create_heal,
      spell_target_one_present_living);
    add_spell("icestorm", "Summon a destructive icestorm", 
      create_icestorm, spell_target_non_team_members);


    // Now we add the spell object to this npc so we have access to the spells
    add_spell_object(this_object());

    arm_me();
}

void
arm_me()
{
    setuid(); seteuid(getuid());
    clone_object(ARM_DIR + "mage_cloak")->move(this_object(), 1);
    clone_object(OBJ_DIR + "mage_ring")->move(this_object(), 1);
    command("wear all");

    clone_object(WEP_DIR + "ice_staff")->move(this_object(), 1);
    command("wield staff");
}

// Part of the bond of the Order of the Dragon is that
// The magic user is able to tap into the mana of the elf that
// is bonded with him or her.
int
query_mana()
{
    object alasia;
    int mana;

    if (!environment())
	return ::query_mana();
    if (objectp(alasia = present("alasia", environment())))
	mana = alasia->query_mana();

    mana += ::query_mana();

    return mana;
}

void
add_mana(int sp)
{
    object alasia;
    int mana;

    if (!environment())
    {
	::add_mana(sp);
	return;
    }
    if (objectp(alasia = present("alasia", environment())))
    {
	if (sp < 0)
	{
	    if (-sp <= (mana = alasia->query_mana()))
	    {
		alasia->add_mana(sp);
		return;
	    }
	    else
	    {
		sp += mana;
		alasia->add_mana(-mana);
	    }
	}
    }
    ::add_mana(sp);
}

object
get_random_enemy()
{
    return ONE_OF(query_enemy(-1) & all_inventory(environment(this_object())));
}


int
cast_helpful_spell()
{
    if (!present("_magic_water_barrier_", environment()))
    {
	command("cast barrier");
	return 1;
    }
    if (!random(4) && query_hp() <= query_max_hp() / 2)
    {
	command("cast heal f'yar");
	return 1;
    }
}

int
cast_harmful_spell(object victim)
{

    if (!victim->query_clachdun_cursed() && !random(3))
    {
	command("cast curse");
	return 1;
    }

    victim = get_random_enemy();
    if (!victim->query_clachdun_frozen() && !random(3))
    {
	command("cast freeze "+OB_NAME(victim));
	return 1;
    }
    if (!random(4))
    {
	command("cast lightningbolt "+OB_NAME(victim));
	return 1;
    }
    command("cast icestorm");
    return 1;
}

int
special_attack(object enemy)
{
    int res;

    if (query_prop(LIVE_I_CONCENTRATE))
	return 1;
    // Damn no mana so don't try and cast
    if (query_mana() <= 125)
	return 0;
    if (!CAN_SEE_IN_ROOM(this_object()))
    {
	command("cast sunburst");
	return 1;
    }

    if (!random(5))
	res = cast_helpful_spell();
    if (!res && !random(2))
	res = cast_harmful_spell(enemy);

    return res;
}
