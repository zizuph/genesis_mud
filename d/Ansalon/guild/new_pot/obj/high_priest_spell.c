/*
 * Ashlar, 09 Jul 98
 *
 * A scroll detailing the ritual to become
 * a priest, and also the spell used to start
 * the ritual
 */
#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include <tasks.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "../guild.h"

/*
 * Function:    safely_load_master_file
 * Description: This safely loads the master file if it hasn't already
 *              been loaded. Otherwise, it just returns the existing
 *              master file. If the file is not loadable, then it
 *              simply returns 0
 * Argument:    filename of the file to load
 */
public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */

public void
scroll_consume(object caster)
{
    object scroll = present("scroll_of_high_dedication", caster);

    if (caster)
    {
        if (living(caster))
        {
            caster->catch_tell("The " + scroll->short() +
                " bursts into flame as the spell is cast!\n");
        }
        else
        {
            tell_room(caster,
                "The " + scroll->short() + " bursts into flame!\n");
        }
    }

    scroll->remove_object();
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    object old_tp = this_player();
    
    set_this_player(caster);
    caster->catch_tell("You begin to read the prayer off the scroll.\n");

    tell_room(environment(caster),
        QCTNAME(caster) + " begins to read a prayer off a scroll.\n",
	    caster);

    set_this_player(old_tp);
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object ob;
    
    caster->catch_tell("You shout the last line of the prayer, " +
    "and a feeling of warmth envelops you.\n");

    setuid();
    seteuid(getuid());

    /* Seems the ritual wasnt loaded properly and couldnt be cloned?
     * Adding a safe loading function and error message just to be sure
     * it works- Carnak
     */
    if (!objectp(safely_load_master_file(GUILDDIR + "obj/high_priest_ritual")))
    {
        caster->catch_msg("Something has gone horribly wrong, please " +
        "contact a wizard.\n");
        return;
    }
    
    ob = clone_object(GUILDDIR + "obj/high_priest_ritual");
    if (ob) ob->move(caster,1);
    
    set_alarm(0.0, 0.0, &scroll_consume(caster));
}

public object *
ded_target(object caster, string str)
{
    object env = environment(caster);

    if (!env || !env->query_prop(NERAKA_I_IS_TEMPLE_ROOF))
    {
        caster->catch_tell("You are not in the proper location to " +
        "perform this ritual.\n");
        return ({ });
    }

    return ({ caster });
}

public int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("dedication");
    set_spell_desc("The Ritual of Dedication");

    set_spell_time(12);
    set_spell_element(SS_ELEMENT_LIFE, 50);
    set_spell_form(SS_FORM_ENCHANTMENT, 50);
    set_spell_mana(450);
    set_spell_task(TASK_HARD);
    set_spell_resist(spell_resist_beneficial);
    set_spell_target(ded_target);

    set_spell_ingredients(({"dragonbrew","dragonbrew","dragonbrew","eye","eye","heart","copper coin","silver coin","gold coin","platinum coin"}));

    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_vocal(1);

    return 0;
}

public void
list_spells(void)
{
/*
    write("\nOn the Scroll of High Dedication:\n" +
        "    dedication - The Ritual of Dedication\n\n");
 */
}
