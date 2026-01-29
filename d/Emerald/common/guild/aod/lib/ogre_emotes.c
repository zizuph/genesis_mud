/*
 *  /d/Emerald/common/guild/aod/lib/ogre_emotes.c
 *
 *  This module defines the emotes for the Ogre race. Typically, these
 *  are not any special emotes that have unique commands. Rather, they
 *  are just converting the effect of a normal emote command to what
 *  happens when an Ogre might perform such an act. This code is
 *  inherited by:
 *
 *      /d/Emerald/common/guild/aod/obj/belt.c
 *
 *  It must be put into an object such as the belt because including
 *  it in the soul fails to mask the emotes that the mudlib provides.
 *
 *  Additionally, functions which control the way ogres communicate
 *  are defined beneath the emote functions.
 *
 *  Created March 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/lib/commands";

#include "../defs.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>

/* Definitions */
#define SOULDESC(x)        (this_player()->add_prop(LIVE_S_SOULEXTRA, (x)))

/* Prototypes */
public void        add_ogre_emotes();
int                bat(string str);
int                beam(string str);
int                bite(string str);
int                blow(string str);
int                boggle(string str);
int                bounce(string str);
int                bow(string str);
int                burp(string str);
int                cackle(string str);
int                caress(string str);
int                cheer(string str);
int                chuckle(string str);
int                clap(string str);
int                clear(string str);
int                cough(string str);
int                cry(string str);
int                cuddle(string str);
int                curl(string str);
int                curtsey(string str);
int                dance(string str);
int                eyebrow(string str);
int                fart(string str);
int                flex(string str);
int                flip(string str);
int                fondle(string str);
int                french(string str);
int                frown(string str);
int                giggle(string str);
int                glare(string str);
int                grin(string str);
int                grope(string str);
int                growl(string str);
int                hiccup(string str);
int                hmm(string str);
int                hold(string str);
int                hug(string str);
int                hum(string str);
int                jump(string str);
int                kick(string str);
int                kiss(string str);
int                knee(string str);
int                kneel(string str);
int                laugh(string str);
int                lick(string str);
int                love(string str);
int                melt(string str);
int                nibble(string str);
int                nod(string str);
int                nudge(string str);
int                nuzzle(string str);
int                pat(string str);
int                peer(string str);
int                pet(string str);
int                poke(string str);
int                pounce(string str);
int                puke(string str);
int                purr(string str);
int                roar(string str);
int                ruffle(string str);
int                scowl(string str);
int                scratch(string str);
int                scream(string str);
int                shake(string str);
int                shrug(string str);
int                sigh(string str);
int                sing(string str);
int                slap(string str);
int                smile(string str);
int                smirk(string str);
int                snap(string str);
int                snarl(string str);
int                sneer(string str);
int                sneeze(string str);
int                snore(string str);
int                snuggle(string str);
int                sob(string str);
int                spank(string str);
int                spit(string str);
int                squeeze(string str);
int                stare(string str);
int                startle(string str);
int                stomp(string str);
int                stumble(string str);
int                strut(string str);
int                swoon(string str);
int                tackle(string str);
int                tap(string str);
int                touch(string str);
int                wave(string str);
int                weep(string str);
int                wiggle(string str);
int                wink(string str);
int                yodel(string str);


/*
 * Function name:        add_ogre_emotes
 * Description  :        This function is called in the inheriting
 *                       object's init() function.
 */
public void
add_ogre_emotes()
{
    add_action(bat, "bat");
    add_action(beam, "beam");
    add_action(bite, "bite");
    add_action(blow, "blow");
    add_action(boggle, "boggle");
    add_action(bounce, "bounce");
    add_action(bow, "bow");
    add_action(burp, "burp");
    add_action(cackle, "cackle");
    add_action(caress, "caress");
    add_action(cheer, "cheer");
    add_action(chuckle, "chuckle");
    add_action(clap, "clap");
    add_action(clap, "applaud");
    add_action(clear, "clear");
    add_action(cough, "cough");
    add_action(cry, "cry");
    add_action(cuddle, "cuddle");
    add_action(curl, "curl");
    add_action(curtsey, "curtsey");
    add_action(dance, "dance");
    add_action(eyebrow, "eyebrow");
    add_action(fart, "fart");
    add_action(flex, "flex");
    add_action(flip, "flip");
    add_action(fondle, "fondle");
    add_action(french, "french");
    add_action(frown, "frown");
    add_action(giggle, "giggle");
    add_action(glare, "glare");
    add_action(grin, "grin");
    add_action(grope, "grope");
    add_action(growl, "growl");
    add_action(hiccup, "hiccup");
    add_action(hmm, "hmm");
    add_action(hold, "hold");
    add_action(hug, "hug");
    add_action(hum, "hum");
    add_action(jump, "jump");
    add_action(kick, "kick");
    add_action(kiss, "kiss");
    add_action(knee, "knee");
    add_action(kneel, "kneel");
    add_action(laugh, "laugh");
    add_action(lick, "lick");
    add_action(love, "love");
    add_action(melt, "melt");
    add_action(nibble, "nibble");
    add_action(nod, "nod");
    add_action(nudge, "nudge");
    add_action(nuzzle, "nuzzle");
    add_action(pat, "pat");
    add_action(peer, "peer");
    add_action(pet, "pet");
    add_action(poke, "poke");
    add_action(pounce, "pounce");
    add_action(puke, "puke");
    add_action(purr, "purr");
    add_action(roar, "roar");
    add_action(ruffle, "ruffle");
    add_action(scowl, "scowl");
    add_action(scratch, "scratch");
    add_action(scream, "scream");
    add_action(shake, "shake");
    add_action(shrug, "shrug");
    add_action(sigh, "sigh");
    add_action(sing, "sing");
    add_action(slap, "slap");
    add_action(smile, "smile");
    add_action(smirk, "smirk");
    add_action(snap, "snap");
    add_action(snarl, "snarl");
    add_action(sneer, "sneer");
    add_action(sneeze, "sneeze");
    add_action(snore, "snore");
    add_action(snuggle, "snuggle");
    add_action(sob, "sob");
    add_action(spank, "spank");
    add_action(spit, "spit");
    add_action(squeeze, "squeeze");
    add_action(stare, "stare");
    add_action(startle, "startle");
    add_action(stomp, "stomp");
    add_action(strut, "strut");
    add_action(stumble, "stumble");
    add_action(swoon, "swoon");
    add_action(tackle, "tackle");
    add_action(tap, "tap");
    add_action(touch, "touch");
    add_action(wave, "wave");
    add_action(weep, "weep");
    add_action(wiggle, "wiggle");
    add_action(wink, "wink");
    add_action(yodel, "yodel");
} /* add_ogre_emotes */


/*
 * =================== Actual Emotes Below This Line ===================
 */

int
bat(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "oafishly", 0);

    if (!stringp(how[0]))
    {
        write("You bat your eyelashes" + how[1] + ".\n");
        allbb(" bats " + this_player()->query_possessive() +
            " eyelashes" + how[1] + ".", how[1], ACTION_VISUAL);
        return 1;
    }

    oblist = parse_this(how[0], "[eyelashes] [at] [the] %l", ACTION_VISUAL);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Bat your eyelashes [how] at whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only bat your eyelashes at one target"
          + " at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You bat your eyelashes" + how[1] + " at", oblist);
        all2actbb(" bats " + this_player()->query_possessive() +
            " eyelashes" + how[1] + " at", oblist, 0, how[1], 
            ACTION_VISUAL);
        targetbb(" bats " + this_player()->query_possessive() +
            " eyelashes" + how[1] + " at you.", oblist, how[1], 
            ACTION_VISUAL);
        return 1;
    }

    actor("You look down at", oblist, " and bat your eyelashes"
      + how[1] + ".");
    all2actbb(" looks down at", oblist, " and bats " 
        + this_player()->query_possessive() +
        " eyelashes" + how[1] + ".", how[1], ACTION_VISUAL);
    targetbb(" looks down at you and bats "
      + this_player()->query_possessive() + " eyelashes"
      + how[1] + ".", oblist, how[1], ACTION_VISUAL);
    return 1;
} /* bat */


int
beam(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "stupidly", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("beaming" + how[1]);
        write("You beam" + how[1] + ".\n");
        allbb(" beams" + how[1] + ".", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Beam [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only beam at one target"
          + " at a time!\n");
        return 1;
    }

    SOULDESC("beaming" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You beam" + how[1] + " at", oblist);
        all2actbb(" beams" + how[1] + " at", oblist, 0, how[1]);
        targetbb(" beams" + how[1] + " at you.", oblist, how[1]);
        return 1;
    }

    actor("You look down at", oblist, " and beam" + how[1] + ".");
    all2actbb(" looks down at", oblist, " and beams" + how[1] + ".",
        how[1]);
    targetbb(" looks down at you and beams" + how[1] + ".", oblist,
        how[1]);
    return 1;
} /* beam */


int
bite(string str)
{
    if (stringp(str))
    {
        notify_fail("Bite what?\n");
        return 0;
    }

    write("You bite on your humongous bottom lip with a chipped"
      + " tooth.\n");
    allbb(" bites on " + this_player()->query_possessive()
      + " humongous bottom lip with a chipped tooth.", "",
        ACTION_OTHER);
    return 1;
} /* bite */


int
blow(string str)
{
    object *oblist;
    string *how;

    if (!strlen(str))
    {
        notify_fail("Blow [how] in whose ear or " +
            "blow a kiss [how] to whom?\n");
        return 0;
    }

    if (wildmatch("kiss *", str))
    {
        how = parse_adverb_with_space(extract(str, 5), BLANK_ADVERB, 0);

        if (!stringp(how[0]))
        {
            notify_fail("Blow [how] in whose ear or " +
                "blow a kiss [how] to whom?\n");
            return 0;
        }

        oblist = parse_this(how[0], "[to] / [at] [the] %i",
            ACTION_VISUAL | ACTION_INTIMATE | ACTION_LACTIVITY);

        if (!sizeof(oblist))
        {
            if (strlen(parse_msg))
            {
                write(parse_msg);
                return 1;
            }

            notify_fail("Blow [how] in whose ear or " +
                "blow a kiss [how] to whom?\n");
            return 0;
        }

        if (sizeof(oblist) > 1)
        {
            write("You can only blow a kiss to one target"
              + " at a time!\n");
            return 1;
        }

        str = (living(oblist[0]) ? "to" : "at");

        if (IS_OGRE(oblist[0]) || !living(oblist[0]))
        {
                actor("You" + how[1] + " blow a kiss " + str, oblist);
                all2actbb(how[1] + " blows a kiss " + str, oblist, "",
                    how[1],
                    ACTION_VISUAL | ACTION_INTIMATE | ACTION_LACTIVITY);
                targetbb(how[1] + " blows a kiss " + str + " you.",
                    oblist, how[1],
                    ACTION_VISUAL | ACTION_INTIMATE | ACTION_LACTIVITY);
                return 1;
        }

        actor("You" + how[1] + " blow a kiss down " + str, oblist);
        all2actbb(how[1] + " blows a kiss down " + str, oblist, "",
            how[1], ACTION_VISUAL | ACTION_INTIMATE | ACTION_LACTIVITY);
        targetbb(how[1] + " blows a kiss down " + str + " you.", oblist,
            how[1], ACTION_VISUAL | ACTION_INTIMATE | ACTION_LACTIVITY);
        return 1;
    }

    how = parse_adverb_with_space(str, "gently", 0);

    if (!stringp(how[0]))
    {
        notify_fail("Blow [how] in whose ear or " +
            "blow a kiss [how] to whom?\n");
        return 0;
    }

    oblist = parse_this(how[0], "[the] %l",
        ACTION_CONTACT | ACTION_INTIMATE | ACTION_LACTIVITY);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Blow [how] in whose ear or blow a kiss [how] to whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only blow in one target's ear"
          + " at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You blow" + how[1] + " in", oblist, "'s ear.");
        all2act(" blows" + how[1] + " in", oblist, "'s ear.", how[1],
            ACTION_CONTACT | ACTION_INTIMATE | ACTION_LACTIVITY);
        target(" blows" + how[1] + " in your ear.", oblist, how[1],
            ACTION_CONTACT | ACTION_INTIMATE | ACTION_LACTIVITY);
        return 1;
    }

    actor("You lean down and blow" + how[1] + " in", oblist,
        "'s ear, nearly knocking " + oblist[0]->query_objective()
      + " over with the blast.");
    all2act(" leans down and blows" + how[1] + " in", oblist, "'s ear,"
      + " nearly knocking " + oblist[0]->query_objective() + " over"
      + " with the blast.", how[1],
        ACTION_CONTACT | ACTION_INTIMATE | ACTION_LACTIVITY);
    target(" leans down and blows" + how[1] + " in your ear, nearly"
      + " knocking you over with the blast.", oblist, how[1],
        ACTION_CONTACT | ACTION_INTIMATE | ACTION_LACTIVITY);
    return 1;
} /* blow */


int
boggle(string str)
{
    if (stringp(str))
    {
        notify_fail("Boggle how?\n");
        return 0;
    }

    write("Your mind boggles at that very concept. This is a very"
      + " familiar feeling, of course, you being an ogre.\n");
    all(" boggles at the very concept. This isn't especially profound,"
      + " however, since most concepts boggle an ogre.", "", 
        ACTION_OTHER);
    return 1;
} /* boggle */


int
bounce(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "uncontrollably", 0);

    if (!stringp(how[0]))
    {
        write("B O I N G !!   S M A S H !!!!    C R A S H !!!!!\n"
          + "You bounce around" + how[1] + ", practically devastating"
          + " the area!\n");
        all(" bounces around" + how[1] + ", practically devastating"
          + " the area!", how[1],
            ACTION_HACTIVITY | ACTION_VISUAL);
        return 1;
    }

    oblist = parse_this(how[0], "[in] [to] [into] [the] %i",
        ACTION_CONTACT | ACTION_HACTIVITY | ACTION_VISUAL);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Bounce [how] into whom/what?\n");
        return 0;
    }

    actor("B O I N G !!   S M A S H !!!!    C R A S H !!!!!!\n"
      + "You bounce around" + how[1] + ", doing all sorts of terrible"
      + " damage to the area until you eventually bump into", oblist);
    all2act(" bounces around" + how[1] + ", doing all sorts of terrible"
      + " damage to the area until " + this_player()->query_pronoun()
      + " bumps into", oblist, 0, how[1],
        ACTION_CONTACT | ACTION_HACTIVITY | ACTION_VISUAL);
    target(" bounces around" + how[1] + ", doing all sorts of terrible"
      + " damage to the area until "
      + this_player()->query_pronoun() + " bumps into you. Fortunately"
      + " you are not harmed!", oblist,
        how[1], ACTION_CONTACT | ACTION_HACTIVITY | ACTION_VISUAL);
    return 1;
} /* bounce */


