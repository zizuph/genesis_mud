/*
 * This is a newer nastier form of poison for humbleleaf
 * which in it's old form was to powerfull
 * some of the effects desidered aren't directly achievable
 * throught the system set up in poinson_effect, but I've
 * made it so that there should be no problems with
 * compatibility with existing code
 * McCram (for Roke) March/97
 * The code relating to the paralysis is similar to the code
 * in the stun.c for the monks because thats what I used
 * as the basis for some of this code and thanks to mercade
 * for some technical advice
 */

#pragma save_binary

inherit   "/std/poison_effect";
#include  "/sys/poison_types.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"

#define   HUMBLE_PROP "_humble_prop"
#define   POISON_TIME 100

#define MAYDO ({"commune","quit","look","v","vitals","help","groan",\
		"moan", "whine","drop","put"})
#define MIGHTDO ({ "north", "south", "east", "west", "up", "down", "in", \
			"out", "northeast", "northwest", "southeast", "southwest",\
			"say"})

int prop_val, dex_val, aware_val, climb_val, acrobat_val, loc_val;
int aware_ext, climb_ext, acrobat_ext, loc_ext;
int inactive, stored;
/*float stuntime,waittime;*/

int
stop(string str)
{
	string verb;

	/* Only paralyze our environment */
	if (environment(this_object()) != poisonee)
		return 0;

	//wizards affected?
	if (this_player()->query_wiz_level())
	 {
		return 0;
	}

	verb = query_verb();

	if (member_array(verb, MAYDO) != -1)
		return 0;

	if (member_array(verb, MIGHTDO) == -1)
	{
		write("You are not able to do that.\n");
		return 1;
	}

	write("You couldn't manage to do that.\n");
	return 1;
}

void
entered_coma()
{
	if (environment(this_object()) != poisonee)
		return;
	poisonee->add_stun();
	add_action("stop", "", 1);
        poisonee->add_prop(LIVE_S_EXTRA_SHORT," is paralysed");
}

void
deactivate_coma()
{
        if (objectp(poisonee))
	{
		poisonee->remove_stun();
		poisonee->remove_prop(LIVE_S_EXTRA_SHORT);
	}
}

create_poison_effect()
{
	::create_poison_effect();

	set_name("humble_poison");
	set_interval(5);
	set_time(POISON_TIME);
	set_poison_type("herb");
	set_strength(50);
	set_silent(1);

	set_damage(({POISON_HP,30,POISON_MANA,30}));

	inactive = 0;
	stored = 0;
}

start_poison()
{

   ::start_poison();

   prop_val = poisonee->query_prop(HUMBLE_PROP);
   prop_val++;
   poisonee->add_prop(HUMBLE_PROP,prop_val+10);

   switch(prop_val)
   {
   case 1..3:
	   {
		   poisonee->set_invis(1);
		   write("You are now invisible.\n" +
			   "You feel a numbness spreding over your skin.\n");
			break;
		}
	case 4:
		{
			poisonee->set_invis(1);
			write("You are now invisible.\n");
			write(break_string("You're hands become numb " +
				"and you start to loose control of your " +
				"facial muscles.\n",70));
			break;
		}
	case 5..6:
		{
			poisonee->set_invis(1);
			write("You are now invisible.\n");
			write(break_string("Your skin goes completely numb. " +
				"Pieces of your body refuse to work.\n",70));

			aware_val = poisonee->query_skill(SS_AWARENESS);
			aware_ext = poisonee->query_skill_extra(SS_AWARENESS);
			aware_ext = aware_val + aware_ext - 1;
			if (aware_val)
				poisonee->set_skill_extra(SS_AWARENESS,
				(poisonee->query_skill_extra(SS_AWARENESS)
				- aware_ext));

			climb_val = poisonee->query_skill(SS_CLIMB);
			climb_ext = poisonee->query_skill_extra(SS_CLIMB);
			climb_ext = climb_val + climb_ext - 1;
			if (climb_val)
				poisonee->set_skill_extra(SS_CLIMB,
				(poisonee->query_skill_extra(SS_CLIMB)
				- climb_ext));

			acrobat_val = poisonee->query_skill(SS_ACROBAT);
			acrobat_ext = poisonee->query_skill_extra(SS_ACROBAT);
			acrobat_ext = acrobat_val + acrobat_ext - 1;
			if (acrobat_val)
				poisonee->set_skill_extra(SS_ACROBAT,
				(poisonee->query_skill_extra(SS_ACROBAT)
				- acrobat_ext));

			loc_val = poisonee->query_skill(SS_LOC_SENSE);
			loc_ext = poisonee->query_skill_extra(SS_LOC_SENSE);
			loc_ext = loc_val + loc_ext -1;
			if (loc_val)
				poisonee->set_skill_extra(SS_LOC_SENSE,
				(poisonee->query_skill_extra(SS_LOC_SENSE)
				- loc_ext));

			dex_val = poisonee->query_stat(SS_DEX);
			if (dex_val > 10)
			{
				dex_val = dex_val - 10;
				poisonee->add_tmp_stat(SS_DEX,-dex_val,POISON_TIME);
			}
			break;
		}
	default:
		{
			write(break_string("You feel the toxin grab your " +
                          "spine. You feel yourself helplessly " +
                          "slipping into paralysis. " +
                          "\n",70));

			dex_val = poisonee->query_stat(SS_DEX);
			if (dex_val > 10)
			{
				dex_val = dex_val - 10;
				poisonee->add_tmp_stat(SS_DEX,-dex_val,POISON_TIME);
			}

			entered_coma();

			break;
		}
	}
}

timeout()
{
	write("You are visible again. \n");
	write(break_string("You feel the toxin leech from your body, " +
		"yet bits of you are still numb.\n",70));

	prop_val = poisonee->query_prop(HUMBLE_PROP) - 10;
	poisonee->add_prop(HUMBLE_PROP,prop_val);

	if ((prop_val > 4) && (prop_val <= 6))
	{
		 if (aware_val)
			  poisonee->set_skill_extra(SS_AWARENESS,
			  (poisonee->query_skill_extra(SS_AWARENESS)
			  + aware_ext));

		 if (climb_val)
			  poisonee->set_skill_extra(SS_CLIMB,
			  (poisonee->query_skill_extra(SS_CLIMB)
			  + climb_ext));

		 if (acrobat_val)
			  poisonee->set_skill_extra(SS_ACROBAT,
			  (poisonee->query_skill_extra(SS_ACROBAT)
			  + acrobat_ext));

		 if (loc_val)
			  poisonee->set_skill_extra(SS_LOC_SENSE,
			  (poisonee->query_skill_extra(SS_LOC_SENSE)
			  + loc_ext));
	}
	else if (prop_val > 6)
		 deactivate_coma;

	poisonee->set_invis(0);
	::timeout();
}

