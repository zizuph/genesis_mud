/* 
 * Magical staff wielded by the ogre magi outside Sparkle.
 * Designed for new and small players, so has wield
 * restrictions based on player size.
 *
 * For other examples of how to include standardised spells
 * in to items that can be used by npcs or players, see
 * /d/Genesis/specials/examples/
 *
 * Arman - January 2021
 */

inherit "/std/weapon";
inherit "/d/Genesis/specials/examples/std_magic_lib";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>
#include <cmdparse.h>

#define PETRIFY   "/d/Genesis/start/human/obj/ogre_magi_staff_spell"
/* 
 * Normally, at_will_harm damage spells shouldn't be added to items.
 * 
 * Petrify is an at_will_harm spell. Normally, allowable spells
 * for such devices as this staff should use the harm spell base,
 * /d/Genesis/specials/std/spells/harm.c, but as this is a staff
 * for newbies the mana cost of harm is quite high.
 *
 * Arman, January 2021
 */

void
create_weapon()
{
    set_name("staff");
    add_name("_medusa_staff");
    set_adj("medusa");
    set_short("staff of the medusa");
    set_long("This is a long thin staff of grey stone. Atop " +
        "has been carved the head of a medusa, its " +
        "hair consisting of fanged snakes that hiss in frozen " +
        "silence. Black runes have been carved along the length " +
        "of the staff.\n");

    add_item(({"black runes","runes"}),
        "Black runes have been carved along the haft of this staff " +
        "in the language of the ogrekin. You may be able to read " +
        "the runes if your language skill is good enough.\n");
    add_cmd_item(({"runes","black runes","the runes"}),
        "read", "@@read_runes");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This staff has captured the spirit " +
         "of a maternal medusa. The medusa is resentful of its " +
         "imprisonment and refuses to be wielded or used by anyone other " +
         "than the ogre mage who bound her. The exception is the small " +
         "and weak, where her maternal desire to guide the young outweighs " +
         "her resentment.\n", 5, "In the hands of a young adventurer, " +
         "this staff may 'petrify' enemies with a blast of earth magic. " +
         "Superior amateur skill in earth magic and spellcraft is " +
         "required to use the magic of the staff.\n", 15, 
         "The spirit of the medusa refuses to allow experienced " +
         "adventurers to wield this staff or use her powers to " +
         "petrify.\n", 45}));
    add_prop(OBJ_S_WIZINFO, "This magical staff is wielded by the ogre " +
         "magi (/d/Genesis/start/human/obj/ogre_mage.c) outside of " +
         "Sparkle. It is designed to allow new and small players to " +
         "experience basic magical spell items, and is restricted " +
         "to those with stats defined as SD_IS_NEWBIE.\n");

    set_default_weapon(30, 20, W_POLEARM, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);

    add_magic_obj_spell("%s", ({ "petrify" }), PETRIFY);

    set_wf(this_object());
    seteuid(getuid(this_object()));
    
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(30);   
}

string
read_runes()
{
    if(this_player()->query_skill(SS_LANGUAGE) < 10)
    {
        write("You need at least superior student language skill to " +
            "be able to read these ogrekin runes.\n");
        return "";
    }

    write("You are able to translate a command word from the " +
        "ogrekin runes carved along the length of the staff - " +
        "'petrify'.\n");
    return "";
}

void
wield_message(object wielder)
{
    if((this_player()->query_skill(SS_SPELLCRAFT) < 20) &&
        (this_player()->query_skill(SS_ELEMENT_EARTH) < 20))
    {
        write("The staff of the medusa seems to hum as you " +
            "wield it, and you hear a sibilant hiss resonate " +
            "inside your head: To unlock my powerssss, you " +
            "must train further in earth magic and spellcraft " +
            "skills! Seek out training in the villages of " +
            "Green Oaks and Sparkle!\n");
        return;
    }
    else if((this_player()->query_skill(SS_SPELLCRAFT) < 20))
    {
        write("The staff of the medusa seems to hum as you " +
            "wield it, and you hear a sibilant hiss resonate " +
            "inside your head: To unlock my powerssss, you " +
            "must train further in spellcraft skills! Seek " +
            "training at the Adventurers Guild in Sparkle!\n");
        return;
    }
    else if((this_player()->query_skill(SS_ELEMENT_EARTH) < 20))
    {
        write("The staff of the medusa seems to hum as you " +
            "wield it, and you hear a sibilant hiss resonate " +
            "inside your head: To unlock my powerssss, you " +
            "must train further in earth magic! Seek training " +
            "at the Academy in the elven town of Green Oaks!\n");
        return;
    }

    write("The eyes in the head of the staff of the medusa " +
        "glow a malevolent green briefly, and the feeling of " +
        "a serpentine embrace coils around you.\n");
    say("The eyes in the head of the staff of the medusa " +
        "wielded by " +QTNAME(wielder)+ " glow a malevolent " +
        "green briefly, before fading back to a stony grey.\n");

    return;
}

mixed 
wield(object what)
{
    // Only newbies and immortals may wield this staff.
    if(!SD_IS_NEWBIE(this_player()) && !this_player()->query_wiz_level())
        return "The staff writhes in your hands like a snake, " +
            "refusing to allow you to wield it!\n";

    set_alarm(1.5, 0.0, &wield_message(this_player()));

    return 0;
}

public status
verify_magic_obj_spell_cast(string arg, object spell)
{
    if(!this_object()->query_wielded())
    {
        write("You have to be wielding the staff of the medusa to " +
            "activate it.\n");
        return 0;
    }

    if(this_player()->query_prop(LIVE_O_CONCENTRATE))
    {
        this_player()->catch_tell("You are currently concentrating on " +
            "casting another spell, and cannot activate the staff of " +
            "the medusa.\n");
        return 0;
    }

    return 1;
}

void
init()
{
    ::init();
    
    /* required to use spell_commands from the std_magic_lib */
    init_spell_commands();
}

/*
 * Function:    cmd_parse_spell_action
 * Description: Parses actions for spell commands and targets to trigger
 *              spells added to the item.
 * Argument:    string arg - the argument which is parsed
 */
public int
cmd_parse_spell_action(string arg)
{
    object tar, *oblist, *enemies;

    // Added so if there is no argument it defaults to the enemy
    // currently being fought.
    if(!strlen(arg))
    {
        if(objectp(this_player()->query_attack()))
        {
            tar = this_player()->query_attack();
            arg = tar->query_name();
        }
    }

    int result = ::cmd_parse_spell_action(arg);
    
    if (!result)
        notify_fail("Petrify who with the staff of the medusa?\n");
    
    return result;
} /* cmd_parse_spell_action */

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
