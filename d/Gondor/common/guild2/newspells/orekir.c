/* 
 * Created on suggestion by Tharizdun.
 * It is really more of a cantrip then a pure spell.
 *
 * The spell is rewarded at the rank of High Servant
 *
 * Name: Orekir, Heart Cleave
 * Use : Takes usable parts from a corpse, but leave
 *       the remaining mass behind. This way the 
 *       smashed pulps and charred remains are still
 *       left behind for the enemies of the Society 
 *       to see.
 *
 * Ingredients: small obsidian shard
 * Forms      : Conjuration
 * Elements   : Air
 * 
 *
 * Tax: I suggest no tax since it gives no advantage
 *      and this spell/cantrip is in fact better 
 *      codewise then the ingott... =o)
 *
 *
 * Description of the cantrip:
 *
 *      The cantrip will harvest bodyparts from a corpse
 *      as if a player cut things from the corpse and 
 *      leave the corpse otherwise intact in regards of
 *      decay. The code modifies the set_state_desc and
 *      pset_state_desc only, to let the original code
 *      handle met and not met descriptions.
 *      If there are special leftovers added (vbfc) the 
 *      code will exclude them from what is harvested.
 *
 *      The research of the name can not completely be 
 *      confirmed by myself, but Kir is a stemform of
 *      Cir- to cut/cleave. I have not yet found a 
 *      translation of Ore to be heart, but will go on
 *      artistik freedom since it sounds good and naming
 *      it 'yaviquelet - harvest corpse' makes it harder
 *      to remember and it sounds mean to cleave the 
 *      heart of the fallen foe!
 *
 *
 *                Toby, 24-Sept-2007
 *
 *
 * Modification log:
 *
 *      Toby, 25-Sept-2007: Worked on the targeting.
 *                          I still need to think of proper materials.
 *                          Thinking of a special grass picked from the
 *                          Morgul Vale. After all, it is a cantrip and 
 *                          used for harvesting to accieve bodyparts for
 *                          other spells.
 *
 *      Toby, 27-Sept-2007: Will code an obsidian shard to be bought in
 *                          the potion shop for 1 copper as ingredient.
 *                          The shard symbolizes something very sharp
 *                          to cut with.
 *
 *
 */

#define DEBUG(x) find_player("toby")->catch_msg("[DEBUG - OREKIR]: "  + x + "\n")

#include "spells.h"
#include <composite.h>
#include <macros.h>
#include <formulas.h>
#include <ss_types.h>
#include <tasks.h>
#include <wa_types.h>
#include <files.h>
#include "/std/combat/combat.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "obj/morgul_corpse.h"

#define HIS(x)  (x)->query_possessive()
#define NAME(x) (x->query_npc() ? file_name(x) : x->query_cap_name())
#define OREKIR_PROP   "_orekir_corpseharvested_prop"

inherit SPELL_INHERIT;


public int
query_spell_pretarget()
{
    return 0;
}

void
hook_targets_gone()
{
    write("Unable to focus Orekir at anything you send it at void.\n");
}


