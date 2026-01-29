/*
 * /d/Gondor/common/guild2/spells/morgul_spells.c
 *
 * Olorin, 12-jan-1994
 *
 * Modification log:
 * 26-Oct-1995: New spell system. Olorin
 */
#pragma strict_types

#define NEW_SPELL_SYSTEM

#ifdef NEW_SPELL_SYSTEM
inherit "/std/object.c";
inherit "/d/Genesis/magic/spellcasting.c";
#else
inherit "/std/spells.c";
#endif

#include <composite.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

/* prototypes */
varargs mixed   check_player(object who, mixed ingr, int mana, int needed);
        object *find_ingr(mixed ingr, object who);
        void    remove_ingr(object *ingr);
        void    fail_cast(object who, object *ingr_arr);

#define HE(x)	(x)->query_pronoun()
#define HIS(x)	(x)->query_possessive()

#undef DEBUG
#define DEBUG 0

#include "/d/Gondor/common/guild2/spells/arhalgul.h"
#include "/d/Gondor/common/guild2/spells/artirith.h"
#include "/d/Gondor/common/guild2/spells/dollost.h"
#include "/d/Gondor/common/guild2/spells/ephessul.h"
#include "/d/Gondor/common/guild2/spells/mortirio.h"
#include "/d/Gondor/common/guild2/spells/naro.h"
#include "/d/Gondor/common/guild2/spells/nifarist.h"
#include "/d/Gondor/common/guild2/spells/palanquendo.h"
#include "/d/Gondor/common/guild2/spells/ringurth.h"
#include "/d/Gondor/common/guild2/spells/sulambar.h"
#include "/d/Gondor/common/guild2/spells/yalarochrama.h"

static string  spell_name;

mixed
do_spell(string str)
{
   string  object_file;

   seteuid(getuid());
   object_file = (MORGUL_SPELLS + spell_name + "_object");
   return call_other(object_file, "do_" + spell_name, str);
}

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
    remove_spell("dollost");
    remove_spell("dramalgos");
    remove_spell("ephessul");
    remove_spell("faugoroth");
    remove_spell("morthul");
    remove_spell("mortirio");
    remove_spell("naro");
    remove_spell("nifarist");
    remove_spell("palanquendo");
    remove_spell("ringurth");
    remove_spell("sulambar");
    remove_spell("thunaur");
    remove_spell("yalarochrama");

    /* add available spells */
    if (guild_level >= MS_ARHAL_MIN)
        add_spell("arhalgul", "do_arhalgul", "Magic Revealing");
    if (guild_level >= MS_ARTIR_MIN)
        add_spell("artirith", "do_artirith", "Out of Sight");
    if (guild_level >= MS_DOLLO_MIN)
        add_spell("dollost", "do_dollost", "Emptyhead");
    if (guild_level >= MS_DRAMA_MIN)
        add_spell("dramalgos", "do_spell", "Stormwind");
    if (guild_level >= MS_EPHES_MIN)
        add_spell("ephessul", "do_ephessul", "Windfence");
    if (guild_level >= MS_FAUGO_MIN)
        add_spell("faugoroth", "do_spell", "Choking Horror");
    if (guild_level >= MS_MORTH_MIN)
        add_spell("morthul", "do_spell", "Black Breath");
    if (guild_level >= MS_MORTI_MIN)
        add_spell("mortirio", "do_mortirio", "See in Darkness");
    if (guild_level >= MS_NARO1_MIN)
        add_spell("naro", "do_naro", "Word of Command");
    if (guild_level >= MS_NIFAR_MIN)
        add_spell("nifarist", "do_nifarist", "Make Forget");
    if (guild_level >= MS_PALAN_MIN)
        add_spell("palanquendo", "do_palanquendo", "Tell Far");
    if (guild_level >= MS_RINGU_MIN)
        add_spell("ringurth", "do_ringurth", "Chill of Death");
    if (guild_level >= MS_SULAM_MIN)
        add_spell("sulambar", "do_sulambar", "Wind of Doom");
    if (guild_level >= MS_THUNA_MIN)
        add_spell("thunaur", "do_spell", "Fire Breath");
    if (guild_level >= MS_YALAR_MIN)
        add_spell("yalarochrama", "do_yalarochrama", "Summon Winged Steed");
}

