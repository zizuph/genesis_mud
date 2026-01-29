/*******************************************************************\
| SHADOW_BASE_COMBAT.C                                              |
\*******************************************************************/

/* 22/04/12 Lavellan    Fixed "attack" stuff to not mess up when using a weapon
 * 11/02/03 ?           Last of who knows how many uncommented changes..
 * 07/12/09 Arandir     Mercade thinks this has to be renamed from H to C
 * 07/06/03 Arandir     Support for configurable learning in combat
 *                      Fixed a couple of typos in learning messages
 * 07/05/26 Arandir     Blacklisting and whitelisting of weapons
 * 07/05/18 Arandir     Better implementation of the cap that
 *                      logs suspect weapons for later check
 * 07/04/27 Cotillion   Capped hit and pen that can be gained
 * 06/09/13 Arandir     Better description when acquiring hit and pen
 *                      Smaller chance of breaking armours
 * 06/09/04 Arandir     Fixed specials using wrong hit and pen
 *                      Extended debugging to log numerical values
 * 06/09/02 Arandir     Fixed use of XOBJ style macros
 *                      Added notifications for non player characters
 * 06/08/28 Arandir     Added the ability to acquire hit and pen
 * 06/08/16 Arandir     Removed the ability to focus
 *                      Removed the tracking of karma
 * 04/08/14 Arandir     Monsters do not get disgraced on kill
 * 04/08/03 Arandir     Removed some unused variables
 * 04/05/22 Arandir     Used centralized hooks
 * 03/11/04 Arandir     Made specials stop silently on kill
 * 03/08/11 Arandir     Fixed the combat messages
 * 03/08/10 Arandir     Copied off the base file
 * 18/07/25 Arman       Made hit and pen acquisition a skill the saves over logins
 * 20/07/05 Ckrik       Removed auto punishment of killing non-Monk players
 *                      because there are too many loose ends for mwarn.
 *                      Auto punishment remains for fraticides.
 * 21/02/07 Arman       Increased karma decay time for m_decay_acquired_weapon
 *                      as a quality of life improvement while monks wait for
 *                      the recode.
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

#define M_DEBUG_LOCAL_ACQUIRE   FALSE
#define M_DEBUG_LOCAL_PLEXUS    FALSE
#define M_DEBUG_LOCAL_STRIKE    FALSE
#define M_USE_STANDARD_STUN     TRUE

//-------------------------------------------------------------------

// Macros to somewhat shorten the display code, assuming the
// existence of the shadow_who and oTarget variables.

#define M_TELL_SW(sText)        shadow_who->catch_tell (sText + "\n")
#define M_MSG_SW(sText)         shadow_who->catch_msg (sText + "\n")

#define M_TELL_TG(sText)        oTarget->catch_tell (sText + "\n")
#define M_MSG_TG(sText)         oTarget->catch_msg (sText + "\n")

#define M_TELL_WT(sText)        shadow_who->tell_watcher (sText + "\n", oTarget)

#define M_TG_QTNAME             QTNAME (oTarget)
#define M_SW_QTNAME             QTNAME (shadow_who)
#define M_TG_QCTNAME            QCTNAME (oTarget)
#define M_SW_QCTNAME            QCTNAME (shadow_who)
#define M_TG_QOBJ               oTarget->query_objective ()
#define M_SW_QOBJ               shadow_who->query_objective ()
#define M_TG_QPOS               oTarget->query_possessive ()
#define M_SW_QPOS               shadow_who->query_possessive ()
#define M_TG_QPNOUN             oTarget->query_pronoun ()
#define M_SW_QPNOUN             shadow_who->query_pronoun ()

// Attack descriptions and related macros

#define M_DIR_NONE              0
#define M_DIR_HIGH_TO_LOW       1
#define M_DIR_HIGH_TO_HIGH      2
#define M_DIR_LOW_TO_LOW        3
#define M_DIR_LOW_TO_HIGH       4

#define M_DESC_FOOT_RIGHT       "right foot"
#define M_DESC_FOOT_LEFT        "left foot"
#define M_DESC_FIST_RIGHT       "right fist"
#define M_DESC_FIST_LEFT        "left fist"

//-------------------------------------------------------------------

static private string *asMonkWarned = ({ });

static private int iAcquiredHit = shadow_who->query_skill(M_SKILL_ACQUIRED_HIT);
static private int iAcquiredPen = shadow_who->query_skill(M_SKILL_ACQUIRED_PEN);

static private int iPlexusAlarm = ALARM_NONE;
static private int iStrikeAlarm = ALARM_NONE;

// The weapons blacklist shows weapons that have suspect stats
// inaccessible to mortals that we cannot turn off, and
// therefore cannot learn from

static private string *asWeaponBlacklist = ({
  // Gigantic Steel Broadsword
  //   Has constantly high hit and pen
  //   Compensates with various penalties
  "/d/Earthsea/roke/thwil/wep/gigantic_sword",
  // Sledgehammer of the colossus
  //   Has constantly high hit and pen
  //   Only obtainable by ogres, at a high cost
  "/d/Emerald/common/guild/aod/wep/forgeclub9",
});

// The weapons whitelist shows weapons that have suspect stats
// either accessible to mortals, or inaccessible to mortals
// that we can turn off, and therefore can learn from

static private string *asWeaponWhitelist = ({
  // Blackened Heavy Battleaxe
  //   Increases hit in wield using query_skill
  //   Resets hit on unwield
  "/d/Earthsea/gont/gont_city/wep/bl_battleaxe",
  // Mithril Bladed Battleaxe
  //   Increases hit and pen in wield using query_real_name
  //   Resets hit and pen on unwield
  "/d/Gondor/ithilien/poros/weapons/mithril_axe",
  // Humming Fire Battleaxe
  //   Increases hit and pen in wield using query_npc
  //   Resets hit and pen on unwield
  "/d/Kalad/common/noble/wep/fire_axe",
  // Sleek Ashwood Longbow
  //   Increases hit and pen in wield using query_npc
  //   Resets hit and pen on unwield
  "/d/Krynn/qualinesti/wep/ash_bow",
});

public int
query_acquiredhit()
{
    return iAcquiredHit;
}

public int
query_acquiredpen()
{
    return iAcquiredPen;
}

//-------------------------------------------------------------------

/*******************************************************************\
| Warning related functions                                         |
\*******************************************************************/

