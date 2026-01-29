// OBJECT:  marionette

    /* Calia Domain

    HISTORY

    [2000-12-21] Created by Uhclem from [C:\CALIA\YULEWARE\TOYS\MARIONET.DOC].

    PURPOSE

    A toy to be found under the Christmas tree in the domain office in the
    Tower of Realms. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>

// GLOBAL VARIABLES

object Global_Adverbs = find_object("sys/global/adverbs");

// OBJECT DEFINITION

void
create_object()

{

    int n = random(10);  /*  Must match number of cases below.  */
    string long_text;

    /*
     *  DESCRIPTION    
     */

    /*
     *  I consider the physical description of the marionette trivial; the 
     *  important details are in the actions, so I put just enough text in this
     *  section to describe the puppet's general character.    
     */

    set_name("marionette");
    add_name("puppet");
    add_name("toy");

    switch (n)

    {

        case 0:

        set_short("sinister kroug marionette");
        long_text = "a menacing kroug footsoldier";
        add_name(({"kroug", "footsoldier", "soldier"}));

        add_item(({"head", "face"}),
            "The head is painted to suggest a face that," +
            " although there's no sharp detail," +
            " gives an impression of malevolence.\n");

        break;

        case 1:

        set_short("happy-go-lucky clown marionette");
        long_text = "a jovial but somewhat dimwitted clown";
        add_name("clown");

        add_item(({"head", "face", "colours", "bright colours",
            "costume", "vivid costume"}),
            "The marionette is painted in a myriad of bright" +
            " colours to suggest the vivid costume of a clown and" +
            " a face with an expression of blissful stupidity.\n");

        break;

        case 2:

        set_short("stern old schoolmaster marionette");
        long_text = "an old and obviously humourless schoolmaster";
        add_name("schoolmaster");

        add_item(({"head", "face"}),
            "The head is painted to suggest a face that," +
            " although there's no sharp detail," +
            " unmistakably depicts a stern disciplinarian.\n");

        break;

        case 3:

        set_short("snaggle-toothed troll marionette");
        long_text = "a hideous troll with crooked, protruding teeth";
        add_name("troll");

        add_item(({"head", "face", "teeth", "protruding teeth"}),
            "The head is crudely painted to suggest a grotesque troll" +
            " face with crooked, protruding teeth.\n");

        break;

        case 4:

        set_short("red-eyed vampire marionette");
        long_text = "a gaunt vampire with bloodshot eyes and sharp fangs";
        add_name("vampire");

        add_item(({"head", "face", "fangs", "eyes",
            "sharp fangs", "white fangs", "bloodshot eyes"}),
            "The head is painted mostly in shades of grey to" +
            " suggest a grim vampire face with white fangs" +
            " and red bloodshot eyes.\n");

        break;

        case 5:

        set_short("pointy-headed pixie marionette");
        long_text = "a bright-eyed pixie with pointy head, nose, and ears";
        add_name("pixie");

        add_item(({"head", "face", "nose", "ears",
            "pointy head", "pointy nose", "pointy ears"}),
            "The head is painted in bright colors, mostly" +
            " pinks and yellows, that accent the pointy nature" +
            " of the pixie's head, nose, and ears.\n");

        break;

        case 6:

        set_short("sleepy old sorceror marionette");
        long_text = "an ancient caster of spells and conjurer of spirits";
        add_name("sorcerer");

        add_item(({"face", "lines", "robe", "hat",
            "long robe", "tall hat", "symbols"}),
            "A long robe and tall hat, both covered with symbols" +
            " of uncertain but probably magical significance," +
            " are painted on the marionette to identify it as a" +
            " sorceror. Lines on the face suggest" +
            " extreme age and the need for a nap.\n");

        break;

        case 7:

        set_short("pompous nobleman marionette");
        long_text = "a nobleman encumbered by his fancy clothes and jewels";
        add_name("nobleman");

        add_item(({"head", "face", "clothes", "fancy clothes", "jewel",
            "jewels", "paint", "pattern"}),
            "The puppet is covered with every color of paint in" +
            " a pattern that suggests an extravagant (and" +
            " heavy) covering of garish clothes and gaudy jewels.\n");

        break;

        case 8:

        set_short("mischevious gremlin marionette");
        long_text = "a strange little creature with a mischievous grin";
        add_name("gremlin");

        add_item(({"head", "face", "eyes", "grin", "mischievous grin"}),
            "The puppet is painted purple all over except for" +
            " the white of its eyes and its wide, toothy grin." +
            " The giddy expression on its face suggests capricious" +
            " rather than sinister inclinations.\n");

        break;

        case 9:

        set_short("portly monk marionette");
        long_text = "an unkempt but well-fed monk";
        add_name("monk");

        add_item(({"head", "face", "robes", "head", "shaved head"}),
            "The puppet is painted to look like a monk" +
            " with a shaved head. His robes are in" +
            " disarray, perhaps because he's grown so fat" +
            " they they simply don't fit any more!\n");

    }

    set_long("This marionette is carved of wood and painted to" +
        " look like " + long_text + ". You can pull its strings" +
        " to make it move.\n");

    add_item(({"body", "joint", "joints", "limb", "limbs",
        "wood", "painted wood"}),
        "The marionette's body is made of painted wood with" +
        " limbs that have joints to allow a wide range of movements.\n");

    add_item(({"string", "strings"}),
        "The strings are attached to the marionette so that it" +
        " will move when you pull them. How it moves depends" +
        " on how you pull!\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 100);

    add_prop(OBJ_M_NO_SELL, "Nobody wants to buy anything" +
        " with that many strings attached!\n");

}