void
create_object()
{
    set_name("Morgul_Spell_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

void
init()
{
    ::init();

    update_morgul_spells();
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
    int     i;
    object  ob,
           *return_arr;

    return_arr = ({ });

    if (ingr)
    {
	if (objectp(ingr))
	    ingr = ({ ingr });

	for (i=0; i < sizeof(ingr); i++)
	{
	    if (ob = present(ingr[i],who))
		return_arr += ({ ob });
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

int
filter_visible(object x)
{
    return (!(x->query_no_show()));
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
            i,
            new_size;
    string  wrt,
           *heap_name = ({}),
           *str_arr;
    object *non_heap = ingr,
           *vis_non_heap;

    if (!ingr || !sizeof(ingr))
        return;

    num_ingr = sizeof(ingr);
    for (i = 0; i < num_ingr; i++)
    {
        if (function_exists("restore_heap", ingr[i]))
        {
            new_size = ingr[i]->num_heap() - 1;
            if (new_size > 0)
               heap_name += ({ "one of the "+ingr[i]->short() });
            else
               heap_name += ({ ingr[i]->short() });
            ingr[i]->set_heap_size(new_size);
            non_heap -= ({ ingr[i] });
        }
    }

    vis_non_heap = filter(non_heap, "filter_visible", TO);
    num_non = sizeof(vis_non_heap);
    num_heaps = num_ingr - sizeof(non_heap);
#if DEBUG
TP->catch_msg("DEBUG morgul_spells: num_ingr = "+num_ingr+", num_heaps = "+num_heaps+"\n");
dump_array(ingr);
dump_array(non_heap);
#endif
    if (num_heaps == 0)
    {
        if (num_non == 0)
            wrt = 0;
        else
            wrt = COMPOSITE_DEAD(vis_non_heap); 		// heaps 0, others 0..n
    }
    else
    {
        if (num_non > 1)
        {
            if (num_heaps == 1)
                wrt = heap_name[0] + ", ";			// heaps 1, others 2..n
            else
                wrt = implode(heap_name, ", ") + ", ";		// heaps 2..n, others 2..n
            wrt += COMPOSITE_DEAD(vis_non_heap);
        }
        else if (num_non == 1)
        {
            if (num_heaps == 1)
                wrt = heap_name[0] + " and ";			// heaps 1, others 1
            else
                wrt = implode(heap_name, ", ") + " and ";	// heaps 2..n, others 1
            wrt += COMPOSITE_DEAD(vis_non_heap);
        }
        else
        {
            if (num_heaps == 1)
                wrt = heap_name[0];				// heaps 1, others 0
            else
                wrt = implode(heap_name[0..num_heaps-2], ", ") +	// heaps 2..n, others 0
                    " and " + heap_name[num_heaps-1];
        }
    }
    if (strlen(wrt))
    {
        wrt += ".\n";
        TP->catch_msg("You sacrificed " + wrt);
    }

    /* And remove the ingredients */
    for (i=0; i < sizeof(non_heap); i++)
    {
#if DEBUG
TP->catch_msg("DEBUG morgul_spells: will remove now "+non_heap[i]->short()+"\n");
#endif
        non_heap[i]->remove_object();
    }
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
        if (random((TP->query_skill(SS_SPELLCRAFT)/10)+1))
            TP->catch_msg("Luckily you manage to keep all "
                + "ingredients intact.\n");
        else
        {
            ran = random(sizeof(ingr));
            if (!function_exists("restore_heap", ingr[ran]))
            {
                if (!(ingr[ran]->query_no_show()))
                    TP->catch_msg("Unfortunately you lose the "
                        + ingr[ran]->short() + " in the process.\n");
                ingr[ran]->remove_object();
            }
            else
            {
                new_size = ingr[ran]->num_heap() - 1;
                if (new_size == 0)
                    TP->catch_msg("Unfortunately you lose "
                    + ingr[ran]->short() + " in the process.\n");
                else
                    TP->catch_msg("Unfortunately you lose one of your "
                    + ingr[ran]->short() + " in the process.\n");
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
    TP->catch_msg("You fail to cast the spell correctly.\n");
    tell_room(ENV(TP), QCTNAME(TP)
            + " fails to cast a spell correctly.\n", TP);

    /* There's a chance she loses the ingredients as well */
    if (sizeof(ingr_arr))
        lose_random_ingr(ingr_arr);
}

/*
 * Function:    query_spell_time
 * Description: It is called from cmdhooks.c, and should return the time
 *              in seconds it takes to prepare the spell. The actual time
 *              will be (time + 2 + LIVE_I_ATTACK_DELAY).
 * Arguments:   verb - The verb that initiated this spell.
 *              arg  - The arguments to the verb.
 * Returns:     The time in seconds.
 */
int
query_spell_time(string verb, string arg)
{
    spell_name = verb;

    switch(verb)
    {
        case "arhalgul":	return MS_ARHAL_TIME;
        case "artirith":	return MS_ARTIR_TIME;
        case "dollost": 	return MS_DOLLO_TIME;
        case "dramalgos": 	return MS_DRAMA_TIME;
        case "ephessul": 	return MS_EPHES_TIME;
        case "faugoroth": 	return MS_FAUGO_TIME;
        case "morthul": 	return MS_MORTH_TIME;
        case "mortirio": 	return MS_MORTI_TIME;
        case "naro": 		return MS_NARO_TIME;
        case "nifarist": 	return MS_NIFAR_TIME;
        case "palanquendo": 	return MS_PALAN_TIME;
        case "ringurth": 	return MS_RINGU_TIME;
        case "sulambar":
            if (TP->query_npc())
                return 0;
            return MS_SULAM_TIME;
        case "thunaur": 	return MS_THUNA_TIME;
        case "yalarochrama": 	return MS_YALAR_TIME;
    }

    return ::query_spell_time(verb);
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *		  the player soul when the command "spells" is typed.
 */
public void
list_spells()
{
    int     i,
            il;
    string  msg = "\n\t _______________________________________________ \n"+
                    "\t/                                               \\\n"+
                    "\t|  The Dark Lord has granted you these spells:  |\n"+
                    "\t|  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  |\n",
            space;

    if (!(il = sizeof(gVerbs)))
        return;

    for (i = 0 ; i < sizeof(gVerbs) ; i++)
        msg += sprintf("\t|  - %-20s %-20s  |\n", gVerbs[i], gNames[i]);

    msg += "\t\\_______________________________________________/\n\n";

    write(msg);
}

int
query_spell_mess(string verb, string arg)
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
        case "morthul":
        case "mortirio":
        case "naro":
        case "nifarist":
        case "palanquendo":
        case "ringurth":
        case "sulambar":
        case "thunaur":
            mess = " draws power from the realm of the shadows.";
            break;
        case "artirith":
            mess = " seems to fade into the realm of the shadows.";
            break;
        case "yalarochrama":
            mess = " starts to summon a creature from the realm of the shadows.";
            break;
    }
    say(({METNAME + mess + "\n", TART_NONMETNAME + mess + "\n", ""}));
    return 1;
}

