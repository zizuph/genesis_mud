/*
 * frustum.c
 *
 * A special skill trainer that uses gems rather than coins.
 *
 * Copyright (c) ?? 1998 ?? by Shiva
 *
 * Revision History:
 *     10-3-00: (Gorboth) - added OBJ_M_NO_GET prop
 */

inherit "/std/container";
inherit "/d/Emerald/lib/train";

#include "/d/Genesis/gems/gem.h"
#include "/d/Emerald/common/guild/vamp/guild.h"
#include "/d/Emerald/sys/skills.h"

#include <macros.h>
#include <money.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>

#define SK_ADD(sknum, desc, name, level) \
    sk_add_train(sknum, desc, name, 0, level)

mapping chosen_weapon = ([]);
mapping cost_factor = ([]);

public void restore_weapon_data();

public void
create_container()
{
    set_name("frustum");
    add_adj("black");
    add_adj("stone");
    add_adj("plain");

    set_short("black stone frustum");
    set_long("A plain, black, stone frustum, about a meter high.  A " + 
        "recess has been carved into the top.\n");

    add_item("recess", "A recess is cut about five centimeters into the " +
       "top of the frustum.\n");

    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 103000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_MAX_VOLUME, 13000);
    add_prop(CONT_I_HEIGHT, 100);
    add_prop(OBJ_M_NO_GET, "The frustum is fixed in place.\n");
 
    create_skill_raise();

    restore_weapon_data();

    SK_ADD(SS_DEFENSE, "dodge attacks", "defense", 100);
    SK_ADD(SS_PARRY, "parry attacks", "parry", 15);
    SK_ADD(SS_BLIND_COMBAT, "fight while blind", "blindfighting", 40);
    SK_ADD(SS_SNEAK, "sneak", "sneak", 75);
    SK_ADD(SS_AWARENESS, "perceive", "awareness", 100);
    SK_ADD(SS_HIDE, "hide", "hide", 75);
    SK_ADD(SS_APPR_MON, "appraise enemies", "appraise enemy", 75);
    SK_ADD(SS_HUNTING, "hunt", "hunting", 75);
    SK_ADD(SS_UNARM_COMBAT, "fight unarmed", "unarmed combat", 90);
    SK_ADD(SS_WEP_SWORD, "fight with swords", "sword", 90);
    SK_ADD(SS_WEP_KNIFE, "fight with knives", "knife", 90);
    SK_ADD(SS_WEP_POLEARM, "fight with polearms", "polearm", 90);
    SK_ADD(SS_WEP_CLUB, "fight with clubs", "club", 90);
    SK_ADD(SS_WEP_AXE, "fight with axes", "axe", 90);

    SK_ADD(SS_LANGUAGE, "speak foreign and archaic languages", "language", 60);
    SK_ADD(SS_TRADING, "make shrewd deals", "trading", 60);
    SK_ADD(SS_SPELLCRAFT, "understand magical theory", "spellcraft", 50);
    SK_ADD(SS_ELEMENT_DEATH, "manipulate the element of death",
           "death magic", 40);
    SK_ADD(SS_ELEMENT_AIR, "manipulate the element of air", "air magic", 40);
    SK_ADD(SS_FORM_ILLUSION, "produce illusions", "illusion", 40);
    SK_ADD(SS_FORM_ENCHANTMENT, "produce enchantments", "enchantment", 40);
    SK_ADD(SS_FORM_ABJURATION, "resist and dispel magic", "abjuration", 60);

#undef SS_VAMP_FOCUS
#ifdef SS_VAMP_FOCUS
    sk_add_train(SS_VAMP_FOCUS, "focus power", "focus", 200, 50);
#endif

#ifdef SS_VAMP_SLASH
    sk_add_train(SS_VAMP_SLASH, "slash a victim", "slash", 80, 100);
#endif
}

public void
restore_weapon_data()
{
    setuid();
    seteuid(getuid());
    restore_object(WEAPON_SAVE);
}

