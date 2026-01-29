/*
 * death_room.c
 *
 * The place where Death tortures players when they've died *grin*
 * Khail, Nov. 15/96
 *
 * Based on original design by:
 * Mrpr 901119
 * Tintin 911031
 * Nick 920211
 */
#pragma strict_types

#include <stdproperties.h>
#include "death.h"

inherit "/std/room";

/* Global vars */
object death;
object lars;
mapping deaths;

/* Prototypes */
public void create_death();
public void create_lars();
public void remove_lars();
public void create_room();
public void do_read_soul(object who);
public void enter_inv(object ob, object from);
public int test_for_player(object who);
public void message1(int count, object who);
public void message2(int count, object who);
public void message3(int count, object who);
public void init();
public int all_cmd(string str);
public void reincarnate_me(object who);
public void test_reincarnate(object who);

/*
 * Function name: create_death
 * Description  : Clones death into the room, if he's not already
 *                present.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_death()
{
    if (death)
    {
        if (present(death, this_object()))
            return;
        else
            death->move(this_object());
        return;
    }
    death = clone_object(DEATH);
    death->move(this_object());
}

/*
 * Function name: create_lars
 * Description  : Clones lars into the room, if he's not already
 *                present.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_lars()
{
    if (lars)
        return;
    lars = clone_object(LARS);
    lars->move(this_object());
}

/*
 * Function name: remove_lars
 * Description  : Removes Lars from the room, if he's present.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
remove_lars()
{
    if (!lars)
        return;
    lars->remove_object();
}

/*
 * Function name: create_room
 * Description  : Sets all the vars to make this room a real room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_room()
{
    set_short("death's workroom");
    set_long("A dark room lighted with a dark light that seems " +
        "to defy darkness not so much by actually illuminating " +
        "the room as by being a darkpoint in less dark " +
        "surroundings. In the strange light (dark?) you can see " +
        "a centrally placed desk covered with books and diagrams. " +
        "The walls are covered with bookshelves filled with dark " +
        "tomes bound in leather that gleam with strange runes.\n\n");

    add_item(({"dark light", "light"}),
        "It's very hard to define, and you have problems wrapping your " +
        "mind around the paradox of a dark object emitting darkness " +
        "like a flame emits light.\n");
    add_item(({"desk"}),
        "It's a fairly common looking desk, surprisingly enough, piled " +
        "high with books, diagrams, and assorted junk that's probably " +
        "been collecting dust since dust was first invented.\n");
    add_item(({"diagram", "diagrams"}),
        "They look like... like... oh gross! Never mind what they look " +
        "like.\n");
    add_item(({"books"}),
        "Countless books like piled on Death's desk and his bookshelves, " +
        "and there isn't a single one of them you understand.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    deaths = ([]);

//  create_death();

}

/*
 * Function name: do_read_soul
 * Description  : Delivers a message based upon the player's alignment.
 * Arguments    : object who - Object pointer to the player to test.
 * Returns      : n/a
 */
