/*
 * File: /d/Avenir/cirion/sphere_soul
 * Created: Cirion, Jan 1999
 * Purpose: Command soul
 *
 * Revisions:
 * 	Lucius, Aug 2017: Cleanups and re-coded.
 *
 */
#pragma strict_types
#include "defs.h"

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>
#include <stdproperties.h>

inherit "/cmd/std/command_driver";

/* It is a real command soul */
public int
query_cmd_soul(void)	{ return 1; }

/* Commands */
public varargs mapping
query_sphere_cmdlist(string sphere)
{
    switch(sphere)
    {
    case SPH_BEAUTY:		return ([
	    "uaccept" : "uaccept_emote",
	      "udust" : "udust_emote",
	      "ulust" : "ulust_emote",
    ]);
    case SPH_DIPLOMACY:		return ([
	    "uadvise" : "uadvise_emote",
	      "uboom" : "uboom_emote",
	    "uchoose" : "uchoose_emote",
	   "uembassy" : "uembassy_emote",
	      "ugift" : "ugift_emote",
	     "ujudge" : "ujudge_emote",
    ]);
    case SPH_DUTY:		return ([
	  "ucasesort" : "ucasesort_emote",
	    "uchoose" : "uchoose_emote",
	     "udefer" : "udefer_emote",
	  "uguidance" : "uguidance_emote",
	      "usigh" : "usigh_emote",
    ]);
    case SPH_FLAME:		return ([
	    "uadvise" : "uadvise_emote",
	      "uboom" : "uboom_emote",
	    "uchoose" : "uchoose_emote",
    ]);
    case SPH_HISTORY:		return ([
	    "uadvise" : "uadvise_emote",
	    "uscribe" : "uscribe_emote",
    ]);
    case SPH_INQUISITION:	return ([
	    "uadvise" : "uadvise_emote",
	      "ucall" : "ucall_emote",
	     "ucrime" : "ucrime_emote",
	     "uglare" : "uglare_emote",
	     "ujudge" : "ujudge_emote",
	  "uremember" : "uremember_emote",
    ]);
    case SPH_INTEL: 		return ([
	    "uadvise" : "uadvise_emote",
	    "ucorpse" : "ucorpse_emote",
    ]);
    case SPH_ISOLATION:		return ([
	     "ualoof" : "ualoof_emote",
	     "udefer" : "udefer_emote",
	   "ushadows" : "ushadows_emote",
	      "ulong" : "ulong_emote",
    ]);
    case SPH_MENTOR:		return ([
	    "uaccept" : "uaccept_emote",
	    "uadvise" : "uadvise_emote",
	    "uberate" : "uberate_emote",
	      "ucall" : "ucall_emote",
	  "uchastise" : "uchastise_emote",
	      "uhips" : "uhips_emote",
	    "uremind" : "uremind_emote",
    ]);
    case SPH_PROTECTION:	return ([
	    "uadvise" : "uadvise_emote",
	   "uapprove" : "uapprove_emote",
	     "ucrime" : "ucrime_emote",
	"ueverything" : "ueverything_emote",
	      "ukata" : "ukata_emote",
	    "uremind" : "uremind_emote",
	     "uswear" : "uswear_emote",
    ]);
    case SPH_TRAINING:		return ([
	  "ubrighten" : "ubrighten_emote",
	    "uchoose" : "uchoose_emote",
	     "udefer" : "udefer_emote",
	  "uguidance" : "uguidance_emote",
	    "ulisten" : "ulisten_emote",
	      "usigh" : "usigh_emote",
    ]);
    case SPH_VENGEANCE:		return ([
	"uaclolthayr" : "uaclolthayr_emote",
	    "ucorpse" : "ucorpse_emote",
	     "ucrime" : "ucrime_emote",
	     "uglare" : "uglare_emote",
	     "ujudge" : "ujudge_emote",
    ]);
    case SPH_VOICE:		return ([
	    "uadvise" : "uadvise_emote",
	  "uchastise" : "uchastise_emote",
	    "uelders" : "uelders_emote",
	      "uhear" : "uhear_emote",
    ]);
    case SPH_WEAPONRY:		return ([
	    "uadmire" : "uadmire_emote",
	"uaclolthayr" : "uaclolthayr_emote",
	      "ukata" : "ukata_emote",
    ]);
    default:	return ([ ]);
    }
}