int
bow(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "awkwardly", 0);

    if (!stringp(how[0]))
    {
        write("You bow" + how[1] + ".\n");
        allbb(" bows" + how[1] + ".", how[1],
            ACTION_VISUAL | ACTION_MACTIVITY);
        return 1;
    }

    oblist = parse_this(how[0], "[to] / [before] [the] %i",
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Bow [how] to whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only bow to one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You bow" + how[1] + " to", oblist);
        all2actbb(" bows" + how[1] + " to", oblist, 0, how[1],
            ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
        targetbb(" bows" + how[1] + " before you.", oblist, how[1],
            ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
        return 1;
    }

    actor("You bow" + how[1] + " to", oblist, ", your head dipping"
      + " to loom just a few feet above " + oblist[0]->query_possessive()
      + ".");
    all2actbb(" bows" + how[1] + " to", oblist, ", "
      + this_player()->query_possessive() + " head dipping to loom just"
      + " a few feet above the latter's.", how[1],
            ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
    targetbb(" bows" + how[1] + " to you, "
      + this_player()->query_possessive() + " head dipping to loom"
      + " just a few feet above your own.", oblist, how[1],
            ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
    return 1;
} /* bow */


int
burp(string str)
{
    str = check_adverb_with_space(str, "deafeningly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Burp how?\n");
        return 0;
    }

    write("You pause a moment and then burp" + str + ", rattling"
      + " everything around you.\n");
    all(" pauses a moment and then burps" + str + ", rattling"
      + " everything in the area.", str, ACTION_AURAL);
    return 1;
} /* burp */


int
cackle(string str)
{
    str = check_adverb_with_space(str, "with glee");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Cackle how?\n");
        return 0;
    }

    SOULDESC("cackling" + str);
    write("You cackle" + str + ", the harsh sound echoing throughout"
      + " the area.\n");
    all(" throws " + this_player()->query_possessive() +
        " huge head back and cackles" + str + "! The sound is"
      + " something like the braying of a hundred demonic mules!", str,
	ACTION_AURAL | ACTION_LACTIVITY);
    return 1;
} /* cackle */


int
caress(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "lovingly", 1);

    oblist = parse_this(how[0], "[the] %i",
        ACTION_CONTACT | ACTION_INTIMATE | ACTION_VISUAL | ACTION_LACTIVITY, 1);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Caress whom/what [how]?\n");
        return 0;
    }

    if (oblist[0] == this_player())
    {
        write("You caress yourself" + how[1] + ".\n");
        all(" caresses " + this_player()->query_objective() +
            "self" + how[1] + ".", how[1], ACTION_VISUAL | ACTION_LACTIVITY);
        return 1;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only caress one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You caress", oblist, how[1] + ".");
        all2act(" caresses", oblist, how[1] + ".", how[1],
            ACTION_CONTACT | ACTION_INTIMATE |
            ACTION_VISUAL | ACTION_LACTIVITY);
        target(" caresses you" + how[1] + ".", oblist, how[1], 
            ACTION_CONTACT | ACTION_INTIMATE |
            ACTION_VISUAL | ACTION_LACTIVITY);
        return 1;
    }

    actor("You reach down and caress", oblist, how[1] + " with your"
      + " huge hands.");
    all2act(" reaches down and caresses", oblist, how[1] + " with "
      + this_player()->query_possessive() + " huge hands.", how[1],
        ACTION_CONTACT | ACTION_INTIMATE |
        ACTION_VISUAL | ACTION_LACTIVITY);
    target(" reaches down and caresses you" + how[1] + " with "
      + this_player()->query_possessive() + " huge hands.", oblist,
        how[1], ACTION_CONTACT | ACTION_INTIMATE |
        ACTION_VISUAL | ACTION_LACTIVITY);
    return 1;
} /* caress */


int
cheer(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "enthusiastically", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("cheering" + how[1]);
        write("You cheer" + how[1] + ", raising your mighty fists"
          + " into the air.\n");
        all(" cheers" + how[1] + ", raising "
          + this_player()->query_possessive() + " mighty fists"
          + " into the air.", how[1],
            ACTION_AURAL | ACTION_MACTIVITY | ACTION_VISUAL);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i",
        ACTION_MACTIVITY | ACTION_AURAL | ACTION_VISUAL);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Cheer [how] at whom/what?\n");
        return 0;
    }

    SOULDESC("cheering" + how[1]);
    actor("You cheer" + how[1] + " at", oblist, " stomping your"
      + " mighty feet and shaking the ground.");
    all2act(" cheers" + how[1] + " at", oblist, ", stomping "
      + this_player()->query_possessive() + " mighty feet and"
      + " shaking the ground.", how[1],
	    ACTION_MACTIVITY | ACTION_AURAL | ACTION_VISUAL);
    target(" cheers" + how[1] + " at you, stomping "
      + this_player()->query_possessive() + " mighty feet and"
      + " shaking the ground.", oblist, how[1],
	    ACTION_MACTIVITY | ACTION_AURAL | ACTION_VISUAL);
    return 1;
} /* cheer */


int
chuckle(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "stupidly", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("chuckling" + how[1]);
        write("You chuckle" + how[1] + ".\n");
        all(" chuckles" + how[1] + ".", how[1], ACTION_AURAL);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i", ACTION_AURAL);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Chuckle [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only bow to one target at a time!\n");
        return 1;
    }

    SOULDESC("chuckling" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You chuckle" + how[1] + " at", oblist);
        all2act(" chuckles" + how[1] + " at", oblist, 0, how[1], ACTION_AURAL);
        target(" chuckles" + how[1] + " at you.", oblist, how[1], ACTION_AURAL);
        return 1;
    }

    actor("You look down at", oblist, " and chuckle" + how[1] + ".");
    all2act(" looks down at", oblist, " and chuckles" + how[1] + ".",
        how[1], ACTION_AURAL);
    target(" looks down at you and chuckles" + how[1] + ".", oblist,
        how[1], ACTION_AURAL);
    return 1;
} /* chuckle */


int
clap(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "excitedly", 0);

    if (!stringp(how[0]))
    {
        write("You jump up and down, clapping" + how[1] + " and"
          + " shaking the ground with each hop.\n");
        all(" jumps up and down, clapping" + how[1] + " and shaking"
          + " the ground with each hop.", how[1],
            ACTION_AURAL | ACTION_LACTIVITY);
        return 1;
    }

    oblist = parse_this(how[0], "[for] / [to] [the] %i",
        ACTION_AURAL | ACTION_LACTIVITY | ACTION_INGRATIATORY);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Clap [how] for whom/what?\n");
        return 0;
    }

    actor("You jump up and down, clapping" + how[1] + " at", oblist,
        " and shaking the ground with each hop.");
    all2act(" jumps up and down, clapping" + how[1] + " at", oblist,
        " and shaking the ground with each hop.", how[1],
        ACTION_AURAL | ACTION_LACTIVITY | ACTION_INGRATIATORY);
    target(" jumps up and down, clapping" + how[1] + " at you and"
      + " shaking the ground with each hop.", oblist, how[1],
        ACTION_AURAL | ACTION_LACTIVITY | ACTION_INGRATIATORY);
    return 1;
} /* clap */


int
clear(string str)
{
    if (str != "throat")
    {
        notify_fail("Clear what? Your throat?\n");
        return 0;
    }

    write("You clear your throat to attract attention! The sound is"
      + " beyond description.\n");
    all(" clears " + this_player()->query_possessive() +
        " throat to attract attention. It sounds like a cross between"
      + " a groaning walrus and an avalanche.", "", ACTION_AURAL);
    return 1;
} /* clear */


int
cough(string str)
{
    str = check_adverb_with_space(str, "violently");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Cough how?\n");
        return 0;
    }

    SOULDESC("coughing" + str);
    write("Forgetting to cover your mouth, you cough" + str + "," 
      + " sending debris flying in all directions!\n");
    all(" coughs" + str + ", sending debris flying in all"
      + " directions!", str);
    return 1;
} /* cough */


int
cry(string str)
{
    object *oblist;
    string *how;

    if (!stringp(str))
    {
        SOULDESC("crying");
        write("You burst into huge, sloppy, Ogreish tears: Waaaaah!\n");
        all(" bursts into huge, sloppy, Ogreish tears which rain"
          + " down on the area.");
        return 1;
    }

    how = parse_adverb_with_space(str, "forlornly", 0);

    if (!stringp(how[0]))
    {
	SOULDESC("crying" + how[1]);
	write("You cry" + how[1] + ", sending huge Ogre tears raining"
          + " down all over the place.\n");
	all(" cries" + how[1] + ", sending huge Ogre tears raining"
          + " down on the area.", how[1]);
	return 1;
    }

    oblist = parse_this(how[0], "[on] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Cry [on] whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only cry on one target at a time!\n");
        return 1;
    }

    SOULDESC("crying");
    str = this_player()->query_possessive();

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You rest your head on", oblist,
            "'s shoulder and cry your heart out.");
        all2act(" rests " + str + " head on", oblist,
            "'s shoulder and cries " + str + " heart out.");
        target(" rests " + str + " head on your shoulder and cries " +
            str + " heart out.", oblist);
        return 1;
    }

    actor("You bend WAAAAY down to rest your head on", oblist,
        "'s shoulder and drench " + oblist[0]->query_objective() + " with"
      + " your tears.");
    all2act(" bends way down to rest " + str + " head on", oblist,
        "'s shoulder and drenches " + oblist[0]->query_objective() + " with "
      + str + " tears.");
    target(" bends way down to rest " + str + " head on your shoulder"
      + " and proceeds to drench you completely with " + str
      + " tears.", oblist);
    return 1;
} /* cry */


int
cuddle(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "lovingly", 1);

    oblist = parse_this(how[0], "[the] %i", ACTION_CONTACT | ACTION_INTIMATE);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Cuddle whom/what [how]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only cuddle one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You cuddle", oblist, how[1] + ".");
        all2act(" cuddles", oblist, how[1] + ".", how[1],
            ACTION_CONTACT | ACTION_INTIMATE);
        target(" cuddles you" + how[1] + ".", oblist, how[1],
    	    ACTION_CONTACT | ACTION_INTIMATE);
        return 1;
    }

    actor("You squat beside", oblist, " and cuddle "
      + oblist[0]->query_objective() + how[1] + ".");
    all2act(" squats beside", oblist, " and cuddles "
      + oblist[0]->query_objective() + how[1] + ".", how[1],
        ACTION_CONTACT | ACTION_INTIMATE);
    target(" squats beside you and cuddles you" + how[1] + ".",
        oblist, how[1], ACTION_CONTACT | ACTION_INTIMATE);
    return 1;
} /* cuddle */


int
curl(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "happily", 1);

    oblist = parse_this(how[0], "[in] / [on] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Curl in whose lap [how]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only cuddle one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You curl up in", oblist, "'s lap and purr" + how[1] 
          + ".");
        all2act(" curls up in", oblist, "'s lap and purrs" + how[1]
          + ".", how[1]);
        target(" curls up in your lap and purrs" + how[1] + ".",
            oblist, how[1]);
        return 1;
    }

    actor("You lower your huge body to curl up at", oblist, "'s"
      + " feet and purr" + how[1] + ".");
    all2act(" lowers " + this_player()->query_possessive() + " huge"
      + " body to curl up at", oblist, "'s feet and purrs" + how[1]
      + ".", how[1]);
    target(" lowers " + this_player()->query_possessive() + " huge"
      + " body to curl up at your feet and purrs" + how[1] + ".",
        oblist, how[1]);
    return 1;
} /* curl */


int
curtsey(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "clumsily", 0);

    if (!stringp(how[0]))
    {
        write("You curtsey" + how[1] + ". How un-ogrely!\n");
        all(" curtseys" + how[1] + ". Who would've guessed an ogre"
          + " could curtsey?", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[to] / [before] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Curtsey [how] to whom/what?\n");
        return 0;
    }

    actor("You curtsey" + how[1] + " to", oblist, ". This is most"
      + " irregular for an ogre, you know!");
    all2actbb(" curtseys" + how[1] + " to", oblist, ", displaying"
      + " highly irregular manners for an ogre.", how[1]);
    targetbb(" curtseys" + how[1] + " to you. Highly irregular for"
      + " an ogre, don't you think?", oblist, how[1]);
    return 1;
} /* curtsey */


int
dance(string str)
{
    object *oblist;

    if (!stringp(str))
    {
        write("You begin crashing around in an lively Ogre dance.\n");
        all(" begins crashing around in a lively Ogre dance.");
        return 1;
    }

    oblist = parse_this(str, "[with] [the] %i", ACTION_CONTACT);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Dance with whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only dance with one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You sweep", oblist, " across the dance floor.");
        all2act(" sweeps", oblist, " across the dance floor.",
            "", ACTION_CONTACT);
        target(" sweeps you across the dance floor.", oblist, "",
            ACTION_CONTACT);
        return 1;
    }

    actor("You scoop", oblist, " up off the ground and begin crashing"
      + " around with " + oblist[0]->query_objective() + " in what you"
      + " feel sure is a great dance. "
      + capitalize(oblist[0]->query_pronoun()) + " looks"
      + " a bit shaken when you put " + oblist[0]->query_objective()
      + " back down again.");
    all2act(" scoops", oblist, " up off the ground and begins crashing"
      + " around with " + oblist[0]->query_objective() + " in what is"
      + " (presumably) a dance of some kind. Though unharmed, "
      + oblist[0]->query_pronoun() + " looks a bit shaken when the big"
      + " Ogre finally puts " + oblist[0]->query_objective() + " back"
      + " down again.", "", ACTION_CONTACT);
    target(" scoops you up off the ground and begins crashing around"
      + " with you in " + this_player()->query_possessive() + " arms,"
      + " apparently thinking " + this_player()->query_pronoun()
      + " is dancing with you. After a thorough"
      + " jostling, you are finally placed back on the ground, feeling"
      + " a bit shaken.", oblist, "", ACTION_CONTACT);
    return 1;
} /* dance */


