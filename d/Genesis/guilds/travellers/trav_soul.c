#pragma strict_types
#pragma no_shadow
#pragma save_binary

inherit "/cmd/std/command_driver";
inherit "/d/Earthsea/lib/help";

#include "guild.h"
#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <files.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <adverbs.h>
#include <cmdparse.h>

#define IDEA_FILE TRAVELLERS_LOG_DIR + "ideas"
#define TPPRO this_player()->query_pronoun()
#define TPPOS this_player()->query_possessive()
#define TPOBJ this_player()->query_objective()

string emotes_help();
string male_titles_help();
string female_titles_help();
string carving_help();

nomask void
create()
{
    set_help_type(({ "trav", "traveller", "travellers" }));
    read_help_dir(TRAVELLERS_HELP_DIR);

    add_help("emotes", emotes_help);
    add_help("male titles", male_titles_help);
    add_help("female titles", female_titles_help);
    add_help("carving", carving_help);
}

nomask int
query_cmd_soul()
{
    return 1;
}
 
nomask string
get_soul_id()
{
    return "Traveller soul";
}
 
public mapping
query_cmdlist()
{
    return ([
                 "tahh"       : "tahh",
                 "tassure"    : "tassure",
                 "tboot"      : "tboot",
                 "tbow"       : "tbow",
                 "tcarve"     : "tcarve",
                 "tchin"      : "tchin",
                 "tconcern"   : "tconcern",
                 "tcough"     : "tcough",
                 "tcross"     : "tcross",
                 "tcurse"     : "tcurse",
                 "tdance"     : "tdance",
                 "tdark"      : "tdark",
                 "tdisbelief" : "tdisbelief",
                 "tdiscovery" : "tdiscovery",
                 "tdisdain"   : "tdisdain",
                 "tdizzy"     : "tdizzy",
                 "tdraw"      : "tdraw",
                 "tdrool"     : "tdrool",
                 "tdust"      : "tdust",
                 "texhaust"   : "texhaust",
                 "teye"       : "teye",
                 "tflex"      : "tflex",
                 "tgaze"      : "tgaze",
                 "tgear"      : "tgear",
                 "tglance"    : "tglance",
                 "tglare"     : "tglare",
                 "tgreet"     : "tgreet",
                 "tgrind"     : "tgrind",
                 "thail"      : "thail",
                 "thatred"    : "thatred",
                 "thello"     : "thello",
                 "thmm"       : "thmm",
                 "thop"       : "thop",
                 "thum"       : "thum",
                 "tjump"      : "tjump",
                 "tkiller"    : "tkiller",
                 "tkiss"      : "tkiss",
                 "tlean"      : "tlean",
                 "tlook"      : "tlook",
                 "tluck"      : "tluck",
                 "tmap"       : "tmap",
                 "tmumble"    : "tmumble",
                 "tnap"       : "tnap",
                 "tnod"       : "tnod",
                 "toops"      : "toops",
                 "tpace"      : "tpace",
                 "tpoke"      : "tpoke",
                 "tpuzzled"   : "tpuzzled",
                 "trespect"   : "trespect",
                 "trest"      : "trest",
                 "treverie"   : "treverie",
                 "triffle"    : "triffle",
                 "trun"       : "trun",
                 "tsalute"    : "tsalute",
                 "tscorn"     : "tscorn",
                 "tscratch"   : "tscratch",
                 "tshiver"    : "tshiver",
                 "tshudder"   : "tshudder",
                 "tsing"      : "tsing",
                 "tskip"      : "tskip",
                 "tsmile"     : "tsmile",
                 "tsnarl"     : "tsnarl",
                 "tspit"      : "tspit",
                 "tsquint"    : "tsquint",
                 "tstare"     : "tstare",
                 "tstudy"     : "tstudy",
                 "tswat"      : "tswat",
                 "tsweaty"    : "tsweaty",
                 "tswing"     : "tswing",
                 "ttap"       : "ttap",
                 "ttemper"    : "ttemper",
                 "ttrip"      : "ttrip",
                 "ttug"       : "ttug",
                 "ttwirl"     : "ttwirl",
                 "tugh"       : "tugh",
                 "twatch"     : "twatch",
                 "twave"      : "twave",
                 "twhew"      : "twhew",
                 "twhistle"   : "twhistle",
                 "tyawn"      : "tyawn",
                 "tyell"      :  "tyell",

                 "tidea"      : "_tidea",
                 "tl"         : "_tl",
                 "tlist"      : "_tl",
                 "mtl"        : "_tl",
                 "mtlist"     : "_tl",
                 "tsay"       : "_tsay",

           ]) + help_cmdlist();
}

string *
parse_adverb_with_space(string str, string def_adv, int trail)
{
    string *adv = ::parse_adverb_with_space(str, def_adv, trail);

    if (adv[1] == " ")
    {
        adv[1] = "";
    }

    return adv;
}

/* The following is from the original guild soul.  I don't
 * like the code much, but I don't have time to redo all of the emotes
 * right now.
 */
public string
swap_for_adv(string str, string adv)
{
    return extract(implode(explode(" " + str + " ", "#adv#"), adv), 1, -2);
}
 
public int
default_emote(mixed str)
{
    int options;
    object *oblist;
    string *how = allocate(2);
 
    options = str[1];
 
    notify_fail(str[2]);
 
    if (options & 1)
    {
        how = parse_adverb_with_space(str[0], str[5], str[6]);
        str[0] = how[0];
    }
 
    if (!strlen(how[1]))
        how[1] = "";
    if (!strlen(str[0]))
        if (options & 8)
            return 0;
        else
        {
            write(swap_for_adv(str[3], how[1]));
            if (options & 4)
                all(swap_for_adv(str[4], how[1]));
            else
                allbb(swap_for_adv(str[4], how[1]));
            return 1;
        }
 
    if (options & 2)
        return 0;
 
    oblist = parse_this(str[0], str[7]);
    if (!sizeof(oblist))
        return 0;
 
    actor(swap_for_adv(str[8], how[1]), oblist, swap_for_adv(str[9], how[1]));
    if (options & 4)
    {
        target(swap_for_adv(str[10], how[1]), oblist);
        all2act(swap_for_adv(str[11], how[1]), oblist,
            swap_for_adv(str[12], how[1]));
        return 1;
    }
    targetbb(swap_for_adv(str[10], how[1]), oblist);
    all2act(swap_for_adv(str[11], how[1]), oblist, swap_for_adv(str[12],
        how[1]));
    return 1;
}
 

