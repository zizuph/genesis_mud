/*
 *      /d/Gondor/common/guild2/spells/morgul_spells.c
 *
 *      Olorin, 12-jan-1994
 *
 *      When adding a new spell, you have to do the following:
 *      - if the spell is not an attack spell, include the spell code;
 *      - add the spell in function update_morgul_spells(),
 *        first removing it, than adding it if the conditions are met;
 *      - define casting time and minimum level in spell_defs.h;
 *      - add the spell to the switch in query_spell_time();
 *      - add the spell to the switch in query_spell_mess();
 *      - add the spell to the switch in query_spell_morgul_level().
 *
 *      Modification log:
 *      Mercade, 10-Mar-1998, Use unimportant leftovers first to prevent
 *          waste of more useful leftovers; General update and documentation.
 */

#pragma strict_types
#pragma save_binary

inherit "/std/spells.c";

#include <cmdparse.h>
#include <comb_mag.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <tasks.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

/* prototypes */
varargs mixed   check_player(object who, mixed ingr, int mana, int needed);
        object *find_ingr(mixed ingr, object who);
        void    remove_ingr(object *ingr);
        void    fail_cast(object who, object *ingr_arr);

#undef DEBUG

#define HE(x)              (x)->query_pronoun()
#define HIS(x)             (x)->query_possessive()
#define HIM(x)             (x)->query_objective()

#include "/d/Gondor/common/guild2/spells/arhalgul.h"
#include "/d/Gondor/common/guild2/spells/artirith.h"
#include "/d/Gondor/common/guild2/spells/crabandir.c"
#include "/d/Gondor/common/guild2/spells/dollost.h"
#include "/d/Gondor/common/guild2/spells/ephessul.h"
#include "/d/Gondor/common/guild2/spells/gostangwedh.c"
#include "/d/Gondor/common/guild2/spells/mortirio.h"
#include "/d/Gondor/common/guild2/spells/naro.h"
#include "/d/Gondor/common/guild2/spells/narusse.c"
#include "/d/Gondor/common/guild2/spells/nifarist.h"
#include "/d/Gondor/common/guild2/spells/palanquendo.h"
#include "/d/Gondor/common/guild2/spells/ringurth.h"
#include "/d/Gondor/common/guild2/spells/sauthacuith.c"
#include "/d/Gondor/common/guild2/spells/sulambar.h"
#include "/d/Gondor/common/guild2/spells/yalarochrama.h"

static string  spell_name;

/*
 * Function name: do_spell
 * Description  : This function is called for all spells that have an
 *                external spell object other than this object. Mostly
 *                these are the combat spells.
 * Arguments    : string str - the command line argument.
 * Returns      : mixed - the spell return string.
 */
mixed
do_spell(string str)
{
   string  object_file;

   seteuid(getuid());
   object_file = (MORGUL_SPELLS + spell_name + "_object");
   return call_other(object_file, "do_" + spell_name, str);
}

/*
 * Function name: update_morgul_spells
 * Description  : This function will update the spell object and add all
 *                spells to the player that are relevant for him. This
 *                can be called in case of promotions and demotions.
 */
