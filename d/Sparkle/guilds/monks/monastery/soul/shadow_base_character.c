/*******************************************************************\
| SHADOW_BASE_CHARACTER.C                                           |
\*******************************************************************/

/*
 * 07/12/09 Arandir     Mercade thinks this has to be renamed from H to C
 * 07/06/14 Arandir     Added a debugging hook to catch certain runtime
 * 04/08/26 Arandir     Mild tuning of the character measurement
 *                      First version of peacefulness trait
 *                      Changes due to new emote hooks
 * 04/08/25 Arandir     Punishments added to perfection trait
 *                      Emote classification code factored out
 *                      First version of honesty trait
 * 04/08/24 Arandir     First version of respect trait
 * 04/08/23 Arandir     First version of perfection trait
 * 04/08/18 Arandir     Further tuning of effort trait
 * 04/08/15 Arandir     New detection for effort trait
 * 04/06/20 Arandir     Time based character scale down
 * 04/06/13 Arandir     Disabled the suspect exp hooks
 * 04/06/12 Arandir     Change to character scale down
 * 04/05/22 Arandir     Detection of exp for effort trait
 * 03/12/13 Arandir     Fixed initial values of persistent data
 * 03/12/03 Arandir     Added the character measurement support
 * 03/08/10 Arandir     Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

/*******************************************************************\
| Functions for managing kinship                                    |
\*******************************************************************/

private static string *asMonkKinship;

#define M_MONK_KINSHIP_VERSION          0

public int iMonkKinshipVersion = M_MONK_KINSHIP_VERSION;
public mixed xMonkKinshipExternal = ({ });


/*
 * Function name : m_export_state_monk_kinship
 * Function name : m_import_state_monk_kinship
 * Description   : Converts the state in the asMonkKinship variable.
 *
 */

void m_export_state_monk_kinship ()
{
  // Exporting the state is trivial, we simply enforce using
  // the latest version of the state information.

  iMonkKinshipVersion = M_MONK_KINSHIP_VERSION;
  xMonkKinshipExternal = asMonkKinship;
}


void m_import_state_monk_kinship ()
{
  switch (iMonkKinshipVersion)
  {
    // Version 0 is the current version, which can be simply copied.

    case 0: asMonkKinship = xMonkKinshipExternal;
            break;
  }
}


/*
 * Function name : m_add_kin
 * Description   : Adds an information about dragon kinship.
 *
 */

void m_add_kin (string sKin)
{
  if (member_array (sKin, asMonkKinship) < 0)
    asMonkKinship += ({ sKin });

  m_save_object ();
}


/*
 * Function name : m_get_kins
 * Description   : Returns information about dragon kinship.
 *
 */

string *m_get_kins ()
{
  return (asMonkKinship);
}


/*
 * Function name : m_is_kin
 * Description   : Queries information about dragon kinship.
 *
 */

