/*
 * Emotions for the Union of the Warriors of
 * Shadow.
 *  Cirion 032596
 */

#include <adverbs.h>
#include <cmdparse.h>

/* ****** Definitions ****** */
#define SOULDESC(x)  (TP->add_prop(LIVE_S_SOULEXTRA, (x)))
#define HIS          (TP->query_possessive())
#define HE           (TP->query_pronoun())
#define HIM          (TP->query_objective())
#define DEPTH        2

/* **** Prototypes **** */
string cry_name();

/* ***** Pain & Joy Functions ***** */
string cry_name()
{
    object    pobj;
    int       i;
    string    str, myrace;
    string   *race_str = ({ "gnome","gnomish",
                            "elf","elvish",
                            "dwarf","dwarvish",
                            "human","human's",
                            "hobbit","squeaky",
                            "goblin","goblin's" });

    i = member_array(TP->query_race(), race_str);
    if(i < 0 || i >= sizeof(race_str) - 1)
      myrace = TP->query_race();
    else
      myrace = race_str[i + 1];

    pobj = previous_object(); /* Reciever of message */
    if (file_name(pobj) == "/secure/vbfc_object")
	pobj = previous_object(-1);

    if(pobj->query_met(TP))
    {
      if (environment(pobj) == environment(TP))
        return TP->query_name()+" cries";
      else
        return "You hear "+TP->query_name()+" crying";
    }
    else
    {
	if (environment(pobj) == environment(TP))
	    str = TP->query_nonmet_name()+" cries";
	else
	    str = TP->query_gender_string() + " " +
		myrace + " voice cries";
	return capitalize(LANG_ADDART(str));
    }
}

string
multiple_possessive(object *obs)
{
    if(sizeof(obs) > 1)
        return "their";
    else
        return obs[0]->query_possessive();
}

/* **********EMOTIONS*********** */
int angry(string str)
{
  object *oblist;

  if(!strlen(str))
  {
    write("Your eyes burn with the dark fire as you "
         +"show your anger.\n");
    allbb("'s eyes seem to burn with a fearsome dark fire.");

    TP->emote_adjust_union_virtue(US_PRIDE, 2);

    SOULDESC("looking very angry");
    return 1;
  }

  oblist = parse_this(str, "[before] / [at] / [to] [the] %l");
  if(!sizeof(oblist))
  {
    notify_fail("Show your anger to whom?\n");
    return 0;
  }

  actor("You turn towards",oblist,", showing your anger.");
  targetbb(" turns towards you, "+HIS+" black eyes aglow "
          +"with a fearsome dark flame.", oblist);
  all2actbb(" turns towards",oblist,", "+HIS
          +" black eyes burning with a fearsome dark flame.");
  SOULDESC("looking very angry");
  TP->emote_adjust_union_virtue(US_PRIDE, 3);

  return 1;
}

int blink(string str)
{
  if(strlen(str))
  {
    notify_fail("Blink what?\n");
    return 0;
   }

  write("You blink.\n");
  allbb(" blinks.");
  SOULDESC("blinking");
  return 1;
}

int brood(string str)
{
    str = check_adverb_with_space(str, "deeply");

    if (str == NO_ADVERB_WITH_SPACE)
    {
	notify_fail("Brood how?\n");
	return 0;
    }

    TP->emote_adjust_union_virtue(US_DIGNITY, 2);

    write("You brood" + str + " over the matter at hand.\n");
    allbb(" broods" + str + " over some matter.");
    SOULDESC("brooding");
    return 1;
}

int calm(string str)
{
  if(strlen(str))
  {
    notify_fail("How do you want to be calm?\n");
    return 0;
   }

  /* ppanic yields % of max panic, defined in ~union/lib/filters.h */
  if(ppanic(TP) < 50)
  {
    TP->emote_adjust_union_virtue(US_DIGNITY, 3);

    write("You remain calm despite the peril ahead.\n");
    allbb(" remains calm.");
    SOULDESC("looking calm and collected");
    return 1;
  }

  TP->emote_adjust_union_virtue(US_PRIDE, -3);

  write("You try to keep your calm, but fail completely.\n");
  allbb(" tries to keep "+HIS+" calm, but fails.");
  SOULDESC("looking extremely scared and panicky");
  return 1;
}