void
update_morgul_spells()
{
    int     guild_level;

    if (ENV(TO) != TP)
        return;

    guild_level = TP->query_morgul_level();

    /* remove all spells */
    remove_spell("arhalgul");
    remove_spell("artirith");
    remove_spell("crabandir");
    remove_spell("dollost");
    remove_spell("dramalgos");
    remove_spell("ephessul");
    remove_spell("faugoroth");
    remove_spell("gostangwedh");
    remove_spell("morthul");
    remove_spell("mortirio");
    remove_spell("naro");
    remove_spell("narusse");
    remove_spell("nifarist");
    remove_spell("palanquendo");
    remove_spell("orekir");
    remove_spell("ringurth");
    remove_spell("sauthacuith");
    remove_spell("sulambar");
    remove_spell("thunaur");
    remove_spell("yalarochrama");

    /* add available spells */
    if (guild_level >= MS_ARHAL_MIN)
        add_spell("arhalgul", "do_arhalgul", "Magic Revealing");
    if (guild_level >= MS_ARTIR_MIN)
        add_spell("artirith", "do_artirith", "Out of Sight");
    if (guild_level >= MS_CRABA_MIN)
        add_spell("crabandir", "do_crabandir", "Crow Watcher");
    if (guild_level >= MS_DOLLO_MIN)
        add_spell("dollost", "do_dollost", "Emptyhead");
    if (guild_level >= MS_DRAMA_MIN)
        add_spell("dramalgos", "do_spell", "Stormwind");
    if (guild_level >= MS_EPHES_MIN)
        add_spell("ephessul", "do_ephessul", "Windfence");
    if (guild_level >= MS_FAUGO_MIN)
        add_spell("faugoroth", "do_spell", "Choking Horror");
    if (guild_level >= MS_GOSTA_MIN)
        add_spell("gostangwedh", "do_gostangwedh", "Chains of Terror");
    if (guild_level >= MS_MORTH_MIN)
        add_spell("morthul", "do_spell", "Black Breath");
    if (guild_level >= MS_MORTI_MIN)
        add_spell("mortirio", "do_mortirio", "See in Darkness");
    if (guild_level >= MS_NARO1_MIN)
        add_spell("naro", "do_naro", "Word of Command");
    if (guild_level >= MS_NARUS_MIN)
        add_spell("narusse", "do_narusse", "Enchant Blade");
    if (guild_level >= MS_NIFAR_MIN)
        add_spell("nifarist", "do_nifarist", "Make Forget");
    if (guild_level >= MS_PALAN_MIN)
        add_spell("palanquendo", "do_palanquendo", "Tell Far");
    if (guild_level >= MS_OREKI_MIN)
        add_spell("orekir", "do_spell", "Heart Cleave");
    if (guild_level >= MS_RINGU_MIN)
        add_spell("ringurth", "do_ringurth", "Chill of Death");
    if (guild_level >= MS_SAUTH_MIN)
        add_spell("sauthacuith", "do_sauthacuith", "Drain Life");
    if (guild_level >= MS_SULAM_MIN)
        add_spell("sulambar", "do_sulambar", "Wind of Doom");
    if (guild_level >= MS_THUNA_MIN)
        add_spell("thunaur", "do_spell", "Fire Breath");
    if (guild_level >= MS_YALAR_MIN)
        add_spell("yalarochrama", "do_yalarochrama", "Summon Winged Steed");
}

/*
 * Function name: create_spells
 * Description  : Constructor. Called to create this object.
 */
