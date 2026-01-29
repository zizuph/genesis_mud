/*
 * spazopetra.c
 *
 * Spazopetra (Shatter Gems) spell for the Spirit Circle of Psuchae
 * This will make the cleric able to shatter gems into shards of the same type
 *
 * Navarre July 22nd 2007.
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER


#define AMETHYST_SHARD      (SPIRIT_GEMS+"amethyst_sd")
#define BLACK_DIAMOND_SHARD (SPIRIT_GEMS+"diamond_black_sd")
#define BLACK_ONYX_SHARD    (SPIRIT_GEMS+"onyx_sd")
#define BLACK_PEARL_SHARD   (SPIRIT_GEMS+"pearl_black_sd")
#define BLOODSTONE_SHARD    (SPIRIT_GEMS+"bloodstone_sd")
#define CARNELIAN_SHARD     (SPIRIT_GEMS+"carnelian_sd")
#define CHALCEDONY_SHARD    (SPIRIT_GEMS+"chalcedony_sd")
#define DIAMOND_SHARD       (SPIRIT_GEMS+"diamond_sd")
#define GARNET_SHARD        (SPIRIT_GEMS+"garnet_sd")
#define LAPIZ_LAZULI_SHARD  (SPIRIT_GEMS+"lapis_sd")
#define MOONSTONE_SHARD     (SPIRIT_GEMS+"moonstone_sd")
#define OPAL_SHARD          (SPIRIT_GEMS+"opal_sd")
#define PINK_CORAL__SHARD   (SPIRIT_GEMS+"coral_sd")
#define WHITE_PEARL_SHARD   (SPIRIT_GEMS+"pearl_sd")
#define YELLOW_TOPAZ_SHARD  (SPIRIT_GEMS+"topaz_yellow_sd")
#define YELLOW_BERYL_SHARD  (SPIRIT_GEMS+"beryl_sd")

object moonstones, carnelians, chalcedony, pink_corals, yellow_topazes,
       yellow_beryls, black_onyxes, g_diamonds, b_diamonds, lapiz_lazuli,
       amethyst, iridescent_opal, garnet, w_pearls, b_pearls,
       s_bloodstones;

string
query_spell_level()
{
    return "Apprentice";
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    if (caster == 0)
    {
        set_spell_name("spazopetra");
        set_spell_desc("Shatter Gems");
        set_spell_target(spell_target_caster);
        set_spell_time(6);
        set_spell_mana(100);
        set_spell_visual(0);
        set_spell_vocal(0);
        set_spell_peaceful(1);
        set_spell_task(TASK_SIMPLE);
        set_spell_element(SS_ELEMENT_LIFE, 10);
        set_spell_form(SS_FORM_ENCHANTMENT, 15);
        set_spell_ingredients(({}));
        set_spell_resist(spell_resist_beneficial);
        add_element_resistance(SS_ELEMENT_LIFE, MAGIC_I_RES_LIFE);
    }
    else
    {
        if (caster->query_intoxicated())
        {
            caster->catch_tell("You cannot use Psuchae's gifts " +
                               "while intoxicated!\n");
            return 1;
        }
        if (caster->query_alignment() < 0)
        {
            caster->catch_tell("You cannot use Psuchae's gifts " +
                               "while you are not good aligned.\n");
            return 1;
        }

	// Find all the gems.
	moonstones      = present("lambent_moonstone", environment(caster));
	carnelians      = present("red_carnelian", environment(caster));
	chalcedony      = present("striped_chalcedony", environment(caster));
	pink_corals     = present("pink_coral", environment(caster));
	yellow_topazes  = present("yellow_topaz", environment(caster));
	yellow_beryls   = present("yellow_beryl", environment(caster));
	black_onyxes    = present("black_onyx", environment(caster));
	g_diamonds      = present("glittering_diamond", environment(caster));
	b_diamonds      = present("black_diamond", environment(caster));
	lapiz_lazuli    = present("blue_lapis lazuli", environment(caster));
	amethyst        = present("purple_amethyst", environment(caster));
	iridescent_opal = present("iridescent_opal", environment(caster));
	garnet          = present("orange-red_garnet", environment(caster));
	w_pearls        = present("white_pearl", environment(caster));
	b_pearls        = present("black_pearl", environment(caster));
	s_bloodstones   = present("shining_bloodstone", environment(caster));
	
	if(!(moonstones || carnelians || chalcedony || pink_corals || yellow_topazes ||
	     yellow_beryls || black_onyxes || g_diamonds || b_diamonds ||
	     lapiz_lazuli  || amethyst || iridescent_opal || garnet ||
	     w_pearls || b_pearls || s_bloodstones))
	{
	    caster->catch_tell("There are no gems here on the ground which " +
			       "this gift would have any effect on!\n");
	    return 1;
	}
    }
    return 0;
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You summon the energies of Psuchae.\n");
    say(QCTNAME(caster) + " appears to be in deep concentration.\n");
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{

    object moonstone_shard, carnelian_shard, chalcedony_shard, pink_coral_shard,
	   yellow_topaz_shard, yellow_beryl_shard, black_onyx_shard, g_diamond_shard,
           b_diamond_shard, lapiz_lazuli_shard, amethyst_shard, iridescent_opal_shard,
	   garnet_shard, w_pearl_shard, b_pearl_shard, s_bloodstone_shard;

    int num_moonstones      = moonstones->num_heap();
    int num_carnelians      = carnelians->num_heap();
    int num_chalcedony      = chalcedony->num_heap();
    int num_pink_corals     = pink_corals->num_heap();
    int num_yellow_topazes  = yellow_topazes->num_heap();
    int num_yellow_beryls   = yellow_beryls->num_heap();
    int num_black_onyxes    = black_onyxes->num_heap();
    int num_g_diamonds      = g_diamonds->num_heap();
    int num_b_diamonds      = b_diamonds->num_heap();
    int num_lapiz_lazulis    = lapiz_lazuli->num_heap();
    int num_amethysts        = amethyst->num_heap();
    int num_iridescent_opals = iridescent_opal->num_heap();
    int num_garnets          = garnet->num_heap();
    int num_w_pearls        = w_pearls->num_heap();
    int num_b_pearls        = b_pearls->num_heap();
    int num_s_bloodstones   = s_bloodstones->num_heap();
    
    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but nothing happened.\n");
        return;
    }
    caster->catch_tell("You channel the energies of Psuchae. A bright "+
                       "light blinds you for a brief moment, while you " +
		       "hear a sound like shattering glass. As you are " +
		       "able to see again, a pile of gem shards lay before you.\n");
  
    say("A bright light blinds you for a brief moment, while you hear a "+
	"sound like shattering glass. As you are able to see again, a "+
	"pile of gem shards lay before you.\n", caster);
    setuid();
    seteuid(getuid());

    moonstones->remove_object();
    carnelians->remove_object();
    chalcedony->remove_object();
    pink_corals->remove_object();
    yellow_topazes->remove_object();
    yellow_beryls->remove_object();
    black_onyxes->remove_object();
    g_diamonds->remove_object();
    b_diamonds->remove_object();
    lapiz_lazuli->remove_object();
    amethyst->remove_object();
    iridescent_opal->remove_object();
    garnet->remove_object();
    w_pearls->remove_object();
    b_pearls->remove_object();
    s_bloodstones->remove_object();
    
    moonstone_shard = clone_object(MOONSTONE_SHARD);
    moonstone_shard->set_heap_size(num_moonstones*(3+random(3)));
    moonstone_shard->move(environment(caster), 1);

    carnelian_shard = clone_object(CARNELIAN_SHARD);
    carnelian_shard->set_heap_size(num_carnelians*(3+random(6)));
    carnelian_shard->move(environment(caster), 1);

    chalcedony_shard = clone_object(CHALCEDONY_SHARD);
    chalcedony_shard->set_heap_size(num_chalcedony*(3+random(6)));
    chalcedony_shard->move(environment(caster), 1);

    pink_coral_shard = clone_object(PINK_CORAL__SHARD);
    pink_coral_shard->set_heap_size(num_pink_corals*(2+random(3)));
    pink_coral_shard->move(environment(caster), 1);

    yellow_topaz_shard = clone_object(YELLOW_TOPAZ_SHARD);
    yellow_topaz_shard->set_heap_size(num_yellow_topazes*(2+random(4)));
    yellow_topaz_shard->move(environment(caster), 1);

    yellow_beryl_shard = clone_object(YELLOW_BERYL_SHARD);
    yellow_beryl_shard->set_heap_size(num_yellow_beryls*(2+random(2)));
    yellow_beryl_shard->move(environment(caster), 1);

    black_onyx_shard = clone_object(BLACK_ONYX_SHARD);
    black_onyx_shard->set_heap_size(num_black_onyxes*(3+random(4)));
    black_onyx_shard->move(environment(caster), 1);

    g_diamond_shard = clone_object(DIAMOND_SHARD);
    g_diamond_shard->set_heap_size(num_g_diamonds*(3+random(5)));
    g_diamond_shard->move(environment(caster), 1);

    b_diamond_shard = clone_object(BLACK_DIAMOND_SHARD);
    b_diamond_shard->set_heap_size(num_b_diamonds*(3+random(7)));
    b_diamond_shard->move(environment(caster), 1);
    
    lapiz_lazuli_shard = clone_object(LAPIZ_LAZULI_SHARD);
    lapiz_lazuli_shard->set_heap_size(num_lapiz_lazulis*(3+random(3)));
    lapiz_lazuli_shard->move(environment(caster), 1);
    
    amethyst_shard = clone_object(AMETHYST_SHARD);
    amethyst_shard->set_heap_size(num_amethysts*(3+random(3)));
    amethyst_shard->move(environment(caster), 1);

    iridescent_opal_shard = clone_object(OPAL_SHARD);
    iridescent_opal_shard->set_heap_size(num_iridescent_opals*(3+random(5)));
    iridescent_opal_shard->move(environment(caster), 1);

    garnet_shard = clone_object(GARNET_SHARD);
    garnet_shard->set_heap_size(num_garnets*(3+random(4)));
    garnet_shard->move(environment(caster), 1);

    w_pearl_shard = clone_object(WHITE_PEARL_SHARD);
    w_pearl_shard->set_heap_size(num_w_pearls*(5+random(10)));
    w_pearl_shard->move(environment(caster), 1);

    b_pearl_shard = clone_object(BLACK_PEARL_SHARD);
    b_pearl_shard->set_heap_size(num_b_pearls*(5+random(10)));
    b_pearl_shard->move(environment(caster), 1);

    s_bloodstone_shard = clone_object(BLOODSTONE_SHARD);
    s_bloodstone_shard->set_heap_size(num_s_bloodstones*(3+random(6)));
    s_bloodstone_shard->move(environment(caster), 1);
}
