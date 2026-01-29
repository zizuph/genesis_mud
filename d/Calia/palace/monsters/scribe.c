// NPC: Scribe of Calia

    /* Calia Domain

    HISTORY

    [97-01-06] Created by Uhclem from [D:\CALIA\GLYKRON\SCRIBE.DOC].

    PURPOSE

    Shimram and Mezzlebeb are partners; only one is needed in the scribes'
    office at any one time.  The scribe of the day answers questions about the
    Chronicles.  The scribe does not chat!  He or she only responds when asked
    questions so as not to interfere with players who want to read. */

// INCLUSIONS AND DEFINITIONS

#pragma save_binary

inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>

// FUNCTIONS

// Function:  add_introduced

/*

Purpose:  let the character introduce himself to players who introduce
themselves.

Arguments:  none

Returns:  nothing

*/

void
add_introduced(string who)

    {

    set_alarm(1.0, 0.0, &command("introduce me to " + who));

    }

// NPC DEFINITION

void
create_monster()

    {

    /* DESCRIPTION */

    if (random(2))

        {

        set_living_name("shimram");
        set_name("shimram");
        add_name("scribe");
        set_race_name("human");
        set_gender(0);
        set_adj(({"squinty-eyed", "ink-stained"}));
        set_title("the Scribe of Calia and Curator of the Calian Chronicles");

        set_long("His face is wrinkled in a permanent squint from hours" +
            " he has spent poring over documents, and leaning over a" +
            " desk for most of his life has left him a bit" +
            " hunchbacked.  But he seems content and wise, both happy" +
            " and able to answer questions about his work.\n");

        add_ask(({"scribe", "scribes", "mezzlebeb", "partner"}),
            ("say " +
            "The Scribes of Calia are myself, Shimram, and" +
            " my esteemed partner, Mezzlebeb."), 1);

        }

    else

        {

        set_living_name("mezzlebeb");
        set_name("mezzlebeb");
        add_name("scribe");
        set_race_name("elf");
        set_gender(1);
        set_adj(({"white-haired", "round-faced"}));
        set_title("the Scribe of Calia and Curator of the Calian Chronicles");

        set_long("She looks like a contented worker, happy to" +
            " spend her hours among treasured books," +
            " scrolls, and parchments.  If you had any" +
            " questions, she looks like the type who" +
            " could supply the answers.\n");

        add_ask(({"scribe", "scribes", "mezzlebeb", "partner"}),
            ("say " +
            "The Scribes of Calia are myself, Mezzlebeb, and" +
            " my esteemed partner, Shimram."), 1);

        }

    /* PHYSICAL ATTRIBUTES */

    default_config_npc(30);  /* This is a writer, not a fighter. */
    set_hp(2000);
    set_skill(SS_UNARM_COMBAT, random(10) + 20);
    set_skill(SS_DEFENCE, random(10) + 20);
    set_skill(SS_AWARENESS, random(50) + 50);
    set_alignment(100 + random(100));

    /*  RESPONSES  */

    add_ask(("ancient times"),
        ("say " +
        "Yes, there was a time when it seems that war was unknown" +
        " in Calia, but that time ended about 350 years" +
        " BC.  That's 'Before Confederation.'"), 1);

    add_ask(("battles"),
        ("say " +
        "There are several battles recorded in the" +
        " chronicles.  You'll find them in volumes 6 and 13."), 1);

    add_ask(("calia"),
        ("say " +
        "We hope that people all over the world will come" +
        " to understand Calia through reading the Chronicles."), 1);

    add_ask(("commune"),
        ("say " +
        "If you long for death, commune Uhclem without" +
        " an urgent reason."), 1);

    add_ask(("control"),
        ("say " +
        "Many people vied for control of Calia, the most" +
        " terrible of these being Kroug, of course."), 1);

    add_ask(("cult"),
        ("say " +
        "Goodness, no!  I am not a member of any cult!"), 1);

    add_ask(("cults"),
        ("say " +
        "Cults were one of the unfortunate responses to the" +
        " strife that arose during the Dim Time.  It saddens me" +
        " to hear that some still exist."), 1);

    add_ask(("defeat"),
        ("say " +
        "Kroug's defeat was accomplished in the Great" +
        " Battle, which is described in Volume 13."), 1);

    add_ask(("desk"),
        ("say " +
        "Ordinarily we write on that desk, but we've spilled some ink" +
        " on it and we're waiting it to dry."), 1);

    add_ask(("early battles"),
        ("say " +
        "The earliest battle in which Caliana was involved was" +
        " during the time of her captivity; it's described in" +
        " volume 6 along with some other battles."), 1);

    add_ask(("events"),
        ("say " +
        "Most of the volumes record events in the history" +
        " of Calia, beginning with ancient times and ending" +
        " just after the Confederation, about twenty years ago."), 1);

    add_ask(("final"),
        ("say " +
        "The final volume was written by Caliana herself, and" +
        " it is not available here.  The text will be transcribed" +
        " and placed in the notebook."), 1);

    add_ask(("hucker"),
        ("say " +
        "He was a dwarf who once tried to conquer Gelan.  You'll" +
        " find him in Volume 8."), 1);

    add_ask(("journal"),
        ("say " +
        "Yes, Caliana kept of journal of her travels shortly" +
        " after her escape from Masthron.  It's contents are" +
        " in volume 7."), 1);

    add_ask(("mail"),
        ("say " +
        "Yes, if you have something to say about the Chronicles" +
        " and do not want to post it on the board, you should" +
        " send mail, not commune."), 1);

    add_ask(("minions"),
        ("say " +
        "Kroug's minions are mindless fanatics enslaved to" +
        " his evil purposes.  Even after his defeat they" +
        " still fight for him."), 1);

    add_ask(("organization"),
        ("say " +
        "The story of how Caliana organized the Guild is" +
        " told in Volume 12."), 1);

    add_ask(("outline"),
        ("say " +
        "Yes, the work is only in outline form now.  When we" +
        " have collected all the information we can, then we" +
        " will set out writing the final version."), 1);

    add_ask(("people"),
        ("say " +
        "There are so many people mentioned in the Chronicles," +
        " it is impossible for me to list them all.  The" +
        " two most important ones, Caliana and Kroug," +
        " have volumes dedicated entirely to their exploits."), 1);

    add_ask(("places"),
        ("say " +
        "The places mentioned in the Chronicles do not" +
        " represent the entire land of Calia.  Most of what" +
        " happens in the history occurs between Gelan and East" +
        " Calia; events in the far north and south are" +
        " generally little known to us."), 1);

    add_ask(("raw information"),
        ("say " +
        "Such information is useful for study, but it" +
        " is hardly entertaining reading."), 1);

    add_ask(("read"),
        ("say " +
        "Yes, you may read here.  The volumes on the table and the" +
        " notes on the board are considered public information."), 1);

    add_ask(("reading"),
        ("say " +
        "That's what this room is for."), 1);

    add_ask(("refill"),
        ("say " +
        "Don't concern yourself with the lamps - I'll take care of them."), 1);

    add_ask(("region"),
        ("say " +
        "The events in the Chronicles occur in coastal and" +
        " East Calia.  Very little is known of events in the" +
        " far north and south."), 1);

    add_ask(("story"),
        ("say " +
        "The story of Calia is the story of the guild, although" +
        " not all Calians see it that way."), 1);

    add_ask(("strife"),
        ("say " +
        "Yes, the land was burdened with constant strife for" +
        " over 300 years.  Only since the time of Caliana have" +
        " we had any significant measure of peace and freedom."), 1);

    add_ask(("trust"),
        ("say " +
        "A difficult subject, trust.  I don't think I can give" +
        " you any advice about that - you'll have to look at" +
        " the books and decide for yourself."), 1);

    add_ask(("understood"),
        ("say " +
        "After the Great Battle, many had high hopes that" +
        " the land would finally know peace, but even today this" +
        " has not been achieved."), 1);

    add_ask(("when"),
        ("say " +
        "I'm not sure what you mean by asking me 'when.' " +
        " Are you inquiring about the time when the" +
        " Chronicles will be completed?  Or perhaps you want to" +
        " know what span of time they cover?"), 1);

    add_ask(("where"),
        ("say " +
        "You puzzle me by asking about 'where.'  Are you asking" +
        " about where we are with regard to completion of" +
        " the Chronicles, or what region of Calia is covered" +
        " in Volume 1?"), 1);

    add_ask(("who"),
        ("say " +
        "Are you inquiring who are the scribes, or who may read" +
        " the books and post comments?"), 1);

    add_ask(("why"),
        ("say " +
        "It is our hope that, even in such a primitive form," +
        " these notes will provide valuable information to you. " +
        " We also trust that you will provide additional comments" +
        " so that we may incorporate them into the" +
        " final edition."), 1);

    add_ask(("work"),
        ("say " +
        "You see the work of the Scribes before you on the table" +
        " - the outline of the Calian Chronicles."), 1);

    add_ask(("write"),
        ("say " +
        "That's what we Scribes do - write.  Not everyone can" +
        " be a warrior."), 1);

    add_ask(("writing"),
        ("say " +
        "The writing has hardly begun.  These notebooks" +
        " contain only raw information, and some of it" +
        " is incomplete or incorrect.  When we have collected" +
        " all the good information we can, we will begin the" +
        " task of writing the story of Calia."), 1);

    add_ask(("writing"),
        ("say " +
        "The Chronicles are mostly history, but there" +
        " are volumes about geography and flora and fauna as well."), 1);

    add_ask(("youth"),
        ("say " +
        "Caliana's youth was spent in servitude to" +
        " the goblin warlord Masthron."), 1);

    add_ask(({"altar", "stone"}),
        ("say " +
        "We don't claim to understand what the altar is for, but" +
        " we have at least recorded its installation in the" +
        " palace.  Look in Volume 17."), 1);

    add_ask(({"annals", "annals of the guild", "volume 12", "Volume 12"}),
        ("say " +
        "Volume 12 is the first half of the Annals of the Guild. " +
        " It tells of the organization of the Warriors, early" +
        " battles, and the events leading up to the Great" +
        " Battle itself."), 1);

    add_ask(({"apotheosis", "volume 17", "Volume 17"}),
        ("say " +
        "Volume 17 is a strange tale.  We have recorded the" +
        " events as they were told to us, whether we understood" +
        " them or not."), 1);

    add_ask(({"argos", "kyrulian", "kyrulians", "elemental", "elementals"}),
        ("say " +
        "I'm afraid there's not much information about that" +
        " in the Chronicles.  You'll need to rely on other" +
        " sources."), 1);

    add_ask(({"battle", "great battle", "volume 13", "Volume 13"}),
        ("say " +
        "Volume 13 tells of the Great Battle, the defeat of" +
        " Kroug, and the terrible price that was paid."), 1);

    add_ask(({"board", "boards"}),
        ("say " +
        "The board in this room is for discussion of" +
        " the Chronicles.  When referring to a specific" +
        " point, it's always helpful to include the line" +
        " number in your note."), 1);

    add_ask(({"calian", "calians"}),
        ("say " +
        "Ahh, what is a Calian?  Is it enough simply to be a" +
        " resident of this land, or does it take something more? " +
        " That is a question each must answer for himself."), 1);

    add_ask(({"caliana", "volume 6", "Volume 6"}),
        ("say " +
        "Volume 6 tells the story of Caliana's youth."), 1);

    add_ask(({"change", "changes", "revise", "revision", "revisions"}),
        ("say " +
        "When all comments have been received, we will begin" +
        " the process of completing the Chronicles.  We expect" +
        " to receive a great number of comments, and many of" +
        " them will probably conflict, so we cannot guarantee that" +
        " all of them will be incorporated into the" +
        " final edition."), 1);

    add_ask(({"chronicle", "chronicles", "Chronicles",
        "Calian Chronicles", "calian chronicles"}),
        ("say " +
        "The Calian Chronicles are a compilation of people," +
        " places, and events in Calian history.  They cover" +
        " a period ranging from ancient times to a mere" +
        " twenty years ago."), 1);

    add_ask(({"comment", "comments"}),
        ("say " +
        "Any member of the Guild may make comments on this board" +
        " or in mail, whichever he, she, or it prefers."), 1);

    add_ask(({"complete", "completion", "completed", "finish", "finished"}),
        ("say " +
        "It's hard to tell when the Chronicles will be completed" +
        " and put on display.  Much depends on how" +
        " many corrections and additions the Guild members" +
        " provide, but I shouldn't think it would take more" +
        " than a few months."), 1);

    add_ask(({"confederation", "government", "congress", "volume 14",
        "Volume 14"}),
        ("say " +
        "Volume 14 is the story of the Calian" +
        " Confederation, established by the Congress of Gelan."), 1);

    add_ask(({"crystalline", "crystalline road", "crystal", "road"}),
        ("say " +
        "The crystalline road is first mentioned in Volume 12."), 1);

    add_ask(({"darkness", "sword of darkness", "darkness sword"}),
        ("say " +
        "The sword of darkness first appears in Volume 13."), 1);

    add_ask(({"dim time", "time", "dim", "volume 4", "Volume 4"}),
        ("say " +
        "Volume 4 describes what we commonly call the Dim Time," +
        " the era in which strife first swept across this" +
        " land.  During that time there were many" +
        " warlords - some insignificant, some powerful -" +
        " who vied for control."), 1);

    add_ask(({"east", "east calia", "East Calia"}),
        ("say " +
        "East Calia is a forbidding landscape of which only a" +
        " little is known.  If Caliana had not recorded details of" +
        " it in her journal, we might know nothing at all of it."), 1);

    add_ask(({"edition", "final edition"}),
        ("say " +
        "The final edition should only take a few months to" +
        " complete once all the changes and additions" +
        " have been processed.  Then the volumes will be bound and" +
        " placed in an area where anyone can read them."), 1);

    add_ask(({"escape", "servitude"}),
        ("say " +
        "Caliana served Masthron first at the forge and then" +
        " as a commander until finally she made her escape.  This" +
        " story is told in Volume 6."), 1);

    add_ask(({"final version", "version"}),
        ("say " +
        "The final version of the history will" +
        " include information contributed by Guild members.  I" +
        " hope you will let us know of anything you" +
        " feel should be included."), 1);

    add_ask(({"final volume", "volume 18", "Volume 18"}),
        ("say " +
        "Volume 18 is the final volume of the Calian Chronicles. " +
        " It is the final document written by Caliana, and we" +
        " scribes can only assume that it is some sort of" +
        " farewell letter.  The notebook is empty; the original" +
        " parchment is in storage and will be put in a place of" +
        " honor when the Chronicles are complete."), 1);

    add_ask(({"flogging", "flog", "feed", "feeding"}),
        ("say " +
        "Uhclem takes care of all of my needs - both" +
        " flogging and feeding.  The writing I do myself, so he" +
        " doesn't need to help me with that!"), 1);

    add_ask(({"flora", "fauna", "animal", "animals", "plant", "plants",
        "volume 2", "Volume 2"}),
        ("say " +
        "Volume 2 is a catalog of the animals and plants known" +
        " to live in Calia.  I'm sure it's not complete - perhaps" +
        " you know of one which is missing from the notebook?"), 1);

    add_ask(({"foundation", "guild", "warriors", "warrior guild",
        "calian warrior guild", "warrior", "volume 11", "Volume 11"}),
        ("say " +
        "Volume 11 isn't really a book.  It is a single" +
        " piece of parchment which contains Caliana's address" +
        " to her followers the day they ascended Mt. Kyrus" +
        " and became the Calian Warrior Guild. " +
        " The notebook is empty, and the parchment is in" +
        " safekeeping until a permanent display case is ready."), 1);

    add_ask(({"friend", "enemy", "friends", "enemies"}),
        ("say " +
        "We have received some from both friends and" +
        " enemies of the Calian Warriors guild, such as scribes" +
        " employed by various warlords.  You'll have to decide" +
        " for yourself how much you can trust that information."), 1);

    add_ask(({"frog", "frogs", "cow", "cows", "wolf", "wolves", "mammal",
        "mammals", "lemming", "lemmings", "gopheroo", "gopheroos", "hamster",
        "hamsters", "turtle", "turtles", "lizard", "lizards"}),
        ("say " +
        "Yes, there are many different animals described" +
        " in the Chronicles, but the collection is" +
        " incomplete, I'm sure.  Please let us know if you have" +
        " seen any other interesting animals in your travels."), 1);

    add_ask(({"funeral", "funerals"}),
        ("say " +
        "Only one funeral is recorded in detail; look in" +
        " Volume 15."), 1);

    add_ask(({"gelan", "capital", "volume 8", "Volume 8"}),
        ("say " +
        "Volume 8 is the story of how Caliana and her" +
        " followers settled in Gelan and brought it prosperity."), 1);

    add_ask(({"geography", "map", "maps", "volume 1", "Volume 1"}),
        ("say " +
        "Volume 1 presents what we know of Calian geography."), 1);

    add_ask(({"goryn", "Goryn"}),
        ("say " +
        "Goryn was the elder brother of Kroug.  Little is known" +
        " of him other than that for a time he ruled as a" +
        " member of the Quartan."), 1);

    add_ask(({"history", "early history", "volume 3", "Volume 3"}),
        ("say " +
        "Volume 3 describes the early history of the land which" +
        " we now call Calia.  I can't vouch for its accuracy -" +
        " everything in it happened long before I was born."), 1);

    add_ask(({"hurn", "sword", "fungus", "maul"}),
        ("say " +
        "You must have heard some rumors about the Chronicles" +
        " to be asking that.  I think you'll find Volume" +
        " 7 very interesting."), 1);

    add_ask(({"ink", "dry"}),
        ("say " +
        "It's such slow drying ink, I'm afraid it will be a long" +
        " time before we can do any writing on this desk again," +
        " and I'm sure the stain will be permanent."), 1);

    add_ask(({"Kroug", "kroug", "krougs", "volume 9", "Volume 9"}),
        ("say " +
        "Volume 9 is the story of Kroug and his foul" +
        " minions.  The original text was written by one" +
        " of his slavering lackeys; we scribes copied the" +
        " key information into the notebook."), 1);

    add_ask(({"kyrus", "mount kyrus", "mountain", "volume 10", "Volume 10"}),
        ("say " +
        "Volume 10 recounts some strange events that occurred" +
        " around Mt. Kyrus before the Warriors took up" +
        " residence in the palace."), 1);

    add_ask(({"lamp", "lamps"}),
        ("say " +
        "It's inconvenient having the lamps so high on the walls. " +
        " I have to stand on the desk to refill them."), 1);

    add_ask(({"Masthron", "masthron"}),
        ("say " +
        "Masthron was a goblin warlord who captured Caliana while" +
        " she was still a young girl.  Eventually she made" +
        " her escape."), 1);

    add_ask(({"maul", "mauling"}),
        ("say " +
        "The tactic which we know as mauling first appears in Volume" +
        " 6, but the word 'maul' is first used in Volume 7."), 1);

    add_ask(({"medallion", "medallions"}),
        ("say " +
        "The medallion is first mentioned in Volume 12."), 1);

    add_ask(({"members", "tyrants"}),
        ("say " +
        "The members of the Quartan were Masthron, Hucker," +
        " Oslewt, and Zarr, although Zarr was later replaced by" +
        " Goryn and then by Kroug."), 1);

    add_ask(({"notebook", "notebooks"}),
        ("say " +
        "The notebooks represent the raw information upon" +
        " which the final version of the Chronicles will be" +
        " based.  If you suspect anything in them is" +
        " inaccurate or incomplete, you are invited to post a" +
        " note on the board or send mail to Uhclem."), 1);

    add_ask(({"parchment", "parchments"}),
        ("say " +
        "There are two parchments which are volumes of" +
        " the Chronicles.  The first is Volume 11, the speech" +
        " Caliana made to the Warriors which established the" +
        " Guild, and the second is the final volume, whose text we" +
        " do not fully understand."), 1);

    add_ask(({"passage", "the passage", "volume 7", "Volume 7"}),
        ("say " +
        "Volume 7 was written by Caliana herself.  It is the" +
        " story of her escape from servitude to the" +
        " goblin warlord Masthron, the passage through East" +
        " Calia, and her eventual arrival in Gelan.  Her journal is" +
        " kept in a safe place, but this notebook summarizes the" +
        " key events she recorded."), 1);

    add_ask(({"peace", "freedom"}),
        ("say " +
        "During the time of the Quartan we had peace but" +
        " not freedom.  Its members were tyrants."), 1);

    add_ask(({"permanent display case", "display case", "case"}),
        ("say " +
        "The parchments which comprise volumes 11 and 18 will" +
        " be put in permanent display cases so that" +
        " everyone can read them."), 1);

    add_ask(({"quest", "quests"}),
        ("say " +
        "As with all boards in Genesis, please do not" +
        " post any quest information here, not even quest ideas. " +
        " If you wish to suggest a quest, you should do so in mail."), 1);

    add_ask(({"question", "what"}),
        ("say " +
        "Could you be more specific?"), 1);

    add_ask(({"raw information", "raw", "information"}),
        ("say " +
        "If you have any information that you believe should be" +
        " included in the Chronicles, or if you know of any" +
        " errors in the information already recorded here," +
        " please do not hesitate to give it to us in the form of a" +
        " note on the board or in mail."), 1);

    add_ask(({"good information", "good"}),
        ("say " +
        "That's the kind of information we want!"), 1);

    add_ask(({"residence", "palace"}),
        ("say " +
        "The crystalline palace is first mentioned in Volume 12."), 1);

    add_ask(({"ruled", "quartan", "Quartan"}),
        ("say " +
        "The Quartan was a group of four warlords who divided" +
        " the land between themselves and ruled it" +
        " through unopposable military might.  Their story is" +
        " in Volume 5."), 1);

    add_ask(({"safe", "safekeeping", "place", "safe place"}),
        ("say " +
        "The parchments which comprise volumes 11 and 18 are being" +
        " kept in a safe place."), 1);

    add_ask(({"slavering", "lackeys", "slavering lackeys"}),
        ("say " +
        "I trust you are referring to Kroug's minions and not" +
        " us.  We scribes work for Uhclem willingly."), 1);

    add_ask(({"source", "sources"}),
        ("say " +
        "The information for the volumes comes from various" +
        " sources.  Many of them are simply collections of tales" +
        " we have heard from travellers."), 1);

    add_ask(({"span", "time", "cover"}),
        ("say " +
        "The Chronicles begin in ancient times - no one can" +
        " say for certain when the earliest mortals walked this land" +
        " - and end just after the Congress of" +
        " Gelan established the Confederation.  That's about" +
        " twenty years ago.  I'm afraid we haven't had time" +
        " to collect more recent information."), 1);

    add_ask(({"stain", "ink stain"}),
        ("say " +
        "Everyone seems to see something different when he looks" +
        " at the stain.  Perhaps it reflects one's innermost" +
        " desires or reveals some unresolved conflict.  I know" +
        " nothing of such things, of course, as I am only" +
        " a simple scribe."), 1);

    add_ask(({"desire", "desires"}),
        ("say " +
        "Bore me not with tales of your desires, and I will not" +
        " bore you with mine."), 1);

    add_ask(({"conflict", "conflicts"}),
        ("say " +
        "The Chronicles are full of conflict."), 1);

    add_ask(({"stonewood", "bleak zone", "zone", "gak", "gaklands",
        "drylands"}),
        ("say " +
        "Ahh, it will be some time before you can go there. " +
        " It's so dangerous that the wizards will have to tame it" +
        " a bit before they open up a path to East Calia."), 1);

    add_ask(({"strange", "strange events", "strange tale"}),
        ("say " +
        "Some strange events are recorded in Volume 17.  You'll" +
        " have to decide for yourself what they mean."), 1);

    add_ask(({"struggle", "dominance", "struggle for dominance", "volume 5",
        "Volume 5"}),
        ("say " +
        "Volume 5 describes the dominance of the four" +
        " most powerful warlords, the ones who ruled the entire" +
        " land for a while."), 1);

    add_ask(({"swarm", "swarming"}),
        ("say " +
        "Swarming is first mentioned Volume 6."), 1);

    add_ask(({"tactic", "tactics"}),
        ("say " +
        "The Chronicles record the tactics known as swarm and maul."), 1);

    add_ask(({"terrible price", "price", "cost", "paid"}),
        ("say " +
        "Yes, the Great Battle was not won without cost, and" +
        " the terrible price is described in volumes 13 and 15."), 1);

    add_ask(({"times", "modern", "modern times", "volume 16", "Volume 16"}),
        ("say " +
        "Volume 16 tells of the changes in Calia after the" +
        " Great Battle and the Congress of Gelan.  Much" +
        " changed during that time, and much continues to" +
        " change even today."), 1);

    add_ask(({"times", "span", "time span"}),
        ("say " +
        "The span covered by the Chronicles extends into ancient" +
        " times and ends with the Confederation twenty years ago."), 1);

    add_ask(({"traveller", "travellers"}),
        ("say " +
        "Travellers have ventured through Calia and brought" +
        " back stories of the things they have seen. " +
        " Perhaps you have travelled and have seen something which" +
        " we have yet to include in our notebooks?"), 1);

    add_ask(({"twenty years", "twenty years ago"}),
        ("say " +
        "The Confederation was formed about twenty years" +
        " ago.  The Chronicles close shortly after that time."), 1);

    add_ask(({"uhclem", "wizard"}),
        ("say " +
        "Uhclem is a wise and intelligent wizard.  He only flogs" +
        " us when we deserve it, and he feeds us once a week" +
        " whether we pass out from hunger or not."), 1);

    add_ask(({"volume", "volumes"}),
        ("say " +
        "The notebooks are labelled Volume 1 through Volume 18. " +
        " Feel free to read any or all of them and make comments."), 1);

    add_ask(({"war legend", "war legend of calia", "murl", "murl brightwater",
        "volume 15", "Volume 15"}),
        ("say " +
        "Ahh... Volume 15... such a story of contrasts, such joy and" +
        " such sadness.  It tells of the wedding of Allerdice and Doe," +
        " and of the funeral of Murl Brightwater, the first" +
        " War Legend of Calia."), 1);

    add_ask(({"warlord", "warlords"}),
        ("say " +
        "This is certainly an area in which the" +
        " Chronicles are currently deficient.  While we believe" +
        " that at one time there were many warlords in the land, only" +
        " a few are documented here.  If you know of one," +
        " even if your information is incomplete, we would like" +
        " to hear from you."), 1);

    add_ask(({"wedding", "marriage", "weddings", "marriages"}),
        ("say " +
        "Yes, there is a wedding in the Chronicles; look in" +
        " Volume 15."), 1);

    add_ask(({"year", "years", "year of confederation"}),
        ("say " +
        "We are currently in the Twentieth Year" +
        " of Confederation.  The Chronicles only cover events" +
        " through the Year of Confederation, so I'm afraid" +
        " there are nineteen years for which we have no records."), 1);

    add_ask(({"Zarr", "zarr"}),
        ("say " +
        "You'll find his story in Volume 5, and again in" +
        " Volume 9."), 1);

    }
