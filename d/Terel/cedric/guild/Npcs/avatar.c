#pragma save_binary

inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <cmdparse.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"

/*
 * The Minstrel Guild: Avatar of the Muses
 *
 * When a Minstrel dies, his comrades may elect to start a Choir of Mourning.
 * This conjures up an Avatar of the Muses, who stands gaurd over the
 * corpse of the Minstrel and protects his body from looting. 
 *
 * Cedric 6/93
 * sections debugged by Vader, 1/97
 */

/* Globals */
object deader, corpse;
string *singers = ({});
string deader_name;
int power, alarm_id, unreset_id;
float decay_time_left, orig_decay;
mixed *calls;				/* alarms in the corpse */

/* Prototypes */
void stare_at_poor_slob(object who);
void all_used_up();
void deader_arrived();
void react_arrive(object newcomer);
void verify_corpse(int inflate_time);

string
power_desc()
{
    switch (power)
    {
    case 0..60:
	return "You notice something odd about her, and realize with "
	    + "amazement that the avatar is completely translucent!\n";
    case 61..200:
	return "You notice something odd about her, and realize with "
	    + "astonishment that the avatar is slightly translucent!\n";
    case 201..400:
	return "";
    default:
	return "You notice with unease that underneath a truly beautiful "
	    + "female form, the avatar is as solid as a rock. Indeed, "
	    + "her pale white skin seems carved from solid marble. An "
	    + "imposing figure to say the least.\n";
    }
}

void
add_singer(string who)
{
    singers += ({ who });
}

/* Function:	check_singer
 * Description: check to see if this person has already joined the Choir
 * 		that summoned us.
 * Returns:	1 if the person has already joined, 0 otherwise.
 */
int
check_singer(string who)
{
    int i;

    for (i=0;i<sizeof(singers);i++)
	if (singers[i] == who)
	    return 1;
    return 0;
}

/*
 * Function:	inflate
 * Description: each time another minstrel joins the Choir that summoned
 * 		this avatar, the avatar gets a little bigger. The singers
 *		are pumping mana directly into the avatar, and its stats,
 *		skills, and duration go up proportionately. Currently inflate
 *		takes as its argument the guild-stat of the singer and
 *		adds that directly to the avatar power. Check power_desc(),
 *		above, for a rough idea of how power corresponds to combat
 *		strength.
 * Arguments:	who - who just joined the choir
 *		amount - the power being added by the new singer
 */
void
inflate(object who, int amount)
{
    mixed *alarm_info;
    int initial_max_hp = query_max_hp();
    
    add_singer(who->query_real_name());
    power += amount;
    tell_room(environment(TO()),
	      "The music of the choir increases in volume, and the "
	      + "avatar seems somehow more substantial, as if the avatar "
	      + "herself was no more than a manifestation of the music, "
	      + "a mere facet of its power.\n");
    /* better stats */
    set_base_stat(SS_CON, query_stat(SS_CON) + amount / 6);
    set_base_stat(SS_STR, query_stat(SS_STR) + amount / 5);
    set_base_stat(SS_DEX, query_stat(SS_DEX) + amount / 7);
    stats_to_acc_exp();
    /* better skills */
    set_skill(SS_DEFENSE, query_skill(SS_DEFENSE) + amount / 7);
    set_skill(SS_BLIND_COMBAT, query_skill(SS_BLIND_COMBAT) + amount / 8);
    set_skill(SS_UNARM_COMBAT, query_skill(SS_UNARM_COMBAT) + amount / 8);
    /* hit points go up with max hit points, but we've taken some damage */
    set_hp(query_hp() + query_max_hp() - initial_max_hp);
    /* increase duration */
    alarm_info = get_alarm(alarm_id);
    remove_alarm(alarm_id);
    alarm_id = set_alarm(alarm_info[2] + itof(amount), 0.0, all_used_up);

    verify_corpse(amount); /* added to make sure avatar doesn't outlast *
                            * the corpse.  Increases the decay_time
                            * of the corpse - Vader */
    
}

/*
 * Function:	set_deader
 * Description: setup the avatar for the person who died, and record the
 * 		name of the minstrel who started the choir.
 * Returns:	0 if the setup was successful
 *		1 if the guy isn't dead, or corpse wasn't where expected.
 */
