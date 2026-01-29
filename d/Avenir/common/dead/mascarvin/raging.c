// file name:        /d/Avenir/common/dead/mascarvin/raging.c
// creator(s):       Lilith, Aug 2021
// revision history: 
// purpose:         Nearly identical to resting.c, this room is where
//                  players who tried to steal from Mascarvin
//                  are sent to await their punishment.
//                  Since resting.c is the primary room for finishing
//                  the Meet Mascarvin quest, I don't want to tie
//                  it up with this drama.
// note:       If players went LD or Quit out before they've
//             finished this scenario, the dead/obj/poison_thief
//             will bring them back here when it loads.     
//                  
// bug(s):           
// to-do:      
//             1) Need a shadow/curse so if/when they die again
//                they meet her, she takes their bodies, and tosses
//                them over to Lars.
    // TODO-Maybe: SHADOW OR CURSE THAT BRINGS PLAYER TO MASCARVIN AT DEATH.
	// SHE TAKES THEIR BODIES SO THEIR STUFF CANNOT BE RECOVERED 
	// AND PASSES THEM ON TO LARS TO FINISH DEATH SEQUENCE.


inherit "/std/room";
inherit "/d/Avenir/inherit/quest";
#include "/d/Avenir/smis/sys/statserv.h"
#include "defs.h"
#include "/sys/terrain.h"
#include "/d/Avenir/include/macros.h"

int act_index = 0, act_alarm = -1;
object solivagant = 0, mascarvin;

void 
reset_room()
{
     /* Don't reset while there are players here */
//    if (sizeof(filter(all_inventory(TO), interactive)))
//      return;
    if (!objectp(mascarvin))
	{	
		mascarvin = clone_object(MASCARVIN);
		mascarvin->move_living("M", TO);
    }
}

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
    who->cmdhooks_break_spell("Your brain flutters wildly and "
	    +"colors clash in your mind.\nA wave of exhaustion rolls "
	    +"over you and you can feel yourself falling forward.\n");
	who->command("$kneel");
	return 1;
	
}