public void
do_read_soul(object who)
{
    int align;
    string str;

    if (!who)
        return;

    align = who->query_alignment();

    switch (align)
    {
        case -1200..-1000:
            str = "YOUR SINS ARE AS MANY AS THE GRAINS OF SAND IN THE " +
                "DESERT.\nMAYBE YOU'RE WORSE A MONSTER THAN EVEN I! " +
                "HAHAHAHAHAHAHAHAHA!\n\n";
            break;
        case -999..-500:
            str = "OH WHAT A DESPICABLE BUG WE HAVE HERE. STEALING " +
                "CANDY FROM BABIES AND BEATING OLD LADIES NO DOUBT. " +
                "WELL, NOW THEY CAN DANCE ON YOUR GRAVE! " +
                "HAHAHAHAHAHA!\n\n";
            break;
        case -499..-200:
            str = "HAVE YOU EVER BEEN TOLD ABOUT REPENTANCE AND " +
                "ATONEMENT? NO? DIDN'T THINK SO EITHER. YOU WILL BE " +
                "TOLD NOW, HOWEVER, FOR ETERNITY! HAHAHAHAHAHAHA!\n\n";
            break;
        case -199..-1:
            str = "SHAME ON YOU MORTAL! STEALING AND KILLING, IS THAT " +
                "ALL YOU CAN THINK OF? WELL, NOW YOU WILL BE GIVEN " +
                "TIME TO REGRET YOUR DEEDS. FOREVER! HAHAHAHAHAHAHAHA!\n\n";
            break;
        case 0:
            str = "WHAT A FENCE-CLIMBER WE HAVE HERE! NEVER MADE UP " +
                "YOUR MIND IN YOUR ENTIRE LIFE, DID YOU? WELL, DON'T " +
                "WORRY, YOU WON'T HAVE TO NOW! HAHAHAHAHAHAHAHA\n\n";
            break;
        case 1..200:
            str = "OH WHAT A NICE FELLOW WE HAVE HERE. ALWAYS WALKING " +
                "THE NARROW ROAD, WERE YOU? WELL, YOU'LL NEVER KNOW " +
                "WHAT THE OTHER ROAD IS LIKE NOW! HAHAHAHAHA!\n\n";
            break;
        case 201..500:
            str = "NEVER SAID A DIRTY WORD IN YOUR LIFE, DID YOU? " +
                "WELL, IT'S TOO LATE TO CHANGE YOUR MIND ABOUT THAT NOW. " +
                "NO MORE MR. NICE GUY! HAHAHAHAHAHAHA!\n\n";
            break;
        case 501..1000:
            str = "I HEARD THEY WERE OUT OF ARCHANGELS IN HEAVEN, PERHAPS " +
                "YOU SHOULD APPLY FOR THE JOB! I HOPE YOU KNOW HOW TO " +
                "PLAY THE HARP, OR THEY'LL GIVE THE JOB TO SOMEONE " +
                "ELSE! HAHAHAHAHAHAHAHA!\n\n";
            break;
        default:
            str = "TRYING TO TAKE GOD'S JOB AWAY FROM HIM, ARE YOU? " +
                "LET ME TELL YOU A BIT ABOUT IT BEFORE YOU SIGN ANY " +
                "PAPERS, THOUGH. BAD HOURS AND NO VACATION. BELIEVE " +
                "ME, YOU DON'T WANT IT! HAHAHAHAHAHAHAHAHA!\n\n";
    }

    tell_object(who, str);
}

/*
 * Function name: message_jr
 * Description  : Fast track Jr's
 * Arguments    : object who - the (un)lucky Jr.
 */
void
message_jr(object who)
{
    tell_object(who, "Death says: OH, YOU! CONNECTIONS IN HIGH PLACES, EH? "+
        "PAH. THE LIKES OF YOU HAVE NO SOUL ANYWAY. BEGONE.\n\n");
    reincarnate_me(who);
}

/*
 * Function name: start_message
 * Description  : Initiates the appropriate death sequence,
 *                based off of the number of scars the 
 *                player has.
 * Arguments    : object who - Object pointer to the player
 *                             about to enter the sequence.
 * Returns      : n/a
 */
public void
start_message(object who)
{
    int scars;
    scars = who->num_scar();

    create_death(); 
 
   /* But on Jr's don't spend too much time .... */
    if (wildmatch("*jr", who->query_real_name()))
    {
        set_alarm(2.0, 0.0, &message_jr(who));
        return;
    }
 
  /* If the player has less than 3 scars, or if the number */
  /* of scars is a multiple of 5, use message1 series. */
    if (scars < 3 || !(scars % 5))
        set_alarm(itof(random(15)), 0.0, &message1(1, who));

  /* Otherwise, if the number of scars is greater than 5 */
  /* and a multiple of 3, use the message2 series. */
    else if (scars > 5 && !(scars  % 3))
        set_alarm(itof(random(15)), 0.0, &message2(1, who));

  /* For anything else, use the message3 series. */
    else
        set_alarm(itof(random(15)), 0.0, &message3(1, who));
}

