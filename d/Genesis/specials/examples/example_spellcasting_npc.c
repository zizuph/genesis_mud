/*
 * Coded by Arman September 2017
 *
 * An example spellcasting creature
 * 
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit "/std/monster";

#define MANA_SHADOW          ("/d/Genesis/specials/guilds/shadows/mana_shadow")
#define SPELL_SOUL           ("/d/Genesis/specials/examples/tutorial_grimoire_spell_soul")
#define SPELL_MANAGER_SOUL   ("/d/Genesis/specials/guilds/souls/spell_manager_soul")
#define TO                   this_object()

void get_me_soul();
int soul_id;

void
create_monster()
{
    if(!IS_CLONE)
	return;

    set_name("spellcaster");
    set_adj("cunning");
    add_adj("savant");
    set_race_name("human");
    set_short("cunning savant spellcaster");
    set_gender(G_MALE);
    set_long("Before you stands an example of a spellcasting npc.\n");

    set_stats(({100,100,100,100,100,100}));
    set_hp(10000);

    set_skill(SS_SPELLCRAFT, 90);
    set_skill(SS_FORM_ENCHANTMENT, 90);
    set_skill(SS_FORM_CONJURATION, 90);
    set_skill(SS_FORM_DIVINATION, 90);
    set_skill(SS_FORM_ABJURATION, 90);
    set_skill(SS_FORM_ILLUSION, 90);
    set_skill(SS_FORM_TRANSMUTATION, 90);
    set_skill(SS_ELEMENT_FIRE, 90);
    set_skill(SS_ELEMENT_EARTH, 90);
    set_skill(SS_ELEMENT_WATER, 90);
    set_skill(SS_ELEMENT_AIR, 90);

    clone_object(MANA_SHADOW)->shadow_me(TO);

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    seteuid(getuid());
}

void
get_me_soul()
{
    add_cmdsoul(SPELL_SOUL);
    add_cmdsoul(SPELL_MANAGER_SOUL);
    add_cmdsoul(MANA_SHADOW);
    update_hooks(); 
    remove_alarm(soul_id);
}

/* Added so that special attack function manages the spell rotations */
public int
no_repeat_harm_spell()
{
    return 1;
}

int
special_attack(object enemy)
{
    int     attacktype = random(4);
 
    if (attacktype == 0 || attacktype == 1)
    {
       if(!("/d/Genesis/specials/examples/grimoire_demonfethos_spell"->has_spell_object(TO)))
       {
         // Cast the demon ward spell if not in effect as first spell cast
          command("cast demonfethos");
          return 1;
       }

       command("cast aquablast"); // Cast the aqua blast harm spell
       return 1;
    }

    return 0;
}
