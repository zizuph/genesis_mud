/*
 * /d/Kalad/common/guilds/khiraa/lp/obj/lp_med.c
 * Purpose    : This is the lich's medallion. It is the spell object, it contains all the spells.
 * Located    : Cloned into the lich's inventory.
 * Created By : Sarr 12.Apr.97
 * Modified By: Toby, 971007 (fixed indents)
 *	  	Toby, 971014 (fixed typos)
 *      Fysix, using the new spellcasting.c, Jan/Feb 1998
 *             plus reviewed all spells.
 */
#pragma strict_types
#pragma save_binary

#include "../../default.h"
#include "../../khiraa.h"
#include "../../magic.h"
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>

inherit "/std/armour";
inherit SPELLCASTING;
inherit "/d/Kalad/lib/magic/targeting";

// Debugging
#define DEBUG(x)    find_player("fysix")->catch_tell(x + "\n");

// Indexes in Spells array
#define LEVEL       0
#define NAME        1
#define DESC        2
#define CREATE_FUN  3
#define TARGET_FUN  4

// Prototypes
int     check_ok_cast(object caster);
void    destroy(object ob);
void    conc_message_chant(object caster, object *targets, string arg);
void    conc_message_hiss(object caster, object *targets, string arg);
void    conc_message_shriek(object caster, object *targets, string arg);
void    conc_message_burn_eyes(object caster, object *targets, string arg);

#include "../spells/lhealth.c"
#include "../spells/lterror.c"
#include "../spells/ltouch.c"
#include "../spells/lphantasm.c"
#include "../spells/ldrain.c"
#include "../spells/ldrainm.c"
#include "../spells/lshield.c"
#include "../spells/lgateway.c"
#include "../spells/linvis.c"
#include "../spells/lclone.c"
#include "../spells/lspeed.c"
#include "../spells/lprism.c"
#include "../spells/ltell.c"
#include "../spells/linfra.c"
#include "../spells/lcrow.c"
#include "../spells/ldark.c"
#include "../spells/lbanshee.c"
#include "../spells/lshadow.c"
#include "../spells/lbone.c"
#include "../spells/ltorment.c"
#include "../spells/lpain.c"
#include "../spells/lcorpse.c"
#include "../spells/lspectre.c"
#include "../spells/lalign.c"
#include "../spells/ldetect.c"
#include "../spells/lrespoi.c"
#include "../spells/lresdeath.c"
#include "../spells/lplague.c"
#include "../spells/lhands.c"
#include "../spells/lraise.c"
#include "../spells/lrot.c"

// Globals (see also the Spells array below)
int Mana_stored;

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
    int mylvl;

    if (IS_GUILD_MASTER(caster))
        return 1;

    if (caster->query_lp_order() == -1)
    {
        tell_object(caster, "You have been disgraced!\n");
        return 0;
    }

    return 1;
}

mixed
spell_fail()
{
    return "Your prayers were not heard by Him.\n";
}

// Concenctration message for some spells
// arg is the argument given to cast the spell
public void
conc_message_hiss(object caster, object *targets, string arg)
{
    write("You hiss a prayer to Him.\n");
    say(QCTNAME(caster) + " hisses something incomprehensible.\n");
}

// Concenctration message for some spells
// arg is the argument given to cast the spell
public void
conc_message_shriek(object caster, object *targets, string arg)
{
    write("You shriek a prayer to Him.\n");
    say(QCTNAME(caster) + " makes a loud shrieking sound.\n");
}

// Concenctration message for some spells
// arg is the argument given to cast the spell
public void
conc_message_chant(object caster, object *targets, string arg)
{
    write("You chant eerie prayers unto the Horror, invoking "+
    "powers from the Beyond.\n");
    say(QCTNAME(caster) + " fills the room with eerie chanting "+
    "as "+HE(caster)+" weaves "+HIS(caster)+" hands in strange "+
    "and mysterious patterns.\n");
}

