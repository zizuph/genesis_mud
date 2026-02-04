/*
 * elf_soul.c    Coded by Mylos on 20.4.93
 * 
 */

inherit "/cmd/std/command_driver";

#include "/d/Emerald/room/vamp/default.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>

#define tpro this_player()->query_pronoun()
#define tpos this_player()->query_possessive()

/* **************************************************************************
 * Return a proper name of the soul in order to get a nice printout.
 */
string
get_soul_id()
{
    return "wildrunner";
}

/* **************************************************************************
 * This is a command soul.
 */
int
query_cmd_soul()
{
    return 1;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 */
mapping
query_cmdlist()
{
    return ([ "accuse" : "accuse",
	      "adore" : "adore",
              "approve" : "approve",
              "calm" : "calm",
              "cbow" : "cbow",
	      "compliment" : "compliment",
              "curl" : "curl",
              "deign" : "deign",
              "disgust" : "disgust",
              "drum" : "drum",
              "ehail" : "ehail",
              "embrace" : "embrace",
              "eturn" : "eturn",
              "frown" : "frown",
              "grip" : "grip",
              "hand" : "hand",
              "hate" : "hate",
              "help" : "help",
              "huff" : "huff",
              "notice" : "notice",
              "pick" : "pick",
	      "regard" : "regard",
              "rejoice" : "rejoice",
              "scowl" : "scowl",
              "shudder" : "shudder",
              "visage" : "visage",
              "wonder" : "wonder",
           ]);
}

int
accuse(string str)
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

int
adore(string str)
{
   object *oblist;

   NF("Adore whom?\n");
   if(!strlen(str))
	return 0;

   oblist = parse_this(str, "%l");
   if(!sizeof(oblist))
	return 0;
   target(" looks at you with total adoration in "+POS(TP)+" eyes.", oblist);
   actor("You look at", oblist," with total adoration in your eyes.");
   all2act(" looks at", oblist," with total adoration in "+POS(TP)+" eyes.");
   return 1;
}

int
approve(string str)
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

int
calm(string str)
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

int
cbow(string str)
{
   object *oblist;

   if(!strlen(str)) {
        write("You execute a perfect courtly bow.\n");
        all(" executes a perfect courtly bow.\n");
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

int
compliment(string str)
{
   object *oblist;

   NF("Who do you wish to compliment?\n");
   if(!strlen(str))
	return 0;

   oblist = parse_this(str, "%l");
   if(!sizeof(oblist))
	return 0;
   target(" compliments you on the way that you conduct yourself.", oblist);
   actor("You compliment", oblist," on the way that "+PRON(oblist[0])+
	" conducts "+oblist[0]->query_objective()+"self.");
   all2act(" compliments", oblist," on the way that "+PRON(oblist[0])+
	" conducts "+oblist[0]->query_objective()+"self.");
   return 1;
}

int
curl(string str)
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

int
deign(string str)
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

int
disgust(string str)
{
        object *oblist;

        notify_fail("turn your back on whom?\n");
        if(!strlen(str))
                return 0;
        oblist = parse_this(str, "[at] %l");
        if(!sizeof(oblist))
                return 0;
        target(" turns "+tpos+" back on you in disgust", oblist);
        actor("You turn your back in disgust on", oblist);
        all2act(" turns "+tpos+" back on", oblist," in disgust.");
        return 1;
}

int
drum()
{
        write("You drum your fingers impatiently.\n");
        all(" drums "+this_player()->query_possessive()+" fingers impatiently.");
        return 1;
}

int
ehail(string str)
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
        all2act(" hails", oblist," loudly in elven: 'Eltelar Calabrin!'");
        return 1;
}

int
embrace(string str)
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

int
frown(string str)
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

int
grip()
{
        write("You grip your hands together in silent fury.\n");
        all(" grips "+tpos+" hands together in silent fury.");
        return 1;
}

int
hand(string str)
{
   object *oblist;

   notify_fail("Gesture to whom to leave the room?\n");
   if(!strlen(str))
        return 0;
   oblist = parse_this(str, "%l");
   if(!sizeof(oblist))
        return 0;
   target(" gestures with "+tpos+" hand that you may leave the "+
        "room.", oblist);
   actor("You gesture with your hand that", oblist," may leave the room.");
   all2act(" gestures with "+tpos+" hand that", oblist," may leave the room.");
   return 1;
}

int
hate(string str)
{
        object *oblist;

        notify_fail("Look with hate at whom?\n");
        if(!strlen(str))
                return 0;
        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;
        target(" looks with absolute hate at you.", oblist);
        actor("You look with complete hate on your face, at", oblist);
        all2act(" looks with hate at", oblist);
        return 1;
}

int
help(string arg)
{
    string subject, filename;

    if (!arg)
        return 0;
    if (sscanf(arg, "wild %s", subject) != 1)
        return 0;
    filename=HELP_DIR + subject;
    if (file_size(filename)>0) {
        this_player()->more(filename);
        return 1;
    }
    notify_fail("No help on that subject available.\n");

    return 0;
}

int
huff(string str)
{
        write("You turn your back and go into a huff.\n");
        all(" turns "+tpos+" back and goes into a huff.");
        return 1;
}

int
notice(string str)
{
   object *oblist;

   notify_fail("Whom do you wish to notice?\n");
   if(!strlen(str))
        return 0;
   oblist = parse_this(str, "%l");
   if(!sizeof(oblist))
        return 0;
   target(" turns to you and says: 'Sorry, I didn't notice you there.'", oblist);
   actor("You turn to", oblist," and say: 'Sorry, I didn't notice you there.'");
   all2actbb(" turns to", oblist," and says: 'Sorry, I didn't notice you...'");
   return 1;
}


int
pick(string str)
{
        write("You pick a piece of dirt of your impeccable clothing.\n");
        all(" picks a piece of imaginable dirt from "+tpos+" clothes.");
        return 1;
}

int
regard(string str)
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
      actor("You regard", oblist," carefully, examining "+POS(oblist[0])+
	 " fine Elven features.");
      all2act(" regards", oblist," carefully, looking over "+POS(oblist[0])+
	 " fine Elven features.");
      return 1;
   }
   if(oblist[0]->query_race_name() == "dwarf") {
      target(" regards you carefully, sneering at your short squat "+
	 "features.", oblist);
      actor("You regard", oblist," carefully, sneering at "+POS(oblist[0])+
	 " short ugly frame.");
      all2act(" regards", oblist," with obvious distaste sneering at "+
	 POS(oblist[0])+" ugly squat frame.");
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
      all2act(" regards", oblist," with an amused grin on "+POS(TP)+" face.");
     return 1;
   }
   else
   target(" regards you closely, taking in every small detail.", oblist);
   actor("You peer at", oblist," taking in every small detail.");
   all2act(" regards", oblist," with a strange expresion on "+POS(TP)+
      " face.");
   return 1;
}

int
rejoice(string str)
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


int
scowl(string str)
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

int
shudder()
{
        write("An uncontrolable shudder goes through your body.\n");
        all(" shudders for a moment.");
        return 1;
}

int
eturn(string str)
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

int
visage()
{
        write("Your unemotional visage drops for a moment to display your "+
           "true emotions.\n");
        all("'s face registers a true emotion for a few moments.");
        return 1;
}

int
wonder()
{
   write("You look around you in wonder at the sheer beauty of nature.\n");
   all("'s face expresses wonder as "+POS(TP)+" looks admires the beauty "+
        "of nature.");
   return 1;
}

