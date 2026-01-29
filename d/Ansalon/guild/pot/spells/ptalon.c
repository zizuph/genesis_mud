/*
 * pTalon
* Modified Louie Oct 15 2005 - Increased damage cap in Krynn and elsewhere
*    to 600/450/300.  Only two options now, Neraka and everywhere
*     else.  Approved by AoB (Cot)
*/
/*
<AoB> Louie: I kinda like 600/450/300 then
<AoB> Louie: Low for killing evil things, good for good aligned
> <AoB> Cotillion: yeah
<AoB> Cotillion: go for that
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>  
#include <alignment.h>
#include <wa_types.h>
#include <files.h>


/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 8;
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
    object tar = targets[0], helmet;
    int base, tar_obnum, *cap;
    string how, ohow;

    if (tar == caster)
    {
        write("There are easier ways to commit suicide.\n");
        return;
    }

/*
Vencar yells: my list would be : 800/600/400 in neraka, 350/250/200 in
krynn/ansalon, 250/175/150 rest of world
Arman rumbles: For a cap?
Vencar yells: holy/neutral/evil
*/

    sscanf(OB_NUM(tar), "%d", tar_obnum);
    
    base = random(31) + 70;

/*
    cap = ({ 250, 175, 150 });
*/
    cap = ({ 600, 450, 300 });

    base += (caster->query_priest_level() + 1) * 3 +
        random(30, tar_obnum);
    base += (caster->query_stat(SS_OCCUP) > 150 ? 150 :
        caster->query_stat(SS_OCCUP));
    if (wildmatch("/d/Ansalon/taman_busuk/neraka/*",
        file_name(environment(caster))))
    {
        base *= 3;
        cap = ({ 800, 600, 400 });
    }
    else if (wildmatch("/d/Ansalon/*",
        file_name(environment(caster))) || wildmatch("/d/Krynn/*",
        file_name(environment(caster))))
    {
        base = (base * 150) / 100;
/*
        cap = ({ 350, 250, 200 });
*/
        cap = ({ 600, 450, 300 });
    }

    /* Vencar 06-feb-2004
       Due to some balance issues, the spell will for now only be good in
       the direct defence of the sacred city Neraka, as was the original
       reason it was approved.
     */
                                 
    /* If inside Krynn/Ansalon we give a bonus if opposing good.
     */
    if ((wildmatch("/d/Ansalon/*", file_name(environment(caster))) ||
        wildmatch("/d/Krynn/*", file_name(environment(caster)))) &&
        tar->query_alignment() >= ALIGN_NEUTRAL)
#ifdef 0
    if ((wildmatch("/d/Ansalon/taman_busuk/neraka/*",
        file_name(environment(caster)))) &&
        tar->query_alignment() >= ALIGN_NEUTRAL)
