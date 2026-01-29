
/*
 *  spelltome.c
 *
 *  A nice tome that contains some spells for mortals to cast.
 *
 *  Contains the following spells:
 *
 *	stop fighting	Makes all fighting in a room stop for a while.
 *			Needed:
 *			- special mushroom.
 *			- 140 mana.
 *          - 100-140 mana is drained from the player for a successful spell
 *
 *
 *	melt armour	Melts the worn pieces of armour of an opponent.
 *			Needed:
 *			- 100 mana.
 *          -  80-100 mana is drained from the player for asuccessful spell
 *
 *  Note that when you make an object that allows players to cast spells,
 *  you MUST also put descriptions of the spells in the directory
 *  /d/<yourdomain>/open/SPELLS/. But you already knew that, because you
 *  have read the /doc/man/general/spells doc, right? ;-)
 *
 * Altered May 7, 1994 by Dunstable
 * Now forces removal of melted/broken armour, no restriction
 * layman guild.
 *
 * This should also check for OBJ_I_RES_MAGIC and OBJ_I_RES_FIRE,
 * not just MAGIC_I_RES_FIRE/MAGIC_I_RES_MAGIC.
 * /Mayhem
 * Added test for [ROOM/OBJ]_M_NO_[MAGIC]_ATTACK. /Mercade
 *
 * Added automagic_validate for the Playerarch office -Dunstable 3-16-95
 *
 * Upped the mana on the spells: Stop from 45 to 140 (with a bit of random)
 *                               Melt from 60 to 100 (with a bit of random)
 * Also added chance to use up ingredient, for now its 1/3 instead of 1/6.
 * Regulated in the function: lose_random_ingr
 *
 *                  Toby, 2008-04-22
 *         
 * Disabled the spells by request from Gorboth/Petros.
 * Eowul, 2010-04-23
 */

inherit "/std/spells";

#include "defs.h"
#include "/sys/cmdparse.h"
#include "/secure/std.h"
#include "/sys/tasks.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"

#define SP_STOP_INGR ({ "_stop_spell_mushroom_" })
#define SP_STOP_MANA 140
#define SP_MELT_INGR ({ "_cast_iron" })
#define SP_MELT_MANA 100

#define SHIRE_LOG_DIR "/d/Shire/log/"

int alarm_id;

//  Prototypes
void check_carry();

/*
 * See if the player can get this back in the Playerarch office
 */
int
automagic_validate(object player)
{
   if(!(player->query_guild_style_occ() == "fighter"))
   {
     return 1;
   }
   return 0;
}

/* Function to make logs of the two spells in the tome 
 * if need arise. Borrowed and modified from MM spell_inherit /Toby
 */
void
log_tome_spell(string sWho, string sSpell, string sTxt)
{
    setuid();
    seteuid(getuid());
    write_file( SHIRE_LOG_DIR + "spelltome", "At " + ctime(time()) + 
                sWho + " used the " + sSpell + ": " + sTxt + " \n" );
}


void
create_spells()
{
    set_name("tome");
    set_short("dusty tome");
    set_long(break_string(
	  "An air of magic emanates from the dusty tome. It has "
	+ "curly golden letters written on the front. "
	+ "You are unable to make out what they say, they must be written "
	+ "in some ancient handwriting. The tome does have a decipherable "
	+ "tomeindex, though. At least some parts of that page look "
        + "readable.\n",70));

    add_item(({"letters","golden letters"}), "The curly golden letters "
	+ "are gibberish for you.\n");

    set_adj("dusty");

    add_prop(OBJ_I_WEIGHT, 457);
    add_prop(OBJ_I_VOLUME, 503);

    /* And we have these spells... */
    add_spell("stop!", "do_stop_spell", "stop fighting");
    add_spell("melt!", "do_melt_spell", "melt armour");
    add_prop(OBJ_M_NO_DROP, "@@wiz_check");
/* This prevents autoloading?
    add_prop(OBJ_M_NO_GIVE, "@@wiz_check");
*/
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
}

