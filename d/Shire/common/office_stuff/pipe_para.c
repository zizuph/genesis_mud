inherit "/std/paralyze";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

#define WOUND "/d/Shire/igneous/wound.c"

//  Prototypes
void produce_msgs(int stage, object player);

int flag, dark_prop;

void
create_paralyze()
{
    set_stop_verb("awaken");
    set_stop_message("You awaken from your dream, feeling uneasy and "+
        "your brow is laced with sweat.  You start to wander if it was "+
        "actually a dream, the places and the dangers seemed so real......\n");
    set_fail_message("You are in a middle of a dream and are unable "+
        "do anything...  You may try and 'awaken' if you wish to end "+
        "this dream.\n");
    set_name("paralyze");
    add_name("_shire_smoke_dream_para");
}

void
init()
{
    ::init();
    if (TP != ENV(TO))
        return;
    if (flag)
        return;
    flag = 1;
    produce_msgs(0,TP);
}

void
produce_msgs(int stage, object player)
{
    float time;
    
    switch(stage)
    {
        case 0:
        player->catch_msg("You begin to feel dizzy and fall unconscious to "+
            "the floor!\n");
        tell_room(ENV(player),QCTNAME(player)+"'s eyes roll back and "+
            HE_SHE(ENV(TO))+" falls unconscious to the floor!\n",ENV(TO));
	time = 8.5;
        break;
        case 1: case 7: case 12: case 20: case 24:
        player->catch_msg("\nYour body starts to tingle and you find yourself "+
            "in another place.\n\n");
        time = 5.7;
        break;
        case 2:
        player->catch_msg("You awaken and find yourself floating high "+
	   "above the ground, looking down at the mircoscopic lands "+
	   "below you.  You see a vast grassy plain surrounded by "+
           "forest and mountains to the east and south, with a great body "+
	   "of water expanding as far as the eye can see to the west and to "+
	   "the north of this grassy plain.   This grand plain is known as "+
	   "the Shire, a home of Hobbits, Humans, Elves, Orcs and Trolls.  "+
	   "Usually a quiet peacfully place, with much danger and adventure "+
	   "lurking about.\n");
        time = 10.0;
        break;
        case 3:
        player->catch_msg("Suddenly you swoop down from the sky,\n");
        time = 15.0;
        break;
        case 4:
        player->catch_msg("Hobbiton Scene 1.\n");
        time = 7.0;
        break;
        case 5:
        player->catch_msg("Hobbiton Scene 2.\n");
        time = 8.0;
        break;
        case 6:
        player->catch_msg("Hobbiton Scene 3.\n");
        time = 7.0;
        break;
        case 8:
	player->catch_msg("Give the player a general view of Bree.\n");
	time = 15.0;
	break;
        case 9:
	player->catch_msg("You wander around Bree till you see what must be "+
	    "the local inn.  A wide arch leads you to the inn's courtyard "+
	    "where you glace upon a large signboard in the shape of a "+
            "fat white pony reared up on its hind legs.  Upon reading "+
            "a nearby sign you find out that the name of the inn is the "+
            "Prancing Pony and it is owned by a Mr. Barliman Butterbur.  "+
            "All this travelling has made you a bit thirsty so you "+
            "decide to wander in and order yourself a drink.\n");
	time = 10.0;
	break;
        case 10:
	player->catch_msg("Order a beer :)\n");
	time = 9.0;
	break;
        case 11:
	player->catch_msg("\nMr. Butterbur says:  Here is your beer "+
	     player->query_nonmet_name()+".\nYou reach for your drink "+
	     "but your hand goes right through the mug handle like it wasn't "+
	     "even there.   Butterbur gasps in astonishment and drops "+
             "your drink, which breaks on the floor.\n");
	time = 1.0;
	break;
        case 13:
        player->catch_msg("Atop Weathertop.\n");
        time = 15.0;
        break;
        case 14:
        player->catch_msg("\nYour tumbling ends and you find yourself within "+
            "a dark sinster forest.  You seem to be hopelessly lost and wander "+
            "aimlessly around till you hear some voices.  Thinking them to be "+
            "your salvation to run as towards them...  then you realize that "+
            "the voices are not your salvation from this forest but quite "+
            "possibly your demise.\n");
        time = 10.0;
        break;
        case 15:
        player->catch_msg("\nYou quickly duck into some nearby bushes hoping "+
            "that the trolls, who's voices you heard, do not spot you.\n");
        time = 5.0;
        break;
        case 16:
        player->catch_msg("\nThe black-eyed spotted male troll says: I'm "+
            "hungry!!\nThe black-eyed spotted male trolls stomach grumbles "+ 
            "noisily.\nThe black-eyed spotted male troll says: Some "+
            player->query_race_name()+" meat would sure hit the spot.\n");
        time = 8.0;
        break;
        case 17:
        player->catch_msg("\nThe hairy massive male troll slaps the "+
            "black-eyed male troll!\nThe hairy massive male troll says: "+
            "This talk about "+player->query_race_name()+" meat has made me "+
            "hungry too! I wish you had never mentioned it.\n"+
            "The hairy massive male trolls grumbles noisily.\n");
        time = 9.0;
        break;
        case 18:
        player->catch_msg("\nYou hear a noise from behind you!  Too late a "+
            "troll has spotted you and captured you!!!\nThe brown-skined "+
            "dark-eyed male troll says: Lookie what I got!!  A plump "+
            player->query_nonmet_name()+" fer our dinner.\n"+
	    "The hairy massive male troll grins wickedly.\n"+
            "The hairy massive male troll says: I'll go get our pot!\n");

        time = 9.0;
        break;
        case 19:
        player->catch_msg("\nYou hear one last thing from the trolls then "+
            "everything goes dark.\n\nThe brown-skined dark-eyed male troll "+
            "says: He he that tickles....  Hey where that "+
            player->query_nonmet_name()+" go?\n\n\n");
        time = 1.0;
        break;
        case 21:
        player->catch_msg("Give players a general view of Rivendell.\n");
        time = 15.0;
        break;
        case 22:
        player->catch_msg("Rivendell Scene 1.\n");
        time = 5.0;
        break;
        case 23:
        player->catch_msg("Rivendell Scene 2.\n");
        time = 6.0;
        break;
        case 25:
        player->catch_msg("MORIA!!!!! this should be fun ;)\n");
        time = 17.0;
        break;
        case 26:
        player->catch_msg("\nYou hear the sounds of drums in the distance "+
	    "'Doom, boom, doom'...  the loud rumblings from the drum echo "+
            "loudly throughout the dim, damp mines.  You worry what hideous "+
            "creature would wander around this place beating a drum, and "+
            "for what purpose.....   You dread and wonder thinking of the two "+
            "pale lights that you saw eariler and why they suddenly "+
            "dissapeared...    could it have been some creature watching you "+
            "in the darkness?\n");
        time = 15.0;
        break;
        case 27:
        player->catch_msg("Drums come close the sound of orcs approaching.\n");
        time = 7.0;
        break;
        case 28:
        player->catch_msg("Cornered with the one and Only Balrog.\n");
        time = 13.0;
        break;
        case 29:
        player->catch_msg("\n");
        time = 5.0;
        break;
        case 30:
        player->catch_msg("The Balrog of Moria stands over you "+
	     "and grins a wicked grin.  You are unable to move the "+
             "wound inflected on you by it's flaming whip has made "+
             "it impossible to flee.  You stare at the fiery, moving "+
	     "shadow in horror, awaiting what must be certain death.  "+
	     "You close your eyes and scream in horror as it's blade "+
             "strikes a mortal wound.\n" );
	setuid(); seteuid(getuid());
	//clone_object(WOUND)->move(player);
        time = 2.0;
        break;
        default:
        stop_paralyze(); // We awaken from our dream.
        break;
    }
    stage += 1;
    set_alarm(time,0.0,&produce_msgs(stage,player));
}









