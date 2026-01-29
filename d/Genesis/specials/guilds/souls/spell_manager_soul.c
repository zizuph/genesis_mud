/*
 * Command Soul for Management of Spells and Effects
 *
 * This is the command soul that every every caster guild should
 * add if it's not there. It will provide common functionality like
 * listing active effects and dispelling them and providing casting
 * of spells based on the new spell system.
 *
 * Created by Petros, October 2009
 */

#pragma strict_types

#include <cmdparse.h>
#include <language.h>
#include <ss_types.h>
#include <state_desc.h>
#include <macros.h>

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";
inherit "/d/Genesis/specials/calculations";

// Defines
#define     LIVE_O_MAINTAINED_EFFECTS   "_live_o_maintained_effects"

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id() 
{ 
    return "Genesis Spell Manager Soul"; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
public int 
query_cmd_soul() 
{ 
    return 1;
}
  
public mapping
query_cmdlist()
{
    return ([
        /* Command name : Function name */
        "help"              : "spell_help",
        "dispel"            : "dispel_spell",
        "divine"            : "divine_item",
        "spelleffects"      : "list_spell_effects",
        "prayereffects"     : "list_spell_effects",
        "spellnotes"        : "show_spell_notes",
    ]);
}

int spell_help(string str)
{
    string path = MASTER_OB(this_object()) + "_help/" + str;
    if (file_size(path) > 0)
    {
	    this_player()->more(path, 1);
	    return 1;
    }
    // We will defer to other notify_fails on help.
    return 0;
}


/*
 * Function name: compare_living_to_spell_enhancer
 * Description  : Compares natural spell ability of living to unarmed enhancer.
 * Arguments    : object living1 - the left hand side to compare.
 *                object enh2 - the right hand side to compare.
 */
void
compare_living_to_spell_enhancer(object living1, object enh2)
{
    /* Spellcraft and divination are both used, so use half their average */
    int skill = (this_player()->query_skill(SS_FORM_DIVINATION) +
        this_player()->query_skill(SS_SPELLCRAFT)) / 4;
    int seed = atoi(OB_NUM(living1)) + atoi(OB_NUM(enh2));
    int stat1;
    int stat2;
    string str1;
    string str2;
    string print1;
    string print2;
    
    str2 = "the " + enh2->short(this_player());

    stat1 = get_natural_spellpower(living1);

    if (this_player() == living1)
    {
        str1 = "your natural talent";
    }
    else
    {
        str1 = living1->query_the_possessive_name() + " natural talent";
    }
    /* Use high precision for hit up to skill, low precision for remainder */
    int high_precision;
    int low_precision;

    /* Find the average of the query_hit up to their skill */
    high_precision = (stat1 > skill
        ? skill : stat1);
    high_precision += (enh2->query_magic_spellpower() > skill
        ? skill : enh2->query_magic_spellpower());
    high_precision /= 2;

    /* Find the average of the query_hit above their skill */
    low_precision = (stat1 > skill
        ? stat1 - skill : 0);
    low_precision += (enh2->query_magic_spellpower() > skill
        ? enh2->query_magic_spellpower() - skill : 0);
    low_precision /= 2;

    /* Gather the to-hit values. */
    stat1 = stat1 + random(high_precision / 10, seed)
        + random(low_precision / 2, seed + 1);
    stat2 = enh2->query_magic_spellpower()
        + random(high_precision / 10, seed + 27)
        + random(low_precision / 2, seed + 28);

    if (stat1 > stat2)
    {
        stat1 = (100 - ((80 * stat2) / stat1));
        print1 = str1;
        print2 = str2;
    }
    else
    {
        stat1 = (100 - ((80 * stat1) / stat2));
        print1 = str2;
        print2 = str1;
    }

    stat1 = ((stat1 * sizeof(SD_COMPARE_PEN)) / 100);
    write("Spell damage enhanced by " + print1 + " is " +
        SD_COMPARE_PEN[((stat1 > 3) ? 3 : stat1)] + " " +
        print2 + ".\n");
}


void
compare_spell_enhancer(object enh1, object enh2)
{
    /* Spellcraft and divination are both used, so use half their average */
    int skill = (this_player()->query_skill(SS_FORM_DIVINATION) +
        this_player()->query_skill(SS_SPELLCRAFT)) / 4;
    int seed = atoi(OB_NUM(enh1)) + atoi(OB_NUM(enh2));
    int swap;
    int stat1;
    int stat2;
    string str1;
    string str2;
    string print1;
    string print2;
    object tmp;

    /* Always use the same order. After all, we don't want "compare X with Y"
     * to differ from "compare Y with X".
     */
    if (OB_NUM(enh1) > OB_NUM(enh2))
    {
        tmp = enh1;
        enh1 = enh2;
        enh2 = tmp;
        swap = 1;
    }

    str1 = enh1->short(this_player());
    str2 = enh2->short(this_player());

    /* Some people will want to compare items with the same description. */
    if (str1 == str2)
    {
        if (swap)
        {
            str1 = "first " + str1;
            str2 = "second " + str2;
        }
        else
        {
            str2 = "first " + str2;
            str1 = "second " + str1;
        }
    }

    /* Use high precision for hit up to skill, low precision for remainder */
    int high_precision;
    int low_precision;

    /* Find the average of the query_hit up to their skill */
    high_precision = (enh1->query_magic_spellpower() > skill
        ? skill : enh1->query_magic_spellpower());
    high_precision += (enh2->query_magic_spellpower() > skill
        ? skill : enh2->query_magic_spellpower());
    high_precision /= 2;

    /* Find the average of the query_hit above their skill */
    low_precision = (enh1->query_magic_spellpower() > skill
        ? enh1->query_magic_spellpower() - skill : 0);
    low_precision += (enh2->query_magic_spellpower() > skill
        ? enh2->query_magic_spellpower() - skill : 0);
    low_precision /= 2;

    /* Gather the to-hit values. */
    stat1 = enh1->query_magic_spellpower()
        + random(high_precision / 10, seed)
        + random(low_precision / 2, seed + 1);
    stat2 = enh2->query_magic_spellpower() 
        + random(high_precision / 10, seed + 27)
        + random(low_precision / 2, seed + 28);

    if (stat1 > stat2)
    {
        stat1 = (100 - ((80 * stat2) / stat1));
        print1 = str1;
        print2 = str2;
    }
    else
    {
        stat1 = (100 - ((80 * stat1) / stat2));
        print1 = str2;
        print2 = str1;
    }

    stat1 = ((stat1 * sizeof(SD_COMPARE_PEN)) / 100);
    write("Spell damage enhanced by the " + print1 + " is " +
        SD_COMPARE_PEN[((stat1 > 3) ? 3 : stat1)] + " the " +
        print2 + ".\n");
}

int
divine_item(string str)
{
    string str1;
    string str2;
    object *oblist;
    object obj1;
    object obj2;
    int str1_is_hand;

    if (!strlen(str) ||
        sscanf(str, "%s with %s", str1, str2) != 2)
    {
        notify_fail("Divine <whom/what> with <whom/what>?\n");
        return 0;
    }

    str1_is_hand = str1 == "hands" || str1 == "hand" || str1 == "magic" ||
       str1 == "my magic";

    /* If we compare 'hands', then we are the left
     * party.
     */
    if (str1_is_hand)
    {
        obj1 = this_player();
    }
    else
    /* Else, see the left hand side of whom/what we want to compare. */
    {
        oblist = parse_this(str1, "[the] %i");
        if (sizeof(oblist) != 1)
        {
            notify_fail("Divine <whom/what> with <whom/what>?\n");
            return 0;
        }
        obj1 = oblist[0];
    }

    /* Get the right hand side of what we want to compare. */
    oblist = parse_this(str2, "[the] %i");
    if (sizeof(oblist) != 1)
    {
        notify_fail("Divine <whom/what> with <whom/what>?\n");
        return 0;
    }
    obj2 = oblist[0];

    /* Yes, people will want to do the obvious. */
    if (obj1 == obj2)
    {
        notify_fail("It is pointless to divine something with itself.\n");
        return 0;
    }

    /* Compare the stats of two livings or
     * fists or feet against unarmed enhancers.
     */
    if (living(obj1) && obj2->query_spellpower_enhancer())
    {
        compare_living_to_spell_enhancer(obj1, obj2);
        return 1;
    }
    
    int compared_spellpower = 0;
    if (obj1->query_spellpower_enhancer() && 
        obj2->query_spellpower_enhancer())
    {
        compare_spell_enhancer(obj1, obj2);
        return 1;
    }
    
    notify_fail("It does not seem possible to divine " +
        (obj1 == this_player() ? "yourself" : LANG_THESHORT(obj1))
        + " with " + LANG_THESHORT(obj2) + ".\n");
    return 0;
}


/*
 * Function:    query_magic_effects
 * Description: Returns a list of magic effects that the player has
 *              cast.
 */
public object *
query_magic_effects(object player)
{
    object * effects = filter(player->query_prop(LIVE_O_MAINTAINED_EFFECTS),
                              &->query_spell_effect_object());
    if (!pointerp(effects))
    {
        effects = ({ });
    }
    else
    {        
        effects -= ({ 0 });
    }
     
    return effects;   
}

/*
 * Function:    query_affecting_desc
 * Description: Tries to describe the target of the maintained effect
 */
public string
query_affecting_desc(object player, object target)
{
    string affecting;
    
    if (!objectp(target))
    {
        affecting = "unknown";
    }
    else if (player == target)
    {
        affecting = "self";
    }
    else if (living(target))
    {
        affecting = target->query_The_name(player);
    }
    else
    {
        affecting = target->short();
        object owner = environment(target);
        if (objectp(owner) && living(owner))
        {
            if (owner == player)
            {
                affecting += " on self";
            }
            else
            {            
                affecting += " on " + environment(target)->query_The_name(player);
            }
        }
    }
    
    if (!strlen(affecting))
    {
        affecting = "unknown";
    }

    return affecting;
}

public int
dispel_all_effects(object player)
{
    if (!objectp(player))
    {
        return 0;
    }

    object * effects = query_magic_effects(player);    
    if (!sizeof(effects))
    {
        return 0;
    }

    // Dispel everything
    foreach (object effect : effects)
    {
        player->catch_tell("You stop concentrating on maintaining " 
            + effect->query_spell_effect_name() + ".\n");
        effect->dispel_effect(player);
    }        
        
    return sizeof(effects);
}

public int
dispel_spell(string str)
{
    object player = this_player();
    object * effects = query_magic_effects(player);
    
    if (!sizeof(effects))
    {
        notify_fail("You are not maintaining any active spell effects to "
            + "dispel.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("What would you like to dispel?\n");
        return 0;
    }

    if (lower_case(str) == "all")
    {
        // The player wants to dispel everything.
        int num_dispelled = dispel_all_effects(player);
        if (num_dispelled == 0)
        {
            write("For some reason, you were not able to dispel anything!\n");
        } 
        else if (num_dispelled == 1)
        {
            write("You have dispelled " + LANG_NUM2WORD(num_dispelled) + 
            " spell effect.\n");
        } 
        else
        {
            write("You have dispelled " + LANG_NUM2WORD(num_dispelled) + 
            " spell effects.\n");
        }
        return 1;
    }

    int effect_index;
    string effect_name, effect_target;
    if (sscanf(str, "%d", effect_index))
    {
        object effect;
        if (!effect_index || effect_index > sizeof(effects))
        {
            notify_fail("There is no spell effect with that number.\n");
            return 0;
        }
        effect = effects[effect_index - 1];

        write("You stop concentrating on maintaining " 
            + effect->query_spell_effect_name() + ".\n");

        effect->dispel_effect(player);
        return 1;
    }
    else if (sscanf(str, "%s on %s", effect_name, effect_target))
    {
        effect_target = lower_case(effect_target);
        effects = filter(effects, &operator(==)(effect_name)
            @ &->query_spell_effect_name());
        foreach (object effect : effects)
        {
            // We have the effect, now we need to verify the target
            object target = PARSE_COMMAND_ONE(effect_target, environment(effect->query_effect_target()), "[the] %i");            
            if (objectp(target) && target == effect->query_effect_target())
            {
                write("You stop concentrating on maintaining " 
                    + effect->query_spell_effect_name() + " on " + effect_target + ".\n");
                effect->dispel_effect(player);
                return 1;
            }
        }
                
        notify_fail("There is no spell effect " + effect_name
            + " on " + effect_target + ".\n");
        return 0;
    } 
    else if (sscanf(str, "%s", effect_name))
    {
        effect_name = lower_case(effect_name);
        effects = filter(effects, &operator(==)(effect_name) @ &->query_spell_effect_name());
        if (sizeof(effects) == 0)
        {
            notify_fail("You are not maintaining anything named '" + effect_name + "'.\n");
            return 0;
        }
        foreach (object effect : effects)
        {
            string affecting = query_affecting_desc(player, effect->query_effect_target());
            write("You stop concentrating on maintaining " 
                  + effect->query_spell_effect_name() + " on " + affecting + ".\n");
            effect->dispel_effect(player);
        }
        return 1;
    }
    
    notify_fail("Dispel <what> on <who>?\n");
    return 0;
}

/*
 * Function:    list_spell_effects
 * Description: This function gets called when the command <spelleffects>
 *              executes. It goes through all the currently maintained
 *              effects and presents it to the player.
 */
public int
list_spell_effects(string str)
{
    object player = this_player();
    object * effects = query_magic_effects(player);
    
    int bViewOtherPlayer = 0;
    if (player->query_wiz_level() && strlen(str))
    {
        // Wizards are allowed to see the spelleffects for players.
        bViewOtherPlayer = 1;
        str = lower_case(str);
        if (!objectp(player = find_player(str)))
        {
            notify_fail("There is no player named " + capitalize(str)
                + " that you can view spelleffects for.\n");
            return 0;
        }
        effects = query_magic_effects(player);
    }
    
    int index = 1;
    string message_text = "Currently Active Magical Effects\n\n";
    if (bViewOtherPlayer)
    {
        message_text = "Currently Active Magical Effects on " 
            + capitalize(player->query_real_name()) + "\n\n";
    }
    message_text += sprintf("### %-15s %-20s %-20s %-5s\n", "Name", "Description", "Target", "Notes");
    message_text += sprintf("--- %'-'15s %'-'20s %'-'20s %'-'|5s\n", "", "", "", "");
    foreach (object effect : effects)
    {
        string affecting = query_affecting_desc(player, 
            effect->query_effect_target());
        if (effect->query_about_to_expire())
        {
            affecting += " *";
        }
        
        message_text += sprintf("%-3d %-=15.15s %-=20.20s %-=20.20s %|=5.5s\n", 
            index++,
            effect->query_spell_effect_name(), 
            effect->query_spell_effect_desc(),
            affecting,
            strlen(effect->query_spell_effect_notes()) ? "Yes" : "No");
    }
    if (!sizeof(effects))
    {
        message_text += sprintf("%|=64s\n", "-= No Active Effects =-"); 
    }
        
    message_text += "\n* indicates effect is about to expire\n";
    message_text += "\nTo see spell notes:    spellnotes <num>\n";
    message_text += "\nTo dispel an effect:   dispel <num>\n";
    message_text += "                       dispel <name>\n";
    message_text += "                       dispel <name> on <target>\n";
    message_text += "\nTo dispel all effects: dispel all\n";
    string additional_messages = player->customize_guild_spell_effect_messages(effects, message_text);
    if (strlen(additional_messages))
    {
        message_text += additional_messages;
    }
    
    write(generate_scroll_text(message_text, "Genesis Magic System"));
    
    return 1;
}

/*
 * Function:    show_spell_notes
 * Description: This function gets called when the command <spellnotes>
 *              executes. It goes through all the currently maintained
 *              effects and presents the requested note to the player
 */
public int
show_spell_notes(string str)
{
    object player = this_player();
    object * effects = query_magic_effects(player);
    
    if (!sizeof(effects))
    {
        notify_fail("You are not maintaining any active spell effects at the "
            + "moment so there are no notes to read.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Which spell note do you wish to see?\n");
        return 0;
    }

    int effect_index;
    string effect_name, effect_target;
    if (sscanf(str, "%d", effect_index))
    {
        object effect;
        if (!effect_index || effect_index > sizeof(effects))
        {
            notify_fail("There is no spell effect with that number.\n");
            return 0;
        }
        effect = effects[effect_index - 1];
        // Found the right effect.
        string message_text = "Spell Details for " 
            + capitalize(effect->query_spell_effect_name()) + "\n\n";
        string affecting = query_affecting_desc(player, 
            effect->query_effect_target());
        message_text += sprintf("%-20s: %-=50.50s\n", "Name", effect->query_spell_effect_name());
        message_text += sprintf("%-20s: %-=50.50s\n", "Description", effect->query_spell_effect_desc());
        message_text += sprintf("%-20s: %-=50.50s\n", "Target", affecting);
        message_text += sprintf("%-20s: %-=50.50s\n", "About to Expire", effect->query_about_to_expire() ? "Yes" : "No");
        message_text += sprintf("%-20s: %-=50.50s\n", "Notes", strlen(effect->query_spell_effect_notes()) ? effect->query_spell_effect_notes() : "None"); 
        write(generate_scroll_text(message_text, "Genesis Magic System"));        
        return 1;
    }
    
    notify_fail("Spellnotes <number>?\n");
    return 0;
}
