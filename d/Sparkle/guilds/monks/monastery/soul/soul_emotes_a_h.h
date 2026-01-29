/*******************************************************************\
| SOUL_EMOTES_A_H.H                                                 |
\*******************************************************************/

/*
 * 07/06/03 Arandir     Added the mdisdain and mhumble emotes
 * 07/05/26 Arandir     Fixed a typo in the mbless emote
 * 07/05/22 Arandir     Fixed a typo in the mbreathe emote
 * 06/09/20 Arandir     Fixed use of Q macros instead of X macros
 * 06/09/02 Arandir     Fixed use of XOBJ style macros
 * 06/08/26 Arandir     Removed the focus skill
 * 06/08/16 Arandir     Added the mfocus emote
 * 04/11/18 Arandir     Typo fix
 * 04/08/17 Arandir     Added action attributes to other emote calls
 * 04/08/15 Arandir     Minor change to mbless
 *                      Added action attributes to parse_this
 * 04/03/06 Arandir     Typo fix
 * 03/09/20 Arandir     Added the mbicker and mhonor emotes
 * 03/09/14 Arandir     Added the mbreathe emote
 * 03/09/14 Arandir     Removed the thys and thous in error messages
 * 03/09/07 Arandir     Fixed typos due to all2act not expanding VBFC
 * 02/07/01 Arandir     Polished up
 * 02/05/03 Arandir	Ported to new area without rewrite
 * 01/08/12 Manat	Changed so that commands may be disabled
 * 01/02/02 Manat	Changed mk align
 * 01/01/20 Manat	Changed mk hand
 * 99/02/01 Lilith	Emotes updated and added
 * 96/04/16 Cirion	Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

/*
 * Function name : m_action_bicker
 *
 */

int m_action_bicker (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  string sFragment;

  notify_fail ("With whom do you wish to bicker ?\n");

  if (!strlen (sArgs))
  {
    write ("You bicker about trivial matters.\n");
    all (" bickers about trivial matters.", "", ACTION_AURAL | ACTION_VISUAL);
    M_SOULDESC ("looking bored");

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[with] [the] %l", ACTION_AURAL | ACTION_VISUAL);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You bicker with", aoObjects, " about trivial matters.");
  target (" bickers with you about trivial matters.", aoObjects, "", ACTION_AURAL | ACTION_VISUAL);
  all2act (" bickers with", aoObjects, " about trivial matters.", "", ACTION_AURAL | ACTION_VISUAL);
  M_SOULDESC ("looking bored");

  return (TRUE);
}


/*
 * Function name: m_action_bless
 *
 */

