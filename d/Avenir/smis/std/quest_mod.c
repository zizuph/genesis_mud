// file name:        /d/Avenir/smis/std/quest.c
// creator(s):       Denis May'96
// purpose:          Standard quest module. Inherit it, if you would like
//		     to code a quest.
#pragma strict_types

#include <macros.h>
#include "../smis.h"
#include "../sys.h"

inherit SMIS_MODULE_PLACER;

static int	gQuest_bitgroup,
		gQuest_bitnum;

static string	gQuest_long_description;

static mixed	*gQuest_variants;

static string caption =
"Quest module: -------------------------------------------------------------\n";
static string bottom =
"---------------------------------------------------------------------v.0.01\n";

void
create_quest()
{
}

nomask void
create_placer()
{
    gQuest_variants = ({ });

    create_quest();

    if(query_module_types())
        set_module_types((query_module_types()- ({ "quest" }))+ ({ "quest" }));
    else
	set_module_types(({ "quest" }));
}

void
reset_quest()
{
}

nomask
void reset_placer()
{
    reset_quest();
}

/*
 * Function name: set_quest_description
 * Description:   The long description of the quest. It is advisable
 *		  to set the general information about the quest here,
 *		  such as where, what and who (WWW).
 * Arguments:     description - the long description
 */
static void
set_quest_long_description(string description)
{
    gQuest_long_description = description;
}

/*
 * Function name: set_marked_bit
 * Description:   What bit to set in the player when the quest is completed.
 * Arguments:     bgroup - bit field (0 - 3)
 *		  
 */
