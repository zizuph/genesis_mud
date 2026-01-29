/*******************************************************************\
| SOUL_FORMS.H                                                      |
\*******************************************************************/

/*
 * 06/12/01 Arandir     Typo fix
 * 06/09/02 Arandir     Made the forms a bit simpler to finish
 * 06/08/27 Arandir     Separated the forms into skillclasses
 *                      Typo fix
 * 06/08/26 Arandir     Added the Memories form
 * 04/03/13 Arandir     Stop forms only when practiced
 * 04/03/06 Arandir     Double space typo
 * 04/01/21 Arandir     Added the Serpentine and Dragon Strike forms
 * 04/01/20 Arandir     Rewrote to better handle conditional movements
 *                      Added the Shields form
 * 04/01/08 Arandir     Fixed the race typo in Dragon Within
 * 03/10/14 Arandir     Added the Victorious form
 * 03/10/09 Arandir     Tuned the form success parameters
 * 03/10/08 Arandir     Added the Dragon Within form
 * 03/10/05 Arandir     Added the Birth form
 * 03/10/03 Arandir     Fixed a bug with set_skill
 * 03/09/28 Arandir     Added the Shadow of Wings form
 * 03/09/22 Arandir     Rewrote to drive forms using tables
 * 03/09/21 Arandir     Removed the use of the SAY macro
 * 03/07/08 Arandir     Rewrote to better handle multiple forms
 * 02/05/03 Arandir	Ported to new area without rewrite
 * ??/??/?? Cirion	Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

// The all function is not used because this_player is not set.

#define M_ALL(oWho,sStr)  tell_room (environment (oWho),QCTNAME (oWho) + " " + (sStr) + "\n", ({ oWho }))

//-------------------------------------------------------------------

/*******************************************************************\
| Form unspecific movements                                         |
\*******************************************************************/

int m_form_check_wears_robe (object oWho)
{
  return (objectp (oWho->query_armour (A_ROBE)));
}


int m_form_do_begin (object oWho)
{
  tell_object (oWho,
    "You begin to practice the physical forms of dragon " +
    "discipline, seeking the mind and body unity integral " +
    "to effective use of your combat moves.\n");

  return (FALSE);
}


int m_form_do_failure (object oWho)
{
  tell_object (oWho,
    "You attempt to perform the next step of the form but " +
    "fail. You will have to practice more to achieve the " +
    "mind and body unity integral to effective use of " +
    "your combat moves.\n");

  M_ALL (oWho,
    "suddenly stops in the middle of " + QPOS (oWho) + " combat movements.");

  return (FALSE);
}


int m_form_do_posture (object oWho)
{
  if (objectp (oWho->query_attack ()))
  {
    tell_object (oWho,
      "Your blood boils with the thrill of combat as you flow into the " +
      "movements that your teachers drilled into you. The long practice " +
      "takes over, making your movements silky smooth and dangerously " +
      "feral.\n");
  }
  else
  {
    tell_object (oWho,
      "You take a deep breath, and as you exhale you assume the " +
      "relaxed stance that your teachers drilled into you. Straight " +
      "and unrestrained, you are ready to move.\n");

     M_ALL (oWho,
       "breathes deeply and assumes a relaxed stance, ready to practice " + QPOS (oWho) + " combat movements.");
  }

  return (FALSE);
}