int
set_deader(string dead_guy, object started_choir, string av_name)
{
    int i;
    
    set_living_name(av_name);
    deader_name = dead_guy; 
    deader = find_living(dead_guy);
    set_title("Avatar of "+deader->query_muse_name());
    if (deader->query_ghost() == 0)
	return 1;
    set_short("avatar of "+deader->query_muse_name());
    set_long("This stern-looking female figure is clothed entirely in white, "
	     + "and has taken up a protective stance over the corpse of "
	     + deader->query_name()+". She seems surrounded somehow by music, "
	     + "a mournful choir of voices that blend together into a "
	     + "seamless whole, a truly angelic harmony. Though she simply "
	     + "stands there motionless, you suspect that any attempt to "
	     + "touch the corpse would arouse her ire.\n@@power_desc@@");
    corpse = present("corpse of "+dead_guy, environment(TO()));
    if (!corpse)
    {
	tell_room(environment(),
	    "The avatar looks around, and a dark look comes over her face. "
	    + "Whatever she is looking for, its absence clearly fills her "
	    + "with wrath. All around you the sound gives evidence of her "
	    + "fury; peals of thunder echo amongst cries of pain and the "
	    + "ground trembles before her. You cry out in terror as her eyes "
	    + "meet yours and peer deep into their depths. Suddenly she is "
	    + "gone! You sigh in relief as the terrible music fades away.\n");
	return 1;
    }
    corpse->add_prop(CONT_M_NO_REM,"The avatar stares stonily at you, and you "
		     + "know without being told that she will die before "
		     + "letting you rifle the body.\n");
    corpse->add_prop(OBJ_M_NO_GET,"The avatar stares stonily at you, and you "
		     + "know without being told that she will die before "
		     + "letting you near the body.\n");

/* section below modified by Vader.  Causes the decay time to be
 * added to the avatar decay time.  If this is not done, the corpse
 * could expire before the avatar removes the properties, causing 
 * the corpses possesions to vanish forever.
 */

    calls = corpse->query_alarms();
    for (i=0;i<sizeof(calls);i++)
    {
      if (calls[i][1] == "decay_fun")
	{
	    orig_decay = calls[i][2];
            decay_time_left = calls[i][2] + 180.0;
            corpse->set_decay(decay_time_left);
	/*    tell_room(environment(), "Resetting decay time.\n"); */
        }
    } 
    

    
    
    add_singer(started_choir->query_real_name());
    return 0;
}

object
query_deader()
{
    return deader;
}

void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("minstrel_avatar");
    set_race_name("avatar");
    set_gender(G_FEMALE);
    add_prop(LIVE_I_NO_CORPSE, 1);
    default_config_npc(20);
    set_alignment(200);
    set_hp(10000);
    
    set_skill(SS_DEFENSE, 20);
    set_skill(SS_BLIND_COMBAT, 10);
    set_skill(SS_UNARM_COMBAT, 30);

    trig_new("%s 'introduces' %s", "react_introduce");
    alarm_id = set_alarm(180.0, 0.0, all_used_up);

}

/* void verify_corpse   
 * Purpose   - resets corpses decay_time upon each inflate
 * arguments - inflate_time, the amount of time left in the avatar
 */ 
void verify_corpse(int inflate_time)
{
   int i;

   calls = corpse->query_alarms();
   for (i=0;i<sizeof(calls);i++)
   {
      if (calls[i][1] == "decay_fun")
	{
	    decay_time_left = orig_decay + itof(inflate_time);
            corpse->set_decay(decay_time_left);
   /*   tell_room(environment(), "Resetting decay time. \n")
*/
            
	}
    } 
}

void react_arrive(object newcomer)
{
    if (newcomer->query_real_name() == deader_name)
    {	/* the dead person has come back to claim the loot! */
	newcomer->CM("The avatar glances at you briefly, then draws up "
		     + "and salutes you!\n");
	tell_room(environment(),
		  "The avatar glances briefly, then draws up and salutes "
	    + QTNAME(newcomer)+"!\n", newcomer);
	set_alarm(2.0,0.0,deader_arrived);
    }
    else
    {
	newcomer->CM("The avatar glances at you briefly, then looks away "
		     + "again.\n");
	tell_room(environment(),
	    "The avatar glances briefly at "+QTNAME(newcomer)+", then looks "
	    + "away again.\n", newcomer);
    }
}