int
eyebrow(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "stupidly", 0);

    if (!stringp(how[0]))
    {
        write("You raise an enormous eyebrow" + how[1] + ".\n");
        allbb(" raises " + this_player()->query_possessive() +
            " enormous eyebrow" + how[1] + ".", how[1]);

        return 1;
    }

    oblist = parse_this(how[0], "[eyebrow] [at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Raise your eyebrow [how] at whom/what?\n");
        return 0;
    }

    actor("You raise your enormous eyebrow" + how[1] + " at", oblist);
    all2actbb(" raises " + this_player()->query_possessive() +
        " enormous eyebrow" + how[1] + " at", oblist, 0, how[1]);
    targetbb(" raises " + this_player()->query_possessive()
      + " enormous eyebrow" + how[1] + " at you.", oblist, how[1]);
    return 1;
} /* eyebrow */


int
fart(string str)
{
    string  noise;

    if (stringp(str))
    {
        notify_fail("Fart how?\n");
        return 0;
    }

    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        switch(random(4))
        {
            case 0:
                noise = "The floor vibrates slightly with the"
                  + " deafening sound.";
                break;
            case 1:
                noise = "Once the walls stop shaking, a terrible"
                  + " odor fills the room.";
                break;
            case 2:
                noise = "The sound echoes like a thunderclap"
                  + " throughout the area.";
                break;
            case 3:
            default:
                noise = "Once the dust settles, you notice that"
                  + " every living thing in the area looks a bit"
                  + " wilted.";
                break;
        }
    }
    else
    {
        switch(random(4))
        {
            case 0:
                noise = "In the distance, you see wildlife bolting for"
                  + " cover.";
                break;
            case 1:
                noise = "A passerby glances up, as if expecting to see"
                  + " thunderclouds.";
                break;
            case 2:
                noise = "Nearby, a dozen frightened birds launch immediately"
                  + " into the air and fly quickly away.";
                break;
            case 3:
            default:
                noise = "Not too far off, you hear the sound of an avalanche"
                  + " that seems to have been triggered by the noise.";
                break;
        }
    }

    write("You fart. " + noise + "\n");
    all(" lets off a REAL rip-roarer. " + noise);
    return 1;
} /* fart */


int
flex(string str)
{
    str = check_adverb_with_space(str, "impressively");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Flex your muscles how?\n");
        return 0;
    }

    write("You flex your Ogre muscles" + str + ". Biceps, pectorals,"
      + " and all manner of huge bulging flesh pop out from your already"
      + " massive frame.\n");
    allbb(" flexes " + this_player()->query_possessive() + " huge"
      + " muscles"+ str + ". Sheesh! "
      + capitalize(this_player()->query_possessive()) + " biceps must"
      + " be the size of water barrels!", str);
    return 1;
} /* flex */


int
flip(string str)
{
    if (stringp(str))
    {
        notify_fail("Flip what?\n");
        return 0;
    }

    write("You flip head over heels, sailing about fifteen feet into"
      + " the air before landing with an earth-shaking crash on both"
      + " of your huge feet.\n");
    all(" flips head over heels, sailing about fifteen feet into the"
      + " air before landing with an earth-shaking crash on both of "
      + this_player()->query_possessive() + " huge feet.");
    return 1;
} /* flip */


int
fondle(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "clumsily", 1);

    oblist = parse_this(how[0], "[the] %i",
        ACTION_CONTACT | ACTION_INTIMATE, 1);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Fondle whom/what [how]?\n");
        return 0;
    }

    if (oblist[0] == this_player())
    {
        write("You fondle yourself" + how[1] + ".\n");
        allbb(" fondles " + this_player()->query_objective() + "self" +
            how[1] + ".", how[1], ACTION_OTHER);
        return 1;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only fondle one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You fondle", oblist, how[1] + ".");
        all2act(" fondles", oblist, how[1] + ".", how[1],
            ACTION_CONTACT | ACTION_INTIMATE);
        target(" fondles you" + how[1] + ".", oblist, how[1],
            ACTION_CONTACT | ACTION_INTIMATE);
        return 1;
    }

    actor("You fondle", oblist, how[1] + ", running your huge fingers"
      + " all over " + oblist[0]->query_objective() + ".");
    all2act(" fondles", oblist, how[1] + ", running "
      + this_player()->query_possessive() + " huge fingers all over"
      + " the latter.", how[1],
        ACTION_CONTACT | ACTION_INTIMATE);
    target(" fondles you" + how[1] + ", running "
      + this_player()->query_possessive() + " huge fingers all"
      + " over you.", oblist, how[1],
        ACTION_CONTACT | ACTION_INTIMATE);
    return 1;
} /* fondle */


int
french(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l", ACTION_CONTACT | ACTION_INTIMATE);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("French whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only french kiss one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You give", oblist, " a REAL kiss..it takes a long time..");
        all2act(" gives", oblist, " a deep and passionate kiss.\n" +
            "It seems to take forever...Sexy, eh?", "",
            ACTION_CONTACT | ACTION_INTIMATE);
        target(" gives you a deep and passionate kiss...\n" +
            "It seems to take forever...", oblist, "",
            ACTION_CONTACT | ACTION_INTIMATE);
        return 1;
    }

    actor("You intend to give", oblist, " a REAL kiss. Unfortunately,"
      + " your tongue is about the size of "
      + oblist[0]->query_possessive() + " entire head, and so"
      + " you just end up slopping it all over "
      + oblist[0]->query_possessive() + " face.");
    all2act(" intends to give", oblist, " a deep and passionate kiss."
      + " Unfortunately, " + this_player()->query_possessive()
      + " tongue is so large, that all "
      + this_player()->query_pronoun() + " can really manage is to"
      + " slop it all over the latter's face. Errr ... sexy ..."
      + " I guess??", "",
            ACTION_CONTACT | ACTION_INTIMATE);
    target(" intends to give you a deep and passionate kiss."
      + " Unfortunately, " + this_player()->query_possessive()
      + " tongue is about as large as your head, and so all he can"
      + " manage to do is slop it all over your face. Quite a"
      + " wet one, but such is ogre-love.", oblist, "",
        ACTION_CONTACT | ACTION_INTIMATE);
    return 1;
} /* french */


int
frown(string str)
{
    object *oblist;
    string *how;

    /* Alternative: concernedly -> showing concern? */
    how = parse_adverb_with_space(str, "as if something is wrong", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("frowning" + how[1]);
        write("You frown" + how[1] + ".\n");
        allbb(" frowns" + how[1] + ".", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Frown [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only frown at one target at a time!\n");
        return 1;
    }

    SOULDESC("frowning" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You frown" + how[1] + " at", oblist);
        all2actbb(" frowns" + how[1] + " at", oblist, 0, how[1]);
        targetbb(" frowns" + how[1] + " at you.", oblist, how[1]);
        return 1;
    }

    actor("You look down at", oblist, " and frown" + how[1] + ".");
    all2actbb(" looks down at", oblist, " and frowns" + how[1] + ".",
        how[1]);
    targetbb(" looks down at you and frowns" + how[1] + ".", oblist,
        how[1]);
    return 1;
} /* frown */


int
giggle(string str)
{
    str = check_adverb_with_space(str, "stupidly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Giggle how?\n");
        return 0;
    }

    SOULDESC("giggling" + str);
    write("You giggle" + str + " (and loudly.)\n");
    all(" giggles" + str + ". It sounds a bit like a buffalo choking on"
      + " something painful.", str);
    return 1;
} /* giggle */


int
glare(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "stonily", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("glaring" + how[1]);
        write("You glare" + how[1] + ".\n");
        allbb(" glares" + how[1] + ".", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Glare [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only glare at one target at a time!\n");
        return 1;
    }

    SOULDESC("glaring" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You glare" + how[1] + " at", oblist);
        all2actbb(" glares" + how[1] + " at", oblist, 0, how[1]);
        targetbb(" glares" + how[1] + " at you.", oblist, how[1]);
        return 1;
    }

    actor("You glare" + how[1] + " down at", oblist, ".");
    all2actbb(" glares" + how[1] + " down at", oblist, 0, how[1]);
    targetbb(" glares down at you" + how[1] + ".", oblist, how[1]);
    return 1;
} /* glare */


int
grin(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "stupidly", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("grinning" + how[1]);
        write("You grin" + how[1] + ".\n");
        allbb(" grins" + how[1] + ".", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Grin [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only grin at one target at a time!\n");
        return 1;
    }

    SOULDESC("grinning" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You grin" + how[1] + " at", oblist);
        all2act(" grins" + how[1] + " at", oblist, 0, how[1]);
        targetbb(" grins" + how[1] + " at you.", oblist, how[1]);
        return 1;
    }

    actor("You look down at", oblist, " and grin" + how[1] + ".");
    all2act(" looks down at", oblist, " and grins" + how[1] + ".",
        how[1]);
    target(" looks down at you and grins" + how[1] + ".", oblist,
        how[1]);
    return 1;
} /* grin */


int
grope(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %i", ACTION_CONTACT | ACTION_INTIMATE);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Grope whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only grope one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You grope", oblist, " in an unskilled manner.");
        all2act(" gropes", oblist, " in an unskilled manner.", "",
            ACTION_CONTACT | ACTION_INTIMATE);
        target(" gropes you in an unskilled manner.", oblist, "",
            ACTION_CONTACT | ACTION_INTIMATE);
        return 1;
    }

    actor("You reach down and grope", oblist, " with your huge and"
      + " clumsy hands.");
    all2act(" reaches down and gropes", oblist, " with "
      + this_player()->query_possessive() + " huge and"
      + " clumsy hands.", "", ACTION_CONTACT | ACTION_INTIMATE);
    target(" reaches down and gropes you with "
      + this_player()->query_possessive() + " huge and"
      + " clumsy hands.", oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
    return 1;
} /* grope */


int
growl(string str)
{
    object *oblist;
    string *how,
            noise;

    how = parse_adverb_with_space(str, "menacingly", 0);
    noise = ", producing a deep and unsettling sound.";

    if (!stringp(how[0]))
    {
        SOULDESC("growling" + how[1]);
        write("You growl" + how[1] + noise + "\n");
        all(" growls" + how[1] + noise, how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Growl [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only growl at one target at a time!\n");
        return 1;
    }

    SOULDESC("growling" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You growl" + how[1] + " at", oblist, noise);
        all2act(" growls" + how[1] + " at", oblist, noise, how[1]);
        target(" growls" + how[1] + " at you" + noise, oblist, how[1]);
        return 1;
    }

    actor("You look down at", oblist, " and growl" + how[1] + noise);
    all2act(" looks down at", oblist, " and growls" + how[1] + noise,
        how[1]);
    target(" looks down at you and growls" + how[1] + noise, oblist,
        how[1]);
    return 1;
} /* growl */


int
hiccup(string str)
{
    if (stringp(str))
    {
        notify_fail("Hiccup what?\n");
        return 0;
    }

    SOULDESC("having the hiccups");
    write("HICCUP!!!\n");
    all(" hiccups with a sound like twenty elephants belching!");
    return 1;
} /* hiccup */


int
hmm(string str)
{
    object *oblist;

    if (!stringp(str))
    {
        write("Hmmmmmmmmmmmmmmm ...\n");
        all(" goes hmmmmmmmmmmmmmmmmmmmm.\nA completely blank expression"
          + " comes over " + this_player()->query_possessive()
          + " face.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Go hmm at whom/what?\n");
        return 0;
    }

    actor("You go hmmmmmmmmmmmmmmmmmm at", oblist, ", your tiny"
      + " brain trying to think.");
    all2act(" goes hmmmmmmmmmmmmmmmmmm at", oblist, ", a completely"
      + " blank expression coming over "
      + this_player()->query_possessive() + " face.");
    target(" goes hmmmmmmmmmmmmmmmmmm at you, a completely blank"
      + " expression coming over " + this_player()->query_possessive()
      + " face.", oblist);
    return 1;
} /* hmm */


int
hold(string str)
{
    object *oblist;

    if (str == "all")
    {
        notify_fail("To hold all people, use \"hold all close\".\n");
        return 0;
    }
 
    oblist = parse_this(str, "[the] %l [close]", ACTION_CONTACT);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        oblist = parse_this(str, "[the] %i 'close'");

        if (!sizeof(oblist))
        {
            if (strlen(parse_msg))
            {
                write(parse_msg);
                return 1;
            }

            notify_fail("Hold whom/what?\n");
            return 0;
        }
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only hold one target close at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You hold", oblist, " close.");
        all2act(" holds", oblist, " close.", "", ACTION_CONTACT);
        target(" holds you close.", oblist, "", ACTION_CONTACT);
        return 1;
    }

    actor("You reach down and hold", oblist, " close, pressing "
      + oblist[0]->query_objective() + " softly up against the side"
      + " of your leg.");
    all2act(" reaches down and holds", oblist, " close, pressing"
      + " the latter softly up against the side of "
      + this_player()->query_possessive() + " leg.", "", ACTION_CONTACT);
    target(" reaches down and holds you close, pressing you softly"
      + " up against the side of " + this_player()->query_possessive()
      + " leg.", oblist, "", ACTION_CONTACT);
    return 1;
} /* hold */


int
hug(string str)
{
    object *oblist;
    string *how;
    int    grouphug;

    how = parse_adverb_with_space(str, BLANK_ADVERB, 1);

    grouphug = (how[0] == "all");
    oblist = parse_this(how[0], "[the] %i", ACTION_CONTACT);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Hug whom/what [how]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        if (grouphug)
        {
            actor("You wrap your gigantic arms around", oblist,
                how[1] + " giving them a monstrous group-hug.");
            all(" wraps " + this_player()->query_possessive() + " massive"
              + " arms around everyone in the room," + how[1] + " giving"
              + " you all a monstrous group-hug.", how[1], ACTION_CONTACT);
            return 1;
        }
        else
        {
            write("You can either hug one target at a time, or do"
              + " a group-hug using <hug all>.\n");
            return 1;
        }
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You hug", oblist, how[1] + ".");
        all2act(" hugs", oblist, how[1] + ".", how[1], ACTION_CONTACT);
        target(" hugs you" + how[1] + ".", oblist, how[1], ACTION_CONTACT);
        return 1;
    }

    actor("You reach down and scoop", oblist, " up in your massive"
      + " arms," + how[1] + " giving " + oblist[0]->query_objective()
      + " a great big hug. Hearing"
      + " a few of " + oblist[0]->query_possessive() + " ribs crack"
      + " you quickly drop " + oblist[0]->query_objective() + " back"
      + " to the ground.");
    all2act(" reaches down and scoops", oblist, " up in "
      + this_player()->query_possessive() + " massive arms," + how[1]
      + " giving " + oblist[0]->query_objective() + " a great big hug."
      + " The latter blanches"
      + " briefly as a few ribs are squeezed too tight before being"
      + " dropped back to the ground.", how[1], ACTION_CONTACT);
    target(" reaches down and scoops you up in "
      + this_player()->query_possessive() + " massive arms,"
      + how[1] + " giving you a great big hug. You wince in pain"
      + " as a few of your ribs begin to crack before being abruptly"
      + " dropped back to the ground.", oblist, how[1], ACTION_CONTACT);
    return 1;
} /* hug */


int
hum(string str)
{
    if (!strlen(str))
    {
        str = "dreadful";
    }
    else
    {
        if (!parse_command(str, ({ }), "[a] %w [tune]", str))
        {
            notify_fail("What kind of tune do you want to hum?\n");
            return 0;
        }
    }

    str = LANG_ADDART(str);
    write("You hum " + str + " tune. The sound is similar to"
      + " that of a hippopotamus drowning in a tarpit.\n");
    say(QCTNAME(this_player()) + " hums " + str + " tune. The sound"
      + " is similar to that of a hippopotamus drowning in a"
      + " tarpit.\n");
    return 1;
} /* hum */


int
jump(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 0);

    if (!stringp(how[0]))
    {
        if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
        {
            how[1] = ADD_SPACE_TO_ADVERB("unexpectedly");
        }

        write("You jump" + how[1] + ", landing again with a loud"
          + " crash!\n");
        all(" jumps" + how[1] + ", landing again with a loud"
          + " crash!", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[on] / [over] [the] %i",
        ACTION_CONTACT | ACTION_HACTIVITY);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Jump how [over whom/what]?\n");
        return 0;
    }

    if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
    {
        how[1] = ADD_SPACE_TO_ADVERB("excitedly");
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only jump over one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You jump" + how[1] + " all over", oblist);
        all2act(" jumps" + how[1] + " all over", oblist, 0, how[1],
            ACTION_CONTACT | ACTION_HACTIVITY);
        target(" jumps" + how[1] + " all over you.", oblist, how[1],
            ACTION_CONTACT | ACTION_HACTIVITY);
        return 1;
    }

    actor("You jump" + how[1] + " over", oblist, "'s head and lands"
      + " with a loud crash!");
    all2act(" jumps" + how[1] + " over", oblist, "'s head and lands"
      + " with a loud crash!", how[1],
        ACTION_HACTIVITY);
    target(" jumps" + how[1] + " over your head and lands with a loud"
      + " crash!", oblist, how[1],
        ACTION_HACTIVITY);
    return 1;
} /* jump */


int
kick(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "fanatically", 1);

    oblist = parse_this(how[0], "[the] %i",
        ACTION_CONTACT | ACTION_MACTIVITY | ACTION_OFFENSIVE);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Kick whom/what [how]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only kick one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You kick", oblist, how[1] + ".");
        all2act(" kicks", oblist, how[1] + ".", how[1],
            ACTION_CONTACT | ACTION_MACTIVITY | ACTION_OFFENSIVE);
        target(" kicks you" + how[1] + ".   OUCH!!!", oblist, how[1],
            ACTION_CONTACT | ACTION_MACTIVITY | ACTION_OFFENSIVE);
        return 1;
    }

    actor("You kick", oblist, how[1] + ", sending "
      + oblist[0]->query_objective() + " flying through the air"
      + " to land in a disgruntled heap yards away.");
    all2act(" kicks", oblist, how[1] + ", sending "
      + oblist[0]->query_objective() + " flying through the air"
      + " to land in a disgruntled heap yards away.", how[1],
        ACTION_CONTACT | ACTION_MACTIVITY | ACTION_OFFENSIVE);
    target(" kicks you" + how[1] + ", sending you flying through"
      + " the air to land in a heap yards away. OOOF!!!", oblist,
        how[1], ACTION_CONTACT | ACTION_MACTIVITY | ACTION_OFFENSIVE);
    return 1;
} /* kick */


