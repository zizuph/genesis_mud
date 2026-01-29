/* death_room.c */
/* Mrpr 901119 */
/* Tintin 911031 */
/* Nick 920211 */

inherit "std/room";

#define DEATH_ROOM "/d/Genesis/room/death/death_room"
#define DEATH "/d/Genesis/room/death/death"
#define DEATH_BADGE "/d/Genesis/room/death/death_badge"
#define WRITE(x) tell_object(pl, x)
#define SPEAK(x) tell_object(pl, "Death says: " + x)

mixed *players = ({});

/*
 * Prototypes
 */
void create_death();
void add_player(object plobj);
void do_remove();
void remove_death_obj(object player);
void remove_player(object plobj);
void mess1(int time, object pl);
void mess2(int time, object pl);
void mess3(int time, object pl);

void
init()
{
    
    object death;
    
    ::init();
    
    death = find_living("moot");
    add_action("cmdfilter", "", 1);
    
    if (this_player() != death)
    {
	if (!this_player()->query_ghost())
	{
	    write("Death says: WHAT ARE YOU DOING HERE? YOUR TIME HAS NOT COME YET. BEGONE!\n");
	    this_player()->move(this_player()->query_default_start_location());
	    return;
	}
	
	add_player(this_player());
	set_heart_beat(1);
    }

}


/*
 * Function name: create_room
 * Description:   Reset the room
 */
void
create_room() 
{
    create_death();
    players = ({ });
    set_short("death's workroom");
    set_long(
"A dark room lighted with a dark light that seems to defy darkness not so much\n" +
"by actually illuminating the room as by being a darkpoint in less dark\n" +
"surroundings. In the strange light (dark?) you can see a centrally placed desk\n" +
"covered with books and diagrams. The walls are covered with bookshelves\n" +
"filled with dark tomes bound in leather that gleam with strange runes.\n\n");
}

/*
 * Function name: create_death
 * Description:   Create death.
 */
void
create_death()
{
    
    object death;
    
    death = clone_object(DEATH);
    death->move( this_object(), 1);
}

/*
 * Function name: heart_beat
 * Description:   Let the actions be governed by time.
 */
void
heart_beat()
{
    
    int align, j, nr;
    
    if (!(nr = sizeof(players)))
    {
	set_heart_beat(0);
	return;
    }
    
    for (j = 0; j < nr; j += 3)
    {
	players[j + 1]++;
	if (players[j + 2] == 0)
	    mess1(players[j + 1], players[j]);
	else if (players[j + 2] == 1)
	    mess2(players[j + 1], players[j]);
	else
	    mess3(players[j + 1], players[j]);
    }

    do_remove();
}

/*
 * Function name: do_read_soul
 * Description:   Get the special read soul messages
 */