string
emotes_help()
{
    string *funs = filter(m_values(query_cmdlist()),
        &operator(!=)('_') @ &operator([])(, 0));

    map(sort_array(funs), &call_other(this_object(), , "?"));
    return "";
}

string
male_titles_help()
{
    setuid();
    seteuid(getuid());
    return implode(TRAVELLERS_SHADOW->query_male_titles(), "\n");
}

string
female_titles_help()
{
    setuid();
    seteuid(getuid());
    return implode(TRAVELLERS_SHADOW->query_female_titles(), "\n");
}

string *get_carvings()
{
    string *carvings;

    setuid();
    seteuid(getuid());

    carvings = filter(get_dir(TRAVELLERS_CARVINGS_DIR), &wildmatch("*.c"));
    return map(carvings, &extract(, 0, -3));
}

string
carving_help()
{
    return "Throughout the ages, travellers have passed the time by carving " +
        "small emblems, toys, animals and figures from wood they find on the " +
        "ground.  You too can carve as these travellers did. To carve, you " +
        "should be wielding an edged weapon and have a block of wood.\n" +
        "Carving is not an automatic knowledge, and as such you can only " +
        "carve the things you have been taught.\n\n" +
        "Current carvings available:\n\t" + implode(get_carvings(), "\n\t") + "\n";
}

int
tahh(string str)
{
    if (!strlen(str))
    {
        write("Ahh...you feel enlightened.\n");
        all(" goes Ahh....  " + capitalize(TPPRO) + 
            " must be feeling enlightened.\n");
        return 1;
    }

    if (str == "?")
    {
        write("Tahh\n");
        return 1;
    }

    return 0;
}

int
tassure(string str)
{
    object *oblist;

    notify_fail(capitalize(query_verb()) + " whom?\n");

    if (!strlen(str))
    {
        return 0;
    }

    if (str == "?")
    {    
        write("Tassure <target>\n");
        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[the] %l")))
    {
        return 0;
    }

    actor("You assure", oblist, " that you know where you are.");
    target(" assures you that " + TPPRO + " knows exactly where " +
        TPPRO + " is.", oblist);

    return 1;
}

int
tboot(string str)
{
    if (!strlen(str))
    {
        write("You remove your boot and shake the rocks out.\n");
        allbb(" carefully removes " + TPPOS + " boot and shakes " +
            "the rocks out.");
        return 1;
    }

    if (str == "?")
    {
        write("Tboot\n");
        return 1;
    }

    return 0;
}

int
tbow(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You bow deeply and gracefully, as only a well Travelled " +
            "human could.\n");
        allbb(" bows deeply and gracefully, as only a well Travelled " +
            "human could.\n");
        return 1;
    }

    if (str == "?")
    {
        write("Tbow [<target>]\n");
        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[to] / [before] [the] %l")))
    {
        notify_fail(capitalize(query_verb()) + " before whom?\n");
        return 0;
    }

    actor("You bow deeply and gracefully before", oblist, ", as only " +
        "a well Travelled human could.");
    targetbb(" bows deeply and gracefully before you, as only a well " +
        "Travelled human could.", oblist);
    all2actbb(" bows deeply and gracefully before", oblist, ", as only " +
        "a well Travelled human could.");
    return 1;
}

int
tcarve(string str)
{
    object ob, wood, *weps;
    string file;

    if (!strlen(str))
    {
        notify_fail("Tcarve what?\n");
        return 0;
    }

    if (str == "?")
    {
        write("Tcarve <what>\n");
        return 1;
    }

    if (!(wood = present(CARVE_OBJECT_ID, this_player())))
    {
        write("You search in vain for a piece of wood to carve.\n");
        allbb(" starts fumbling around for something and muttering " +
            "about carving being a good way to pass time.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    file = TRAVELLERS_CARVINGS_DIR + str + ".c";
    if (file_size(file) < 1)
    {
        notify_fail("You don't know how to carve that!\n");
        return 0;
    }

    if (!sizeof(weps = filter(this_player()->query_weapon(-1), 
        &operator(!=)(0) @ &operator(&)(, W_SLASH) @ &->query_dt())))
    {
        write("You don't have anything appropriate to carve with.\n");
        return 1;
    }

    ob = clone_object(file);
    ob->move(this_player(), 1);
    wood->remove_object();

    ob->set_long(ob->query_long() + "The name '" + 
        this_player()->query_name() + "' is carved on it in tiny letters.\n");

    write("You carve the wood into the shape of " + LANG_ADDART(ob->short()) +
          " with your " + weps[0]->short() + ".\n");
    allbb(" carves some wood into the shape of " + LANG_ADDART(ob->short()) +
          " with " + TPPOS + " " + weps[0]->short() + ".");

    return 1;
}

int
tchin(string str)
{
    string *how = parse_adverb_with_space(str, "thoughtfully", 0);
    
    if (!strlen(how[0]))
    {
        write("You rub your chin" + how[1] + ".\n");
        allbb(" rubs " + TPPOS + " chin" + how[1] + ".\n");
        return 1;
    }

    if (how[0] == "?")
    {
        write("Tchin [<adverb>]\n");
        return 1;
    }

    return 0;
}

int
tconcern(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You show genuine concern.\n");
        allbb(" has a look of genuine concern on " + TPPOS + "face.");
        return 1;
    }

    if (str == "?")
    {
        write("Tconcern [<target>]\n");
        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[for] [the] %l")))
    {    
        notify_fail("Show concern for whom?\n");
        return 0;
    }

    actor("You show genuine concern for", oblist, ".");
    targetbb(" shows genuine concern for you.", oblist);
    all2actbb("  shows genuine concern for", oblist, ".");
    
    return 1;
}

int
tcough(string str)
{
    if (!strlen(str))
    {
        write("You almost cough out your lungs.\n");
        all(" coughs violently, attempting to clear " + TPPOS + 
            " throat of trail dust.");
        return 1;
    }

    if (str == "?")
    {
        write("Tcough\n");
        return 1;
    }

    return 0;
}

int
tcross(string str)
{
    if (str == "?")
    {
        write("Tcross\n");
        return 1;
    }

    if (strlen(str))
    {
        return 0;
    }

    write("You cross your fingers, hoping for the best.\n");
    allbb(" crosses " + TPPOS + " fingers, hoping for the best.");
    return 1;
}

int
tcurse(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You curse loudly in fourteen different languages.\n");
        all(" curses loudly in fourteen different languages; " +
            "you feel your vocabularly has improved.");
        return 1;
    }

    if (str == "?")
    {
        write("Tcurse [<target>]\n");
        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
         notify_fail(capitalize(query_verb()) + " at whom?\n");
         return 0;
    }

    actor("You curse loudly at", oblist, ".");
    target(" curses loudly at you.", oblist);
    all2actbb("  curses loudly at", oblist, ".");

    return 1;
}
    
int
tdance(string str)
{
    if (str == "?")
    {
        write("Tdance [<adverb>].\n");
        return 1;
    }

    str = check_adverb_with_space(str, "gracefully");

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail(capitalize(query_verb()) + " how?\n");
        return 0;
    }

    write("You" + str + " perform a dance once taught to you.\n");
    allbb(str + " performs a strange dance that you have never seen " +
        "before.\n");
    return 1;
}

