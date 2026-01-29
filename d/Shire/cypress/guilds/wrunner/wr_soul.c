/* This is the Wildrunners soul - emotions coded originally by Mylos.     */
/* This soul was based on the work of others - Tricky, Quis, Nick et al.  */
/* Recoded 28/08/95 by Tulix III to bring up to Grunts standard.          */
/* help command revised -- Shiva ??/??/96
 * "ground" moved into soul and revised -- Shiva 12/04/96
 */

inherit "/cmd/std/command_driver";
#include "/d/Shire/cypress/sys/defs.h"
#include "/d/Shire/cypress/guilds/wrunner/wrunner_defs.h"
//#include "help.c"
#include "ground.c"
//#include "widea.h"
#include <macros.h>
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <composite.h>
#include <files.h>
#include <time.h>
#include <std.h>
#include <wa_types.h>
#include <options.h>
#include <adverbs.h>
#include <cmdparse.h>

#define tpro this_player()->query_pronoun()
#define tpos this_player()->query_possessive()
#define MORE(x)   this_player()->more(read_file(x,2))
#define IDEA_FILE WRUNNER_DIR + "ideas"

/* **************************************************************************
 * Return a proper name of the soul in order to get a nice printout.
 */
string get_soul_id()
{
    return GUILD_SOUL_ID;
}

/* **************************************************************************
 * This is a command soul.
 */