int
kiss(string str)
{
    object *oblist;
    string *how;
    string *zones;
    string *parts;
    int size;
    string location;

    if (!stringp(str))
    {
        notify_fail("Whom are you trying to kiss [how/where]?\n");
        return 0;
    }

    zones = ({ "forehead", "cheek", "lips", "nose", "hand", "feet", "chin",
        "neck", "ear" });

    parts = explode(str, " ");
    if ((size = sizeof(parts)) > 1)
    {
        if (member_array(parts[size - 1], zones) != -1)
        {
            location = parts[size - 1];
            str = implode(parts[..(size - 2)], " ");
        }
    }

    if (strlen(location))
    {
        oblist = parse_this(str, "[the] %l [on] [the]",
            ACTION_CONTACT | ACTION_INTIMATE);
    }
    else
    {
        how = parse_adverb_with_space(str, "clumsily", 1);
        oblist = parse_this(how[0], "[the] %i",
            ACTION_CONTACT | ACTION_INTIMATE);
    }

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Kiss whom [how/where]?\n");
        return 0;
    }


    if (sizeof(oblist) > 1)
    {
        write("You can only kiss one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        if (strlen(location))
        {
            str = ((sizeof(oblist) == 1) ?
                (oblist[0]->query_possessive() + " " + location + ".") :
                ("their " + location + "s."));
            actor("You kiss", oblist, " on " + str);
            all2act(" kisses", oblist, " on " + str, "",
                ACTION_CONTACT | ACTION_INTIMATE);
            target(" kisses you on your " + location + ".", oblist, "",
                ACTION_CONTACT | ACTION_INTIMATE);
        }
        else
        {
            actor("You kiss", oblist, how[1] + ".");
            all2act(" kisses", oblist, how[1] + ".", how[1],
                ACTION_CONTACT | ACTION_INTIMATE);
            target(" kisses you" + how[1] + ".", oblist, how[1],
                ACTION_CONTACT | ACTION_INTIMATE);
        }

        return 1;
    }

    if (strlen(location))
    {
        str = ((sizeof(oblist) == 1) ?
            (oblist[0]->query_possessive() + " " + location + ".") :
            ("their " + location + "s."));
        actor("You get down on one knee and kiss", oblist, " on " + str);
        all2act(" gets down on one knee and kisses", oblist, " on "
          + str, "", ACTION_CONTACT | ACTION_INTIMATE);
        target(" gets down on one knee and kisses you on your "
          + location + ".", oblist, "",
            ACTION_CONTACT | ACTION_INTIMATE);
    }
    else
    {
        actor("You get down on one knee and kiss", oblist, how[1]
          + " with your huge lips.");
        all2act(" gets down on one knee and kisses", oblist, how[1]
          + " with " + this_player()->query_possessive()
          + " huge lips.", how[1], ACTION_CONTACT | ACTION_INTIMATE);
        target(" gets down on one knee and kisses you" + how[1]
          + " with " + this_player()->query_possessive()
          + " huge lips.", oblist, how[1],
            ACTION_CONTACT | ACTION_INTIMATE);
    }

    return 1;
} /* kiss */


int
knee(string str)
{
    object *oblist;
    object *femlist;

    oblist = parse_this(str, "[the] %l",
        ACTION_CONTACT | ACTION_OFFENSIVE | ACTION_MACTIVITY);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Knee whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only knee one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        femlist = FILTER_GENDER(oblist, G_FEMALE);
        if (sizeof(femlist))
        {
            actor("You try to knee", femlist,
                ".\nNot very effective though.");
            all2act(" tries to knee", femlist,
                ".\nNot very effective though.", "",
                ACTION_CONTACT | ACTION_OFFENSIVE | ACTION_MACTIVITY);
            target(" tries to knee you, without much effect.", femlist,
                "", ACTION_CONTACT | ACTION_OFFENSIVE | ACTION_MACTIVITY);
            return 1;
        }
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        if (sizeof(oblist))
        {
            actor("You hit", oblist, " with your knee, sending " +
                ((sizeof(oblist) > 1) ? "them" : "him") +
                " to the ground, writhing in pain!");
            all2act(" suddenly raises " + this_player()->query_possessive() +
                " knee, sending", oblist, " to the floor, writhing in pain!", "",
                ACTION_CONTACT | ACTION_OFFENSIVE | ACTION_MACTIVITY);
            target(" hits you with " + this_player()->query_possessive() +
                " knee below your belt!\n" +
                "You double over and fall to the ground, writhing in " +
                "excrutiating pain,\nfeeling like you may throw up " +
                "everything you have eaten!", oblist, "",
                ACTION_CONTACT | ACTION_OFFENSIVE | ACTION_MACTIVITY);
            return 1;
        }
    }

    actor("You attempt to knee", oblist, " in the groin. Unfortunately,"
      + " with your great height, you instead knee "
      + oblist[0]->query_objective() + " in the face, sending "
      + oblist[0]->query_objective() + " staggering backward!");
    all2act(" attempts to knee", oblist, " in the groin. Unfortunately,"
      + " due to the difference in height, "
      + this_player()->query_pronoun() + " instead knees "
      + oblist[0]->query_objective() + " in the face, sending "
      + oblist[0]->query_objective() + " staggering backward!",
        ACTION_CONTACT | ACTION_OFFENSIVE | ACTION_MACTIVITY);
    target(" attempts to knee you in the groin. Unfortunately, because "
      + this_player()->query_pronoun() + " is so tall, "
      + this_player()->query_possessive() + " gigantic knee smashes"
      + " right into your face, sending you staggering backward in"
      + " terrible pain!", oblist, "",
        ACTION_CONTACT | ACTION_OFFENSIVE | ACTION_MACTIVITY);
    return 1;
} /* knee */


int
kneel(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "respectfully", 0);

    if (!stringp(how[0]))
    {
        write("You kneel" + how[1] + ", still managing to tower"
          + " nearly ten feet off the ground.\n");
        allbb(" kneels" + how[1] + ", still managing to tower"
          + " nearly ten feet off the ground.", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[before] [the] %i", ACTION_PROXIMATE);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Kneel [how] before whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only knee one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You kneel" + how[1] + " before", oblist);
        all2actbb(" kneels" + how[1] + " before", oblist, 0, how[1],
            ACTION_PROXIMATE);
        targetbb(" kneels" + how[1] + " before you.", oblist, how[1],
            ACTION_PROXIMATE);
       return 1;
    }

    actor("You kneel" + how[1] + " before", oblist, ", still"
      + " managing to tower high above "
      + oblist[0]->query_objective() + ".");
    all2actbb(" kneels" + how[1] + " before", oblist, ", still managing"
      + " to tower high above " + oblist[0]->query_objective() + ".",
        how[1], ACTION_PROXIMATE);
    targetbb(" kneels" + how[1] + " before you, still managing to"
      + " tower high above your head.", oblist, how[1],
        ACTION_PROXIMATE);
    return 1;
} /* kneel */


int
laugh(string str)
{
    object *oblist;
    string *how;

    if (!stringp(str))
    {
        write("You fall down laughing, slamming the ground with your"
          + " mighty fists.\n");
        all(" falls down laughing, slamming the ground with "
          + this_player()->query_possessive() + " mighty fists.");
        SOULDESC("laughing");
        return 1;
    }

    how = parse_adverb_with_space(str, "stupidly", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("laughing" + how[1]);
        write("You laugh" + how[1] + ".\n");
        all(" laughs" + how[1] + ".", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i", 0, 1);

    if (!sizeof(oblist))
    {
        notify_fail("Laugh how [at whom/what]?\n");
        return 0;
    }

    if (oblist[0] == this_player())
    {
        SOULDESC("laughing" + how[1]);
        write("You laugh" + how[1] + " at yourself.\n");
        all(" laughs" + how[1] + " at " + this_player()->query_objective() +
            "self.", how[1]);
        return 1;
    }

    SOULDESC("laughing" + how[1]);
    actor("You laugh" + how[1] + " at", oblist, ", stomping your"
      + " mighty feet on the ground.");
    all2act(" laughs" + how[1] + " at", oblist, ", stomping "
      + this_player()->query_possessive() + " mighty feet on"
      + " the ground." , how[1]);
    target(" laughs" + how[1] + " at you, stomping "
      + this_player()->query_possessive() + " mighty feet on the"
      + " ground.", oblist, how[1]);
    return 1;
} /* laugh */


int
lick(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 1);

    if (!stringp(how[0]))
    {
        if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
        {
            how[1] = ADD_SPACE_TO_ADVERB("hungrily");
        }

        write("You lick your huge lips" + how[1] + ".\n");
        allbb(" licks " + this_player()->query_possessive() + " huge"
          + " lips" + how[1] + ".", how[1], ACTION_VISUAL);
        return 1;
    }

    oblist = parse_this(how[0], "[the] %i",
        ACTION_CONTACT | ACTION_INTIMATE);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Lick whom/what [how]?\n");
        return 0;
    }

    if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
    {
        how[1] = ADD_SPACE_TO_ADVERB("joyously");
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only lick one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You lick", oblist, how[1] + ".");
        all2actbb(" licks", oblist, how[1] + ".", how[1],
            ACTION_CONTACT | ACTION_INTIMATE);
        target(" licks you" + how[1] + ".", oblist, how[1],
            ACTION_CONTACT | ACTION_INTIMATE);
        return 1;
    }

    actor("You lick", oblist, how[1] + ", your huge tongue leaving "
      + oblist[0]->query_objective()
      + " with a very wet face.");
    all2actbb(" licks", oblist, how[1] + ", "
      + this_player()->query_possessive() + " huge tongue leaving"
      + " the latter with a very wet face.", how[1],
        ACTION_CONTACT | ACTION_INTIMATE);
    target(" licks you" + how[1] + ", "
      + this_player()->query_possessive() + " huge tongue leaving"
      + " you with a very wet face.", oblist, how[1],
        ACTION_CONTACT | ACTION_INTIMATE);
    return 1;
} /* lick */