void desc_orekir_cast(object caster, object *targets)
{
    caster->catch_tell(one_of_list( ({
        "With the power the Dark Lord has bestowed upon you, you call Heart Cleave upon the corpse "+
               "of the poor " + targets[0]->query_race() + "!\n",
        "With the power of the Dark Lord flowing through you, you call Heart Cleave upon the corpse "+
               "of the poor " + targets[0]->query_race() + "!\n",
        "The power of the Black Master courses through you as you call Heart Cleave upon the corpse "+
               "of the poor " + targets[0]->query_race() + "!\n",
        }) ) );

    caster->catch_tell("The corpse twists and throbs, suddenly bursting open in many places at " +
        "once! Body parts leave the corpse and float swiftly toward you at your commanding " +
        "summons. Utterly ruined, the corpse collapses into a vile heap of tainted gore.\n");

    tell_room(environment(caster), QCTNAME(caster) + " turns " +HIS(caster)+ " gaze towards the "+
         targets[0]->query_race()+ " corpse and raises " +HIS(caster)+ " arms slowly and menacingly, " +
         "rasping something low and guttural. The corpse twists and throbs, suddenly bursting open " +
         "in many places at once! Body parts leave the corpse and float swiftly toward " +
         QTNAME(caster)+ " at " +HIS(caster)+ " commanding summons. Utterly ruined, the corpse " +
         "collapses into a vile heap of tainted gore.\n", caster);
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
    mixed  my_leftovers;
    object my_theorgan;
    string *caster_get = ({});
    int    i, j;


    if (IS_CORPSE_OBJECT(targets[0]))
    {
        if(targets[0]->query_prop(OREKIR_PROP))
        {
            caster->catch_tell("You have already harvested this corpse! Are you " +
                        "seeking to anger the Black Master?\n");
            return;
        }

        my_leftovers = targets[0]->query_leftover(0);


        /* This extra loop is needed as to not reveal to the player there 
           are special things to cut from the corpse.
         */
        for (i = 0; i < sizeof(my_leftovers); i++)
        {
            if(my_leftovers[i][3])
                my_leftovers -= ({ my_leftovers[i] });
        }

        if ( !sizeof(my_leftovers) )
        {
            caster->catch_tell("With the Dark Powers flowing through your undead body " +
                        "you realize there are no bodyparts to reap on this useless " +
                        "lifeless form.\n");

            targets[0]->set_state_desc("tainted corpse of ");
            targets[0]->set_pstate_desc("tainted corpses of ");

            return;
        }

        desc_orekir_cast(caster, targets);

        targets[0]->set_state_desc("vile heap of tainted gore resembling that of ");
        targets[0]->set_pstate_desc("vile heaps of tainted gore resembling that of ");

        for (i = 0; i < sizeof(my_leftovers); i++)
        {
/*            if(my_leftovers[i][3])
                continue;
*/
            for (j = 0 ; j < my_leftovers[i][2] ; j++)
            {
                my_theorgan = clone_object(my_leftovers[i][0]);
                my_theorgan->leftover_init(my_leftovers[i][1], targets[0]->query_race());

                if(my_theorgan->move(caster, 0))
                    my_theorgan->remove_object();
                else
                    caster_get += ({ LANG_ADDART(my_theorgan->query_name()) });
			}
				targets[0]->remove_leftover(my_leftovers[i][1]);
        }

        targets[0]->add_prop(OREKIR_PROP, 1);

        if(!sizeof(caster_get))
            caster->catch_tell("The Dark Lord claimed as his own what was useful from this corpse!\n");
        else
            caster->catch_tell("You harvest " + COMPOSITE_WORDS(caster_get) + " from the corpse.\n");
    }
    IDLENESS->increase_activity( caster, SMALL_SPELL );
}

int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("orekir");
    set_spell_desc("Strip a corpse of useful leftovers.");
    set_spell_target(spell_target_one_present_non_living);

    if(!arg && objectp(caster))
    {
        caster->catch_tell("You must supply a target!\n");
        return 1;
    }

    /*The spell is not being configured for   *
     *a casting attempt, and therefore should *
     *not return 1                            */
    if (!objectp(caster))
    {
        return 0;
    }
    set_free_hands(0);

    /*Special configuration for morgul npcs.  */
    if (caster->query_npc())
    {
        set_spell_stationary(0);
        set_spell_time(spell_resolve_time(caster->query_stat(SS_OCCUP),
            3, 12));
        set_spell_mana(25);
        set_spell_task(TASK_SIMPLE);
        set_spell_element(SS_ELEMENT_AIR, 10);
        set_spell_form(SS_FORM_CONJURATION, 20);
        set_spell_ingredients(0);
        set_spell_peaceful( 1 );
        set_spell_resist(spell_resist);
        set_spell_visual(0);
        set_spell_vocal(0);
        return 0;
    }

    if (!default_morgul_spell_setup(caster))
    {
        return 1;
    }
    set_spell_time( spell_resolve_time( caster->query_stat(SS_OCCUP), 2, 4) );
    set_spell_peaceful( 1 );
    set_spell_mana(20+random(10));
    set_spell_task(TASK_SIMPLE);
    set_spell_resist_task( TASK_IMPOSSIBLE );
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_visual(0);
    set_spell_vocal(0);

    if (caster->query_wiz_level())
    {
        set_spell_ingredients(0);
    }
    else
    {
        set_spell_ingredients(({ "orekir_ingr1" }));
    }
    set_spell_offensive(0);
    set_spell_resist(spell_resist);
}