/*
 * Function name: enter_inv (MASK)
 * Description  : Starts the death routine running when the player enters
 *                the room.
 * Arguments    : object ob - Object pointer to the object entering the 
 *                            room.
 *                object from - Object pointer to 'ob's previous 
 *                              environment.
 * Returns      : n/a
 */
public void
enter_inv(object ob, object from)
{
  /* Always call back to the function being masked. */
    ::enter_inv(ob, from);

  /* Make sure the entering object is a player */
  /* before starting up the death sequence. */ 
    if (!ob || !living(ob) || ob->query_npc() )
        return;

  /* Make sure the player's a ghost, boot them to default */
  /* start location otherwise. */
    if (!ob->query_ghost())
    {
        tell_object(ob, "Death says: WHAT ARE YOU DOING HERE? YOUR " +
            "TIME HAS NOT YET COME. BEGONE!\n");
        ob->move_living("X", ob->query_default_start_location());
        return;
    }

  /* Ok, 'ob' appears to be a dead player, let's start him on the road 
   * to recovery. */
    start_message(ob);
}

/*
 * Function name: test_for_player
 * Description  : A little security to make sure the player
 *                doesn't go LD or slip out of the room somehow
 *                during the death sequence.
 * Arguments    : object who - The player to test.
 * Returns      : 0 - The player is not longer valid for death.
 *                1 - The player is still listening, keep talking.
 */
public int
test_for_player(object who)
{
  /* Make sure 'who' is still around. */
    if (!who || !objectp(who))
        return 0;

  /* If 'who' is non-interactive, try to make them quit. */
    if (!interactive(who))
    {
      /* Make sure they've got a death mark before quitting them. */
        if (!present(DEATH_MARK_NAME, who))
            clone_object(DEATH_MARK)->move(who, 1);
        who->command("$quit");
        return 0;
    }
  
  /* If the player is no longer in the room and is still a ghost */
  /* bring them back. */
    if (environment(who) != this_object())
    {
        if (who->query_ghost())
        {
            tell_object(who, "You hear Death whisper: YOU DON'T GET " +
                "AWAY FROM ME THAT EASILY!\n\n");
            who->move_living("X", this_object());
            return 1;
        }
        
        return 0;
    }
    return 1;
}

/*
 * Function name: message1
 * Description  : Generates the actual sequence of messages a 
 *                player is pestered with before death will 
 *                reincarnate them.
 * Arguments    : int count - Which message to deliver to the 
 *                            player.
 *                object who - Object pointer to the player to
 *                             send the messages to.
 * Returns      : n/a
 */