void
create_spells()
{
    set_name("Morgul_Spell_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

/*
 * Function name: init
 * Description  : Called to add all spells to the player when he comes in
 *                contact with it.
 */
void
init()
{
    ::init();

    update_morgul_spells();
}

/*
 * Function name: best_leftover_first
 * Description  : When a spell requires a "leftover" as ingredient, we do
 *                a little extra parsing to first use leftovers that are
 *                not specifically used as spell ingredient themselves.
 * Arguments    : object *leftovers - the leftovers the player carries.
 * Returns      : object - the leftover to use as ingredient.
 */
object
best_leftover_first(object *leftovers)
{
    int index = -1;
    int size = sizeof(leftovers);

    /* Loop over all leftovers the player carries. */
    while(++index < size)
    {
        /* Find the first leftover that is not a special leftover. */
        if (member_array(leftovers[index]->query_organ(),
            MORGUL_SPECIFIC_LEFTOVERS) == -1)
        {
            return leftovers[index];
        }
    }

    /* All are special, use the last one in the list. */
    return leftovers[size - 1];
}

/*
 * Function name:   find_ingr
 * Description:	    Find an ingredient or a number of ingredients in
 *		    a player.
 * Arguments:	    ingr: Either a string or an arrays of strings with
 *		    names of the ingredients. It is wise to give a unique
 *		    name to your object, something like "_shire_carrot_",
 *		    in addition to its normal names.
 * Returns:	    An array with found objects.
 */
object *
find_ingr(mixed ingr, object who)
{
    int     index,
            size;
    object *ob,
           *deep_inv,
           *return_arr;

    if (!ingr)
        return ({ });

    if (stringp(ingr))
        ingr = ({ ingr });

    deep_inv = deep_inventory(who);
    return_arr = ({ });

    size = sizeof(ingr);
    index = -1;
    while(++index < size)
    {
        if (sizeof(ob = filter(deep_inv, &->id(ingr[index]))))
        {
            /* If the ingredient is a single leftover, we first parse out some
             * 'special' leftovers that are used specifically in spells, so
             * that they are not used by chance here.
             */
            if (ingr[index] == "leftover")
            {
                return_arr += ({ best_leftover_first(ob) });
            }
            else
            {
                return_arr += ({ ob[0] });
            }
        }
    }

    return return_arr;
}

/*
 * Function name:   check_player
 * Description:     Check if the player matches a few tests. If not, the
 *                  reason is returned.
 * Arguments:       who: The player to check
 *                  ingr: if 0, the no magical ingredients are checked.
 *                        if object or list of objects, check if the player
 *                        posesses all of them.
 *                  mana: Required mana to cast the spell
 *		    needed: Compared with morgul level. If smaller, then the
 *			  player is not crafted enough to cast the spell.
 * Returns:         0 if the player matches, else the string with the reason
 *		    why the player flunked.
 */
varargs mixed
check_player(object who, mixed ingr, int mana, int needed)
{
    int     i,
            level,
            is_wiz;
    object *ob_arr;

    /* Test for ghosts */
    if (who->query_ghost())
        return "You cannot do that in your state.\n";

    is_wiz = who->query_wiz_level();
#if DEBUG
    is_wiz = 0;
#endif
    /* Make sure that wizards can always cast it */
    if (is_wiz)
	return 0;

    /* Is magic allowed in this room? */
    if (environment(who)->query_prop(ROOM_I_NO_MAGIC))
        return MORGUL_S_SPELL_FAIL;

    if (who->query_guild_name_occ() != GUILD_NAME)
	return "Only Servants of the Dark Lord can cast this spell.\n";

    level = (who->query_morgul_level());

    /* Test the player's guild level */
    if (level < needed)
	return "The Dark Lord has not given you the power to cast this spell.\n";

    /* Test if enough mana */
    if (who->query_mana() < mana)
	return "You do not feel strong enough to cast the spell.\n";

    // npc mages do not need ingredients
    if (who->query_npc())
        return 0;

    /* Test for all magic ingredients */
    if (ingr)
    {
	if (stringp(ingr))
	    ingr = ({ ingr });

	ob_arr = find_ingr(ingr, who);
	if (!ob_arr)
	    ob_arr = ({ });

	if (sizeof(ingr) != sizeof(ob_arr))
	    return "One of the ingredients is missing!\n";
    }

    /* Passed all tests successfully */
    return 0;
}

/*
 * Function name:   remove_ingr
 * Description:	    Remove all ingredients, and tell it to the player
 * Arguments:	    ingr: The array with objects of ingredients
 */
void
remove_ingr(object *ingr)
{
    int     num_ingr,
            num_heaps,
            num_non,
            index,
            new_size;
    string  wrt,
           *heap_name = ({}),
           *str_arr;
    object *non_heap = ingr,
           *vis_non_heap;

    if (!ingr || !sizeof(ingr))
        return;

    num_ingr = sizeof(ingr);
    index = -1;
    while(++index < num_ingr)
    {
        if (function_exists("restore_heap", ingr[index]))
        {
            new_size = ingr[index]->num_heap() - 1;
            if (new_size > 0)
               heap_name += ({ "one of the " + ingr[index]->short() });
            else
               heap_name += ({ ingr[index]->short() });
            ingr[index]->set_heap_size(new_size);
            non_heap -= ({ ingr[index] });
        }
    }

    vis_non_heap = filter(non_heap, &not() @ &->query_no_show());
    num_non = sizeof(vis_non_heap);
    num_heaps = num_ingr - sizeof(non_heap);

#if DEBUG
    write("DEBUG morgul_spells: num_ingr = " + num_ingr + ", num_heaps = " +
        num_heaps + "\n");
    dump_array(ingr);
    dump_array(non_heap);
#endif

    if (num_heaps == 0)
    {
        if (num_non == 0)
            wrt = 0;
        else
            wrt = COMPOSITE_DEAD(vis_non_heap);   // heaps 0, others 0..n
    }
    else
    {
        if (num_non > 1)
        {
            if (num_heaps == 1)
                wrt = heap_name[0] + ", ";        // heaps 1, others 2..n
            else
                wrt = implode(heap_name, ", ") + ", ";		// heaps 2..n, others 2..n
            wrt += COMPOSITE_DEAD(vis_non_heap);
        }
        else if (num_non == 1)
        {
            if (num_heaps == 1)
                wrt = heap_name[0] + " and ";	  // heaps 1, others 1
            else
                wrt = implode(heap_name, ", ") + " and ";	// heaps 2..n, others 1
            wrt += COMPOSITE_DEAD(vis_non_heap);
        }
        else
        {
            if (num_heaps == 1)
                wrt = heap_name[0];		// heaps 1, others 0
            else
                wrt = implode(heap_name[0..num_heaps-2], ", ") +	// heaps 2..n, others 0
                    " and " + heap_name[num_heaps-1];
        }
    }
    if (strlen(wrt))
    {
        write("You sacrificed " + wrt + ".\n");
    }

    /* And remove the ingredients */
    non_heap->remove_object();
}

/*
 * Function name:   lose_random_ingr
 * Description:	    Destructs one random ingredient with a chance depending
 *		    on SS_SPELLCRAFT and tells the player that it happened.
 * Arguments:	    ingr: An array of objects of ingredients, as returned
 *			  by find_ingr()
 */
void
lose_random_ingr(object *ingr)
{
    int ran,
        new_size;
  
    if (sizeof(ingr))
    {
        if (random((TP->query_skill(SS_SPELLCRAFT) / 10) + 1))
            write("Luckily you manage to keep all ingredients intact.\n");
        else
        {
            ran = random(sizeof(ingr));
            if (!function_exists("restore_heap", ingr[ran]))
            {
                if (!(ingr[ran]->query_no_show()))
                    write("Unfortunately you lose the " +
                        ingr[ran]->short() + " in the process.\n");
                ingr[ran]->remove_object();
            }
            else
            {
                new_size = ingr[ran]->num_heap() - 1;
                if (new_size == 0)
                    write("Unfortunately you lose " +
                        ingr[ran]->short() + " in the process.\n");
                else
                    write("Unfortunately you lose one of your " +
                        ingr[ran]->short() + " in the process.\n");
                ingr[ran]->set_heap_size(new_size);
            }
        }
    }
}

/*
 * Function name:   fail_cast
 * Description:     Handles the casting failure. There is a chance of 1/6th
 *		    that some ingredient will be lost at the failure.
 * Arguments:	    who: The player who failed to cast the spell
 *		    ingr_arr: The array with ingredient objects.
 */
void
fail_cast(object who, object *ingr_arr)
{
    string msg_m, msg_n;

    write("You fail to cast the spell correctly.\n");
    msg_m = who->query_met_name() + " fails to cast a spell correctly.\n";
    msg_n = "The " + who->query_nonmet_name() +
        " fails to cast a spell correctly.\n";
    tell_room(ENV(TP), ({ msg_m, msg_n }), TP);

    /* There's a chance she loses the ingredients as well */
    if (sizeof(ingr_arr))
        lose_random_ingr(ingr_arr);
}

/*
 * Function name: query_spell_time
 * Description:   How long time will it take to cast a spell?
 * Arguments:	  verb - The spell verb
 * Returns:       The time it will take. Real casting time will be time + 2 
 */
int
query_spell_time(string verb)
{
    spell_name = verb;

    switch (verb)
    {
        case "arhalgul":	return MS_ARHAL_TIME;
        case "artirith":	return MS_ARTIR_TIME;
        case "dollost": 	return MS_DOLLO_TIME;
        case "dramalgos": 	return MS_DRAMA_TIME;
        case "ephessul": 	return MS_EPHES_TIME;
        case "faugoroth": 	return MS_FAUGO_TIME;
        case "gostangwedh": return MS_GOSTA_TIME;
        case "morthul": 	return MS_MORTH_TIME;
        case "mortirio": 	return MS_MORTI_TIME;
        case "naro": 		return MS_NARO_TIME;
        case "narusse":		return MS_NARUS_TIME;
        case "nifarist": 	return MS_NIFAR_TIME;
        case "palanquendo":	return MS_PALAN_TIME;
        case "orekir":      return MS_OREKI_TIME;
        case "ringurth": 	return MS_RINGU_TIME;
        case "sauthacuith": return MS_SAUTH_TIME;
        case "sulambar":    return (TP->query_npc() ? 0 : MS_SULAM_TIME);
        case "thunaur": 	return MS_THUNA_TIME;
        case "yalarochrama": return MS_YALAR_TIME;
    }

    return ::query_spell_time(verb);
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *		  the player soul when the command "spells" is typed.
 */
void
list_spells()
{
    int     index,
            size;
    string  msg = "\n\t _______________________________________________ \n"+
                    "\t/                                               \\\n"+
                    "\t|  The Dark Lord has granted you these spells:  |\n"+
                    "\t|  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  |\n",
            space;

    size = sizeof(verb_list);
    if (!size)
        return;

    index = -1;
    while(++index < size)
    {
        msg += sprintf("\t|  - %-20s %-20s  |\n", verb_list[index],
            name_list[index]);
    }

    msg += "\t\\_______________________________________________/\n\n";

    write(msg);
}

int
query_spell_mess(string verb)
{
    string  mess;

    write("You prepare to employ Dark Sorcery and draw upon the power of the Dark Lord.\n");

    switch(verb)
    {
        case "arhalgul":
        case "dollost": 
        case "dramalgos":
        case "ephessul":
        case "faugoroth":
        case "gostangwedh":
        case "morthul":
        case "mortirio":
        case "naro":
        case "narusse":
        case "nifarist":
        case "palanquendo":
        case "ringurth":
        case "sauthacuith":
        case "sulambar":
        case "thunaur":
            mess = " draws power from the realm of the shadows.";
            break;
        case "artirith":
            mess = " seems to fade into the realm of the shadows.";
            break;
        case "crabandir":
        case "yalarochrama":
            mess = " starts to summon a creature from the realm of the shadows.";
            break;
        case "orekir":
            mess = " looms over a nearby corpse and draws power from the realm of the shadows.";
            break;
    }
    if (strlen(mess))
        say( ({ METNAME + mess + "\n", TART_NONMETNAME + mess + "\n", "" }) );

    return 1;
}

/*
 * Function name: query_spell_morgul_level
 * Description:   return Morgul level needed to cast a spell
 * Arguments:     spell - the name of the spell (the command verb)
 * Returns:       the Morgul level required, -1 if no spell
 */
public int
query_spell_morgul_level(string spell)
{
    if (!strlen(spell))
        return -1;

    switch(LOW(spell))
    {
        case "arhalgul":	return MS_ARHAL_MIN;
        case "artirith":	return MS_ARTIR_MIN;
        case "crabandir":	return MS_CRABA_MIN;
        case "dollost":		return MS_DOLLO_MIN;
        case "dramalgos":	return MS_DRAMA_MIN;
        case "ephessul":	return MS_EPHES_MIN;
        case "faugoroth":	return MS_FAUGO_MIN;
        case "gostangwedh":	return MS_GOSTA_MIN;
        case "morthul":		return MS_MORTH_MIN;
        case "mortirio":	return MS_MORTI_MIN;
        case "naro":		return MS_NARO1_MIN;
        case "narusse":		return MS_NARUS_MIN;
        case "nifarist":	return MS_NIFAR_MIN;
        case "orekir":	    return MS_OREKI_MIN;
        case "palanquendo":	return MS_PALAN_MIN;
        case "ringurth":	return MS_RINGU_MIN;
        case "sauthacuith": return MS_SAUTH_MIN;
        case "sulambar":	return MS_SULAM_MIN;
        case "thunaur":		return MS_THUNA_MIN;
        case "yalarochrama": return MS_YALAR_MIN;
        default:		    return -1;
    }
}