void
do_read_soul(object pl)
{
    int align;
            
    align = (int) pl->query_alignment();
            
    if (align < -1000)
    {
                SPEAK(
"YOUR SINS ARE AS MANY AS THE GRAINS OF SAND IN THE DESERT.\n" +
"MAYBE YOU'RE WORSE A MONSTER THAN I! HAHAHAHAHA!\n\n");
    }
    else if (align < -500)
    {
                SPEAK(
"OH WHAT A DESPISABLE BUG WE HAVE HERE. STEALING CANDY FROM\n" +
"BABIES AND BEATING OLD LADIES NO DOUBT. WELL NOW THEY CAN DANCE\n" +
"ON YOUR GRAVE. HAHAHA!\n\n");
    }
    else if (align < -200)
    {
                SPEAK(
"HAVE YOU EVER BEEN TOLD ABOUT REPENTANCE AND ATONEMENT? NO?\n" +
"DIDN'T THINK SO EITHER. YOU WILL BE TOLD NOW HOWEVER,\n" +
"FOR ETERNITY! HAHAHA!\n\n");
    }
    else if (align < 0)
    {
                SPEAK(
"SHAME ON YOU MORTAL ONE! STEALING AND KILLING, IS THAT ALL\n" +
"YOU CAN THINK OF? WELL NOW YOU WILL BE GIVEN TIME TO REGRET YOUR\n" +
"DEEDS. FOR EVER, HAHA!\n\n");
    }
    else if (align == 0)
    {
                SPEAK(
"WHAT A FENCE-CLIMBER WE HAVE HERE! NEVER MADE UP YOUR MIND\n" +
"IN ALL YOUR LIFE, DID YOU? WELL, DON'T WORRY. YOU WON'T HAVE TO\n" +
"NOW EITHER! HAHAHA!\n\n");
    }
    else if (align < 200)
    {
                SPEAK(
"OH WHAT A NICE FELLOW WE HAVE HERE. ALWAYS WALKING THE NARROW\n" +
"ROAD, DID YOU? WELL, YOU'LL NEVER KNOW WHAT THE OTHER ROAD IS LIKE\n"  +
"NOW! HAHAHA!\n\n");
    }
    else if (align < 500)
    {
                SPEAK(
"NEVER SAID A DIRTY WORD IN YOUR LIFE DID YOU? WELL, IT'S TOO\n" +
"LATE TO CHANGE YOUR MIND ABOUT THAT NOW. HAHAHA! NO MR NICE-GUY YOU\n" +
"ARE WHAT YOU WERE. HAHAHA!\n\n");
    }
    else if(align < 1000)
    {
                SPEAK(
"I HEARD THEY WERE OUT OF ARCHANGELS IN HEAVEN. PERHAPS YOU\n" +
"SHOULD APPLY FOR THE JOB? I HOPE YOU KNOW HOW TO PLAY THE HARP,\n" +
"OR THEY'LL GIVE THE JOB TO SOMEONE ELSE! HAHAHA!\n\n");
    }
    else
    {
            SPEAK(
"TRYING TO TAKE THE JOB AWAY FROM GOD, ARE YOU? HAHAHA! LET ME TELL\n" +
"YOU A BIT ABOUT IT BEFORE YOU SIGN ANY PAPERS THOUGH. BAD HOURS AND NO\n" +
"VACATION. BELIEVE ME, YOU DON'T WANT IT!\n\n");
    }
}

/* 
 * Function name: mess1
 * Description:   Standard message you get from death when comming here
 * Arguments:     time - how long the player has been here
 */