public int
tdark(string str)
{
    if (str == "?")
    {
        write("Tdark\n");
        return 1;
    }

    return default_emote(({ str, 2, "Why should I want to do that?\n",
        "You pensively peer ahead into the distance, preparing to enter " +
        "the heart of darkness.\n", " pensively peers ahead into the " +
        "distance to enter the heart of darkness." }));
}

public int
tdisbelief(string str)
{
    if (str == "?")
    {
        write("Tdisbelief [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 0, "I don't believe you!\n", "You " +
        "cannot believe what is happening here!\n", " stares in disbelief.",
        0, 0, "[at] / [to] / [toward] [the] %l", "You stare at", " in " +
        "disbelief.", " stares at you in disbelief.", " stares at", " in " +
        "disbelief." }));
}

public int
tdiscovery(string str)
{
    if (str == "?")
    {
        write("Tdiscovery\n");
        return 1;
    }

    return default_emote(({ str, 2, "Discover what?\n", 
        "With trembling hands, you pull out a sheet of paper and " +
       "sketch the surroundings on it with a few quick strokes.\n" +
        "What a discovery!\n", " pulls out a sheet of paper and " +
        "sketches " + TPPOS + " surroundings on " +
        "it with a look of pure delight." }));
}

public int
tdisdain(string str)
{
    object *oblist;

    if (str == "?")
    {
        write("Tdisdain <target>\n");
        return 1;
    }

    notify_fail("Show disdain to whom?\n");
    if (!strlen(str))
        return 0;
    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
        return 0;
    if (sizeof(oblist) > 1)
    {
        notify_fail("So venomous is your stare that you can only disdain " +
            "one unfortunate soul at a time!\n");
        return 0;
    }
    if (oblist[0]->query_race_name() == "human")
    {
        write("You should not show disdain to fellow humans.\n");
        return 1;
    }
    actor("You show your complete disdain of", oblist, " a non-human.");
    targetbb(" gives you a look of complete and utter disdain.", oblist);
    all2actbb(" gives ", oblist, " a look of complete and utter disdain.");
    return 1;
}

public int
tdizzy(string str)
{
    if (str == "?")
    {
        write("Tdizzy\n");
        return 1;
    }

    return default_emote(({ str, 2, "Dizzy what?\n", "You feel momentarily " +
        "dizzy after your long travels.\n", " looks momentarily dizzy, " +
        "apparently tired after " + TPPOS + " long travels." }));
}

public int
tdraw(string str)
{
    if (str == "?")
    {
        write("Tdraw\n");
        return 1;
    }

    return default_emote(({ str, 2, "Draw what?\n", "You draw a map in " +
        "the dust with your walking stick.\n", " draws a map in the " +
        "dust with " + TPPOS + " walking stick." }));
}

public int
tdrool(string str)
{
    if (str == "?")
    {
        write("Tdrool\n");
        return 1;
    }

    return default_emote(({ str, 2, "Drool what?\n", "You drool all " +
        "over yourself.\n", " drools all over " + TPOBJ + "self." }));
}

public int
tdust(string str)
{
    if (str == "?")
    {
        write("Tdust\n");
        return 1;
    }

    return default_emote(({ str, 2, "Dust what?\n", "You clean yourself of " +
        "trail dust.\n", " wipes off the dust from the trail that has " +
        "clung to " + TPPOS + " clothes." }));
}

public int
texhaust(string str)
{
    if (str == "?")
    {
        write("Texhaust\n");
        return 1;
    }

    return default_emote(({ str, 6, "So exhausted you're hallucinating?\n", 
        "You take a deep breath and lean on your trusty walking stick.\n",
        " sighs deeply and attempts to count the miles " + TPPRO +
        " has travelled this day while leaning on " + TPPOS + " walking " +
        "stick." }));
}

public int
teye(string str)
{
    if (str == "?")
    {
        write("Teye [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 0, "Eye whom?\n", "You steadily examine " +
        "your surroundings with the skill of an experienced trailblazer.\n",
        " settles back and begins to study the land with rough, weathered " +
        "eyes.", 0, 0, "[the] %l", "You carefully study", " with knowing " +
        "eyes.", " studies you through travelled eyes.", " studies",
        " through travelled eyes." }));
}

public int
tflex(string str)
{
    if (str == "?")
    {
        write("Tflex [<adverb>] [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 1, "Flex who how?\n", "You flex your " +
        "muscles#adv#, letting everyone know who is boss here.\n",
        " flexes " + TPPOS + " muscles#adv#, letting everyone know " +
        "who is boss here.", "menacingly", 1, "[the] %l",
        "You flex your muscles at", "#adv#.", " flexes " + TPPOS +
        " muscles#adv# at you.", " flexes " + TPPOS + " muscles at ",
        "#adv#." }));
}

