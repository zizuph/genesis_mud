#pragma strict_types

inherit "/cmd/std/command_driver";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Roke/varl/atuan/cape/guild/default.h"

#define HELP_FILE "BLAH"
#define MORE_OBJ "BLAH"

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Traveller"; }

public mapping
query_cmdlist()
{
    return ([
#include "tcommands.h"
        ]);
}

public int
e_tsmile(string arg)
{
    object *oblist;

    notify_fail("Smile at who?\n");

    if (!strlen(arg))
    {
        allbb(" smiles like an experienced Traveller.");
        write("You smile like an experienced Traveller.\n");
        return 1;
    }

    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;

    actor("You smile at", oblist, " like an experienced Traveller.");
    all2actbb("smiles at", oblist, " like an experienced Traveller.");
    targetbb(" smiles at you like an experienced Traveller.", oblist);
    return 1;
}

public int
e_tlook(string arg)
{
    notify_fail("Tlook what?\n");
    if (strlen(arg))
        return 0;

    allbb(" turns " + this_player()->query_possessive() + " head and looks " +
        "wistfully into the distance.");
    write("You look wistfully into the distance and reflect on your years " +
        "of travelling.\n");
    return 1;
}

public int
e_trun(string arg)
{
    notify_fail("Trun where?\n");
    if (strlen(arg))
        return 0;

    allbb(" wanders around in circles, getting nowhere fast.");
    write("You wander aimlessly in a circle, you feel rather dumb.\n");
    return 1;
}

public int
e_twhistle(string arg)
{
    notify_fail("Whistle how?\n");
    if (strlen(arg))
        return 0;

    all(" whistles a little tune and begins to quicken " + 
        this_player()->query_possessive() + " pace.");
    write("You begin to whistle a nice walking tune and quicken your " +
        "pace.\n");
    return 1;
}

public int
e_tgear(string arg)
{
    notify_fail("Tgear what?\n");
    if (strlen(arg))
        return 0;

    all(" thoroughly examines every piece of " + 
        this_player()->query_possessive() + " equipment to prepare for " + 
        this_player()->query_possessive() + " long journey ahead.");
    write("You systematically check your gear; you feel ready to travel " +
        "again.\n");
    return 1;
}

public int
e_tcough(string arg)
{
    notify_fail("Tcough what?\n");
    if (strlen(arg))
        return 0;

    all(" coughs violently, attempting to clear " + 
        this_player()->query_possessive() + " throat of trail dust.");
    write("You almost cough out your lungs!\n");
    return 1;
}

public int
e_tboot(string arg)
{
    notify_fail("Do what with your boot?\n");
    if (strlen(arg))
        return 0;

    all(" carefully removes " + this_player()->query_possessive() + " boot " +
        "and attempts to shake the rocks out of it.");
    write("Boy your feet smell great! To you anyway.\n");
    return 1;
}

public int
e_tlean(string arg)
{
    notify_fail("Lean on what?\n");
    if (strlen(arg))
        return 0;

    all(" leans gently on " + this_player()->query_possessive() + " " +
        "walking stick, apparently very tired.");
    write("Aahh, how relaxing!\n");
    return 1;
}

public int
e_tdance(string arg)
{
    notify_fail("from " + this_player()->query_possessive() + " " +
        "travels.\n");
    if (strlen(arg))
        return 0;

    all(" gracefully performs a strange dance that you have never seen " +
        "before. It is obviously something that " + 
        this_player()->query_pronoun() + " learned");
    write("You gracefully perform a dance once taught to you.\n");
    return 1;
}

public int
e_treverie(string arg)
{
    notify_fail("Remember what?\n");
    if (strlen(arg))
        return 0;

    all("'s eyes close momentarily as " + this_player()->query_pronoun() + 
        " fondly remembers " + this_player()->query_possessive() + " first " +
        "journey as a Traveller.");
    write("You close your eyes and reflect on your life as a " +
        "Traveller.\n");
    return 1;
}

