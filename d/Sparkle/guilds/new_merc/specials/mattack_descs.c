/*
 *  /d/Sparkle/guilds/new_merc/specials/mattack_descs.c
 *
 *  This file contains functions for the descriptions of the attacks
 *  for the mercenary guild special attack.
 *
 *  Created March 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <macros.h>
#include <wa_types.h>


/*
 * Function name:        nonlethal_descs
 * Description  :        Provide descriptions for those attacks that do
 *                       near-lethal damage, but do not kill
 * Arguments    :        object attacker - the one performing the attack
 *                       object victim   - the one being attacked
 *                       object wep      - the weapon we are using
 */
public void
nonlethal_descs(object attacker, object victim, object wep)
{
    string  cattacker = QCTNAME(attacker);
    string  tattacker = QTNAME(attacker);
    string  cvictim   = QCTNAME(victim);
    string  tvictim   = QTNAME(victim);
    string  his       = attacker->query_possessive();
    string  he        = attacker->query_pronoun();
    string  him       = attacker->query_objective();
    string  vhis      = victim->query_possessive();
    string  vhe       = victim->query_pronoun();
    string  vhim      = victim->query_objective();
    string  weapon    = wep->short();
    int     onehander = wep->query_hands() != W_BOTH;

    switch (wep->query_wt)
    {
    case W_AXE:
        if (onehander)
        {
            tell_room(environment(attacker),
                cattacker + " spins with a sudden deft maneuver, sinking"
              + " the blade of " + his + " " + weapon + " savagely into "
              + tvictim + "'s unguarded shoulder blade!\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Spinning in a sudden deft maneuver,"
              + " you sink your " + weapon + " savagely into "
              + tvictim + "'s shoulder blade!\n");
            victim->catch_tell("Spinning in a sudden deft maneuver, "
              + tattacker + " sinks " + his + " " + weapon + " savagely"
              + " into your shoulder blade. Incredible pain surges"
              + " through your body!\n");
        }
        else
        {
            tell_room(environment(attacker),
                "Heaving mightily, " + tattacker + " brings the blade of "
              + his + " " + weapon + " crashing down through "
              + tvictim + "'s defenses, burying the blade deep into "
              + tvictim + "'s exposed chest!\n",
               ({ attacker, victim }) );
            attacker->catch_tell("You heave mightily, bringing the"
              + " blade of your " + weapon + " crashing down through "
              + tvictim + "'s defenses to bury the blade deep into "
              + vhis + " exposed chest!\n");
            victim->catch_tell(cattacker + " heaves mightily, bringing"
              + " the blade of " + his + " " + weapon + " crashing"
              + " down through your unprepared defenses to sink with"
              + " horrifying pain into your exposed chest!\n");
        }
        break;
    case W_SWORD:
        if (onehander)
        {
            tell_room(environment(attacker),
                "Offering a quick feint, " + tattacker + " springs"
              + " deftly forward slicing a nasty gash in " + tvictim
              + "'s exposed belly with " + his + " " + weapon + "!\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Seeing an opening in " + tvictim 
              + "'s defences, you feint left and then spring quickly"
              + " forward slicing a nasty gash in " + tvictim + "'s"
              + " exposed belly with your " + weapon + "!\n");
            victim->catch_tell(cattacker + " feints to the right, and"
              + " then following the opening in your defenses as you"
              + " react, leapes forward, slicing a gash with " + his
              + " " + weapon + " in your exposed belly! Dreadful pain"
              + " washes over your entire body.\n");
        }
        else
        {
            tell_room(environment(attacker),
                "With sudden might and speed, " + tattacker + " lunges"
              + " forward with " + his + " " + weapon + ", penetrating "
              + tvictim + "'s defenses and plunging the point of the"
              + " blade deep into the flesh of " + vhis + " left"
              + " breast! " + cvictim + " staggers back, clutching"
              + " painfully at the wound.\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Gripping your " + weapon + " tightly,"
              + " you lunge forward with all of your mustered strength,"
              + " penetrating " + tvictim + "'s defenses, and plunging"
              + " the point of the blade deep into the flesh of "
              + vhis + " left breast! " + cvictim + " staggers back,"
              + " clutching painfully at the wound and staring at you"
              + " with surprise and anger.\n");
            victim->catch_tell("With surprising speed and force, "
              + tattacker + " lunges at you with the point of " + his
              + " " + weapon + ", plunging the blade into the flesh of"
              + " your left breast! Reeling in pain and anger, you "
              + "stagger back, clutching at the wound.\n");
        }
        break;
    case W_CLUB:
        if (onehander)
        {
            tell_room(environment(attacker),
                "Brandishing " + his + " " + weapon + " with a terrible"
              + " burst of speed, " + tattacker + " springs behind "
              + tvictim + ", smashing the weapon into " + vhis
              + " exposed back with tremendous force! " + cvictim
              + " sprawles upon the ground, and struggles painfully back"
              + " to " + vhis + " feet.\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Seizing on the opportunity of the"
              + " moment, you fling yourself around and behind "
              + tvictim + ", using the momentum of your movement to add"
              + " weight to your weapon hand. With a staggering blow,"
              + " you deliver the " + weapon + " directly to the small"
              + " of " + tvictim + "'s back, sending " + vhim
              + " sprawling in pain to the ground! Thrashing violently, "
              + vhe + " struggles back to " + vhis + " feet.\n");
            victim->catch_tell("In a surprising maneuver, "
              + tattacker + " flings " + him + "self around and behind"
              + " you to bring " + his + " " + weapon + " crashing into"
              + " the small of your back with hideous force! Your senses"
              + " explode with pain, and you find yourself sprawled on"
              + " the ground, clutching in every direction for support."
              + " You drag yourself back to your feet as quickly as you"
              + " are able.\n");
        }
        else
        {
            tell_room(environment(attacker),
                cvictim + " advances on " + tattacker + " in a sudden"
              + " rush. Countering the offensive, " + tattacker 
              + " spins, holding the " + weapon + " outward for momentum"
              + " and balance. With terrible impact, " + tvictim 
              + " charges with full force into the mallet of the"
              + " swinging " + weapon + ", which sends " + vhim 
              + " flying off " + vhis + " feet to land in a crumpled"
              + " heap a few yards back! " + cvictim + " staggers back"
              + " into the fray, dazed by the collision.\n",
               ({ attacker, victim }) );
            attacker->catch_tell(cvictim + " barrels blindly toward you"
              + " in a sudden rush. Anticipating the maneuver, you"
              + " sidestep and spin round with your " + weapon + " using"
              + " its centrifugal force for balance and power. "
              + tvictim + " collides headlong with the mallet of your"
              + " weapon, and is lifted off " + vhis + " feet by the force"
              + " of the impact, which sends " + vhim + " sailing"
              + " backwards to land painfully on " + vhis + " back a"
              + " few yards away! Staggering back up, " + vhe + " slowly"
              + " readvances into combat, dazed by the incident.\n");
            victim->catch_tell("With a sudden vigor, you rush confidently"
              + " towards " + tattacker + ", who sidesteps your attack,"
              + " and spins " + his + " " + weapon + " round. To your"
              + " dismay, and with unbelievable impact, you collide"
              + " headlong with the mallet of the " + weapon + ", the"
              + " force of which lifts you off your feet and sends you"
              + " flying backward to land painfully on the ground a few"
              + " yards back! Angry and flustered, you jump up and"
              + " advance warily to face your opponent again.\n");
        }
        break;
    case W_KNIFE:
        tell_room(environment(attacker),
            "With cat-like speed, " + tattacker + " leaps past " 
          + tvictim + "'s defenses, and plunges " + his + " " + weapon
          + " deep into the meat of " + vhis + " underarm! Flinching"
          + " backwards, " + tvictim + " cradles the wound, glaring at " 
          + tattacker + " in surprise and pain.\n",
               ({ attacker, victim }) );
        attacker->catch_tell("Seeing an opening in " + tvictim + "'s"
          + " defences, you stab forward with all of your might,"
          + " plunging your " + weapon + " deep into the meat of "
          + vhis + " underarm! Flinching in pain, " + tvictim
          + " staggers backward, cradling the wound, and glaring at"
          + " you in surprise and anger.\n");
            victim->catch_tell("Judging a weakness in your stance, " 
          + tattacker + " stabs suddenly towards your heart. You"
          + " instinctively flinch, but only in time to save your very"
          + " life, as the " + weapon + " plunges deeply into the meat of"
          + " your underarm! Staggering backward in pain, you glare with"
          + " hatred at " + tvictim + " and nurse your painful wound.\n");
        break;
    case W_POLEARM:
        tell_room(environment(attacker),
            "Lunging forward with sudden speed and dexterity, "
          + tattacker + " forces " + his + " " + weapon + " through "
          + tvictim + "'s defences, plunging the weapon deeply into the"
          + " flesh of " + vhis + " shoulder! " + cvictim + " falls"
          + " backwards, and rolls to " + vhis + " feet, clutching at"
          + " the wound in pain.\n",
               ({ attacker, victim }) );
        attacker->catch_tell("Noticing a mistake in " + tvictim + "'s"
          + " stance, you lunge forward with all of your mustered speed"
          + " and strength, thrusting your " + weapon + "deeply into the"
          + " flesh of " + his + " shoulder! The force of the blow"
          + " knocks " + vhim + " backwards. Quickly rolling back to "
          + vhis + " feet, " + vhe + " winces in pain, clutching at the"
          + " wound.\n");
        victim->catch_tell(cattacker + " lunges suddenly toward you,"
          + " thrusting his " + weapon + " with alarming speed and"
          + " dexterity. Attempting to avoid the blade, the best you are"
          + " able to do is to twist your heart out of the way of the"
          + " blade, which plunges painfully into your shoulder! Falling"
          + " backwards, you quickly roll to your feet, clutching at the"
          + " terrible pain in your cut flesh.\n");
        break;
    default: /* unarmed */
        tell_room(environment(attacker),
             cattacker + " grabs " + tvictim + " by the skull, dragging "
           + vhis + " head downward just in time to receive a swift and"
           + " devastating knee to the face! Dazzled by pain and"
           + " surprise, " + tvictim + " tumbles backward covering "
           + vhis + " wounded mouth with " + vhis + " arm.\n",
               ({ attacker, victim }) );
        attacker->catch_tell("Anger takes you suddenly, and you grab "
           + tvictim + "'s skull with both of your hands, dragging "
           + vhis + " head downward as you bring your leg up to deliver"
           + " a devastating knee into " + vhis + " face! Tumbling back"
           + " from you in pain and disbelief, " + tvictim + " covers "
           + vhis + " wounded mouth with " + vhis + " arm.\n");
        victim->catch_tell("To your complete surprise, " + tattacker
           + " grabs you suddenly by the back of the skull, and drags"
           + " your head downward to deliver a devastating knee right to"
           + " your face! The world disappears for a moment, as you"
           + " tumble backward, blinded by pain and dazzling lights.\n");
        break;
    }
} /* nonlethal_descs */