string
wiz_long()
{
	if (!TP->query_wiz_level())
		return "";
	return "(If a player is here DO NOT TRANS THEM OUT. "
		+"Do <stat here> to read WIZ_INFO.)\n";
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
		+"chorus, whilst a roiling mass presses upon your conscious"
    	+"ness - the psychic remnants of those recently dead and "
    	+"those long forgotten. You have a sense of the multitudes "
	    +"that once lived in the penumbra of the Source, dedicated to "
	    +"the Gods, and gathered to the bosom of Mascarvin for "
	    +"nurturing, awaiting the possibility of rebirth.\n"
		+"@@wiz_long");
	
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
	    +"Mascarvin Quest.\n" 
		+"If the player is in this room it is because they tried "
		+"to steal from the goddess of death and this is a (temporary) "
		+"punishment.\n"
		+"    If they are experiencing a paralyze and/or "
		+"poison, this is normal.\n"
		+"   If they are upset that they were transed back here "
		+"it happened because they went LD or quit or otherwise "
		+"tried to escape their fate and the Goddess is not "
		+"finished with them yet!\n\n"
		+"   DO NOT TRANS A PLAYER OUT OF THIS ROOM!\n\n"
		+"They will be moved out once they've gone through the "
		+"~3 minute sequence. If they seem genuinely stuck then "
		+"tell them to use the non-obvious <pit> exit.\n");
	add_exit(CRYPT+"pit_of_despair","pit", 0, 10, 1);	

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
next_act_thief(int index)
{
    string name;

    if(!objectp(solivagant) || !interactive(solivagant)
        || !present(solivagant))
        return 0;

    if (!present("mascarvin"))
	{
		mascarvin = clone_object(MASCARVIN);
		mascarvin->move_living("M", TO);
    }
		
    name = solivagant->query_name();
    switch(index)
    {
        case 0:
		    solivagant->set_skill(SS_MASQ_STAGE, STAGE_6_THIEF);
			solivagant->MAKE_INFIDEL;
		    mascarvin->command("emote stands regally before you, an "
			    +"expression of disbelief and outrage on her face.\n");
           return 2;
            break;
        case 1:
		    mascarvin->command("emote walks around you, looking you "
			    +"up and down.\n");
			mascarvin->command("scowl at "+ name);
            return 3;
            break;
        case 2:
            mascarvin->command("say Who tries to steal from the Goddess "
			    +"of Death? What were you thinking to try such a thing?");
			mascarvin->command("emote tilts her head as if listening to "
			    +"your thoughts.\n");
            return 15;
			break;
		case 3:
		    mascarvin->command("say Here In Sybarus, stealing is one "
			    +"of just a few crimes that warrants death. It is "
                +"blasphemy, do you hear?\n");
            return 12;
            break;
        case 4:        
            mascarvin->command("say In stealing from another being you "
                +"commit blasphemy. It is tantamount to saying you believe "
                +"the gods have not provided properly for you!");	
            mascarvin->command("say We gods of Sybarus provide for your "
                +"kind as you deserve. As. You. Deserve!");   
            mascarvin->command("say If you want more, then Serve Us Better!\n");         				
            return 13;
            break;
        case 5:
            mascarvin->command("emote shakes her head while looking at "
			    +"you with an expression of infinite sadness on her face.");
            mascarvin->command("say And you -- you tried to steal from me, "
                +"from a god...");
            mascarvin->command("say You really are a simpleton, aren't you?");
			mascarvin->command("emote looks as though something has just "
			    +"occurred to her, and it doesn't bode well for you.");
            mascarvin->command("say Or...are you a tool of that ugly toad "
                +"Nitikas?\n");
            return 15;
            break;
        case 6:        
            mascarvin->command("say That cesspool scum of a god stole my "
                +"granddaughter Tjana and her mother is still sick with "
                +"grief centuries later.\n");
            return 12;
            break;
        case 7:        
            mascarvin->command("say You do not want to know what I do to "
                +"his followers when they cry out on their deathbeds. I "
                +"have no succor nor peace for those who serve the god "
                +"of greed...\n");
            return 14;
            break;
        case 8:        
            mascarvin->command("say There you are, frozen in the grip "
                +"of death, unable to speak, unable to move...");
		    mascarvin->command("say Unable to beseech your gods for "
			    +"aid in this, your hour of need... ");
            mascarvin->command("say Are you frightened yet?");
            mascarvin->command("emote laughs with genuine mirth. The "
			    +"sound of her laughter bounces around the room.\n");
            return 13;
            break;
        case 9:        
            mascarvin->command("say I could kill you, you know. Steal your "
                +"mind and leave your soul roaming the catacombs in decaying "
                +"flesh for eternity.");
			mascarvin->command("say But that isn't very creative.");
			mascarvin->command("say I want to do something FUN with you...\n");
            return 15;
            break;
        case 10:        
            mascarvin->command("say I could give you to the pahloor. "
                +"They love to play with their food...");
            mascarvin->command("emote claps her hands delightedly.");
            mascarvin->command("That would be such entertaining bloodsport!");
            mascarvin->command("Would you like that?\n");
            return 16;
            break;
        case 11:        
            mascarvin->command("emote suddenly looks excited and happy.");
            mascarvin->command("say Oh! I have a better idea!");
            mascarvin->command("clap");
			return 10;
            break;
        case 12:        
            mascarvin->command("emote moves a hand in a twisting "
                +"motion\n\nYou suddenly find yourself dangling upside-" 
				+"down!\n");
            return 6;
            break;
        case 13:        
            mascarvin->command("emote shakes her hand in the air, and "
                +"you feel yourself flung about wildly, with your worldly "
                +"possessions falling to the floor beneath your head.");
			solivagant->command("$drop all");		
            return 10;
            break;
        case 14: 
		    mascarvin->command("emote waggles her hand and laughs delightedly.\n"
			    +"You roll about in the air like a doll in the hand of a child.\n");
            return 5;
            break;
	    case 15: 
		    write("You've been shaken so violently you're starting to feel sick.\n");
            return 5;
            break;
        case 16:         
		    return 5;;
            break;
        case 17:        
        	mascarvin->command("say There! Excellent. A fate worse "
                +"than death is in store for you.\n");
            return 10;
            break;
        case 18:        
            mascarvin->command("say All that you had is now forfeit.\n");
            return 10;
            break;
        case 19:        
            mascarvin->command("say Perhaps going forward you will "
                +"remember not to take what is not freely given...and "
                +"perhaps remember your manners should you find your"
                +"self in the presence of a god again.\n");
            return 10;
            break;
        case 20:        
            mascarvin->command("say I put you on notice, you fool. "
                +"If you see me again it will mean your death, and the "
                +"loss of everything you hold dear once again.\n");
            return 8;
            break;
        case 21:        
            mascarvin->command("say Go, and live all the rest of your "
                +"days in fear.\n");
		    return 8;
            break;
        case 22:        
		    mascarvin->command("emote strokes the side of you face "
			    +"tenderly with a very sharp fingernail.");
            mascarvin->command("say For I am death, and death cannot "
                +"be robbed nor cheated...\n\n");
            return 8;
            break;		
        case 23:        
	        if (!CHECK_QUEST_MASQ(solivagant))
			{	
	            reward_quest("Meet Mascarvin", solivagant, MASQ_GROUP, MASQ_BIT, MASQ_EXP_ALT);
	            SCROLLING_LOG(MASQ_LOG, capitalize(solivagant->query_real_name()) +
				" met Mascarvin, thief version "+ MASQ_EXP_ALT);
	            STATSERV_LOG_EVENT("crypt", "Meet Mascarvin: alt v thief");
			}
		    // Now drop them in the pit of despair.
	        solivagant->move_living("X", CRYPT+"pit_falling");
			// Make the Source react.
            FLUX("\nThe Source above floods the entire cavern with surreal light "
			    +"and a god's rage washes over you.\nSomehow, you know that "
				+"Mascarvin, Goddess of Death and Rebirth, has punished " 
				+"someone for a grevious transgression.\nThe "
				+"light of the Source returns to its normal level.\n\n"); 
	        solivagant = 0;
            act_index = 0;
			
	        return 2;
			break;
		default:
		    return 0;
			break;
	}
    return 1;	
}

/* Alternate sequence of interaction with thieves */
void
do_act_thief()
{
    int next;
    act_alarm = 0;
   
    if(!present(solivagant))
    {
        stop_acting();
        return;
    }
			
    next = next_act_thief(act_index++);
    if(!next)
    {
       stop_acting();
       return;
    }

    act_alarm = set_alarm(itof(next), 0.0, do_act_thief);
}

// Get the sequence going.
// Allow wizards to test room using:
// <Call here start_acting name>
void
start_acting(object who)
{
    if(objectp(solivagant) || sizeof(get_alarm(act_alarm)))
       return;
    solivagant = who;
    act_alarm = set_alarm(1.0, 0.0, do_act_thief);

	// One or both of these should be present already
	// but if not, add them.
    object para, poison;
	if (!present(PARA_ID, who))
		para=clone_object(PARA)->move(who, 1);
	if (!present(POISON_ID, who))
		poison=clone_object(POISON)->move(who, 1);
}

void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    if (present(PARA_ID, to))
       start_acting(to);
}

void
leave_inv(object to, object dest)
{
    ::leave_inv(to, dest);
    if (solivagant == to)
        stop_acting();		
    
}


 