int
love(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %i", ACTION_PROXIMATE | ACTION_INTIMATE);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Love whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only love one target at a time!\n");
        return 1;
    }

    SOULDESC("hopelessly in love");

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You tell your true feelings to", oblist);
        all2act(" whispers softly to", oblist, "", "",
            ACTION_PROXIMATE | ACTION_INTIMATE);
        target(" whispers sweet words of love to you.", oblist, "",
            ACTION_PROXIMATE | ACTION_INTIMATE);
        return 1;
    }

    actor("You bend down and tell your true feelings to", oblist,
        ", hoping that you didn't goof up the words.");
    all2act(" bends down and whispers softly to", oblist, ", looking"
      + " a bit sheepish while doing so.", "",
        ACTION_PROXIMATE | ACTION_INTIMATE);
    target(" bends down and whispers a bunch clumsy nonsense in"
      + " your ear. You manage to understand that the big ogre must"
      + " love you, even though the attempt to tell you so was"
      + " horribly botched.", oblist, "",
        ACTION_PROXIMATE | ACTION_INTIMATE);
    return 1;
} /* love */


int
melt(string str)
{
    object *oblist;

    oblist = parse_this(str, "[in] [the] %l", ACTION_CONTACT | ACTION_INTIMATE);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Melt in whose arms?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only melt in one target's arms at a time!\n");
        return 1;
    }

    SOULDESC("hopelessly in love");

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You melt in", oblist, "'s arms.");
        all2act(" melts in", oblist, "'s arms.", "",
            ACTION_CONTACT | ACTION_INTIMATE);
        target(" melts in your arms.", oblist, "",
            ACTION_CONTACT | ACTION_INTIMATE);
        return 1;
    }

    actor("You melt in", oblist, "'s arms, nearly crushing "
      + oblist[0]->query_objective() + " beneath you. Whoopsie!! You"
      + " quickly rise and help " + oblist[0]->query_objective()
      + " up off the ground.");
    all2act(" melts in", oblist, "'s arms, nearly crushing the"
      + " poor soul beneath " + this_player()->query_objective()
      + ". With a look of surprise and concern, the big ogre quickly"
      + " rises and helps " + oblist[0]->query_objective()
      + " up off the ground.", "",
        ACTION_CONTACT | ACTION_INTIMATE);
    target(" melts in your arms, nearly crushing you beneath "
      + this_player()->query_possessive() + " massive body! Realizing"
      + " what has happened, " + this_player()->query_pronoun()
      + " quickly gets off of you and helps you to your feet,"
      + " looking a bit sheepish.", oblist, "",
        ACTION_CONTACT | ACTION_INTIMATE);
    return 1;
} /* melt */


int
nibble(string str)
{
    object *oblist;

    oblist = parse_this(str, "[on] [the] %l",
        ACTION_CONTACT | ACTION_INTIMATE);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Nibble on whose ear?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only nibble on one target's ear at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You nibble on", oblist, "'s ear.");
        all2act(" nibbles on", oblist, "'s ear.", "",
            ACTION_CONTACT | ACTION_INTIMATE);
        target(" nibbles on your ear.", oblist, "",
            ACTION_CONTACT | ACTION_INTIMATE);
        return 1;
    }

    actor("You bend down and try to nibble on", oblist, "'s ear, but"
      + " your big teeth are so clumsy you accidentally chew on the"
      + " entire side of " + oblist[0]->query_possessive() + " face!");
    all2act(" bends down and tries to nibble on", oblist, "'s ear,"
      + " but " + this_player()->query_possessive() + " big ogre teeth"
      + " are so clumsy that " + this_player()->query_pronoun()
      + " instead ends up accidentally chewing on the entire side of"
      + " the latter's face!", "",
        ACTION_CONTACT | ACTION_INTIMATE);
    target(" bends down and tries to nibble on your ear, but "
      + this_player()->query_possessive() + " big ogre teeth are so"
      + " clumsy that " + this_player()->query_pronoun() + " ends up"
      + " accidentally chewing on the entire side of your face!",
         oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
    return 1;
} /* nibble */


int
nod(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "stupidly", 0);

    if (!stringp(how[0]))
    {
        write("You nod" + how[1] + ".\n");
        allbb(" nods" + how[1] + ".", how[1]);
        SOULDESC("nodding" + how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Nod [how] at whom/what?\n");
        return 0;
    }

    SOULDESC("nodding" + how[1]);

    if (sizeof(oblist) > 1)
    {
        write("You can only nod at one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You nod" + how[1] + " at", oblist);
        all2actbb(" nods" + how[1] + " at", oblist, 0, how[1]);
        targetbb(" nods" + how[1] + " at you.", oblist, how[1]);
        return 1;
    }

    actor("You look down at", oblist, " and nod" + how[1] + ".");
    all2act(" looks down at", oblist, " and nods" + how[1] + ".",
        how[1]);
    target(" looks down at you and nods" + how[1] + ".", oblist,
        how[1]);
    return 1;
} /* nod */


int
nudge(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %i", ACTION_CONTACT | ACTION_VISUAL);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Nudge whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only nudge one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You nudge", oblist);
        all2act(" nudges", oblist, "", ACTION_CONTACT | ACTION_VISUAL);
        target(" nudges you.", oblist, "", ACTION_CONTACT | ACTION_VISUAL);
        return 1;
    }

    actor("You nudge", oblist, ", nearly knocking "
      + oblist[0]->query_objective() + " over.");
    all2act(" nudges", oblist, ", nearly knocking "
      + oblist[0]->query_objective() + " over.",
        ACTION_CONTACT | ACTION_VISUAL);
    target(" nudges you, nearly knocking you over.", oblist, "",
        ACTION_CONTACT | ACTION_VISUAL);
    return 1;
} /* nudge */


int
nuzzle(string str)
{
    object *oblist;
    string *how;
    string pos;

    how = parse_adverb_with_space(str, "playfully", 1);

    oblist = parse_this(how[0], "[the] %l",
        ACTION_CONTACT | ACTION_INTIMATE | ACTION_VISUAL);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Nuzzle whom [how]?\n");
        return 0;
    }

    pos = oblist[0]->query_possessive();
    str = this_player()->query_possessive();

    if (sizeof(oblist) > 1)
    {
        write("You can only nuzzle one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You put your arms around", oblist, " and nuzzle your face"
          + how[1] + " in " + pos + " neck.");
        all2act(" puts " + str + " arms around" , oblist, " and nuzzles "
          + str + " face" + how[1] + " in " + pos + " neck.", how[1],
            ACTION_CONTACT | ACTION_INTIMATE | ACTION_VISUAL);
        target(" puts " + str + " arms around you and nuzzles " + str +
            " face" + how[1] + " in your neck.", oblist, how[1],
            ACTION_CONTACT | ACTION_INTIMATE | ACTION_VISUAL);
        return 1;
    }

    actor("You bend down and nuzzle", oblist, "'s neck" + how[1]
      + " with your gigantic nose.");
    all2act(" bends down and nuzzles", oblist, "'s neck" + how[1]
      + " with " + str + " gigantic nose.", how[1],
        ACTION_CONTACT | ACTION_INTIMATE | ACTION_VISUAL);
    target(" bends down and nuzzles your neck" + how[1] + " with "
      + str + " gigantic nose.", oblist, how[1],
        ACTION_CONTACT | ACTION_INTIMATE | ACTION_VISUAL);
    return 1;
} /* nuzzle */


int
pat(string str)
{
    object *oblist;
    string *zones;
    string *parts;
    int    size;
    string location;

    zones = ({ "back", "forehead", "head", "shoulder", "tummy", "belly",
        "bottom" });

    /* When patting yourself, pat on your tummy. */
    str = (strlen(str) ? lower_case(str) : "tummy");
    if (member_array(str, zones) != -1)
    {
        write("You pat yourself on your gigantic " + str + ".\n");
        all(" pats " + this_player()->query_objective() +
           "self on " + this_player()->query_possessive() + " gigantic "
         + str + ".", "", ACTION_VISUAL);
        return 1;
    }

    parts = explode(str, " ");
    if ((size = sizeof(parts)) > 1)
    {
        if (member_array(parts[size - 1], zones) != -1)
        {
            location = parts[size - 1];
            str = implode(parts[..(size - 2)], " ");
        }
    }

    oblist = parse_this(str, "[the] %l [on] [the]", ACTION_CONTACT);
    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Pat [whom] [where]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only pat one target at a time!\n");
        return 1;
    }

    /* When patting someone else, pat on the back by default if
     * they are a fellow ogre. Non-ogres make it the head.
     */
    if (!stringp(location))
    {
        if (IS_OGRE(oblist[0]))
        {
            location = "back";
        }
        else
        {
            location = "head";
        }
    }

    str = ((sizeof(oblist) == 1) ?
           (oblist[0]->query_possessive() + " " + location) :
           ("their " + location + "s"));

    if (IS_OGRE(oblist[0]))
    {
        actor("You pat", oblist, " on " + str + ".");
        all2act(" pats", oblist, " on " + str + ".", "", ACTION_CONTACT);
        target(" pats you on your " + location + ".", oblist, "",
            ACTION_CONTACT);
        return 1;
    }

    actor("You reach down and pat", oblist, " on " + str + " with your"
      + " fingertips.");
    all2act(" reaches down and pats", oblist, " on " + str + " with "
      + this_player()->query_possessive() + " fingertips.", "",
        ACTION_CONTACT);
    target(" reaches down and pats you on your " + location + " with "
      + this_player()->query_possessive() + " fingertips.", oblist,
        "", ACTION_CONTACT);
    return 1;
} /* pat */


int
peer(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "quizzically", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("peering" + how[1]);
        write("You peer" + how[1] + " around.\n");
        allbb(" peers" + how[1] + " around.", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Peer [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only poke one target at a time!\n");
        return 1;
    }

    SOULDESC("peering" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You peer" + how[1] + " at", oblist,".  Hmm......");
        all2actbb(" peers" + how[1] + " at", oblist, 0, how[1]);
        targetbb(" peers" + how[1] + " at you.", oblist, how[1]);
        return 1;
    }

    actor("You peer" + how[1] + " down at", oblist,".  Hmm......");
    all2actbb(" peers" + how[1] + " down at", oblist, 0, how[1]);
    targetbb(" peers" + how[1] + " down at you.", oblist, how[1]);
    return 1;
} /* peer */


int
pet(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "adoringly", 1);

    if (!stringp(how[0]))
    {
        notify_fail("Pet whom [how]?\n");
        return 0;
    }

    oblist = parse_this(how[0], "[the] %l", ACTION_CONTACT);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Pet whom [how]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only pet one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]))
    {
        actor("You pet", oblist, how[1] + " on the head.");
        all2act(" pets", oblist, how[1] + " on the head.", how[1],
            ACTION_CONTACT);
        target(" pets you" + how[1] + " on the head.", oblist, how[1],
           ACTION_CONTACT);
        return 1;
    }

    actor("You reach down and pet", oblist, how[1] + " on the head.");
    all2act(" reaches down and pets", oblist, how[1] + " on the head.",
        how[1], ACTION_CONTACT);
    target(" reaches down and pets you" + how[1] + " on the head.",
        oblist, how[1], ACTION_CONTACT);
    return 1;
} /* pet */


int
poke(string str)
{
    object *oblist;
    string *zones;
    string *parts;
    string location;
    int    size;

    zones = ({ "eye", "ear", "nose", "thorax", "abdomen", "shoulder", "ribs" });

    str = (strlen(str) ? lower_case(str) : "abdomen");
    if (member_array(str, zones) != -1)
    {
        write("You poke yourself in your " + str + ".\n");
        all(" pokes " + this_player()->query_objective() +
            "self in " + this_player()->query_possessive() + " " + str + ".");
        return 1;
    }

    parts = explode(str, " ");
    if ((size = sizeof(parts)) > 1)
    {
        if (member_array(parts[size - 1], zones) != -1)
        {
            location = parts[size - 1];
            str = implode(parts[..(size - 2)], " ");
        }
    }

    if (!stringp(location))
    {
        location = "ribs";
    }

    oblist = parse_this(str, "[the] %l [in] [the]", ACTION_CONTACT);
    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Poke [whom] [where]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only poke one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You poke", oblist, " in the " + location + ".");
        all2act(" pokes", oblist, " in the " + location + ".", "",
            ACTION_CONTACT);
        target(" pokes you in the " + location + ".", oblist, "",
            ACTION_CONTACT);
        return 1;
    }

    actor("You poke", oblist, " in the " + location + ", the tip"
      + " of your giant finger pushing " + oblist[0]->query_objective()
      + " back a bit.");
    all2act(" pokes", oblist, " in the " + location + ", the tip"
      + " of " + this_player()->query_possessive() + " giant finger"
      + " pushing the latter back a bit.", "", ACTION_CONTACT);
    target(" pokes you in the " + location + ", the tip of "
      + this_player()->query_possessive() + " giant finger pushing"
      + " you back a bit.", oblist, "", ACTION_CONTACT);
    return 1;
} /* poke */