void
init()
{
    if (this_player() == environment())
       this_player()->add_prop("_freed_orc_prisoner_",1);
    add_action("do_read","read");
    add_action("do_tear","tear");
}


string
query_auto_load()
{
    return MASTER_OB(this_object()) + ":";
}

void
init_arg(string str)
{
    return;
}

string
wizinfo()
{
   return "Members of an occupational fighter guild cannot use this.\n";
}

int
do_read(string str)
{
    object tp;

    notify_fail("Read what?\n");
    if (!str)
	return 0;

    tp = this_player();
    str = lower_case(str);

    if (str == "tome" || str == "dusty tome")
    {
	notify_fail("The dusty tome is too big to read at once.\n"
		  + "Read the index to make a selection.\n");
	return 0;
    }

    /* Fighters are strong enough. They don't get to use this tome */
    if (tp->query_guild_style_occ() == "fighter")
    {
	say(QCTNAME(tp) + " opens " + tp->query_possessive() + " dusty tome "
	  + "and tries to decipher the contents.\n"
	  + "After staring a while, " + tp->query_pronoun() + " tears it up in anger.\n");
	write("You open the dusty tome and try to decipher the index.\n"
	    + "After a moment of staring, you decide that it was probably meant for sissy\n"
	    + "magic-users. Real "
           + ((tp->query_gender() == G_MALE) ? "men" :
             (( tp->query_gender() == G_FEMALE) ? "women" : "beings"))
	    + " don't need that stuff anyway. It's their loss.\n"
	    + "You tear the tome up in anger.\n");
	remove_object();
	return 1;
    }
    if (str == "tomeindex")
    {
	say(QCTNAME(tp) + " opens " + tp->query_possessive() + " dusty tome "
	  + "and starts reading it.\n");
	write("You open the dusty tome on the index. You read:\n"
	+ "    Ye olde book of Great Magick ande High Spellcraft.\n"
	+ "\n"
	+ "    Instans Paecissimus ............ Tomepage 1\n"
	+ "    Shrinkissime Armorilla ......... Tomepage 2\n"
	+ "    Getting rid of the tome ........ Tomepage 9\n"
        + "\n"
        + "The rest of the index is unfortunately unreadable.\n");
	return 1;
    }
    if (str == "tomepage 1")
    {
	say(QCTNAME(tp) + " opens " + tp->query_possessive() + " dusty tome "
	  + "and starts reading it.\n");
	write("You open the dusty tome on tomepage 1. You read:\n"
	+ "     Instans Paecissimus\n"
	+ "     -------------------\n"
	+ "\n"
	+ "     The mighty spell of Instans Paecissimus is used by powerfull\n"
	+ "     spellcasters to stop all hostilities in a room.\n"
	+ "     This spell can only be cast if the proper ingredient, \n"
	+ "     the rare tree-mushroom, is held by the spellcaster.\n"
	+ "     Novice spellcasters will probably not succeed in casting\n"
	+ "     this spell.\n"
	+ "     Cast this spell with \"stop!\".\n");
	return 1;
    }
    if (str == "tomepage 2")
    {
	say(QCTNAME(tp) + " opens " + tp->query_possessive() + " dusty tome "
	  + "and starts reading it.\n");
	write("You open the dusty tome on tomepage 2. You read:\n"
	+ "     Shrinkissime Armorilla\n"
	+ "     ----------------------\n"
	+ "\n"
	+ "     This powerfull spell was invented by accident by a novice\n"
	+ "     sorceror who wanted to cast a 'warm up' spell on a knight\n"
	+ "     who felt cold. The spell did not warm up the knight, but\n"
	+ "     instead melted his armour, rendering it useless. The only\n"
	+ "     things left on the knights body were his magically protected\n"
	+ "     undergarment and his unworn gloves.\n"
	+ "     Skillfull spellcasters will be able to cast this spell\n"
        + "     successfully on an opponent, doing more damage when they\n"
	+ "     are more skilled.\n"
	+ "     To cast this spell, one needs a piece of cast iron, which\n"
	+ "     can usually be found in forges.\n"
	+ "     Cast this spell with \"melt! <opponent>\".\n");
	return 1;
    }
    if (str == "tomepage 9")
    {
	say(QCTNAME(tp) + " opens " + tp->query_possessive() + " dusty tome "
	  + "and starts reading it.\n");
	write("You open the dusty tome on tomepage 9. You read:\n"
	+ "     Getting rid of this tome\n"
	+ "     ------------------------\n"
	+ "\n"
	+ "     If you are not pleased with this tome anymore, you can\n"
	+ "     simply tear it apart.\n");
	return 1;
    }

    /* Read was not meant for us */
    return 0;
}