public int
tgaze(string str)
{
    if (str == "?")
    {
        write("Tgaze\n");
        return 1;
    }

    return default_emote(({ str, 2, "Gaze how?\n", "You gaze into the " +
        "distance, thinking of old adventures.\n", " gazes into the " +
        "distance, apparently thinking of old adventures." }));
}

public int
tgear(string str)
{
    if (str == "?")
    {
        write("Tgear\n");
        return 1;
    }

    return default_emote(({ str, 2, "Check your gear how?\n", "You " +
        "systematically check your gear; you feel ready to travel again.\n",
        " thoroughly examines every piece of " + TPPOS + " equipment " +
        "to prepare for " + TPPOS + " long journey ahead." }));
}

public int
tglance(string str)
{
    if (str == "?")
    {
        write("Tglance [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 0, "Glance at whom?\n",
        "You glance up from your maps.\n", " glances up from " +
         TPPOS + " maps.", 0, 0, "[at] / [to] / [toward] [the] %l", "You glance at",
        ".", " glances at you.", "glances at",
        "." }));
}

public int
tglare(string str)
{
    if (str == "?")
    {
        write("Tglare [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 0, "Glare at whom?\n",
        "You give everyone a nasty look.\n",
        " looks around with a nasty expression on " + TPPOS +
        " face.", 0, 0, "[to] / [toward] / [at] [the] %l",
         "You give", " nasty looks.",
        " gives you nasty looks.", " gives", " nasty looks." }));
}

public int
tgreet(string str)
{
    if (str == "?")
    {
        write("Tgreet [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 4, "Greet whom?\n", 
        "You raise your stick in greeting to everyone.\n",
        " raises " + TPPOS + " stick in general greeting.",
        0, 0, "[the] %l", "You raise your stick in " +
        "greeting toward", ".",
        " raises " + TPPOS + " stick toward you in greeting.",
        " raises " + TPPOS + " stick toward", " in greeting." }));
}

public int
tgrind(string str)
{
    if (str == "?")
    {
        write("Tgrind [<adverb>] [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 5, "Grind [how] [at whom]?\n",
        "You grind your teeth together#adv# in frustration.\n",
        " grinds " + TPPOS + " teeth together#adv# in frustration.",
        "noisily", 0, "[to] / [toward] / [at] [the] %l",
        "You grind your teeth together#adv#, frustrated with",
        ".", " grinds " + TPPOS + " teeth together#adv#.\n" +
        capitalize(TPPOS) + " seems frustrated with you.",
        " grinds " + TPPOS + " teeth together#adv#, apparently " +
        "frustrated with", "." }));
}

public int
thail(string str)
{
    string mess;

    if (str == "?")
    {
        write("Thail <target>\n");
        return 1;
    }

    mess = "Greetings, how have your travels treated you?";
    return default_emote(({ str, 12, "Who did you want to hail?\n", 0, 0,
        0, 0, "[the] %l", "You shake", "'s hand and say: " + mess,
        " shakes your hand and says: " + mess, " shakes", "'s hand and " +
        "says: " + mess }));
}

public int
thatred(string str)
{
    if (str == "?")
    {
        write("Thatred <target>\n");
        return 1;
    }

    return default_emote(({ str, 8, "Show hatred toward whom?\n", 0, 0, 0,
        0, "[the] %l", "You stare at", " with absolute hatred in your " +
        "eyes.", " stares at you with absolute loathing.", " stares at",
        " with absolute loathing in " + TPPOS + " eyes." }));
}

public int
thello(string str)
{
    if (str == "?")
    {
        write("Thello [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 4, "Hello what?\n", "You say hello in " +
        "several languages.\n", " says hello in several languages.",
        0, 0, "[at] / [to] / [toward] [the] %l", "You say hello " +
        "to", " in several languages.", " says hello to you in " +
        "several languages.", " says hello to", " in several " +
        "languages." }));
}

public int
thmm(string str)
{
    if (str == "?")
    {
        write("Thmm [<adverb>] [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 5, "Hmm how at whom?\n", "You go hmm " +
        "and rub your thumb along your stick#adv#.\n", " goes hmm and " +
        "rubs " + TPPOS + " thumb along " + TPPOS + " stick#adv#.",
        "thoughtfully", 0, "[to] / [toward] / [at] [the] %l",
        "You go hmm at", " and rub your stick#adv#.", " goes hmm at you " +
        "and rubs " + TPPOS + " stick#adv#.", " goes hmm at", " and " +
        "rubs " + TPPOS + " stick#adv#." }));
}

public int
thop(string str)
{
    if (str == "?")
    {
        write("Thop\n");
        return 1;
    }

    return default_emote(({ str, 2, "Hop how?\n", "You hop from foot " +
        "to foot, growing impatient.\n", " hops from foot to foot, clearly " +
        "impatient." }));
}

public int
thum(string str)
{
    if (str == "?")
    {
        write("Thum [<adverb>] [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 5, "Hum [how] [to whom]?\n",
        "You hum a melody#adv# as you walk.\n", " hums a melody#adv# as " +
        TPPRO + " walks", "quietly", 0, "[to] / [at] / [toward] [the] %l",
        "You hum a melody#adv# for", ".", " hums a melody#adv# for you.",
        " hums a melody#adv# for", "." }));
}

public int
tjump(string str)
{
    if (str == "?")
    {
        write("Tjump\n");
        return 1;
    }

    return default_emote(({ str, 2, "Jump what?\n", "You put your stick on "+
        "the ground and jump over it.\n", " jumps over " + TPPOS + " stick." }));
}

public int
tkiller(string str)
{
    if (str == "?")
    {
        write("Tkiller\n");
        return 1;
    }

    return default_emote(({ str, 6, "Killer what?\n",
        "You twist your face into what you hope is the expression " +
        "of a grim and hardened killer and quickly turn around just " +
        "in case a horibble monster happens to lurk behind you.\n",
        " twists " + TPPOS + " face into a fierce expression and " +
        "spins quickly around to look behind " + TPOBJ + "self." }));
}

