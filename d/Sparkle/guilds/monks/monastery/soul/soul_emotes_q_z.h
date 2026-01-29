/*******************************************************************\
| SOUL_EMOTES_Q_Z.H                                                 |
\*******************************************************************/

/*
 * 06/09/20 Arandir     Fixed use of Q macros instead of X macros
 * 06/09/02 Arandir     Fixed use of XOBJ style macros
 * 04/08/17 Arandir     Added action attributes to other emote calls
 * 04/08/15 Arandir     Added action attributes to parse_this
 * 03/09/20 Arandir     Added the mrespect emote
 * 03/09/14 Arandir     Added the mregret, mstep, mscout and mwipe emotes
 * 03/09/14 Arandir     Removed the thys and thous in error messages
 * 03/09/10 Arandir     Added support for recalling telioys
 * 03/09/07 Arandir     Fixed typos due to all2act not expanding VBFC
 * 02/07/02 Arandir     Polished up and bugfixed
 * 02/05/03 Arandir	Ported to new area without rewrite
 * 99/02/01 Lilith	Emotes updated and added
 * 96/04/16 Cirion	Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

/*
 * Function name : m_action_recall
 *
 */

int m_action_recall (string sArgs)
{
  object oWho = this_player ();
  mixed  *axTelioys;
  int    iTelioy;

  write ("You pause momentarily, trying to recall your past " +
         "conversation.\n");

  axTelioys = oWho->m_recall_telioys ();
  if (sizeof (axTelioys))
  {
    for (iTelioy = 0 ; iTelioy < sizeof (axTelioys) ; iTelioy ++)
    {
      write ("You " +
             one_of_list (({ "clearly", "hesitantly", "vaguely", "vividly" })) +
             " recall a vision of " +
             axTelioys [iTelioy][0] +
             " appearing before you and whispering: " +
             axTelioys [iTelioy][1] + "\n");
    }
  }
  else
  {
    write ("Try as you might, nothing comes to your mind.\n");
  }

  allbb (" pauses momentarily, as if trying to recall something.", "", ACTION_VISUAL);
  M_SOULDESC ("trying to recall something");

  return (TRUE);
}


/*
 * Function name : m_action_refuse
 *
 */

int m_action_refuse (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  string *asAdverb;

  notify_fail ("How and whose dispute are you refusing ?\n");

  asAdverb = parse_adverb_with_space (sArgs, "adamantly", FALSE);

  if (!strlen (asAdverb [0]))
  {
    write ("You" + asAdverb [1] + " refuse to become embroiled in the dispute.\n");
    all (asAdverb [1] + " refuses to become embroiled in the dispute.", "", ACTION_AURAL | ACTION_VISUAL);
    M_SOULDESC ("refusing" + asAdverb [1]);

    return (TRUE);
  }

  aoObjects = parse_this (asAdverb [0], "[the] %i", ACTION_AURAL | ACTION_VISUAL);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You" + asAdverb [1] + " refuse to become embroiled in",
         aoObjects, "'s dispute.");
  target (asAdverb [1] + " refuses to become embroiled in your dispute.",
          aoObjects, "", ACTION_AURAL | ACTION_VISUAL);
  all2act (" refuses quite" + asAdverb [1] + " to become embroiled in",
           aoObjects, "'s dispute.", "", ACTION_AURAL | ACTION_VISUAL);
  M_SOULDESC ("refusing" + asAdverb [1]);

  return (TRUE);
}


/*
 * Function name : m_action_regret
 *
 */

int m_action_regret (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;

  notify_fail ("To whom do you wish to express regret ?\n");

  if (!strlen (sArgs))
  {
    write ("You give an expression of extreme regret.\n");
    allbb (" gives an expression of extreme regret.", "", ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);
    M_SOULDESC ("regretful");

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[the] %l", ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You give an expression of extreme regret to", aoObjects);
  targetbb (" gives you " + XPOS (oWho) + " expression of extreme regret.", aoObjects, "", ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);
  all2actbb (" turns to ", aoObjects, " with an expression of extreme regret.", "", ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);
  M_SOULDESC ("regretful");

  return (TRUE);
}