void
mess1(int time, object pl)
{
    switch (time)
    {
        case 5:
	    SPEAK("IT IS TIME\n");
	    WRITE("\nDeath lifts his right arm and makes beckoning motion.\n" +
		  "You feel quite certain that if you had been alive you would have died from\n" +
		  "fear on the spot. Strangely enough you don't feel anything like that at all.\n" +
		  "Just a mild curiosity.\n\n");
	    break;

	case 10:
	    SPEAK("NO GLANDS, THAT'S WHY.\n");
	    WRITE("\nDeath seems to smile a bit. On the other hand that's a bit hard to tell.\n" +
		  "It might very well be that that is his normal expression....\n\n");
	    break;

	case 15:	
	    SPEAK("WITHOUT GLANDS YOU FEEL NOTHING, NOTHING AT ALL.\n");
	    WRITE("\nWell, he seems to be right. Instead of being mad with fear you're getting\n" +
		  "a little bored. You wish for something to happen real soon.\n\n");
	    break;

	case 20:
	    SPEAK("COME HERE, I MUST READ YOUR SOUL.\n");
	    WRITE(
"\nDeath steps closer, reaches out a bony hand straight into your chest,\n" +
"grabbing something that is within! You feel a strange internal yank as\n" +
"your very soul is removed for examination...Suddenly Death collects your\n" +
"bodyless essence with great sweeping motions of his skeletal hands and\n" +
"puts you in a small glass orb that he inserts into his right eye socket!\n" +
"You feel a strange blue light from within his eyeless orb penetrate you\n" +
"as he leans over the chart.\n\n");
	    break;

	case 30:
	    do_read_soul(pl);
	    break;

	case 35:
	    SPEAK(
"WELL, I GUESS YOU HAVE DONE YOURS FOR THIS TIME, SEE YOU ON\n" +
"ARMAGEDDON DAY! HAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA!\n\n");
	    WRITE(
"Death removes the orb from his eye and stands up. Suddenly he turns and walks\n" +
"out of the room through the nearest wall, still holding you in his skeletal\n" +
"hand! He walks rapidly through a dark winding corridor, down a staircase to\n" +
"the innermost room in the bottom of the cellar. Finally he stops in front of a\n" +
"door bearing the words 'ETERNITY' in black letters. On the door you can see a\n" +
"small hatch which Death opens with a flick of his hand. From the open hatch\n" +
"you can hear the moaning murmurs of a million souls. Slowly he lifts you to\n" +
"the gaping maw of the hatch.\n\n");
	    break;

	case 40:
	    WRITE("Lars arrives through a rift in the fabric of space.\n");
	    break;
	case 45:
	    WRITE("Lars smiles at you.\n");
	    break;
	case 47:
	    WRITE("Lars whispers something to Death.\n");
	    break;
	case 54:
	    SPEAK("WHAT? OUT OF THE QUESTION! YOU KNOW THAT!\n\n");
	    break;
	case 56:
	    WRITE("Lars sighs deeply.\n");
	    break;
	case 58:
	    WRITE("Lars whispers something to Death.\n");
	    break;
	case 60:
	    SPEAK("REINCARNATION? FOR THIS ONE? HE IS NOT WORTHY OF THAT!\n" +
		  "PLEASE BE SENSIBLE LARS!\n\n");
	    break;
	case 62:
	    WRITE("Lars sulks in the corner.\n");
	    WRITE("Lars leaves through a rift in the fabric of space.\n");
	    WRITE("Death looks at you with something that must be disgust even if it's hard to\n" +
		  "say. His face is not the best suited face for showing expressions, but\n" +
		  "you feel fairly confident about this one.\n\n");
	    break;

	case 70:
	    SPEAK("OH ALL RIGHT THEN! I CAN WAIT. ONE DAY YOU WILL BE MINE ANYWAY!\n\n");
	    WRITE("Suddenly Death hurles you up in the air, you feel a strange sensation as you\n" +
		  "pass through the very walls of the building, out in the open air, through some\n" +
		  "other walls and fairly surprised horses before you finally stop inside another\n" +
		  "building. It seems vaguely familiar...\n\n");
	    break;

	default:
	    break;
    }
}

/*
 * Function name: mess2
 * Description:   Message 2, a little shorter than the first since 
 *		  players tend to get killed over and over again
 */
void
mess2(int time, object pl)
{
    switch (time)
    {
	case 50:
	    SPEAK("IT IS TIME\n");
	    WRITE("Death lifts his right arm and makes a beckoning motion.\n");
	    break;

	case 55:
	    WRITE("\nDeath penetrates you with his big empty orbs. You think you notice\n" +
		  "surprise deep down in there.\n\n");
	    break;

	case 57:
	    SPEAK("YOU AGAIN!!\n");
	    WRITE("Death grumbles and complains.\n\n");
	    break;

	case 59:
	    WRITE("Death ponders deeply.\n");
	    break;

	case 65:
	    WRITE("\nDeath sighs deeply.\n");
	    SPEAK("WELL I PROMISED LARS, I GUESS HE'LL HAVE HIS WAY AGAIN.\n");
	    WRITE("Death sulks in a corner.\n");
	    break;

        case 69:
	    WRITE("Death chuckles to himself.\n\n");
	    break;

	case 70:
	    SPEAK("IT'S EASY TO SEE YOU WILL SOON VISIT ME AGAIN ANYWAY!\n");
	    WRITE("Death moves with surprisingly speed and suddenly you realize you are\n" +
	   	  "somewhere else....\n\n");
	    break;

	default:
	    break;
    }
}

/*
 * Function name: mess3
 * Description:   You get this message if you have died many times
 */