public int
tkiss(string str)
{
    if (str == "?")
    {
        write("Tkiss <target>\n");
        return 1;
    }

     return default_emote(({ str, 8, "Throw a kiss to whom?\n", 0, 0, 0, 0,
        "[the] %l", "You throw an air kiss to", " in promise of a quick return.",
        " throws you an air kiss as promise of " + TPPOS + " quick return.", " throws",
        " an air kiss as promise of a quick return." }));
}

public int
tlean(string str)
{
    if (str == "?")
    {
        write("Tlean\n");
        return 1;
    }

    return default_emote(({ str, 2, "Lean on what?\n", "Aahh, how " +
        "relaxing!\n", " leans gently on " + TPPOS + " walking stick, " +
        "apparently very tired." }));
}

public int
tlook(string str)
{
    if (str == "?")
    {
        write("Tlook\n");
        return 1;
    }

    return default_emote(({ str, 2, "Look what?\n", "You look " +
        "wistfully into the distance and reflect on your years of " +
        "travelling.\n", " turns " + TPPOS + " head and looks wistfully " +
        "into the distance." }));
}

public int
tluck(string str)
{
    if (str == "?")
    {
        write("Tluck <target>\n");
        return 1;
    }

    return default_emote(({ str, 8, "Wish luck to whom?\n", 0, 0, 0, 0,
        "[to] / [at] / [toward] [the] %l", "You wish", " good luck on the " +
        "coming journey.", " wishes you luck on your coming journey.",
        " wishes", " luck on the coming journey." }));
}

public int
tmap(string str)
{
    if (str == "?")
    {
        write("Tmap [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 0, "Wave map at whom?\n", "You unroll " +
        "your map and try to decide where to go.\n", " unrolls a map and " +
        "tries to decide where to go.", 0, 0, "[at] / [to] / [toward] " +
        "[the] %l", "You wave your map under", "'s nose.", " waves " +
        TPPOS + " map under your nose.", " waves " + TPPOS + " map " +
        "under", "'s nose." }));
}

public int
tmumble(string str)
{
    if (str == "?")
    {
        write("Tmumble\n");
        return 1;
    }

    return default_emote(({ str, 6, "Mumble how?\n", "You mumble something " +
        "about being disappointed.\n", " mumbles something about being " +
        "disappointed." }));
}

public int
tnap(string str)
{
    if (str == "?")
    {
        write("Tnap\n");
        return 1;
    }

    return default_emote(({ str, 2, "Nap how?\n", "You lie down and take " +
        "a nap.\n", " picks a comfortable spot, lies down, and takes a " +
        "nap." }));
}

public int
tnod(string str)
{
    if (str == "?")
    {
        write("Tnod [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 0, "Nod at whom?\n", "You nod your head " +
        "in assent.\n", " nods " + TPPOS + " head in assent.", 0, 0,
        "[to] / [toward] / [at] [the] %l", "You nod your head at",
        " signaling your assent.", " nods " + TPPOS + " head " +
        "at you, signaling " + TPPOS + " assent.",
        " nods " + TPPOS + " head at", " signaling " + TPPOS +
        " assent." }));
}

public int
toops(string str)
{
    if (str == "?")
    {
        write("Toops\n");
        return 1;
    }

    return default_emote(({ str, 6, "Oops how?\n", "Eyes darting around to check if " +
        "anyone saw it, you quickly turn your map upside up and assume " +
        "an innocent expression on your face.\n", " turns " +
        TPPOS + " map over looking intensely at the surrounding area." }));
}

public int
tpace(string str)
{
    if (str == "?")
    {
        write("Tpace [<adverb>]\n");
        return 1;
    }

    return default_emote(({ str, 3, "Pace how?\n",
        "You pace#adv# back and forth.\n", " paces" +
        "#adv# back and forth", "energetically", 0 }));
}

public int
tpoke(string str)
{
    if (str == "?")
    {
        write("Tpoke [<target>}\n");
        return 1;
    }

    return default_emote(({ str, 4, "Poke whom?\n", "You hit your stick " +
        "on the ground, making a lot of racket!\n", " raps " + TPPOS +
        "stick on the ground, making a lot of racket!\n", 0, 0, "[the] %l",
        "You poke", " in the ribs with your weather beaten walking stick.",
        " pokes you in the ribs with " + TPPOS + " weather beaten " +
        "walking stick.", " pokes", " in the ribs with " + TPPOS + " " +
        "weather beaten walking stick." }));
}

public int
tpuzzled(string str)
{
    if (str == "?")
    {
        write("Tpuzzled [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 0, "Do what?\n", "You look at the sky, " +
        "puzzled at its very existence.\n", " looks skyward, a look of " + 
        "bewilderment on " + TPPOS + " face.", 0, 0, "[at] / [to] /" +
        "[toward] [the] %l", "You stare at", " obviously puzzled.",
        " looks at you, obviously puzzled. Maybe you aren't making sense.",
        " looks at", ", obviously puzzled" }));
}

public int
trespect(string str)
{
    object *oblist;

    if (str == "?")
    {
        write("Trespect <target>\n");
        return 1;
    }
 
    notify_fail("Wrong, try again. \n");
    if (!strlen(str))
        return 0;
 
    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
        return 0;
    if (sizeof(oblist) > 1)
        actor("You look respectfully at", oblist, ", knowing the wonders " +
            "their eyes have seen.");
        else
            actor("You look respectfully at", oblist, ", knowing the " +
                "wonders " + oblist[0]->query_possessive() + " eyes have " +
                "seen.");
    all2actbb(" looks respectfully at", oblist, ".");
    targetbb(" looks respectfully at you, knowing all the things " +
        this_player()->query_pronoun() + " has yet to see.", oblist);
    return 1;
}

public int
trest(string str)
{
    if (str == "?")
    {
        write("Trest\n");
        return 1;
    }

    return default_emote(({ str, 2, "Rest how?\n", 
        "You rest your chin upon your stick, weary from the day's travels.\n",
     " rests " + TPPOS + " chin on " + TPPOS + " stick, weary from " +
    "the day's travels." }));
}