public int
e_tshiver(string arg)
{
    notify_fail("aste Lands.\n");
    if (strlen(arg))
        return 0;

    all(" shivers, pulling " + this_player()->query_possessive() + " cloak " +
        "more tightly around " + this_player()->query_objective() + "self " +
        "as " + this_player()->query_pronoun() + " remembers " + 
        this_player()->query_possessive() + " travels through the Northern " +
        "W");
    write("You wrap your cloak more tightly around yourself.\n");
    return 1;
}

public int
e_tshudder(string arg)
{
    notify_fail("Shudder from what?\n");
    if (strlen(arg))
        return 0;

    all(" shudders, remembering some terrible sight that " + 
        this_player()->query_pronoun() + " saw on one of " + 
        this_player()->query_possessive() + " many journies as a " +
        "traveller.");
    write("Yikes! That was scary.\n");
    return 1;
}

public int
e_tdust(string arg)
{
    notify_fail("Dust what?\n");
    if (strlen(arg))
        return 0;

    all(" wipes off the dust from the trail that has clung to " + 
        this_player()->query_possessive() + " clothes.");
    write("You clean yoursef of trail dust.\n");
    return 1;
}

public int
e_texhaust(string arg)
{
    notify_fail("So exhausted you're hallucinating, eh?\n");
    if (strlen(arg))
        return 0;

    all(" sighs deeply and attempts to count the miles " + 
        this_player()->query_pronoun() + " has travelled this day while " +
        "leaning on " + this_player()->query_possessive() + " walking " +
        "stick.");
    write("You take a deep breath and lean on your trusty walking " +
        "stick.\n");
    return 1;
}

public int
e_ttemper(string arg)
{
    notify_fail("You seem to be so mad you can't even type.\n");
    if (strlen(arg))
        return 0;

    all(" leaves teeth marks in " + this_player()->query_possessive() + " " +
        "walking stick as " + this_player()->query_pronoun() + " bites " +
        "into it in total rage.");
    write("Grrrr!\n");
    return 1;
}

public int
e_twirl(string arg)
{
    notify_fail("at.\n");
    if (strlen(arg))
        return 0;

    all(" twirls " + this_player()->query_possessive() + " walking stick " +
        "in a flashy display of skill. You do not feel as though you could " +
        "accomplish such a fe");
    write("You twirl your walking stick out of pure boredom.\n");
    return 1;
}

public int
e_thail(string arg)
{
    object *oblist;

    notify_fail("Who did you want to hail?\n");
    if (!strlen(arg))
        return 0;

    oblist = parse_this(arg, "[the] %l");
    if (!sizeof(oblist))
        return 0;
    actor("You shake", oblist, "'s hand and say: Greetings, how have your " +
        "travels treated you?");
    all2act("shakes", oblist, "'s hand and says: Greetings, how have your " +
        "travels treated you?");
    target(" shakes your hand and says: Greetings, how have your travels " +
        "treated you?", oblist);
    return 1;
}

public int
e_tbreathe(string arg)
{
    notify_fail("Breathe how?\n");
    if (strlen(arg))
        return 0;

    all(" takes a deep breath and collects " + 
        this_player()->query_possessive() + " mind for travels to come.");
    write("You take a deep breath and ponder the journey ahead.\n");
    return 1;
}

public int
e_tspit(string arg)
{
    object *oblist;

    notify_fail("Spit at whom?\n");

    if (!strlen(arg))
    {
        all(" hawks up a glob of phlegm and spits it an amazing " +
        "distance.");
        write("You show everyone what your lungs are capable of!\n");
        return 1;
    }

    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;

    actor("You spit your phlegm on", oblist, ".");
    all2act("spits phlegm directly on", oblist, "'s shoe.");
    target(" hawks up a glob of phlegm and spits it directly on your " +
        "shoe.", oblist);
    return 1;
}

public int
e_teye(string arg)
{
    object *oblist;

    notify_fail("Teye who?\n");

    if (!strlen(arg))
    {
        all(" settles back and begins to study the land with rough, " +
        "weathered eyes.");
        write("You steadily examine your surroundings with the skill of an " +
        "experienced trailblazer.\n");
        return 1;
    }

    oblist = parse_this(arg, "[the] %l");
    if (!sizeof(oblist))
        return 0;

    actor("You carefully study", oblist, " with knowing eyes.");
    all2act("studies", oblist, " through travelled eyes.");
    target(" studies you through travelled eyes.", oblist);
    return 1;
}