void
mess3(int time, object pl)
{
    switch (time)
    {
	case 45:
	    SPEAK("IT IS TIME, COME HERE.\n");
	    break;

	case 50:
	    WRITE("\nDeaths turns his eyeless orbs towards you.\n\n");
	    break;

	case 52:
	    SPEAK("YOU HAVE BECOME A REGULAR HERE HAVEN'T YOU?\n\n");
	    break;

	case 55:
	    SPEAK("COME HERE, I FEEL LIKE READING YOUR SOUL.\n");
	    WRITE("Death reaches out towards you and you don't dare to look.\n\n");
	    break;

	case 60:
	    do_read_soul(pl);
	    WRITE("Death chuckles deeply.\n\n");
	    break;

	case 62:
	    WRITE("Death turns his back on you and starts to work with something in a corner.\n\n");
	    break;

	case 70:
	    WRITE("Death suddenly lifts his head and notices you.\n");
	    SPEAK("ARE YOU STILL HERE!?!\n");
	    SPEAK("BEGONE!\n");
	    WRITE("Death flicks a finger and you are suddenly somewhere else...\n");
	    break;

	default:
	    break;
    }
}

/*
 * Function name: do_remove
 * Description:   Removes players that's finished
 */
void
do_remove()
{
    int j, nr;
    
    if (!sizeof(players))
	return;
    
    nr = sizeof(players);
    
    for (j = 0; j < nr; j += 3)
    {
	if (players[j + 1] >= 73)
	{
	    if (players[j])
	    {
		if(query_ip_number(players[j]))
		{
		    remove_death_obj(players[j]);
		    players[j]->reincarnate();
		}
		else
		{
		    players[j]->command("quit");
		}
	    }
	    players = exclude_array(players, j, j + 2);
	    do_remove();
	    return;
	}
    }
}

/*
 * Function name: remove_death_obj
 * Description:   Remove the "death_mark"-object, add badge.
 */
void
remove_death_obj(object player)
{
    
    object plobj, badge;
    
    badge = present("death_badge", player);
    if (!badge)
    {
	badge = clone_object(DEATH_BADGE);
	badge->move(player, 1);
    }
    while (plobj = present("death_mark", player))
	plobj->remove_object();
}

/*
 * Function name: add_player
 * Description:   Adds a player to the list
 */
void
add_player(object plobj)
{
    int *start, mess;

    start = ({ 0, 45, 40 });

    mess = plobj->num_scar();
    if (mess < 3 || !(mess % 5))
	mess = 0;
    else if (mess > 5 && (mess % 3))
	mess = 2;
    else
	mess = 1;
	
    players = players + ({ plobj, start[mess], mess });
}

/*
 * Function name: remove_player
 * Description:   Removes a player from the list
 */
void
remove_player(object plobj)
{
    
    int i;
    
    if (!(i = sizeof(players)))
	return;
    
    if (i <= 2)
    {
	if (players[0] == plobj)
	{
	    players = ({ });
	    set_heart_beat(0);
	    return;
	}
	return;
    }

    i = member_array(plobj, players);
    if (i >= 0)
	players = exclude_array(players, i, i + 2);
}

/*
 * Function name: leave_inv
 * Description:   Remove players if they leave the room prematurly
 */
void
leave_inv(object ob, object to)
{
    remove_player(ob);
    ::leave_inv(ob, to);
}

/* 
 * Function name: filter
 * Description:   Filter out relevant commands.
 */
int
cmdfilter(string str)
{
    switch(query_verb())
    {
    case "quit":
    	write("Death says: YOU CAN NOT ESCAPE DEATH!\n");
	return 0;
    case "look":
    case "take":
    case "get":
    case "help":
    case "bug":
    case "typo":
    case "sysbug":
    case "idea":
    case "praise":
	return 0;
    }    
    write("That is impossible in your immaterial state.\n");
    if (this_player()->query_wiz_level())
    {
	write("Well, since you are a wizard it might be possible anyway.\n");
	return 0;
    }

    return 1;
}

public varargs mixed
long(string str)
{
    mixed s;
    int i;
    
    s = ::long(str);
    if (str)
	return s;
    if (!pointerp(players))
	return s;
    for (i = 0; i < sizeof(players); i += 3)
    {
	if (players[i] == this_player())
	{
	    if (players[i + 1] >= 40 && players[i + 1] < 62 &&
			players[i + 2] == 0)
		return s + "Lars The Implementor.\n";
	}
    }
    return s;
}
