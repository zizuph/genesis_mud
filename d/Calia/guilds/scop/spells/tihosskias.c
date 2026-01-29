/*
 * tihosskias.c
 *
 * Tihosskias (Shadow Wall) spell for the Spirit Circle of Psuchae
 *
 * Navarre, November, 2006
 * Navarre, October 2007: Removed resistance check on caster, as they kept
 *                        Failing due to their shadowform.
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER

private string direction = "";

string
query_spell_level()
{
    return "Elder";
}

/*
 * Filter walls
 */
int
filter_wall(object ob)
{
    return ob->id("_SCOP_shadow_wall");
}

/*
 * Use this to determine the direction
 */
public object *
target_direction(object caster, string str)
{
    string who, dir;
    object* targets;
    object* existing_walls;

    int i;

    if (!strlen(str))
    {
        caster->catch_tell("You must specify a direction to summon the Shadow Wall.\n");
        return ({});
    }

    if (!(IN_ARRAY(str, environment(caster)->query_exit_cmds())))
    {
        caster->catch_tell("That is not a valid exit for the spell!\n");
        return ({});
    }

    existing_walls = filter(all_inventory(environment(caster)), &->id("_SCOP_shadow_wall"));

    for(int i = 0; i < sizeof(existing_walls); i++)
    {
      if(existing_walls[i]->query_blocked_exit() == str)
      {
            caster->catch_tell("There is already a wall blocking that path!\n");
            return ({ });
      }
    }

    direction = str;

    return ({ caster });
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
    object shadow_wall;

    if (caster == 0)
    {
        set_spell_name("tihosskias");
        set_spell_desc("Shadow Wall");

        set_spell_target(target_direction);
        set_spell_target_verify(spell_verify_present);
        set_spell_time(4);
        set_spell_mana(100);
        set_spell_vocal(0);
        set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_OCCUP)/2));
        set_spell_resist_task(TASK_FORMIDABLE);
        set_spell_element(SS_ELEMENT_SPIRIT, 40);
        set_spell_form(SS_FORM_DIVINATION, 30);
        set_spell_ingredients(({"_leftover_rib", "black_diamond_shard"}));
        set_spell_object(SPIRIT_SPELLS + "tihosskias_obj"); 
            

        add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);
     }
     else
     {     

         if (caster->query_intoxicated())
         {
             caster->catch_tell("You cannot use Psuchae's gifts while intoxicated!\n");
             return 1;
         }
         if (caster->query_alignment() < 0)
         {
             caster->catch_tell("You cannot use Psuchae's gifts while you are not "+
                                "good aligned.\n");
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
    caster->catch_tell("You concentrate on the powers of Psuchae.\n");
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
    int success, hitresult, pen;
    object spellob;
    object* existing_walls = ({});
    object tar = targets[0];
    object metawep;

    if (tar != caster && random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but your target is" +
                           " unaffected.\n");
        return;
    }

    caster->catch_msg("You wave your arms in an intricate design forming " +
                      "a shadow. The shadow shatters throwing shadowy " +
                      "tendrils in your carefully chosen direction. "+
                      "As the tendrils stop, a mesh of shadows pervade " +
                      "the area leading "+direction+".\n");

    tell_room(environment(caster), QCTNAME(caster)+" waves "+HIS(caster) +
              " arms in an intricate design forming a shadow. The shadow " +
              "shatters throwing shadowy tendrils in a carefully chosen " +
              "direction. As the tendrils stop, a mesh of shadows pervade " +
              "the area leading "+direction+".\n", caster);
    setuid();
    seteuid(getuid());
    spellob = make_spell_effect_object(query_spell_object(), caster, tar, 
                                       resist[0], result);
    spellob->set_blocked_exit(direction);
    spellob->set_caster(caster);
    spellob->move(environment(caster),1);
}
