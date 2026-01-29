/*
 * /d/Gondor/clubs/storyteller/obj/telsoul.c
 * (Partial) soul of the Storytellers (Tellers) Club,
 * namely, club (global) emotions only.
 */

inherit "/cmd/std/command_driver";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include <macros.h>
#include <adverbs.h>
#include <stdproperties.h>

#define SOULDESC(x)  (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define OBHIM   (oblist[0]->query_objective())
#define HE(x)   ((x)->query_pronoun())
#define HIS(x)  ((x)->query_possessive())
#define HIM(x)  ((x)->query_objective())
#define OBHIS   (oblist[0]->query_possessive())

string get_soul_id() { return "The Storyteller Club"; }

int query_cmd_soul() { return 1; }

/*
 * Returns a mapping of the form "verb":"function" with all the commands
 * the player can perform as a member of the Storytellers Club.
 * Please add new commands in alphabetical order.
 */

mapping
query_cmdlist()
{
  setuid();
  seteuid(getuid());
  return ([
            "help"       : "help",
           "stadjust"    : "stadjust",
           "stapplaud"   : "stapplaud",
           "stbid"       : "stbid",
           "stbook"      : "stbook",
           "stclean"     : "stclean", 
           "stclear"     : "stclear",
           "stedge"      : "stedge",
           "stemphasis"  : "stemphasis",
           "stgaze"      : "stgaze",
           "stgreet"     : "stgreet",
           "stlisten"    : "stlisten",
           "stlost"      : "stlost",
           "stidea"      : "stidea",
           "stobserve"   : "stobserve",
           "stpause"     : "stpause",
           "stpeer"      : "stpeer",
           "strub"       : "strub",
           "stsigh"      : "stsigh",
           "stsmile"     : "stsmile",
           "ststory"     : "ststory",
           "sttear"      : "sttear"
         ]);
}


int
stadjust()
{ 
   if (!present(SPECTACLES_ID, this_player()))
   {
	write("You have no spectacles to adjust.\n");
	return 1;
   }

   write("You adjust your reading spectacles and continue on with "
      +"your story.\n");
   all(" adjusts "+HIS(TP)+" reading spectacles and continues "
      +"on with "+HIS(TP)+" story.");
   return 1;
}

int
do_applaud(string genre, mixed *oblist)
{
   switch(genre)
   {
      case "joy":
      if (!sizeof(oblist)) {
         write("You applaud joyfully and give a cheer for the happy "+
            "ending.\n");
         all(" applauds joyfully and gives a cheer for the happy "+
            "ending.");
          }
      else { 
         actor("You applaud",oblist," joyfully and give a cheer for the "+
            "happy ending.");
         target(" applauds you joyfully and gives a cheer for the happy "+
            "ending.",oblist);
         all2act(" applauds", oblist," joyfully and gives a cheer for "+
            "the happy ending.");
          }
      return 1; 
      break;
      case "sorrow":
      if (!sizeof(oblist)) {
         write("You applaud tearfully and hug everyone with a soft sigh.\n");
         all(" applauds tearfully and hugs everyone with a soft sigh.");
         }
      else {
         actor("You applaud",oblist," tearfully and hug "+OBHIM+
            " with a soft sigh.");
         target(" applauds you tearfully and hugs you with a soft "+
            "sigh.",oblist);
         all2act(" applauds",oblist," tearfully and hugs "+OBHIM+
            " with a soft sigh.");
          }
      return 1;
      break;
      case "comedy":
      if (!sizeof(oblist)) {
         write("You applaud with a merry laugh and a mirthful giggle.\n");
         all(" applauds with a merry laugh and a mirthful giggle.");
          }
      else {
         actor("You applaud",oblist," with a merry laugh and a mirthful "+
            "giggle.");
         target(" applauds you with a merry laugh and a mirthful giggle.",
            oblist);
         all2act(" applauds",oblist," with a merry laugh and a mirthful "+
            "giggle.");
          }
      return 1;
      break;
      case "romance":
      if (!sizeof(oblist)) {
         write("You applaud with a blissful look on your face, place a "+
            "hand over your heart, and sigh dreamily.\n");
         all(" applauds with a blissful look on "+HIS(TP)+" face, places "+
            "a hand over "+HIS(TP)+" heart, and sighs dreamily.");
          }
      else {
         actor("You applaud",oblist," with a blissful look on your face, "+
            "place a hand over your heart, and sigh dreamily.");
         target(" applauds you with a blissful look on "+HIS(TP)+" face, "+
            "places a hand over "+HIS(TP)+" heart, and sighs "+
            "dreamily.",oblist);
         all2act(" applauds",oblist," with a blissful look on "+HIS(TP)+
            " face, places a hand over "+HIS(TP)+" heart, and sighs "+
            "dreamily.");
          }
      return 1;
      break;
      case "horror":
      if (!sizeof(oblist)) {
         write("You applaud, wide-eyed and obviously relieved that the "+
            "fearsome tale is over.\n");
         all(", "+HIS(TP)+" eyes wide, applauds, obviously relieved that "+
            "the fearsome tale is over.");
          }
      else {
         actor("You applaud",oblist,", wide-eyed and obviously relieved "+
            "that "+OBHIS+" fearsome tale is over.");
         target(", "+HIS(TP)+" eyes wide, applauds you, obviously relieved "+
            "that your fearsome tale is over.",oblist);
         all2act(" applauds",oblist,", wide-eyed and obviously relieved "+
            "that "+OBHIS+" fearsome tale is over.");
          }
      return 1;
      break;
      case "suspense":
      if (!sizeof(oblist)) {
         write("You applaud breathlessly from the edge of your seat.\n");
         all(" applauds breathlessly from the edge of " +HIS(TP) + " seat.");
         }
      else {
         actor("You applaud",oblist," breathlessly from the edge of your "+
            "seat.");
         target(" applauds you breathlessly from the edge of "+HIS(TP)+
            " seat.",oblist);
         all2act(" applauds",oblist," breathlessly from the edge of "+HIS(TP)+
            " seat.");
          }
      return 1;
      break;
      default:
      write("You applaud heartily and remind everyone again how much you "+
         "really do love a good story!\n");
      all(" applauds heartily and reminds everyone again how much "+
         HE(TP)+ " really does love a good story!");
      return 1;
      break;
   }
}