int
pounce(string str)
{
    object *oblist;
    string pos;
    string obj;

    oblist = parse_this(str, "[on] [the] %l", ACTION_CONTACT);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Pounce on whom?\n");
        return 0;
    }

    pos = ((sizeof(oblist) > 1) ? "their" : oblist[0]->query_possessive());
    obj = ((sizeof(oblist) > 1) ? "them" : oblist[0]->query_objective());

    if (sizeof(oblist) > 1)
    {
        write("You can only pounce on one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You pounce on", oblist, " like a cat, knocking " + obj +
            " flat on " + pos + " back!");
        all2act(" pounces on", oblist, " like a cat, knocking " + obj +
            " flat on " + pos + " back!", "", ACTION_CONTACT);
        target(" pounces on you like a cat, knocking you flat on your back.",
            oblist, "", ACTION_CONTACT);
        return 1;
    }

    actor("You try to pounce on", oblist, " like a cat, but instead"
      + " end up landing on " + obj + " more like an oliphaunt,"
      + " knocking " + obj + " flat on " + pos + " back!");
    all2act(" tries to pounce on", oblist, " like a cat, but instead"
      + " ends up landing on " + obj + " more like an oliphaunt,"
      + " knocking " + obj + " flat on " + pos + " back!", "",
          ACTION_CONTACT);
    target(" tries to pounce on you like a cat, but instead ends up"
      + " landing on your more like an oliphaunt, knocking you flat on"
      + " your back.", oblist, "", ACTION_CONTACT);
    return 1;
} /* pounce */


int
puke(string str)
{
    object *oblist;

    if (!stringp(str))
    {
        write("You puke all over the place. Nearly everything in"
          + " the area is splattered with your awful sick!\n");
        all(" doubles over and pukes all over the place. Nearly"
          + " everything in the area is splattered with "
          + this_player()->query_possessive() + " awful sick!");
        return 1;
    }

    oblist = parse_this(str, "[on] / [over] [the] %i", 
        ACTION_PROXIMATE | ACTION_OFFENSIVE);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Puke on whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only puke on one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You puke on", oblist);
        all2act(" pukes on", oblist, "", "",
            ACTION_PROXIMATE | ACTION_OFFENSIVE);
        target(" pukes all over you!", oblist, "",
            ACTION_PROXIMATE | ACTION_OFFENSIVE);
        return 1;
    }

    actor("You puke on", oblist, ", completely drenching "
      + oblist[0]->query_objective() + " in"
      + " your hideous vomit. Oh, the humanity!!");
    all2act(" pukes on", oblist, ", completely drenching "
      + oblist[0]->query_objective() + " in hideous vomit. Oh, the"
      + " humanity!!", "",
        ACTION_PROXIMATE | ACTION_OFFENSIVE);
    target(" pukes all over you, completely drenching you in "
      + this_player()->query_possessive() + " hideous vomit! Death"
      + " could scarcely be worse than this! Oh, the humanity!!",
        oblist, "", ACTION_PROXIMATE | ACTION_OFFENSIVE);
    return 1;
} /* puke */


int
purr(string str)
{
    str = check_adverb_with_space(str, "contentedly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Purr how?\n");
        return 0;
    }

    SOULDESC("purring" + str);
    write("MMMMEEEEEEEEOOOOOOOWWWWWWW! You purr" + str + ". The sound"
      + " is something like an enormous panther.\n");
    all(" purrs" + str + ". The sound is something like an enormous"
      + " panther.", str, ACTION_AURAL);
    return 1;
} /* purr */


int
roar(string str)
{
    string  noise;

    str = check_adverb_with_space(str, "aggressively");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Roar how?\n");
        return 0;
    }

    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        noise = str + " sending vibrations rattling along the walls"
          + " and floor";
    }
    else
    {
        noise = str + ", the sound echoing for miles around";
    }

    SOULDESC("roaring" + str);
    write("RRRRROOOOOOAAAAAWWWWWW! You roar" + noise + ".\n");
    all(" roars" + noise + ".", str, ACTION_AURAL);
    return 1;
} /* roar */


int
ruffle(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "playfully", 1);

    oblist = parse_this(how[0], "[the] %l", ACTION_CONTACT);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Ruffle whom [how]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only ruffle one target's hair at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You ruffle", oblist, "'s hair" + how[1] + ".");
        all2act(" ruffles", oblist, "'s hair" + how[1] + ".", how[1],
            ACTION_CONTACT);
        target(" ruffles your hair" + how[1] + ".", oblist, how[1],
            ACTION_CONTACT);
        return 1;
    }

    actor("You reach down and ruffle", oblist, "'s hair" + how[1]
      + " with one of your enormous fingers.");
    all2act(" reaches down and ruffles", oblist, "'s hair" + how[1]
      + " with one of " + this_player()->query_possessive()
      + " enormous fingers.", how[1], ACTION_CONTACT);
    target(" reaches down and ruffles your hair" + how[1]
      + " with one of " + this_player()->query_possessive()
      + " enormous fingers.", oblist, how[1], ACTION_CONTACT);
    return 1;
} /* ruffle */


int
scowl(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "menacingly", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("scowling" + how[1]);
        write("You scowl" + how[1] + ".\n");
        allbb(" scowls" + how[1] + ".", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Scowl [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only scowl at one target at a time!\n");
        return 1;
    }

    SOULDESC("scowling" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You scowl" + how[1] + " at", oblist);
        all2actbb(" scowls" + how[1] + " at", oblist, 0, how[1]);
        targetbb(" scowls" + how[1] + " at you.", oblist, how[1]);
        return 1;
    }

    actor("You look down at", oblist, " and scowl" + how[1] + ".");
    all2actbb(" looks down at", oblist, " and scowls" + how[1] + ".",
        how[1]);
    targetbb(" looks down at you and scowls" + how[1] + ".",
        oblist, how[1]);
    return 1;
} /* scowl */


int
scratch(string str)
{
    object *oblist;
    string *zones;
    string *parts;
    string location;
    int    size;

    zones = ({ "head", "chin", "back", "behind", "nose", "ear" });

    str = (strlen(str) ? lower_case(str) : "head");
    if (member_array(str, zones) != -1)
    {
        write("You scratch your " + str + ".\n");
        allbb(" scratches " + this_player()->query_possessive() +
            " " + str + ".");
        return 1;
    }

    parts = explode(str, " ");
    if ((size = sizeof(parts)) > 1)
    {
        if (member_array(parts[size - 1], zones) != -1)
        {
            location = parts[size - 1];
            str = implode(parts[..(size - 2)], " ");
        }
    }

    if (!stringp(location))
    {
        location = "head";
    }

    oblist = parse_this(str, "[the] %l [at] [the]", ACTION_CONTACT);

    if (!sizeof(oblist))
    {
        notify_fail("Scratch [whom] [where]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only scratch one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You scratch", oblist, "'s " + location + ".");
        all2act(" scratches", oblist, "'s " + location + ".", "", ACTION_CONTACT);
        target(" scratches your " + location + ".", oblist, "", ACTION_CONTACT);
        return 1;
    }

    actor("You reach down and scratch", oblist, "'s " + location
      + " with one of your giant fingernails.");
    all2act(" reaches down and scratches", oblist, "'s " + location
      + " with one of " + this_player()->query_possessive()
      + " giant fingernails.", "", ACTION_CONTACT);
    target(" reaches down and scratches your " + location
      + " with one of " + this_player()->query_possessive()
      + " giant fingernails.", oblist, "", ACTION_CONTACT);
    return 1;
} /* scratch */


int
scream(string str)
{
    object *rooms, troom;
    int    index;
    int    size;

    if (stringp(str))
    {
        notify_fail("Scream what?\n");
        return 0;
    }

    if (!objectp(troom = environment(this_player())))
    {
        return 0;
    }

    rooms = FIND_NEIGHBOURS(troom, 3);

    index = -1;
    size = sizeof(rooms);
    while(++index < size)
    {
        tell_room(rooms[index], "@@shout_name:" + CMD_LIVE_SPEECH +
            "@@ shakes the area with a loud scream!\n", this_player());
    }

    all(" screams so loudly that it shakes the entire area!"
      + " ARRGGGGGGHHHHHH!!!!");
    write("ARRGGGGGGHHHHHH!!!! You shake the entire area with your"
      + " mighty scream!\n");
    return 1;
} /* scream */


int
shake(string str)
{
    object *oblist;
    int attrs = ACTION_VISUAL | ACTION_LACTIVITY;

    if (!stringp(str))
    {
        write("You shake your head in disagreement.\n");
        allbb(" shakes " + this_player()->query_possessive() +
              " head in disagreement.", attrs);
        return 1;
    }

    if (wildmatch("head *", str))
    {
        oblist = parse_this(str, "[head] [at] [the] %i", attrs);

        if (!sizeof(oblist))
        {
            notify_fail("Shake your head in disagreement at whom/what?\n");
            return 0;
        }

        if (sizeof(oblist) > 1)
        {
            write("You can only shake your head at one target at a"
              + " time!\n");
            return 1;
        }

        if (IS_OGRE(oblist[0]))
        {
            actor("You shake your head in disagreement at", oblist);
            all2act(" shakes " + this_player()->query_possessive() +
                " head in disagreement at", oblist, "", "", attrs);
            target(" shakes " + this_player()->query_possessive() +
                " head in disagreement at you.", oblist, "", attrs);
            return 1;
        }

        actor("You look down at", oblist, " and shake your head in"
          + " disagreement.");
        all2act(" looks down at", oblist, " and shakes "
          + this_player()->query_possessive() + " head in disagreement.",
            "", attrs);
        target(" looks down at you and shakes "
          + this_player()->query_possessive() + " head in disagreement.",
            oblist, "", attrs);
        return 1;
    }

    oblist = parse_this(str, "[hand] [hands] [with] [the] %l", attrs);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Shake hands with whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only shake hands with one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]))
    {
        actor("You shake hands with", oblist);
        all2act(" shakes", oblist, "'s hand.", "", attrs);
        target(" shakes your hand.", oblist, "", attrs);
        return 1;
    }

    actor("You reach down to shake hands with", oblist, ", but in"
      + " doing so clasp " + oblist[0]->query_possessive()
      + " entire forearm in your huge palm.");
    all2act(" reaches down to shake hands with", oblist, ", but in"
      + " doing so clasps " + oblist[0]->query_possessive()
      + " entire forearm in " + this_player()->query_possessive()
      + " huge palm.", "", attrs);
    target(" reaches down to shake hands with you, but in doing so"
      + " clasps your entire forearm in "
      + this_player()->query_possessive() + " huge palm.", oblist,
        "", attrs);
    return 1;
} /* shake */


int
shrug(string str)
{
    str = check_adverb_with_space(str, "helplessly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Shrug how?\n");
        return 0;
    }

    write("You shrug your gigantic shoulders" + str + ".\n");
    allbb(" shrugs " + this_player()->query_possessive()
      + " massive shoulders" + str + ".", str,
        ACTION_VISUAL | ACTION_LACTIVITY);
    return 1;
} /* shrug */


int
sigh(string str)
{
    str = check_adverb_with_space(str, "deeply");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Sigh how?\n");
        return 0;
    }

    SOULDESC("sighing" + str);
    write("You sigh" + str + ", the gust from your exhale buffeting"
      + " the surrounding area.\n");
    all(" sighs" + str + ", the gust from "
      + this_player()->query_possessive() + " exhale buffeting the"
      + " surrounding area.", str, ACTION_AURAL);
    return 1;
} /* sigh */


int
sing(string str)
{
    if (stringp(str))
    {
        notify_fail("Sing what?\n");
        return 0;
    }

    write("You sing a completely dreadful tune!\n");
    all(" tries to sing, but it sounds more like the world's most"
      + " bloated elephant seal summoning a mate!", "", ACTION_AURAL);
    return 1;
} /* sing */


int
slap(string str)
{
    object *oblist;
    int attrs = ACTION_CONTACT | ACTION_VISUAL | ACTION_AURAL |
        ACTION_MACTIVITY | ACTION_OFFENSIVE;

    oblist = parse_this(str, "[the] %i", attrs, 1);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Slap whom/what?\n");
        return 0;
    }

    if (oblist[0] == this_player())
    {
        write("You slap yourself.\n");
        all(" slaps " + this_player()->query_objective() + "self.", "", attrs);
        return 1;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only slap one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You slap", oblist);
        all2act(" slaps", oblist, "", attrs);
        target(" slaps you!", oblist, "", attrs);
        return 1;
    }

    actor("You slap", oblist, ", your giant palm connecting with "
      + oblist[0]->query_possessive() + " entire upper-torso to send "
      + oblist[0]->query_objective() + " sprawling to the ground.");
    all2act(" slaps", oblist, ", " + this_player()->query_possessive()
      + " giant palm connecting with chest, shoulders, and head to"
      + " send the latter sprawling to the ground.", "", attrs);
    target(" slaps you, " + this_player()->query_possessive()
      + " giant palm connecting with your entire upper-torso to send"
      + " you sprawling to the ground!", oblist, "", attrs);
    return 1;
} /* slap */


