// OBJECT:  bongo drums

    /* Calia Domain

    HISTORY

    [99-12-09] Created by Uhclem from [D:\CALIA\YULEWARE\TOYS\BONGOS.DOC].

    PURPOSE

    A toy to be found under the Christmas tree in the domain office in the
    Tower of Realms. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <math.h>

// GLOBAL VARIABLES

object Global_Adverbs = find_object("sys/global/adverbs");

string *Sounds = ({"bop", "bop", "bop", "bop", "bip", "bip", "bip", "bip",
    "bip", "bippty-bop", "bop-a-bop", "boppity-bop-bop", "bip-bop-bip-bop"});

// OBJECT DEFINITION

void
create_object()

{

    int l;
    int m;
    int n;

    /*
     *  DESCRIPTION    
     */

    set_short("pair of bongo drums");
    set_name("drum");
    add_name("drums");
    add_name("pair");
    add_name("bongo");
    add_name("bongos");
    add_name("toy");

    set_long("The small drums are made of polished wood" +
        " with tightly stretched leather heads. They are bound" +
        " together so that they're easy to take with you anywhere and" +
        " play any way you like.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 100);

    add_prop(OBJ_M_NO_SELL, "Sorry, you can't drum up any" +
        " business with this little toy.\n");

    /*
     *  ITEMS    
     */

    add_item(({"wood", "polished wood"}),
        "The wood is well-crafted, honed to a perfectly round" +
        " shape and rubbed with oils to a high shine.\n");

    add_item(({"head", "leather head", "heads", "leather heads",
        "leather", "drumhead", "drumheads"}),
        "The leather is tightly stretched over the drums so that" +
        " they will make an agreeable sound when they're played -" +
        " at least if they're played agreeably.\n");

    /*
     *  Scramble (not just randomize) sound array    
     */

    for (n=sizeof(Sounds)/2-1; n>0; n=n-1)

    {

        l = random(sizeof(Sounds));
        m = random(sizeof(Sounds));
        Sounds[l] = Sounds[m];

    }

}

// FUNCTIONS

// Function:  play_bongos

/*

Purpose:  play the bongo drums.

Arguments:  string containing this object and an optional adverb.

Returns:  0/1

*/

int
play_bongos(string str)

