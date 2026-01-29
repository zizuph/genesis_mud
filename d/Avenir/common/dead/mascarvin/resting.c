// file name:        /d/Avenir/common/dead/mascarvin/resting.c
// creator(s):       Lilith, May 2021
// update history:   Lilith, Aug 2021: added some add_items.
//                   Lilith, Sep 2021: updated statserv logging.
// purpose:         
// note:             
//                  
// bug(s):           
// to-do:

inherit "/std/room";
inherit "/d/Avenir/inherit/quest";
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/macros.h"
#include "/sys/terrain.h"
#include "defs.h"

int act_index = 0, act_alarm = -1;
object solivagant = 0, mascarvin, table, portal, throne;


void 
reset_room()
{

    /* Don't reset while there are players here */
    if (sizeof(filter(all_inventory(TO), interactive)))
		return;

    if (!table)
	table=clone_object(OBJ +"table_goddess");
    table->move(TO);
    if (!portal)
	portal=clone_object(OBJ +"portal_torus");
    portal->move(TO);	
    if (!throne)
	throne=clone_object(OBJ +"throne_of_skulls");
    throne->move(TO);
}
/* 
string
door_desc()
{
    if(member_array("east", query_exit_cmds()) != -1)
	return "A skull-shaped opening leads out to the east. ";
    else
	return "";
}
*/
/* You dare cast magic in a god's home, you deserve what you get. */
public int
anti_magic(object who)
{
    /* Don't bother with uncast spells. */
    if (!who->query_prop(LIVE_I_CONCENTRATE))
	return 0;

    who->catch_tell("An oppressive force presses upon you like "+
      "a giant hand closing around you.\n");

    /* hurt him some (but don't kill him) */
    who->heal_hp(-50 - random(100));
    who->add_mana(-50 - random(100));
    who->add_fatigue(-50 - random(100));

    /* break his spell */
    who->cmdhooks_break_spell("Your brain flutters wildly in "
      +"time with your heart.\nA wave of exhaustion rolls "
      +"over you and you can feel yourself falling forward.\n");
    who->command("$kneel");
    return 1;

}


void
create_room()
{
    set_short("Resting place, the Bosom of Mascarvin");
    set_long("Warmth pervades this amorphous space. Close and red-dark, "
      +"it pulses and thrums with numinous energy. "
      +"The air is heavy with an earthy, feminine scent that calls "
      +"up visceral pre-memories of maternal nurturing. The milky mist "
      +"above swirls and flows into the shape of a grinning skull "
      +"that seems to be looking down upon you. "
      +"Anguished cries and contented murmurs echo in a faint "
      +"chorus, whilst a roiling mass presses upon your "
      +"consciousness -- the presence of those recently dead and "
      +"those long forgotten. You have a sense of the multitudes "
      +"that once lived in the penumbra of the Source, dedicated to "
      +"the Gods, and gathered to the bosom of Mascarvin for "
      +"nurturing, awaiting the possibility of rebirth.\n"
      // These items are actually cloned as no_show_obvious in the room.
      +"   There is a dais in the room, and on it, a throne " 
      +"of skulls with a table placed nearby. Opposite it "
      +"is a very large torus, spinning on its edge. "
      +"\n");

    add_item(({"ceiling","mist", "skull", "grinning skull"}),
      "The mist, you now surmise, is the stuff of souls. "
      +"It swirls overhead in the form of a skull "
      +"grinning down at you. It glows just enough to "
      +"illuminate this place.\n");

    add_prop(ROOM_M_NO_TELEPORT, 
      "An angry goddess-figure wreathed in red-gold flames "
      +"appears to prevent you from doing that.\n");
    add_prop(ROOM_M_NO_MAGIC, anti_magic(TP));
    add_prop(ROOM_M_NO_SCRY, "A dark room.\n");

    add_prop(OBJ_S_WIZINFO, "This is the final room of the Meet "
      +"Mascarvin Quest. Player will be in the room for a while "
      +"as a sequence of events unfurls, and their actions have "
      +"real consequences.\n" 
      +"If the player is paralyzed it is because they tried to "
      +"steal from the goddess of death and this is a (temporary) "
      +"punishment.\n"
      +"   NO NOT TRANS PLAYER OUT OF THIS ROOM\n"
      +"unless "
      +"the player has been here for more than 5 minutes. \n"
      +"If the player gets stuck somehow, trans them to "
      +"/d/Avenir/common/dead/mascarvin/maze/skull (the previous "
      +"room)and then do:"
      +"      Call here open_door\nso player can re-enter the room "
      +"and finish the quest.\n");
    // From /d/Avenir/include/macros.h -- This is an 
    // inside room in an underground domain.
	IN;  
    IN_IN;
    set_terrain(({ TERRAIN_SHADOWS, TERRAIN_HASDEAD, TERRAIN_UNDERGROUND,
    	TERRAIN_ROCK }));

    reset_room();
}