void 
init_living()
{
    object newcomer = this_player();

    if (!newcomer)
    {
	command("scowl");
	return;
    }
    
    set_alarm(2.0, 0.0, &react_arrive(newcomer));
}

void deader_arrived()
{
    corpse->remove_prop(CONT_M_NO_REM);
    corpse->remove_prop(OBJ_M_NO_GET);
    corpse->set_alarm(decay_time_left, 0.0, &corpse->decay_fun());
    tell_room(environment(),
	     "Her duty complete, the avatar is gone with a flash of light and "
	      + "a crash of sound. The mournful notes of the choir fade away, "
	      + "ending softly on a rising note. A breeze stirs briefly, and "
	      + "once again there is silence...\n");
    remove_alarm(alarm_id);
    remove_object();
}

void all_used_up()
{
    corpse->remove_prop(CONT_M_NO_REM);
    corpse->remove_prop(OBJ_M_NO_GET);
    
    command("sigh");
    tell_room(environment(),
	  "The avatar stirs, and looks about. Apparently not finding "
	  + "the object of her interest, she sighs once more and quietly "
	  + "vanishes from sight. The mournful notes of the choir fade away, "
	  + "ending softly on a rising note. A breeze stirs briefly, and "
	  + "once again there is silence...\n");
    remove_object();
}

void
react_introduce(string person, string who)
{
    object *obs;
    string name, dummy;

    if (sscanf(person, "Ghost of %s", dummy) == 1) {
        name = dummy;
    } else {
        name = person;
    }

    obs = FIND_STR_IN_OBJECT(lower_case(name), environment());
    if (sizeof(obs) == 0 || sizeof(obs) >= 2) return;
    if (!CAN_SEE(obs[0], TO())) return;
    set_alarm(4.0, 0.0, &stare_at_poor_slob(obs[0]));
    return;
}

void stare_at_poor_slob(object who)
{
    string name;

    if (!who || environment() != environment(who)) return;
    name = lower_case(who->query_name());

    if (MEMBER(who)) {
	command("nod respectfully "+name);
    } else {
        who->CM("The avatar favors you with an solemn unblinking stare.");
    }

    return;
}

/*
 * Function:	do_die
 * Description: We shadow do_die in order to take care of a couple of things
 *		before we die. First we release the corpse, so that it may be
 *		taken or looted. If the killer is a Minstrel, we make them
 *		regret it. Finally we go out with a bang, lots of fancy
 *		verbage as we disintegrate (no corpse, since LIVE_I_NO_CORPSE
 *		is set), calling ::do_die to do the dirty deed.
 */
public void
do_die(object killer)
{
    string logfile, *loglines;
    int i;
    
    seteuid(getuid());
    if (MEMBER(killer))
    {
	killer->CM("You deal the fatal blow, and stand triumphant over the "
	+ "fallen "+query_title()+". Yet the victory seems curiously hollow, "
	+ "and your "+ present("minstrel_instrument", killer)->query_name() 
	+ " slips from your suddenly "
	+ "numb fingers. \n");
        write_file(BANISHDIR+killer->query_real_name() +"_banished",
		   "Banished forever from the Minstrels.\n");
	killer->muse_banish();
    }

    killer->CM("The avatar trembles with pain and anger, and gives you "
	       + "a dark look of wrath. All around you the sound gives "
	       + "evidence of her fury; peals of thunder echo amongst "
	       + "cries of pain and the very ground trembles before her. "
	       + "You cry out in terror as her eyes meet yours and peer "
	       + "deep into their depths. Suddenly the avatar is "
	       + "gone! You sigh in relief as the terrible music fades "
	       + "away.\n");
    tell_room(environment(),
	"The avatar trembles with pain and anger, and gives "+QTNAME(killer)
	+ "a dark look of wrath. All around you the sound gives evidence of "
	+ "her fury; peals of thunder echo amongst cries of pain and the "
	+ "ground trembles before her. "+ QTNAME(killer) + "cries out in "
	+ "terror as the avatar's eyes "
	+ "meet "+killer->query_possessive()+" and peer deep into their "
	+ "depths. Suddenly the avatar is "
	+ "gone! You sigh in relief as the terrible music fades away.\n",
	killer);
    corpse->remove_prop(CONT_M_NO_REM);
    corpse->remove_prop(OBJ_M_NO_GET);
    
    ::do_die(killer);
}