{

    object tp = this_player();
    object drums;
    string *words;
    string adverb = "";
    string play_how = "";
    string punctuate = ".";
    int sound_size = sizeof(Sounds);
    int m = 0;
    int n = 0;

    if (stringp(str))

    {

        words = explode(str, " ");

        if (sizeof(words) > 1)

        {

            drums = present(words[sizeof(words) - 2], tp);
            adverb = Global_Adverbs->full_adverb(words[sizeof(words)-1]);

        }

        else

        {

            drums = present(words[0], tp);
            adverb = ".";

        }

    }

    if (drums != this_object())

    {

        notify_fail("Play what?\n");
        return 0;

    }

    if (adverb != ".")

    {

        play_how = " " + adverb;

    }

    switch (adverb)

    {

        case "":
        notify_fail("Play the drums how?\n");
        return 0;
        break;

        case ".":
        str = implode(Sounds, ", ");
        break;

        case "absentmindedly":
        case "aimlessly":
        case "annoyingly":
        case "awkwardly":
        case "badly":
        case "carelessly":
        case "crudely":
        case "dreadfully":
        case "horribly":
        case "lazily":
        case "recklessly":
        case "terribly":
        play_how += ", beating out an uneven and unpleasant rhythm";
        n = NAME_TO_RANDOM(adverb, 1999, 3) + 1;
        str = implode(Sounds[0..n], ", ");
        str += " - " + implode(Sounds[n..n*2], ", ");
        str += " - " + implode(Sounds[n*2..n*3], ", ");
        break;

        case "agreeably":
        case "angelically":
        case "charmingly":
        case "delightfully":
        case "enchantingly":
        case "exquisitely":
        case "gracefully":
        case "impressively":
        case "irresistibly":
        case "majestically":
        case "pleasantly":
        case "radiantly":
        case "soothingly":
        case "sweetly":

        play_how +=
            ({
            ", making a sound that could charm the birds from the trees",
            ", mesmerizing everyone within earshot",
            ", eliciting refined musical tones from the little toy instrument"
            })[NAME_TO_RANDOM(adverb, 1999, 3)];

        m = NAME_TO_RANDOM(adverb, 1999, sound_size/2);
        n = NAME_TO_RANDOM(adverb, 1999, sound_size);
        str = implode(Sounds[n..n] + Sounds[0..m] + Sounds[n..n], ", ");
        break;

        case "apoplectically":
        case "hysterically":
        case "masochistically":
        case "painfully":

        play_how += " by pounding them against various" +
            " sensitive body parts";

        n = NAME_TO_RANDOM(adverb, 1999, sound_size/2);
        str = implode(Sounds[n..sound_size], "-ouch! ") + "-oww-oww-owwww!";
        break;

        case "arousingly":
        case "erotically":
        case "hornily":
        case "incestuously":
        case "lewdly":
        play_how += ", hoping there aren't any children watching";
        n = NAME_TO_RANDOM(adverb, 1999, sound_size/2);

        str = implode(Sounds[sound_size/4..sound_size/2] + ({"bump-a-THUMP",
            "bump-a-THUMP"}) + Sounds[0..n], ", ");

        punctuate = "!";
        break;

        case "astonishingly":
        case "amazingly":
        case "formidably":
        case "adeptly":
        case "brilliantly":
        case "wonderfully":
        play_how += ", beating out an intoxicating rhythm";
        n = NAME_TO_RANDOM(adverb, 1999, sound_size/2);
        str = implode(Sounds[0..n] + Sounds[sound_size/4..sound_size/2], ", ");
        break;

        case "blissfully":
        case "contentedly":
        case "euphorically":
        case "exuerantly":
        case "happily":
        case "joyfully":
        play_how += " with head tilted back and eyes closed in elation";
        n = NAME_TO_RANDOM(adverb, 1999, sound_size/2);
        str = implode(Sounds[0..sound_size/2] + Sounds[0..n], ", ");
        punctuate = "!";
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

        play_how += ", beating out a " +
            ({
            "staid",
            "reserved",
            "pensive"
            })[NAME_TO_RANDOM(adverb + tp->query_name(), 1999, 3)] +
            ", " +
            ({
            "dirgelike",
            "funereal",
            })[NAME_TO_RANDOM(adverb + tp->query_name(), 1999, 2)] +
            " rhythm";

        str = "bip... bop... bip... bop... bip... bop...";
        break;

        case "ignorantly":
        m += 3;
        case "fiercely":
        m += 3;
        case "angrily":
        m += 3;
        case "clumsily":
        m += 3;
        play_how += ", beating on them with both fists";
        str = implode(Sounds[0..m], "! ");
        punctuate = "!";
        break;

        case "briefly":
        str = Sounds[NAME_TO_RANDOM(tp->query_name(), 1999, sound_size)];
        break;

        case "calmly":
        case "idly":
        case "languidly":
        case "slowly":
        case "tediously":
        str = "bop... bop... bop... bop... bop";
        break;

        case "crazily":
        case "drunkenly":
        case "foolishly":
        case "goofily":
        case "inanely":
        case "maniacally":
        case "psychotically":
        case "rabidly":
        case "randomly":
        case "ridiculously":
        case "stupidly":
        case "wantonly":
        case "zanily":
        play_how += ", whacking them furiously on the sides, top, and bottom";
        n = NAME_TO_RANDOM(adverb, 1999, sound_size);

        str = ({"Wham! ", "Bam! ", "Pow! "})[n % 3] +
            capitalize(implode(Sounds[n..sound_size-1], "-")) +
            "! " + ({"Bam! ", "Wham! "})[n % 2] + "Boom";

        punctuate = "!";
        break;

        case "bluntly":
        case "boldly":
        case "decisively":
        case "forcefully":
        case "grimly":
        case "loudly":
        case "mightily":
        case "powerfully":
        case "tunelessly":
        play_how += ", pounding one drumhead over and over";
        n = NAME_TO_RANDOM(adverb + tp->query_name(), 1999, sound_size);

        str = Sounds[n] + "! " + Sounds[n] + "! " + Sounds[n] + "! " +
            Sounds[n];

        punctuate = "!";
        break;

        case "creatively":
        case "dangerously":
        case "enigmatically":
        case "heroically":
        case "quixotically":
        case "theatrically":
        case "zealously":

        play_how +=
            ({
            ", standing on top of them and playing them with all ten toes",
            " while performing a series of spins and backflips",
            ", jabbing and punching them as if they were a deadly enemy",
            ", striking them with wildly gyrating arm motions"
            })[NAME_TO_RANDOM(adverb + tp->query_name(), 1999, 4)];

        n = NAME_TO_RANDOM(adverb + tp->query_name(), 1999, sound_size / 2);
        str = implode(Sounds[0..0] + Sounds[n..sound_size-1], ", ");
        break;

        case "deliriously":
        case "feverishly":
        case "vigorously":
        str = implode(Sounds, "-");
        punctuate = "!";
        break;

        case "delicately":
        case "gently":
        case "mildly":
        play_how += " with a dainty tapping of the fingertips on the drumhead";
        str = "bip, bip, bip";
        break;

        case "discreetly":
        case "coyly":
        case "nonchalantly":
        case "secretively":
        case "sneakily":
        case "surreptitiously":

        play_how += ", acting as if nobody will notice who's" +
            " making all the noise";

        str = "[" + implode(Sounds[1..6], "-") + "]";
        break;

        case "dwarvishly":
        play_how += ", beating them with both fists";
        str = "bop, bop, POW! Bop, bop, POW";
        punctuate = "!";
        break;

        case "elvishly":
        play_how += ", humming a lilting tune to accompany the drumbeats";
        str = "bippity-bop, bippity-bop, bippity-bippity-bippity-bop";
        break;

        case "endlessly":
        case "eternally":
        case "excessively":
        case "mercilessly":
        case "relentlessly":
        case "unceasingly":

        str = implode(Sounds + Sounds + Sounds + Sounds + Sounds, ", ") +
            ", " +
            ({
            "etc.",
            "and so on and so forth",
            "and so on",
            "ad infinitum",
            "ad nauseam"
            })[NAME_TO_RANDOM(adverb + tp->query_name(), 1999, 5)];

        break;

        case "feebly":
        case "weakly":
        case "meekly":
        play_how += " with just one slight tap of the drumhead";
        str = "bip";
        break;

        case "ironically":
        case "materialistically":
        case "sycophantically":
        case "xenophobically":

        play_how += ", as " + adverb + " as anyone has ever played" +
            " a set of bongos";

        n = NAME_TO_RANDOM(adverb + tp->query_name(), 1999, sound_size-6);

        str =
            Sounds[n] + ({"! ", "? ", "?? ", "; ", "-", "... "})[random(6)] +
            Sounds[n+1] + ({"! ", "? ", "&", "; ", "-", "... "})[random(6)] +
            Sounds[n+2] + ({"! ", "? ", "~", "; ", "-", "... "})[random(6)] +
            Sounds[n+3] + ({"! ", "? ", "&", "; ", "-", "... "})[random(6)] +
            Sounds[n+4] + ({"! ", "? ", "~", "; ", "-", "... "})[random(6)] +
            Sounds[sound_size-1];

        punctuate = "!!!";
        break;

        case "fuzzily":
        case "gratuitously":
        case "lopsidedly":
        case "quizzically":
        case "quackishly":
        case "righteously":
        case "speculatively":
        case "subversively":

        play_how +=
            ({
            " with a curiously compelling rhythm",
            " in both countenance and demeanor",
            ", snorting, blinking, and grimacing",
            ", repeatedly making a sound like a" +
            " custard-filled sock striking the bottom of a barrel"
            })[NAME_TO_RANDOM(adverb + tp->query_name(), 1999, 4)];

        str = implode(Sounds[0..sound_size/2] +
            ({Sounds[0], Sounds[0], Sounds[0]}), ", ");

        break;

        case "gnomishly":
        case "busily":
        str = "BopBopBopBopBopBopBopBopBopBopBopBopBopBopBopBop";
        punctuate = "!";
        break;

        case "hellishly":
        case "devilishly":
        case "evilly":
        case "diabolically":
        case "impishly":
        case "malevolently":
        case "rakishly":
        case "sardonically":
        case "satanically":
        case "subversively":
        case "wickedly":
        n = NAME_TO_RANDOM(adverb + tp->query_name(), 1999, sound_size - 5);
        play_how += ", grinning and cackling occasionally between the beats";
        str = implode(Sounds[n..sound_size] + Sounds[0..n], "! ");
        punctuate = "!";
        break;

        case "hobbitishly":
        case "hungrily":

        play_how += ", thumping them soundly as if trying to shake loose a " +
            ({
            "sandwich",
            "pie",
            "cake",
            "plum pudding",
            "stash of cookies"
            })[NAME_TO_RANDOM(adverb + tp->query_name(), 1999, 5)] +
            " hidden inside";

        str = implode(Sounds[0..sound_size/2], "! ");
        punctuate = "!";
        break;

        case "humanly":
        case "blandly":
        case "normally":
        case "philosophically":
        case "systematically":
        play_how += ", making the sound of one hand drumming";
        str = implode(Sounds[0..3] + Sounds[2..5] + Sounds[4..7], ", ");
        break;

        case "monotonously":
        case "boringly":
        case "wearily":
        str = "bop, bop, bop, bop, bop, bop, bop, bop, bop, bop";
        break;

        case "musically":
        case "tunefully":
        case "symphonically":
        play_how += ", the higher-pitched drum first, and then the lower one";
        str = "bip-bip-bip-bop, bip-bip-bip-bop";
        punctuate = "!";
        break;

        case "obscenely":
        case "indecently":
        case "rudely":
        play_how += " with a body part that was not intended for this purpose";
        str = implode(Sounds[0..1] + Sounds[1..2] + Sounds[2..3], ", ");
        punctuate = "!";
        break;

        case "politely":
        case "diplomatically":
        case "courteously":
        play_how += ", pausing first to ask for everyone's attention";
        str = implode(Sounds[0..3] + Sounds[2..5] + Sounds[4..7], ", ");
        break;

        case "quietly":
        case "faintly":
        play_how += ", just barely tapping the drumheads";
        str = implode(Sounds[0..random(sound_size/2)+2], ", ");
        break;

        case "silently":
        case "noiselessly":
        case "soundlessly":
        str = "  ";
        break;

        case "bizarrely":
        m += 2;
        case "perversely":
        m += 2;
        case "outrageously":
        m += 2;
        case "strangely":
        m += 2;
        case "oddly":
        m += 2;

        play_how +=
            ({
            ", holding them upside-down and whacking" +
            " them with one knee",
            " with both feet and both hands",
            ", beating on them from the inside"
            })[NAME_TO_RANDOM(adverb + tp->query_name(), 1999, 3)];

        str = implode(Sounds[0..m] + Sounds[m-1..m], ", ");
        punctuate = "!";
        break;

        case "aggressively":
        case "bitterly":
        case "cruelly":
        case "emphatically":
        case "firmly":
        case "harshly":
        case "intently":
        case "wildly":
        str = implode(Sounds + Sounds, ", ");
        punctuate = "!";
        break;

        default:

        n = NAME_TO_RANDOM(adverb, 1999, sound_size);
        str = implode(Sounds[n..sound_size] + Sounds[0..n], ", ");
        n = NAME_TO_RANDOM(tp->query_name(), 1999, sound_size);
        str += ", " + Sounds[n] + ", " + Sounds[n];

    }

    write("You play the bongo drums" + play_how + ": " + str + punctuate +
        "\n");

    say(QCTNAME(tp) + " plays " + tp->query_possessive() +
        " bongo drums" + play_how + ": " + str + punctuate + "\n");

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
    add_action(play_bongos, "play");

}