public void
message1(int count, object who)
{
    string str;

  /* Make sure player is still around before wasting cpu */
  /* on messages. */
    if (!test_for_player(who))
        return;

  /* Generate a string based on the 'count' var. */
    switch(count)
    {
        case 1:
            str = "Death says: IT IS TIME.\n" +
                "Death lifts his right arm and makes a beckoning motion. " +
                "You feel quite certain that if you had been alive you " +
                "would have died on the spot from fear. Strangely " +
                "enough, you don't feel anything like that at all, " +
                "just a mild curiousity.\n\n";
            break;
        case 2:
            str = "Death says: NO GLANDS, THAT'S WHY.\n" +
                "Death seems to smile a bit. On the other hand, that's " +
                "a bit hard to tell given his physical condition, it " +
                "might very well be his normal expression...\n\n";
            break;
        case 3:
            str = "Death says: WITHOUT GLANDS YOU FEEL NOTHING, " +
                "NOTHING AT ALL.\n" +
                "Well, he seems to be right. Instead of being mad with " +
                "fear you're getting a little bored. You wish for " +
                "something to happen real soon.\n\n";
            break;
        case 4:
            str = "Death says: COME HERE, I MUST READ YOUR SOUL.\n" +
                "Death steps closer, reaches straight into your chest " +
                "with a bony hand, grabbing something within! You " +
                "feel a strange internal yank as your very soul is " +
                "removed for examination... Suddenly Death collects " +
                "your bodyless essence with a great sweeping motion " +
                "of his skeletal hands and puts you in a small glass " +
                "orb that he inserts into his right eye socket! You " +
                "feel a strange blue light from within his eyeless orb " +
                "penetrate you as he leans over the chart.\n\n";
            break;
      /* Special case. No string delivered here, just the do_read_soul */
      /* messages. */ 
        case 5:
            do_read_soul(who);
            break;
        case 6:
            str = "Death says: WELL, I GUESS YOU HAVE DONE YOURS FOR THIS " +
                "TIME, SEE YOU ON ARMAGEDDON DAY! HAHAHAHAHAHAHAHAHAHA!\n" +
                "Death removes the orb from his eye and stands up. " +
                "He steps in front of a door you didn't notice bearing the " +
                "words 'ETERNITY' in black letters. On the door you see " +
                "a small hatch which Death opens with a flick of his " +
                "hand. From the open hatch you can hear the moaning " +
                "murmurs of a million souls. Slowly he lifts you to " +
                "the gaping maw of the hatch.\n\n";
            break;
      /* Here's the man! Lars to the rescue! */
        case 7:
            create_lars();
            str = "Lars arrives through a rift in the fabric of space.\n\n";
            break;
        case 8:
            str = "Lars smiles at you.\n\n";
            break;
        case 9:
            str = "Lars whispers something to Death.\n\n";
            break;
        case 10:
            str = "Death says: WHAT? OUT OF THE QUESTION! YOU KNOW " +
                "THAT!!\n\n";
            break;
        case 11:
            str = "Lars sighs deeply.\n\n";
            break;
        case 12:
            str = "Lars whispers something to Death.\n\n";
            break;
        case 13:
            str = "Death says: REINCARNATION? FOR THIS ONE? HE IS NOT " +
                "WORTHY OF IT AND YOU KNOW IT! BE SENSIBLE, LARS!\n\n";
            break;
        case 14:
            str = "Lars sulks in the corner.\n" +
                "Lars leaves through a rift in the fabric of space.\n" +
                "Death looks at you with something that must be disgust " +
                "even if it's hard to say. His face is not the best " +
                "suited face for showing expressions, but you feel " +
                "fairly confident about this one.\n\n";
            remove_lars();
            break;
        case 15:
            str = "Death says: OH ALL RIGHT THEN! I CAN WAIT. ONE DAY " +
                "YOU WILL BE MINE ANYWAY! HAHAHAHAHAHA!\n" +
                "Suddenly Death hurls you up in the air, you feel a " +
                "strange sensation as you pass through the very walls " +
                "of the building, out into the open air, through some " +
                "other walls and a couple of fairly surprised horses " +
                "before you finally stop inside another building. It " +
                "seems vaguely familiar, somehow.\n\n";
            break;
    }

  /* If a string was set in the switch case, deliver it. */
    if (str && stringp(str) && strlen(str))
        tell_object(who, str);

  /* If the message delivered was the final one, reincarnate */
  /* the player and be done with him. */
    if (count == 15)
        reincarnate_me(who);
  /* Player isn't finished yet, increment the counter and call */
  /* this function again in random(15) seconds. */
    else
        set_alarm(itof(random(15)), 0.0, &message1(++count, who));
}

/*
 * Function name: message2
 * Description  : Generates the actual sequence of messages a 
 *                player is pestered with before death will 
 *                reincarnate them. For the most part, 
 *                virtually identical to message1().
 * Arguments    : int count - Which message to deliver to the 
 *                            player.
 *                object who - Object pointer to the player to
 *                             send the messages to.
 * Returns      : n/a
 */