/*
 * Function name : m_action_relax
 *
 */

int m_action_relax (string sArgs)
{
  write ("You consciously relax every muscle in your body in an attempt to achieve inner peace.\n");
  allbb (" appears completely relaxed. Suddenly, you notice how still and peaceful everything has become.", "", ACTION_VISUAL);
  M_SOULDESC ("looking relaxed and peaceful");

  return (TRUE);
}


/*
 * Function name : m_action_roar
 *
 */

int m_action_roar (string sArgs)
{
  object oWho = this_player ();
  object oRoom = environment (oWho);

  if (oRoom->query_prop (ROOM_I_INSIDE))
  {
    write ("You throw your head back and roar with fury.\n");
    all (" throws " + XPOS (oWho) + " head back and roars so loudly your ears ring.", "", ACTION_AURAL | ACTION_VISUAL | ACTION_THREATENING);

    return (TRUE);
  }

  write ("You roar forth your fury to the skies.\n" +
         "Thunder rumbles in the distance.\n");
  all (" roars forth " + XPOS (oWho) + " fury to the skies.\n" +
       "Thunder rumbles in the distance.", "", ACTION_AURAL | ACTION_VISUAL | ACTION_THREATENING);
  M_SOULDESC ("roaring furiously");

  return (TRUE);
}


/*
 * Function name : m_action_respect
 *
 */