int
smile(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "stupidly", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("smiling" + how[1]);
        write("You smile" + how[1] + ".\n");
        allbb(" smiles" + how[1] + ".", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Smile [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only smile at one target at a time!\n");
        return 1;
    }

    SOULDESC("smiling" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You smile" + how[1] + " at", oblist);
        all2actbb(" smiles" + how[1] + " at", oblist, 0, how[1]);
        targetbb(" smiles" + how[1] + " at you.", oblist, how[1]);
        return 1;
    }

    actor("You look down at", oblist, " and smile" + how[1] + ".");
    all2actbb(" looks down at", oblist, " and smiles" + how[1] + ".",
        how[1]);
    targetbb(" looks down at you and smiles" + how[1] + ".", oblist,
        how[1]);
    return 1;
} /* smile */


int
smirk(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, BLANK_ADVERB, 0);

    if (!stringp(how[0]))
    {
        SOULDESC("smirking" + how[1]);
        write("You smirk" + how[1] + ".\n");
        all(" smirks" + how[1] + ".", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Smirk [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only smirk at one target at a time!\n");
        return 1;
    }

    SOULDESC("smirking" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You smirk" + how[1] + " at", oblist, ".");
        all2act(" smirks" + how[1] + " at", oblist, 0, how[1]);
        target(" smirks" + how[1] + " at you.", oblist, how[1]);
        return 1;
    }

    actor("You look down at", oblist, " and smirk" + how[1] + ".");
    all2act(" looks down at", oblist, " and smirks" + how[1] + ".",
        how[1]);
    target(" looks down at you and smirks" + how[1] + ".", oblist,
        how[1]);
    return 1;
} /* smirk */


int
snap(string str)
{
    if (stringp(str))
    {
        notify_fail("Snap what?\n");
        return 0;
    }

    write("You snap your enormous fingers.\n");
    all(" snaps " + this_player()->query_possessive() + " enormous"
      + " fingers.");
    return 1;
} /* snap */


int
snarl(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "savagely", 0);

    oblist = parse_this(how[0], "[at] [the] %i", ACTION_AURAL);

    if (!sizeof(oblist))
    {
        notify_fail("Snarl [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only smirk at one target at a time!\n");
        return 1;
    }

    SOULDESC("snarling" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You snarl" + how[1] + " at", oblist);
        all2act(" snarls" + how[1] + " at", oblist, 0, how[1],
            ACTION_AURAL);
        target(" snarls" + how[1] + " at you.", oblist, how[1],
            ACTION_AURAL);
        return 1;
    }

    actor("You look down at", oblist, " and snarl" + how[1] + ".");
    all2act(" looks down at", oblist, " and snarls" + how[1] + ".",
        how[1], ACTION_AURAL);
    target(" looks down at you and snarls" + how[1] + ".", oblist,
        how[1], ACTION_AURAL);
    return 1;
} /* snarl */


int
sneer(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "contemptuously", 0);

    if (!strlen(how[0]))
    {
        SOULDESC("sneering" + how[1]);
        write("You sneer" + how[1] + ".\n");
        allbb(" sneers" + how[1] + ".", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Sneer [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only sneer at one target at a time!\n");
        return 1;
    }

    SOULDESC("sneering" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You sneer" + how[1] + " at", oblist,".");
        all2actbb(" sneers" + how[1] + " at", oblist, 0, how[1]);
        targetbb(" sneers" + how[1] + " at you.", oblist, how[1]);
        return 1;
    }

    actor("You look down at", oblist, " and sneer" + how[1] + ".");
    all2actbb(" looks down at", oblist, " and sneers" + how[1] + ".",
        how[1]);
    targetbb(" looks down at you and sneers" + how[1] + ".", oblist,
        how[1]);
    return 1;
} /* sneer */


int
sneeze(string str)
{
    if (stringp(str))
    {
        notify_fail("Sneeze what?\n");
        return 0;
    }

    write("You sneeze, shaking the entire area with the blast!\n");
    all(" sneezes, shaking the entire area with the blast!", "",
        ACTION_AURAL | ACTION_VISUAL);
    return 1;
} /* sneeze */


int
snore(string str)
{
    string  noise;

    str = check_adverb_with_space(str, "loudly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Snore how?\n");
        return 0;
    }

    noise = "It sounds like a sheet of metal being drug across a"
      + " gravel pit!";

    SOULDESC("snoring" + str);
    write("You snore EXTREMELY" + str + ". Zzzzzzzzzz ...\n"
      + noise + "\n");
    all(" snores EXTREMELY" + str + ". " + noise, str, ACTION_AURAL);
    return 1;
} /* snore */


int
snuggle(string str)
{
    object *oblist;
    int attrs = ACTION_CONTACT | ACTION_INTIMATE | ACTION_LACTIVITY;

    oblist = parse_this(str, "[with] / [up] [to] [the] %i", attrs);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Snuggle up to whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only snuggle with one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You snuggle up to", oblist);
        all2act(" snuggles up to", oblist, "", attrs);
        target(" snuggles up to you.", oblist, "", attrs);
        return 1;
    }

    actor("You snuggle up to", oblist, ", kneeling beside "
      + oblist[0]->query_objective() + " and"
      + " rubbing your huge cheek against "
      + oblist[0]->query_possessive() + " shoulders.");
    all2act(" snuggles up to", oblist, ", kneeling beside "
      + oblist[0]->query_objective() + " and rubbing "
      + this_player()->query_possessive() + " huge cheek against"
      + " the latter's shoulder.", "", attrs);
    target(" snuggles up to you, kneeling down to rub "
      + this_player()->query_possessive() + " huge cheek"
      + " against your shoulder.", oblist, "", attrs);
    return 1;
} /* snuggle */


int
sob(string str)
{
    str = check_adverb_with_space(str, "sadly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Sob how?\n");
        return 0;
    }

    SOULDESC("sobbing" + str);
    write("You sob" + str + ", raining huge tears down on the area.\n");
    all(" sobs" + str + ", raining huge tears down on the area.",
        str, ACTION_VISUAL | ACTION_AURAL);
    return 1;
} /* sob */


int
spank(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "playfully", 1);

    oblist = parse_this(how[0], "[the] %i", ACTION_CONTACT);

    if (!sizeof(oblist))
    {
        notify_fail("Spank whom/what [how]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only spank one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You spank", oblist, how[1] + ".");
        all2act(" spanks", oblist, how[1] + ".", how[1],
            ACTION_CONTACT);
        target(" spanks you" + how[1] + ".", oblist, how[1], 
            ACTION_CONTACT);
        return 1;
    }

    actor("You spank", oblist, how[1] + ", accidentally sending "
      + oblist[0]->query_objective() + " tumbling head over heels.");
    all2act(" spanks", oblist, how[1] + ", accidentally sending"
      + " the latter tumbling head over heels.", how[1], ACTION_CONTACT);
    target(" spanks you" + how[1] + ", accidentally sending you"
      + " tumbling head over heels!", oblist, how[1], ACTION_CONTACT);
    return 1;
} /* spank */


int
spit(string str)
{
    object *oblist;
    int attrs;

    if (!stringp(str))
    {
        write("You spit on the ground in disgust. Of course, now,"
          + " thanks to you, the ground is the only thing that is"
          + " truly disgusting.\n");
        all(" spits on the ground in disgust. Of course, now, thanks"
          + " to " + this_player()->query_objective() + ", the ground"
          + " is the only thing that is truly disgusting.", ACTION_OTHER);
        return 1;
    }

    attrs = ACTION_PROXIMATE | ACTION_OFFENSIVE | ACTION_VISUAL;

    oblist = parse_this(str, "[on] [the] %i", attrs);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Spit at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only spit on one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You spit on", oblist);
        all2act(" spits on", oblist, "", attrs);
        target(" spits on you!", oblist, "", attrs);
        return 1;
    }

    actor("You spit on", oblist, " who, to "
      + oblist[0]->query_possessive() + " horror, is now completely"
      + " covered in your obnoxious saliva!");
    all2act(" spits on", oblist, " who, to the latter's horror, is"
      + " now completely covered in obnoxious saliva!", "", attrs);
    target(" spits on you, completely covering you in "
      + this_player()->query_possessive() + " obnoxious saliva!",
        oblist, "", attrs);
    return 1;
} /* spit */


int
squeeze(string str)
{
    object *oblist;
    string *how;
    int attrs = ACTION_CONTACT | ACTION_MACTIVITY | ACTION_VISUAL;

    how = parse_adverb_with_space(str, "fondly", 1);

    oblist = parse_this(how[0], "[the] %i", attrs);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Squeeze whom/what [how]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only squeeze one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You squeeze", oblist, how[1] + ".");
        all2act(" squeezes", oblist, how[1] + ".", how[1], attrs);
        target(" squeezes you" + how[1] + ".", oblist, attrs);
        return 1;
    }

    actor("You squeeze", oblist, how[1] + ", quickly stopping as"
      + " you think you notice a few of "
      + oblist[0]->query_possessive() + " ribs creaking painfully.");
    all2act(" squeezes", oblist, how[1] + ", quickly stopping as"
      + " soon as a few of the latter's ribs begin to creak"
      + " painfully.", how[1], attrs);
    target(" squeezes you" + how[1] + ", quickly stopping as soon"
      + " as " + this_player()->query_pronoun() + " hears a few of"
      + " your ribs begin to creak painfully.", oblist, attrs);
    return 1;
} /* squeeze */


int
stare(string str)
{
    object *oblist;
    string *how;

    if (!stringp(str))
    {
        SOULDESC("staring into space");
        write("You stare into space.\n");
        allbb(" stares into space.");
        return 1;
    }

    how = parse_adverb_with_space(str, "dreamily", 0);

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Stare at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only stare at one target at a time!\n");
        return 1;
    }

    SOULDESC("staring" + how[1]);

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You stare" + how[1] + " at", oblist);
        all2actbb(" stares" + how[1] + " at", oblist, 0, how[1]);
        targetbb(" stares" + how[1]+ " into your eyes.", oblist, how[1]);
        return 1;
    }

    actor("You stare" + how[1] + " down at", oblist);
    all2actbb(" stares" + how[1] + " down at", oblist, 0, how[1]);
    targetbb(" stares" + how[1]+ " down into your eyes.", oblist,
        how[1]);
    return 1;
} /* stare */


int
startle(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Startle whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only startle at one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You startle", oblist);
        all2act(" startles", oblist);
        target(" startles you.", oblist);
        return 1;
    }

    actor("You startle", oblist, " badly! Hee hee hee!");
    all2act(" startles", oblist, " rather badly! Ogres should know"
      + " better than to do that sort of thing.");
    target(" startles you badly! WHOA!! Ogres should know better than"
      + " to do that sort of thing, the big meanies.", oblist);
    return 1;
} /* startle */


int
stomp(string str)
{
    if (stringp(str))
    {
        notify_fail("Stomp what?\n");
        return 0;
    }

    write("You stomp your enormous feet angrily, causing everything"
      + " in the area to bounce a few inches off the ground.\n");
    all(" stomps " + this_player()->query_possessive() + " enormous feet"
      + " angrily, causing everything in the area to bounce a few inches"
      + " off the ground.", 
        ACTION_MACTIVITY | ACTION_VISUAL | ACTION_AURAL);
    return 1;
} /* stomp */


int
strut(string str)
{
    str = check_adverb_with_space(str, "proudly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Strut how?\n");
        return 0;
    }

    write("You strut your big ogre stuff" + str + ", shaking"
      + " everything in the area with each stomp!\n");
    all(" struts" + str + ", shaking everything in the area with"
      + " each stomp.", str, ACTION_MACTIVITY);
    return 1;
} /* strut */


int
stumble(string str)
{
    if (stringp(str))
    {
        notify_fail("Just stumbling will suffice.\n");
        return 0;
    }

    write("CRASH!!! You stumble and fall to the ground, which shakes"
      + " violently.\n");
    all(" stumbles and falls to the ground, which shakes violently!");
    return 1;
} /* stumble */


int
swoon(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "wistfully", 0);
    if (!stringp(how[0]))
    {
        write("You swoon" + how[1] + " and pass out momentarily as you " +
            "collapse to the ground with a great crash.\n");
        all(" swoons" + how[1] + " and passes out momentarily as " +
            this_player()->query_pronoun() + " collapses to the ground"
          + " with a great crash.", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[over] [the] %l", ACTION_CONTACT );
    if (!sizeof(oblist))
    {
        notify_fail("Swoon [how] [over whom]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only swoon over one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You swoon" + how[1] + " and pass out momentarily into"
          + " the arms of", oblist, ".");
        all2act(" swoons" + how[1] + " and passes out momentarily into"
          + " the arms of", oblist, 0, how[1], ACTION_CONTACT);
        target(" swoons" + how[1] + " and passes out momentarily into"
          + " your arms.", oblist, how[1], ACTION_CONTACT);
        return 1;
    }

    actor("You swoon" + how[1] + " and pass out momentarily into the"
      + " unsuspecting arms of", oblist, ", who, overwhelmed by your"
      + " massive bulk, collapses beneath you.");
    all2act(" swoons" + how[1] + " and passes out momentarily into"
      + " the unsuspecting arms of", oblist, ", who, overwhelmed by"
      + " such massive bulk, collapses beneath "
      + this_player()->query_objective() + ".", how[1], ACTION_CONTACT);
    target(" swoons" + how[1] + " and passes out momentarily into"
      + " your unsuspecting arms. Of course, you can't even begin to"
      + " support the weight of an ogre, and immediately collapse"
      + " beneath " + this_player()->query_possessive() + " massive"
      + " bulk.", oblist, how[1], ACTION_CONTACT);
    return 1;
} /* swoon */


int
tackle(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l", ACTION_CONTACT | ACTION_HACTIVITY);
    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Tackle whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only tackle one target at a time!\n");
        return 1;
    }

    if (random(7))
    {
        if (IS_OGRE(oblist[0]) || !living(oblist[0]))
        {
            actor("You tackle", oblist);
            all2act(" tackles", oblist, ". " +
                ((sizeof(oblist) > 1) ? "They fall": "The latter falls") +
                " to the ground in a very unflattering way.", "",
                ACTION_CONTACT | ACTION_HACTIVITY);
            target(" comes running at you. " +
                capitalize(this_player()->query_pronoun()) +
                " attempts to tackle you and succeeds. You fall to the ground " +
                "in a very unflattering way.", oblist, "",
                ACTION_CONTACT | ACTION_HACTIVITY);
            return 1;
        }

        actor("You tackle", oblist, ", completely burying "
          + oblist[0]->query_objective() + " beneath"
          + " your massive bulk.");
        all2act(" tackles", oblist, ", completely burying "
          + oblist[0]->query_objective() + " beneath "
          + this_player()->query_possessive() + " massive"
          + " bulk.", "", ACTION_CONTACT | ACTION_HACTIVITY);
        target(" tackles you, driving you to the ground to bury you"
          + " beneath " + this_player()->query_possessive()
          + " massive bulk!", oblist, "",
            ACTION_CONTACT | ACTION_HACTIVITY);
    }
    else
    {
        actor("You try to tackle", oblist, " but fall flat on your"
          + " face with an earth-shaking crash.");
        all2act(" tries to tackle", oblist, " but misses and falls flat on " +
            this_player()->query_possessive() + " face with an earth-"
          + "shaking crash.", "",
            ACTION_CONTACT | ACTION_HACTIVITY);
        target(" comes running at you. " +
            capitalize(this_player()->query_pronoun()) +
            " attempts to tackle you but misses and falls flat on " +
            this_player()->query_possessive() + " face with an earth-"
          + "shaking crash.", oblist, "",
            ACTION_CONTACT | ACTION_HACTIVITY);
    }

    return 1;
} /* tackle */


