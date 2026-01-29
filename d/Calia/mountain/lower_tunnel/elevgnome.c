
/* 
   Elevator gnome (minds the elevator), of the mountain tunnels of Calia.

   Coder: Digit.
   
   Some updates, 28/5/96, Maniac
*/

#pragma save_binary

inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
 
void return_introduce(string who);
 

void 
create_monster() 
{
    set_name("gnosher");
    set_living_name("gnosher");
    set_title("Master of the Moving Room");
    add_name("gnome");
    set_adj(({"excited","bouncy"}));
    set_race_name("gnome");
    set_long("He is a short gnome who can't seem to stop talking.  "+
       "He seems very excited about something, perhaps you should "+
       "stay and listen to him for a while.\n");
 
    set_act_time(1);
    add_act("say HaveYouSeenTheMovingRoomYet,Huh??");
    add_act("say It'sEasierOnTheMulesIfItOnlyTakesPeople"+
       "UpInsteadOfUpAndDownAsWell.");
    add_act("say IHopeTheyAssembleItProperlyThisTime.Last"+
       "TimeItFellApartHalfWayUpWithPeopleStillInIt!");
    add_act("say EnjoyTheRide!It'sPerfectlySafeNow!TrustMe!");
    add_act("emote points towards the opening.");
    add_act("bounce");
    add_act("say IHopeItWorksBetterThisTimeThanLastTime...OhHi!IDidn't"+
       "SeeYouThere!HowAreYouDoing?It'sSafe!TrustMe!!");
	add_act("confused");
	add_act("scratch");
	add_act("say HiThere! ThisIsGnomeCraftsmanshipAtItsFinest!!");
    add_act("giggle");
    add_act("bounce");
    add_act("smile");
    trig_new("%w 'flies' 'out' %s", "react_laugh");
 
    set_stats(({ 60, 60, 60, 60, 60, 60})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_POLEARM, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(10000);
    set_alignment(300);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
    set_tell_active(1); 
}


int
react_laugh(string who, string dummy1)
{
    if (stringp(who))
    {
       who = lower_case(who);
       set_alarm(1.0, 0.0, &command("laugh " + who)); 
       return 1;
    }
}


int
add_introduced(string who)
{
    if (stringp(who))
    {
       who = lower_case(who);
       set_alarm(1.0, 0.0, &return_introduce(who));
       return 1;
    }
}


void
return_introduce(string who)
{
    object obj;

    if (objectp(obj = present(who, environment())))
    {
       command("introduce me to "+who);
       switch (random(3)) {
          case 0 : command("say VeryNiceToMeetYou,"+obj->query_name()+"!");
                   command("bow to "+who);
                   command("bounce");
                   command("giggle");
                   break;
          case 1 :  command("bow to "+who);
                    break;
          default : command("say Greetings,"+obj->query_name()+"!");
                    command("bow to "+who);
                    break;
       }
    }
}

