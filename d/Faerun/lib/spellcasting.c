/*
 *  faerun/lib/spellcasting.c
 *
 *  This is the inherit for a spellcasting NPC, it will make sure spells get
 *  added to the object, and will give do the spellcasting for you.
 *
 *  To use, create a monster and inherit this file, then in your constructor
 *  call:
 *
 *  add_spell("filename to the spell");
 *  set_cast_chance(50); 
 *  setup_spellcasting();
 *
 *  The cast chance is a percentage of chance that a spell is cast. To get
 *  the npc to actually cast spells, you will have to add a call in 
 *  special_attack
 *
 *  int special_attack(object ob)
 *  {
 *      return special_attack_spellcast(ob);
 *  }
 *
 *  That's it, special_attack_spellcast will pick a spell to cast from the
 *  added spells, and checks with the chance if it can cast.
 *
 *  Created by Wully, 12-2-2004
 */

#include <macros.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"

object  spellcasting_object;
string  *spell_names;
int     cast_chance;

/*
 * Function name: add_spell
 * Description  : Adds a spell to our available spells
 * Arguments    : filename - the spell to add
 */
varargs void add_spell(mixed filename, function use_spell)
{
    // Make sure we have a spellcasting object, if not create one
    if(!objectp(spellcasting_object))
    {
        seteuid(getuid());
        spellcasting_object = 
            clone_object(FAERUN_LIB + "spellcasting_spells");
    }

    // Pass the add to the spellcasting object
    spellcasting_object->add_spell(filename);
}

/*
 * Function name: setup_spellcasting
 * Description  : Initialize the arrays with spells and move the spellcasting
 *              : object if we have it
 */
void setup_spellcasting()
{
    // Move the spellcasting object
    if(objectp(spellcasting_object))
    {
        spellcasting_object->move(this_object(), 1);
        spell_names = m_indexes(spellcasting_object->query_spell_map());
    }
}

/*
 * Function name: set_cast_chance
 * Description  : The percentage of chance we have that we start casting a
 *              : spell
 * Arguments    : percentage - the percentage
 */
void set_cast_chance(int percentage)
{
    cast_chance = percentage;
}

/*
 * Function name: query_cast_chance
 * Description  : How often do we cast
 * Returns      : a percentage
 */
int query_cast_chance()
{
    return cast_chance;
}

/*
 * Function name: spellcast_check
 * Description  : Called from the special_attack_spellcast function, allows
 *              : us to disable some spells
 * Arguments    : name - the name of the spell
 * Returns      : 0 when not using, 1 when using the spell
 */
int spellcast_check(string name)
{
    // Always use all spells
    return 1;
}

/*
 * Function name: special_attack_spellcast
 * Description  : Should be called from the special attack, will cast a 
 *              : spell
 * Arguments    : ob - the target of our attack
 * Returns      : 0 when no spell is cast, 1 when it is
 */
int special_attack_spellcast(object ob)
{
    string  *usable_spells;

    // Never start a new spell when we are already casting one
    if(objectp(this_object()->query_prop(LIVE_I_CONCENTRATE)))
        return 0;

    if(pointerp(spell_names))
        usable_spells = filter(spell_names, spellcast_check);

    // See if we have spells
    if(!sizeof(usable_spells))
        return 0;

    // See if we are lucky this round
    if(random(100) <= cast_chance)
    {
        // Lets us cast a spell
        this_object()->command("cast " + 
            spell_names[random(sizeof(usable_spells))] + " " +
            OB_NAME(ob));

        // Return success
        return 1;
    }

    return 0;
}