public void
message2(int count, object who)
{
    string str;

  /* Make sure the player's still here. */
    if (!test_for_player(who))
        return;

    switch(count)
    {
        case 1:
            str = "Death says: IT IS TIME!\n" +
                "Death lifts his right arm and makes a beckoning " +
                "motion.\n\n";
            break;
        case 2:
            str = "Death penetrates you with his big empty orbs. You " +
                "think you notice surprise deep down in there.\n\n";
            break;
        case 3:
            str = "Death says: YOU AGAIN!!!\n" +
                "Death grumbles and complains.\n\n";
            break;
        case 4:
            str = "Death says: I KNEW YOU WEREN'T WORTH A REINCARNATION, " +
                "NOW YOU'VE RUINED ANOTHER PERFECTLY GOOD BODY! I TOLD " +
                "LARS THAT, BUT WOULD HE LISTEN? OH, NOOOOOO.\n\n";
            break;
        case 5:
            str = "Death sighs deeply.\n" +
                "Death says: WELL, I PROMISED LARS, I GUESS HE'LL HAVE " +
                "HIS WAY... _AGAIN_.\n" +
                "Death sulks in a corner.\n\n";
            break;
        case 6:
            str = "Death chuckles to himself.\n\n";
            break;
        case 7:
            str = "Death says: IT'S EASY TO SEE YOU WILL SOON VISIT ME " +
                "AGAIN ANYWAY!\n" +
                "Death moves with surprising speed, and suddenly you " +
                "realize you are somewhere else that is uncomfortably " +
                "familiar...\n\n";
            break;
    }

  /* Deliver the message */
    tell_object(who, str);
  
  /* If final message, reincarnate. */
    if (count == 7)
        reincarnate_me(who);
  /* Otherwise increment counter and call this fun again. */
    else
        set_alarm(itof(random(15)), 0.0, &message2(++count, who));
}

/*
 * Function name: message3
 * Description  : Generates the actual sequence of messages a 
 *                player is pestered with before death will 
 *                reincarnate them. Almost identical to the
 *                message1() function.
 * Arguments    : int count - Which message to deliver to the 
 *                            player.
 *                object who - Object pointer to the player to
 *                             send the messages to.
 * Returns      : n/a
 */
public void
message3(int count, object who)
{
    string str;

  /* Make sure player's still here. */
    if (!test_for_player(who))
        return;

    switch(count)
    {
        case 1:
            str = "Death says: IT IS TIME, COME HERE.\n\n";
            break;
        case 2:
            str = "Death turns his eyeless orbs towards you.\n\n";
            break;
        case 3:
            str = "Death says: I DON'T BELIEVE IT, NOT YOU AGAIN? " +
                 "YOU'VE BECOME A GENUINE REGULAR HERE, HAVEN'T YOU?\n\n";
            break;
        case 4:
            str = "Death says: COME HERE, I FEEL LIKE READING YOUR " +
                "SOUL.\n" +
                "Death reaches out towards you, but you don't dare " +
                "to look\n\n";
            break;
      /* Read the player's soul again, just for the hell of it. */
        case 5:
            do_read_soul(who);
            str = "Death chuckles deeply.\n\n";
            break;
        case 6:
            str = "Death turns his back on you and starts to work with " +
                "something in a corner.\n\n";
            break;
        case 7:
            str = "Death suddenly lifts his head and notices you.\n" +
                "Death says: ARE YOU STILL HERE?!?!?\n" +
                "Death says: BEGONE!\n" +
                "Death flicks a finger at you, and suddenly you are " +
                "in another place, a place which you are embarrasingly " +
                "familiar with...\n\n";
    }

  /* Deliver the message. */
    tell_object(who, str);

  /* If final count, reincarnate. */
    if (count == 7)
        reincarnate_me(who);
  /* Otherwise increment counter and call this fun again. */
    else
        set_alarm(itof(random(15)), 0.0, &message3(++count, who));
}

/*
 * Function name: init (MASK)
 * Description  : Exploit init() function to include an add_action
 *                in the player that will lock out all but a few
 *                basic commands.
 * Arguments    : n/a
 * Description  : n/a
 */
public void
init()
{
  /* Always call back to masked functions. */
    ::init();
  /* Anything the player types goes through the */
  /* all_cmd trap for evaluation. */
    add_action(all_cmd, "", 1);
}

/*
 * Function name: all_cmd
 * Description  : Evaluates a command a player attempted 
 *                to use. If it's one of a very small list
 *                of basic commands, allow it. Otherwise,
 *                block it.
 * Arguments    : string str - Arguments to the command the
 *                player attempted.
 * Returns      : 0 - failure, keep threading.
 *                1 - success, halt execution.
 *                Note that in the case of a command trap, a
 *                'failure' means that it allows the command
 *                to continue threading. A 'success' means that
 *                it's one that we won't allow, and block it.
 */