public mapping
query_union_cmdlist(string sphere)
{
    return ([
    "uaddress" : "uaddress_emote",
    "uapplaud" : "ucheer_emote",
     "uassess" : "uassess_emote",
     "uassist" : "uassist_emote",
        "ubow" : "ubow_emote",
      "ubored" : "ubored_emote",
      "ubrush" : "ubrush_emote",
       "ucare" : "ucare_emote",
     "ucaress" : "ucaress_emote",
     "ucommit" : "ucommit_emote",
    "ucompell" : "ucompell_emote",
    "ucongrat" : "ucongrat_emote",
  "uconfident" : "uconfident_emote",
   "uconsider" : "uconsider_emote",
   "ucontempt" : "ucontempt_emote",
      "ucount" : "ucount_emote",
       "ucurl" : "ucurl_emote",
    "ucurtsey" : "ucurtsey_emote",
        "ucry" : "ucry_emote",
    "udeclare" : "udeclare_emote",
     "udefend" : "udefend_emote",
 "udisapprove" : "udisapprove_emote",
  "udisbelief" : "udisbelief_emote",
    "udiscern" : "udiscern_emote",
    "udisdain" : "udisdain_emote",
    "udisgust" : "udisgust_emote",
       "udown" : "udown_emote",
    "uexamine" : "uexamine_emote",
       "ufall" : "ufall_emote",
      "uflare" : "uflare_emote",
       "uflip" : "uflip_emote",
      "ufocus" : "ufocus_emote",
       "ugaze" : "ugaze_emote",
      "uglint" : "uglint_emote",
     "uground" : "uground_emote",
     "uintent" : "uintent_emote",
       "ukiss" : "ukiss_emote",
       "uknot" : "uknot_emote",
  "uknowledge" : "uknowledge_emote",
      "ulaugh" : "ulaugh_emote",
       "ulook" : "ulook_emote",
    "unervous" : "unervous_emote",
        "unod" : "unod_emote",
       "unote" : "unote_emote",
       "uoath" : "uoath_emote",
   "uoffended" : "uoffended_emote",
    "uoutrage" : "uoutrage_emote",
    "upatient" : "upatient_emote",
      "upeace" : "upeace_emote",
    "upenance" : "upenance_emote",
     "upierce" : "upierce_emote",
     "upledge" : "upledge_emote",
     "upolish" : "upolish_emote",
       "upray" : "upray_emote",
      "uproud" : "uproud_emote",
   "uquestion" : "uquestion_emote",
       "urage" : "urage_emote",
      "uraise" : "uraise_emote",
  "urecognize" : "urecognize_emote",
     "urecord" : "urecord_emote",
     "uregard" : "uregard_emote",
     "ureject" : "ureject_emote",
     "usalute" : "usalute_emote",
     "usecret" : "usecret_emote",
     "usecure" : "usecure_emote",
    "uservice" : "uservice_emote",
      "ushade" : "ushade_emote",
      "ushame" : "ushame_emote",
      "ushock" : "ushock_emote",
    "usilence" : "usilence_emote",
     "usilent" : "usilent_emote",
       "using" : "using_emote",
     "usmooth" : "usmooth_emote",
   "usolitude" : "usolitude_emote",
    "usqueeze" : "usqueeze_emote",
      "ustand" : "ustand_emote",
      "ustare" : "ustare_emote",
     "ustench" : "ustench_emote",
      "ustoic" : "ustoic_emote",
     "ustroke" : "ustroke_emote",
      "uswing" : "ushow_emote",
      "uteach" : "uteach_emote",
      "uthink" : "uthink_emote",
     "uthroat" : "uthroat_emote",
    "utremble" : "utremble_emote",
       "uturn" : "uturn_emote",
    "uuseless" : "uuseless_emote",
       "uwarn" : "uwarn_emote",
       "uwear" : "uwear_emote",
        "uwet" : "uwet_emote",
       "uwill" : "uwill_emote",
     "uworthy" : "uworthy_emote",
    "uwounded" : "uwounded_emote",
]);
}

/*
 * This function is called by occ_soul to print out
 * additional help information.
 */
public void
help_union_spheres(void)
{
    string *cmds, sphere = TP->query_union_sphere();

    if (!strlen(sphere))
	sphere = DEFAULT_SPHERE;

    cmds = sort_array(m_indices(query_union_cmdlist(sphere)));
    write(sprintf("%|78s\n\n      %-#76.4s\n\n",
	    "--- Emotions for the "+ OCC_NAME +" ---",
	    implode(cmds, "\n")));

    cmds = sort_array(m_indices(query_sphere_cmdlist(sphere)));
    write(sprintf("%|78s\n\n      %-#76.4s\n\n",
	    "-- Commands for the Sphere of "+
	    SPHERES[sphere] +" --", implode(cmds, "\n")));
}

public varargs string
u_describe_weapons(int weapon_type = -1,  int weapon_count = 2,
		   int hands_allowed = 0, int require = W_ANYH,
		   object who = this_player())
{
    object wield;
    string desc, *weps = ({ });;

    if (wield = who->query_weapon(W_LEFT))
    {
	if ((weapon_type == -1) || (weapon_type == wield->query_wt()))
	{
	    weps += ({ wield->short() });
	    weapon_count--;
	}
    }
    else if ((require != W_LEFT) && (require != W_BOTH) && (hands_allowed))
	weps += ({ "left hand" });

    if (wield = who->query_weapon(W_RIGHT))
    {
	if ((weapon_type == -1) || (weapon_type == wield->query_wt()))
	{
	    if (weapon_count > 0)
		weps += ({ wield->short() });
	    weapon_count--;
	}
    }
    else if ((require != W_RIGHT) && (require != W_BOTH) && (hands_allowed))
	weps += ({ "right hand" });

    // require that we have 2 weapons
    if ((require == W_BOTH) && (sizeof(weps) != 2))
	desc = "";
    else if (!sizeof(weps))
	desc = "";
    else
	desc = COMPOSITE_WORDS(weps);

    return desc;
}

#include "sphere_soul1.h"
#include "sphere_soul2.h"
#include "sphere_soul3.h"