int
stapplaud(string str)
{
   string genre;
   mixed *oblist;
   if (strlen(str))
      parse_command(str,ENV(TP),"%w [for] %l",genre,oblist);
   if (sizeof(oblist) > 0)
     oblist = exclude_array(oblist,0,0);
   return do_applaud(genre,oblist);
}

int
stbid(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb(str, "warmly", 0);

    oblist = parse_this(how[0], "[to] %l");

    if (!sizeof(oblist))
    {
       write("You "+how[1]+" bid everyone farewell and wish them "
             + "a safe and prosperous journey that ends in a good "
             + "tale.\n");
       all(" "+how[1]+" bids you farewell and wishes you a safe and "
           + "prosperous journey that ends in a good tale.");
       return 1;
    }

    actor("You "+how[1]+" bid",oblist," farewell and wish "
          +OBHIM+" a safe and prosperous journey that ends in a "
          +"good tale.");
    all2act(" "+how[1]+" bids",oblist," farewell and wishes "+OBHIM
          +" a safe and prosperous journey that ends in a good "
          +"tale.");
    target(" "+how[1]+" bids you farewell and wishes you a safe and "
          +"prosperous journey that ends in a good tale.", oblist);
    return 1;
}

int
stbook(string genre)
{
   switch(genre)
   {
      case "joy":
        write("You flip idly through your storybook and smile happily "+
           "as a joyful passage catches your eye.\n");
        all(" flips idly through "+HIS(TP)+" storybook and smiles "+
           "happily as a joyful passage catches "+HIS(TP)+" eye.");
      return 1; 
      break;
      case "sorrow":
        write("You flip idly through your storybook and shed a "+
           "solitary tear as a sorrowful passage catches your eye.\n");
        all(" flips idly through "+HIS(TP)+" storybook and sheds a "+
           "solitary tear as a sorrowful passage catches "+HIS(TP)+" eye.");
      return 1;
      break;
      case "comedy":
        write("You flip idly through your storybook and giggle softly "+
           "as a humorous passage catches your eye.\n");
        all(" flips idly through "+HIS(TP)+" storybook and giggles "+
           "softly as a humorous passage catches "+HIS(TP)+" eye.");
      return 1;
      break;
      case "romance":
        write("You flip idly through your storybook and smile tenderly "+
           "as a romantic passage catches your eye.\n");
        all(" flips idly through "+HIS(TP)+" storybook and smiles "+
           "tenderly as a romantic passage catches "+HIS(TP)+" eye.");
      return 1;
      break;
      case "horror":
        write("You flip idly through your storybook and cringe slightly "+
           "as a terrifying passage catches your eye.\n");
        all(" flips idly through "+HIS(TP)+" storybook and cringes "+
           "slightly as a terrifying passage catches "+HIS(TP)+" eye.");
      return 1;
      break;
      case "suspense":
        write("You flip idly through your storybook and gasp breathlessly "+
           "as a suspenseful passage catches your eye.\n");
        all(" flips idly through "+HIS(TP)+" storybook and gasps "+
           "breathlessly as a suspenseful passage catches "+HIS(TP)+" eye.");
      return 1;
      break;
      default:
        write("You flip idly through your storybook and smile warmly "+
           "as you reminisce about the many stories it contains.\n");
        all(" flips idly through "+HIS(TP)+" storybook and smiles as "+
           HE(TP)+" reminisces about the many stories it contains.");
      return 1;
      break;
   }
}