public int
all_cmd(string str)
{
  /* Use query_verb() to figure out what command the player */
  /* is trying to use. All those in the switch are permitted. */
    switch(query_verb())
    {
        case "quit":
            write("Death says: YOU CAN NOT ESCAPE DEATH!\n");
            return 0;
        case "look":
        case "l":
        case "help":
        case "bug":
        case "typo":
        case "idea":
        case "praise":
        case "sysbug":
            return 0;
    }

  /* Anything not in the switch we're going to block. */
    write("That is impossible in your immaterial state.\n");

  /* Except for wizards, who aren't susceptible to this */
  /* particular block. They can use any command. */  
    if (this_player()->query_wiz_level())
    {
        write("But since you're a wizard, you decide to go ahead " +
            "and do it anyway.\n");
        return 0;
    }

  /* For anyone not a wizard, thread halts here. */
    return 1;
}

/*
 * Function name: reincarnate_me
 * Description  : Starts the actual reincarnation process for
 *                the player.
 * Arguments    : object who - Object pointer to the player to
 *                             send to the bodies room.
 * Returns      : n/a
 */
public void
reincarnate_me(object who)
{
  /* Make sure the player being reincarnated is up for */
  /* reincarnation. I.e. interactive and a ghost. If they */
  /* aren't, don't do this. */
    if (!who || !interactive(who) || !who->query_ghost())
        return;

  /* We can reincarnate them, so start the process. */
    else
    {
      /* Remove the player's death mark. */
        present("death_mark", who)->remove_object();
      /* Add the player's name & number of deaths this */
      /* login to the 'deaths' mapping. */
        if (deaths[who->query_real_name()])
            deaths[who->query_real_name()] += 1;
        else
            deaths[who->query_real_name()] = 1;
      /* A little backup system. If 'who' still exists */
      /* after reincarnate() is called, something's wrong, */
      /* so call test_reincarnate for confirmation in 1 sec. */
        set_alarm(1.0, 0.0, &test_reincarnate(who));
      /* Ok, let's try to reincarnate. This should destroy the */
      /* player's normal body, give him a ghost body, */
      /* /d/Genesis/login/ghost_player.c, and move him to the  */
      /* bodies room, and we're done with him.*/ 
        who->reincarnate();
    }
}

/*
 * Function name: test_reincarnate
 * Description  : Simply ensures that 'who' is no longer a
 *                valid object pointer. It should have been
 *                destroyed by the reincarnate() function. If
 *                it still exists, try again with a new 
 *                death mark.
 * Arguments    : object who - Object pointer to test for
 *                             existance.
 * Returns      : n/a
 */
public void
test_reincarnate(object who)
{
    if (who)
        clone_object(DEATH_MARK)->move(who, 1);
}

/*
 * Function name: query_deaths
 * Description  : A function that just returns the number
 *                of times a player has died this login. Used
 *                by the death_mark to decide if the player 
 *                goes through the full sequence, of if they
 *                get to go straight to the bodies chamber.
 * Arguments    : string who - real name of the player to test.
 * Returns      : number of times the player has died.
 */
public int
query_deaths(string who)
{
    if (mappingp(deaths) && strlen(who))
        return deaths[who];
}

/*
 * Funtion name: set_deaths
 * Description : Can be used to set the number of deaths a player
 *               has had (or supposedly had) during this boot.
 *               Possible uses can be to force a player through
 *               the quick version by setting his number of deaths
 *               to > 0, or by forcing through the long version
 *               by setting = 0. Note the only effect this will have
 *               on the death sequence is which version they go 
 *               through (verbose or brief).
 * Arguments   : string who - The name of the player.
 *               int num - The number of time to set they've died.
 * Returns     : n/a
 */
public void
set_deaths(string who, int num)
{
    if (!who || !strlen(who))
        return;

    who = lower_case(who);
    deaths[who] = num;
}