public int
treverie(string str)
{
    if (str == "?")
    {
        write("Treverie\n");
        return 1;
    }

    return default_emote(({ str, 2, "Remember what?\n", "You close your " +
        "eyes and reflect on your life as a Traveller.\n", "'s eyes " +
        "close momentarily as " + TPPRO + " fondly remembers " + TPPOS +
        " first journey as a Traveller." }));
}

public int
triffle(string str)
{
    if (str == "?")
    {
        write("Triffle\n");
        return 1;
    }

    return default_emote(({ str, 6, "Riffle through what?\n", "You " +
        "quickly riffle through your maps and take out a different one.\n",
        " riffles through " + TPPOS + " maps, apparently finding the " +
        "correct one." }));
}

public int
trun(string str)
{
    if (str == "?")
    {
        write("Trun\n");
        return 1;
    }

    return default_emote(({ str, 2, "Run where?\n", "You wander aimlessly " +
        "in a circle; you feel rather dumb.\n", " wanders around in " +
        "circles, getting nowhere fast." }));
}

public int
tsalute(string str)
{
    if (str == "?")
    {
        write("Tsalute [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 0, "Salute whom?\n", "You salute " +
        "everyone in the manner of a traveller.\n", " gives a swift " +
        "clean salute in the manner of a traveller.", 0, 0, "[the] %l",
        "You salute", " in the manner of a traveller.", " gives you a " +
        "swift clean salute in the manner of a traveller.", " gives",
        " a swift clean salute in the manner of a traveller." }));
}

public int
tscorn(string str)
{
    object *oblist;
    string n = "";

    if (str == "?")
    {
        write("Tscorn <target>\n");
        return 1;
    }
 
    notify_fail("Heap scorn on whom?\n");
    if (!strlen(str))
        return 0;
    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
        return 0;
    if (sizeof(oblist) > 1)
    {
        notify_fail("You can't scorn that many people at once and let them " +
            "all know how deeply you despise them.\n");
        return 0;
    }
    switch(oblist[0]->query_race_name())
    {
        case "human" : notify_fail("You should not scorn other humans.\n");  
                       return 0;
        case "elf": n = " an elf"; return 1;
        default: n = " a " + oblist[0]->query_race_name();
    }
    actor("You scorn", oblist, " because " + oblist[0]->query_pronoun() +
        " is" + n + ".");
    all2actbb(" scorns", oblist, " because " + oblist[0]->query_pronoun() +
        " is" + n + ".");
    targetbb(" scorns you because you are" + n + ".\n", oblist);
    return 1;
}

public int
tscratch(string str)
{
    if (str == "?")
    {
        write("Tscratch <message>\n");
        return 1;
    }

    if (!strlen(str)) {
        notify_fail("What wasn't here the last time you were?\n");
        return 0;
    }

    write("You scratch your head and look at the " + str + ". You " +
        "are quite sure it wasn't here the last time you visited " +
        "this place.\n");
    allbb(" scratches " + TPPOS + " head and stares at the " + str +
        ", seemingly quite sure it wasn't here the last time " +
          TPPRO + " was in this place.");
    return 1;
}

public int
tshiver(string str)
{
    if (str == "?")
    {
        write("Tshiver\n");
        return 1;
    }

    return default_emote(({ str, 2, "Shiver how?\n", "You wrap your " +
        "cloak more tightly around yourself.\n", " shivers, pulling " +
        TPPOS + " cloak more tightly around " + TPOBJ + "self " +
        "as " + TPPRO + " remembers " + TPPOS + " travels through the " +
        "Northern Waste Lands." }));
}

public int
tshudder(string str)
{
    if (str == "?")
    {
        write("Tshudder\n");
        return 1;
    }

    return default_emote(({ str, 2, "Shudder from what?\n", "Yikes! That " +
        "was scary.\n", " shudders, remembering some terrible sight that " +
        TPPRO + " saw on one of " + TPPOS + " many journies as a " +
        "traveller." }));
}

public int
tsing(string str)
{
    if (str == "?")
    {
        write("Tsing\n");
        return 1;
    }

    return default_emote(({ str, 6, "Sing how?\n", "You sing a " +
        "song about the joys of travelling.\n",
        " sings a song about the joys of travelling." }));
}

public int
tskip(string str)
{
    if (str == "?")
    {
        write("Tskip\n");
        return 1;
    }

    return default_emote(({ str, 2, "Skip how?\n", "You get a little skip " +
        "in your step.\n", " gets a little skip in " + TPPOS + " step." }));
}

public int
tsmile(string str)
{
    if (str == "?")
    {
        write("Tsmile [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 0, "Smile at whom?\n", "You smile like " +
        "an experienced Traveller.\n", " smiles like an experienced " +
        "Traveller.", 0, 0, "[at] / [to] / [toward] [the] %l", "You smile " +
        "at", " like an experienced Traveller.", " smiles at you like " +
        "an experienced Traveller.", " smiles at", " like an experienced " +
        "Traveller." }));
}

public int
tsnarl(string str)
{
    mixed *oblist;
    string wanttosay;

    if (str == "?")
    {
        write("Tsnarl [<target>] [<message>]\n");
        return 1;
    }

    if (!strlen(str))
    {
        write("You snarl.\n");
        all(" snarls.");
        return 1;
    }
    parse_command(str, all_inventory(environment(this_player())) - 
        ({ this_player() }), "[at] / [to] / " +
        "[toward] [the] %l %s", oblist, wanttosay);

    if (!sizeof(oblist))
    {
        write("You snarl " + str + "\n");
        all(" snarls: " + str);
        return 1;
    }

    oblist = NORMAL_ACCESS(oblist, 0, 0);
    if (!strlen(wanttosay))
    {
        actor("You snarl at", oblist, ".");
        target("'s face contorts in rage and " + TPPRO + " snarls at you.",
            oblist);
        all2act(" snarls at", oblist, ", " + TPPOS + " face contorted in rage.");
    }
    else
    {
        actor("You snarl at", oblist, ": " + wanttosay);
        target(" snarls at you: " + wanttosay, oblist);
        all2act(" snarls at", oblist, ": " + wanttosay);
    }

    return 1;
}