int clash(string str)
{
  string    ret;
  mixed    *objs = ({ });

  if(TP->query_weapon(W_RIGHT))
    objs += ({TP->query_weapon(W_RIGHT)});

  if(TP->query_weapon(W_LEFT))
    objs += ({TP->query_weapon(W_LEFT)});

  if(sizeof(objs) < 2)
  {
    notify_fail("You would need to be wielding two weapons "
        +"to do that.\n");
    return 0;
  }

  if(TP->query_stat(SS_STR) > 100)
    ret = ".\nSparks fly everywhere";
  else
    ret = "";

  write("You clash "+LANG_THESHORT(objs[0])
       +" against "+LANG_THESHORT(objs[1])
       +", making a loud noise"+ret+".\n");
  all(" clashes "+HIS+" "+objs[0]->short()
       +" against "+HIS+" "+objs[1]->short()
       +", making a loud noise"+ret+".");
  return 1;
}

int cross(string str)
{
  string    ret;
  mixed    *objs = ({ });

  if(TP->query_weapon(W_RIGHT))
    objs += ({TP->query_weapon(W_RIGHT)});

  if(TP->query_weapon(W_LEFT))
    objs += ({TP->query_weapon(W_LEFT)});

  if(sizeof(objs) < 2)
  {
    notify_fail("You would need to be wielding two weapons "
        +"to do that.\n");
    return 0;
  }

  TP->emote_adjust_union_virtue(US_GRACE, 2);

  write("You hold "+LANG_THESHORT(objs[0])
       +" across "+LANG_THESHORT(objs[1])
       +" in a cross before you.\n");
  allbb(" holds "+HIS+" "+objs[0]->short()
       +" across "+HIS+" "+objs[1]->short()
       +" before "+TP->query_objective()+", making a cross.");
  return 1;
}

int curse(string str)
{
   object *oblist;
   string *how;

   how = parse_adverb_with_space(str, "furiously", 0);

   if(!strlen(how[0]))
   {
     write("You curse" + how[1] + " in the name of Plalgus.\n");
     all(" curses" + how[1] + " in the name of Plalgus.");
     SOULDESC("cursing angrily");
     return 1;
   }

   oblist = parse_this(how[0], "[at] [the] %l");

   if(!sizeof(oblist))
   {
     notify_fail("Curse [how] at whom?\n");
     return 0;
   }

   actor("You curse" + how[1] + " at", oblist);
   target(" curses" + how[1] + " at you.", oblist);
   all2act(" curses" + how[1] + " at", oblist);
   SOULDESC("cursing angrily");
   return 1;
}

int dance(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        TP->emote_adjust_union_virtue(US_GRACE, 2);
	write("You dance with a sinuous, weaving motion.\n");
	all(" seems to dance with a strange, weaving motion.");
        SOULDESC("swaying back and forth slowly");
	return 1;
    }

    oblist = parse_this(str, "[with] / [before] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Dance with whom?\n");
	return 0;
    }

    TP->emote_adjust_union_virtue(US_GRACE, 2);

    target(" dances before you with a strange, weaving motion.", oblist);
    actor("You dance before", oblist, " with a sinuous, weaving "
         +"motion.");
    all2act(" dances before", oblist, " with a sinuous, weaving motion");
    SOULDESC("swaying back and forth slowly");
    return 1;
}

int dignity(string str)
{
  object *oblist;

  if(!strlen(str))
  {
    TP->emote_adjust_union_virtue(US_DIGNITY, 2);

    write("You stand to your full height, dignified and proud.\n");
    allbb(" stands to "+HIS+" full height, dignified "
         +"and proud.");
    SOULDESC("standing dignified and proud");
    return 1;
  }

  oblist = parse_this(str, "[before] [the] %l");
  if(!sizeof(oblist))
  {
    notify_fail("Stand dignified before whom?\n");
    return 0;
  }

  targetbb(" stands to "+HIS+" full height before you, "
        +"dignified and proud.", oblist);
  actor("You stand dignified before", oblist, ".");
  all2actbb(" stands to "+HIS+" full height before",oblist,
        ", dignified and proud.");

  TP->emote_adjust_union_virtue(US_DIGNITY, 5);

  SOULDESC("standing dignified and proud");
  return 1;
}

int ectios(string str)
{
  object *oblist;

  if(!strlen(str))
  {
    write("You touch two fingers to your lips in farewell and whisper \"Ectios\".\n");
    allbb(" brushes two fingers to " + POSSESS(TP) + " lips briefly "
         +"in a salute of farewell and whispers \"Ectios\".\n"
         +CAP(POSSESS(TP)) + " eyes flicker momentarily with a lonely flame.");
    return 1;
  }

  oblist = parse_this(str, "[to] [the] %l");
  if(!sizeof(oblist))
  {
    notify_fail("Bid farewell to whom?\n");
    return 0;
  }

  actor("You touch two fingers to your lips in farewell and whisper \"Ectios\" to",oblist,".");
  targetbb(" turns towards you and brushes two fingers to " + POSSESS(TP) + " lips briefly "
         +"in a salute of farewell, whispering \"Ectios\".", oblist);
  all2actbb(" turns towards",oblist," and whispers something softly.\n"
         +CAP(POSSESS(TP)) + " eyes flicker momentarily with a lonely flame.");

  oblist->union_hook_got_ectios(TP);

  SOULDESC("looking very angry");
  return 1;
}