public int
e_tpoke(string arg)
{
    object *oblist;

    notify_fail("Tpoke whom?\n");

    if (!strlen(arg))
    {
        all(" raps " + this_player()->query_possessive() + " weather " +
        "beaten walking stick on the ground, making a lot of racket.");
        write("You hit your stick on the ground, making a lot of " +
        "racket!\n");
        return 1;
    }

    oblist = parse_this(arg, "[the] %l");
    if (!sizeof(oblist))
        return 0;

    actor("You poke", oblist, " in the ribs with your weather beaten " +
        "walking stick.");
    all2act("pokes", oblist, " in the ribs with " + 
        this_player()->query_possessive() + " weather beaten walking " +
        "stick.");
    target(" pokes you in the ribs with " + 
        this_player()->query_possessive() + " weather beaten walking " +
        "stick.", oblist);
    return 1;
}

public int
e_tsalute(string arg)
{
    object *oblist;

    notify_fail("Salute whom?\n");

    if (!strlen(arg))
    {
        all(" gives a swift clean salute in the manner of a traveller.");
        write("You salute everyone in the manner of a traveller.\n");
        return 1;
    }

    oblist = parse_this(arg, "[the] %l");
    if (!sizeof(oblist))
        return 0;

    actor("You salute", oblist, " in the manner of a traveller.");
    all2act("gives", oblist, " a swift clean salute in the manner of a " +
        "traveller.");
    target(" gives you a swift clean salute in the manner of a " +
        "traveller.", oblist);
    return 1;
}

public int
e_curse(string arg)
{
    object *oblist;

    notify_fail("Curse at whom?\n");

    if (!strlen(arg))
    {
        all(" curses loudly in fourteen different languages; you feel your " +
        "vocabulary has improved.");
        write("You curse loudly in fourteen different languages.\n");
        return 1;
    }

    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;

    actor("You curse at", oblist, " loudly.");
    all2act("curses at", oblist, " loudly.");
    target(" curses at you loudly.", oblist);
    return 1;
}

public int
e_map(string arg)
{
    object *oblist;

    notify_fail("Wave map at whom?\n");

    if (!strlen(arg))
    {
        all(" unrolls a map and tries to decide where to go.");
        write("You unroll your map and try to decide where to go.\n");
        return 1;
    }

    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;

    actor("You wave your map under", oblist, "'s nose.");
    all2act("waves " + this_player()->query_possessive() + " map under", 
        oblist, "'s nose.");
    target(" waves " + this_player()->query_possessive() + " map under " +
        "your nose.", oblist);
    return 1;
}

public int
e_bored(string arg)
{
    object *oblist;

    notify_fail("Act bored with whom?\n");

    if (!strlen(arg))
    {
        all(" yawns and looks very bored.");
        write("You yawn and look around the room in boredom.\n");
        return 1;
    }

    oblist = parse_this(arg, "[the] %l");
    if (!sizeof(oblist))
        return 0;

    actor("You look around while", oblist, " is talking to you.");
    all2act("looks around while", oblist, " is talking. " + 
        capitalize(this_player()->query_pronoun()) + " doesn't appear to " +
        "be listening.");
    target(" looks around while you are talking. " + 
        capitalize(this_player()->query_pronoun()) + " doesn't appear to " +
        "be listening.", oblist);
    return 1;
}

public int
e_watch(string arg)
{
    object *oblist;

    notify_fail("Watch whom?\n");

    if (!strlen(arg))
    {
        all(" looks around carefully.");
        write("You slowly look around.\n");
        return 1;
    }

    oblist = parse_this(arg, "[the] %l");
    if (!sizeof(oblist))
        return 0;

    actor("You watch", oblist, " suspiciously.");
    all2act("watches", oblist, " suspicously.");
    target(" watches you suspiciously.", oblist);
    return 1;
}