int
do_tear(string str)
{
    object tp, *obs;
    string what;

    notify_fail("Tear what?\n");
    if (!str)
	return 0;

    str = lower_case(str);

    if (!sscanf(str, "%s apart", what))
	return 0;

    tp = this_player();
    obs = FIND_STR_IN_OBJECT(what, tp);

    notify_fail("Tear what exactly apart?\n");
    if (!sizeof(obs) || sizeof(obs) > 1)
	return 0;

    if (obs[0] != this_object())
	return 0;

    write("You tear the tome apart.\n");
    say(QCTNAME(tp) + " tears " + tp->query_possessive() + " tome apart.\n");
    remove_object();
    return 1;
}

/* Wizards may give the tome to someone else */
int
wiz_check()
{
    if (this_player() && this_player()->query_wiz_level())
    {
        alarm_id = set_alarm(1.0,0.0,&check_carry());
	return 0;
    }
    else
	return 1;
}

void
check_carry()
{
    remove_alarm(alarm_id);
    if (!living(environment()) || environment()->query_npc())
	remove_object();
}

/*************************************************************************
 *
 *	Standard checks before a player is allowed to cast a spell:
 *	   + is the player a ghost?
 *	   + is the player a true Hin Warrior?
 *	   + does the player have all magical ingredients?
 *	   + does the player have enough mana?
 *	   - does the player have high enough skills?
 *
 *	And afterwards:
 *	   - remove the magical ingredients
 *	   - subtract the used mana
 *	   - perhaps add a little skill?
 *
 *					(+) handled in check_player().
 */


/*
 * Function name:   check_player
 * Description:     Check if the player matches a few tests. If not, the
 *                  reason is returned.
 * Arguments:       who: The player to check
 *                  ingr: if 0, then no magical ingredients are checked.
 *                        if object or list of objects, check if the player
 *                        posesses all of them.
 *                  mana: Required mana to cast the spell
 * Returns:         0 if the player turns out to be okay, the string
 *		    with the errormessage if something is wrong.
 */
mixed
check_player(object who, mixed ingr, int mana)
{
    int i;
    return "The ancient magic once contained within the tome has "
        + "forever been lost.\n";
        
    /* Test for ghosts */
    if (who->query_ghost())
	return "You cannot do that in your state.\n";

    /* Make sure that wizards can always cast it */
    if (who->query_wiz_level())
	return 0;

    if (environment(who)->query_prop(ROOM_I_NO_MAGIC))
    {
        return "The surroundings demand to remain void of magic.\n";
    }

    if (environment(who)->query_prop(ROOM_I_NO_MAGIC_ATTACK) ||
        environment(who)->query_prop(ROOM_I_NO_ATTACK))
    {
        return "The surroundings demand that you remain peaceful.\n";
    }

    if (who->query_guild_style_occ() == "fighter")
	return "True fighters cannot cast such a spell.\n";

    /*
     * Test for all magic ingredients
     */
    if (ingr)
    {
    	if (objectp(ingr))
	    ingr = ({ ingr });

	for (i=0; i < sizeof(ingr); i++)
	{
	    if (!present(ingr[i],who))
		return "One of the magic ingredients is missing!\n";
	}
    }

    /*
     * Test if enough mana
     */
    if (who->query_mana() < mana)
	return "You do not feel strong enough to cast the spell.\n";

    /* Passed all tests successfully */
    return 0;
}