int gaze(string str)
{
   object *oblist;
   string *how;

   how = parse_adverb_with_space(str, "menacingly", 0);

   oblist = parse_this(how[0], "[at] [the] %l");

   if(!sizeof(oblist))
   {
     write("You gaze" + how[1] + " about, your eyes "
           +"aglow with dark flames.\n");
     allbb(" gazes" + how[1] + " about, "
           +HIS+" eyes aglow with a dark flame.");
     SOULDESC("gazing"+how[1]);
     return 1;
   }

   targetbb(" gazes" + how[1] + " at you, a dark fire "
           +"burning in "+HIS+" eyes.", oblist);
   actor("You gaze" + how[1] + " at", oblist,", your eyes "
           +"aglow with dark flames.");
   all2actbb(" gazes" + how[1] + " at", oblist,", "
           +HIS+" eyes aglow with a dark flame.");
   SOULDESC("gazing"+how[1]);
   return 1;
}

int glare(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "fiercefully", 0);

    if (!strlen(how[0]))
    {
	write("You glare" + how[1] + ".\n");
	allbb(" glares" + how[1] + ".");
	SOULDESC("glaring" + how[1]);
	return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Glare [how] at whom?\n");
	return 0;
    }

    SOULDESC("glaring" + how[1]);
    targetbb(" glares" + how[1] + " at you.", oblist);
    actor("You glare" + how[1] + " at", oblist);
    all2actbb(" glares" + how[1] + " at", oblist);
    return 1;
}

int greet(string str)
{
  object *oblist;

  oblist = parse_this(str, "[the] %l");

  if(!sizeof(oblist))
  {
    notify_fail("Greet whom?\n");
    return 0;
  }

  targetbb(" greets you with a slight nod of " + HIS
        +" head.", oblist);
  actor("You greet", oblist," with a slight nod of your head.");
  all2actbb(" greets", oblist," with a slight nod of "+HIS+" head.");
  return 1;
}


#define IND_DIRECTIONS ({ "up", "down", "north", "south", "west", "east", \
    "northwest", "southwest", "northeast", "southeast" })

int indicate(string str)
{
   object *oblist,
           knife;
   string *tmp;

   notify_fail("You would need to be holding a knife to do that.\n");
   if(!my_knife())
     return 0;

   knife = my_knife();

   notify_fail("Where do you want to indicate with your "
              +knife->short()+"?\n");

   if(!strlen(str))
   {
     write("You wave your "+knife->short()+" in a general direction.\n");
     allbb(" waves "+HIS+" "+knife->short()+" in a general direction.");
     return 1;
   }

   str = lower_case(str);
   if (member_array(str, IND_DIRECTIONS) >= 0)
   {
     write("You indicate " + str + " with your "+knife->short()+".\n");
     allbb(" indicates " + str + " with "+HIS+" "+knife->short()+".");
     return 1;
   }

   if(str == (string) TP->query_real_name() ||
	str == "me" || str == "myself")
   {
     write("You point your "+knife->short()+" at yourself.\n");
     allbb(" points "+HIS+" "+knife->short()+" at " 
            + TP->query_objective() + "self.");
     return 1;
   }

   oblist = parse_this(str, "[at] [the] %l");

   if(!sizeof(oblist))
   {
     tmp = explode(str, " ");
     if(sizeof(tmp) > 1 && tmp[0] == "at")
        str = implode(tmp[1 .. sizeof(tmp) - 1], " ");
     oblist = FIND_STR_IN_OBJECT(str, environment(TP));
     if(!sizeof(oblist))
     {
        if(environment(TP)->item_id(str))
        {
          write("You indicate the " + str
               +" with your "+knife->short()+".\n");
          allbb(" indicates " + LANG_ADDART(str) + " with "
               +HIS+" "+knife->short()+".");
          return 1;
         }
      return 0;
      }
     write("You point at " + LANG_THESHORT(oblist[0])
          +" with your "+knife->short()+".\n");
     allbb(" points at " + LANG_THESHORT(oblist[0])
          +" with "+HIS+" "+knife->short() + ".");
     return 1;
    }

    targetbb(" points at you with "+HIS+" "+knife->short()+".", oblist);
    actor("You point at", oblist," with your "+knife->short()+".");
    all2actbb(" points at", oblist, " with "+HIS+" "+knife->short()+".");
    return 1;
}