public int
e_disbelief(string arg)
{
    object *oblist;

    notify_fail("I don't believe you!\n");

    if (!strlen(arg))
    {
        all(" stares in disbelief.");
        write("You cannot believe what is happening here!\n");
        return 1;
    }

    oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
    if (!sizeof(oblist))
        return 0;

    actor("You stare at", oblist, " in disbelief.");
    all2act("stares at", oblist, " in disbelief.");
    target(" stares at you in disbelief.", oblist);
    return 1;
}
 
public int
e_scorn(string arg)
{
    object *oblist;
    string n = "";
 
    notify_fail("Heap scorn on whom?\n");
    if (!strlen(arg))
        return 0;
    oblist = parse_this(arg, "[the] %l");
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
        case "elf": n = "n";
        default: n = " a" + n + " " + oblist[0]->query_race_name();
    }
    actor("You scorn", oblist, "because " + oblist[0]->query_pronoun() +
        "is" + n + ".");
    all2actbb("scorns", oblist, "because " + oblist[0]->query_pronoun() +
        "is" + n + ".");
    targetbb(" scorns you because you are" + n + ".\n", oblist);
    return 1;
}
 
public string
q_title(object ob, int wiz)
{
    if (!ob->query_guild_member("Traveller guild"))
        return 0;
    if (!wiz && ob->query_wiz_level())
        return 0;
    if (wiz && !ob->query_wiz_level())
        return 0;
    if (extract(ob->query_name(), -2) == "jr")
        return 0;
    return implode(explode(break_string(ob->query_presentation(), 76), "\n"),
        "\n    ");
}
 
public int
e_tl(string arg)
{
    int i;
    i = (query_verb() == "tlw" ? 1 : 0);
    write("The following Travellers are currently logged on:\n" +
       implode(map(users() - ({ 0 }), "q_title", this_object(), i) - ({ 0 }),
        "\n") + "\n");
    return 1;
}
 
public int
e_help(string arg)
{
    seteuid(getuid());
    if (arg != "traveller")
        if (arg != "traveller more")
            return 0;
        else
            clone_object(MORE_OBJ)->more(HELP_FILE);
    else
        cat(HELP_FILE);
    return 1;
}
 
public int
e_disdain(string arg)
{
    object *oblist;
 
    notify_fail("Show disdain to whom?");
    if (!strlen(arg))
        return 0;
    oblist = parse_this(arg, "[the] %l");
    if (!sizeof(oblist))
        return 0;
    if (sizeof(oblist) > 1)
    {
        notify_fail("So venemous is your stare that you can only disdain " +
            "one unfortunate soul at a time!\n");
        return 0;
    }
    if (oblist[0]->query_race_name() == "human")
    {
        write("You should not show disdain to fellow humans.\n");
        return 1;
    }
    actor("You show your complete disdain of", oblist, " a non-human.\n");
    targetbb(" gives you a look of complete and utter disdain.", oblist);
    all2actbb(" gives ", oblist, " a look of complete and utter disdain.");
    return 1;
}
 
public int
e_tsay(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Tsay what?\n");
        return 0;
    }
 
    if (this_player()->query_skill(SS_LANGUAGE) < 15)
    {
        notify_fail("Speaking the ancient road language of the Travellers " +
            "requires better knowledge of languages.\n");
        return 0;
    }
 
    if (this_player()->query_get_echo())
        write("In the road language of the Travellers, you say: " + arg +
            "\n");
    else
        write("Ok.\n");
 
    filter(all_inventory(environment(this_player())) - ({ this_player() }),
        "do_say", this_object(), arg);
    return 1;
}
 
public int
do_say(object who, string arg)
{
    if (!living(who))
        return 0;
    if ((IS_MEMBER(who) && who->query_skill(SS_LANGUAGE) > 19) ||
        who->query_skill(SS_LANGUAGE) > 60)
        tell_object(who, this_player()->query_The_name(who) + " mutters " +
            "in the language of the Travellers: " + arg + "\n");
    else
        tell_object(who, this_player()->query_The_name(who) + " says " +
            "something in a strange language.\n");
}