#endif
        base += tar->query_alignment() / 5;
        
    if ((helmet = tar->query_armour(A_HEAD)))
        base -= random(helmet->query_ac() * 2);

    result = (base / 2 * (min(result, 100) / 35 + 1) * (100 - resist[0])) / 100;

    if (tar->query_alignment() > 250)
        result = min(result, cap[0]);
    else if (tar->query_alignment() < -250)
        result = min(result, cap[2]);
    else
        result = min(result, cap[1]);

    GUILD_ADMIN->log(caster, "ptalon",tar->query_real_name() + "(" +
        file_name(tar) + "): " + result + ", base: " + base + ", resist: " +
        resist[0]);

    if (base < 0 || result < 5)
    {
        caster->catch_tell("Drawing the darkness closer to you, you begin " +
            "to form with your mind the shape of a Dragon's Talon. Sharp " +
            "and lethal, you strike it against " +
            tar->query_the_name(caster) + ", slashing " + HIM(tar) + " with " +
            "no apparent effect only to disappear again.\n");
        tar->catch_tell("You see the shadows solidify into a dark shape " +
            "above you. You realize what it is just as a Dark Talon " +
            "relentlessly slashes down upon you, apparently doing no harm " +
            "and is gone just as quickly as it appeared.\n");
        all_msgbb("Dark shadows begin to form above " + QTNAME(tar) +
            " which takes shape to form a Dark Talon relentlessly slashing " +
            "down upon " + HIM(tar) + ", apparently doing no harm and is " +
            "gone just as quickly as it appeared.\n", caster, tar);

        return;
    }

    switch (result)
    {
        case 1..30:
            how = "scratches " + HIS(tar) + " flesh";
            ohow = "scratches your flesh";
            break;
        case 31..60:
            how = "draws trickles of blood";
            ohow = how;
            break;
        case 61..100:
            how = "tears into " + HIS(tar) + " flesh";
            ohow = "tears into your flesh";
            break;
        case 101..200:
            how = "slashes deep wounds in " + HIS(tar) + " flesh";
            ohow = "slashes deep wounds in your flesh";
            break;
        case 201..350:
            how = "rips open a gash in " + HIS(tar) + " flesh";
            ohow = "rips open a gash in your flesh";
            break;
            break;
        default:
            how = "makes bones visible";
            ohow = how;
            break;
    }

    caster->catch_tell("Drawing the darkness closer to you, you begin " +
        "to form with your mind the shape of a Dragon's Talon. Sharp " +
        "and lethal, you strike it against " +
        tar->query_the_name(caster) + " that relentlessly " + how +
        " only to disappear again.\n");
    tar->catch_tell("You see the shadows solidify into a dark shape " +
        "above you. You realize what it is just as a Dark Talon " +
        "relentlessly " + ohow + " and is gone just as quickly " +
        "as it appeared.\n");
    all_msgbb("Dark shadows begin to form above " + QTNAME(tar) +
        " which takes shape to form a Dark Talon relentlessly slashing " +
        "down upon " + HIM(tar) + " which " + how + " and is gone just " +
        "as quickly as it appeared.\n", caster, tar);

#ifdef 0
    /* Silence is assumed as consent
     */

    // FIX BY BORON, we cap damage at 500
    // May 24, 2002
    if ( result > 500)
        result = 500;
#endif
                    
/*
    tar->heal_hp(-result);
*/
    tar->hit_me(result, MAGIC_DT, caster, -1, A_HEAD);
    if (tar->query_hp() <= 0)
        tar->do_die(caster);
}

public object *
ptalon_target(object caster, string str)
{
    if (!stringp(str) || (str == ""))
        return spell_target_one_present_enemy(caster, str);
    else
        return spell_target_one_other_present_living(caster, str);
}

/* Function name: ingredient_burntout_torch
 * Description:   Used to find a burnt out torch ingredient
 * Arguments:     object *possible - possible ingredients to check
 *                object *found    - ingredients already found
 * Returns:       object - the ingredient found or 0 if non matched
 */
object
ingredient_burntout_torch(object *possible, object *found)
{
    object *arr = possible - found;
    int i = -1, size = sizeof(arr);
    
    while (++i < size)
        if (IS_TORCH_OBJECT(arr[i]) && arr[i]->id("torch") && !arr[i]->query_time())
            return arr[i];
   
    return 0;
}        

object
herb_ingr(object *possible, object *found)
{
    object *list, pl;
    int i;
    
    list = possible - found;
    for (i = 0 ; i < sizeof(list) ; i++)
    {
        if (living(environment(list[i])))
            pl = environment(list[i]);
        else if (living(environment(environment(list[i]))))
            pl = environment(environment(list[i]));
        else if (living(environment(environment(environment(list[i])))))
            pl = environment(environment(environment(list[i])));
        else
            continue;

        if (!IS_HERB_OBJECT(list[i]))
            continue;

        if (list[i]->do_id_check(pl) &&
            wildmatch("*willow", list[i]->query_herb_name()) == 1)
            return list[i];
    }
    
    return 0;
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
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("ptalon");
    set_spell_desc("Summon talons of dragons to slash your foe");

    set_spell_element(SS_ELEMENT_LIFE, 62);
    set_spell_form(SS_FORM_CONJURATION, 20);

    set_spell_time(3);
    set_spell_mana(50);

    set_spell_task(TASK_ROUTINE);

    set_spell_resist(spell_resist_basic);
    set_spell_target(ptalon_target);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(0);    
    set_spell_offensive(1);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"nail", herb_ingr}));
    /*"beach willow"}));
/* Burnt out torches decay when putting them outside a player's
   inventory
 */
    //ingredient_burntout_torch}));
#endif

    set_spell_vocal(1);

    return 0;
}