int query_cmd_soul()
{
    return 1;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 */
mapping query_cmdlist()
{
    return ([ "help"            : "help",
              "weaccuse"        : "accuse",
              "weadore"         : "adore",
              "weagree"         : "agree",
              "weapologize"     : "apologize",
              "weapplaud"       : "applaud",
              "weapprove"       : "approve",
              "weavert"         : "avert",
              "weblanch"        : "blanch",
              "webow"           : "bow",
              "wecalm"          : "calm",
              "wecompliment"    : "compliment",
              "wecurl"          : "curl",
              "wedeign"         : "deign",
              "wedisgust"       : "disgust",
              "wedrum"          : "drum",
              "wehail"          : "hail",
              "weembrace"       : "embrace",
              "weturn"          : "turn",
              "wefrown"         : "frown",
              "wegrip"          : "grip",
              "weground"        : "ground",
              "wehand"          : "hand",
              "wehate"          : "hate",
              "wehelp"          : "help",
              "wehuff"          : "huff",
              "weidea"          : "idea",
              "wenotice"        : "notice",
              "wepick"          : "pick",
              "weregard"        : "regard",
              "werejoice"       : "rejoice",
              "wesay"           : "say",
              "wescowl"         : "scowl",
              "weshudder"       : "shudder",
              "wevisage"        : "visage",
              "wewonder"        : "wonder",
              "wewrinkle"       : "wrinkle",
           ]);
}

/*
 * Help routines for Wildrunners
 */
int help(string str)
{
    setuid(); seteuid(getuid());
    switch (str)
    {
    case "wild":
    case "wild elves":
    MORE(GUILD_HELP + "general");
    break;
    
    case "wild emotes": 
    case "wild emotions":
    case "wild elves emotes":
    case "wild elves emotions":
        MORE(GUILD_HELP + "emotes");
    break;
/*    
    case "wildrunner titles":
        MORE(GUILD_HELP + "titles");
    break;
*/
    case "wild levels":
    case "wild elves levels":
        MORE(GUILD_HELP + "levels");
    break;

    default:
    return 0;
    }
    return 1;
}


int accuse(string str)
{
        object *oblist;

        notify_fail("Accuse whom?\n");
        if(!strlen(str))
                return 0;

        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;
        target(" points an accusatory finger at you.", oblist);
        actor("You point an accusatory finger at", oblist);
        all2act(" points an accusatory finger at", oblist);
        return 1;
}

int adore(string str)
{
   object *oblist;

   NF("Adore whom?\n");
   if(!strlen(str))
        return 0;

   oblist = parse_this(str, "%l");
   if(!sizeof(oblist))
        return 0;
   target(" looks at you with total adoration in "+HIS_HER(TP)+" eyes.", oblist);
   actor("You look at", oblist," with total adoration in your eyes.");
   all2act(" looks at", oblist," with total adoration in "+HIS_HER(TP)+" eyes.");
   return 1;
}


int agree(string str)
{
        object *oblist;
        if(!strlen(str))
        {
                write("You stroke your chin thoughtfully, and come to " +
                    "the conclusion you agree with the idea.\n");
                all(" strokes " + HIS_HER(TP) + " chin thoughtfully, then " +
                "decides " + HE_SHE(TP) + " agrees with the idea.");
                return 1;
        }
        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;
        actor("You stroke your chin, lost in thought. After deep " +
            "contemplation, you come to the conclusion you agree " +
            "with",oblist,"'s idea.");
        target(" strokes " + HIS_HER(TP) + " chin, seemingly lost in thought. After " +
            "deep contemplation, " + HE_SHE(TP) + " comes to the conclusion " + 
            HE_SHE(TP) + " agrees with your idea.", oblist);
        all2actbb(" strokes " + HIS_HER(TP) + " chin, seemingly lost in " +
            "thought. After deep contemplation, " + HE_SHE(TP) + 
            " comes to the conclusion " + HE_SHE(TP) + " agrees " +
            "with", oblist,"'s idea.");
        return 1;
}

int apologize(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "stiffly", 0);

    if (!stringp(how[0]))
    {
        write("You clench your jaw and" + how[1] + " offer a hollow apology.\n");
        allbb(" clenches " + HIS_HER(TP) + " jaw and" + how[1] + 
            " offers a hollow apology.", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("weapologize [how] to whom?\n");
        return 0;
    }

    actor("You clench your jaw and" + how[1] + " offer a hollow " +
        "apology to", oblist,".");
    targetbb(" clenches " + HIS_HER(TP) + " jaw and" + how[1] + 
        " offers a hollow apology to you.", oblist);
    all2actbb(" clenches " + HIS_HER(TP) + " jaw and" + how[1] +
        " offers a hollow apology to", oblist, ".");

    return 1;
}

int applaud(string str)
{
        object *oblist;
        if(!strlen(str))
        {
                write("You nod your head and clap your hands vigorously for a job well done.\n");
                all(" strokes " + HIS_HER(TP) + " chin thoughtfully, then " +
                "decides " + HE_SHE(TP) + " agrees with the idea.");
                return 1;
        }
        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;
        actor("You stroke your chin, lost in thought. After deep " +
            "contemplation, you come to the conclusion you agree " +
            "with",oblist,"'s idea.");
        target(" strokes " + HIS_HER(TP) + " chin, seemingly lost in thought. After " +
            "deep contemplation, " + HE_SHE(TP) + " comes to the conclusion " + 
            HE_SHE(TP) + " agrees with your idea.", oblist);
        all2actbb(" strokes " + HIS_HER(TP) + " chin, seemingly lost in " +
            "thought. After deep contemplation, " + HE_SHE(TP) + 
            " comes to the conclusion " + HE_SHE(TP) + " agrees " +
            "with", oblist,"'s idea.");
        return 1;
}



int approve(string str)
{
        object *oblist;
        if(!strlen(str))
        {
                write("You nod approval at the idea.\n");
                all(" nods approval at the idea.");
                return 1;
        }
        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;
        target(" nods approval at your idea.", oblist);
        actor("You nod approval at",oblist,"'s idea.");
        all2actbb(" nods approval at", oblist,"'s idea.");
        return 1;
}

int avert(string str)
{
        write("avert your eyes from the unpleasantness before them.\n");
        all(" averts " + HIS_HER(TP) + " eyes from the unpleasantness " +
            "before them.");
        return 1;
}

int calm(string str)
{
        object *oblist;

        notify_fail("Remain calm despite whom?\n");
        if(!strlen(str))
                return 0;
        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;
        target(" remains calm despite your petty insinuation." ,oblist);
        actor("You remain calm and serene despite", oblist,"'s comments.");
        all2act(" remains calm despite", oblist,"'s comments.");
        return 1;
}

int blanch(string str)
{
        write("You swallow slowly, and feel all color drain from your face.\n");
        all(" swallows slowly, and you see all color drain from " + 
            HIS_HER(TP) + " face.");
        return 1;
}

int bow(string str)
{
   object *oblist;

   if(!strlen(str))
   {
        write("You execute a perfect courtly bow.\n");
        all(" executes a perfect courtly bow.");
        return 1;
   }
   oblist = parse_this(str, "[at] %l");
   if(!sizeof(oblist))
        return 0;
   target(" executes a perfect courtly bow to you.", oblist);
   actor("You execute a perfect courtly bow towards", oblist,".");
   all2act(" executes a perfect courtly bow to", oblist,".");
   return 1;
}

int compliment(string str)
{
   object *oblist;

   NF("Who do you wish to compliment?\n");
   if(!strlen(str))
        return 0;

   oblist = parse_this(str, "%l");
   if(!sizeof(oblist))
        return 0;
   target(" compliments you on the way that you conduct yourself.", oblist);
   actor("You compliment", oblist," on the way that "+HE_SHE(oblist[0])+
        " conducts "+oblist[0]->query_objective()+"self.");
   all2act(" compliments", oblist," on the way that "+HE_SHE(oblist[0])+
        " conducts "+oblist[0]->query_objective()+"self.");
   return 1;
}

int curl(string str)
{
   object *oblist;

   if(!strlen(str))
   {
        write("You curl your lip in derision at the lesser mortals.\n");
        all(" curls "+this_player()->query_possessive()+" lip in derision "+
             "at the lesser mortals.");
             return 1;
   }
   oblist = parse_this(str, "[at] %l");
   if(!sizeof(oblist))
        return 0;
   target(" curls "+this_player()->query_possessive()+" lip in derision "+
           "towards you.", oblist);
   actor("You curl your lip in derision at", oblist);
   all2act(" curls "+this_player()->query_possessive()+" lip in derision "+
           "at", oblist);
   return 1;
}

int deign(string str)
{
        object *oblist;

        notify_fail("Deign to notice whom?\n");
        if(!strlen(str))
                return 0;
        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;
        target(" deigns to acknowledge you, a non-elf.", oblist);
        actor("You deign to acknowledge", oblist,", a non-elf.");
        all2act(" deigns to acknowledge", oblist,", a non-elf.");
        return 1;
}


int disgust(string str)
{
        object *oblist;

        notify_fail("Turn your back on whom?\n");
        if(!strlen(str))
                return 0;
        oblist = parse_this(str, "[at] %l");
        if(!sizeof(oblist))
                return 0;
        target(" turns "+tpos+" back on you in disgust.", oblist);
        actor("You turn your back in disgust on", oblist);
        all2act(" turns "+tpos+" back on", oblist," in disgust.");
        return 1;
}

int drum()
{
        write("You drum your fingers impatiently.\n");
        all(" drums "+this_player()->query_possessive()+" fingers impatiently.");
        return 1;
}

int hail(string str)
{
        object *oblist, name;

        notify_fail("Hail whom?\n");
        if(!strlen(str))
                return 0;
        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;

        target(" hails you loudly in pure elven: 'Eltelar Calabrin!'", oblist);
        actor("You hail", oblist, " loudly in elven: 'Eltelar Calabrin!'");
        all2act(" hails ", oblist," loudly in elven: 'Eltelar Calabrin!'");
        return 1;
}

int embrace(string str)
{
        object *oblist;

        notify_fail("Embrace whom?\n");
        if(!strlen(str))
                return 0;
        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;
        target(" embraces you fondly in the elven tradition.", oblist);
        actor("You embrace", oblist," fondly in the true elven tradition.");
        all2act(" embraces", oblist," in the elven tradition.");
        return 1;
}

int frown(string str)
{
        object *oblist;

        notify_fail("Frown at whom?\n");
        if(!strlen(str))
                return 0;

        oblist = parse_this(str, "[at] %l");
        if(!sizeof(oblist))
                return 0;

        target(" folds "+tpos+" arms, and frowns at you.", oblist);
        actor("You fold your arms and frown at", oblist);
        all2act(" folds "+tpos+" arms and frowns at", oblist);
        return 1;
}

int grip(string str)
{
  if(!str) return 0;
  notify_fail("Grip what?  Perhaps your hands?\n");
  if(str == "hands" || str == "fury")
  {
        write("You grip your hands together in silent fury.\n");
        all(" grips "+tpos+" hands together in silent fury.");
        return 1;
  }
  return 0;
}

int hand(string str)
{
   object *oblist;

   notify_fail("Gesture to whom to leave?\n");
   if(!strlen(str))
        return 0;
   oblist = parse_this(str, "%l");
   if(!sizeof(oblist))
        return 0;
   target(" gestures with "+tpos+" hand that you may leave now.", oblist);
   actor("You gesture with your hand that", oblist," may leave now.");
   all2act(" gestures with "+tpos+" hand that", oblist," may leave now.");
   return 1;
}

int hate(string str)
{
        object *oblist;

        notify_fail("Look with hate at whom?\n");
        if(!strlen(str))
                return 0;
        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;
        target(" looks at you with absolute hate.", oblist);
        actor("You look with complete hate on your face, at", oblist);
        all2act(" looks with hate at", oblist);
        return 1;
}

int huff(string str)
{
        write("You turn your back and go into a huff.\n");
        all(" turns "+tpos+" back and goes into a huff.");
        return 1;
}

int notice(string str)
{
   object *oblist;

   notify_fail("Whom do you wish to notice?\n");
   if(!strlen(str))
        return 0;
   oblist = parse_this(str, "%l");
   if(!sizeof(oblist))
        return 0;
   target(" turns to you and says: 'Sorry, I didn't notice you there.'", oblist);
   actor("You turn to ", oblist," and say: 'Sorry, I didn't notice you there.'");
   all2actbb("turns to ", oblist," and says: 'Sorry, I didn't notice you...'");
   return 1;
}


int pick(string str)
{
        write("You pick a piece of dirt off your impeccable clothing.\n");
        all(" picks a piece of imaginable dirt from "+tpos+" clothes.");
        return 1;
}

int regard(string str)
{
   object *oblist;

   NF("Regard whom?\n");
   if(!strlen(str))
        return 0;

   oblist = parse_this(str, "[at] %l");
   if(!sizeof(oblist))
        return 0;

   if(oblist[0]->query_race_name() == "elf") {
      target(" regards you carefully, looking over your fine "+
         "features.", oblist);
      actor("You regard", oblist," carefully, examining "+HIS_HER(oblist[0])+
         " fine Elven features.");
      all2act(" regards", oblist," carefully, looking over "+HIS_HER(oblist[0])+
         " fine Elven features.");
      return 1;
   }
   if(oblist[0]->query_race_name() == "dwarf") {
      target(" regards you carefully, sneering at your short squat "+
         "features.", oblist);
      actor("You regard", oblist," carefully, sneering at "+HIS_HER(oblist[0])+
         " short ugly frame.");
      all2act(" regards", oblist," with obvious distaste sneering at "+
         HIS_HER(oblist[0])+" ugly squat frame.");
      return 1;
   }
   if(oblist[0]->query_race_name() == "goblin") {
      target(" hardly looks down at you, considering you the lowest of "+
         "the low.", oblist);
      actor("You regard", oblist," as the lowest of the low, a slave to "+
         "the superior Elven race.");
      all2act(" regards", oblist," as a slave to the superior Elven race.");
      return 1;
   }
   if(oblist[0]->query_race_name() == "human") {
      target(" regards you closely, distrusting you vehemently.", oblist);
      actor("You regard", oblist," carefully, obvious distrust showing "+
         "on your face.");
      all2act(" regards", oblist," carefully, obviously distrusting "+
         oblist[0]->query_objective()+".");
      return 1;
   }
   if(oblist[0]->query_race_name() == "gnome") {
      target(" peers at you closely, taking in every detail.", oblist);
      actor("You peer at", oblist," closely, considering "+
         oblist[0]->query_objective()+" to be a lesser mortal than you.");
      all2act(" regards", oblist," with an amused grin on "+HIS_HER(TP)+" face.");
     return 1;
   }
   else
   target(" regards you closely, taking in every small detail.", oblist);
   actor("You peer at", oblist," taking in every small detail.");
   all2act(" regards", oblist," with a strange expresion on "+HIS_HER(TP)+
      " face.");
   return 1;
}

int rejoice(string str)
{
        object *oblist;

        notify_fail("Rejoice at whom?\n");
        if(!strlen(str))
                return 0;
        oblist = parse_this(str, "[at] %l");
        if(!sizeof(oblist))
                return 0;
        target(" rejoices that you are safe and well.", oblist);
        actor("You rejoice that", oblist," is safe and well.");
        all2act(" rejoices that", oblist," is safe and well.");
        return 1;
}

int scowl(string str)
{
        object *oblist;

        if(!strlen(str))
        {
                write("You scowl in anger.\n");
                all(" scowls in anger.");
                return 1;
        }
        oblist = parse_this(str, "[at] %l");
        if(!sizeof(oblist))
                return 0;
        target(" scowls in anger at you.", oblist);
        actor("You scowl in anger at", oblist);
        all2act(" scowls in anger at", oblist);
        return 1;
}

int shudder()
{
        write("An uncontrolable shudder goes through your body.\n");
        all(" shudders for a moment.");
        return 1;
}

int turn(string str)
{
        object *oblist;

        notify_fail("Turn to face whom?\n");
        if(!strlen(str))
                return 0;
        oblist = parse_this(str, "[to] %l");
        if(!sizeof(oblist))
                return 0;
        target(" turns slowly to face you.", oblist);
        actor("You turn slowly to face", oblist);
        all2actbb(" turns slowly to face",oblist);
        return 1;
}

int visage()
{
        write("Your unemotional visage drops for a moment to display your "+
           "true emotions.\n");
        all("'s face registers a true emotion for a few moments.");
        return 1;
}

int wonder()
{
   write("You look around you in wonder at the sheer beauty of nature.\n");
   all("'s face expresses wonder as "+HE_SHE(TP)+" admires the beauty "+
        "of nature.");
   return 1;
}

int wrinkle()
{
   write("You wrinkle your nose in disgust!\n");
   all(" wrinkles " +tpos+ " nose in disgust!");
   return 1;
}

/*
 * Commands and routine for submitting ideas
 */
void write_msg(string str)
{
    setuid();
    seteuid(getuid());
    write_file(IDEA_FILE, sprintf("\n%-13s (%s)\n%s\n", 
        capitalize(this_player()->query_real_name()), ctime(time()), str));

    write("Message submited.\nOk.\n");
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

/*
 *command to submit ideas
 */
int idea(string str){

    if (strlen(str))
    {
       if (str == "")
       {
           write("noidea [<message>]\n");
           return 1;
       }

       &write_msg(str);
       return 1;
    }

    setuid();
    seteuid(getuid());

    clone_object(EDITOR_OBJECT)->edit("done", "");
    return 1;
}