/*
 * Function name: query_weapon_focus_chosen
 * Description:   Gets the weapon focus chosen by the given player, or -1
 *                if none is selected.
 */
public int
query_weapon_focus_chosen(string who)
{
    if (member_array(who, m_indices(chosen_weapon)) < 0)
    {
        return -1;
    }
    else
    {
        return chosen_weapon[who];
    }
}

/*
 * Function name: query_weapon_focus
 * Description:   Gets the weapon focus chosen by the given player, or a
 *                default if none is selected.
 */
public int
query_weapon_focus(string who)
{
    int chosen = query_weapon_focus_chosen(who);

    // default to unarmed if no focus is chosen
    if (chosen == -1)
    {
        return SS_UNARM_COMBAT;
    }

    return chosen;
}

#ifdef DEBUG_ON
#  define DEBUG_FILE "/d/Emerald/mist_tower/obj/debug"
#  define DEBUG(msg) if (calling_function() == "get_train_max") \
                         write_file(DEBUG_FILE, msg);
#else
#  define DEBUG(msg)
#endif

varargs int
sk_query_max(int snum, int silent)
{
    int chosen, max = ::sk_query_max(snum, silent);
    string name;

    setuid();
    seteuid(getuid());

    DEBUG(time() + " " + this_player()->query_real_name() +
        ": " + snum);

    // Max levels for certain skills deviate from the default values
    // depending on the player's chosen weapon focus.
    if (member_array(snum,
        ({ SS_WEP_SWORD, SS_WEP_AXE,
           SS_WEP_POLEARM, SS_WEP_CLUB,
           SS_WEP_KNIFE, SS_UNARM_COMBAT, SS_PARRY })) < 0)
    {
        DEBUG(" max " + max + "\n");
        return max;
    }

    name = this_player()->query_real_name();

    // Check for a weapon focus.  The default is unarmed combat.
    if (member_array(name, m_indices(chosen_weapon)) < 0)
    {
        DEBUG(" default unarm");
        chosen = SS_UNARM_COMBAT;
    }
    else
    {
        chosen = chosen_weapon[name];
    }

    DEBUG(" chosen sk " + chosen);

    // Parry can only be trained if unarmed combat is not the focus
    if (snum == SS_PARRY)
    {
        max = ((chosen != SS_UNARM_COMBAT) ? max : 0);
    }
    else
    {
        // Only the chosen focus can be trained to max.  All others are at 0.
        max = ((snum == chosen) ? max : 0);
    }

    DEBUG(" max " + max + "\n");

    return max;
}

public int
sk_cost(int snum, int fr, int to)
{
    string name = this_player()->query_real_name();
    int chosen = query_weapon_focus(name);

    // increase skill cost for the chosen weapon according to the
    // cost factor for this player.
    if (snum == chosen)
    {
        return ::sk_cost(snum, fr, to) * 
            (100 + cost_factor[this_player()->query_real_name()]) / 100;
    }
    else
    {
        return ::sk_cost(snum, fr, to);
    }
}

int
help(string str)
{
    if ((str != "train") && (str != "training") && (str != "trainer"))
    {
        return 0;
    }
  
    setuid();
    seteuid(getuid());
  
    str =
        "'skill levels'\n" +
        "     List the various skill levels attainable.\n\n" +
        "'learn <skill>'\n" +
        "     Learn a skill which you do not know.\n" +
        "     Ex. 'learn defence', 'learn awareness'\n\n" +
        "'improve'\n" +
        "     List all skills trainable here.\n\n" +
        "'improve <levels>'\n" +
        "     List all skills which may be trained the indicated\n" +
        "     number of levels or more.\n" +
        "     Ex. 'improve 3', 'improve 10'\n\n" +
        "'improve <skill>'\n" +
        "     Improve a desired skill one level.\n" +
        "     Ex. 'improve defence', 'improve awareness'\n\n" +
        "'improve <skill> <levels>'\n" +
        "     Improve a desired skill as many levels as indicated.\n" +
        "     Levels actually trained are limited by what you can\n" +
        "     afford and how much you can learn.\n" +
        "     Ex. 'improve defence 3', 'improve awareness 6'\n\n" +
        "'improve <skill> max'\n" +
        "     Improve a skill as high as you can, limited by what you\n" +
        "     can afford and how much you can learn.\n" +
        "     Ex. 'improve defence max', 'improve awareness max'\n\n" +
        "";
  
    this_player()->more(str);
  
    return 1;
}

