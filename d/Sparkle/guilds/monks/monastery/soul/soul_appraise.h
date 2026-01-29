/*******************************************************************\
| SOUL_APPRAISE.H                                                   |
\*******************************************************************/

/*
 * 06/09/02 Arandir     Fixed use of XOBJ style macros
 * 03/07/08 Arandir     Polished up a bit
 * 02/05/03 Arandir	Ported to new area without rewrite
 * 98/05/10 Cirion	Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

/*
 * Monk ability to appraise different armour coverings.
 *
 * This ability allows the monk to appraise the protection
 * of an enemy, and is meant to be used in conjunction with
 * their ability to strike at a certain hitloc. If the monk
 * is able to discern which body parts are the least protected,
 * then they will better be able to judge where to strike. The
 * command works differently when used on humanoids or
 * non-humanoids:
 *
 * humanoids: this command will go over all the armours the
 *     target is wearing and evaluate their strengths (the
 *     ac of the armours), and give a textual description
 *     of the the strength.
 *
 * non-humanoids: the command will go over all the available
 *     hitlocs on the target and evaluate their strengths
 *     (the ac of the hitloc itself).
 *
 * Appraisals are done in a way similiar to the appraise_object
 * function in /std/object.c. When appraising an armour, the
 * player's SS_APPR_OBJ skills is used to determine success.
 * When appraising an ememy's hitloc, SS_APPR_MON skill is used.
 * Appraisals will be pseudo-random based on these skills, but
 * will always remain constant for an instance of a given
 * object, using the object's OB_NUM as the seed. Thus, a
 * player will not be able to appraise multiple times and
 * take the average of the appraisals to get the exact value.
 *
 */

//-------------------------------------------------------------------

/*
 * Function name : m_appraise_armour_strength
 * Description   : Appraise the strength of a piece of armour.
 *   oArmour       : The armour to appraise.
 *   oForWhom      : For whom the appraise is done.
 * Returns       : The strength description.
 *
 */

string m_appraise_armour_strength (object oArmour, object oForWhom)
{
  int    iArmourClass;
  int    iSkillFactor;
  int    iSeed;

  iSkillFactor = 1000 / (oForWhom->query_skill (SS_APPR_OBJ) + 1);
  iArmourClass = oArmour->query_ac ();

  sscanf (OB_NUM (oArmour), "%d", iSeed);

  iSkillFactor = random (iSkillFactor, iSeed);
  iArmourClass = iArmourClass +
                 (iSkillFactor % 2 ? -iSkillFactor % 70
                                   : iSkillFactor) * iArmourClass / 100;
  iArmourClass = MAX (0, iArmourClass);

  switch (iArmourClass)
  {
    case  0 ..  2: return ("flimsy");
    case  3 ..  5: return ("feeble");
    case  6 ..  8: return ("little");
    case  9 .. 12: return ("some");
    case 13 .. 18: return ("a bit of");
    case 19 .. 24: return ("fair");
    case 25 .. 28: return ("good");
    case 29 .. 33: return ("considerable");
    case 34 .. 37: return ("very good");
    case 38 .. 41: return ("excellent");
    case 42 .. 47: return ("fantastic");
    default:       return ("impenetrable");
  }
}


/*
 * Function name : m_appraise_hitloc_strength
 * Description   : Appraise the strength of a specific hitloc.
 *   oMonster      : The owner of the hitloc.
 *   iHitloc       : The hitloc to appraise.
 *   oForWhom      : For whom the appraise is done.
 * Returns       : The strength description.
 *
 */