int interrupt(string str)
{
  object *oblist;

  if(!strlen(str))
  {
    write("You raise your hand, signifying that you would like "
     + "to speak.\n");
    allbb("raises " + POSSESS(TP) + " hand, signifying that "
     + TP->query_pronoun() + " would like to say something.");
    SOULDESC("trying to say something");
    return 1;
  }

  oblist = parse_this(str, "[the] %l");

  if(!sizeof(oblist))
  {
    notify_fail("Interrupt whom?\n");
    return 0;
  }

  targetbb(" interrupts you, trying to say something", oblist);
  actor("You interrupt", oblist,", indicating that you want "
       +"to speak.");
  all2actbb(" interrupts", oblist,", indicating that "
       +this_player()->query_pronoun()+" wants to speak");
  SOULDESC("trying to say something");
  return 1;
}

int joy(string what)
{
    object *rooms;
    object troom;
    int    index;
    int    size;

    if(!TP)
      return 0;

    if(!(troom = environment(TP)))
      return 0;

    rooms = FIND_NEIGHBOURS(troom, DEPTH);

    index = -1;
    size = sizeof(rooms);
    while(++index < size)
    {
      tell_room(rooms[index], "@@cry_name:" + file_name(this_object()) +
        "@@ out loud and joyous.\n", TP);
    }

    TP->emote_adjust_union_virtue(US_DIGNITY, 2);

    write("You cry out in a loud, joyous voice.\n");
    SOULDESC("looking euphoric");
    return 1;
}

int laugh(string str)
{
   object *oblist;
   string *how;

   how = parse_adverb_with_space(str, "silently", 0);

   if(!strlen(how[0]))
   {
     write("You laugh" + how[1] + ".\n");
     all(" laughs" + how[1] + ".");
     SOULDESC("laughing" + how[1]);
     return 1;
   }

  oblist = parse_this(how[0], "[at] [the] %l");

  if(!sizeof(oblist))
  {
     notify_fail("Laugh how [at whom]?\n");
     return 0;
  }

  target(" laughs" + how[1] + " at you.", oblist);
  actor("You laugh" + how[1] + " at", oblist, ".");
  all2act(" laughs" + how[1] + " at", oblist);
  SOULDESC("laughing" + how[1]);
  return 1;
}

int mourn(string str)
{
  object  ob,
         *obs,
          who;
  string  name;

  if(!strlen(str))
  {
   write("You show your grief.\n");
   allbb(" mourns sadly.");
   SOULDESC("grieving");
   return 1;
  }

  parse_command(str, ({}), "[over] / [for] [the] / [a] %s", str);
  obs = FIND_STR_IN_OBJECT(str, ENV(TP));
  if(!sizeof(obs)) obs = FIND_STR_IN_OBJECT(str, TP);
  if(!sizeof(obs))
  {
    notify_fail("Mourn over what?\n");
    return 0;
  }

  ob = obs[0];
  if(living(ob))
  {
    actor("But",({ob})," is not yet dead.");
    return 1;
  }

  if(!ob->id("corpse"))
  {
    notify_fail("That would be silly.\n");
    return 0;
  }

  actor("You mourn over "+LANG_THESHORT(ob));
  allbb(" mourns over "+LANG_THESHORT(ob)+".");
  SOULDESC("grieving");

  if(sizeof(ob->query_names()) < 2)
   return 1;

  name = ob->query_names()[2];
  if(strlen(name))
    sscanf(name, "corpse of %s", name);

  who = find_player(lower_case(name));

  if(!who || !who->query_ghost())
   return 1;

  TP->emote_adjust_union_virtue(US_DIGNITY, 10);

  write("You feel comforted slightly.\n");
  who->catch_msg("A sense of grief falls upon you, and enshrouds "
     +"you like a veil.\nYou feel the presence of "+QTNAME(TP)+".\n");
  return 1;
}

int murmur(string str)
{
   object *oblist;

   if(!strlen(str))
   {
     write("You murmur something under your breath.\n");
     all(" murmurs something incomprehensible.");
     SOULDESC("murmuring about something");
     return 1;
   }

   if((strlen(str) > 60) &&
      (!(TP->query_wiz_level())))
   {
     write("You don't have enough breath to murmur that much.\n");
     all(" murmurs something incomprehensible.");
     SOULDESC("murmuring about something");
     return 1;
   }

  write("You murmur something about " + str + "\n");
  all(" murmurs something about " + str);
  SOULDESC("murmuring something");
  return 1;
}

#include "emotion2.h"