public void
sk_hook_write_header(int steps)
{
    if (steps == 0)
    {
        steps = 1;
    }

    write("These are the skills you are able to improve " + LANG_WNUM(steps) +
        (steps == 1 ? " step" : " steps") + " through the " + short() + ".\n" +
        "  Skill:                   Gems:    "+
        "Next level:              Max level:\n"+
        "--------------------------------------"+
        "--------------------------------------\n");
}

void
sk_hook_skillisting()
{
    write("Here follow all skills available to you through the " + short() +
        " and your next level in each:\n" +
        "  Skill:                   Gems:    "+
        "Next level:              Max level:\n"+
        "--------------------------------------"+
        "--------------------------------------\n");
}

/*
 * Function name: query_gem_required
 * Description:   Get the gem required for a given skill level.
 * Arguments:     The skill level
 * Returns:       The full pathname of the gem needed.
 */
public string
query_gem_required(int level)
{
    string gem;

    switch (level)
    {
        case 1..5:
            gem = "quartz";
            break;
        case 6..10:
            gem = "agate";
            break;
        case 11..15:
            gem = "jasper";
            break;
        case 16..20:
            gem = "coral";
            break;
        case 21..25:
            gem = "turquoise";
            break;
        case 26..30:
            gem = "amber";
            break;
        case 31..35:
            gem = "onyx";
            break;
        case 36..40:
            gem = "carnelian";
            break;
        case 41..45:
            gem = "garnet";
            break;
        case 46..50:
            gem = "amethyst";
            break;
        case 51..55:
            gem = "aquamarine";
            break;
        case 56..60:
            gem = "jade";
            break;
        case 61..65:
            gem = "lapis";
            break;
        case 66..70:
            gem = "opal";
            break;
        case 71..75:
            gem = "pearl_black";
            break;
        case 76..80:
            gem = "sapphire";
            break;
        case 81..85:
            gem = "ruby";
            break;
        case 86..90:
            gem = "beryl_red";
            break;
        default:
            gem = "alexandrite";
            break;
    }

    return (GEM_OBJ_DIR + gem);
}   

/*
 * Function name: gem_cost
 * Description:   Get the cost in gems to increase a given skill from one
 *                level to another.
 * Arguments:     1) (int)  The skill number
 *                2) (int)  The current skill level
 *                3) (int)  The new skill level
 * Returns:       A mapping which maps gem types to the number of each type
 *                required.  Ex. ([ "bloodstone" : 2, "quartz" : 8 ])
 */
public mapping
gem_cost(int snum, int from, int to)
{
    int this_level, next_level, cost, gem_num, gem_value;
    string gem_type;
    mapping m = ([]);

    setuid();
    seteuid(getuid());

    this_level = from;
    while (this_level < to)
    {
        gem_num = 0;
        next_level = this_level + 1;
        gem_type = query_gem_required(next_level);

        // Gems have proved to be difficult to obtain in sufficient numbers,
        // so I've reduced the cost until there are more around.
        cost = sk_cost(snum, this_level, next_level) / 3 * 2;

        gem_value = gem_type->query_prop(HEAP_I_UNIT_VALUE);
        
        do
        {
            cost -= gem_value;
            gem_num++;
        }
        while (cost > 0);

        m[gem_type] = m[gem_type] + gem_num;
        this_level = next_level;
    }

    return m;
}

/*
 * Function name: sk_fix_cost
 * Description:   Get a string describing the cost of raising a skill by a
 *                specified number of levels.
 * Arguments:     1) (int) The skill number
 *                2) (int) The number of levels to raise the skill
 * Returns:       A string describing the cost (in gems)
 */