/*
 * Function name : m_add_warning
 * Description   : Adds the target to the list of warned players
 *
 */

void m_add_warning (mixed xWho)
{
  string sWho = objectp (xWho) ? dg_get_name (xWho) : xWho;
  if (member_array (sWho, asMonkWarned) < 0)
  {
    asMonkWarned += ({ sWho });
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| General attack related functions                                  |
\*******************************************************************/

/*
 * Function name : m_special_active
 * Description   : Check to see if the alarm for attacking is
 *                 set. If it is, then the shadowed player is
 *                 currently either preparing or recovering
 *                 from a special attack.
 *
 */

int m_special_active ()
{
  return ((iPlexusAlarm != ALARM_NONE) || (iStrikeAlarm != ALARM_NONE));
}


/*
 * Function name : m_special_interrupt
 * Description   : Silently interrupt a special attack.
 *
 */

void m_special_interrupt ()
{
  DG_REMOVE_ALARM (iPlexusAlarm);
  DG_REMOVE_ALARM (iStrikeAlarm);
}


/*
 * Function name : m_may_special_attack
 * Description   : See if we are allowed to special attack someone.
 *   oWhom         : Whom do we want to attack.
 *   sAttack       : Which attack do we want to use in lowercase.
 * Returns       : A string describing why we cannot attack or FALSE.
 *
 */

mixed m_may_special_attack (object oWhom, string sAttack)
{
  mixed xResult;

  // We can only attack livings that are present in the room.

  if (!oWhom ||
      !living (oWhom) ||
      !present (oWhom, environment (shadow_who)) ||
      (shadow_who == oWhom))
  {
    return ("You do not see the target of your " + sAttack + ".\n");
  }

  // We may not attack when stunned or waiting.

  if (shadow_who->query_prop (LIVE_I_ATTACK_DELAY) ||
      shadow_who->query_prop (LIVE_I_STUNNED))
  {
    return ("You are too stunned to " + sAttack + ".\n");
  }

  // Some properties can prevent us from attacking.
  if ((xResult = oWhom->query_prop (OBJ_M_NO_ATTACK)) ||
      (xResult = environment (oWhom)->query_prop (ROOM_M_NO_ATTACK)))
  {
    if (stringp(xResult))
        return (xResult);
    return ("You sense a force protecting " + XTNAME (shadow_who, oWhom) + ".\n");
  }

  // Certain functions in the target may block all special attacks.

  if (oWhom->query_not_attack_me (shadow_who, -1))
  {
    // A message is given by query_not_attack_me, none needed here.

    return ("");
  }

  // Certain properties in the target may block our special attacks.

  xResult = oWhom->query_prop (M_PROP_LIVE_NO_SPECIAL + sAttack);
  if (stringp (xResult))
  {
    return (xResult);
  }

  // We also have some checks that depend on the attack type.

  switch (sAttack)
  {
    case "strike":

      // This is just a placeholder for possible future checks.

      break;

    case "plexus":

      // The enemy has to have a human shape to have a solar plexus.

      if (!dg_is_humanoid (oWhom))
      {
        return (XCTNAME (shadow_who, oWhom) + " does not have " +
                "a solar plexus you can hit.\n");
      }

      break;
  }

  return (FALSE);
}


/*
 * Function name : m_set_special_target
 * Description   : Start attacking the target of a special attack.
 *   oWhom         : Whom do we want to attack.
 * Returns       : A string describing why we cannot attack or FALSE.
 *
 */

mixed m_set_special_target (object oWhom)
{
  object oEnemy;
  string sFragmentHim;
  string sFragmentOthers;

  // Some checks are executed only when we are not fighting yet.

  oEnemy = shadow_who->query_attack ();
  if (oWhom != oEnemy)
  {
    // We must dare to attack when not in combat yet.

    if (!F_DARE_ATTACK (shadow_who, oWhom))
    {
      return ("You don't dare attack.\n");
    }

    // Introduced players should not be attacked straight away.

    if (!(shadow_who->query_npc ()) &&
        (shadow_who->query_met (oWhom)) &&
        (shadow_who->query_prop (LIVE_O_LAST_KILL) != oWhom))
    {
      shadow_who->add_prop (LIVE_O_LAST_KILL, oWhom);
      return ("Attack " + XTNAME (shadow_who, oWhom) + " ? " +
              "Please confirm by trying again.\n");
    }

    // Attack the object that is our target.

    shadow_who->attack_object (oWhom);

    if (objectp (oEnemy))
    {
      sFragmentHim = "turn to attack";
      sFragmentOthers = "turns to attack";
    }
    else
    {
      sFragmentHim = "attack";
      sFragmentOthers = "attacks";
    }

    shadow_who->catch_tell ("You " + sFragmentHim + " " + XTNAME (shadow_who, oWhom) + ".\n");
    oWhom->catch_tell (XCTNAME (oWhom, shadow_who) + " " + sFragmentOthers + " you !\n");
    say (QCTNAME (shadow_who) + " " + sFragmentOthers + " " + QTNAME (oWhom) + ".\n", ({ shadow_who, oWhom }));
  }

  return (FALSE);
}


/*
 * Function name : m_add_special_fatigue
 * Description   : Add a fatigue to the player after a special attack.
 *
 */

void m_add_special_fatigue ()
{
  int iFatigue = shadow_who->query_fatigue ();
  int iDrain = random (3);

  if (iFatigue < iDrain)
  {
    shadow_who->heal_hp (iFatigue - iDrain);
    shadow_who->set_fatigue (0);
    M_TELL_SW ("The strain of the attack drains you.");
  }
  else
  {
    shadow_who->add_fatigue (-iDrain);
  }
}


/*
 * Function name : adjust_combat_on_move
 * Description   : Called to let movement affect the ongoing fight.
 *   iLeaving      : Distinguishes leaving from arriving.
 *
 */

void adjust_combat_on_move (int iLeaving)
{
  if (m_special_active ())
  {
    m_special_interrupt ();
    M_TELL_SW ("You stop preparing your attack.");
  }

  shadow_who->adjust_combat_on_move (iLeaving);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Acquire related functions                                         |
\*******************************************************************/

/*
 * Function name : m_get_default_hit
 * Function name : m_get_default_pen
 * Description   : Returns the default values of hit and pen for unarmed.
 *
 */

int m_get_default_hit ()
{
  return (W_HAND_HIT +
          F_UNARMED_HIT (shadow_who->query_skill (SS_UNARM_COMBAT),
                         shadow_who->query_stat (SS_DEX)));
}

int m_get_default_pen ()
{
  return (W_HAND_PEN +
          F_UNARMED_PEN (shadow_who->query_skill (SS_UNARM_COMBAT),
                         shadow_who->query_stat (SS_STR)));
}


/*
 * Function name : m_adjust_acquired_weapon
 * Description   : Adjusts the unarmed attacks to match the acquired weapon.
 *
 */

void m_adjust_acquired_weapon ()
{
  object oCombat = shadow_who->query_combat_object ();
  int iSkill = shadow_who->query_skill (SS_UNARM_COMBAT);
  int *aiAttacks = oCombat->query_attack_id();

#if M_DEBUG_LOCAL_ACQUIRE
s_log (M_LOG_DEBUG, "Adjusting to acquired hit " + iAcquiredHit + " pen " + iAcquiredPen + ".");
#endif

  // The addition of 6 to unarmed skill for left and right hand
  // is copied off humanoid unarmed. No idea why mudlib does it
  // but we want to do the same ...
  if (IN_ARRAY(W_LEFT, aiAttacks))
    if (!oCombat->query_attack(W_LEFT)[6])
      oCombat->add_attack (iAcquiredHit, iAcquiredPen, W_BLUDGEON, 25, W_LEFT, iSkill + 6);
  if (IN_ARRAY(W_RIGHT, aiAttacks))
    if (!oCombat->query_attack(W_RIGHT)[6])
      oCombat->add_attack (iAcquiredHit, iAcquiredPen, W_BLUDGEON, 25, W_RIGHT, iSkill + 6);
  if (IN_ARRAY(W_FOOTL, aiAttacks))
    if (!oCombat->query_attack(W_FOOTL)[6])
      oCombat->add_attack (iAcquiredHit, iAcquiredPen, W_BLUDGEON, 25, W_FOOTL, iSkill);
  if (IN_ARRAY(W_FOOTR, aiAttacks))
    if (!oCombat->query_attack(W_FOOTR)[6])
      oCombat->add_attack (iAcquiredHit, iAcquiredPen, W_BLUDGEON, 25, W_FOOTR, iSkill);
}


/*
 * Function name : m_decay_acquired_weapon
 * Description   : Decays the acquired weapon hit and pen.
 *
 */

void m_decay_acquired_weapon ()
{
  int iInt;
  int iWis;
  int iMinimumHit;
  int iMinimumPen;

  // The decay function is called once per minute. We use randomization
  // to make sure decay is done as per the formula but not regularly.
  // - the function is now called every 2 minutes, Arman.

  iInt = shadow_who->query_stat (SS_INT);
  iWis = shadow_who->query_stat (SS_WIS);
  if (!random (M_ACQUIRE_DECAY (iInt, iWis)))
  {
    // The calculation of minimum values is copied off humanoid unarmed.
    iMinimumHit = m_get_default_hit ();
    iMinimumPen = m_get_default_pen ();

    if (time() - shadow_who->query_combat_time() <= 60)
    {
      if ((iAcquiredHit > iMinimumHit) ||
          (iAcquiredPen > iMinimumPen))
      {
        iAcquiredHit = max (iAcquiredHit - 1, iMinimumHit);
        shadow_who->set_skill(M_SKILL_ACQUIRED_HIT, iAcquiredHit);
        iAcquiredPen = max (iAcquiredPen - 1, iMinimumPen);
        shadow_who->set_skill(M_SKILL_ACQUIRED_PEN, iAcquiredPen);

        m_adjust_acquired_weapon ();
      }
    }
  }
}

/*
 * Function:    m_get_karma_percentage
 * Description: Karma/Lessons learned add to the iAcquiredPen and iAcquiredHit
 *              which directly affect the hit/pen of the monk's attacks.
 *              This function determines the percentage of the karma that the
 *              monk has compared to the maximum that is achievable.
 */
public int 
m_get_karma_percentage(int pen = iAcquiredPen, int hit = iAcquiredHit)
{
    // The range of karma goes from the default hit/pen when logging in
    // to the maximums imposed by the "suspect" defines. 
    int rangeBegin = m_get_default_hit() + m_get_default_pen();
    int rangeEnd   = M_WEAPON_SUSPECT_HIT + M_WEAPON_SUSPECT_PEN;
    
    int monkKarma = max(0, pen + hit - rangeBegin);
    int totalRange = max(1, rangeEnd - rangeBegin);
    
    return min(100, (monkKarma * 100) / totalRange);
}

/*
 * Function:    m_get_karma_description
 * Description: Returns the description of how much karma the monk
 *              has relative to his maximum.
 */
public string
m_get_karma_description(int pen = iAcquiredPen, int hit = iAcquiredHit)
{
    int karmaPercentage = m_get_karma_percentage(pen, hit);
    string sDescription;
    switch (karmaPercentage)
    {
        case  0:       sDescription = "no"; break;     
        case  1 ..  5: sDescription = "tiny"; break;
        case  6 .. 10: sDescription = "slight"; break;
        case 11 .. 15: sDescription = "little"; break;
        case 16 .. 20: sDescription = "simple"; break;
        case 21 .. 30: sDescription = "decent"; break;
        case 31 .. 40: sDescription = "nice"; break;
        case 41 .. 50: sDescription = "interesting"; break;
        case 51 .. 60: sDescription = "useful"; break;
        case 61 .. 70: sDescription = "valuable"; break;
        case 71 .. 80: sDescription = "tremendous"; break;
        case 81 .. 90: sDescription = "terrific"; break;
        default:       sDescription = "invaluable"; break;
    }
    
    return sDescription;
}

/*
 * Function name : m_acquire_weapon
 * Description   : Acquire the best weapon hit and pen of a victim.
 *
 */

void m_acquire_weapon (object oWho)
{
  object oCombat;
  object oWeapon;
  int *aiAttacks;
  mixed *axAttack;
  int iMaxHit = 0;
  int iMaxPen = 0;
  int iHit;
  int iPen;
  int iClass;
  int iSkill;
  int iDegree;
  string sDegree;

  // See what the victim has in terms of weapons.

  oCombat = oWho->query_combat_object ();
  if (!objectp (oCombat)) return;
  aiAttacks = oCombat->query_attack_id ();
  if (!sizeof (aiAttacks)) return;

  foreach (int iAttack : aiAttacks)
  {
    // By best attack we mean the best sum of hit and pen.
    axAttack = oCombat->query_attack (iAttack);
    iHit = axAttack [ATT_WCHIT];
    iPen = max (axAttack [ATT_WCPEN][0],
                axAttack [ATT_WCPEN][1],
                axAttack [ATT_WCPEN][2]);
    if (iMaxHit + iMaxPen < iHit + iPen)
    {
      // We use the hit and pen of the weapon rather than
      // the hit and pen of the attack, which can be
      // adjusted due to various modifiers ...
      oWeapon = axAttack [ATT_OBJ];
      if (objectp (oWeapon))
      {
        // These are hacks to get weapons whose stats
        // differ for monsters and mortals to behave

        // Hack One: Unwield
        oWeapon->unwield ();

        // After the hacks here the weapon should be
        // exactly as powerful as when mortals use it

        iMaxHit = oWeapon->query_hit ();
        iMaxPen = oWeapon->query_pen ();
        iClass = oWeapon->query_wt ();

        // For two handed weapons, we rescale the hit/pen to reflect
        // the one handed vs two handed max hit/pen limits
        if (oWeapon->query_hands () == W_BOTH)
        {
          iMaxHit = iMaxHit * 50 / 60;
          iMaxPen = iMaxPen * 50 / 60;
        }

        if ((iMaxHit >= M_WEAPON_SUSPECT_HIT) ||
            (iMaxPen >= M_WEAPON_SUSPECT_PEN))
        {
          if (member_array (MASTER_OB (oWeapon), asWeaponWhitelist) < 0)
          {
            // The weapon is not whitelisted and must be capped
            iMaxHit = min (iMaxHit, M_WEAPON_SUSPECT_HIT);
            iMaxPen = min (iMaxPen, M_WEAPON_SUSPECT_PEN);
            if (member_array (MASTER_OB (oWeapon), asWeaponBlacklist) < 0)
            {
              // The weapon is not blacklisted and must be reported
              s_log (M_LOG_DEBUG, "Suspect acquired weapon has hit " + iMaxHit + " pen " + iMaxPen + ".", oWeapon);
            }
          }
        }
      }
      else
      {
        // There is no weapon, take the attack as is
        iMaxHit = iHit;
        iMaxPen = iPen;
        iClass = W_NO_T;
      }
    }
  }

#if M_DEBUG_LOCAL_ACQUIRE
s_log (M_LOG_DEBUG, "The acquired weapon has hit " + iMaxHit + " pen " + iMaxPen + " class " + iClass + ".");
#endif

  // See if we have chanced upon something better than we have.

  if ((iMaxHit > iAcquiredHit) || (iMaxPen > iAcquiredPen))
  {
    // Acquiring a weapon is a random task governed
    // by the appropriate forming skillclass ...

    switch (iClass)
    {
      case W_AXE:
      case W_CLUB:
        iSkill = M_SKILL_FORMING_CLUB;
        break;
      case W_KNIFE:
      case W_SWORD:
        iSkill = M_SKILL_FORMING_BLADE;
        break;
      case W_JAVELIN:
      case W_POLEARM:
        iSkill = M_SKILL_FORMING_STICK;
        break;
      default:
        iSkill = 0;
        break;
    }

#if M_DEBUG_LOCAL_ACQUIRE
s_log (M_LOG_DEBUG, "The acquisition skill is " + iSkill + ".");
#endif

    if (iSkill)
    {
      // Calculate the degree of improvement
      // so that the message can be customized.

      // We compare the percentage full of karma before and after this lesson
      // is learned to get the correct description.
      iDegree = m_get_karma_percentage(iMaxPen, iMaxHit) - m_get_karma_percentage();
      switch (iDegree)
      {
        case  0 ..  5: sDegree = "a tiny"; break;
        case  6 .. 10: sDegree = "a slight"; break;
        case 11 .. 15: sDegree = "a little"; break;
        case 16 .. 20: sDegree = "a simple"; break;
        case 21 .. 30: sDegree = "a decent"; break;
        case 31 .. 40: sDegree = "a nice"; break;
        case 41 .. 50: sDegree = "an interesting"; break;
        case 51 .. 60: sDegree = "a useful"; break;
        case 61 .. 70: sDegree = "a valuable"; break;
        case 71 .. 80: sDegree = "a tremendous"; break;
        case 81 .. 90: sDegree = "a terrific"; break;
        default:       sDegree = "an invaluable"; break;
      }

      // Improve if the random task succeeds ...

      int bWeaponBroken = 0;
      if (shadow_who->resolve_task (TASK_ROUTINE, ({ iSkill, iSkill })) > 0)
      {
        if (objectp (oWeapon))
        {
          // Try to break the weapon. Some weapons don't break, so we have to
          // check afterwards to make sure that it's actually broken. Learning
          // from an unbreakable weapon would allow a monk to exploit this
          // weapon endlessly.
          oWeapon->remove_broken(TRUE);
          bWeaponBroken = oWeapon->query_prop(OBJ_I_BROKEN);
        }
        else
        {
          // If there is no actual weapon, it's an attack and it always "breaks"
          bWeaponBroken = 1;
        }
      }
      
      if (bWeaponBroken)
      {
        iAcquiredHit = max (iMaxHit, iAcquiredHit);
        shadow_who->set_skill(M_SKILL_ACQUIRED_HIT, iAcquiredHit);
        iAcquiredPen = max (iMaxPen, iAcquiredPen);
        shadow_who->set_skill(M_SKILL_ACQUIRED_PEN, iAcquiredPen);
        m_adjust_acquired_weapon ();

        M_TELL_SW ("You realize you have learned " + sDegree + " lesson from this fight.");
      }
      else
      {
        M_TELL_SW ("You realize you have missed " + sDegree + " lesson in this fight.");
      }
    }
  }
}

/*
 * Function name : unwield
 * Description   : Shadowed to recalculate unarmed when unwielding weapon
 *
 */
public void
unwield(object weapon)
{
    shadow_who->unwield(weapon);
    set_alarm(1.0, 0.0, m_adjust_acquired_weapon);
}

// Ckrik 20210515 intercepts necessary for karma to function
// properly with existing enhancers
public mixed
wear_arm(object ob)
{
    shadow_who->wear_arm(ob);
    set_alarm(1.0, 0.0, m_adjust_acquired_weapon);
}
public mixed
wear_clothing(object ob)
{
    shadow_who->wear_clothing(ob);
    set_alarm(1.0, 0.0, m_adjust_acquired_weapon);
}
public void
remove_arm(object ob)
{
    shadow_who->remove_arm(ob);
    set_alarm(1.0, 0.0, m_adjust_acquired_weapon);
}
public void
remove_clothing(object ob)
{
    shadow_who->remove_clothing(ob);
    set_alarm(1.0, 0.0, m_adjust_acquired_weapon);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Plexus related functions                                          |
\*******************************************************************/

/*
 * Function name : m_plexus_message
 * Description   : Describe the result of the plexus
 *   iHitsuc       : The success of the hit.
 *   oTarget       : The target of the hit.
 *   oArmour       : The body armour of the target.
 *   iArmourClass  : The armour class of the armour.
 *
 */

void m_plexus_message (int iHitsuc, object oTarget, object oArmour, int iArmourClass)
{
  if (iHitsuc < 0)
  {
    // This is a complete miss ...

    M_MSG_SW (
      "You aim your open hand at " + M_TG_QTNAME + ", but " +
      M_TG_QPNOUN + " dodges aside.");
    M_MSG_TG (
      M_SW_QCTNAME + " aims for your solar plexus with " +
      M_SW_QPOS + " open hand, but you dodge aside.");
    M_TELL_WT (
      M_SW_QCTNAME + " aims for the solar plexus of " +
      M_TG_QTNAME + ", but " + M_TG_QPNOUN + " dodges aside.");

    return;
  }

  if (iHitsuc == 0)
  {
    // This is a hit that had no effect ...

    if (iArmourClass > 5)
    {
      // Blame the failed hit on the body armour of the target.

      M_MSG_SW (
        "You drive your open hand into " + M_TG_QTNAME + "'s solar " +
        "plexus, but the force is absorbed by " + M_TG_QPOS + " " +
        QSHORT (oArmour) + ".");
      M_MSG_TG (
        M_SW_QCTNAME + " drives " + M_SW_QPOS + " open hand into your " +
        "solar plexus, but the force of the blow is absorbed by your " +
        QSHORT (oArmour) + ".");
      M_TELL_WT (
        M_SW_QCTNAME + " drives " + M_SW_QPOS + " open hand into " +
        M_TG_QTNAME + "'s solar plexus, " + "but the force of the " +
        "blow is absorbed by " + M_TG_QPOS + " " + QSHORT (oArmour) + ".");

      return;
    }
    else
    {
      // No body armour to blame the failed hit on.

      M_MSG_SW (
        "You drive your open hand into " + M_TG_QTNAME + "'s solar " +
        "plexus, but the blow seems to have no effect.");
      M_MSG_TG (
        M_SW_QCTNAME + " drives " + M_SW_QPOS + " open hand into " +
        "your solar plexus, but the blow seems to have no effect.");
      M_TELL_WT(
        M_SW_QCTNAME + " drives " + M_SW_QPOS + " open hand into " +
        M_TG_QTNAME + "'s solar plexus, but the blow seems to have " +
        "no effect.");

      return;
    }
  }

  // This means we did hit normally ...

  M_TELL_WT (
    M_SW_QCTNAME + " drives " + M_SW_QPOS + " open hand into " +
    M_TG_QTNAME + "'s solar plexus, stunning " + M_TG_QOBJ + ".");
  M_MSG_SW (
    "You strike " + M_TG_QTNAME + "'s solar plexus with your " +
    "open hand, stunning " + M_TG_QOBJ + ".");
  M_MSG_TG (
    M_SW_QCTNAME + " strikes your solar plexus with " + M_SW_QPOS +
    " open hand. You feel numb.");
}


/*
 * Function name : m_do_plexus
 * Description   : Handles the effect of the plexus special attack.
 *   oWhom         : Who was the target.
 *
 */

void m_do_plexus (object oWhom)
{
  object oArmour;
  object oCombat;
  object oStun;
  int    iArmourClass;
  int    iHitsuc;
  int    iStr;
  int    iDex;
  int    iWis;
  int    iPlexus;
  float  fStunTime;
  float  fSlowTime;
  mixed  xResist;
  mixed  xResult;

  iPlexusAlarm = ALARM_NONE;

  // Make sure the target did not become invalid ...

  xResult = m_may_special_attack (oWhom, "plexus");
  if (stringp (xResult))
  {
    shadow_who->catch_tell (xResult);
    return;
  }

  // Get some data on us and the target ...

  oArmour = oWhom->query_armour (TS_TORSO);
  if (objectp (oArmour)) iArmourClass = oArmour->query_ac ();

  iStr = shadow_who->query_stat (SS_STR);
  iDex = shadow_who->query_stat (SS_DEX);
  iWis = shadow_who->query_stat (SS_WIS);
  iPlexus = shadow_who->query_skill (M_SKILL_PLEXUS);

  // Test to see if we hit ...

  oCombat = shadow_who->query_combat_object ();
  iHitsuc = oCombat->cb_tohit (W_ANYH, M_PLEXUS_HIT, oWhom);

  if (iHitsuc > 0)
  {
    // Calculate the stun phase and slow phase time.

    fStunTime = M_PLEXUS_STUN_DELAY (iPlexus, iStr, iDex);
    fSlowTime = M_PLEXUS_SLOW_DELAY (iPlexus, iDex, iWis);

    xResist = oWhom->query_prop (M_PROP_LIVE_NO_SPECIAL + "plexus");
    if (intp (xResist))
    {
      fStunTime = (itof (100 - xResist) * fStunTime) / 100.0;
      fSlowTime = (itof (100 - xResist) * fSlowTime) / 100.0;
    }

#if M_DEBUG_LOCAL_PLEXUS
s_log (M_LOG_DEBUG, "Plexus stun " + ftoa (fStunTime) + " slow " + ftoa (fSlowTime) + ".");
#endif

#if M_USE_STANDARD_STUN
    // The standard stun object correctly handles combat aid max of 100, allowing
    // cooldown times to be considered. We clone it here and start the effect.
    oStun = clone_object (M_PATH_OBJ + "/stun_new");
    oStun->m_land_plexus (shadow_who, oWhom, fStunTime, fSlowTime);
#else
    // Use the old stun object to administer the paralysis.

    oStun = present (M_PLEXUS_STUN_ID, oWhom);
    if (!objectp (oStun))
    {
      DG_FIXUID;
      oStun = clone_object (M_PATH_OBJ + "/stun");
      oStun->move (oWhom, MOVE_SUBLOC_ALWAYS);
    }

    oStun->m_land_plexus (fStunTime, fSlowTime);
#endif
  }

  // Display a message about the special before doing other potentially visible things.
  if (iHitsuc <= 0 || objectp(oStun))
  {
    // We only display the message for misses and actual stuns. If it hits a cooldown,
    // when using a standard stun, the stun object displays its own messages.
    m_plexus_message (iHitsuc, oWhom, oArmour, iArmourClass);
  }

  if (m_get_learning (shadow_who) && iHitsuc > 0)
  {
    // Successful hits can damage the body armour when the monk has turned off mdisdain.
    // Conversely, if they choose not to break weapons, they will also not break
    // armours when they plexus.

    if ((iArmourClass > 5) && (random (3) == 0))
    {
      oArmour->set_condition (oArmour->query_condition () + 1);
    }
  }

  // Specials tire us a bit.

  m_add_special_fatigue();

  // Notify non player characters about finished special so that it can be restarted.

  if (!interactive (oWhom)) oWhom->m_notify_plexus_landed ();
}


/*
 * Function name : m_start_plexus
 * Description   : Commences the plexus special attack
 *   oWhom         : Whom to hit
 *
 */

void m_start_plexus (object oWhom)
{
  mixed xResult;

  // Check whether we are free to execute the special ...

  if (iPlexusAlarm != ALARM_NONE)
  {
    M_TELL_SW ("You are already preparing an attack.");
    return;
  }

  // Check whether we are allowed to execute the special and attack the target ...

  xResult = m_may_special_attack (oWhom, "plexus");
  if (stringp (xResult))
  {
    shadow_who->catch_tell (xResult);
    return;
  }

  xResult = m_set_special_target (oWhom);
  if (stringp (xResult))
  {
    shadow_who->catch_tell (xResult);
    return;
  }

  // Notify about starting the attack and schedule the hit.

  M_TELL_SW ("You try to get a chance to hit " +
             XOBJ (oWhom) +
             " in the solar plexus.");

  iPlexusAlarm = set_alarm (M_PLEXUS_LAND_DELAY (
                              shadow_who->query_skill (M_SKILL_PLEXUS),
                              shadow_who->query_stat (SS_DEX),
                              shadow_who->query_stat (SS_WIS)),
                            0.0, &m_do_plexus (oWhom));
}

//-------------------------------------------------------------------

/*******************************************************************\
| Strike related functions                                          |
\*******************************************************************/

/*
 * Function name : m_get_strike_weapon
 * Description   : Get a random attack that is used to say
 *                 to the player what he used to strike with.
 *                 Does not return attacks with wielded weapon.
 *   oWho          : Who is doing the strike.
 * Returns       : A name of the attacking body part.
 *
 */

string m_get_strike_weapon ()
{
  string *asAttacks;

  // We can not hold a weapon in our legs ...

  asAttacks = ({ M_DESC_FOOT_LEFT, M_DESC_FOOT_RIGHT });

  // If we are not wielding anything in both hands, we can be
  // wielding something in either hand ...

  if (!objectp (shadow_who->query_weapon (W_BOTH)))
  {
    if (!objectp (shadow_who->query_weapon (W_LEFT)))
      asAttacks += ({ M_DESC_FIST_LEFT });
    if (!objectp (shadow_who->query_weapon (W_RIGHT)))
      asAttacks += ({ M_DESC_FIST_RIGHT });
  }

  // Now just return a random attack.

  return (one_of_list (asAttacks));
}


/*
 * Function name : m_get_strike_direction
 * Description   : Figures out the direction of an attack
 *                 given the combination of a weapon and
 *                 a target.
 *   sWith         : The weapon.
 *   sWhere        : The target.
 * Returns       : Direction indication
 *
 */

int m_get_strike_direction (string sWith, string sWhere)
{
  if ((sWith == "left fist") || (sWith == "right fist"))
  {
    // From high
    if (sWhere == "legs") return (M_DIR_HIGH_TO_LOW);
                     else return (M_DIR_HIGH_TO_HIGH);
  }
  else
  {
    // From low
    if (sWhere == "legs") return (M_DIR_LOW_TO_LOW);
                     else return (M_DIR_LOW_TO_HIGH);
  }
}


/*
 * Function name : m_strike_message
 * Description   : Give a description of the strike special attack
 *   oTarget       : The target we hit
 *   iPHurt        : The percentage of remaining hitpoints we took
 *   sHitLoc       : The location of the target that we hit
 *   iPHit         : The percentage of success we had
 *   iDamage       : The damage in hitpoints we did
 *
 */

void m_strike_message (object oTarget, int iPHurt, string sHitLoc, int iPHit, int iDamage)
{
  string sWeapon = m_get_strike_weapon ();
  int    iPrefix;
  string sPrefixHim = "";
  string sPrefixOthers = "";
  string sHitHim;
  string sHitOthers;

  // On humanoids, we can recognize directions of the strikes.

  if (oTarget->query_humanoid ())
  {
    switch (m_get_strike_direction (sWeapon, sHitLoc))
    {
      case M_DIR_HIGH_TO_LOW:
        iPrefix = random (4);
        sPrefixHim = (({ "Executing a quick roll on the ground",
                         "With a quick downward jab",
                         "Crouching down",
                         "Ducking down" })) [iPrefix];
        sPrefixOthers = (({ "Executing a quick roll on the ground",
                            "With a quick downward jab",
                            "Crouching down",
                            "Ducking down" })) [iPrefix];
        break;

      case M_DIR_HIGH_TO_HIGH:
        iPrefix = random (2);
        sPrefixHim = (({ "Spinning around",
                         "Executing a deft spin on the balls of your feet" })) [iPrefix];
        sPrefixOthers = (({ "Spinning around",
                            "Executing a deft spin on the balls of " + M_SW_QPOS + " feet" })) [iPrefix];
        break;

      case M_DIR_LOW_TO_LOW:
        iPrefix = random (2);
        sPrefixHim = (({ "With a sweeping motion",
                         "Dropping to the ground" })) [iPrefix];
        sPrefixOthers = (({ "With a sweeping motion",
                            "Dropping to the ground" })) [iPrefix];
        break;
    }
  }

  // Make the hitloc description a tad prettier.

  sHitLoc = m_translate_hitloc (sHitLoc);

  // See about the strength of the hit.

  iPHurt = MAX (-1, iPHurt);

  switch (iPHurt)
  {
    case -1:            sHitHim = "miss";       sHitOthers = "misses";          break;
    case 0 .. 2:        sHitHim = "brush";      sHitOthers = "brushes";         break;
    case 3 .. 4:        sHitHim = "bruise";     sHitOthers = "bruises";         break;
    case 5 .. 9:
      if ((sWeapon == M_DESC_FOOT_RIGHT) || (sWeapon == M_DESC_FOOT_LEFT))
      {                 sHitHim = "kick";       sHitOthers = "kicks";
      } else {          sHitHim = "punch";      sHitOthers = "punches";
      }                                                                         break;
    case 10 .. 19:      sHitHim = "strike";     sHitOthers = "strikes";         break;
    case 20 .. 29:      sHitHim = "slam";       sHitOthers = "slams";           break;
    case 30 .. 49:      sHitHim = "smash";      sHitOthers = "smashes";         break;
    default:            sHitHim = "crush";      sHitOthers = "crushes";         break;
  }

  // Now just put it all together.

  if (strlen (sPrefixHim))
  {
    sPrefixHim += ", you " + sHitHim + " ";
    sPrefixOthers += ", " + M_SW_QTNAME + " " + sHitOthers + " ";
  }
  else
  {
    sPrefixHim = "You " + sHitHim + " ";
    sPrefixOthers = M_SW_QCTNAME + " " + sHitOthers + " ";
  }

  M_MSG_SW (sPrefixHim + QTPNAME (oTarget) + " " + sHitLoc + " with your " + sWeapon + ".");
  M_MSG_TG (sPrefixOthers + "your " + sHitLoc + " with " + M_SW_QPOS + " " + sWeapon + ".");
  M_TELL_WT (sPrefixOthers + QTPNAME (oTarget) + " " + sHitLoc + " with " + M_SW_QPOS + " " + sWeapon + ".");
}


/*
 * Function name : m_do_strike
 * Description   : Lands the strike special attack.
 *   oWhom         : Whom to hit
 *   sWhere        : Where to hit
 *
 */

void m_do_strike (object oWhom, string sWhere)
{
  object oCombat;
  int    iHitloc;
  int    iHitsuc;
  int    iHitpen;
  int    iStr;
  int    iDex;
  int    iStrike;
  mixed  xResist;
  mixed  xResult;
  mixed  *axHitres;

  iStrikeAlarm = ALARM_NONE;

  // Make sure the target did not become invalid ...

  xResult = m_may_special_attack (oWhom, "strike");
  if (stringp (xResult))
  {
    shadow_who->catch_tell (xResult);
    return;
  }

  // Get some data on us and the target ...

  iHitloc = dg_get_hitloc_id (oWhom, sWhere);

  iStr = shadow_who->query_stat (SS_STR);
  iDex = shadow_who->query_stat (SS_DEX);
  iStrike = shadow_who->query_skill (M_SKILL_STRIKE);

  // Test to see if we hit ...

  oCombat = shadow_who->query_combat_object ();
  iHitsuc = oCombat->cb_tohit (ATTACK_SPECIAL, M_STRIKE_HIT (iStrike, iAcquiredHit, iDex), oWhom);

  if (iHitsuc > 0)
  {
    iHitpen = M_STRIKE_PEN (iStrike, iAcquiredPen, iStr);

    xResist = oWhom->query_prop (M_PROP_LIVE_NO_SPECIAL + "strike");
    if (intp (xResist))
    {
      iHitpen = ((100 - xResist) * iHitpen) / 100;
    }

    axHitres = oWhom->hit_me (iHitpen, W_BLUDGEON, shadow_who, ATTACK_SPECIAL, iHitloc);
  }
  else
  {
    axHitres = oWhom->hit_me (iHitsuc, 0, shadow_who, ATTACK_SPECIAL, iHitloc);
  }

  // Display a message about the special before doing other potentially visible things.

  m_strike_message (oWhom,
                    axHitres [HITRES_PHURT],
                    axHitres [HITRES_HITLOC_DESC],
                    axHitres [HITRES_PHIT],
                    axHitres [HITRES_DAMAGE]);

  if (iHitsuc > 0)
  {
    // Successful hits can actually kill the victim.

    if (oWhom->query_hp () <= 0)
    {
      oWhom->do_die (shadow_who);
    }
  }

  // Specials tire us a bit.

  m_add_special_fatigue ();

  // Notify non player characters about finished special so that it can be restarted.

  if (!interactive (oWhom)) oWhom->m_notify_strike_landed ();
}


/*
 * Function name : m_start_strike
 * Description   : Commences the strike special attack
 *   oWhom         : Whom to hit
 *   sWhere        : Where to hit
 *
 */

varargs void m_start_strike (object oWhom, string sWhere = "")
{
  mixed xResult;

  // Check whether we are free to execute the special ...

  if (iStrikeAlarm != ALARM_NONE)
  {
    M_TELL_SW ("You are already preparing an attack.");
    return;
  }

  // Check whether we are allowed to execute the special and attack the target ...

  xResult = m_may_special_attack (oWhom, "strike");
  if (stringp (xResult))
  {
    shadow_who->catch_tell (xResult);
    return;
  }

  xResult = m_set_special_target (oWhom);
  if (stringp (xResult))
  {
    shadow_who->catch_tell (xResult);
    return;
  }

  // Notify about starting the attack and schedule the hit.

  if (strlen (sWhere))
  {
    M_TELL_SW ("You prepare to strike " +
               XOBJ (oWhom) +
               " on the " + sWhere + ".");
  }
  else
  {
    M_TELL_SW ("You prepare to strike " +
               XOBJ (oWhom) +
               ".");
  }

  iStrikeAlarm = set_alarm (M_STRIKE_DELAY (
                              shadow_who->query_skill (M_SKILL_STRIKE),
                              shadow_who->query_stat (SS_CON)),
                            0.0, &m_do_strike (oWhom, sWhere));
}

//-------------------------------------------------------------------

/*******************************************************************\
| General combat related functions                                  |
\*******************************************************************/

/*
 * Function name : m_hook_combat_notify_you_killed_me
 * Description   : This is called each time we kill something,
 *                 the function checks for punishments that
 *                 are administered to monks for kills and
 *                 acquires the hit and pen of the victim.
 *   oHim          : Who was killed
 */

void m_hook_combat_notify_you_killed_me (object oHim)
{
  string sText;
  string sMe;

  // Silently stop specials on kill.

  if (m_special_active ()) m_special_interrupt ();

  // Find the best weapon of the victim and acquire
  // its hit and pen, success depending on the
  // appropriate forming skillclass.

  if (m_get_learning (shadow_who)) m_acquire_weapon (oHim);

  // It is against the rules of the guild to kill
  // a monk, to kill a player without warning, and
  // to kill a dragon. For any of this, the monk
  // gets disgraced.

  if (interactive (shadow_who)
      &&
      (
       dg_is_dragon (oHim)
       ||
       (interactive (oHim)
        &&
        (
         (m_is_monk (oHim))
         // Ckrik 20200705 - mwarn has too many loose ends, so for killing non-Monk
         // players, we'll rely on the victim reporting the deed to the council.
         //||
         //(member_array (dg_get_name (oHim), asMonkWarned) < 0)
        )
       )
      )
     )
  {
    m_punish (shadow_who, M_PUNISH_DISGRACE);
    sMe = capitalize (dg_get_name (shadow_who));
    sText = sMe + " was disgraced for killing " +
            LANG_ADDART (oHim->query_nonmet_name ()) +
            " going by the name of " +
            capitalize (dg_get_name (oHim)) + ".";
    s_log (M_LOG_WIZARD | M_LOG_COUNCIL, sText);
    M_OBJ_BOARD_MEMBER->m_post_note (sMe + " disgraced", M_SPIRIT_UPPER, dg_framed_text (sText));
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Initialization                                                    |
\*******************************************************************/

void m_shadow_combat_init ()
{
  // The initial value of the acquired weapon hit and pen
  // must be set to the default unarmed values because
  // specials use it.


  iAcquiredHit = m_get_default_hit ();
  iAcquiredPen = m_get_default_pen ();

  if(shadow_who->query_skill(M_SKILL_ACQUIRED_HIT) > iAcquiredHit)
      iAcquiredHit = shadow_who->query_skill(M_SKILL_ACQUIRED_HIT);

  if(shadow_who->query_skill(M_SKILL_ACQUIRED_PEN) > iAcquiredPen)
      iAcquiredPen = shadow_who->query_skill(M_SKILL_ACQUIRED_PEN);

  m_adjust_acquired_weapon();

  // The acquired weapon hit and pen is decayed periodically.

  // set_alarm (60.0, 60.0, &m_decay_acquired_weapon ());
  set_alarm (60.0, 120.0, &m_decay_acquired_weapon ());
}

/*
 * Function:    m_set_acquired_karma
 * Description: This is used in debug/test code to set the karma
 *              appropriately.
 */
void m_set_acquired_karma(int hit, int pen)
{
    iAcquiredHit = hit;
    iAcquiredPen = pen;
    m_adjust_acquired_weapon();
}

//-------------------------------------------------------------------