public void
stop_acting()
{
    act_index = 0;
    solivagant = 0;
    remove_alarm(act_alarm);
}

/* Meeting with the Goddess of Death */
int
next_action(int index)
{
    string name;

    if(!objectp(solivagant) || !interactive(solivagant)
      || !present(solivagant))
	return 0;

    name = solivagant->query_name();

    switch(index)
    {
    case 0:
	return 2;
	break;
	// Act One, Meet Mascarvin
    case 1:
	tell_room(TO, "A feeling of awe presses down upon you.\n");
	return 3;
	break;
    case 2:
	tell_room(TO, "You feel a divine presence filling the room.\n");
	return 5;
	break;
    case 3:
	mascarvin = clone_object(MASCARVIN);
	mascarvin->move_living("M", TO);

	if(!present(mascarvin))
	    return 0;

	tell_room(TO, QCNAME(mascarvin) + " steps forth from the mist.\n");
	return 3;
	break;
    case 4:
	mascarvin->command("introduce me");	  
	return 10;
	break;
    case 5:
	mascarvin->command("say I see you, " + name + ".");
	// Player has officially met Mascarvin.
	solivagant->set_skill(SS_MASQ_STAGE, STAGE_5_MEET);
	return 10;
	break;
    case 6:
	mascarvin->command("say I have followed your deeds. I was "
	  +"prepared to harvest your soul, but it proved unnecessary.");
	mascarvin->command("say You have made it to a place few who "
	  +"expect to live ever do.");		
	return 10;
	break;
    case 7:
	mascarvin->command("say So, I have decided to let you live.");
	mascarvin->command("smile generously at " + name + ".");		  
	return 12;
	break;
    case 8:
	tell_room(TO, "A deep tone fills the room, low and "+
	  "mournful. The portal stops its spinning.\n"); 
	return 3;
	break;
    case 9:			
	mascarvin->command("emote turns toward the portal.");
	mascarvin->command("say I have a soul to collect. "
	  +"Await my return, don't touch anything, and your "
	  +"patience shall be rewarded.");			
	return 3;
	break;
    case 10:
	mascarvin->command("emote steps into the "
	  +"flame-limned portal.\nThe portal starts spinning "
	  +"again.\n");
	mascarvin->remove_object();					
	return 45;
	break;  
	// Act 2, Mascarvin Returns.		  
    case 11:
	mascarvin = clone_object(MASCARVIN);
	mascarvin->move_living("M", TO);
	tell_room(TO, "The portal stops spinning and Mascarvin steps "
	  +"into the room.\n");		
	return 3;
	break;
    case 12:
	mascarvin->command("emote cradles a body in her arms and "
	  +"sits on the throne of skulls. Pressing their head to "
	  +"her chest, she looks down at you.");			   
	return 6;
	break;
    case 13:
	mascarvin->command("say Once again, you see something few "
	  +"who expect to live ever see.");
	mascarvin->command("say This I do out of love for the people "
	  +"of Sybarus, a reward for their service. I collect their "
	  +"souls and give them peace and nourishment so they may be "
	  +"reborn to serve again.");
	return 8;
	break;
    case 14:
	mascarvin->command("say In this way do the Gods of Sybarus honor those "
	  +"who follow the Pact.");
	mascarvin->command("emote intones: This is our way.");
	return 10;
	break;
    case 15:
	if (!IS_SYBARITE(solivagant))
	    mascarvin->command("say Do your gods care for you so well, I "
	      +"wonder?");
	else
	    mascarvin->command("say So do I reward you for your service, when "
	      +"your time comes, dear sybarite.");	
	return 3;
	break;
    case 16:
	mascarvin->command("say Speaking of rewards, allow me to reward "
	  +"your patience with the earlier interruption.");
	if (!CHECK_QUEST_MASQ(solivagant))
	{	
	    reward_quest("Meet Mascarvin", solivagant, MASQ_GROUP, MASQ_BIT, MASQ_EXP);
	    SCROLLING_LOG(MASQ_LOG, capitalize(solivagant->query_real_name()) +
		" met Mascarvin, got "+ MASQ_EXP +" reward.");
		STATSERV_LOG_EVENT("crypt", "Meet Mascarvin: complete");
	}
	FLUX("\nThe Source reaches a new level of brightness and as its " 
	  +"light touches you, you have a feeling that someone " 
	  +" has pleased the goddess Mascarvin.\n\n");
	return 5;
	break;
    case 17:
	mascarvin->command("emote gestures toward a lacquered kesoit "
	  +"table.");
	mascarvin->command("get food from table");
	return 8;
	break;
    case 18:
	mascarvin->command("say Please, help yourself to whatever you would like.");
	mascarvin->command("eat food");
	return 15;
	break;		
    case 19:
	mascarvin->command("say Sadly, our time has come to an end.");
	mascarvin->command("say My work as the goddess of death is never done.");
	return 15;
	break;		
    case 20:
	mascarvin->command("say This is your last opportunity to take "
	  +"what you would like from my table.");
	mascarvin->command("say I will turn you over to the Chatelaine's "
	  +"good care. She will see you out of the catacombs, if you "
	  +"so desire.");
	return 20;
	break;		
    case 21:
	mascarvin->command("emote turns to look at the body in her "
	  +"arms and shifts it tenderly.");
	mascarvin->command("say May it be many yera til we meet again.");
	return 3;
	break;						
    case 22:
	solivagant->set_skill(SS_MASQ_STAGE, 0);
	solivagant->move_living("X", CRYPT+"crypt_entr");
	solivagant = 0;
	act_index = 0;
	return 2;
    default:
	return 0;
	break;     
    }
}