public int
tspit(string str)
{
    if (str == "?")
    {
        write("Tspit [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 4, "Spit at whom?\n", "You show everyone " +
        "what your lungs are capable of!\n", " hawks up a glob of phlegm " +
        "and spits it an amazing distance.", 0, 0, "[at] / [to] / " +
        "[toward] [the] %l", "You spit your phlegm on", ".", " hawks up " +
        "a glob of phlegm and spits it directly on your shoe.", " spits " +
        "phlegm on", "'s shoe." }));
}

public int
tsquint(string str)
{
    if (str == "?")
    {
        write("Tsquint\n");
        return 1;
    }

    if (!strlen(str))
        str = "toward the sun";
    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You can't get your bearings inside.\n");
        return 0;
    }
    return default_emote(({ "", 2, "Squint where?\n", "You turn " +
        "to face " + str + " and squint your eyes to gain your " +
        "bearings.\n", " turns to face " + str + " and squints into " +
        "the distance to assure " + TPOBJ + "self of " + TPPOS +
        " bearings." }));
}

public int
tstare(string str)
{
    if (str == "?")
    {
        write("Tstare [<adverb>] <target>\n");
        return 1;
    }

    return default_emote(({ str, 13, "Stare [how] at whom?\n", 0,
        0, "malevolently", 0, "[to] / [toward] / [at] [the] %l",
        "You stare#adv# at", " for suggesting you might be lost.",
        " stares#adv# at you for suggesting " + TPPRO + " might be lost.",
        " stares#adv# at", " for suggesting " + TPPRO + " might be lost." }));
}

public int
tstudy(string str)
{
    if (str == "?")
    {
        write("Tstudy\n");
        return 1;
    }

    return default_emote(({ str, 2, "Study what?\n", "You search your " +
        "maps for clues concerning your location.\n", " looks intently " +
        "at " + TPPOS + " maps, glances around the area, then back at " +
        TPPOS + " maps." }));
}

public int
tswat(string str)
{
    if (str == "?")
    {
        write("Tswat <target>\n");
        return 1;
    }

    return default_emote(({ str, 8, "You haven't picked the stinker.\n",
        0, 0, 0, 0, "[the] %l", "You swat at some imaginary flies around",
        ". (whew! they stink!)", " swats at some imaginary flies, " +
        "implying that your odor is severe.", " implies that", " needs " +
        "to take a bath by swatting at imaginary flies." }));
}

public int
tsweaty(string str)
{
    if (str == "?")
    {
        write("Tsweaty\n");
        return 1;
    }

    return default_emote(({ str, 2, "Sweaty how?\n", "You wipe the sweat " +
        "from your brow.\n", " wipes the sweat from " + TPPOS +
        " brow." }));
}

public int
tswing(string str)
{
    object *oblist;

    if (str == "?")
    {
        write("Tswing [<target>]\n");
        return 1;
    }
 
    notify_fail("Swing your stick at whom?\n");
 
    if (!strlen(str))
    {
        allbb(" swings " + this_player()->query_possessive() + " stick " +
            "violently.");
        write("You swing your stick violently.\n");
        return 1;
    }
 
    oblist = parse_this(str, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;
 
    actor("You swing your stick at", oblist, " almost hitting " +
    (sizeof(oblist) > 1 ? "them" : oblist[0]->query_objective()) + ".");
    all2actbb(" swings " + this_player()->query_possessive() + " stick at",
        oblist, " violently.");
    targetbb(" swings " + this_player()->query_possessive()
        + " stick at you brushing the tip of your nose.", oblist);
    return 1;
}

public int
ttap(string str)
{
    if (str == "?")
    {
        write("Ttap [<adverb>] [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 5, "Tap what?\n", "You tap your " +
        "stick on the ground#adv# attempting to gain everyone's " +        
        "attention.\n", " taps " + TPPOS + " weather beaten walking " +
        "stick#adv# on the ground, clearly attempting to gain some " +
        "recognition.", "impatiently", 1, "[the] %l", "You tap",
        " on the shoulder#adv#.", " taps you on the shoulder#adv# with " +
        TPPOS + " weather beaten walking stick.", " taps", " on the " +
        "shoulder#adv# with " + TPPOS + " weather beaten walking " +
        "stick." }));
}

public int
ttemper(string str)
{
    if (str == "?")
    {
        write("Ttemper\n");
        return 1;
    }

    return default_emote(({ str, 2, "You seem to be so mad you can't even " +
        "type.\n", "Grrrr!\n", " leaves teeth marks in " + TPPOS +
        " walking stick as " + TPPRO + " bites into it in total rage." }));
}

public int
ttrip(string str)
{
    if (str == "?")
    {
        write("Ttrip [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 0, "What was that?\n", "Tired from your " +
        "days of walking, you stagger forward, trip, and fall to the " +
        "ground.\n", " staggers forward, then abruptly trips and falls to " +
        "the ground.", 0, 0, "[at] / [to] / [toward] [the] %l",
        "Tired from days of walking, you stagger and trip, falling onto",
        ".", ", obviously tired, trips and falls onto you.",
        " trips and falls on", "." }));
}

public int
ttug(string str)
{
    if (str == "?")
    {
        write("Ttug [<adverb>]\n");
        return 1;
    }

    return default_emote(({ str, 3, "Tug your ear how?\n",
        "You tug your ear#adv#.\n", " tugs#adv# on " + TPPOS + " ear.",
        "nervously", 0 }));
}

public int
ttwirl(string str)
{
    if (str == "?")
    {
        write("Ttwirl\n");
        return 1;
    }

    return default_emote(({ str, 2, "Twirl your stick how?\n", "You twirl " +
        "your walking stick out of pure boredom.\n", " twirls " + TPPOS +
        " walking stick in a flashy display of skill. You do not feel as " +
        "though you could accomplish such a feat." }));
}

public int
tugh(string str)
{
    if (str == "?")
    {
        write("Tugh\n");
        return 1;
    }

    return default_emote(({ str, 6, "Ugh how?\n", "You go ugh!\n",
        " goes ugh!" }));
}

public int
twatch(string str)
{
    if (str == "?")
    {
        write("Twatch [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 0, "Watch whom?\n", "You slowly look " +
        "around.\n", " looks around carefully.", 0, 0, "[the] %l", "You watch",
        " suspiciously.", " watches you suspiciously.", " watches",
        " suspiciously." }));
}