int m_action_respect (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;

  notify_fail ("To whom do you wish to show respect ?\n");

  if (!strlen (sArgs)) return (FALSE);

  aoObjects = parse_this (sArgs, "[the] %l", ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You show respect to", aoObjects);
  targetbb (" shows you " + XPOS (oWho) + " respect.", aoObjects, "", ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);
  all2actbb (" shows ", aoObjects, " " + XPOS (oWho) + " respect.", "", ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);
  M_SOULDESC ("respectful");

  return (TRUE);
}


/*
 * Function name : m_action_scout
 *
 */

int m_action_scout (string sArgs)
{
  write ("Remembering the plight of your forefathers, you " +
         "carefully scan your surroundings for potential " +
         "misgivings.\n");
  allbb (" scans the surrounding area very carefully.", "",
         ACTION_VISUAL);
  M_SOULDESC ("looking around carefully");

  return (TRUE);
}


/*
 * Function name : m_action_shun
 *
 */

int m_action_shun (string sArgs)
{
  object oWho = this_player ();
  string sWho = dg_get_name (oWho);
  object *aoObjects;
  string sFragment;

  notify_fail ("Whom or what do you shun ?\n");

  if ((sArgs == sWho) ||
      (sArgs == "myself") ||
      (sArgs == "me") ||
      !strlen (sArgs))
  {
    write ("You shun yourself in a fit of existential angst.\n");
    allbb (" appears to regard " + XOBJ (oWho) + "self with disdain.", "", ACTION_AURAL | ACTION_VISUAL);
    M_SOULDESC ("looking disdainful");

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[the] %i", ACTION_AURAL | ACTION_VISUAL);

  switch (sizeof (aoObjects))
  {
    case 0:  return (FALSE);
    case 1:  sFragment = XPNOUN (aoObjects [0]) + " represents";
             break;
    default: sFragment = "they represent";
             break;
  }

  actor ("You shun", aoObjects," and all " + sFragment + ".");
  targetbb (" regards you, and all that you represent, with " +
            "an expression of utter revulsion.", aoObjects, "",
            ACTION_AURAL | ACTION_VISUAL);
  all2actbb (" appears to regard", aoObjects, " and all that " +
             sFragment + " with utter revulsion.", "",
             ACTION_AURAL | ACTION_VISUAL);
  M_SOULDESC ("looking disdainful");

  return (TRUE);
}


/*
 * Function name : m_action_sketch
 *
 */

int m_action_sketch (string sArgs)
{
  object oWho = this_player ();
  string sWho = dg_get_name (oWho);
  object *aoObjects;
  string sFragmentTooth = "the likeness of a dragon tooth in the air";

  notify_fail ("Whom or what do you wish to sketch before ?\n");

  if (!strlen (sArgs))
  {
    write ("You extend your arm and with your forefinger, sketch " +
            sFragmentTooth + ".\n");
    allbb (" extends " + XPOS (oWho) + " arm and sketches " +
           sFragmentTooth + " with " + XPOS (oWho) + " forefinger.", "",
           ACTION_VISUAL | ACTION_INGRATIATORY);

    return (TRUE);
  }

  if ((sArgs == sWho) ||
      (sArgs == "myself") ||
      (sArgs == "me") ||
      !strlen (sArgs))
  {
    write ("You sketch " + sFragmentTooth + " before you.\n");
    allbb (" extends " + XPOS (oWho) + " arm and sketches " +
           sFragmentTooth + " with " + XPOS (oWho) + " forefinger.", "",
           ACTION_VISUAL | ACTION_INGRATIATORY);

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[before] / [near] [the] %i", ACTION_VISUAL | ACTION_INGRATIATORY);

  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You extend your arm and with your forefinger, sketch " +
         sFragmentTooth + " before", aoObjects, ".");
  targetbb (" extends " + XPOS (oWho) + " arm and sketches " +
            sFragmentTooth + " before you with " + XPOS (oWho) +
            " forefinger.", aoObjects, "",
            ACTION_VISUAL | ACTION_INGRATIATORY);
  all2actbb (" extends " + XPOS (oWho) + " arm and sketches " +
             sFragmentTooth + " before", aoObjects, " with " +
             XPOS (oWho) + " forefinger.", "",
             ACTION_VISUAL | ACTION_INGRATIATORY);

  return (TRUE);
}


/*
 * Function name : m_action_slice
 *
 */

int m_action_slice (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  string *asAdverb;

  notify_fail ("How and at whom are you gesturing ?\n");

  asAdverb = parse_adverb_with_space (sArgs, "repeatedly", FALSE);

  if (!strlen (asAdverb [0]))
  {
    write ("You emphasize what you are saying by slicing the " +
           "air" + asAdverb [1] + " with your hand.\n");
    allbb (" emphasizes what " + XPNOUN (oWho) + " is saying by slicing " +
           "the air" + asAdverb [1] + " with " + XPOS (oWho) + " hand.", "",
           ACTION_VISUAL);

    return (TRUE);
  }

  aoObjects = parse_this (asAdverb [0], "[at] [the] %l", ACTION_VISUAL);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You emphasize what you are saying to", aoObjects, " by " +
         "slicing the air" + asAdverb [1] + " with your hand.");
  targetbb (" emphasizes what " + XPNOUN (oWho) + " is saying to you by " +
            "slicing the air" + asAdverb [1] + " with " + XPOS (oWho) +
            " hand.", aoObjects, "", ACTION_VISUAL);
  all2actbb (" emphasizes what " + XPNOUN (oWho) + " is saying to", aoObjects,
             " by slicing the air" + asAdverb [1] + " with " + XPOS (oWho) +
             " hand.", "", ACTION_VISUAL);

  return (TRUE);
}


/*
 * Function name : m_action_step
 *
 */

int m_action_step (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  string *asAdverb;

  notify_fail ("How and from whom or what do you wish to step back ?\n");

  asAdverb = parse_adverb_with_space (sArgs, "lightly", FALSE);

  if (!strlen (asAdverb [0]))
  {
    write ("You" + asAdverb [1] + " step backwards in a subtle gesture of peace.\n");
    allbb (asAdverb [1] + " steps backward in a subtle gesture of peace.", "", ACTION_VISUAL | ACTION_INGRATIATORY);

    return (TRUE);
  }

  aoObjects = parse_this (asAdverb [0], "[from] [the] %l", ACTION_VISUAL | ACTION_INGRATIATORY);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You" + asAdverb [1] + " step backwards from", aoObjects,
         " in a subtle gesture of peace.");
  targetbb (asAdverb [1] + " steps backwards from you to make you " +
            "feel more at ease.", aoObjects, "", ACTION_VISUAL | ACTION_INGRATIATORY);
  all2actbb (asAdverb [1] + " steps backwards from", aoObjects, " to make " +
             DG_AMOUNT_SWITCH (sizeof (aoObjects), XOBJ (aoObjects [0]), "them") +
             " feel more at ease.", "", ACTION_VISUAL | ACTION_INGRATIATORY);

  return (TRUE);
}