// Concenctration message for some spells
// arg is the argument given to cast the spell
public void
conc_message_burn_eyes(object caster, object *targets, string arg)
{
    write("Your eyes burn red as you chant the proper prayer "+
        "for this spell, and your hands begin to glow purple.\n");
    say(QCTNAME(caster) + "'s eyes burn bright red as " +
        HE(caster) + " begins " + "to chant, and " +
        HIS(TP) + " hands turn purple.\n");
}


// Spells to be fixed:
/*
*/

// Add spells to the new owner, called when medallion
// enters a player
void
setup_my_spells(object owner)
{
    // All spells
    mixed spells = ({
        ({ 0, "ltell", "Speak Afar", create_spell_ltell,
            target_tell_message }),
        ({ 0, "lcrow", "Summon Crow", create_spell_lcrow, spell_target_caster }),
        ({ 1, "ltorment", "Torment", create_spell_ltorment,
            spell_target_one_present_object }),
        ({ 1, "lhealth", "Illusional Health", create_spell_lhealth,
            target_lhealth }),
        ({ 2, "ldark", "Create Darkness", create_spell_ldark, spell_target_caster  }),
        ({ 3, "linfra", "See in the Dark", create_spell_linfra, spell_target_caster }),
        ({ 4, "lspectre", "Summon Spectre", create_spell_lspectre,
           spell_target_one_distant_living  }),
        ({ 5, "lrot", "Rot Corpses", create_spell_lrot,
           spell_target_caster }),
        ({ 5, "lcorpse", "Corpse Scream", create_spell_lcorpse,
            spell_target_one_present_non_living  }),
        ({ 6, "lalign", "Detect Alignment", create_spell_lalign,
            spell_target_one_present_living  }),
        ({ 7, "lclone", "Clone", create_spell_lclone,
            spell_target_one_present_living }),
        ({ 8, "ldetect", "Identify Magic Item", create_spell_ldetect,
            spell_target_one_present_non_living  }),
        ({ 9, "linvis", "Invisibility", create_spell_linvis,
            spell_target_caster  }),
        ({ 10, "lplague", "Plague of Despair", create_spell_lplague,
            spell_target_one_other_present_living_or_enemy }),
        ({ 11,"lgateway","Gateway", create_spell_lgateway,
            spell_target_one_present_non_living }),
        ({ 12, "lspeed", "Unholy Speed", create_spell_lspeed,
            spell_target_caster }),
        ({ 13,"lshield", "Death Shield", create_spell_lshield,
            spell_target_one_present_living }),
        ({ 14, "lpain", "Cause More Pain", create_spell_lpain,
            spell_target_one_other_present_living_or_enemy }),
        ({ 15, "lrespoi", "Resist Poison Shield", create_spell_lrespoi,
            spell_target_one_present_living }),
        ({ 16, "lresdeath", "Resist Death Shield", create_spell_lresdeath,
            spell_target_one_present_living }),
        ({ 17, "lhands", "Hands of Doom", create_spell_lhands,
            spell_target_one_other_present_living_or_enemy  }),
        ({ 18, "lphantasm", "Phantasm",
            create_spell_lphantasm, spell_target_caster }),
        ({ 19, "lshadow", "Shadow Defense", create_spell_lshadow,
            spell_target_caster  }),
        ({ 20, "ltouch", "Ghoul Touch",
            create_spell_ltouch,
            spell_target_one_other_present_living_or_enemy }),
        ({ 21, "lbone", "Bone Shield", create_spell_lbone, spell_target_caster  }),
        ({ 22, "ldrain", "Life Drain", create_spell_ldrain,
            spell_target_one_other_present_living_or_enemy }),
        ({ 23, "lterror", "Create Terror and Madness",
            create_spell_lterror, spell_target_caster }),
        ({ 23, "ldrainm", "Life Drain Myself", create_spell_ldrainm,
            target_ldrainm }),
        ({ 24, "lbanshee", "Banshee Wail", create_spell_lbanshee,
            target_lbanshee  }),
        ({ 25, "lraise", "Raise the Dead", create_spell_lraise,
            target_lraise  }),
        ({ 25, "lprism", "Prism Shield", create_spell_lprism,
            spell_target_one_present_living }),
        });

    int i,
        lvl = owner->query_guild_order(),
        n = sizeof(spells);

    if(IS_GUILD_MASTER(owner))
        lvl = 26;

    // Add all the spells the owner is allowed to have
    for (i = 0; i < n; i++)
        if (lvl > spells[i][LEVEL])
            add_spell(spells[i][NAME], spells[i][DESC],
                spells[i][CREATE_FUN], spells[i][TARGET_FUN]);
}