int m_is_kin (string sKin)
{
  return (member_array (sKin, asMonkKinship) >= 0);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions for managing relationship                               |
\*******************************************************************/

// Changes in strength of a relationship to a character are linear when
// increased and exponential when decreased. That way, a change in
// polarity of a relationship is proportional to its strength.

#define M_RELATIONSHIP_IMPROVE          0
#define M_RELATIONSHIP_WORSEN           1

#define M_RELATIONSHIP_DECREASE_MUL     6
#define M_RELATIONSHIP_DECREASE_DIV     7


private static mapping mMonkRelationship;

#define M_MONK_RELATIONSHIP_VERSION     0

public int iMonkRelationshipVersion = M_MONK_RELATIONSHIP_VERSION;
public mixed xMonkRelationshipExternal = ([ ]);


/*
 * Function name : m_export_state_monk_relationship
 * Function name : m_import_state_monk_relationship
 * Description   : Converts the state in the mMonkRelationship variable.
 *
 */

void m_export_state_monk_relationship ()
{
  // Exporting the state is trivial, we simply enforce using
  // the latest version of the state information.

  iMonkRelationshipVersion = M_MONK_RELATIONSHIP_VERSION;
  xMonkRelationshipExternal = mMonkRelationship;
}


void m_import_state_monk_relationship ()
{
  switch (iMonkRelationshipVersion)
  {
    // Version 0 is the current version, which can be simply copied.

    case 0: mMonkRelationship = xMonkRelationshipExternal;
            break;
  }
}


/*
 * Function name : m_add_relation
 * Description   : Adds an information about player relationship.
 *
 */

void m_add_relation (mixed xWho)
{
  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;

  if (member_array (sWho, m_indices (mMonkRelationship)) < 0)
    mMonkRelationship += ([ sWho : 0 ]);

  m_save_object ();
}


/*
 * Function name : m_change_relation
 * Description   : Changes the strength of player relationship.
 * Returns       : TRUE as an indication of strengthening or
 *                 FALSE as an indication of weakening
 *
 */

int m_change_relation (mixed xWho, int iDirection)
{
  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;
  int iStrength = mMonkRelationship [sWho];
  int iResult = TRUE;

       if ((iStrength >= 0) && (iDirection == M_RELATIONSHIP_IMPROVE)) iStrength ++;
  else if ((iStrength <= 0) && (iDirection == M_RELATIONSHIP_WORSEN)) iStrength ++;
  else
  {
    iStrength = (iStrength * M_RELATIONSHIP_DECREASE_MUL) / M_RELATIONSHIP_DECREASE_DIV;
    iResult = FALSE;
  }

  if (member_array (sWho, m_indices (mMonkRelationship)) >= 0)
       mMonkRelationship [sWho] = iStrength;
  else mMonkRelationship += ([ sWho : iStrength ]);

  m_save_object ();

  return (iResult);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions for character mesaurement                               |
\*******************************************************************/


private static mixed *axMonkCharacter;

#define M_MONK_CHARACTER_VERSION        1

public int iMonkCharacterVersion = M_MONK_CHARACTER_VERSION;
public mixed xMonkCharacterExternal =
({
  ({ 0, 0, 0, 0, 0 }),
  ({ 0, 0, 0, 0, 0 }),
  0
});

#define M_MONK_CHARACTER_POSITIVE       0
#define M_MONK_CHARACTER_NEGATIVE       1
#define M_MONK_CHARACTER_AGE            2


// The calibration of the constants below is tricky. Few comments.
//
// M_CHARACTER_SCALE_AGE        Says how much the character has to age
//                              in game time before being scaled down.
//                              A larger value makes the character
//                              slower to change.
//
// M_CHARACTER_SCALE_MUL        Rational number that determines the ratio
// M_CHARACTER_SCALE_DIV        used to scale down the character with age.
//
// M_EVALUATE_PERIOD            Says how long before a sequence
//                              of observations is evaluated.


#define M_CHARACTER_SCALE_AGE           (24 * 60 * 60 / F_SECONDS_PER_BEAT)

#define M_CHARACTER_SCALE_MUL           30
#define M_CHARACTER_SCALE_DIV           31


private static int *aiMonkCharacterEvaluateAlarms =
({ ALARM_NONE, ALARM_NONE, ALARM_NONE, ALARM_NONE, ALARM_NONE });

#define M_CHARACTER_DEADLINE            (10.0 * 60.0)


// The manner in which observations cancel each other out is rather
// tricky. The values of positive and negative observations get
// added and the character is shifted by the result.

// The values must be kept small to make the character robust.

private static int *aiMonkCharacterObservationsPositive =
({ 0, 0, 0, 0, 0 });
private static int *aiMonkCharacterObservationsNegative =
({ 0, 0, 0, 0, 0 });

#define M_DIRECTION_POSITIVE                    1
#define M_DIRECTION_VERY_POSITIVE               2
#define M_DIRECTION_EXTREMELY_POSITIVE          5
#define M_DIRECTION_NEGATIVE                    -1
#define M_DIRECTION_VERY_NEGATIVE               -2
#define M_DIRECTION_EXTREMELY_NEGATIVE          -5


/*
 * Function name : m_export_state_monk_character
 * Function name : m_import_state_monk_character
 * Description   : Converts the state in the axMonkCharacter variable.
 *
 */

void m_export_state_monk_character ()
{
  // Exporting the state is trivial, we simply enforce using
  // the latest version of the state information.

  iMonkCharacterVersion = M_MONK_CHARACTER_VERSION;
  xMonkCharacterExternal = axMonkCharacter;
}


void m_import_state_monk_character ()
{
  switch (iMonkCharacterVersion)
  {
    // Version 0 has to be converted.
    // Differences between 0 and 1 are:
    //  - Added character age item

    case 0: xMonkCharacterExternal += ({ 0 });

            // Pass through to next version

    // Version 1 is the current version, which can be simply copied.

    case 1: axMonkCharacter = xMonkCharacterExternal;
            break;
  }
}


/*
 * Function name : m_get_character
 * Description   : Returns information about character.
 *
 */

mixed *m_get_character ()
{
  // This is a debugging hook to figure out why an indexing
  // on illegal type runtime is sometimes triggered by this
  // particular line ...

  if (!pointerp (axMonkCharacter))
  {
     s_log (M_LOG_DEBUG, "Getting character with invalid state.", axMonkCharacter, TRUE);
     return 0;
  }

  return (({ axMonkCharacter [M_MONK_CHARACTER_POSITIVE],
             axMonkCharacter [M_MONK_CHARACTER_NEGATIVE] }));
}


/*
 * Function name : m_character_evaluate
 * Description   : Updates character based on observations
 *
 */

void m_character_evaluate (int iCharacter)
{
  int iObservation;

  // Note that the alarm got called.

  aiMonkCharacterEvaluateAlarms [iCharacter] = ALARM_NONE;

  // Update the character based on the observation.

  iObservation = aiMonkCharacterObservationsPositive [iCharacter] +
                 aiMonkCharacterObservationsNegative [iCharacter];

  aiMonkCharacterObservationsPositive [iCharacter] = 0;
  aiMonkCharacterObservationsNegative [iCharacter] = 0;

  if (iObservation)
  {
    if (iObservation > 0) axMonkCharacter [M_MONK_CHARACTER_POSITIVE][iCharacter] += iObservation;
    if (iObservation < 0) axMonkCharacter [M_MONK_CHARACTER_NEGATIVE][iCharacter] -= iObservation;

    m_save_object ();
  }
}


/*
 * Function name : m_character_observation
 * Description   : Keeps track of character observations
 *
 */

void m_character_observation (int iCharacter, int iDirection)
{
  // Only the most positive and the most negative observation is kept.

  if (iDirection > aiMonkCharacterObservationsPositive [iCharacter])
    aiMonkCharacterObservationsPositive [iCharacter] = iDirection;
  if (iDirection < aiMonkCharacterObservationsNegative [iCharacter])
    aiMonkCharacterObservationsNegative [iCharacter] = iDirection;

  // Observations are tracked across a fixed time interval.

  if (aiMonkCharacterEvaluateAlarms [iCharacter] == ALARM_NONE)
    aiMonkCharacterEvaluateAlarms [iCharacter] =
      set_alarm (M_CHARACTER_DEADLINE, 0.0, &m_character_evaluate (iCharacter));
}


/*
 * Function name : m_hook_character_remove_object
 * Description   : Flushes the character observations
 *
 */

void m_hook_character_remove_object ()
{
  int iCharacter;

  for (iCharacter = 0 ;
       iCharacter < sizeof (aiMonkCharacterEvaluateAlarms) ;
       iCharacter ++)
  {
    if (aiMonkCharacterEvaluateAlarms [iCharacter] != ALARM_NONE)
    {
      m_character_evaluate (iCharacter);
    }
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Overall Character Monitoring                                      |
\*******************************************************************/


void m_effort_heartbeat ();
void m_honesty_heartbeat ();
void m_perfection_heartbeat ();

void m_hook_honesty_attacking_player (object oHim);
void m_hook_perfection_attacked_by_player ();
void m_hook_peacefulness_attacking_player ();

void m_hook_effort_emote_us_on_player ();
void m_hook_honesty_emote_us_on_player (int iClassification, object *aoTargets);
void m_hook_respect_emote_us_on_player (int iClassification);
void m_hook_perfection_emote_player_on_us (int iClassification);


// How often the heartbeat is evaluated.

#define M_CHARACTER_HEARTBEAT_INT          (5 * 60)
#define M_CHARACTER_HEARTBEAT_FLOAT        (5.0 * 60.0)


/*
 * Function name : m_character_heartbeat
 * Description   : Periodic evaluation of the character.
 *
 */

void m_character_heartbeat ()
{
  // Do nothing when linkdead.

  if (!interactive (shadow_who)) return;

  // The individual traits are handled in separate
  // functions for improved code readability.

  m_effort_heartbeat ();
  m_honesty_heartbeat ();
  m_perfection_heartbeat ();
}


/*
 * Function name : m_hook_character_emote_seen
 * Description   : Reacts to seen emotes.
 *
 */

void m_hook_character_emote_seen (
  string sEmote,
  string sAdverb,
  object oActor,
  object *aoTargets,
  int iAttributes)
{
  object *aoRealTargets;
  int iClassification;

  // Ignore emotes where the actor is not a player.

  if (!interactive (oActor)) return;

  // Ignore emotes where we are neither the target nor the
  // only possible target for an emote without any target.

  if (sizeof (aoTargets))
  {
    if (member_array (shadow_who, aoTargets) < 0) return;
  }
  else
  {
    aoRealTargets = FILTER_LIVE (all_inventory (environment (oActor))) - ({ oActor });
    if ((sizeof (aoRealTargets) != 1) || (aoRealTargets [0] != shadow_who)) return;
  }

  // This took a bit of debugging :-). Adjust the emote and adverb to
  // be on the safe side of string manipulation and classify the emote
  // and adverb pair. Ignore emote and adverb pairs that could not be
  // classified.

  if (!stringp (sEmote)) sEmote = "";
  if (!stringp (sAdverb)) sAdverb = "";
  sEmote = dg_remove_whitespace (sEmote);
  sAdverb = dg_remove_whitespace (sAdverb);

  iClassification = m_classify_emote (oActor, sEmote, sAdverb, iAttributes);
  if (!iClassification) return;

  // Now react to the emotes.

  m_hook_perfection_emote_player_on_us (iClassification);
}


/*
 * Function name : m_hook_character_emote_done
 * Description   : Reacts to done emotes.
 *
 */

void m_hook_character_emote_done (
  string sEmote,
  object *aoTargets)
{
  object *aoRealTargets;
  int iClassification;

  // Ignore emotes where no player is either the target or
  // the only possible target for an emote without any target.

  if (sizeof (aoTargets))
  {
    aoRealTargets = FILTER_PLAYERS (aoTargets);
    if (!sizeof (aoRealTargets)) return;
  }
  else
  {
    aoRealTargets = FILTER_LIVE (all_inventory (environment (shadow_who))) - ({ shadow_who });
    if ((sizeof (aoRealTargets) != 1) || (!interactive (aoRealTargets [0]))) return;
  }

  // This took a bit of debugging :-). Adjust the emote and adverb to
  // be on the safe side of string manipulation and classify the emote
  // and adverb pair. Ignore emote and adverb pairs that could not be
  // classified.

  if (!stringp (sEmote)) sEmote = "";
  sEmote = dg_remove_whitespace (sEmote);

  iClassification = m_classify_emote (shadow_who, sEmote, "", 0);
  if (!iClassification) return;

  // Now react to the emotes.

  m_hook_effort_emote_us_on_player ();
  m_hook_respect_emote_us_on_player (iClassification);
  m_hook_honesty_emote_us_on_player (iClassification, aoTargets);
}


/*
 * Function name : m_hook_character_attacking
 * Function name : m_hook_character_attacked
 * Description   : Reacts to attacks.
 *
 */

void m_hook_character_attacking (object oHim)
{
  // We are only interested in attacking other players.

  if (interactive (oHim))
  {
    m_hook_honesty_attacking_player (oHim);
    m_hook_peacefulness_attacking_player ();
  }
}

void m_hook_character_attacked (object oHim)
{
  // We are only interested in being attacked by other players.

  if (interactive (oHim))
  {
    m_hook_perfection_attacked_by_player ();
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Perfection Trait                                                  |
\*******************************************************************/

/*
 * Function name : m_perfection_heartbeat
 * Description   : Periodic evaluation of the perfection trait.
 *
 */

void m_perfection_heartbeat ()
{
  // Staying punished is an offense every heartbeat.

  if (m_is_punished (shadow_who))
  {
    m_character_observation (M_TRAIT_PERFECTION, M_DIRECTION_EXTREMELY_NEGATIVE);
  }
}


/*
 * Function name : m_hook_perfection_emote_player_on_us
 * Description   : Reaction to player doing emote on us wrt the perfection trait.
 *
 */

void m_hook_perfection_emote_player_on_us (int iClassification)
{
  int iDirection = 0;

  if (iClassification & (M_EMOTE_FONDNESS | M_EMOTE_ADMIRATION | M_EMOTE_FRIENDSHIP | M_EMOTE_POLITENESS))
  {
         if (iClassification & M_EMOTE_MILD)    iDirection = M_DIRECTION_POSITIVE;
    else if (iClassification & M_EMOTE_EXTREME) iDirection = M_DIRECTION_EXTREMELY_POSITIVE;
    else                                        iDirection = M_DIRECTION_VERY_POSITIVE;
  }

  if (iClassification & M_EMOTE_HOSTILITY)
  {
         if (iClassification & M_EMOTE_MILD)    iDirection = M_DIRECTION_NEGATIVE;
    else if (iClassification & M_EMOTE_EXTREME) iDirection = M_DIRECTION_EXTREMELY_NEGATIVE;
    else                                        iDirection = M_DIRECTION_VERY_NEGATIVE;
  }

  if (iDirection) m_character_observation (M_TRAIT_PERFECTION, iDirection);
}


/*
 * Function name : m_hook_perfection_attacked_by_player
 * Description   : Reaction to being attacked by a player wrt the perfection trait.
 *
 */

void m_hook_perfection_attacked_by_player ()
{
  m_character_observation (M_TRAIT_PERFECTION, M_DIRECTION_EXTREMELY_NEGATIVE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Honesty Trait                                                     |
\*******************************************************************/


/*
 * Function name : m_honesty_heartbeat
 * Description   : Periodic evaluation of the honesty trait.
 *
 */

void m_honesty_heartbeat ()
{
  object *aoTeam;
  object oEnemy;
  int iMember;
  int iImpact;

  // Being in team is an expression of relationship every heartbeat.

  aoTeam = shadow_who->query_team_others ();
  for (iMember = 0 ; iMember < sizeof (aoTeam) ; iMember ++)
  {
    iImpact = m_change_relation (aoTeam [iMember], M_RELATIONSHIP_IMPROVE);
    if (iImpact) m_character_observation (M_TRAIT_HONESTY, M_DIRECTION_POSITIVE);
            else m_character_observation (M_TRAIT_HONESTY, M_DIRECTION_NEGATIVE);
  }
}


/*
 * Function name : m_hook_honesty_emote_us_on_player
 * Description   : Reaction to us doing emote on player wrt the honesty trait.
 *
 */

void m_hook_honesty_emote_us_on_player (int iClassification, object *aoTargets)
{
  int iTarget;
  int iDirection;
  int iRelationshipChange;
  int iRelationshipImpact;

  if (iClassification & (M_EMOTE_FONDNESS | M_EMOTE_ADMIRATION | M_EMOTE_FRIENDSHIP | M_EMOTE_POLITENESS))
  {
    iRelationshipChange = M_RELATIONSHIP_IMPROVE;
  }
  else if (iClassification & (M_EMOTE_HOSTILITY | M_EMOTE_DEBASEMENT))
  {
    iRelationshipChange = M_RELATIONSHIP_WORSEN;
  }
  else return;

  for (iTarget = 0 ; iTarget < sizeof (aoTargets) ; iTarget ++)
  {
    iRelationshipImpact = m_change_relation (aoTargets [iTarget], iRelationshipChange);
    if (iRelationshipImpact)
    {
           if (iClassification & M_EMOTE_MILD)    iDirection = M_DIRECTION_POSITIVE;
      else if (iClassification & M_EMOTE_EXTREME) iDirection = M_DIRECTION_EXTREMELY_POSITIVE;
      else                                        iDirection = M_DIRECTION_VERY_POSITIVE;
    }
    else
    {
           if (iClassification & M_EMOTE_MILD)    iDirection = M_DIRECTION_NEGATIVE;
      else if (iClassification & M_EMOTE_EXTREME) iDirection = M_DIRECTION_EXTREMELY_NEGATIVE;
      else                                        iDirection = M_DIRECTION_VERY_NEGATIVE;
    }
    m_character_observation (M_TRAIT_HONESTY, iDirection);
  }
}


/*
 * Function name : m_hook_honesty_attacking_player
 * Description   : Reaction to attacking a player wrt the honesty trait.
 *
 */

void m_hook_honesty_attacking_player (object oHim)
{
  int iImpact = m_change_relation (oHim, M_RELATIONSHIP_WORSEN);
  if (iImpact) m_character_observation (M_TRAIT_HONESTY, M_DIRECTION_EXTREMELY_POSITIVE);
          else m_character_observation (M_TRAIT_HONESTY, M_DIRECTION_EXTREMELY_NEGATIVE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Effort Trait                                                      |
\*******************************************************************/

// An increase in total exp is judged by its relative size,
// which approximates the behavior of the stats command.
// If we deem making slight progress in 60 minutes excellent,
// the corresponding relative increase in total exp is
// M_CHARACTER_HEARTBEAT_INT /
// M_EFFORT_STATS_SCALE *
// M_EFFORT_STATS_LEVELS * 60.

// Remember that total exp for this calculation is capped at
// SD_IMPROVE_MAX * M_EFFORT_STATS_SCALE in the same manner
// as inside the stats command. The M_EFFORT_STATS_SCALE and
// M_EFFORT_STATS_LEVELS constants reflect what is hardcoded
// inside the stats command.

#define M_EFFORT_STATS_SCALE            15
#define M_EFFORT_STATS_LEVELS           10

#define M_EFFORT_EXP(t) \
  (M_EFFORT_STATS_SCALE * M_EFFORT_STATS_LEVELS * ((t) / M_CHARACTER_HEARTBEAT_INT))

#define M_EFFORT_EXP_EXCELLENT          M_EFFORT_EXP (60*60)
#define M_EFFORT_EXP_DECENT             M_EFFORT_EXP (120*60)
#define M_EFFORT_EXP_POOR               M_EFFORT_EXP (300*60)

// How long before idleness is penalized.

#define M_EFFORT_IDLE                   (5 * 60)


private static int iMonkEffortQuestExp = 0;
private static int iMonkEffortCombatExp = 0;
private static int iMonkEffortGeneralExp = 0;


/*
 * Function name : m_effort_heartbeat
 * Description   : Periodic evaluation of the effort trait.
 *
 */

void m_effort_heartbeat ()
{
  int iQuestExpDelta;
  int iCombatExpDelta;
  int iGeneralExpDelta;
  int iExpDelta;
  int iExpTotal;

  // Get the increase in exp for all exp types.

  iQuestExpDelta = shadow_who->query_exp_quest () - iMonkEffortQuestExp;
  iCombatExpDelta = shadow_who->query_exp_combat () - iMonkEffortCombatExp;
  iGeneralExpDelta = shadow_who->query_exp_general () - iMonkEffortGeneralExp;

  // The first evaluation does not have the previous values.

  if (iMonkEffortQuestExp + iMonkEffortCombatExp + iMonkEffortGeneralExp)
  {
    // Any increase in quest exp is an extreme change.

    if (iQuestExpDelta > 0)
    {
      m_character_observation (M_TRAIT_EFFORT, M_DIRECTION_EXTREMELY_POSITIVE);
    }
    else
    {
      // An increase in total exp is judged by its relative size,
      // which approximates the behavior of the stats command.
      // Idling is considered as a factor too.

      iExpDelta = iCombatExpDelta + iGeneralExpDelta;
      iExpTotal = shadow_who->query_exp ();

      // Total exp for this calculation is capped in the same manner
      // as inside the stats command, for whatever good it does.

      if (iExpTotal > SD_IMPROVE_MAX * M_EFFORT_STATS_SCALE)
        iExpTotal = SD_IMPROVE_MAX * M_EFFORT_STATS_SCALE;

      if (iExpDelta > iExpTotal / M_EFFORT_EXP_EXCELLENT)
        m_character_observation (M_TRAIT_EFFORT, M_DIRECTION_EXTREMELY_POSITIVE);
      else if (iExpDelta > iExpTotal / M_EFFORT_EXP_DECENT)
        m_character_observation (M_TRAIT_EFFORT, M_DIRECTION_VERY_POSITIVE);
      else if (iExpDelta > iExpTotal / M_EFFORT_EXP_POOR)
        m_character_observation (M_TRAIT_EFFORT, M_DIRECTION_POSITIVE);
      else if (query_idle (shadow_who) < M_EFFORT_IDLE)
        m_character_observation (M_TRAIT_EFFORT, M_DIRECTION_NEGATIVE);
      else
        m_character_observation (M_TRAIT_EFFORT, M_DIRECTION_VERY_NEGATIVE);
    }
  }

  // Update the previous values.

  iMonkEffortQuestExp += iQuestExpDelta;
  iMonkEffortCombatExp += iCombatExpDelta;
  iMonkEffortGeneralExp += iGeneralExpDelta;
}


/*
 * Function name : m_hook_effort_emote_us_on_player
 * Description   : Reaction to us doing emote on player wrt the effort trait.
 *
 */

void m_hook_effort_emote_us_on_player ()
{
  m_character_observation (M_TRAIT_EFFORT, M_DIRECTION_POSITIVE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Respect Trait                                                     |
\*******************************************************************/

/*
 * Function name : m_hook_respect_emote_us_on_player
 * Description   : Reaction to us doing emote on player wrt the respect trait.
 *
 */

void m_hook_respect_emote_us_on_player (int iClassification)
{
  int iDirection = 0;

  if (iClassification & (M_EMOTE_ADMIRATION | M_EMOTE_FRIENDSHIP | M_EMOTE_POLITENESS))
  {
         if (iClassification & M_EMOTE_MILD)    iDirection = M_DIRECTION_POSITIVE;
    else if (iClassification & M_EMOTE_EXTREME) iDirection = M_DIRECTION_EXTREMELY_POSITIVE;
    else                                        iDirection = M_DIRECTION_VERY_POSITIVE;
  }

  if (iClassification & (M_EMOTE_HOSTILITY | M_EMOTE_DEBASEMENT))
  {
         if (iClassification & M_EMOTE_MILD)    iDirection = M_DIRECTION_NEGATIVE;
    else if (iClassification & M_EMOTE_EXTREME) iDirection = M_DIRECTION_EXTREMELY_NEGATIVE;
    else                                        iDirection = M_DIRECTION_VERY_NEGATIVE;
  }

  if (iDirection) m_character_observation (M_TRAIT_RESPECT, iDirection);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Peacefulness Trait                                                |
\*******************************************************************/


/*
 * Function name : m_hook_peacefulness_attacking_player
 * Description   : Reaction to attacking a player wrt the peacefulness trait.
 *
 */

void m_hook_peacefulness_attacking_player ()
{
  m_character_observation (M_TRAIT_PEACEFULNESS, M_DIRECTION_EXTREMELY_NEGATIVE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Initialization                                                    |
\*******************************************************************/

void m_shadow_character_init ()
{
  int iCharacter;
  int iDelta;

  // The character is scaled down with age in game time. The
  // scaling down is done once per login which makes players
  // who login for shorter durations scale down mildly faster
  // but that should not influence the grand scheme of things.

  iDelta = shadow_who->query_age () - axMonkCharacter [M_MONK_CHARACTER_AGE];

  if (iDelta > M_CHARACTER_SCALE_AGE)
  {
    for (iCharacter = 0 ;
         iCharacter < sizeof (aiMonkCharacterEvaluateAlarms) ;
         iCharacter ++)
    {
      axMonkCharacter [M_MONK_CHARACTER_POSITIVE][iCharacter] =
        (axMonkCharacter [M_MONK_CHARACTER_POSITIVE][iCharacter] *
          M_CHARACTER_SCALE_MUL) /
          M_CHARACTER_SCALE_DIV;

      axMonkCharacter [M_MONK_CHARACTER_NEGATIVE][iCharacter] =
        (axMonkCharacter [M_MONK_CHARACTER_NEGATIVE][iCharacter] *
          M_CHARACTER_SCALE_MUL) /
          M_CHARACTER_SCALE_DIV;
    }

    // If we lag more than 10 scale downs behind age in game time,
    // the scale downs are dropped. This helps the initialization
    // and the players who login for longer durations.

    axMonkCharacter [M_MONK_CHARACTER_AGE] +=
      (iDelta > M_CHARACTER_SCALE_AGE * 10) ? iDelta : M_CHARACTER_SCALE_AGE;

    m_save_object ();
  }

  // Some parts of the character are evaluated periodically.

  set_alarm (0.0, M_CHARACTER_HEARTBEAT_FLOAT, &m_character_heartbeat ());
}

//-------------------------------------------------------------------