int
stclean()
{ 
   if (!present(SPECTACLES_ID, this_player()))
   {
	write("You have no spectacles to clean.\n");
	return 1;
   }

   write("You take off your spectacles and clean them.\n");
   all(" takes off "+HIS(TP)+" spectacles and cleans them.");
   return 1;
}

int
stclear()
{ 
   write("You clear your throat and prepare to begin your tale.\n");
   all(" clears "+HIS(TP)+" throat and prepares to begin "+
         HIS(TP)+" tale.");
   return 1;
}

int
stedge(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
       write("You are on the edge of your seat as you listen to the story.\n");
       all(" is on the edge of "+HIS(TP)+" seat as "+HE(TP)+" listens to "+
           "the story.");
       return 1;
    }

    actor("You are on the edge of your seat as you listen to",oblist,
          " tell "+OBHIS+" story.");
    all2act(" is on the edge of "+HIS(TP)+" seat as "+HE(TP)+
          " listens to",oblist," tell "+OBHIS+" story.");
    target(" is on the edge of "+HIS(TP)+" seat as "+HE(TP)+
          " listens to your story.", oblist);
    return 1;
}

int
stemphasis(string str)
{
    object *oblist;

    oblist = parse_this(str, "[at] [the] %l");

    if (!present(SPECTACLES_ID, this_player()))
    {
 	write("You have no spectacles to emphasize with.\n");
 	return 1;
    }

    if (!sizeof(oblist))
       NFN0("Shake your spectacles with emphasis at whom?");

    actor("You take off your spectacles and shake them at",oblist,
          " to emphasize your words.");
    all2act(" takes off "+HIS(TP)+" spectacles and shakes them at",
          oblist," to emphasize "+HIS(TP)+" words.");
    target(" takes off "+HIS(TP)+" spectacles and shakes them at "+
           "you to emphasize "+HIS(TP)+" words.", oblist);
    return 1;
}

int
stgaze()
{
   SOULDESC("considering how today's events will make a fine story"); 
   write("You sit for a moment, gazing at your storybook as you "+
         "consider how today's events will make a fine story.\n");
   all(" sits for a moment, gazing at "+HIS(TP)+" storybook as "+
         HE(TP)+" considers how today's events will make a fine "+
         "story.");
   return 1;
}

int
stgreet(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "warmly", 1);

    oblist = parse_this(how[0], "[the] %l");

    if (!sizeof(oblist))
       NFN0("Greet whom?");

    actor("You shake",oblist,"'s hand"+how[1]+", getting a bit of "+
          "wet ink on "+OBHIM+".");
    all2act(" shakes",oblist,"'s hand"+how[1]+", getting a bit of "+
          "wet ink on "+OBHIM+".");
    target(" shakes your hand"+how[1]+", getting a bit of wet ink "+
          "on you.", oblist);
    return 1;
}

int
stlisten(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "eagerly", 0);

    oblist = parse_this(how[0], "[to] [the] %l");

    if (!sizeof(oblist))
    {
       write("You listen"+how[1]+" to the story.\n");
       all(" listens"+how[1]+" to the story.");
       return 1;
    }

    actor("You listen"+how[1]+" to",oblist,"'s story.");
    all2act(" listens"+how[1]+" to",oblist,"'s story.");
    target(" listens"+how[1]+" to your story.", oblist);
    return 1;
}

int
stlost()
{
   SOULDESC("staring off into space, lost in thought"); 
   write("You stare off into space, lost in your thoughts and all "+
         "the tales in your head.\n");
   all(" stares off into space, lost in "+HIS(TP)+" thoughts "+
         "and all the tales in "+HIS(TP)+" head.");
   return 1;
}