string
query_mana_stored()
{
    switch(Mana_stored)
    {
        case 0:
            return "You notice the skull's eyes are a pale white color.\n";
        break;
        case 1..100:
            return "You notice the skull's eyes are a light red color.\n";
        break;
        case 101..200:
            return "You notice the skull's eyes are a deep rose color.\n";
        break;
        case 201..300:
            return "You notice the skull's eyes are pure red.\n";
        break;
        case 301..400:
            return "You notice the skull's eyes are a deep red color.\n";
        break;
        case 401..500:
            return "You notice the skull's eyes are a bright red color.\n";
        break;
        case 501..600:
            return "You notice the skull's eyes are a fiery red color.\n";
        break;
        default:
            return "You notice the skull's eyes are a buggy color.\n";
    }
    return "You notice the skull's eyes are a buggy color.\n";
}

void
create_armour()
{
    set_name("medallion");
    add_name("skull-medallion");
    add_name("lich_medallion");

    add_adj("dark");
    add_adj("eerie");

    set_short("eerie dark skull-medallion");

    set_long("The most prominent feature of this medallion is the "+
        "bone-white grim looking skull in the center of a black steel "+
        "plate. The plate itself hangs on a chain that you can wear "+
        "around your neck. The skull's eyes contain two red jewels that "+
        "shine in the light. On the back of the plate, you see blood-red "+
        "runes, which you read as praises to the Nameless Horror. At the "+
        "very bottom, you also see 'help khiraa'.\n"+
        "@@query_mana_stored@@");

    set_ac(1);
    set_at(A_NECK);

    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_SELL,"You don't dare to do such a thing.\n");
    add_prop(OBJ_M_NO_DROP,"You don't dare to do such a thing.\n");

    setuid();
    seteuid(getuid());
}

// Put mana into the medallion
int
do_suck(string str)
{
    NF("Add mana to medallion?\n");
    if(str != "mana to medallion")
        return 0;
    NF("You don't have the mana to add.\n");
    if(TP->query_mana() <= 100)
        return 0;
    NF("The "+short()+" cannot handle that much mana.\n");
    if(Mana_stored >= 600)
        return 0;
    Mana_stored += 100;
    TP->add_mana(-100);

    write("You grasp the "+short()+" and let your mind link with it.\n");
    write("You feel your mind drain.\n");
    say(QCTNAME(TP)+" grasps the "+short()+" tightly.\n");
    tell_room(ENV(TP),"The "+short()+"'s eyes glow softly for a moment.\n");

    return 1;
}

// Get mana out of the medallion
int
do_drain(string str)
{
    NF("Suck medallion?\n");
    if(str != "medallion")
        return 0;
    NF("The medallion doesn't have any mana!\n");
    if(Mana_stored <= 0)
        return 0;
    Mana_stored -= 100;
    TP->add_mana(100);
    write("You grasp the "+short()+" and feel mana enter your body.\n");
    say(QCTNAME(TP)+" grasps the "+short()+" and grins evilly.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_suck, "ladd");
    add_action(do_drain, "lsuck");
}

void
message(object ob)
{
    tell_object(ob,"You rise from the grave, unholy thoughts on "+
        "your mind as you prepare to further the will of Him.\n");
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
        if (!IS_LP(to) && !IS_GUILD_MASTER(to))
            set_alarm(4.0, 0.0, &destroy(to));
        else
        {
            // Wait with setting up the spells till the player's
            // shadow is loaded too
            set_alarm(1.0, 0.0, &setup_my_spells(to));

            add_spell_object(to);

            // Guild masters don't need to add mana for testing purposed
            if (IS_GUILD_MASTER(to))
                Mana_stored = 1000000;
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