varargs string
sk_fix_cost(int snum, int steps)
{
    int this_level, next_level, max, coins, i, num;
    string next_rank, max_rank, cost_string, *gems, name;
    mapping gem_map;
  
    if (!(max = sk_query_max(snum)))
    {
        return "";
    }

    setuid();
    seteuid(getuid());

    this_level = this_player()->query_base_skill(snum);
    steps = steps || 1;
    next_level = this_level + steps;
    cost_string = "";
  
    if (next_level > max)
    {
        cost_string = "                --- ";
    }
    else
    {
        gem_map = gem_cost(snum, this_level, next_level);
        gems = m_indices(gem_map);
        for (i = 0; i < sizeof(gems); i++)
        {
            num = gem_map[gems[i]];
            name = ((num == 1) ? gems[i]->singular_short(this_player()) :
                                 gems[i]->plural_short(this_player()));
            cost_string += " " + num + " " + name;
        }
    }    
  
    if (this_level >= max)
    {
        next_rank = "maxed";
    }
    else
    {
        next_rank = sk_rank(next_level);
    }
  
    max_rank = sk_rank(max);
  
    return sprintf("%-18s %20s %-22s %-22s\n", sk_trains[snum][0],
        cost_string, next_rank, max_rank);
}

int
sk_improve(string str)
{
    int steps, snum, level, i, j, max_steps, num;
    string skill, verb, pre, aft, *tmp, *gems, msg, gem_id;
    mixed skval;
    mapping gem_map;
    object gem, *inv, *gems_present, *checked_gems;

    if (sk_no_list(this_player()))
    {
        return 1;
    }
  
    /* "defence" can be spelled with an 's' */
    if (strlen(str) && sscanf(str, "%sdefense%s", pre, aft))
    {
        str = pre + "defence" + aft;
    }

    if (!strlen(str) || sscanf(str, "%d", steps))
    {
        return sk_list(steps);
    }
    
    if (sk_no_train(this_player()))
    {
        return 1;
    }
  
    verb = query_verb() || "improve";
    
    tmp = explode(str, " ");

    if ((sizeof(tmp) > 1) && (sscanf(tmp[sizeof(tmp) - 1], "%d", steps) == 1))
    {
        skill = implode(tmp[0 .. -2], " ");
    }
    else
    {
        steps = 1;
        skill = str;
    }

    if ((snum = sk_find_skill(skill)) < 0)
    {
        return sk_hook_unknown_skill(skill, verb);
    }
  
    level = this_player()->query_base_skill(snum);
  
    if (level && (verb == "learn"))
    {
        return sk_hook_learn_known(skill);
    }
    
    if ((steps > 1) && ((level + steps) > sk_query_max(snum)) &&
        (sk_query_max(snum) > level))
    {
        steps = sk_query_max(snum) - level;
    }
  
    skval = sk_trains[snum];
    if ((steps > 1) && ((max_steps = skval[4] *
        this_player()->query_stat(skval[3]) / 100 - level) > 0) &&
        (max_steps < steps))
    {
        steps = max_steps;
    }
    
    if ((level + steps) > sk_query_max(snum))
    {
        return sk_hook_improved_max(skill);
    }

    if (!sk_do_train(snum, this_player(), level + steps))
    {
        return sk_hook_cant_train(skill, level + steps);
    }
  
    inv = all_inventory();
    for (i = 0; i < sizeof(inv); i++)
    {
        if (!inv[i]->query_gem())
        {
	    break;
        }
    }

    if (!sizeof(inv) || (i < sizeof(inv)))
    {
        this_player()->set_skill(snum, level);
        write("You concentrate on your ability to " + sk_tdesc[snum][0] +
            " and reach out to touch the " + short() + ", but nothing " +
            "happens.\n");
        return 1;
    }

    gem_map = gem_cost(snum, level, level + steps);
    gems = m_indices(gem_map);
    gems_present = filter(all_inventory(), &->query_gem());
    checked_gems = ({});
    for (i = 0; i < sizeof(gems); i++)
    {
        num = gem_map[gems[i]];
        gem_id = gems[i]->query_prop(HEAP_S_UNIQUE_ID);
        for (j = 0; j < sizeof(gems_present); j++)
        {
            if (gems_present[i]->query_prop(HEAP_S_UNIQUE_ID) == gem_id)
            {
                if (gems_present[i]->num_heap() < num)
                {
                    this_player()->set_skill(snum, level);
                    write("The " + short() + " doesn't contain enough gems.\n");
                    return 1;
                }

                if (gems_present[i]->num_heap() > num)
                {
                    gems_present[i]->split_heap(num);
                }

                checked_gems += ({ gems_present[i] });
                break;
            }
        }

        if (j >= sizeof(gems_present))
        {
            this_player()->set_skill(snum, level);
            write("The " + short() + " doesn't contain the correct gems.\n");
            return 1;
        }
    }

    /* This is somewhat wasteful.  It would be more efficient just to do
     * set_heap_size(), but this is easier, and this code isn't executed
     * so much that it's terribly important.
     */
    checked_gems->force_heap_split();
    checked_gems->remove_object();

    write("You concentrate on your ability to " + sk_tdesc[snum][0] +
        " and reach out to touch the " + short() + ".  As your hands " +
        "come in contact with its surface, " +
        (sizeof(all_inventory()) ? "some" : "all") + " of the gems " +
        "inside disintegrate, and a pulse of energy rushes through " +
        "you.  Instantly, you sense that your knowledge has increased.\n" +
        "You achieve the rank of " + sk_rank(level + steps) + ".\n");

    msg = " places " + this_player()->query_possessive() + " hands on the " +
        short() + ", and " + (sizeof(all_inventory()) ? "some" : "all") +
        " of the gems inside disintegrate.\n";
    say(({ METNAME + msg, NONMETNAME + msg, "" }));

    return 1;
}