int m_action_bless (string sArgs)
{
  object oWho = this_player ();
  string sWho = dg_get_name (oWho);
  string sFragmentSegoy = "blessing of Segoy, the Dragon Father of All Creation";
  string sFragmentTooth = "the likeness of a dragon tooth in the air";
  string sFragment;
  string sBlesser;
  object *aoObjects;
  object oObject;
  int    iObject;

  if (oWho->query_prop (LIVE_M_MOUTH_BLOCKED))
  {
    notify_fail ("You can't seem to speak.\n");
    return (FALSE);
  }

  notify_fail ("Whom or what do you wish to bless ?\n");

  // Blessing yourself is different from blessing others.

  if ((sArgs == sWho) ||
      (sArgs == "me") ||
      (sArgs == "myself") ||
      !strlen (sArgs))
  {
    write ("You ask the " + sFragmentSegoy + ", for your endeavor.\n");
    allbb (" seeks the " + sFragmentSegoy + ", for " + XOBJ (oWho) + "self.", "", ACTION_PROXIMATE | ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[the] %i", ACTION_PROXIMATE | ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);

  // If somebody was blessed already, let the player know but
  // continue with the blessing, so that the need for blessing
  // by council member on dedication can eventually be met.

  for (iObject = 0 ; iObject < sizeof (aoObjects) ; iObject ++)
  {
    oObject = aoObjects [iObject];
    sBlesser = oObject->query_prop (M_PROP_TMP_I_BLESSED);
    if (stringp (sBlesser))
    {
      if (sBlesser == sWho)
      {
        write ("You recall that you have already blessed " + LANG_THESHORT (oObject) + ".\n");
      }
      else
      {
        write ("You sense that " + capitalize (sBlesser) + " has already blessed " + LANG_THESHORT (oObject) + ".\n");
      }
    }
    oObject->add_prop (M_PROP_TMP_I_BLESSED, sWho);
  }

  switch (sizeof (aoObjects))
  {
    case 0:  return (FALSE);
    case 1:  sFragment = XOBJ (aoObjects [0]);
             break;
    default: sFragment = "them";
             break;
  }

  actor ("You sketch " + sFragmentTooth + " near", aoObjects, " and solemnly ask " +
         "the " + sFragmentSegoy + ", over " + sFragment + ".");
  targetbb (" sketches " + sFragmentTooth + " and asks the " +
            sFragmentSegoy + ", over you.", aoObjects, "",
            ACTION_PROXIMATE | ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);
  all2actbb (" sketches " + sFragmentTooth + " near", aoObjects, " and solemnly " +
             "asks the " + sFragmentSegoy + ", over " + sFragment + ".", "",
             ACTION_PROXIMATE | ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);

  return (TRUE);
}


/*
 * Function name : m_action_bow
 *
 */

int m_action_bow (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  string sFragment;

  notify_fail ("To whom do you wish to bow ?\n");

  if (!strlen (sArgs))
  {
    write ("You drop your arms to your sides and perform " +
           "a small bow, holding it for a fraction of a second " +
           "before standing fully erect.\n");
    allbb (" drops " + XPOS (oWho) + " arms to " +
           XPOS (oWho) + " sides and performs a small bow.", "",
           ACTION_PROXIMATE | ACTION_VISUAL | ACTION_INGRATIATORY);

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[to] [the] %l", ACTION_PROXIMATE | ACTION_VISUAL | ACTION_INGRATIATORY);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You drop your arms to your sides and perform " +
         "a small bow to", aoObjects, ", holding it for a " +
         "fraction of a second before standing fully erect.");
  targetbb (" drops " + XPOS (oWho) + " arms to " + XPOS (oWho) +
            " sides and performs a small bow to you.", aoObjects, "",
            ACTION_PROXIMATE | ACTION_VISUAL | ACTION_INGRATIATORY);
  all2actbb (" drops " + XPOS (oWho) + " arms to " + XPOS (oWho) +
             " sides and performs a small bow to", aoObjects, "",
             ACTION_PROXIMATE | ACTION_VISUAL | ACTION_INGRATIATORY);

  return (TRUE);
}


/*
 * Function name : m_action_breathe
 *
 */

int m_action_breathe (string sArgs)
{
  object oWho = this_player ();

  write ("You breathe heavily from all the toil of your hardships.\n");
  all (" breathes heavily. " + XCPNOUN (oWho) + " must be toiling hard.", "", ACTION_AURAL | ACTION_VISUAL);
  M_SOULDESC ("breathing heavily");

  return (TRUE);
}


/*
 * Function name: m_action_center
 *
 */

int m_action_center (string sArgs)
{
  object oWho = this_player ();
  string sFragmentBreathe = "You breathe in deeply, briefly tapping the dragon " +
                            "spirit within and centering yourself so that you " +
                            "might ignore the";
  string sFragmentProvoke = "provoke " + XOBJ (oWho) + ", nor disturb " +
                            XPOS (oWho) + " equanimity";
  object *aoObjects;

  notify_fail ("Whom or what do you wish to ignore ?\n");

  if (oWho->resolve_task (TASK_ROUTINE,
                          ({ M_SKILL_FORMING_CLUB,
                             M_SKILL_FORMING_BLADE,
                             M_SKILL_FORMING_STICK })) > 0)
  {
    if (!strlen (sArgs))
    {
      write (sFragmentBreathe + " distractions of your surroundings.\n");
      all (" seems to radiate a calm certainty that leaves you with the " +
           "feeling that nothing can " + sFragmentProvoke + ".", "", ACTION_VISUAL);
    }
    else
    {
      aoObjects = parse_this (sArgs, "[the] %i", ACTION_VISUAL);
      if (sizeof (aoObjects) != 1) return (FALSE);

      actor (sFragmentBreathe + " provocations of", aoObjects, ".");
      target (" seems to radiate a calm certainty that leaves you " +
              "with the feeling that nothing you can do will " +
              sFragmentProvoke + ".", aoObjects, "", ACTION_VISUAL);
      all2act (" seems to radiate a calm certainty that leaves you " +
               "with the feeling that nothing", aoObjects, " can do will " +
               sFragmentProvoke + ".", "", ACTION_VISUAL);
    }

    M_SOULDESC ("radiating a calm certainty");
  }
  else
  {
    write ("You breathe deeply and attempt to center yourself, " +
           "but fail.\n");
    all (" looks momentarily disconcerted.", "", ACTION_VISUAL);
  }

  return (TRUE);
}


/*
 * Function name : m_action_chant
 *
 */

int m_action_chant (string sArgs)
{
  object oWho = this_player ();
  string sFragmentLore = "a bit of dragon lore in an arcane language";

  if (oWho->query_prop (LIVE_M_MOUTH_BLOCKED))
  {
    notify_fail ("You can't seem to speak.\n");
    return (FALSE);
  }

  switch (oWho->query_race_name ())
  {
    case "elf":
      write ("You close your eyes and raise your mellifluous " +
             "voice to chant " + sFragmentLore + ".\n");
      all (" raises " + XPOS (oWho) + " mellifluous voice to " +
           "chant " + sFragmentLore + ".", "", ACTION_AURAL);
      M_SOULDESC ("chanting melliflously");
      break;

    case "hobbit":
      write ("In a voice like that of a chirping bird, you " +
             "close your eyes and chant " + sFragmentLore + ".\n");
      all (", sounding like a chirping bird, raises " + XPOS (oWho) +
           "voice to chant " + sFragmentLore + ".", "", ACTION_AURAL);
      M_SOULDESC ("chanting quickly");
      break;

    case "goblin":
      write ("You raise your low, gravelly voice to chant " +
             sFragmentLore + ".\n");
      all (" raises " + XPOS (oWho) + " low, gravelly voice to " +
           "chant " + sFragmentLore + ".", "", ACTION_AURAL);
      M_SOULDESC ("chanting deeply");
      break;

    case "dwarf":
      write ("You raise your deep, earthy voice to chant " + sFragmentLore + ".\n");
      all (" raises " + XPOS (oWho) + " deep, earthy voice to " + "chant " + sFragmentLore + ".", "", ACTION_AURAL);
      M_SOULDESC ("chanting deeply");
      break;

    default:
      write ("You raise your full, melodious voice to chant " + sFragmentLore + ".\n");
      all (" raises " + XPOS (oWho)+ " voice to chant " + sFragmentLore + ".", "", ACTION_AURAL);
      M_SOULDESC ("chanting with a full, melodious voice");
      break;
  }

  return (TRUE);
}


/*
 * Function name : m_action_chastise
 *
 */

int m_action_chastise (string sArgs)
{
  object *aoObjects;

  notify_fail ("Whom do you wish to chastize ?\n");

  if (!strlen (sArgs)) return (FALSE);

  aoObjects = parse_this (sArgs, "[the] %l", ACTION_VISUAL);

  switch (sizeof (aoObjects))
  {
    case 0:
      return (FALSE);

    case 1:
      actor ("You allow the barest hint of castigation to " +
             "show on your face as you meet", aoObjects, "'s eyes.");
      targetbb (" raises wise, fiery eyes to meet yours, and with" +
               "in their implacable depths you see the barest hint " +
               "of castigation.", aoObjects, "",
               ACTION_VISUAL);
      all2actbb (" looks for a long moment into", aoObjects,"'s eyes.", "",
                 ACTION_VISUAL);
      break;

    default:
      actor ("You allow the barest hint of castigation to " +
             "show on your face as you meet the eyes of", aoObjects, ".");
      targetbb (" raises wise, fiery eyes to meet yours, and with" +
                "in their implacable depths you see the barest hint " +
                "of castigation.", aoObjects, "", ACTION_VISUAL);
      break;
  }

  return (TRUE);
}


/*
 * Function name : m_action_control
 *
 */

int m_action_control (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;

  notify_fail ("Your anger at whom do you wish to control ?\n");

  if (!strlen (sArgs))
  {
    write ("You fight to control your anger as you have " +
           "learned in your studies of the dragon discipline.\n");
    all ("'s face visibly clouds as " + XPNOUN (oWho) + " fights to " +
         "control " + XPOS (oWho) + " anger.", "", ACTION_VISUAL);

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[my] [anger] [at] [the] %l", ACTION_VISUAL);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You fight to control your anger with", aoObjects,", using " +
         "what you have learned in your studies of the dragon " +
         "discipline.");
  target ("'s face clouds visibly as " + XPNOUN (oWho) + " struggles to " +
          "control " + XPOS (oWho) + " anger at your behavior.", aoObjects, "",
          ACTION_VISUAL);
  all2act (" clouds visibly in the face as " + XPNOUN (oWho) + " fights to " +
           "control " + XPOS (oWho) + " anger at", aoObjects, "'s behavior.", "",
           ACTION_VISUAL);

  return (TRUE);
}


/*
 * Function name : m_action_dedicate
 *
 */

int m_action_dedicate (string sArgs)
{
  object oWho = this_player ();

  notify_fail ("You can only dedicate yourself.\n");

  if (sArgs != "myself") return (FALSE);

  if (m_is_monk (oWho, SS_OCCUP))
  {
    write ("You take a moment to mentally dedicate your " +
           "life to mastering the dragon discipline.\n" +
           "You feel a renewed sense of purpose.\n");
    allbb (" appears to have a renewed sense of purpose.", "", ACTION_VISUAL);
    M_SOULDESC ("looking purposeful");
  }
  else
  {
    write ("You take a moment to consider the possibility of " +
           "fully dedicating yourself to the mastery of the " +
           "dragon discipline.\n");
    allbb (" appears to be considering something.", "", ACTION_VISUAL);
  }

  return (TRUE);
}


/*
 * Function name: m_action_defend
 *
 */

int m_action_defend (string sArgs)
{
  object oWho = this_player ();
  string sWho = dg_get_name (oWho);
  object *aoObjects;
  string sFragmentGrace = "with serpentine grace and economy of movement";

  notify_fail ("Whom do you wish to defend ?\n");

  if ((sArgs == sWho) ||
      (sArgs == "me") ||
      (sArgs == "myself") ||
      (!strlen (sArgs)))
  {
    write ("You shift " + sFragmentGrace + " into a stance from which you " +
           "might better defend yourself.\n");
    allbb (" shifts " + sFragmentGrace + " into a stance from which " +
           XPNOUN (oWho) + " can defend " + XOBJ (oWho) + "self, a look " +
           "of calm preparation on " + XPOS (oWho) + " face.", "",
           ACTION_PROXIMATE | ACTION_VISUAL | ACTION_INGRATIATORY);

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[the] %l", ACTION_PROXIMATE | ACTION_VISUAL | ACTION_INGRATIATORY);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You shift " + sFragmentGrace + " into a stance from which you " +
         "might better defend", aoObjects, " against harm.");
  targetbb (" shifts " + sFragmentGrace + " into a stance from which " +
            XPNOUN (oWho) + " can more readily defend you, a look of calm " +
            "preparation on " + XPOS (oWho) + " face.", aoObjects, "",
            ACTION_PROXIMATE | ACTION_VISUAL | ACTION_INGRATIATORY);
  all2actbb (" shifts " + sFragmentGrace + " into a stance from which " +
             XPNOUN (oWho) + " can more readily defend", aoObjects, " a look of " +
             "calm preparation on " + XPOS (oWho) + " face.", "",
             ACTION_PROXIMATE | ACTION_VISUAL | ACTION_INGRATIATORY);

  return (TRUE);
}


/*
 * Function name : m_action_disdain
 * Description   : This disables the learning in combat.
 *
 */

int m_action_disdain (string sArgs)
{
  object oWho = this_player ();

  write ("You show disdain for the combat abilities of your enemies, certain that there is nothing they could teach you.\n");
  all (" shows disdain for the combat abilities of " + XPOS (oWho) + " enemies.", "", ACTION_VISUAL);
  M_SOULDESC ("radiating disdain");

  m_set_learning (oWho, FALSE);

  return (TRUE);
}


/*
 * Function name : m_action_display
 *
 */

int m_action_display (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  string sFragmentHow;

  if (oWho->query_fatigue () < 10)
  {
    notify_fail ("You are too exhausted to do that.\n");
    return (FALSE);
  }

  switch (oWho->query_skill (SS_UNARM_COMBAT) + random (5) - 3)
  {
    case -99 ..  5:  sFragmentHow = "pathetic";                   break;
    case   6 .. 10:  sFragmentHow = "amateurish";                 break;
    case  11 .. 20:  sFragmentHow = "passable";                   break;
    case  21 .. 30:  sFragmentHow = "mildly impressive";          break;
    case  31 .. 37:  sFragmentHow = "impressive";                 break;
    case  38 .. 46:  sFragmentHow = "very impressive";            break;
    case  47 .. 58:  sFragmentHow = "remarkably agile";           break;
    case  59 .. 70:  sFragmentHow = "fleet and graceful";         break;
    case  71 .. 80:  sFragmentHow = "fluid and dextrous";         break;
    case  81 .. 91:  sFragmentHow = "absolutely dazzling";        break;
    case  92 .. 96:  sFragmentHow = "incredibly swift and fluid"; break;
    case  97 .. 999: sFragmentHow = "impossibly serpentine";      break;
  }

  sFragmentHow = LANG_ADDART (sFragmentHow);

  notify_fail ("Before whom do you wish to display your combat abilities ?\n");

  if (!strlen (sArgs))
  {
    write ("You perform " + sFragmentHow + " display of your " +
           "combat abilities.\n");
    allbb (" performs " + sFragmentHow + " display of " + XPOS (oWho) +
           " combat abilities.", "", ACTION_VISUAL);

    oWho->add_fatigue (-random (10));

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[before] / [for] / [to] [the] %l", ACTION_VISUAL);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You perform " + sFragmentHow + " display of " +
         "your combat abilities before", aoObjects, ".");
  targetbb (" performs " + sFragmentHow + " display of " +
            XPOS (oWho) + " combat abilities before you.", aoObjects, "",
            ACTION_VISUAL);
  all2actbb (" performs " + sFragmentHow + " display of " +
             XPOS (oWho) + " combat abilities before", aoObjects, "",
             ACTION_VISUAL);

  oWho->add_fatigue (-random (10));

  return (TRUE);
}


/*
 * Function name: m_action_drop
 *
 */

int m_action_drop (string sArgs)
{
  string sFragmentBare = "bare of all pretenses of civility, revealing the " +
                         "intent and chilling eyes of a predator";
  object *aoObjects;

  notify_fail ("Before whom do you wish to drop all pretenses ?\n");

  if (!strlen (sArgs))
  {
    write ("You drop all pretenses of civility and stare about " +
           "you with the intent eyes of a predator.\n");
    allbb ("'s equanimity suddenly dissolves. You find yourself " +
           "staring at a face " + sFragmentBare + ".", "",
           ACTION_VISUAL | ACTION_THREATENING);

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[pretenses] [before] [the] %l", ACTION_VISUAL | ACTION_THREATENING);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You drop all pretenses of civility and stare at", aoObjects,
         " with the intent and chilling eyes of a predator.");
  targetbb ("'s equanimity toward you suddenly dissolves. You " +
            "find yourself staring at a face " + sFragmentBare + ".", aoObjects, "",
            ACTION_VISUAL | ACTION_THREATENING);
  all2actbb ("'s equanimity towards", aoObjects, " suddenly dissolves. " +
             "You find yourself staring at a face " + sFragmentBare + ".", "",
             ACTION_VISUAL | ACTION_THREATENING);

  return (TRUE);
}


/*
 * Function name : m_action_fist
 *
 */

int m_action_fist (string sArgs)
{
  object oWho = this_player ();
  string *asAdverb;

  asAdverb = parse_adverb_with_space (sArgs, "triumphantly", FALSE);

  write ("You raise your fist" + asAdverb [1] + " in the air.\n");
  allbb (" raises " + XPOS (oWho) + " fist" + asAdverb [1] + " in the air.", "", ACTION_VISUAL);

  return (TRUE);
}


/*
 * Function name : m_action_focus
 *
 */

int m_action_focus (string sArgs)
{
  object oWho = this_player ();

  write ("As you focus all your energies within yourself, " +
         "everything around becomes very silent.\n");
  allbb (" starts to breathe very slowly and a look of " +
         "relaxed alertness falls upon " + XPOS (oWho) + " face.",
         "",
         ACTION_AURAL | ACTION_VISUAL);

  M_SOULDESC ("very focused");

  return (TRUE);
}


/*
 * Function name: m_action_gaze
 *
 */

int m_action_gaze (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;

  notify_fail ("Upon whom or what do you wish to gaze ?\n");

  if (!strlen (sArgs))
  {
    write ("Your eyes gleam as you reflect upon the vast wisdom " +
           "of the dragons.\n");
    allbb ("'s eyes gleam with the brilliance of untold wisdom.", "",
           ACTION_VISUAL);

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[at] / [upon] [the] %i", ACTION_VISUAL);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You reflect upon the vast wisdom of the dragons as you " +
         "gaze at", aoObjects, ".");
  targetbb ("'s eyes gleam with the brilliance of untold wisdom " +
            "as " + XPNOUN (oWho) + " gazes upon you.", aoObjects, "",
            ACTION_VISUAL);
  all2actbb (" gazes upon", aoObjects, " " + XPOS (oWho) +
             " eyes gleaming with the brilliance of untold wisdom.", "",
             ACTION_VISUAL);

  return (TRUE);
}


/*
 * Function name: m_action_greet
 *
 */

int m_action_greet (string sArgs)
{
  object oWho = this_player ();
  string sWho = dg_get_name (oWho);
  object *aoObjects;
  string sFragmentName;

  notify_fail ("Whom do you wish to greet ?\n");

  if (!strlen (sArgs))
  {
    write ("You greet everone with your open arms.\n");
    allbb (" greets everyone with " + XPOS (oWho) + " open arms.", "",
           ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[the] %i", ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);
  if (!sizeof (aoObjects)) return (FALSE);

  sFragmentName = " as " + capitalize (sWho) + ", " + m_get_title (oWho);

  actor ("You greet", aoObjects, " as a friend of dragons and present " +
         "yourself" + sFragmentName + ".");
  target (" greets you as a friend of dragons and presents " +
          XOBJ (oWho) + "self" + sFragmentName + ".", aoObjects, "",
          ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);
  all2act (" greets", aoObjects, " as a friend of dragons and presents " +
           XOBJ (oWho) + "self" + sFragmentName + ".", "",
           ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);

  return (TRUE);
}


/*
 * Function name: m_action_growl
 *
 */

int m_action_growl (string sArgs)
{
  object oWho = this_player ();
  string sFragmentGrowl = "a low, rumbling growl as a chilling, " +
                          "almost predatory grin creeps across";
  object *aoObjects;

  notify_fail ("At whom do you wish to growl ?\n");

  if (!strlen (sArgs))
  {
    write ("You emit " + sFragmentGrowl + " your lips.\n");
    all (" emits " + sFragmentGrowl + " " + XPOS (oWho) + " lips.", "",
         ACTION_AURAL | ACTION_VISUAL | ACTION_THREATENING);

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[at] [the] %i", ACTION_AURAL | ACTION_VISUAL | ACTION_THREATENING);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You emit a low, rumbling growl at", aoObjects, " while a " +
         "chilling, almost predatory grin spreads across your face.");
  target (" emits a low, rumbling growl at you while a chilling, " +
          "almost predatory grin creeps across " + XPOS (oWho) +
          " face.", aoObjects, "", ACTION_AURAL | ACTION_VISUAL | ACTION_THREATENING);
  all2act (" emits a low growl at", aoObjects, ", while a chilling, " +
           "almost predatory grin spreads across " + XPOS (oWho) +
           " face.", "", ACTION_AURAL | ACTION_VISUAL | ACTION_THREATENING);

  return (TRUE);
}


/*
 * Function name : m_action_hand
 *
 */

int m_action_hand (string sArgs)
{
  object oWho = this_player ();
  object *aoStop;
  object *aoListen;
  string sStop;
  string sListen;
  string sFragment;
  string *asAdverb;

  notify_fail ("Whom do you wish to listen to whom ?\n");

  asAdverb = parse_adverb_with_space (sArgs, "sternly", FALSE);

  if (!strlen (asAdverb [0]))
  {
    write ("You hold up your right hand" + asAdverb [1] + " to silence those " +
           "around you.\n");
    allbb (" holds up " + XPOS (oWho) + " right hand" + asAdverb [1] +
           " and motions you to silence.", "", ACTION_VISUAL);

    return (TRUE);
  }

  if (!parse_command (asAdverb [0], ({ }),
                      "[at] [the] %s [to] 'listen' [to] %s",
                      sStop, sListen))
  {
    if (!parse_command (asAdverb [0], ({ }),
                        "[at] [the] %s",
                        sStop))
    {
      return (FALSE);
    }
    sListen = "";
  }

  aoStop = parse_this (sStop, "%l", ACTION_VISUAL);
  aoStop = FILTER_IS_SEEN (oWho, aoStop);
  aoListen = parse_this (sListen, "%l", ACTION_VISUAL);
  aoListen = FILTER_IS_SEEN (oWho, aoListen);

  switch (sizeof (aoStop))
  {
    case 0:  return (FALSE);
    case 1:  sFragment = XOBJ (aoStop [0]);
             break;
    default: sFragment = "them";
             break;
  }

  if (sizeof (aoListen))
  {
    actor (
      "You hold up your right hand" + asAdverb [1] + " towards",
      aoStop, ", motioning " + sFragment + " to be silent and " +
      "listen to " + COMPOSITE_WORDS (m_map_descriptions (oWho, aoListen)) + ".");
    target2actbb (
      " holds up " + XPOS (oWho) + " right hand" + asAdverb [1] +
      " and motions ", aoStop, " to be silent and listen",
      " to ", aoListen);
    all2actbb (
      " holds up " + XPOS (oWho) + " right hand" + asAdverb [1] +
      " and motions", aoStop, " to be silent and listen to " +
      XOBJ (oWho) + ".");
  }
  else
  {
    actor (
      "You hold up your right hand" + asAdverb [1] + " towards",
      aoStop, ", motioning " + sFragment + " to be silent and listen to you.");
    targetbb (
      " holds up " + XPOS (oWho) + " right hand" + asAdverb [1] +
      " and motions you to be silent and listen to " +
      XOBJ (oWho) + ".", aoStop);
    all2actbb (
      " holds up " + XPOS (oWho) + " right hand" + asAdverb [1] +
      " and motions", aoStop, " to be silent and listen to " +
      XOBJ (oWho) + ".");
  }

  return (TRUE);
}


/*
 * Function name : m_action_honor
 *
 */

int m_action_honor (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  string sFragment;

  notify_fail ("Whom do you wish to honor ?\n");

  if (!strlen (sArgs))
  {
    write ("You honor your ancestors with a moment of silence.\n");
    allbb (" honors " + XPOS (oWho) + " ancestors with a moment of silence.", "", ACTION_VISUAL | ACTION_INGRATIATORY);

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[the] %l", ACTION_VISUAL | ACTION_INGRATIATORY);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You honor", aoObjects, " with a silent bow.");
  targetbb (" honors you with a silent bow.", aoObjects, "", ACTION_VISUAL | ACTION_INGRATIATORY);
  all2actbb (" honors", aoObjects, " with a silent bow.", "", ACTION_VISUAL | ACTION_INGRATIATORY);

  return (TRUE);
}


/*
 * Function name : m_action_humble
 * Description   : This enables the learning in combat.
 *
 */

int m_action_humble (string sArgs)
{
  object oWho = this_player ();
  string sSkill;
  int    iSkill;

  iSkill = MAX (oWho->query_skill (M_SKILL_FORMING_CLUB),
                MAX (oWho->query_skill (M_SKILL_FORMING_BLADE),
                     oWho->query_skill (M_SKILL_FORMING_STICK)));

  // This expects M_SKILL_MAX_FORMING to be 100 ...

  switch (iSkill)
  {
    case  0 .. 19 : sSkill = "You feel totally unable to learn, however."; break;
    case 20 .. 39 : sSkill = "You feel rather unable to learn, however."; break;
    case 40 .. 59 : sSkill = "You feel somewhat prepared to learn."; break;
    case 60 .. 89 : sSkill = "You feel decently prepared to learn."; break;
    default       : sSkill = "You feel perfectly prepared to learn."; break;
  }

  write ("You humbly acknowledge the combat abilities of your enemies, certain that there is much they could teach you. " + sSkill + "\n");
  all (" humbly acknowledges the combat abilities of " + XPOS (oWho) + " enemies.", "", ACTION_VISUAL);
  M_SOULDESC ("showing humbleness");

  m_set_learning (oWho, TRUE);

  return (TRUE);
}

//-------------------------------------------------------------------