// FUNCTIONS

// Function:  pull_strings()

/*

Purpose:  pull the marionette's strings and make it move in a variety of ways
depending on the adverb used in the command.

Arguments:  string containing 'string' or 'strings' and optional adverb.

Returns:  0/1

*/

int
pull_strings(string str)

{

    string *movements =
        ({"prances about wildly, gyrating its arms and legs and" +
        " rolling its head from side to side.",
        "bends down and bounces in a herky-jerky fashion as if it" +
        " were riding a bucking horse.",
        "flails its arms and legs about haphazardly as if doing several" +
        " different dances at once.",
        "performs a rigorous exercise routine including" +
        " jumping-jacks, push-ups, and even a few squat-thrusts."});

    string *words;
    string adverb = "";
    string pulls_how;

    /*
     *  In most cases, everyone in the room sees the same puppet movement, and 
     *  only moves_how is needed.  When this_player (operating the puppet)
     *  needs to see a different message, moves_how is displayed to everyone
     *  else and moves_tp is displayed to this_player.    
     */

    string moves_how;
    string moves_tp;
    object tp = this_player();

    if (!stringp(str) || !wildmatch("*string*", str))

    {

        /*
         * Player did not specify what to pull.   
         */

        notify_fail("Pull what?\n");
        return 0;

    }

    if (environment() != tp)

    {

        /*
         * Player is not holding this marionette.   
         */

        notify_fail("You cannot reach the strings from this distance.\n");
        return 0;

    }

    /*
     *  Most players will probably type "pull strings" or "pull strings 
     *  <adverb>", but a few may try something like "pull the marionette's
     *  strings" or - horrors - "pull the strings on the marionette <adverb>".
     *  Look for the last word to be either an adverb or "string[s]" and ignore
     *  the rest.  If no adverb is specified, insert a ".".    
     */

    words = explode(str, " ");

    if (sizeof(words) > 1 && !wildmatch("string*", words[sizeof(words)-1]))

    {

        adverb = Global_Adverbs->full_adverb(words[sizeof(words)-1]);

    }

    else

    {

        adverb = ".";

    }

    if (adverb == "")  /*  Result if adverb is not recognized.  */

    {

        notify_fail("Pull the strings how?\n");
        return 0;

    }

    if (adverb != ".")

    {

        pulls_how = " " + adverb + ".";

    }

    else

    {

        pulls_how = adverb;

    }

    /*
     *  The following switch chooses the marionette's motion based upon the 
     *  adverb supplied by the player.  Any adverbs for which no specific cases
     *  are provided are processed by the default case which selects one of the
     *  strings from the "movements" array.    
     */

    switch (adverb)

    {

        case "absentmindedly":
        case "aimlessly":
        case "carelessly":
        case "lazily":

        moves_how = "shuffles around in no particular" +
            " direction, wobbling to the right and to the left, and" +
            " its head nods slowly as if it were about to fall asleep.";

        break;

        case "badly":
        case "dreadfully":
        case "horribly":
        case "terribly":

        moves_how = "jerks and twitches as if it were in" +
            " its death throes, freezes in a grotesque" +
            " position when its strings tangle momentarily, then" +
            " goes limp and dangles from its strings like a corpse" +
            " from a hangman's noose.";

        break;

        case "awkwardly":
        case "crudely":

        moves_how = "stumbles forward a bit, then rocks" +
            " back and forth listlessly because " + QTNAME(tp) +
            " is holding its strings too high off the ground.";

        moves_tp = "stumbles forward a bit, then rocks" +
            " back and forth listlessly because you're" +
            " holding its strings too high off the ground.";

        break;

        case "obsequiously":
        case "quiescently":
        case "sycophantically":

        moves_how = "takes a few hesitant steps, then" +
            " assumes a sitting position and acts as if looking" +
            " up something in a big dictionary.";

        break;

        case "agreeably":
        case "charmingly":
        case "delightfully":
        case "enchantingly":
        case "impressively":
        case "irresistibly":
        case "majestically":
        case "pleasantly":
        case "radiantly":

        moves_how = "performs " +
            ({"a surprisingly", "a marvelously", "an unexpectedly",
            "a remarkably"})[random(4)] +
            " " +
            ({"graceful", "fluid", "refined", "sophisticated"})[random(4)] +
            " " +
            ({"minuet", "polonaise", "waltz", "tarantella"})[random(4)] +
            ", including " +
            ({"brilliant", "scintillating", "lightning-quick",
            "crisp"})[random(4)] +
            " " +
            ({"spins", "leaps", "scissor-kicks",
            "heel-and-toe movements"})[random(4)] +
            " " +
            ({"executed in rapid succession",
            "performed to the rhythmic 'click-clack' of its wooden joints",
            "and sprightly gyrations of its head and arms",
            "that seem nearly impossible for a" +
            " string-controlled puppet to execute"})[random(4)] +
            ".";

        break;

        case "angelically":
        case "exquisitely":
        case "gracefully":
        case "soothingly":
        case "sweetly":

        moves_how =
            ({"floats suspended from its strings just" +
            " above the ground, the gentle motion of its" +
            " arms and legs suggesting",
            "swings in broad arcs from its strings, moving" +
            " its limbs in rhythmic patterns to imitate"})[random(2)] +
            " " +
            ({"the beating of a dove's wings or the lazy circling" +
            " of a goldfish in a pond.",
            "the graceful spiral of a falling leaf buoyed by" +
            " a subtle breeze."})[random(2)];

        break;

        case "cluelessly":
        case "dementedly":
        case "freakishly":
        case "maniacally":
        case "sardonically":

        moves_how = "pulls back on the strings and makes " + QTNAME(tp) +
            " do a lively jig!";

        moves_tp = "pulls back on the strings and makes you do" +
            " a lively jig!";

        break;

        case "coldly":
        case "heartlessly":
        case "icily":

        moves_how = "shivers so violently that its joints" +
            " produce a numbing, high-pitched rattle that makes" +
            " you shiver as well!";

        break;

        case "religiously":
        case "reverently":
        case "sanctimoniously":

        moves_how = "bangs its head on the ground in reverence to" +
            " the god of marionettes.";

        break;

        case "arousingly":
        case "erotically":
        case "passionately":
        case "romantically":
        case "seductively":
        case "sexily":

        moves_how =
            ({"rubs its legs together in the manner of a" +
            " cricket, making a chirping sound to attract a mate.",
            "clicks its wooden hands together as if they" +
            " were castanets and performs a sensuous but" +
            " sophisticated flamenco dance guaranteed to" +
            " seduce any female marionette who witnesses it.",
            "briefly has a passionate encounter with your leg, much" +
            " as small dogs are prone to do at" +
            " the most inopportune moments."})[random(3)];

        break;

        case "dramatically":
        case "melodramatically":
        case "theatrically":

        moves_how =
            ({"struggles with an imaginary enemy,",
            "defends itself against an imaginary attacker,",
            "falls back in the face of an imaginary" +
            " assailant, but quickly recovers" +
            " and takes the offensive,"})[random(3)] +
            " " +
            ({"rolling on the ground and grappling with its foe.",
            "thrusting and parrying in the manner of a master swordsman.",
            "trading powerful kicks and punches."})[random(3)] + " ";

        if (random(2))  /*  true=victory, false=defeat for the marionette  */

        {

            moves_how +=
                ({"The battle is hard-fought, but the " + short() +
                " finally gets the upper hand, lifting the" +
                " opponent high overhead and then slamming it" +
                " down headfirst on the ground.",
                "The enemy gains the advantage momentarily," +
                " pushing the " + short() + " onto its back," +
                " but the puppet reverses the position and" +
                " finishes off its opponent in" +
                " a protracted, agonizing stranglehold."})[random(2)];

        }

        else

        {

            moves_how +=
                ({"The " + short() + " is dealt a mortal" +
                " blow! It staggers back, clutches its" +
                " chest, gathers enough strength to raise its fist" +
                " and rail at cruel fate, then slumps to" +
                " the ground, defeated but vowing with the last" +
                " quiver of its strings to rise again.",
                "Suddenly, the depraved enemy draws a poison" +
                " knife that finds its mark! The " + short() +
                " convulses in agony, yet continues to fight even" +
                " as the poison takes effect, finally managing," +
                " with its last bit of strength, to turn the" +
                " blade on its opponent, and the two die together" +
                " in a lethal embrace."})[random(2)];

        }

        break;

        case "in a paranoid manner":

        moves_how =
            ({"creeps about and ducks behind imaginary hedges and walls,",
            "peers over, under, and through some imaginary bushes,",
            "digs and then crawls through an imaginary tunnel,"})[random(3)] +
            " " +
            ({"bolts upright and points at something in the distance,",
            "leaps as if startled from behind,",
            "jumps back in surprise from something at its feet,"})[random(3)] +
            " and then " +
            ({"races away as far as its strings will allow!",
            "churns its legs and arms as if running for its life!",
            "races away, flailing its arms in abject terror!"})[random(3)];

        break;

        case "inanely":
        case "in a silly manner":
        case "ridiculously":
        case "stupidly":

        moves_how = "prances about with its knees slightly" +
            " bent, clapping its wooden hands to make a noise" +
            " that sounds a little like two coconut halves" +
            " being banged together.";

        break;

        case "flatulently":

        moves_how =
            ({"holds onto its strings for dear life as it is swept" +
            " off its feet by a sudden gust of wind!",
            "scurries as far as its strings will allow and holds" +
            " its hand over its nose!"})[random(2)];

        break;

        case "apoplectically":
        case "hysterically":
        case "masochistically":
        case "painfully":

        moves_how = "heaves and twitches as if in the grip" +
            " of a sudden seisure! The violent motion nearly" +
            " wrenches its head from its body, but the spasm" +
            " subsides with all body parts intact.";

        break;

        case "hornily":
        case "incestuously":
        case "lewdly":

        moves_how = "cavorts in a manner so " +
            ({"lewd", "aberrant", "perverse"})[random(3)] +
            ", so " +
            ({"profoundly", "unspeakably", "intensely"})[random(3)] +
            " " +
            ({"grotesque", "revolting", "vile"})[random(3)] +
            ", so " +
            ({"unspeakably", "unimaginably", "utterly"})[random(3)] +
            " and " +
            ({"unfathomably", "irredeemably", "incomprehensibly"})[random(3)] +
            " " +
            ({"disturbed and profane",
            "deranged and offensive",
            "wanton and lustful"})[random(3)] +
            ", " +
            ({"wallowing (if a marionette can indeed be said" +
            " to wallow) in perversion of every kind",
            "performing acts that would surely compel" +
            " the puppetmaker to demolish his creation",
            "assuming postures suited only to self-abuse or" +
            " to congress with creatures of" +
            " deviant shape"})[random(3)] +
            ", " +
            "that you - yes, even you - are compelled to avert your" +
            " eyes until the motion has subsided!";

        break;

        case "astonishingly":
        case "amazingly":
        case "formidably":
        case "adeptly":
        case "brilliantly":
        case "wonderfully":

        moves_how = "prances about in a small" +
            " circle, performing somersaults, handsprings," +
            " and even the occasional cartwheel -" +
            " a formidable accomplishment for someone" +
            " suspended from strings!";

        break;

        case "blissfully":
        case "contentedly":
        case "euphorically":
        case "exuerantly":
        case "happily":
        case "joyfully":

        moves_how = "prances " + adverb + " around in a" +
            " intoxicating jig. Its head rocks back and its body" +
            " jiggles as if in laughter, and its arms beckon one" +
            " and all to join in the euphoric dance.";

        break;

        case "bleakly":
        case "dejectedly":
        case "gloomily":
        case "grimly":
        case "morosely":
        case "sadly":
        case "sorrowfully":
        case "melancholically":
        case "somberly":

        moves_how = "creeps around with head bowed low, perhaps" +
            " acting the part of " +
            ({"a mourner at a funeral", "a captured soldier"})[random(2)] +
            " or " +
            ({"a rejected suitor", "a condemned prisoner"})[random(2)] +
            ", its feet barely shuffling along the ground" +
            " as it tediously marches toward some dreaded destination.";

        break;

        case "bluntly":
        case "boldly":
        case "decisively":
        case "forcefully":
        case "grimly":
        case "loudly":
        case "mightily":
        case "powerfully":

        moves_how = "stomps its little wooden feet on the ground" +
            " and shakes its little wooden fists! The painted eyes" +
            " glare at you as its head swings around, and" +
            " you get the impression that " +
            ({"you must have done something to anger it!",
            "it must have you confused with its arch enemy!",
            "this is not a puppet to be trifled with!"})[random(3)];

        break;

        case "creatively":
        case "dangerously":
        case "enigmatically":
        case "heroically":
        case "quixotically":
        case "theatrically":
        case "zealously":

        /*
         *  This is isn't supposed to make sense, even to people who have seen 
         *  the utterly hilarious fantasy film "Being John Malkovich," from
         *  which I borrow an important bit of dialog.  Trying to figure out
         *  this variation will annoy the non-native English speakers and
         *  probably most of the native speakers as well.    
         */

        moves_how = ({"assumes", "adopts", "strikes"})[random(3)] +
            " " +
            ({"an eccentric", "a peculiar", "a puzzling"})[random(3)] +
            " " +
            ({"attitude", "pose", "stance"})[random(3)] +
            ", with " +
            ({"eyes", "ears", "knees"})[random(3)] +
            " " +
            ({"akimbo", "clenched", "extended"})[random(3)] +
            " and " +
            ({"nose", "brow", "chin"})[random(3)] +
            " " +
            ({"askance", "agog", "askew"})[random(3)] +
            ", " +
            ({"sprinces (which is to say, 'springs' and 'pounces')",
            "crumps (which is to say, 'crouches' and 'jumps')",
            "snarts (which is to say, 'sneaks' and 'darts')"})[random(3)] +
            " " +
            ({"forward", "sideways", "indirectly"})[random(3)] +
            " into " +
            ({"an oblique", "a forward-standing sideways-leaning",
            "a somewhat precarious but nonetheless ambitious"})[random(3)] +
            " position, then" +
            " " +
            ({"returns to what may or may not have been its previous pose.",
            "immediately reverts to an innocent, 'it-wasn't-me' posture.",
            "goes limp, dangling... hmm, how best to put" +
            " it? Perhaps '" + adverb + "' captures it best..." +
            " yes, dangling " + adverb +
            " from its strings."})[random(3)] +
            " " +
            ({"You find yourself wondering about the meaning" +
            " and purpose of puppetry in Genesis, but there" +
            " are no easy answers.",
            "You feel confused and beguiled by the" +
            " marionette, yet forgiving because of the warm spirit" +
            " of the yule season.",
            "The word 'Malkovich' flashes momentarily before your" +
            " eyes, and a voice in your head, with no" +
            " prompting from you, responds in a low" +
            " but clear tone, 'Malkovich!' You figure that it must" +
            " be a yule greeting of some kind and give" +
            " it no further thought."})[random(3)];

        break;

        case "deliriously":
        case "feverishly":

        moves_how = "dances with abandon, its arms beating out" +
            " a wild rhythm as its legs churn the air.";

        break;

        case "delicately":
        case "gently":
        case "mildly":

        moves_how = "moves ever so slightly - just a miniscule nod" +
            " of the head, a delicate wave of the hand," +
            " and a barely perceptible undulation of the body" +
            " - a lifelike movement that can only be attempted" +
            " by an expert puppeteer.";

        break;

        case "discreetly":
        case "coyly":
        case "nonchalantly":
        case "secretively":
        case "sneakily":
        case "surreptitiously":

        moves_how = "moves, yet " + QTNAME(tp) + " didn't" +
            " pull the strings... or did " + tp->query_pronoun() + "?";

        moves_tp = "moves, yet nobody noticed your pulling" +
            " the strings... or did they?";

        break;

        case "dwarvishly":

        moves_how = "attempts a dance that would be" +
            " best performed underground... far underground, in the dark.";

        break;

        case "elvishly":

        moves_how = "attempts a dance of ancient origin, one" +
            " that under happier circumstances would have" +
            " been forgotten long ago.";

        break;

        case "again":

        moves_how = "moves again.";

        break;

        case "endlessly":
        case "eternally":
        case "excessively":
        case "relentlessly":
        case "repeatedly":
        case "unceasingly":

        moves_how = "dances and dances and dances and dances" +
            " some more. Its arms, legs, and head gyrate constantly" +
            " in a blur of motion and a clatter of noise." +
            " Not until smoke starts to emerge" +
            " from the wooden joints does " + QTNAME(tp) +
            " finally relent and let the puppet rest.";

        moves_tp = "dances and dances and dances and dances" +
            " some more. Its arms, legs, and head gyrate constantly" +
            " in a blur of motion and a clatter of noise. When" +
            " smoke starts to emerge from the wooden joints," +
            " you decide that it's time to stop pulling the" +
            " strings and give the puppet a rest.";

        break;

        case "feebly":
        case "meekly":
        case "weakly":

        moves_how = "hesitates, ready to move" +
            " yet somehow uncertain, constrained," +
            " even paralyzed, finally managing to execute" +
            " a single indistinct dance step, or perhaps it" +
            " was just a stumble.";

        break;

        case "ironically":
        case "materialistically":
        case "motionlessly":
        case "sycophantically":
        case "xenophobically":

        moves_how = "simply raises its head and peers up at " + QTNAME(tp) +
            " as if waiting for an explanation.";

        moves_tp = "simply raises its head and peers up at you" +
            " as if waiting for an explanation.";

        break;

        case "fuzzily":
        case "gratuitously":
        case "lopsidedly":
        case "quackishly":
        case "quizzically":
        case "righteously":
        case "speculatively":
        case "subversively":
        case "weirdly":

        moves_how = "is provoked into a frenzy of" +
            " dancing, tumbling, and gymnastics, wheeling" +
            " and careening about in broad arcs and at" +
            " odd angles, finally coming to rest in a pose that" +
            " can only mean relief that the weird episode has ended.";

        break;

        case "annoyingly":
        case "busily":
        case "gnomishly":

        moves_how = "gyrates busily but without apparent purpose" +
            " or direction, its joints resonating with an annoying" +
            " - nay, obnoxious - sound: ClickClackClickClackClickClack!";

        break;

        case "hellishly":
        case "devilishly":
        case "evilly":
        case "diabolically":
        case "impishly":
        case "malevolently":
        case "satanically":
        case "subversively":
        case "wickedly":

        moves_how =
            ({"makes signs of allegiance to the various" +
            " dark powers that afflict Genesis, ending with" +
            " a special salute to Kroug himself",
            "mimes a ritual of animal" +
            " sacrifice, performing the" +
            " bathing-in-blood sequence with particular gusto",
            "directs several obscene gestures in your" +
            " direction, including some questioning the virtue" +
            " of your mother and the identity of your father"})[random(3)] +
            ", " +
            ({"skewers some imaginary opponents with an imaginary lance",
            "crushes some imaginary opponents under its feet",
            "challenges all comers to die at its" +
            " hands in single unarmed combat"})[random(3)] +
            ", and then " +
            ({"folds its arms and points its nose in the air" +
            " in an expression of pure contempt.",
            "squats on the ground and sulks as if it were" +
            " frustrated by the limited reach of the strings" +
            " that animate it.",
            "returns to a less belligerent posture," +
            " although its facial expression seems to be - just" +
            " perhaps - a little more hostile than before."})[random(3)];

        break;

        case "hobbitishly":
        case "hungrily":

        moves_how = "rubs its tummy with one hand, and with the" +
            " other it shades its painted eyes as it" +
            " carefully scans the horizon for something good to eat.";

        break;

        case "blandly":
        case "boringly":
        case "humanly":
        case "monotonously":
        case "normally":
        case "philosophically":
        case "regularly":
        case "systematically":
        case "wearily":

        moves_how = "walks upright in a regular gait, looking" +
            " where it's going and swinging its arms in" +
            " a rhythm consistent with its leg motion.";

        break;

        case "musically":
        case "tunefully":
        case "symphonically":

        moves_how = "prances to a tune hummed by " + QTNAME(tp) +
            ", " +
            ({"a cheerful", "an enigmatic", "a lyrical"})[random(3)] +
            " melody " +
            ({"that lends itself to", "suitable for",
            "perfect for"})[random(3)] +
            " " +
            ({"dancing or just tapping one's foot in time.",
            "either simple or intricate dance steps equally well.",
            "an energetic dance by someone whose" +
            " joints never suffer sprains."})[random(3)];

        break;

        case "indecently":
        case "obscenely":

        moves_how = "puts one hand over its crotch and" +
            " gyrates its pelvic area! You almost think you see" +
            " a white glove on that hand, but no - it must" +
            " be just a reflection off the polished wood.";

        break;

        case "rudely":

        moves_how = "turns around and bends over as if" +
            " trying to moon you!";

        break;

        case "arrogantly":
        case "conceitedly":
        case "haughtily":

        moves_how = "bows deeply with an exaggerated flourish" +
            " of its right hand, the left held 'just so' behind" +
            " its back, and then straightens up into a" +
            " dignified, haughty but not huffy posture that" +
            " implies that you're on its social level, but" +
            " only just barely.";

        break;

        case "courteously":
        case "diplomatically":
        case "politely":

        moves_how = "bows deeply at the waist, its nose" +
            " nearly touching its toes (how nice to" +
            " have such flexible joints!), and then rises to" +
            " a dignified stance of attention.";

        break;

        case "quickly":
        case "rapidly":
        case "speedily":
        case "swiftly":

        moves_how =
            ({"races from position to position at" +
            " breakneck speed, first running, then jumping," +
            " then swimming, then back to running again.",
            "leaps " + adverb + " and repeatedly up and down as" +
            " if standing on hot coals!",
            "performs somersaults over and over at such a rapid" +
            " pace that it's hardly more than a whirling" +
            " blur before your eyes!"})[random(3)];

        break;

        case "quietly":
        case "faintly":
        case "silently":
        case "noiselessly":
        case "soundlessly":

        moves_how = "moves ever so slowly through the steps of" +
            " a dance, its wooden joints easing through their" +
            " paces without the slightest sound.";

        break;

        case "bizarrely":
        case "perversely":
        case "outrageously":
        case "strangely":
        case "oddly":

        moves_how = "performs a bizarre pantomime of " +
            ({"filling a sock with warm vanilla custard and" +
            " then throwing it against a wall.",
            "climbing a pine tree upside-down and" +
            " collecting pine-cones along the way.",
            "winding its own entrails into a ball and then" +
            " bowling down some imaginary pins."})[random(3)] +
            " Then it " +
            ({"unexpectedly", "abruptly", "immediately"})[random(3)] +
            " turns around and" +
            " looks up at " + QTNAME(tp) + " as if to ask what" +
            " in the world " + tp->query_pronoun() +
            " is doing!";

        moves_tp = "performs a bizarre pantomime of " +
            ({"filling a sock with warm vanilla custard and" +
            " throwing it against a wall.",
            "climbing a pine tree upside-down, collecting pine" +
            " cones along the way.",
            "winding its own entrails into a ball and" +
            " bowling down some imaginary pins."})[random(3)] +
            " Then it " +
            ({"unexpectedly", "abruptly", "immediately"})[random(3)] +
            " turns around and looks up at you as if to ask what" +
            " in the world you are doing!";

        break;

        case "aggressively":
        case "emphatically":
        case "firmly":
        case "haphazardly":
        case "harshly":
        case "intently":
        case "recklessly":
        case "vigourously":
        case "wildly":

        moves_how =
            ({"jerks up and down as if tossed about in a storm," +
            " its arms, legs, and head gyrating in all" +
            " directions at once.",
            "bounds and cavorts with unbelievable energy, but" +
            " in no particular dance step - just a" +
            " lot of vigourous but disorganized movement.",
            "repeatedly leaps into the air and lands again" +
            " with great force, each time making such a loud" +
            " 'whack!' when it reaches the end of its strings" +
            " that you feel certain they're going to break!"})[random(3)];

        break;

        case "bitterly":
        case "cruelly":
        case "mercilessly":

        moves_how =
            ({"jumps up and down with such force that its arms" +
            " flail wildly; at times it looks like it's" +
            " calling for help - won't someone save it" +
            " from its cruel puppeteer?",
            "again and again finds itself jerked upward and then" +
            " flung back to the ground; occasionally" +
            " the force jerks its head back, and the painted" +
            " eyes seem to peer up and plead, 'why?'",
            "is flung helplessly about as it's repeatedly compelled" +
            " to execute some dance, march, or pantomime - it's hard" +
            " to tell which at this speed."})[random(3)];

        break;

        default:

        /*
         *  If the player doesn't choose how to pull the strings, select a 
         *  random effect.    
         */

        moves_how = movements[random(sizeof(movements))];

    }

    if (moves_how)

    {

        if (moves_tp)

        {

            tell_room(environment(tp), QCTNAME(this_player()) +
                " pulls the strings on " + tp->query_possessive() +
                " " + short() + pulls_how + "\n" +
                "The " + short() + " " + moves_how + "\n",
                ({tp}));

            write("You pull the strings on your " + short() +
                pulls_how + "\n" +
                "The " + short() + " " + moves_tp + "\n");

        }

        else

        {

            tell_room(environment(tp), QCTNAME(this_player()) +
                " pulls the strings on " + tp->query_possessive() +
                " " + short() + pulls_how + "\n" +
                "The " + short() + " " + moves_how + "\n",
                ({tp}));

            write("You pull the strings on your " + short() +
                pulls_how + "\n" +
                "The " + short() + " " + moves_how + "\n");

        }

    }

    return 1;

}

// Function:  init

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    ::init();
    add_action(pull_strings, "pull");

}