public void
touch_frustum(object ob)
{
    if (!ob)
    {
        return;
    }

    set_this_player(ob);
    write("As you contact the surface of the " + short() + ", you feel " +
        "a brief magical influence in your mind.  You sense that the " +
        short() + " might be used to enhance your own knowledge.\n");
    sk_improve("");
}

public void
emote_hook(string emote, object actor, string adverb, object *oblist, int cmd_attr, int target)
{
    if (cmd_attr & ACTION_CONTACT)
    {
        touch_frustum(actor);
    }
}

int
select_weapon(string str)
{
    mapping m = ([ "sword"   : SS_WEP_SWORD,
                   "axe"     : SS_WEP_AXE,
                   "polearm" : SS_WEP_POLEARM,
                   "knife"   : SS_WEP_KNIFE,
                   "club"    : SS_WEP_CLUB,
                   "unarmed combat" : SS_UNARM_COMBAT, ]);
    string name;

    if (!strlen(str) ||
        (member_array(str, m_indices(m)) < 0))
    {
        notify_fail("Possible selections are: " + 
            COMPOSITE_WORDS(m_indices(m)) + ".\n");
        return 0;
    }
   
    name = this_player()->query_real_name();

    if ((member_array(name, m_indices(chosen_weapon)) >= 0) &&
        (chosen_weapon[name] != m[str]))
    {
        cost_factor[name] += 10;
    }

    chosen_weapon[name] = m[str];

    setuid();
    seteuid(getuid());
    save_object(WEAPON_SAVE);

    // This is needed because the trainer is a cloned object. It causes the
    // master object to reload the new weapon data, so that the skill decay
    // routines, which reference the master, not the cloned object, have
    // access to the updated skill maximums for the player. 
    MASTER->restore_weapon_data();

    write("Ok.\n");
    return 1;
}

public void
init()
{
    ::init();
    init_skill_raise();

    add_action(select_weapon, "select");
}
