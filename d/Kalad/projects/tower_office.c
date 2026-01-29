
/* 
   This is Kalad's office in the tower of realms.
   It is based upon  /d/Genesis/room/info_office.c
   made by Maniac 7/1/97.

   Coder: Korat
   Date:  25/1/1997
   Todo: - Make it more interesting!
 */ 

#include <stdproperties.h>
#include "/d/Genesis/start/human/town/tower.h"

inherit TOWER_OFFICE;

#include "/d/Kalad/defs.h"

int alarmid;
int eventnumber = 0;
int events_is_on = 0;

string *events = (({"Suddenly you see the faint outlines of a huge city "+
    "around you. Several humans walk past you without "+
    "acknowledging your presence at all. They wear mundane clothes "+
    "except a few of them who seem to be well off. Armed men "+
    "wearing emblems of a clenched fist patrol the streets, but "+
    "do not react to you at all. A caravan slowly passes by with "+
    "large beasts bearing the weight of what five men would have "+
    "trouble with. Some chained wretches come dangling after "+
    "the beasts - must be slaves soon to be sold on a market in "+
    "this city. Behind you some men talk with faint voices; You "+
    "catch some of the words but they don't convey much meaning to you. "+
    "As you turn to face them, the image of the city dissipates...\n",
    "The fog seems to change. A weak wind caresses your face "+
    "bringing weak voices to your ears. They sing ... but "+
    "a song not of pleasure. The words are rough but the sentences "+
    "dances. One voice seems to fiercely declare something: "+
    "'Jal z'ress ulu Lolth! Ultrinnan ulu Undraeth!'. "+
    "The voices fade away...\n",
    "Suddenly the fog seems to scatter away! A path forms in it "+
    "and a man clothed in white walks steadily towards you. He "+
    "seems to clutch a cross in his right hand so hard that "+
    "the fingers seems to blend with the white colour of the "+
    "sleeves. Suddenly he stops, with his eyes widening up "+
    "conveying pure schock and fear. A weak sound emits from "+
    "his lips: 'Lord Drakmere, I failed...'. As he falls to "+
    "the ground a ghastly creature is revealed standing behind "+
    "the white clothed body. A wraith! It opens its mouth "+
    "and a stench of decay reaches you. Just as the creature "+
    "leaps towards you, the fog melts together again.\n",
    "In the fog you suddenly think you saw some nomads "+
    "passing close by you. But when you look again, you "+
    "cannot see anything.\n",
    "Cries of wolves howling to the sky shatters the quiet of "+
    "the fog. The cries surround you, closing in slowly "+
    "making you feel you must be their prey of the day. "+
    "In the corner of your eye you suddenly see one of them! "+
    "A huge wolf with a goblin upon it rides past you. Both "+
    "the wolf and the goblin flicker their razor sharp "+
    "teeth while they cry out aloud a vicious shout of "+
    "combat! The clan of the Red Fangs. Only when the sounds "+
    "of their bloodlust weakens do you relax again.\n",
    "Suddenly a huge citygate looms above you. Several "+
    "human guards clothed in chainmail and armed with "+
    "polearms ready to slice up any unwanted guests "+
    "run towards you, and soon have you surrounded. "+
    "A sergeant among them states aloud: 'Intruder! "+
    "None are allowed to enter Cyrabus until ordered "+
    "otherwize!'. The image seems to fade away, and "+
    "you see the guards shout aloud in fear. In their "+
    "eyes you must be fading away just as they fade "+
    "until only the fog is to be seen again.\n",
    "Someone suddeny pokes you in the stomach. You look "+
    "down and see a small dwarven child. He (or is it "+
    "a she?) giggles and emits some rough sounds "+
    "that must be words in the language the child knows. "+ 
    "Just as you are to respond back, you notice a larger "+
    "dwarf rapidly closing in on you, brandishing a vicious "+
    "battleaxe ready to strike! Luckily the fog again "+
    "seems to envelope you, making the dwarves fade away. "+
    "In the last seconds before the image is gone you "+
    "notice the area around you. A huge cavern with "+
    "several ruined stone buildings scattered around you.\n",
    "You close your eyes for a second, wondering about "+
    "the magic that must be in work in this thick fog. "+
    "When you open them again, you stare into the eyes of "+
    "a huge dragon! Black scales shimmer in the weak "+
    "light, and immensive claws along with ebony white "+
    "teeth come at you with a breathtaking speed. "+
    "An oppressive heat envelopes you as the dragon takes "+
    "a deep breath preparing to blow out a sea of black "+
    "flames at you. You close your eyes and prepare for death ... "+
    "but death seems not to arrive. When you open your eyes "+
    "again, the fog is back.\n"}));

/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here (quest orb)
 */
public void
reset_room()
{
    object quest_orb;
    
    if (!present("_genesis_quest_orb"))
    {
        quest_orb = clone_object(QUEST_ORB);
        quest_orb->set_orb_domain("Kalad");
        quest_orb->set_extra_line("The dark crystal orb is floating"
          + " before you, seemingly on the wind.");
        quest_orb->move(this_object(), 1);
    }    
}

void
create_tower_office()
{
    set_long("Your body is embraced by a thick, grey fog "+  
      "that makes it hard to see even your own hands. "+
      "Had it not been for a signpost that glimmers weakly "+
      "with a golden light, you would be lost for eternity ...\n\n"+
      "On the ground beneath the signpost you notice some "+
      "rocks forming an arrow; pointing outwards into the fog.\n");

    add_item("signpost","The signpost emits a weak "+
      "light. Upon it you see a sign with words to read.\n");

    add_item("fog","The fog is thick and embraces you with "+
      "a cold touch. There is some kind of energy in it; "+
      "A pulsating force that you cannot set words to. Magic!\n");

    add_item(({"rock","rocks","arrow"}),"The arrow seems to "+
      "point outwards into the fog. Your only chance of returning "+
      "back to the tower would be to follow that direction.\n");

    add_prop(ROOM_S_MAP_FILE, "domain_office.txt");

    add_item("sign", OFFICE_SIGN_TEXT); 
    add_cmd_item("sign", "read", OFFICE_SIGN_TEXT); 
    disable_logged_in_display(); 
    set_project_dir("/d/Kalad/projects/");
    add_tower_link("fog");

    reset_room();
}

/*
 * start_events()
 * Starts the alarm that echoes text-events to the players in this room.
 *
*/
void
start_events()
{
    alarmid = set_alarm(30.0,60.0,"do_event");
    events_is_on = 1;
    return;
}

/*
 * do_event()
 * Echoes the next text in a list of texts to all players in the room.
 * Will turn off the alarm calling this function if no players are
 * present here.
 *
*/
void
do_event()
{
    object *all_players_here;
    string str;

    all_players_here = FILTER_LIVE(all_inventory(TO));
    if (!sizeof(all_players_here))
    {
	remove_alarm(alarmid); /* remove the repeating alarm! */
	events_is_on = 0;
	return;
    }

    eventnumber = eventnumber + 1;
    if (sizeof(events) < (eventnumber + 1)) eventnumber = 0;

    str = events[eventnumber];
    tell_room(TO, str);
    return;
}

/*
 * init()
 * Is called when an object enters this room.
 * Is used here to start events if the events are not already on.
 *
*/
void
init()
{
    object *all_in_room;
    ::init();

    all_in_room = FILTER_LIVE(all_inventory(TO));
    if (sizeof(all_in_room) && events_is_on == 0)
    {
	start_events();
    }
    return;
}