string m_appraise_hitloc_strength (object oMonster, int iHitloc, object oForWhom)
{
  object oCombat;
  mixed  *axHitloc;
  mixed  xArmourClass;
  int    iArmourClass;
  int    iSkillFactor;
  int    iSeed;
  int    i;

  iSkillFactor = 1000 / (oForWhom->query_skill (SS_APPR_MON) + 1);
  oCombat = oMonster->query_combat_object ();
  axHitloc = oCombat->query_hitloc (iHitloc);
  if (sizeof (axHitloc) <= HIT_M_AC) return ("strange");
  xArmourClass = axHitloc [HIT_AC];
  if (pointerp (xArmourClass))
  {
    iArmourClass = 0;
    for (i = 0 ; i < sizeof (xArmourClass) ; i ++)
    {
      iArmourClass += xArmourClass [i];
    }
    iArmourClass /= sizeof (xArmourClass);
  }
  else iArmourClass = xArmourClass;

  sscanf (OB_NUM (oMonster), "%d", iSeed);

  iSkillFactor = random (iSkillFactor, iSeed);
  iArmourClass = iArmourClass +
                 (iSkillFactor % 2 ? -iSkillFactor % 70
                                   : iSkillFactor) * iArmourClass / 100;
  iArmourClass = MAX (0, iArmourClass);

  switch (iArmourClass)
  {
    case  0 ..  1: return ("very fragile");
    case  2 ..  2: return ("fragile");
    case  3 ..  3: return ("rather frail");
    case  4 ..  4: return ("frail");
    case  5 ..  5: return ("delicate");
    case  6 ..  8: return ("weak");
    case  9 .. 12: return ("sturdy");
    case 13 .. 18: return ("strong");
    case 19 .. 24: return ("tough");
    case 25 .. 28: return ("robust");
    case 29 .. 34: return ("rugged");
    case 35 .. 46: return ("very rugged");
    default:       return ("invincible");
  }
}

//-------------------------------------------------------------------

/*
 * Function name : m_action_appraise
 *
 */

int m_action_appraise (string sArgs)
{
  object oWho = this_player ();
  object *aoWhom;
  object oWhom;
  object oArmour;
  object oCombat;
  int    iHumanoid;
  int    *aiHitlocs;
  mixed  *axHitloc;
  string sHitloc;
  int    iHitloc;
  int    i;

  notify_fail ("Whom wouldst thou appraise ?\n");

  if (!strlen (sArgs)) return (FALSE);
  aoWhom = parse_this (sArgs, "%l");
  if (sizeof (aoWhom) != 1) return (FALSE);
  oWhom = aoWhom [0];

  // Check minimum skills for the command.

  if (oWho->query_skill (SS_APPR_OBJ) < 3)
  {
    write ("You would first need to improve your skills in " +
           "object appraisal.\n");
    return (TRUE);
  }

  if (oWho->query_skill (SS_APPR_MON) < 3)
  {
    write ("You would first need to improve your ability " +
           "to appraise other creatures.\n");
    return (TRUE);
  }

  // Get the hitlocs of the target.

  iHumanoid = oWhom->query_humanoid ();
  oCombat = oWhom->query_combat_object ();
  aiHitlocs = oCombat->query_hitloc_id ();

  if (!sizeof (aiHitlocs))
  {
    write (XCPOS (oWhom) + " body seems impervious to your scrutiny.\n");
    return (TRUE);
  }

  for (i = 0 ; i < sizeof (aiHitlocs) ; i ++)
  {
    iHitloc = aiHitlocs [i];
    axHitloc = oCombat->query_hitloc (iHitloc);

    if (sizeof (axHitloc) > HIT_M_AC)
    {
      // For humanoids, the hitloc is the same as the tool
      // slot for the armour, which is used here.

      if (iHumanoid) oArmour = oWhom->query_armour (iHitloc);
                else oArmour = NULL;

      sHitloc = axHitloc [HIT_DESC];

      if (objectp (oArmour))
      {
        write (capitalize (LANG_THESHORT (oArmour)) +
               " covering " + XPOS (oWhom) + " " +
               m_appraise_hitloc_strength (oWhom, iHitloc, oWho) +
               " " + sHitloc + " " +
               (dg_is_singular (oArmour) ? "appears" : "appear") +
               " to offer " +
               m_appraise_armour_strength (oArmour, oWho) +
               " protection.\n");
      }
      else
      {
        write (XCPOS (oWhom) + " " + sHitloc + " " +
               (dg_is_singular (sHitloc) ? "appears" : "appear") + " " +
               m_appraise_hitloc_strength (oWhom, iHitloc, oWho) + ".\n");
      }
    }
  }

  M_SOULDESC ("concentrating deeply on something");

  return (TRUE);
}

//-------------------------------------------------------------------