public int
twave(string str)
{
    if (str == "?")
    {
        write("Twave [<adverb>] [<target>]\n");
        return 1;
    }

    return default_emote(({ str, 5, "Wave how to whom?\n", "You wave" +
         "#adv# at everyone, saying 'Until we meet again!'\n",
        " waves#adv# and says 'Until we meet again!'", "briefly", 0,
        "[to] / [toward] / [at] [the] %l", "You wave#adv# at",
        ", saying 'Until we meet again!'", " waves#adv# at you " +
        "and says 'Until we meet again!'", " waves#adv# at",
        ", saying 'Until we meet again!'" }));
}

public int
twhew(string str)
{
    if (str == "?")
    {
        write("Twhew\n");
        return 1;
    }

    return default_emote(({ str, 6, "Whew how?\n", "You wipe the sweat off " +
        "of your brow, shaken after surviving another near-death " +
        "experience.\n", " wipes the sweat off of " + TPPOS + " brow, " +
        "shaken after having survived yet once more." }));
}

public int
twhistle(string str)
{
    if (str == "?")
    {
        write("Twhistle\n");
        return 1;
    }

    return default_emote(({ str, 6, "Whistle how?\n", "You begin to " +
        "whistle a nice walking tune and quicken your pace.\n", " whistles " +
        "a little tune and quickens " + TPPOS + " pace." }));
}

public int
tyawn(string str)
{
    if (str == "?")
    {
        write("Tyawn [<adverb>]\n");
        return 1;
    }

    return default_emote(({ str, 3, "Yawn how?\n", "You yawn#adv# " +
        "and sing a song about a far away land you once visited.\n",
        " yawns#adv#, singing a song about a far away land " + TPPRO +
        " once visited.", "tiredly", 0 }));
}

public int
tyell(string str)
{
    if (str == "?")
    {
        write("Tyell\n");
        return 1;
    }

    return default_emote(({ str, 6, "Yell how?\n", "You yell out your " +
        "happiness.\n", " yells out " + TPPOS + " happiness." }));
}

void write_msg(string str)
{
    setuid();
    seteuid(getuid());
    write_file(IDEA_FILE, sprintf("\n%-13s (%s)\n%s\n", 
        capitalize(this_player()->query_real_name()), ctime(time()), str));

    write("Ok.\n");
}
       
int
_tidea(string str)
{
    if (strlen(str))
    {
       if (str == "?")
       {
           write("Tidea [<message>]\n");
           return 1;
       }

       write_msg(str);
       return 1;
    }

    setuid();
    seteuid(getuid());

    clone_object(EDITOR_OBJECT)->edit("done", "");
    return 1;
}

void done(string str)
{
    if (!strlen(str))
    {
        write("Aborted.\n");
        return;
    }

    write_msg(str);
}
    
int
_tsay(string str)
{
    int i, skill;
    object *others;

    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (str == "?")
    {
        write("Tsay <message>\n");
        return 1;
    }

    if (this_player()->query_skill(SS_LANGUAGE) < 15)
    {
        write("Speaking the ancient road language of the Travellers " +
            "requires better knowledge of languages.\n");
        return 1;
    }

    if (this_player()->query_option(OPT_ECHO))
    {
        write("You speak in the road language of the Travellers.\nYou say: " + 
            str + "\n");
    }
    else
    {
        write("Ok.\n");
    }

    others = all_inventory(environment(this_player())) - ({ this_player() });
    for (i = 0; i < sizeof(others); i++) 
    {
        if (!interactive(others[i]))
        {
            continue;
        }
    
        skill = others[i]->query_skill(SS_LANGUAGE);
        if ((IS_MEMBER(others[i]) && (skill > 19)) || (skill > 60))
        {
            tell_object(others[i], this_player()->query_The_name(others[i]) +
                " speaks in the language of the Travellers.\n" + 
                capitalize(TPPRO) + " says: " + str + "\n");
        }
        else
        {
            tell_object(others[i], this_player()->query_The_name(others[i]) +
                " says something in a strange language.\n");
        }
    }
  
    return 1;
}

                 
#define flagged(x,y) ((strlen(x) && (member_array(y, explode(x, "")) != -1)))
 
int sort_names(object ob1, object ob2)
{
    string a = ob1->query_real_name(), b = ob2->query_real_name();
    return ((a == b) ? 0 : ((a < b) ? -1 : 1));
}

int
_tl(string str)
{
    int sw, i;
    object *members;
    string list, title;
 
    if (str == "?")
    {
        write("(m)tl [mwn]\n");
        return 1;
    }
    
    sw = this_player()->query_option(OPT_SCREEN_WIDTH);
    sw = (sw ? sw - 3 : 77);
 
    members = filter(users(), &->query_guild_member(GUILD_NAME));
 
    if (flagged(str, "m"))
        members = filter(members, &not() @ &->query_wiz_level());
    else if (flagged(str, "w"))
        members = filter(members, &->query_wiz_level());
 
    if (!this_player()->query_wiz_level())
    {
        members = filter(members, 
            &operator(>=)(this_player()->query_prop(LIVE_I_SEE_INVIS)) @
            &->query_prop(OBJ_I_INVIS));
    }
 
    if (!sizeof(members))
    {
        write("There are no Travellers of that kind abroad.\n");
        return 1;
    }
 
    write("The following Travellers are logged currently abroad:\n");
 
    members = sort_array(members, sort_names);
 
    if (flagged(str, "n"))
        list = sprintf("%-*#s\n", sw, 
            implode(map(members, &->query_name()), "\n"));
    else
    {
        list = "";
        for (i = 0; i < sizeof(members); i++)
        {
            title = members[i]->query_guild_title_race();

            if (strlen(title))
            {
                title = " the " + title;
            }

            title = members[i]->query_name() + title;
            list += implode(explode(break_string(title, sw), "\n"), 
                "\n    ") + "\n";
        }
    }

    if (query_verb()[0] == 'm')
    {
        this_player()->more(list);
    }
    else
    {
        write(list);
    }
 
    return 1;
}
 
#undef flagged(x,y)