/*
 * Function name:   find_ingr
 * Description:	    Finds the ingredients in a person.
 * Arguments:	    ingr: A string or an array of string of ingredients
 *			  It is advisable to give your special ingredients
 *			  a special extra name, like "MY_CARROT", so not
 *			  anyones carrot will be recognised...
 *		    who:  The person to be checked for the objects.
 * Returns:	    An array with the objects found, might be empty.
 */
object *
find_ingr(mixed ingr, object who)
{
    int i;
    object ob, *return_arr;

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
 * Function name:   lose_random_ingr
 * Description:	    Destructs one random ingredient with a chance of 1/3th,
 *                  and tells the player that it happened.
 * Arguments:	    ingr: An array of objects of ingredients, as returned
 *                  by find_ingr()
 */
void
lose_random_ingr(object *ingr)
{
    int ran;

    if (sizeof(ingr))
    {
        if (random(3))
            this_player()->catch_msg("Luckily you manage to keep all "
            + "ingredients intact.\n");
        else
        {
            ran = random(sizeof(ingr));
            this_player()->catch_msg("Unfortunately you lose the "
            + ingr[ran]->short() + " in the process.\n");
            ingr[ran]->remove_object();
        }
    }
}


/*
 * Function name:   remove_ingr
 * Description:	    Destructs all ingredients, and tells the player that
 *		    it happened.
 * Arguments:	    ingr: An array of objects of ingredients, as returned
 *			  by find_ingr()
 */
void
remove_ingr(object *ingr)
{
    int s, i;
    string wrt, *str_arr;

    if (!ingr || !sizeof(ingr))
        return;

    wrt = "You sacrificed ";
    s = sizeof(ingr);

    if (s == 1)
        wrt += LANG_ADDART(ingr[0]->short()) + ".\n";
    else
    {
	str_arr = map(ingr, "map_short", this_object());
        wrt += LANG_ADDART(implode(str_arr[0..(s-2)], ", "))
             + " and " +  LANG_ADDART(str_arr[s-1]) + ".\n";
    }
    this_player()->catch_msg(wrt);

    /* And remove the ingredients */
    for (i=0; i < s; i++)
	ingr[i]->remove_object();
}

string
map_short(object obj)
{
    return obj->short();
}

int shire_factor(object who)
{
    return (who->test_bit("Shire", 0, 0) + 1);
}


/*************************************************************************
 *
 *  The actual spells
 */

/*
 * Function name:   do_stop_spell
 * Decription:	    Cast the stop fighting spell.
 * Returns:	    1 if spell was cast, 0 otherwise.
 */
mixed
do_stop_spell()
{
    object tp, env, *ob_arr, *ingr_arr, obj;
    int i, power, is_wiz, success;
    string fail;

    tp = this_player();
    is_wiz = tp->query_wiz_level();
    env = environment(tp);

    if (present("statuette of nob nar", environment(tp)))
	return "It is unnecessary to cast that spell here.\n";

    if (fail = check_player(tp, SP_STOP_INGR, SP_STOP_MANA))
	return fail;

    if (env->query_prop(OBJ_I_NO_MAGIC))
    {
        log_tome_spell(tp->query_name(), "Stop", "Tried using it in OBJ_I_NO_MAGIC environment.");
        return "Spells cannot be cast in these surroundings.\n";
    }    

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_STOP_INGR, tp);

    /* Let's see if the player can cope with the task... */
    if (!is_wiz &&
        (success = tp->resolve_task(TASK_DIFFICULT,
              ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT,
                 SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END,
                 SS_FORM_CONJURATION,SS_ELEMENT_EARTH }) )) <= 0)
    {
	tp->catch_msg("You fail to cast the spell correctly.\n");
	tell_room(environment(tp), QCTNAME(tp) + " fails to cast a spell "
		+ "correctly.\n", tp);
	lose_random_ingr(ingr_arr);
	return 1;
    }

    tell_room(env, QCTNAME(tp) + " calls upon Nob Nar to stop all "
	+ "fighting.\n", tp);
    tp->catch_msg("You call upon Nob Nar to stop all fighting.\n");

    if (env->query_prop(ROOM_I_INSIDE))
    {
       tell_room(env, break_string(
          "Outside you hear a deep rumble. "
        + "Suddenly a bolt of lightning cuts through the ceiling and impacts "
        + "on the floor! "
        + "When the light is gone, you see a statuette has appeared on that "
        + "same spot.\n",70));
    }
    else
    {
       tell_room(env, break_string(
          "Clouds gather above you and form a dense, gray blanket. "
        + "Suddenly a bolt of lightning springs from the clouds and impacts "
        + "on the floor! "
        + "When the light is gone, you see a statuette has appeared on that "
        + "same spot.\n",70));
    }

    /* Finally start casting the spell */

    seteuid(getuid());
    obj = clone_object(STAND_DIR + "stop_statue");
    obj->move(env);

    if (success > 30 || is_wiz)
        obj->make_peace(300 * shire_factor(tp));
    else
        obj->make_peace(10 * success * shire_factor(tp));

    /* Make her pay for it */
    tp->add_mana(-SP_STOP_MANA+random(40));

    /* And remove the ingredients */
    if (!is_wiz)
        remove_ingr(ingr_arr);

    tell_room(env, QCTNAME(tp) + " casts a spell successfully.\n", tp);
    tp->catch_msg("You cast the spell successfully.\n");

    log_tome_spell(tp->query_name(), "Stop", "Location - " + file_name(env));

    return 1;
}