static void
set_quest_bit(int bgroup, int bnum)
{
    gQuest_bitgroup = bgroup;
    gQuest_bitnum = bnum;
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
static void
add_quest_variant(string var_desc, int var_exp, int var_al, int var_pres)
{
    gQuest_variants += ({ ({ var_desc, var_exp, var_al, var_pres }) });
}


/*****************************************************************************
 * Now follow the command handlers.
 */

/*
 * Function name: format_variant
 * Description:   
 * Arguments:     
 * Returns:       
 */
static string
format_variant(mixed *arr)
{
    return arr[0] + "\n" +
	   "Experience: " + arr[1] + "\n" +
	   "Alignment:  " + arr[2] + "\n" +
	   "Prestige:   " + arr[3];
}

public int
perform_about_command()
{
    SMIS_CHECK_CALLER;

    write(gCaption + implode(map(gQuest_variants, format_variant), "\n\n") +
	  "\n" + gBottom);

    return 1;
}

static string
desc_quest()
{
    return "";
}

static nomask string
desc_placer()
{
    return (strlen(gQuest_long_description) ?
	gQuest_long_description + "\n" : "") + desc_quest() +
	" - about:       Shows the information about the quest;\n";
}


/*****************************************************************************
 * Rewarding
 */

public nomask int
reward_quest(object who, int quest_variant)
{
    string	experience_msg,
	   	alignment_msg,
	   	prestige_msg,
	   	log_msg,
	   	quest_type;

    int		experience,
		alignment,
		prestige;

    if(!query_module_enabled() ||
       quest_variant >= sizeof(gQuest_variants))
	return 0;

    experience = gQuest_variants[quest_variant][1];
    alignment  = gQuest_variants[quest_variant][2];
    prestige   = gQuest_variants[quest_variant][3];

    if(!who || !interactive(who))
        return 0;

    if(who->test_bit(OBJECT_DOMAIN, gQuest_bitgroup, gQuest_bitnum))
        return 0;

    if(experience < 1)
	experience = 1;

    // experience given can never be greater than the current experience
    // of the player, based on the guildline in man xp_scale
    experience = MIN(who->query_exp(), experience);

    // Quest types[number] also from man xp_scale
    switch(experience)
    {
    case 1 .. 50:
        experience_msg = "a tiny bit more";
        quest_type = "tour[0]";
        break;
    case 51 .. 100:
        experience_msg = "slightly more";
        quest_type = "serious tour[0]";
        break;
    case 101 .. 1000:
        experience_msg = "a bit more";
        quest_type = "minor assignment[1]";
        break;
    case 1001 .. 10000:
        experience_msg = "more";
        quest_type = "small adventure[2]";
        break;
    case 10001 .. 50000:
        experience_msg = "quite a bit more";
        quest_type = "major adventure[3]";
        break;
    case 50001 .. 100000:
        experience_msg = "much more";
        quest_type = "quest[4]";
        break;

    default:
        experience_msg = "a great deal more";
        quest_type = "ultimate quest[5]";
        break;
    }

    log_msg = ctime(time())+ " " +capitalize(who->query_real_name()) +
              "("+who->query_average_stat()+")"+ 
              " completed " + query_module_id() + "\n"+
              "          " + experience + " exp (" +
              quest_type + ")";

    who->set_bit(gQuest_bitgroup, gQuest_bitnum);
    who->add_exp(experience, 0);
    who->catch_msg("You feel "+experience_msg+" experienced!\n");

    if(alignment)
    {
        // Bound the alignment adjustment based on the
        // guildlines in sman adjust_alignment

        if(alignment < -1000) alignment = -1000;
        if(alignment >  1000) alignment =  1000;

        log_msg += " " + alignment + " align";
        
        if((who->query_alignment() > 0 && alignment < 0 ) ||
           (who->query_alignment() < 0 && alignment > 0 ))
            alignment_msg = "You feel you have gone against your nature " +
			    "and done ";
        else
          alignment_msg = "You feel you have done ";

        switch(alignment)
        {
        case -1000 .. -800:
            alignment_msg += "an unholy act.";
            break;
        case -799 .. -600:
            alignment_msg += "a vile act.";
            break;
        case -599 .. -400:
            alignment_msg += "an evil act.";
            break;
        case -399 .. -200:
            alignment_msg += "a nasty act.";
            break;
        case -199 .. -100:
            alignment_msg += "a mean thing.";
            break;
        case -99 .. -1:
            alignment_msg += "an unpleasant deed.";
            break;
        case 0:
            alignment_msg += "an insignificant action.";
            break;
        case 1 .. 99:
            alignment_msg += "a nice act.";
            break;
        case 100 .. 199:
            alignment_msg += "an amiable act.";
            break;
        case 200 .. 600:
            alignment_msg += "a good act.";
            break;
        case 601 .. 1000:
            alignment_msg += "a holy act.";
            break;

        default:
             alignment_msg += "an insignificant action.";
             break;
        }
        who->adjust_alignment(alignment);
        who->catch_msg(alignment_msg + "\n");
    }

/* 
 * Check to see if there is any prestige for the quest and if
 * the player is a knight.
 * I don't think this will work for the Prestigion Knights'
 * Club, though.
 */
   if(prestige && 
      (who->query_guild_name_occ() == "Solamnian Knights" ||
       who->query_guild_name_lay() == "Sentries of Solamnia" ))
   {
        // Bound the min/max prestige levels based on the guidelines
        // in /d/Krynn/info/EXPORT/PRESTIGE

        if(prestige < -8)
	    prestige = -8;

        if(prestige >  2500)
	    prestige = 2500;

        log_msg += ", " + prestige + " prestige";

        switch(prestige)
        {
        case -8:
            prestige_msg = "you have done an extremely dishonourable act.";
            break;
        case -7 .. -5:
            prestige_msg = "dishonoured by your actions.";
            break;
        case -4 .. -2:
            prestige_msg = "you have done a dishonurable deed.";
            break;
        case -1:
            prestige_msg = "you are slightly dishonoured by your actions.";
            break;
        case 0 .. 50:
            prestige_msg = "you have done a kind deed.";
            break;
        case 51 .. 100:
            prestige_msg = "you have done a prestigious deed.";
            break;
        case 101 .. 200:
            prestige_msg = "you have done a just act.";
            break;
        case 201 .. 500:
            prestige_msg = "you have done a honourable act.";
            break;
        case 501 .. 1000:
            prestige_msg = "you have done a noble act.";
            break;
        case 1001 .. 1500:
            prestige_msg = "you have done a just and noble deed.";
            break;
        case 1501 .. 2000:
            prestige_msg = "you have done a great deed of honour and justice.";
            break;
        case 2001 .. 2500:
            prestige_msg = "you have done a deed of honour worthy of legends.";
            break;
        }
        who->change_prestige(prestige);
        who->catch_msg("You know in your heart that " + prestige_msg + "\n");
    }

    who->save_me();

    // Don't log tests by wizards and jrs
    if(!who->query_wiz_level() &&
       extract(who->query_real_name(), 
               strlen(who->query_real_name()) - 2,
	       strlen(who->query_real_name())) != "jr")
	write_file(SMIS_QUEST_LOG, log_msg + ".\n");

    return experience;
}