int m_form_do_bow (object oWho)
{
  if (objectp (oWho->query_attack ()))
  {
    tell_object (oWho, "You relax a little as the combat continues, staying poised and alert.\n");
  }
  else
  {
    oWho->command ("$mk bow");
  }

  return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Movements specific to Poised for Flight                           |
\*******************************************************************/

int m_form_do_wings_unfold (object oWho)
{
  tell_object (oWho,
    "Your mind wills your body to take the first of " +
    "the dragon forms, Poised for Flight. Your arms " +
    "seem to float upwards until they are stretched. " +
    "You feel the membranes of your wings unfold.\n");

  M_ALL (oWho,
    "raises " + QPOS (oWho) + " arms as though unfolding " + QPOS (oWho) + " wings.");

  return (FALSE);
}


int m_form_do_jump (object oWho)
{
  tell_object (oWho,
    "You swiftly flow into Dragon Launch, springing into " +
    "the air, pulling your arms in against your body and " +
    "then thrusting them forward and up, your taloned fingers " +
    "seeming to hold your arched body suspended above the " +
    "ground.\n");

  M_ALL (oWho,
    "launches into the air, defying gravity with fantastic ease.");

  return (FALSE);
}


int m_form_do_flight (object oWho)
{
  tell_object (oWho,
    "You are a dragon in flight, engaging its enemy in the " +
    "air, claws slashing and jaws striking, before wheeling " +
    "away, a cry of challenge trumpeting from your throat.\n");

  M_ALL (oWho,
    "whirls like a winged fury, hands and feet hammering the air.");

  oWho->command ("$mk kiai");

  return (FALSE);
}


int m_form_do_stance (object oWho)
{
  tell_object (oWho,
    "You land lightly on the balls of your feet and shift " +
    "to the Dragon Strike stance.\n");

  M_ALL (oWho,
    "lands in a crouch, then assumes a deceptively relaxed stance.");

  return (FALSE);
}


int m_form_do_lunge (object oWho)
{
  tell_object (oWho,
    "You lunge forward, the muscles in your extended arms rippling " +
    "with effort as your taloned fingers puncture the enemy's " +
    "armoured breast to rip out its heart.\n");

  M_ALL (oWho,
    "lunges forward, the muscles in " + QPOS (oWho) + " extended " +
    "arms rippling as " + QPNOUN (oWho) + " makes a quick, jabbing " +
    "motion with a taloned fist.");

  return (FALSE);
}


int m_form_do_flip (object oWho)
{
  tell_object (oWho,
    "Your blood sings a dragon song in your ears as you " +
    "effortlessly tumble in the air, flipping backwards to " +
    "land, catlike, on your feet.\n");

  M_ALL (oWho,
    "tumbles backwards in the air and lands, catlike, on " +
    QPOS (oWho) + " feet.");

  return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Movements specific to Shadow of Wings                             |
\*******************************************************************/

int m_form_do_shadow (object oWho)
{
  tell_object (oWho,
    "You kneel slowly on the ground, a knot of tension " +
    "ready to burst. With a smooth rise to a seemingly " +
    "unnatural height, you start performing Shadow of " +
    "Wings. Head raised, eyes intent, you feel the air " +
    "stir with the force of your massive wings unfolding.\n");

  M_ALL (oWho,
    "kneels down and smoothly rises again to a sudden gust of " +
    "wind, eerily reminiscent of " + QPOS (oWho) + " massive " +
    "wings unfolding.");

  return (FALSE);
}


int m_form_do_thrust (object oWho)
{
  tell_object (oWho,
    "A determined thrust forward initiates the form. You slide " +
    "forward, arm outstretched, the impact of your hand delivering " +
    "a solid crushing blow.\n");

  M_ALL (oWho,
    "thrusts forward with a crushing blow of " + QPOS (oWho) + " outstretched arm.");

  return (FALSE);
}


int m_form_do_sweep (object oWho)
{
  tell_object (oWho,
    "You swerve left, crouching down to avoid an attack. Your right " +
    "leg swings through an arched sweep of the ground, a powerful " +
    "dragon tail unbalancing an enemy.\n");

  M_ALL (oWho,
    "swerves left, crouching down with a powerful sweep of the ground.");

  return (FALSE);
}


int m_form_do_shield (object oWho)
{
  tell_object (oWho,
    "You rise again, left arm blocking, right following after in a " +
    "horizontal motion. As you take a short step backwards, you " +
    "pull your arms together in front of your chest.\n");

  M_ALL (oWho,
    "takes a short step backwards, arms blocking close to " + QPOS (oWho) + " chest.");

  return (FALSE);
}


int m_form_do_wings_strike (object oWho)
{
  tell_object (oWho,
    "In a powerful forward movement, you attack with the Slash " +
    "of Wings. Your arms flow wide and then back together, force " +
    "flowing from your entire body into your hands as they deliver " +
    "a fatal blow.\n");

  M_ALL (oWho,
    "strikes with " + QPOS (oWho) + " hands flowing wide and then back. " +
    "You have a sudden sense of being struck by a clap of air from large " +
    "beating wings, though you see nothing stir.");

  oWho->command ("$mk kiai");

  return (FALSE);
}


int m_form_do_fold (object oWho)
{
  tell_object (oWho,
    "A dragon settling down, you fold your arms on your chest " +
    "in a drawn motion. Slowly relaxing, you feel a sense of " +
    "heightened alertness permeating you.\n");

  M_ALL (oWho,
    "folds " + QPOS (oWho) + " arms slowly, as a dragon would fold " + QPOS (oWho) + " wings.");

  return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Movements specific to Birth                                       |
\*******************************************************************/

int m_form_do_egg_crouch (object oWho)
{
  tell_object (oWho,
    "Slowly yet smoothly, you lower yourself to the ground, " +
    "sitting cross-legged in an oval-shaped position. A moment " +
    "of suspense ends with a sudden burst of motion, as you roll " +
    "over your right shoulder in the first movement of Birth.\n");

  M_ALL (oWho,
    "lowers " + QOBJ (oWho) + "self to the ground, cross-legged in an " +
    "oval-shaped position. Suddenly, " + QPNOUN (oWho) + " tumbles over " +
    QPOS (oWho) + " right shoulder in an evasive movement.");

  return (FALSE);
}


int m_form_do_knee_break (object oWho)
{
  tell_object (oWho,
    "Roll after backroll and flip after flip, you move fast and low. " +
    "A quick sideroll changes into a devastating low kick at knee " +
    "height, a newborn dragon cracking a shell of its egg.\n");

  M_ALL (oWho,
    "changes a quick sideroll into a devastating low kick.");

  return (FALSE);
}


int m_form_do_burst_shell (object oWho)
{
  tell_object (oWho,
    "You halt your movement in a kneeling position, transferring your " +
    "momentum into a single powerful uppercut aimed at and through " +
    "your enemy's diaphragm. Your hand is a spear, a dragon horn " +
    "tearing remnants of its egg in a strife for freedom.\n");

  M_ALL (oWho,
    "flows into a kneeling position with a single powerful uppercut, " +
    "an image of a newborn dragon bursting through a shell of its " +
    "egg suddenly forming in your mind.");

  oWho->command ("$mk kiai");

  return (FALSE);
}


int m_form_do_first_flight (object oWho)
{
  tell_object (oWho,
    "You jump into the air with a trio of scythe-like kicks that " +
    "take you high up and back to the ground in a whirlwind of " +
    "attacks. A dragon child is come into the world.\n");

  M_ALL (oWho,
    "jumps into the air with a whirlwind of kicks, a dragon " +
    "child come into the world.");

  return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Movements specific to Dragon Within                               |
\*******************************************************************/

int m_form_do_soul_dive (object oWho)
{
  tell_object (oWho,
    "You close your eyes and cross your arms on your chest. Seeking " +
    "to free yourself from the disturbance of senses, you forget " +
    "the world of " + LANG_PWORD (oWho->query_race_name ()) + " and " +
    "dive deep into your soul where dwells the Dragon. Deeper " +
    "and deeper, your searching for the Dragon becomes the " +
    "Dragon searching for you, an outlet of life.\n");

  M_ALL (oWho,
    "concentrates with crossed arms, so still " + QPNOUN (oWho) + " seems lost to the world.");

  return (FALSE);
}


int m_form_do_soul_roar (object oWho)
{
  tell_object (oWho,
    "Golden haze envelops your sight, suddenly narrow and slitted as " +
    "if viewed by reptilian eyes. Your arms spread like wings, you " +
    "throw back your head and roar.\n");

  M_ALL (oWho,
    "spreads " + QPOS (oWho) + " arms wide and roars, the echo of " +
    "the cry reverberating through your surroundings.");

  return (FALSE);
}


int m_form_do_dragon_leap (object oWho)
{
  tell_object (oWho,
    "Suddenly, you are flying, the pitiful forces of nature that " +
    "bind " + LANG_PWORD (oWho->query_race_name ()) + " to the ground " +
    "left behind. You feel as light as a breeze, leaping and " +
    "spinning in the terrible Dance of the Dragon.\n");

  M_ALL (oWho,
    "leaps with amazing ease, " + QPOS (oWho) + " arms and legs " +
    "scything with deadly precision as " + QPNOUN (oWho) + " spins " +
    "and whirls with preternatural grace.");

  return (FALSE);
}


int m_form_do_dance_instinct (object oWho)
{
  tell_object (oWho,
    "Your hands and feet are claws, slashing through the air, silent " +
    "yet deadly. You move fast as thought, countless movements melting " +
    "into a single sequence, natural and instinctive as it wells up from " +
    "the depths of your soul.\n");

  M_ALL (oWho,
    "carves air with " + QPOS (oWho) + " hands and feet, each blow combining " +
    "terrifying power with icy control. The blows are free and fast, an " +
    "instinctive part of a beautiful and deadly dance.");

  return (FALSE);
}


int m_form_do_dance_climax (object oWho)
{
  tell_object (oWho,
    "Your dance grows ever faster, rising towards an ecstatic climax. " +
    "Your arms and legs blur as they cut through the air, the movements " +
    "coming together, reaching out towards one final effort. At last you " +
    "strike, both your physical strength and your mental focus flowing " +
    "into the attack.\n");

  M_ALL (oWho,
    "moves in a blur, reaching out towards one final effort. At last, " +
    QPNOUN (oWho) + " strikes, " + QPOS (oWho) + " body falling into " +
    "alignment behind the attack.");

  oWho->command ("$mk kiai");

  return (FALSE);
}


int m_form_do_soul_bleed (object oWho)
{
  tell_object (oWho,
    "As the Dance comes to an end, you feel the Dragon returning to " +
    "the depths of your soul. Your heart beats fast, full of joy as " +
    "the glorious roar of the Dragon still resonates though you.\n");

  M_ALL (oWho,
    "bears an expression of beatific joy on " + QPOS (oWho) + " face and " +
    "the light of victory in " + QPOS (oWho) + " eyes.");

  return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Movements specific to Victorious                                  |
\*******************************************************************/

int m_form_do_weave_pattern (object oWho)
{
  tell_object (oWho,
    "Eyes never leaving your opponent, your arms begin weaving " +
    "a mesmerizing pattern of block and parries. Slow and precise, " +
    "the motions suddenly erupt in a thunderous strike.\n");

  M_ALL (oWho,
    "weaves a mesmerizing pattern of blocks and parries with " +
    QPOS (oWho) + " arms, suddenly erupting in a thunderous strike.");

  return (FALSE);
}


int m_form_do_flying_kick (object oWho)
{
  tell_object (oWho,
    "Shifting all your weight to your back leg, you leap forward. " +
    "Your leading foot, a sharp talon, snaps in a flying front " +
    "kick into the chest of your opponent. Landing gracefully, " +
    "you crouch down, muscles tensed, waiting for the counter " +
    "strike.\n");

  M_ALL (oWho,
    "leaps forward in a flying front kick, landing gracefully in " +
    "a crouch and waiting for the counter strike.");

  return (FALSE);
}


int m_form_do_flowing_arch (object oWho)
{
  tell_object (oWho,
    "Your arms form a flowing arch as you quickly turn, guiding " +
    "a strike away from your body. Taking advantage of the momentum, " +
    "you form a solid barrier with one arm for the opponent to break " +
    "upon, the other arm readying for a strike.\n");

  M_ALL (oWho,
    "forms a flowing arch with " + QPOS (oWho) + " arms, guiding " +
    "strikes away from " + QPOS (oWho) + " body.");

  return (FALSE);
}


int m_form_do_shoulder_roll (object oWho)
{
  tell_object (oWho,
    "A quick shoulder roll brings you under your opponent's guard " +
    "with an incapacitating double strike to the head. With your " +
    "opponent momentarily stunned, you move away into a defensive " +
    "stance, inviting a graceful retreat.\n");

  M_ALL (oWho,
    "moves under " + QPOS (oWho) + " opponent's guard with a quick " +
    "shoulder roll and delivers an incapacitating double strike.");

  return (FALSE);
}


int m_form_do_trip_claw (object oWho)
{
  tell_object (oWho,
    "Using the momentum of the oncoming rush, you force your opponent " +
    "to the ground and follow with a savage Dragon Claw grasp of the " +
    "throat, compressing the windpipe. You feel calm and serene, " +
    "yet victorious.\n");

  M_ALL (oWho,
    "uses the momentum of the oncoming rush to force " + QPOS (oWho) + " opponent to the ground.");

  return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Movements specific to Shields                                     |
\*******************************************************************/

int m_form_check_wears_shields (object oWho)
{
  object oLeft, oRight;

  oLeft = oWho->query_armour (W_LEFT);
  oRight = oWho->query_armour (W_RIGHT);

  return ((oLeft && (oLeft->id ("shield"))) &&
          (oRight && (oRight->id ("shield"))));
}


int m_form_do_shields_spread (object oWho)
{
  if (m_form_check_wears_shields (oWho))
  {
    tell_object (oWho,
      "You cross your shielded arms on your chest and bow your head " +
      "momentarily. As you lift your stare, your arms spread outward " +
      "from your sides like enormous wings. Wisps of mist appear as " +
      "you stir the air.\n");

    M_ALL (oWho,
      "crosses " + QPOS (oWho) + " arms on " + QPOS (oWho) + " chest, " +
      QPOS (oWho) + " stare suddenly rising as the arms spread outward " +
      "again.");

    return (FALSE);
  }
  else
  {
    tell_object (oWho,
      "You cross your arms on your chest but then you realize that " +
      "shields are needed to continue this move.\n");

    M_ALL (oWho,
      "crosses " + QPOS (oWho) + " arms on " + QPOS (oWho) + " chest.");

    return (TRUE);
  }
}


int m_form_do_shielded_throat (object oWho)
{
  if (m_form_check_wears_shields (oWho))
  {
    tell_object (oWho,
      "A dragon shielded by its enormous wings, you pull your left arm " +
      "in. Suddenly, your right arm strikes at the throat of your " +
      "adversary with the edge of the shield.\n");

    M_ALL (oWho,
      "shields " + QOBJ (oWho) + "self with " + QPOS (oWho) + " left arm, " +
      "striking out with the shielded edge of " + QPOS (oWho) + " right arm.");

    return (FALSE);
  }
  else
  {
    tell_object (oWho,
      "You pull your left arm in in a protective gesture but then you " +
      "realize that shields are needed to continue this move.\n");

    M_ALL (oWho,
      "pulls " + QPOS (oWho) + " left arm in in a protective gesture.");

    return (TRUE);
  }
}


int m_form_do_shielded_plexus (object oWho)
{
  if (m_form_check_wears_shields (oWho))
  {
    tell_object (oWho,
      "You swerve and shift your shields to protect your right side, " +
      "simultaneously striking out to stun your adversary with a low " +
      "blow. With a graceful turn, you return to a shielded stance.\n");

    M_ALL (oWho,
      "swerves and shields " + QPOS (oWho) + " right side, striking " +
      "to stun simultaneously.");

    return (FALSE);
  }
  else
  {
    tell_object (oWho,
      "You pull your left arm in in a protective gesture but then you " +
      "realize that shields are needed to continue this move.\n");

    M_ALL (oWho,
      "pulls " + QPOS (oWho) + " left arm in in a protective gesture.");

    return (TRUE);
  }
}


int m_form_do_shielded_sweep (object oWho)
{
  if (m_form_check_wears_shields (oWho))
  {
    tell_object (oWho,
      "Secure within the wall of your shields, you brace to keep " +
      "your balance under the coming attacks. With a precise timing, " +
      "you move just when another attack commences, turning under the " +
      "shields and delivering a sweeping low kick.\n");

    M_ALL (oWho,
      "turns under " + QPOS (oWho) + " shields and delivers a sweeping " +
      "low kick.");

    return (FALSE);
  }
  else
  {
    tell_object (oWho,
      "You brace yourself to keep your balance but then realize you " +
      "need shields to continue this move.\n");

    M_ALL (oWho,
      "braces " + QOBJ (oWho) + "self to keep " + QPOS (oWho) + " balance.");

    return (TRUE);
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Movements specific to Serpentine                                  |
\*******************************************************************/

int m_form_do_serpent_sway (object oWho)
{
  tell_object (oWho,
    "Thinking on the legacy of the serpents deep in the bowels " +
    "of the earth, you breathe deeply. Focusing your thoughts to " +
    "touch the Serpent Within, you sway side to side, undulating " +
    "slowly, hypnotically, in a defensive stance that never stops " +
    "writhing.\n");

  M_ALL (oWho,
    "sways side to side in a defensive stance that never stops writhing.");

  return (FALSE);
}


int m_form_do_serpent_slide (object oWho)
{
  tell_object (oWho,
    "You feel like your skin is sparkling, the glow of your inner " +
    "strength reminiscent of a torchlight reflecting off the walls " +
    "of a deep cave rich with minerals and gemstones. Sliding across " +
    "the ground, you come right up and roll around your opponent.\n");

  M_ALL (oWho,
    "slides across the ground, coming right up and rolling around " +
    QPOS (oWho) + " opponent.");

  return (FALSE);
}


int m_form_do_claw_constrict (object oWho)
{
  tell_object (oWho,
    "Pulling your elbow back, you strike with an incredible force, " +
    "fingers extended in the Claw that Constricts. Hitting the " +
    "solar plexus of your opponent, you squeeze the air out.\n");

  M_ALL (oWho,
    "strikes with incredible force, fingers squeezing the air out of " +
    QPOS (oWho) + " opponent.");

  return (FALSE);
}


int m_form_do_stone_tail (object oWho)
{
  tell_object (oWho,
    "Sliding back, you drop to the ground on your hands. Whipping your " +
    "left leg, you sweep your foe's leg and follow quickly with the Tail " +
    "of Stone. Pushing your weight into the ground, you draw on its strength " +
    "to deliver a powerful kick at knee height.\n");

  M_ALL (oWho,
    "drops to the ground and whips " + QPOS (oWho) + " left leg, following " +
    "quickly with a powerful kick at knee height.");

  return (FALSE);
}


int m_form_do_fire_fist (object oWho)
{
  tell_object (oWho,
    "Rising up with a roar that sounds like a stone torn apart, you stand " +
    "at your full height. Eyes glowing with the fires of the world, you " +
    "put your fists one over the other. A predatorial smile crosses your " +
    "face as you channel your inner strength into the Dragon Fists of " +
    "Fire, double punching your opponent.\n");

  M_ALL (oWho,
    "rises with a roar. A predatorial smile crosses " + QPOS (oWho) + " face " +
    "as " + QPNOUN (oWho) + " punches " + QPOS (oWho) + " opponent with both fists.");

  oWho->command ("$mk kiai");

  return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Movements specific to Dragon Strike                               |
\*******************************************************************/

int m_form_do_slow_defence (object oWho)
{
  tell_object (oWho,
    "Slowly moving through a series of defensive postures, you focus " +
    "on the slow motion of your body, allowing your awareness to delve " +
    "deep into your being. Your movement has become your only focus. " +
    "The rythms of your body have become one with the patterns of your " +
    "thought. As a dragon in flight you are aware of all that surrounds " +
    "you.\n");

  M_ALL (oWho,
    "slows in " + QPOS (oWho) + " defensive movements.");

  return (FALSE);
}


int m_form_do_heel_kick (object oWho)
{
  if (objectp (oWho->query_attack ()))
  {
    tell_object (oWho,
      "In constant motion, but perfectly balanced, your movements are " +
      "fluid and graceful. You begin to shift your balance slightly as " +
      "you prepare to begin a new pattern. Without the briefest of pauses " +
      "you pivot on the ball of one foot, raising your leg and kicking " +
      "with your heel.\n");

    M_ALL (oWho,
      "pivots and flows fluidly into a kick with " + QPOS (oWho) + " heel.");
  }
  else
  {
    tell_object (oWho,
      "In constant motion, but perfectly balanced, your movements are " +
      "fluid and graceful. You begin to shift your balance slightly as " +
      "you prepare to begin a new pattern. Without the briefest of pauses " +
      "you pivot on the ball of one foot, slowly raising your leg and " +
      "pushing your heel outwards in a kick as far as it will reach.\n");

    M_ALL (oWho,
      "pivots and flows fluidly into a kick with " + QPOS (oWho) + " heel.");
  }

  return (FALSE);
}


int m_form_do_sense_oneness (object oWho)
{
  tell_object (oWho,
    "Movement and thought are one. Your awareness builds steadily as you begin to " +
    "experience only the moment. There is no past or future for you now. There is " +
    "no Time. You have become one with the Moment. You have found the essence of " +
    "your Soul.\n");

  M_ALL (oWho,
    "moves with a unique sense of oneness with " + QPOS (oWho) + " surroundings.");

  return (FALSE);
}


int m_form_do_sudden_lunge (object oWho)
{
  tell_object (oWho,
    "With a sudden lunge and blinding speed, you strike with an open hand. " +
    "Moving forward, your fists fly outwards with an inhuman force powering " +
    "them. Graceful and balanced, you strike out with a short quick kick. In " +
    "the same motion, you jump briefly into the air and lash out with the " +
    "other leg. There is no pause in your attack, no hesitation in your " +
    "movement.\n");

  M_ALL (oWho,
    "lunges with a blinding speed, striking with his " + QPOS (oWho) + " open " +
    "hand and following with two short quick kicks.");

  return (FALSE);
}


int m_form_do_crescent_kick (object oWho)
{
  tell_object (oWho,
    "Landing on the balls of your feet, you sweep your arms through " +
    "a defensive block, immediately attacking again with four quick " +
    "fist strikes. In one fluid motion, you drop to the ground " +
    "balanced on one foot. The other sweeps out in a crescent " +
    "as you rise again to continue your attack. You roar loudly " +
    "with the fury of a Dancer in rage.\n");

  M_ALL (oWho,
    "drops to the ground balanced on one foot, to rise with a crescent " +
    "kick and a chilling roar.");

  return (FALSE);
}


int m_form_do_bask_some (object oWho)
{
  tell_object (oWho,
    "You bask in the power you have unleased from your soul. Your senses " +
    "reach out around you and despite the whirlwind of your movements, " +
    "you are aware of each grain of sand beneath your feet and the breath " +
    "of even the smallest creature nearby. You are one with your Dragon " +
    "nature. You are alive.\n");

  M_ALL (oWho,
    "becomes one with the fight, reaching out with all senses, basking in the power unleashed.");

  return (FALSE);
}


int m_form_do_lethal_dance (object oWho)
{
  if (m_form_check_wears_robe (oWho))
  {
    tell_object (oWho,
      "The flurry of kicks and punches erases the difference between " +
      "one movement and the next, becoming a single lethal dance. " +
      "The dance climaxes as you launch youself into the air, whipping " +
      "your body around and lashing out with your leg. You land softly " +
      "on the balls of your feet, suddenly perfectly still, only your " +
      "robe whipping around you and then slowly unfurling, pausing, " +
      "sinking to the ground, all in one final graceful movement.\n");

    M_ALL (oWho,
      "punctuates " + QPOS (oWho) + " lethal dance with a flying " +
      "kick, landing into a standstill, " + QPOS (oWho) + " robe " +
      "whipping around and then slowly unfurling, pausing, " +
      "sinking to the ground, all in one graceful movement.");
  }
  else
  {
    tell_object (oWho,
      "The flurry of kicks and punches erases the difference between " +
      "one movement and the next, becoming a single lethal dance. " +
      "The dance climaxes as you launch youself into the air, whipping " +
      "your body around and lashing out with your leg. You land softly " +
      "on the balls of your feet, suddenly perfectly still.\n");

    M_ALL (oWho,
      "punctuates " + QPOS (oWho) + " lethal dance with a flying " +
      "kick, landing into a standstill.");
  }

  return (FALSE);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Movements specific to Memories                                    |
\*******************************************************************/

int m_form_do_old_greeting (object oWho)
{
  if (objectp (oWho->query_attack ()))
  {
    tell_object (oWho,
      "The experience of past encounters flood up to envelop you in a haze of " +
      "memories. The movements of your opponent merge with the recollection of " +
      "enemies that you have faced before, becoming like a familiar book reread a " +
      "thousand times.\n");

    M_ALL (oWho,
      "merges with the flow of combat as if " + QPNOUN (oWho) + " can see the blows before they land.");
  }
  else
  {
    tell_object (oWho,
      "You slowly fold your hands in front of your chest in a traditional " +
      "sign of greeting, remaining impassive for what seem to be several " +
      "seconds.\n");

    M_ALL (oWho,
      "slowly folds " + QPOS (oWho) + " hands in front of " + QPOS (oWho) + " chest " +
      "in a traditional sign of greeting, remaining impassive for what seem to be " +
      "several seconds.");
  }

  return (FALSE);
}


int m_form_do_invisible_stick (object oWho)
{
  if (m_form_check_wears_robe (oWho))
  {
    tell_object (oWho,
      "You whirl into motion, letting the folds of your robe obscure " +
      "a series of fast strikes, punctuated with a vicious stab " +
      "towards the ground.\n");

    M_ALL (oWho,
      "whirls into motion, letting the folds of " + QPOS (oWho) + " robe " +
      "obscure most of " + QPOS (oWho) + " movement, except for a vicious " +
      "stab towards the ground.");
  }
  else
  {
    tell_object (oWho,
      "You whirl into motion with a series of fast strikes, punctuated " +
      "with a vicious stab towards the ground.\n");

    M_ALL (oWho,
      "whirls into motion with a series of fast strikes, punctuated " +
      "with a vicious stab towards the ground.");
  }

  return (FALSE);
}


int m_form_do_stick_break (object oWho)
{
  if (objectp (oWho->query_attack ()))
  {
    tell_object (oWho,
      "With almost ceremonial perfection, you bring your hands " +
      "together in a strong grip and a twist, designed to free " +
      "yourself of your opponent.\n");

    M_ALL (oWho,
      "brings " + QPOS (oWho) + " hands together in a strong grip " +
      "and a twist to free " + QOBJ (oWho) + "self from " +
      QPOS (oWho) + " opponent.");
  }
  else
  {
    tell_object (oWho,
      "Reaching as if to grip a stick lodged in the ground, you " +
      "bring your hands together in a strong twist, dumping the " +
      "broken end of the stick on the ground with a ceremonious " +
      "gesture.\n");

    M_ALL (oWho,
      "reaches out, bringing " + QPOS (oWho) + " hands together in " +
      "a strong twist and then opening them in a strangely ceremonious " +
      "gesture.");
  }

  return (FALSE);
}


m_form_do_deep_trance (object oWho)
{
  tell_object (oWho,
    "Your lips move wordlessly, as if in a deep trance. Motionless " +
    "for a moment, your shadow appears to grow darker, as if light " +
    "was drawn towards your shrouded form.\n");

  M_ALL (oWho,
    "remains motionless for a moment, " + QPOS (oWho) + " lips moving " +
    "wordlessly as " + QPOS (oWho) + " shadow appears to grow darker.");

  return (FALSE);
}


m_form_do_spinning_kick (object oWho)
{
  tell_object (oWho,
    "Suddenly several steps away from your former position, you land " +
    "after delivering a jumping spinning axe kick, followed by a " +
    "series of punches in quick succession.\n");

  M_ALL (oWho,
    "is suddenly several steps away from " + QPOS (oWho) + " former " +
    "position, landing from what must have been a jumping spinning " +
    "axe kick.");

  return (FALSE);
}


m_form_do_fight_hydra (object oWho)
{
  tell_object (oWho,
    "You strike in so many directions you would defeat even a seven " +
    "headed hydra. The blur of your movements almost makes your " +
    "shadow disappear, as if you were giving off light.\n");

  M_ALL (oWho,
    "strikes in so many directions " + QPNOUN (oWho) + " would defeat " +
    "even a seven headed hydra. The blur of " + QPOS (oWho) + " movement " +
    "almost makes " + QPOS (oWho) + " shadow disappear.");

  return (FALSE);
}


m_form_do_chilling_roar (object oWho)
{
  tell_object (oWho,
    "You accompany your blow with a deep roar, not really loud " +
    "but chilling to the bone.\n");

  M_ALL (oWho,
    "accompanies " + QPOS (oWho) + " blow with a deep roar, not " +
    "really loud but chilling to the bone.");

  return (FALSE);
}


m_form_do_drooling_dragon (object oWho)
{
  if (objectp (oWho->query_attack ()))
  {
    tell_object (oWho,
      "You tease your opponent with a mischievous grimace of a very " +
      "cute but very deadly drooling dragon.\n");

    M_ALL (oWho,
      "grimaces in an imitation of a very cute but very deadly drooling dragon.");
  }
  else
  {
    tell_object (oWho,
      "You drop your arms to your sides and perform a bow, but cannot resist " +
      "adding a mischievous grimace of a very cute but very deadly drooling " +
      "dragon.\n");

    M_ALL (oWho,
      "drops " + QPOS (oWho) + " arms to " + QPOS (oWho) + " sides and " +
      "performs a bow. You glimpse " + QOBJ (oWho) + " grimacing in an " +
      "imitation of a very cute but very deadly drooling dragon.");
  }

  return (FALSE);
}

//-------------------------------------------------------------------

// Each form step is described by its function and difficulty.
// A multidimensional array is used to keep those.

#define M_STEPS_FUNCTION        0
#define M_STEPS_DIFFICULTY      1

#define M_STEP_DELAY            5.0


private static mixed *axFormPoisedForFlight =
({
  ({ m_form_do_posture,         TASK_SIMPLE }),
  ({ m_form_do_wings_unfold,    TASK_SIMPLE }),
  ({ m_form_do_jump,            TASK_ROUTINE }),
  ({ m_form_do_flight,          TASK_SIMPLE }),
  ({ m_form_do_stance,          TASK_SIMPLE }),
  ({ m_form_do_lunge,           TASK_HARD }),
  ({ m_form_do_flip,            TASK_HARD }),
  ({ m_form_do_bow,             TASK_SIMPLE })
});

private static mixed *axFormShadowOfWings =
({
  ({ m_form_do_posture,         TASK_SIMPLE }),
  ({ m_form_do_shadow,          TASK_ROUTINE }),
  ({ m_form_do_thrust,          TASK_HARD }),
  ({ m_form_do_sweep,           TASK_HARD }),
  ({ m_form_do_shield,          TASK_ROUTINE }),
  ({ m_form_do_wings_strike,    TASK_EXACTING }),
  ({ m_form_do_fold,            TASK_ROUTINE }),
  ({ m_form_do_bow,             TASK_SIMPLE })
});

private static mixed *axFormBirth =
({
  ({ m_form_do_posture,         TASK_SIMPLE }),
  ({ m_form_do_egg_crouch,      TASK_HARD }),
  ({ m_form_do_knee_break,      TASK_HARD }),
  ({ m_form_do_burst_shell,     TASK_EXACTING }),
  ({ m_form_do_first_flight,    TASK_HARD }),
  ({ m_form_do_bow,             TASK_SIMPLE })
});

private static mixed *axFormDragonWithin =
({
  ({ m_form_do_posture,         TASK_SIMPLE }),
  ({ m_form_do_soul_dive,       TASK_EXACTING }),
  ({ m_form_do_soul_roar,       TASK_HARD }),
  ({ m_form_do_dragon_leap,     TASK_ROUTINE }),
  ({ m_form_do_dance_instinct,  TASK_ROUTINE }),
  ({ m_form_do_dance_climax,    TASK_HARD }),
  ({ m_form_do_soul_bleed,      TASK_ROUTINE }),
  ({ m_form_do_bow,             TASK_SIMPLE })
});

private static mixed *axFormVictorious =
({
  ({ m_form_do_posture,         TASK_SIMPLE }),
  ({ m_form_do_weave_pattern,   TASK_ROUTINE }),
  ({ m_form_do_flying_kick,     TASK_ROUTINE }),
  ({ m_form_do_flowing_arch,    TASK_ROUTINE }),
  ({ m_form_do_shoulder_roll,   TASK_HARD }),
  ({ m_form_do_trip_claw,       TASK_HARD }),
  ({ m_form_do_bow,             TASK_SIMPLE })
});

private static mixed *axFormShields =
({
  ({ m_form_do_posture,         TASK_SIMPLE }),
  ({ m_form_do_shields_spread,  TASK_ROUTINE }),
  ({ m_form_do_shielded_throat, TASK_ROUTINE }),
  ({ m_form_do_shielded_plexus, TASK_ROUTINE }),
  ({ m_form_do_shielded_sweep,  TASK_HARD }),
  ({ m_form_do_bow,             TASK_SIMPLE })
});

private static mixed *axFormSerpentine =
({
  ({ m_form_do_posture,         TASK_SIMPLE }),
  ({ m_form_do_serpent_sway,    TASK_HARD }),
  ({ m_form_do_serpent_slide,   TASK_ROUTINE }),
  ({ m_form_do_claw_constrict,  TASK_ROUTINE }),
  ({ m_form_do_stone_tail,      TASK_HARD }),
  ({ m_form_do_fire_fist,       TASK_EXACTING }),
  ({ m_form_do_bow,             TASK_SIMPLE })
});

private static mixed *axFormDragonStrike =
({
  ({ m_form_do_posture,         TASK_SIMPLE }),
  ({ m_form_do_slow_defence,    TASK_EXACTING }),
  ({ m_form_do_heel_kick,       TASK_HARD }),
  ({ m_form_do_sense_oneness,   TASK_HARD }),
  ({ m_form_do_sudden_lunge,    TASK_EXACTING }),
  ({ m_form_do_crescent_kick,   TASK_HARD }),
  ({ m_form_do_bask_some,       TASK_HARD }),
  ({ m_form_do_lethal_dance,    TASK_EXACTING }),
  ({ m_form_do_bow,             TASK_SIMPLE })
});

private static mixed *axFormMemories =
({
  ({ m_form_do_posture,         TASK_SIMPLE }),
  ({ m_form_do_old_greeting,    TASK_ROUTINE }),
  ({ m_form_do_invisible_stick, TASK_DIFFICULT }),
  ({ m_form_do_stick_break,     TASK_DIFFICULT }),
  ({ m_form_do_deep_trance,     TASK_EXACTING }),
  ({ m_form_do_spinning_kick,   TASK_HARD }),
  ({ m_form_do_fight_hydra,     TASK_EXACTING }),
  ({ m_form_do_chilling_roar,   TASK_SIMPLE }),
  ({ m_form_do_drooling_dragon, TASK_SIMPLE })
});


// Besides here, a complete listing of all forms
// is also in the syntax description message !

private static mapping mFormSteps =
([
  "birth"               : axFormBirth,
  "dragon within"       : axFormDragonWithin,
  "dragon strike"       : axFormDragonStrike,
  "memories"            : axFormMemories,
  "poised for flight"   : axFormPoisedForFlight,
  "serpentine"          : axFormSerpentine,
  "shadow of wings"     : axFormShadowOfWings,
  "shields"             : axFormShields,
  "victorious"          : axFormVictorious
]);

// Note that there should always be one simpler
// form in each skillclass, else that skillclass
// cannot really be trained by forming.

// Note that there are hints relating forms to
// their skillclasses in the catacomb ring rooms.
// A change here necessitates a change there too ...

private static mapping mFormSkill =
([
  "birth"               : M_SKILL_FORMING_STICK,
  "dragon within"       : M_SKILL_FORMING_BLADE,
  "dragon strike"       : M_SKILL_FORMING_CLUB,
  "memories"            : M_SKILL_FORMING_STICK,
  "poised for flight"   : M_SKILL_FORMING_BLADE,
  "serpentine"          : M_SKILL_FORMING_CLUB,
  "shadow of wings"     : M_SKILL_FORMING_CLUB,
  "shields"             : M_SKILL_FORMING_BLADE,
  "victorious"          : M_SKILL_FORMING_STICK
]);

//-------------------------------------------------------------------

void m_form_step (object oWho)
{
  function fFunction;
  mixed    *axForm;
  mixed    *axStep;
  int      iSkill;
  int      iSkillAgainstOne;
  int      iSkillAgainstTwo;
  int      iAlarm;
  int      iFailure;

  axForm = oWho->query_prop (M_PROP_TMP_I_FORM_STEPS);
  iSkill = oWho->query_prop (M_PROP_TMP_I_FORM_SKILL);
  if (!axForm) return;

  axStep = axForm [0];
  axForm = axForm [1 ..];

  // The skills working against the form are always
  // the remaining two of the three form skills.

  switch (iSkill)
  {
    case M_SKILL_FORMING_CLUB:  iSkillAgainstOne = M_SKILL_FORMING_BLADE;
                                iSkillAgainstTwo = M_SKILL_FORMING_STICK;
                                break;
    case M_SKILL_FORMING_BLADE: iSkillAgainstOne = M_SKILL_FORMING_CLUB;
                                iSkillAgainstTwo = M_SKILL_FORMING_STICK;
                                break;
    case M_SKILL_FORMING_STICK: iSkillAgainstOne = M_SKILL_FORMING_CLUB;
                                iSkillAgainstTwo = M_SKILL_FORMING_BLADE;
                                break;
    default:                    s_log (M_LOG_DEBUG, "Invalid forming skill retrieved from a property.");
                                break;
  }

  // Performing a step of a form is a game of chance
  // with the relevant form skill and the unarmed
  // combat skill working in favor and the other
  // two form skills working against the step.

  // Since the relevant form skill is improved upon
  // successful completion of a form, this makes it
  // pretty much impossible to max more than one of
  // the three form skills.

  if (oWho->resolve_task (axStep [M_STEPS_DIFFICULTY],
                          ({ SKILL_WEIGHT, 500, iSkill,
                             SKILL_WEIGHT, 200, SS_UNARM_COMBAT }),
                          oWho,
                          ({ iSkillAgainstOne, iSkillAgainstTwo })) > 0)
  {
    fFunction = axStep [M_STEPS_FUNCTION];
    iFailure = fFunction (oWho);
  }
  else
  {
    m_form_do_failure (oWho);
    iFailure = TRUE;
  }

  if (!iFailure && (sizeof (axForm)))
  {
    iAlarm = set_alarm (M_STEP_DELAY, 0.0, &m_form_step (oWho));

    oWho->add_prop (M_PROP_TMP_I_FORM_ALARM, iAlarm);
    oWho->add_prop (M_PROP_TMP_I_FORM_STEPS, axForm);
  }
  else
  {
    oWho->remove_prop (M_PROP_TMP_I_FORM_ALARM);
    oWho->remove_prop (M_PROP_TMP_I_FORM_STEPS);

    if (!iFailure) oWho->set_skill (iSkill, MIN (M_SKILL_MAX_FORMING, oWho->query_skill (iSkill) + 1));
  }
}


int m_action_form (string sArgs)
{
  object oWho = this_player ();
  mixed  *axForm;
  int    iSkill;
  int    iAlarm;

  notify_fail ("Syntax: " + query_verb () + " <form>\n" +
               "  <form>             - the form to practice\n" +
               "Note: The forms are Birth, Dragon Within, Dragon Strike, Memories, Poised for Flight, Serpentine, Shadow of Wings, Shields, Victorious.\n");

  if (!strlen (sArgs)) return (FALSE);
  if (member_array (sArgs, m_indices (mFormSteps)) < 0) return (FALSE);

  axForm = mFormSteps [sArgs];
  iSkill = mFormSkill [sArgs];

  if (oWho->query_prop (M_PROP_TMP_I_FORM_ALARM))
  {
    write ("You are already practicing a form.\n");
  }
  else
  {
    iAlarm = set_alarm (M_STEP_DELAY, 0.0, &m_form_step (oWho));

    // We are in the soul, hence no global variables,
    // state must be passed in alarms or properties.

    oWho->add_prop (M_PROP_TMP_I_FORM_ALARM, iAlarm);
    oWho->add_prop (M_PROP_TMP_I_FORM_STEPS, axForm);
    oWho->add_prop (M_PROP_TMP_I_FORM_SKILL, iSkill);

    m_form_do_begin (oWho);
  }

  return (TRUE);
}


int m_action_stop (string sArgs)
{
  object oWho = this_player ();
  mixed  xAlarm;

  xAlarm = oWho->query_prop (M_PROP_TMP_I_FORM_ALARM);

  if (intp (xAlarm) && xAlarm)
  {
    remove_alarm (xAlarm);

    oWho->remove_prop (M_PROP_TMP_I_FORM_ALARM);
    oWho->remove_prop (M_PROP_TMP_I_FORM_STEPS);
    oWho->remove_prop (M_PROP_TMP_I_FORM_SKILL);

    write ("You stop practicing the physical forms of your dragon discipline.\n");
    M_ALL (oWho, "stops practicing " + QPOS (oWho) + " combat movements.");
  }
  else
  {
    write ("You are not practicing a form.\n");
  }

  return (TRUE);
}

//-------------------------------------------------------------------