/*
 * Function name:        lethal_descs
 * Description  :        Provide descriptions for those attacks that do
 *                       killing damage to the victim
 * Arguments    :        object attacker - the one performing the attack
 *                       object victim   - the one being attacked
 *                       object wep      - the weapon we are using
 */
public void
lethal_descs(object attacker, object victim, object wep)
{
    string  cattacker = QCTNAME(attacker);
    string  tattacker = QTNAME(attacker);
    string  cvictim   = QCTNAME(victim);
    string  tvictim   = QTNAME(victim);
    string  his       = attacker->query_possessive();
    string  he        = attacker->query_pronoun();
    string  him       = attacker->query_objective();
    string  vhis      = victim->query_possessive();
    string  vhe       = victim->query_pronoun();
    string  vhim      = victim->query_objective();
    string  weapon    = wep->short();
    int     onehander = wep->query_hands() != W_BOTH;

    switch (wep->query_wt)
    {
    case W_AXE:
        if (onehander)
        {
            tell_room(environment(attacker),
                "Crouching low, " + tattacker + " springs up suddenly,"
              + " and with terrible speed sends the blade of " + his
              + " " + weapon + " slicing through " + tvictim + "'s"
              + " neck! Staggering backwards, " + tvictim + "'s"
              + " lifeless body falls limply to the ground, the head"
              + " coming apart from the shoulders as it lands.\n",
               ({ attacker, victim }) );
            attacker->catch_tell("You crouch low, and then with great"
              + " exertion spring upwards, swinging your weapon hand with"
              + " all your mustered strength in a wide arcing motion"
              + " towards " + tvictim + "'s neck. Connecting true, the "
              + weapon + "'s blade passes cleanly through flesh and"
              + " bone, and " + tvictim + " staggers back, falling"
              + " headless to the ground at your feet!\n");
            victim->catch_tell(cattacker + " crouches suddenly low, and"
              + " then springs upward with horrible strength and speed,"
              + " swinging " + his + " " + weapon + " toward your neck"
              + " before you can prepare any defense! Pain dazzles your"
              + " senses for the briefest instant, and then, as if from"
              + " above, you see your headless body hit the ground.\n");
        }
        else
        {
            tell_room(environment(attacker),
                "With furious strength, " + tattacker + " raises " + his
              + " " + weapon + " high, bursting toward " + tvictim 
              + " with a shout of wrath. The weapon crashes down upon " 
              + tvictim + "'s brow with a sickening crack, driving the"
              + " cloven skull downward as the heavy weapon grinds to a"
              + " halt on the ground! " + cattacker + " pulls the"
              + " blade of the " + weapon + " from the twisted and"
              + " lifeless body.\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Filled with a sudden wrath, you charge"
              + " at " + tvictim + " with your " + weapon + " held high"
              + " above your head. Your blind fury unleashes itself as"
              + " the weapon comes crashing down upon " + tvictim + "'s"
              + " head, cleaving the skull in two, and driving it to the"
              + " ground with the force of your blow! With a grunt of"
              + " satisfaction, you pull the blade from the now lifeless"
              + " body.\n");
            victim->catch_tell("With a sudden howl of wrath, "
              + tattacker + " rushes toward you, " + weapon + " held"
              + " high. Caught off guard, and staggering backward, you"
              + " bring your defenses up too late, as the deadly blade"
              + " comes crashing down toward your face! A splitting rush"
              + " of pain sends you spinning into darkness, and you"
              + " remember nothing more.\n");
        }
        break;
    case W_SWORD:
        if (onehander)
        {
            tell_room(environment(attacker),
                "Bursting through " + tvictim + "'s defences, " 
              + tattacker + " drives the point of " + his + " " 
              + weapon + " deep into " + tvictim + "'s belly, ramming"
              + " the blade clean through " + vhis + " torso to emerge"
              + " bloodied from from the other side! The two opponents"
              + " remain locked for a moment in a deadly embrace, and"
              + " then " + tvictim + "'s eyes glaze over, and " + vhe 
              + " slumps lifelessly to the ground, sliding off of " 
              + tattacker + "'s blade to fall upon " + vhis + " side.\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Mustering all your skill and strength,"
              + " you burst through " + tvictim + "'s defenses and drive"
              + " the point of your " + weapon + " deep into " + vhis 
              + " belly, ramming the blade clean through " + vhis 
              + " torso to emerge bloodied from the other side! Locked"
              + " face to face with you, a look of rage, and then of"
              + " sorrow, and then of death passes through " + tvictim
              + "'s eyes, who slides at last off of your blade to slump"
              + " lifeless to the ground at your feet.\n");
            victim->catch_tell(cattacker + " bursts suddenly through your"
              + " defenses, driving the point of " + his + " " + weapon
              + " deep into your belly! A sharp and freezing pain washes"
              + " over you as you feel the blade emerge from the flesh of"
              + " your back, having run clean through your torso. Locked"
              + " face to face with " + tattacker + " you glare defiantly"
              + " into " + his + " eyes, only to be overcome with memories"
              + " from your past as the world begins to fade. The last"
              + " thing you remember is pity in the eyes of your slayer"
              + " as " + he + " releases you from " + his + " grasp.\n");
        }
        else
        {
            tell_room(environment(attacker),
                "Moving with great breadth and power, " + tattacker 
              + " twirls " + his + " " + weapon + " above " + his 
              + " head, spinning with its momentum in a devastating arc"
              + " towards the neck of " + tvictim + ". Finding its mark,"
              + " the blade passes through sinew and bone, beheading "
              + tvictim + " where " + vhe + " stands!\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Filled with a sudden inspiration of"
              + " prowess, you twirl your " + weapon + " above your head,"
              + " regripping it tightly as it fits once again into your"
              + " palms. Following its momentum, you spin with deft power"
              + " and balance aiming the blade at " + tvictim + "'s neck."
              + " Unable to react in time, " + tvictim + " stands like"
              + " a statue as the " + weapon + " severs sinew and bone,"
              + " behedding " + vhim + " where " + vhe + " stands!\n");
            victim->catch_tell("In a dazzling display of swordsmanship, "
              + tattacker + " twirls " + his + " " + weapon + " above "
              + his + " head, spinning with confusing motion to follow"
              + " the momentum of the blade as it travels around on your"
              + " left. Bewildered, you discover that the blade has"
              + " traveled fast, too fast, and now comes with all its"
              + " speed and power on your right aimed precisely at your"
              + " undefended neck! You stiffen as the " + weapon 
              + " connects, feeling only an instant of pain before all"
              + " goes black.\n");
        }
        break;
    case W_CLUB:
        if (onehander)
        {
            tell_room(environment(attacker),
                "With a cry of rage, " + tattacker + " spins with blinding"
              + " speed, throwing " + his + " weapon arm out in a flash"
              + " of deadly force which connects squarely with the side"
              + " of " + tvictim + "'s head! With a sickening crack, " 
              + tvictim + " topples to the ground, " + vhis + " neck bent"
              + " at an impossible angle, and lies dead at " + tattacker
              + "'s feet.\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Rage fills your throat, and with a"
              + " sudden burst of skill and power, you spin with blinding"
              + " speed, throwing your weapon arm out in a flash of"
              + " deadly force which connects squarely with the side of "
              + tvictim + "'s head! No match for your " + weapon + ", "
              + tvictim + "'s neck snaps sideways with a sickening crack,"
              + " bent at an impossible angle. Toppling, it is obvious"
              + " that " + vhe + " is dead before " + vhe + " hits the"
              + " ground.\n");
            victim->catch_tell(cattacker + " lets fly a sudden cry of"
              + " rage, and spins with blinding speed, sending " + his
              + " " + weapon + " hurtling toward your head with deadly"
              + " force! Sound and pain are cut off in an instant as"
              + " blackness covers your eyes.\n");
        }
        else
        {
            tell_room(environment(attacker),
                "In a dazzling display of beastly strength, "
              + tattacker + " rears up, bringing " + his + " " + weapon
              + " down upon " + tvictim + " with the speed and power"
              + " of an avalanche. Unslowed in its descent, the weapon"
              + " drives downward, carrying flesh and bone with it,"
              + " breaking the body of " + tvictim + " like a dry barrel"
              + " upon the ground!\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Brimming with sudden and terrible"
              + " wrath, you rear up, brandishing your " + weapon
              + " with beastial strength. With the speed and power of an"
              + " avalanche, you bring the weapon down upon " + tvictim 
              + ". Unslowed in its descent, the " + weapon + " drives"
              + " downward, carrying flesh and bone with it, breaking"
              + " the body of " + tvictim + " like a dry barrel upon the"
              + " ground at your feet!\n");
            victim->catch_tell("To your horror, " + tattacker + " rears"
              + " up in a dazzling display of beastial strength,"
              + " brandishing " + his + " " + weapon + " with great"
              + " ferocity above you! As the weapon comes down, it is as"
              + " if you are caught beneath a mighty avalanche, your"
              + " flesh and bones being driven to the ground, breaking"
              + " as if made of brittle wood. Excruciating pain ravages"
              + " your ruined body, and then slowly fades as your life"
              + " slips away.\n");
        }
        break;
    case W_KNIFE:
        tell_room(environment(attacker),
            "Twisting " + his + " way inside " + tvictim + "'s defences, "
          + tattacker + " rams " + his + " " + weapon + " up beneath "
          + tvictim + "'s chin, burying the weapon deeply in the flesh of"
          + " the throat! Clutching desperately at the wound, " + tvictim
          + " falls to the ground and soon ceases all movement.\n",
               ({ attacker, victim }) );
        attacker->catch_tell("With uncharacteristic skill and speed, you"
          + " thrust yourself inside " + victim + "'s defenses, and stab"
          + " immediately upward, burying your " + weapon + " into the"
          + " soft flesh of " + vhis + " throat! Clutching desperately at"
          + " the wound with spasms of pain, " + tvictim + " falls to the"
          + " ground, where " + vhe + " quickly falls still.\n");
        victim->catch_tell("To your amazement, you find that "
          + tattacker + " dashes within your defences, brandishing " 
          + his + " deadly " + weapon + ". Before you can react,"
          + " horrifying pain stabs into your mind as you feel the weapon"
          + " being stabbed deeply into the flesh of your throat! Choking"
          + " with terror and dismay, you collapse to the ground,"
          + " desperately attempting to remove the weapon. Slowly, the"
          + " world fades to black.\n");
        break;
    case W_POLEARM:
        tell_room(environment(attacker),
            "With ferocious strength and terrifying speed, " + tattacker
          + " runs and leaps toward " + tvictim + ", sailing through the"
          + " air with " + his + " " + weapon + " pointed downward for"
          + " the kill. Unable to counter the move, " + tvictim
          + " gives out a yelp of dismay before the onslaught, and is"
          + " struck through the chest by the blade, which pins " + vhis
          + " dying body to the ground!\n",
               ({ attacker, victim }) );
        attacker->catch_tell("Feeling the lust of battle rise, you dash"
          + " forward, leaping high in the air above " + tvictim + " with"
          + " your " + weapon + " pointed directly at " + vhis + " heart."
          + " Sensing " + vhis + " doom, " + tvictim + " yelps in dismay"
          + " before being pinned to the ground by your blade, which runs "
          + vhim + " cleanly through the chest!\n");
            victim->catch_tell(cattacker + " runs at you suddenly, leaping"
          + " high in the air above your head and descending with " + his
          + " " + weapon + " pointed directly at your unguarded frame!"
          + " In terror and dismay, you yelp and attempt to flinch away"
          + " from the danger, but the blade comes too fast, piercing your"
          + " chest and forcing you to the ground where you are pinned."
          + " Pain overcomes you, and death follows quickly.\n");
        break;
    default:
        tell_room(environment(attacker),
            cattacker + " spins swiftly to the side of " + tvictim 
          + ", bringing " + his + " arm flailing sidelong for a"
          + " devastating chop directly to " + tvictim + "'s exposed"
          + " throat! Clutching wildly at " + vhis + " neck, " + tvictim
          + " drops immediately to " + vhis + " knees, choking and unable"
          + " to draw a breath. As " + vhe + " struggles more and more"
          + " desperately, the color of " + vhis + " face darkens,"
          + " finally flushing a deep red as " + he + " falls forward"
          + " onto " + vhis + " belly and lies still.\n",
               ({ attacker, victim }) );
        attacker->catch_tell("Judging your opponent carefully, you"
          + " spin swiftly to " + tvictim + "'s side, throwing your arm in"
          + " for a devastating chop to " + vhis + " exposed throat!"
          + " Clutching wildly at " + vhis + " neck, " + tvictim + " drops"
          + " immediately to " + vhis + " knees, choking and unable to"
          + " draw a breath. As " + vhe + " struggles more and more"
          + " desperately, the color of " + vhis + " face darkens, finally"
          + " flushing a deep red as " + vhe + " falls forward onto " 
          + vhis + " belly and lies still.\n");
        victim->catch_tell("Spinning swiftly to your side, " + tattacker
          + " throws an arm outwards, bringing it towards you with"
          + " blinding speed for a devastating chop to your exposed"
          + " throat! You feel your larynx crushed by the blow, and drop"
          + " to your knees, overcome with pain and the need to draw a"
          + " breath! Unable to get any air, you struggle in vain for"
          + " life, which slips agonizingly away.\n");
        break;
    }
} /* lethal_descs */