/* Normal actions for Mascarvin's meetings with mortals */
void
do_act()
{
    int next;
    act_alarm = 0;

    if(!present(solivagant))
    {
	stop_acting();
	return;
    }
    if (present(PARA_ID, solivagant))
    {
	solivagant->move_living("X", RAGING, 1, 1);
	stop_acting();
	return;
    }		

    next = next_action(act_index++);
    if(!next)
    {
	stop_acting();
	return;
    }

    act_alarm = set_alarm(itof(next), 0.0, do_act);
}

void
start_acting(object who)
{
    if(objectp(solivagant) || sizeof(get_alarm(act_alarm)))
	return;
    solivagant = who;
    act_alarm = set_alarm(1.0, 0.0, do_act);
}

void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);
	if (!interactive(to))
		return;
	if (to->query_wiz_level())  // need to do this or wizards are tossed out ;)
		to->set_skill(SS_MASQ_STAGE, STAGE_5_MEET);
	/* Let them Meet Mascarvin */
    if (to->query_skill(SS_MASQ_STAGE) >= STAGE_4_SKULLS)
	    start_acting(to);
    else
	{	
        /* Mortal hasn't done previous stages and doesn't belong here yet */
		to->catch_tell("You get a very strong feeling that you do "
	        +"NOT belong here.\n");
		to->catch_tell("You realize that some powerful being is "
		    +"moving you somewhere else!!!\n");
		to->move_living("X", MASQ+ "maze/skull"); 
	}	
		
}

void
leave_inv(object to, object dest)
{
    ::leave_inv(to, dest);
    if (solivagant == to)
    {
	solivagant = 0;
	stop_acting();
	table->remove_object();	
	mascarvin->remove_object();
	reset_room();		
    }
}



