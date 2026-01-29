/*
 * /d/Kalad/common/guilds/khiraa/dk/obj/dk_medallion.c
 * Purpose    : This is the death knight's medallion. It is the spell
 *              object, it contains all the spells.
 * Located    : Cloned into the lich's inventory.
 * Created By : Sarr 12.Apr.97
 * Modified By: Toby, 971007 (fixed indents)
 *	  	Toby, 971014 (fixed typos)
 *      Sarr, using the new spellcasting.c, Feb 1998
 *
 */
#pragma strict_types
#pragma save_binary

#include "../../default.h"
#include "../../khiraa.h"
#include "../../magic.h"
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <tasks.h>

inherit "/std/armour";
inherit SPELLCASTING;
inherit "/d/Kalad/lib/magic/targeting";

// Indexes in Spells array
#define LEVEL       0
#define NAME        1
#define DESC        2
#define CREATE_FUN  3
#define TARGET_FUN  4


// Prototypes
int check_ok_cast(object caster);
void destroy(object ob);

// All spells
#include "../spells/ktorment.c"
#include "../spells/kinfra.c"
#include "../spells/kcrow.c"
#include "../spells/kfoul.c"
#include "../spells/kflame.c"
#include "../spells/kdark.c"
#include "../spells/kfear.c"
#include "../spells/kblade.c"
#include "../spells/karmour.c"
#include "../spells/kbones.c"
#include "../spells/ktell.c"

// Don't recover
int
query_recover()
{
    return 0;
}


// Guild masters don't have to have any ingredients
varargs mixed
find_components(object caster, mixed component_list,
    object *item_list)
{
    return (IS_GUILD_MASTER(caster) ? ({}) :
        ::find_components(caster, component_list, item_list));
}

// Check if the caster can cast the spell
int
check_ok_cast(object caster)
{
    if (IS_GUILD_MASTER(caster))
        return 1;

    if (caster->query_lp_order() == -1)
    {
        tell_object(caster, "You have been disgraced!\n");
        return 0;
    }
}

// Add spells to the new owner, called when medallion
// enters a player
void
setup_my_spells(object owner)
{
    int i,n,lvl;
    mixed Spells = ({

    ({ 3, "kinfra", "See Within Darkness",
        create_spell_kinfra, spell_target_caster }),
    ({ 2, "ktorment", "Torment", create_spell_ktorment,
        spell_target_one_present_object }),
    ({ 1, "kcrow", "Summon crow",
        create_spell_kcrow, spell_target_caster }),
    ({ 5, "kfoul", "Aura of Putridness",
        create_spell_kfoul, spell_target_caster }),
    ({ 7, "kflame", "Flaming Arrow",
        create_spell_kflame, spell_target_one_present_living }),
    ({ 4, "kdark", "Create Darkness", create_spell_kdark,
        spell_target_caster }),
    ({ 6, "kfear", "Aura of Fear", create_spell_kfear,
        spell_target_present_livings }),
    ({ 8, "kblade", "Death Blade", create_spell_kblade,
        spell_target_one_present_object }),
    ({ 9, "karmour", "Death Armour", create_spell_karmour,
        spell_target_one_present_object }),
    ({ 10, "kbones", "Bone Shield", create_spell_kbones,
        spell_target_caster }),
    ({ 1, "ktell", "Tell Afar", create_spell_ktell,
        target_tell_message })
    });

    lvl = owner->query_guild_order();
    n = sizeof(Spells);

    if(IS_GUILD_MASTER(owner))
        lvl = 11;

    // Add all the spells the owner is allowed to have
    for (i = 0; i < n; i++)
        if (lvl >= Spells[i][LEVEL])
            add_spell(Spells[i][NAME], Spells[i][DESC],
                Spells[i][CREATE_FUN], Spells[i][TARGET_FUN]);
}

void
create_armour()
{
    set_name( ({"ring", "skull-ring", "death_knight_medallion"}) );
    set_adj( ({"black", "ghastly" }) );

    set_short("black ghastly skull-ring");

    set_long("You gaze upon a magnificant ring of finely wrought obsidian "+
        "that has been magically strengthened. It gleams with an eerie "+
        "light that seems to flicker when you move it around. A ghastly "+
        "looking skull with its mouth open in a silent scream stares back "+
        "at you with eyes of red jewels. The eyes seem to pulse with an "+
        "unspeakable evil that you know belongs to that of the Nameless "+
        "Horror. Etched on one side are runes that read 'help khiraa'.\n");

    set_ac(1);
    set_at(A_ANY_FINGER);

    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_SELL,"You don't dare to do such a thing.\n");
    add_prop(OBJ_M_NO_DROP,"You don't dare to do such a thing.\n");

    setuid();
    seteuid(getuid());
}

void
destroy(object ob)
{
    tell_object(ob, "The " + short() + " explodes in your hands!\n");
    remove_object();
}

// Add spells to the object I am entering
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (living(to))
    {
        if (!IS_DK(to) && !IS_GUILD_MASTER(to))
            set_alarm(4.0, 0.0, &destroy(to));
        else
        {
            // Wait with setting up the spells till the player's
            // shadow is loaded too
            set_alarm(1.0, 0.0, &setup_my_spells(to));

            add_spell_object(to);
        }
    }
}

// Remove the spells
void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    if (living(env))
        remove_spell_object(env);
}