int
filter_living(object obj)
{
    return living(obj);
}


/*
 * Originally we melted every armour, but that is too strong.
 * Either the damage should be divided by the number of affected
 * armours, or the damage should be done to only one armour.
 * Because I'm lazy, I chose for that last option. ;-)
 * Hmmm. Okay, so people complain about that, so I damage the
 * best armour. That'll please them. ;-)
 */

object
find_best_armour(object target)
{
	int i,max_i, max;
	object *arm_arr;
	
	max_i = 0;
	max = 0;
	
/* Find all worn pieces of armour */
    arm_arr = filter(all_inventory(target),"filter_worn_armours",
			   this_object());
    if (!sizeof(arm_arr))
		return 0; 
    else for (i = 0; i < sizeof(arm_arr); i++)
	{
		if (arm_arr[i]->query_ac() > max)
		{					
			max 	= arm_arr[i]->query_ac();
			max_i = i;
		}
	}
	return arm_arr[max_i];
}

/*
 * Function name:   do_melt_spell
 * Decription:	    Cast the melt armour spell.
 * Arguments:	    who: the person whose armour is to be melted.
 * Returns:	    1 if spell was cast, 0 otherwise.
 */
mixed
do_melt_spell(string who)
{
    object *arm_arr, target, tp, env, ob_arr, *ingr_arr, *obs;
    string arm_short, how, tmp, fail;
    int i, power, is_wiz, success, old_ac, new_ac, damage;

    tp = this_player();
    is_wiz = tp->query_wiz_level();
    env = environment(tp);

    if (!who)
	return "Cast the spell on who?\n";

    obs = FIND_STR_IN_OBJECT(lower_case(who),environment(tp));

    if (sizeof(obs) != 1)
        return "Cast the spell on who?\n";

    target = obs[0];

    if (target->query_prop(OBJ_I_NO_MAGIC))
    {
        return "Spells cannot be cast on that target.\n";
    }    
    if (target->query_prop(OBJ_I_NO_ATTACK) ||
        target->query_prop(OBJ_I_NO_MAGIC_ATTACK))
    {
        return "You cannot seem to cast this spell on that target now.\n";
    }
    
    /* Check if the spell can be cast */
    if (fail = check_player(tp, SP_MELT_INGR, SP_MELT_MANA))
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_MELT_INGR, tp);

    if (!is_wiz &&
        (success = tp->resolve_task(TASK_DIFFICULT,
              ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT,
               SKILL_WEIGHT, 90, SKILL_AVG, TS_WIS, TS_INT, SKILL_END,
               SS_FORM_TRANSMUTATION, SS_ELEMENT_EARTH}))) <= 0)
    {
	tp->catch_msg("You fail to cast the spell correctly.\n");
	tell_room(environment(tp), QCTNAME(tp) + " fails to cast a spell "
		+ "correctly.\n", tp);
	lose_random_ingr(ingr_arr);
	return 1;
    }

    if (is_wiz)
		success = 200;

	arm_arr = ({ find_best_armour(target) });
	if(!arm_arr[0]) 
		return capitalize(who) + " doesn't wear any armour!\n";

    /* Start casting the spell */
    tp->catch_msg("You successfully cast a melt armour spell on "
				  + capitalize(who) + "...\n");
    tell_room(env, QCTNAME(tp) + " casts a spell on " + QCTNAME(target)
			  + ".\n", tp);

    log_tome_spell(tp->query_name(), "Melt", "Location - " + file_name(env));

    for (i=0; i < sizeof(arm_arr); i++)
    {
        arm_short = arm_arr[i]->short();

        /* Is the object resistant to magic? */
        if (arm_arr[i]->query_prop(MAGIC_I_RES_FIRE)
            || arm_arr[i]->query_prop(OBJ_I_RES_FIRE)
            || arm_arr[i]->query_prop(OBJ_I_RES_MAGIC)
            || arm_arr[i]->query_prop(MAGIC_I_RES_MAGIC))
        {
            how = " resists the spell.\n";
            log_tome_spell(tp->query_name(), "Melt", arm_short + " resist the spell!");
        }
        else
        {
            how = " glows bright yellow and then turns black!\n";

            log_tome_spell(tp->query_name(), "Melt", arm_short + " gets damaged (blackened)!");
        
            if (success > 200)
                success = 100 * shire_factor(tp);
            else
                success = success/2 * shire_factor(tp);
        
            damage = (30*success)/100;
            old_ac = arm_arr[i]->query_ac();
            new_ac = old_ac - damage;

            if (new_ac < 0)
                new_ac = 0;

            arm_arr[i]->set_ac(new_ac);

            if (sscanf(arm_arr[i]->short(), "%s (blackened)",tmp) == 0)
                arm_arr[i]->set_short(arm_short + " (blackened)");

            arm_arr[i]->add_prop(OBJ_I_BROKEN,1);
            target->remove_broken(1);
        }

        tp->catch_msg(break_string(capitalize(who)+"'s "+arm_short + how,70));
	target->catch_msg(break_string("Your " + arm_short + how,70));

	tell_room(env,
	 ({ break_string(target->query_name() + "'s " + arm_short + how,70),
	    break_string(target->query_The_name()+"'s " + arm_short + how,70)
	 }), ({tp,target}));

      /*  Leave the armour on if it didn't melt! */
      if(new_ac == old_ac)
      {
        target->catch_msg("Your armour is quite warm, but you "+
          "manage to keep it on.\n");
    /* Make her pay for it and remove the ingredients */
    if (!is_wiz)
    {
	tp->add_mana(-SP_MELT_MANA+random(20));
        remove_ingr(ingr_arr);
    }
    return 1;
      }
        /* Remove the armour if it is too hot */
        if (new_ac == 0)
        {
            target->catch_msg("Your armour is too hot! You remove it!\n");
            arm_arr[i]->remove_me();
        }
    }


    /* Make her pay for it and remove the ingredients */
    if (!is_wiz)
    {
	tp->add_mana(-SP_MELT_MANA+random(20));
        remove_ingr(ingr_arr);
    }
    return 1;
}

int
filter_worn_armours(object obj)
{
    if ((function_exists("create_object",obj) == "/std/armour")
	     && obj->query_worn())
        return 1;
    return 0;
}