int
stidea()
{
   SOULDESC("scribbling notes on a scrap of paper"); 
   write("You get an idea and hurriedly scribble a few notes on "+
         "a scrap of paper.\n");
   all(" gets an idea and hurriedly scribbles a few notes on "+
         "a scrap of paper.");
   return 1;
}

int
stobserve(string str)
{
   string *how;

   how = parse_adverb_with_space(str, "carefully", 0);

   SOULDESC("observing the surroundings, noting every detail");
   write("You observe your surroundings"+how[1]+", noting every "+ 
         "detail for future reference.\n");
   all(" observes "+HIS(TP)+" surroundings"+how[1]+", noting "+
         "every detail for future reference.");
   return 1;
}

int
stpause(string str)
{
   string *how;

   how = parse_adverb_with_space(str, "dramatically", 0);

   write("You pause"+how[1]+" and let your words take their full "+ 
         "effect before continuing.\n");
   all(" pauses"+how[1]+" and lets "+HIS(TP)+" words take their "+
         "full effect before continuing.");
   return 1;
}

int
stpeer(string str)
{
    object *oblist;
    string *how;

    if (!present(SPECTACLES_ID, this_player()))
    {
	write("You have no spectacles to peer over.\n");
	return 1;
    }

    how = parse_adverb_with_space(str, "silently", 0);

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
       NFN0("Peer over your spectacles at whom?");

    actor("You peer"+how[1]+" at",oblist," over the top of "+
       "your reading spectacles.");
    all2act(" peers"+how[1]+" at",oblist," over the top of "+
       HIS(TP)+" reading spectacles.");
    target(" peers"+how[1]+" at you over the top of "+HIS(TP)+
       " reading spectacles.", oblist);
    return 1;
}

int
strub()
{
   write("You thoughtfully rub your ink-stained fingers together, "+
         "your demeanor pensive and quiet.\n");
   all(" thoughtfully rubs "+HIS(TP)+" ink-stained fingertips "+
         "together, "+HIS(TP)+" demeanor pensive and quiet.");
   return 1;
}

int
stsigh(string str)
{
   string *how;

   how = parse_adverb_with_space(str, "wistfully", 0);

   SOULDESC("remembering old friends and the stories they have shared"); 
   write("You sigh"+how[1]+", remembering old friends and the "+
         "stories they have shared.\n");
   all(" sighs"+how[1]+", remembering old friends and the stories "+
         "they have shared.");
   return 1;
}

int
stsmile(string str)
{
   string *how;

   how = parse_adverb_with_space(str, "warmly", 0);

   SOULDESC("smiling, remembering happy times and glorious tales"); 
   write("You smile"+how[1]+", remembering happy times and "+
         "glorious tales.\n");
   all(" smiles"+how[1]+", remembering happy times and glorious "+
         "tales.");
   return 1;
}

int
ststory(string str)
{
   string *how;

   how = parse_adverb_with_space(str, "hopefully", 0);

   SOULDESC("hoping someone has a story to tell"); 
   write("You study the people around you"+how[1]+", wondering if "+ 
         "any of them might have a story to tell.\n");
   all(" studies the people around "+HIM(TP)+how[1]+", wondering "+
         "if any of them might have a story to tell.");
   return 1;
}

int
sttear()
{
   if (!present(SPECTACLES_ID, this_player()))
   {
	write("You wipe a tear from your eye before continuing.\n");
        all(" wipes a tear from "+HIS(TP)+" eye before continuing.\n");
	return 1;
   }

   write("You remove your spectacles for a moment to wipe away a "+
         "tear before continuing.\n");
   all(" removes "+HIS(TP)+" spectacles for a moment to wipe away a "+
         "tear before continuing.");
   return 1;
}

int
help(string str)
{
    string subject, filename;

    if (!strlen(str))
        return 0;

    setuid();
    seteuid(getuid(TO));

    if (str == "teller" || str == "storyteller")
    {
        this_player()->more(read_file(TELLER_HELP_DIR + "help.txt"), 0);
        return 1;
    }

    if (sscanf(str, "teller %s", subject) != 1)
        return 0;

    filename = TELLER_HELP_DIR + subject + ".txt";

    if (file_size(filename) <= 0)
    {
        NFN0("No help on that subject I'm afraid.");
    }

    cat(filename);
    return 1;
}