/*
 * Function name : m_action_victory
 *
 */

int m_action_victory (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;

  notify_fail ("Over whom or what do you wish to cry victory ?\n");

  if (!strlen (sArgs))
  {
    write ("A magnificent cry of victory erupts from your throat " +
           "and wings away into the heavens.\n");
    say ("A magnificent cry of victory erupts from " + QTNAME (oWho) +
         "'s throat and wings away into the heavens.\n");

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[over] [the] %i", ACTION_AURAL | ACTION_VISUAL);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You declare your triumph over", aoObjects, " with a " +
         "magnificent cry of victory that erupts from your " +
         "throat and wings away into the heavens.");
  targetbb (" declares " + XPOS (oWho) + " triumph over you with a " +
            "magnificent cry of victory that erupts from " + XPOS (oWho) +
            " throat and wings away into the heavens.", aoObjects, "",
            ACTION_AURAL | ACTION_VISUAL);
  all2actbb (" declares " + XPOS (oWho) + " triumph over", aoObjects,
             " with a magnificent cry of victory that erupts from " +
             XPOS (oWho) + " throat and wings away into the heavens.", "",
             ACTION_AURAL | ACTION_VISUAL);

  return (TRUE);
}


/*
 * Function name : m_action_warn
 *
 */

int m_action_warn (string sArgs)
{
  object oWho = this_player ();
  string sWho = dg_get_name (oWho);
  object *aoObjects;
  object oObject;
  int    iObject;
  string sFragment;

  notify_fail ("Whom do you wish to warn ?\n");

  if (!strlen (sArgs)) return (FALSE);

  aoObjects = parse_this (sArgs, "[the] %l", ACTION_AURAL | ACTION_VISUAL | ACTION_THREATENING);
  aoObjects -= ({ oWho });
  if (!sizeof (aoObjects)) return (FALSE);

  for (iObject = 0 ; iObject < sizeof (aoObjects) ; iObject ++)
  {
    oObject = aoObjects [iObject];
    if (interactive (oObject))
    {
      oWho->m_add_warning (oObject);
    }
  }

  sFragment = "with cold intensity: I am " + capitalize (sWho) + ", " +
              m_get_title (oWho) + ", and as is my Way, I offer you " +
              "this warning. Depart, or I shall attack !";

  actor ("You focus a stern gaze upon", aoObjects, " and declare " + sFragment);
  target (" focuses a stern gaze upon you and declares " + sFragment, aoObjects, "", ACTION_AURAL | ACTION_VISUAL | ACTION_THREATENING);
  all2act (" focuses a stern gaze upon", aoObjects," and declares " + sFragment, "", ACTION_AURAL | ACTION_VISUAL | ACTION_THREATENING);

  return (TRUE);
}


/*
 * Function name : m_action_wing
 *
 */

int m_action_wing (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;

  notify_fail ("Whom do you wish to take under your wing ?\n");

  if (!strlen (sArgs)) return (FALSE);

  aoObjects = parse_this (sArgs, "[the] %l", ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You take", aoObjects, " under your wing, promising " +
         "lessons in wisdom, honor, and lore.");
  target (" takes you under " + XPOS (oWho) + " wing, " +
          "promising lessons in wisdom, honor, and lore.", aoObjects, "",
          ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);
  all2act (" takes", aoObjects," under " + XPOS (oWho) + " wing, " +
           "promising lessons in wisdom, honor, and lore.", "",
           ACTION_AURAL | ACTION_VISUAL | ACTION_INGRATIATORY);

  return (TRUE);
}


/*
 * Function name : m_action_wipe
 *
 */

int m_action_wipe (string sArgs)
{
  object oWho = this_player ();

  write ("You wipe the sweat from your brow.\n");
  allbb (" wipes the sweat from " + XPOS (oWho) + " brow.", "", ACTION_VISUAL);

  return (TRUE);
}

//-------------------------------------------------------------------