int
tap(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 0);

    if (!stringp(how[0]))
    {
        if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
        {
            how[1] = ADD_SPACE_TO_ADVERB("impatiently");
        }

        write("You tap your foot" + how[1] + ", causing everything"
          + " in the area to bounce off the ground a bit.\n");
        all(" taps " + this_player()->query_possessive() + " foot"
          + how[1] + ", causing everything in the area to bounce"
          + " off the ground a bit.", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[on] [the] %l", ACTION_CONTACT);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Tap [whom] [how]?\n");
        return 0;
    }

    if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
    {
        how[1] = NO_ADVERB;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only tap one target at a time!\n");
        return 1;
    }

    this_player()->reveal_me(1);
    str = ((sizeof(oblist) == 1) ? oblist[0]->query_possessive() :
       "their");

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You tap", oblist, how[1] + " on the shoulder to attract "
          + str + " attention.");
        all2act(" taps", oblist, how[1] + " on the shoulder to attract "
          + str + " attention.", how[1], ACTION_CONTACT);
        target(" taps you" + how[1] +
            " on the shoulder to attract your attention.", oblist, how[1],
            ACTION_CONTACT);
        oblist->reveal_me(1);
        return 1;
    }

    actor("You tap", oblist, how[1] + " on the shoulder to attract "
      + str + " attention, your huge fingertip nearly causing "
      + oblist[0]->query_objective() + " to lose " + str + " balance.");
    all2act(" taps", oblist, how[1] + " on the shoulder to attract "
      + str + " attention, the huge fingertip also nearly causing "
      + oblist[0]->query_objective() + " to lose " + str + " balance.",
        how[1], ACTION_CONTACT);
    target(" taps you" + how[1] +
        " on the shoulder to attract your attention, "
      + this_player()->query_possessive() + " giant fingertip nearly"
      + " causing you to lose your balance.", oblist, how[1],
        ACTION_CONTACT);
    oblist->reveal_me(1);

    return 1;
} /* tap */


public int
touch(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %i", ACTION_CONTACT | ACTION_LACTIVITY);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Touch whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only touch one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]) || !living(oblist[0]))
    {
        actor("You touch", oblist, ".");
        all2act(" touches", oblist, ".", 0,
            ACTION_CONTACT | ACTION_LACTIVITY);
        target(" touches you.", oblist, 0,
            ACTION_CONTACT | ACTION_LACTIVITY);
        return 1;
    }

    actor("You reach down and touch", oblist, ".");
    all2act(" reaches down and touches", oblist, ".", 0,
        ACTION_CONTACT | ACTION_LACTIVITY);
    target(" reaches down and touches you.", oblist, 0, 
        ACTION_CONTACT | ACTION_LACTIVITY);
    return 1;
} /* touch */


int
wave(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "stupidly", 0);

    if (!stringp(how[0]))
    {
        write("You wave" + how[1] + ".\n");
        allbb(" waves" + how[1] + ".", how[1],
            ACTION_VISUAL | ACTION_LACTIVITY);
        return 1;
    }

    /* I am not sure whether you wave to or at someone, so I'll allow
     * both. If you know how it should be, let us know ;-)
     */
    oblist = parse_this(how[0], "[to] / [at] [the] %i",
        ACTION_VISUAL | ACTION_LACTIVITY);

    if (!sizeof(oblist))
    {
        notify_fail("Wave [how] to whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only wave to one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]))
    {
        actor("You wave" + how[1] + " in", oblist, "'s direction.");
        all2actbb(" waves" + how[1] + " in", oblist, "'s direction.", how[1],
            ACTION_VISUAL | ACTION_LACTIVITY);
        targetbb(" waves" + how[1] + " in your direction.", oblist, how[1],
            ACTION_VISUAL | ACTION_LACTIVITY);
        return 1;
    }

    actor("You look down at", oblist, " and wave" + how[1] + " in "
      + oblist[0]->query_possessive() + " direction.");
    all2actbb(" looks down at", oblist, " and waves" + how[1] + " in "
      + oblist[0]->query_possessive() + " direction.", how[1],
        ACTION_VISUAL | ACTION_LACTIVITY);
    targetbb(" looks down at you and waves" + how[1] + " in your"
      + " direction.", oblist, how[1],
        ACTION_VISUAL | ACTION_LACTIVITY);
    return 1;
} /* wave */


int
weep(string str)
{
    str = check_adverb_with_space(str, "bitterly");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Weep how?\n");
        return 0;
    }

    SOULDESC("weeping" + str);
    write("You weep" + str + ", sending huge tears splashing down"
      + " all over the place.\n");
    all(" weeps" + str + ", sending huge tears splashing down all"
      + " over the place.", str, ACTION_AURAL | ACTION_VISUAL);
    return 1;
} /* weep */


int
wiggle(string str)
{
    str = check_adverb_with_space(str, BLANK_ADVERB);

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Wiggle how?\n");
        return 0;
    }

    write("You wiggle your massive bottom" + str + ".\n");
    allbb(" wiggles " + this_player()->query_possessive() +
          " massive bottom" + str + ". By the Gods ... what a terrible"
        + " and disgraceful sight!", str, ACTION_MACTIVITY);
    return 1;
} /* wiggle */


int
wink(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "suggestively", 0);

    if (!stringp(how[0]))
    {
        write("You wink" + how[1] + ".\n");
        allbb(" winks" + how[1] + ".", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Wink [how] at whom/what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only wink at one target at a time!\n");
        return 1;
    }

    if (IS_OGRE(oblist[0]))
    {
        actor("You wink" + how[1] + " at", oblist);
        all2actbb(" winks" + how[1] + " at", oblist, 0, how[1]);
        targetbb(" winks" + how[1] + " at you.", oblist, how[1]);
        return 1;
    }

    actor("You look down at", oblist, " and wink" + how[1] + ".");
    all2actbb(" looks down at", oblist, " and winks" + how[1] + ".",
        how[1]);
    targetbb(" looks down at you and winks" + how[1] + ".",
        oblist, how[1]);
    return 1;
} /* wink */


int
yodel(string str)
{
    if (stringp(str))
    {
        notify_fail("Yodel what?\n");
        return 0;
    }

    write("YODELEII ... YODELEIIUUGGHH ... AAAUGHHAUAHHHGH!!!! Hmmm ..."
      + " it seems Ogres just weren't meant to yodel.\n");
    all(" begins trying to yodel. It sounds like someone is strangling"
      + " a frightened yak!", "", ACTION_AURAL);
    SOULDESC("(apparently) yodeling");
    return 1;
} /* yodel */


/***********************************************************************
 *  Functions below are taken mostly from /cmd/live/speech.c           *
 *  and modified to give a few Ogre-specific features. Ogres           *
 *  always speak in all-caps, cannot whisper without being overheard,  *
 *  are heard 2 rooms away when shouting, and cannot rsay.             *
 ***********************************************************************/


/*
 * Function name:        rsay
 * Description  :        Ogres have no racial language. So we just stop
 *                       that right here.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 (always)
 */
public int
rsay(string arg)
{
    write("Ogres are typically too stupid to speak and thus have no"
      + " racial language of their own.\n");
    return 1;
} /* rsay */


/*
 * Function name: say_to
 * Description  : This function is called whenever the player starts his
 *                say-string with 'to'. This usually indicates that the
 *                player wants to say something to some people in particular.
 *                All others will still hear it though.
 * Arguments    : string str - the text to say (not including 'to').
 *                string adverb - the adverb to use.
 * Returns      : int 1/0 - success/failure.
 *
 * I've brought this in from the mudlib to enable me to manipulate the
 * way Ogres speak.
 */
public int
say_to(string str, function format)
{
    return CMD_LIVE_SPEECH->say_to(upper_case(str), format);
} /* say_to */


/*
 * Function name:        say_text
 * Description  :        this is a mask copied almost entirely from the
 *                       mudlib. I want ogres to talk in all caps while
 *                       retaining the normal functionality.
 */
varargs int
say_text(string str, string adverb = "")
{
    return CMD_LIVE_SPEECH->say_text(upper_case(str), adverb);
} /* say_text */


/*
 * Function name:        asay
 * Description  :        pulled from the mudlib to control ogre speech
 */
int
asay(string str)
{
    return CMD_LIVE_SPEECH->asay(upper_case(str));
} /* asay */


/* **************************************************************************
 * Ask - Ask someone something.
 */
int
ask(string str)
{
    return CMD_LIVE_SPEECH->ask(upper_case(str));
} /* ask */


/*
 * Function name: shout_name
 * Description  : Called through VBFC to find the name/description of the
 *                person who does the shouting.
 * Returns      : string - the name/description of the living.
 */
string
shout_name()
{
    object pobj = previous_object(); /* Reciever of message */
    if (file_name(pobj) == VBFC_OBJECT)
    {
        pobj = previous_object(-1);
    }
    if (pobj->query_met(this_player()))
    {
        return this_player()->query_name();
    }
    return capitalize(LANG_ADDART(this_player()->query_gender_string())) +
        " " + this_player()->query_race_name() + " voice";
} /* shout_name */


int
shout(string str)
{
    object *rooms;
    object troom;
    object *oblist;
    string *how;
    string cap_str;
    mixed  tmp;
    int    use_target = 0;
    int    index;
    int    size;
    string preposition;

    if (!strlen(str))
    {
        notify_fail("Shout what?\n", 0);
        return 0;
    }

    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(tmp) ? tmp : "You are gagged and cannot shout.\n");
        return 1;
    }
 
    if ((strlen(str) > 60) &&
        (!this_player()->query_wiz_level()) &&
        (!this_player()->query_npc()))
    {
        notify_fail("Even your mouth is not big enough to shout all that.\n");
        return 0;
    }

    /* Note that [at][to] in a beautiful way tests both 'at' and 'to', while
     * wildmatch normally tests per letter, and not per word! */   
    if (wildmatch("[at][to] *", str))
    {
        preposition = extract(str, 0, 1);
        /* Shout at all people. */
        /* We already tested for at/to, so no repeat check necessary. */
        if (wildmatch("?? all *", str))
        {
            str = extract(str, 7);
            oblist =
                FILTER_OTHER_LIVE(all_inventory(environment(this_player())));
        }
        /* Shout to my team. */
        else if (wildmatch("?? team *", str))
        {
            str = extract(str, 8);
            oblist = this_player()->query_team_others() &
                all_inventory(environment(this_player()));
        }
        /* Find out who we shout to. */
        else if (parse_command(lower_case(cap_str = str),
            environment(this_player()), "[at] [to] [the] %i %s", oblist, str))
        {
            str = extract(cap_str, -(strlen(str)));
            oblist = NORMAL_ACCESS(oblist, 0, 0) - ({ this_player() });
        }
    }

    if (pointerp(oblist) && !sizeof(oblist))
    {
        notify_fail("Shout [what] at/to whom?\n");
        return 0;
    }

    how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 0);
    if (strlen(how[0]) &&
        how[1] != NO_DEFAULT_ADVERB_WITH_SPACE)
    {
        str = how[0];
    }
    else
    {
        how[1] = NO_ADVERB;
    }

    /* Sanity check. */
    if (!(troom = environment(this_player())))
    {
        return 0;
    }

    /* For shouting, we don't want to find our own room. Also, lets make
     * it so that ogre shouts travel 2 rooms instead of just one. */
    rooms = FIND_NEIGHBOURS(troom, 2);

    str = upper_case(str);
    index = -1;
    size = sizeof(rooms);
    while(++index < size)
    {
        tell_room(rooms[index], "@@shout_name:" + file_name(this_object()) +
            "@@" + how[1] + " shouts: " + str + "\n", this_player());
    }

    if (sizeof(oblist))
    {
        if (this_player()->query_option(OPT_ECHO))
            actor("You" + how[1] + " shout "
              + preposition, oblist, ": " + str);
        else
            write("Ok.\n");
        all2act(how[1] + " shouts " + preposition, oblist, ": " + str);
        target(how[1] + " shouts " + preposition + " you: " + str, oblist);
    }
    else
    {
        all(how[1] + " shouts: " + str);
        if (this_player()->query_option(OPT_ECHO))
            write("You" + how[1] + " shout: " + str + "\n");
        else
            write("Ok.\n");
    }

    return 1;
} /* shout */


/* **************************************************************************
 * Whisper - whisper something to someone.
 */
void
print_whisper_to(string adverb, object *oblist, string str)
{
    object  *folks;

    str = upper_case(str);

    if (this_player()->query_option(OPT_ECHO))
        actor("You whisper" + adverb + " to", oblist, ": " + str);
    else
        write("Ok.\n");
    all2act(" whispers something to", oblist);
    
    /* Ogres just aren't any good at whispering, it seems. */
    folks = FILTER_PLAYERS(all_inventory(environment(this_player()))) -
        oblist - ({ this_player() });
    folks->catch_tell("Of course, since " + this_player()->query_pronoun()
      + " is an ogre, you hear " + this_player()->query_possessive()
      + " voice hoarsly boom: " + str + "\n");

    target(" cups " + this_player()->query_possessive() + " massive hand"
      + " and booms" + adverb + " in your ear: " + str, oblist);
    oblist->catch_whisper(str);   

    /* Onlookers don't get what was being whispered. */
    folks->speech_hook("whisper", this_player(), adverb, oblist, "", -1);
    oblist->speech_hook("whisper", this_player(), adverb, oblist, str, 1);
} /* print_whisper */


int
whisper(string str)
{
    mixed tmp;
    string *how;

    if (!stringp(str))
    {
        notify_fail("Whisper [to] <whom> <what>?\n");
        return 0;
    }

    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(tmp) ? tmp : "You are gagged and cannot whisper.\n");
        return 1;
    }
    
    how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 0);
    if (strlen(how[0]) && how[1] != NO_DEFAULT_ADVERB_WITH_SPACE)
    {
        str = how[0];
    }
    else
    {
        how[1] = NO_ADVERB;
    }

    if (strlen(str))
    {
        if (wildmatch("to *", str))
            str = extract(str, 3);
        
        if (say_to(str, &print_whisper_to(how[1])))
        {
            return 1;
        }
    }
    
    notify_fail("Whisper [to] <whom> <what>?\n");
    return 0;
} /* whisper */
