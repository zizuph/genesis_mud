/*
 * forms.c
 *
 * This file contains the emote-code for the different forms of
 * the different styles of the Blademasters, and is included in
 * the main blade_soul.c command soul in this directory. This file
 * will not load individually.
 *
 * Khail - April 15/97
 */

/*
 * Function name: do_form1
 * Description  : Allows the player to perform a sort of 'practice'
 *                kata with one one-handed weapon.
 * Arguments    : str - Arguments passed to the 'bform1' command.
 * Returns      : 0 - Do nothing.
 *                1 - Do emote.
 */
public int
do_form1(string str)
{
    object *weplist;
    string wepshort,
           poss,
           pro,
           obj;

    if (!str || !strlen(str) || str == "list")
    {
        write("Available forms for one weapon:\n" +
            "\t1: Viper Strikes From Den\n" +
            "\t2: Heron Blocks The Viper\n" +
            "\t3: Viper Coils\n" +
            "\t4: Heron Stands Ready\n" +
            "\t5: Heron Evades And Attacks\n" +
            "\t6: Viper Strikes Low\n" +
            "\t7: Heron Parts The Rushes\n" +
            "\t8: Viper Returns To Den\n");
        return 1;
    }

    if (TP->query_stat(SS_DEX) < FORM_DEX_MIN)
    {
        NF("You do not have the dexterity for the single one-handed " +
            "sword forms.\n");
        return 0;
    }

    weplist = filter(TP->query_weapon(-1), &operator(==)(W_SWORD) @
        &->query_wt());
    weplist = filter(weplist, &operator(!=)(W_BOTH) @ 
        &->query_hands());

    if (!sizeof(weplist))
    {
        NF("You'll need to wield a one-handed sword to perform this.\n");
        return 0;
    }

    wepshort = weplist[0]->short();

    poss = TP->query_possessive();
    pro = TP->query_pronoun();
    obj = TP->query_objective();

    if (str == "1" ||
        str == "viper strikes from den" ||
        str == "Viper Strikes From Den")
    {
        TP->catch_msg("Holding your " + wepshort + " by your side and " +
            "reversing your grip on it, you suddenly lash out with " +
            "it at your imagined target, in a move designed to block " +
            "an attack while clearing your blade from a scabbard.\n");
        allbb(" holds " + poss + " " + wepshort + " " + "at " + poss + 
            " side, reversing " + poss + " grip on its hilt. " + 
            capitalize(pro) + " suddenly lashes out with it at an " +
            "unseen target, as if drawing " + poss + " blade to " +
            "block an attack.");
    }

    else if (str == "2" ||
             str == "heron blocks the viper" ||
             str == "Heron Blocks The Viper")
    {
        TP->catch_msg("You sweep your " + wepshort + " in front of you, " +
            "downwards across your body as if diverting a " +
            "thrust, then raise it horizontally across your " +
            "brow, blocking an unseen overhead swing.\n");
        allbb(" sweeps " + poss + " " + wepshort + " in front of " +
            obj + ", downwards across " + poss + " body as if " +
            "diverting a thrust, then suddenly raises it " +
            "horizontally across his brow to block an unseen " +
            "chop.");
    }

    else if (str == "3" ||
             str == "viper coils" ||
             str == "Viper Coils")
    {
        TP->catch_msg("You crouch back into a low stance, with your " +
            wepshort + " drawn back beside your hip, blade " +
            "directed towards your imagined foe before you.\n");
        allbb(" crouches back into a low stance, with " + poss +
            " " + wepshort + " drawn back beside " + poss + " " +
            "hip, blade pointing in front of him.");
    }

    else if (str == "4" ||
             str == "heron stands ready" ||
             str == "Heron Stands Ready")
    {
        TP->catch_msg("You draw yourself backwards, your " + wepshort +
            " held ready behind your head, with the blade directed " +
            "forwards, beside your temple.\n");
        allbb(" draws " + obj + "self backwards, " + poss + " " +
            wepshort + " held ready behind " + poss + " head, " +
            "with the blade directed forwards, beside " + poss + 
            " temple.");
    }

    else if (str == "5" ||
             str == "heron evades and attacks" ||
             str == "Heron Evades And Attacks")
    {
        TP->catch_msg("You take a step backwards, slashing your " + wepshort +
            " downwards to block an imagined thrust, then spin " +
            "backwards around your right foot, thrusting your own " +
            "blade forward as your body recenters on your foe.\n");
        allbb(" takes a step backwards, slashing " + poss + " " +
            wepshort + " downwards as if blocking a thrust, then " +
            "spins backwards around " + poss + " right foot, " +
            "thrusting his blade forward as " + pro + " recenters " +
            obj + "self.");
    }

    else if (str == "6" ||
             str == "viper strikes low" ||
             str == "Viper Strikes Low")
    {
        TP->catch_msg("You duck low as if avoiding a slash, and leap " +
            "forward with your " + wepshort + " aimed forward, " +
            "thrusting beneath your foe's assault.\n");
        allbb(" ducks low as if avoiding a slash, and leaps " +
            "forward with " + poss + " " + wepshort + " aimed " +
            "forward, thrusting beneath the imagined attack.");
    }

    else if (str == "7" ||
             str == "heron parts the rushes" ||
             str == "Heron Parts The Rushes")
    {
        TP->catch_msg("You step forward, thrusting your " + wepshort +
            " before you, then twist the blade sharply as if " +
            "parrying and deflecting a thrust. You then spin " +
            "your blade back and slash downwards, then redirect " +
            "the blow sideways to clear the attacker.\n");
        allbb(" steps forward, thrusting " + poss + " " + wepshort +
            " before " + obj + ", then twists the blade sharply " +
            "as if parrying and deflecting an unseen thrust. " +
            capitalize(pro) + " then spins " + poss + " blade " +
            "back and slashes downwards over his head, abruptly " +
            "changing the direction of the slash to horizontal " +
            "in mid-blow, as if clearing away an unseen opponent.");
    }

    else if (str == "8" ||
             str == "viper returns to den" ||
             str == "Viper Returns To Den")
    {
        TP->catch_msg("You spin the " + wepshort + " in your hand, " +
            "reversing the grip and slip it to your side, " +
            "as if easing the blade back into a scabbard.\n");
        allbb(" spins " + poss + " " + wepshort + " in " +
            poss + " hand, reversing the grip and slips it " +
            "to " + poss + " side, as if easing the blade " +
            "back into a scabbard.");
    }
    else
    {
        write("No such form, " + str + ". Use 'bform1 list' " +
            "to see available one-handed forms.\n");
    }
    return 1;
}

/*
 * Function name: do_form2
 * Description  : Allows the player to perform a sort of 'practice'
 *                kata with 2 one-handed weapons.
 * Arguments    : str - Arguments passed to the 'bform2' command.
 * Returns      : 0 - Do nothing.
 *                1 - Do emote.
 */
public int
do_form2(string str)
{
    object *weplist;
    string wep1short,
           wep2short,
           poss,
           pro,
           obj;

    if (!str || !strlen(str) || str == "list")
    {
        write("Available forms for two weapons:\n" +
            "\t1: Dragon Stance\n" +
            "\t2: Tiger Faces Dragon\n" +
            "\t3: Dragon Coils\n" +
            "\t4: Tiger Evades The Dragon\n" +
            "\t5: Dragon Strikes The Tiger\n" +
            "\t6: Tiger Flanks The Dragon\n" +
            "\t7: Tiger Stalks The Dragon\n" +
            "\t8: Dragon Unleashes Fire\n");
        return 1;
    }

    if (TP->query_skill(SS_2H_COMBAT) < FORM_2H_MIN)
    {
        NF("You do not have the two-handed combat skill necessary " +
            "for the two-sword forms.\n");
        return 0;
    }

    weplist = filter(TP->query_weapon(-1), &operator(==)(W_SWORD) @
        &->query_wt());
    weplist = filter(weplist, &operator(!=)(W_BOTH) @ 
        &->query_hands());

    if (sizeof(weplist) != 2)
    {
        NF("You'll need to wield two one-handed swords to perform this.\n");
        return 0;
    }

    wep1short = TP->query_weapon(W_RIGHT)->short();
    wep2short = TP->query_weapon(W_LEFT)->short();
    poss = TP->query_possessive();
    pro = TP->query_pronoun();
    obj = TP->query_objective();

    if (str == "1" ||
        str == "dragon stance" ||
        str == "Dragon Stance")
    {
        TP->catch_msg("You step back with your right foot into a wide " +
            "stance, with your " + wep2short + " held low before " +
            "you in your left hand, between you and an unseen " +
            "enemy, and your " + wep1short + " held above your " +
            "head in your right hand, blade directed towards " +
            "the enemy.\n");
        allbb(" steps back with " + poss + " right foot into " +
            "a wide stance, with " + poss + " " + wep2short +
            " held low before " + obj + " in " + poss + " left " +
            "hand, and " + poss + " " + wep1short + " held above " +
            poss + " head in " + poss + " right hand, blade " +
            "directed in front of " + obj + ".");
    }

    else if (str == "2" ||
             str == "tiger faces dragon" ||
             str == "Tiger Faces Dragon")
    {
        TP->catch_msg("You cross your arms beneath one another, so that " +
            "the blades of your " + wep1short + " and " +
            wep2short + " touch behind your back. You lunge "+
            "forward at the imagined foe, simultaneously " +
            "slashing high with your " + wep1short + " and " +
            "low with your " + wep2short + ".\n");
        allbb(" crosses " + poss + " arms beneath one another, " +
           "the blades of " + poss + " " + wep1short + " and " +
           wep2short + " touching behind " + poss + " back. " +
           capitalize(pro) + " lunges forward, bringing " +
           poss + " blades forwards, simultaneously slashing " +
           "high with " + poss + " " + wep1short + " and low " +
           "with " + poss + " " + wep2short + ".");
    }

    else if (str == "3" ||
             str == "dragon coils" ||
             str == "Dragon Coils")
    {
        TP->catch_msg("You draw yourself up tall, raising both " +
            "blades to your head. The " + wep1short + " in " +
            "your right hand held behind your head, blade " +
            "directed forward, the " + wep2short + " in your " +
            "left hand held vertically against the outside " +
            "edge of the " + wep1short + ".\n");
        allbb(" draws " + obj + "self up tall, raising both " +
            "of " + poss + " blades to " + poss + " head. " +
            "The " + wep1short + " in " + poss + " right hand held " +
            "beside " + poss + " head, blade directed forward, " +
            "the " + wep2short + " in " + poss + " left hand " +
            "held vertically against the outside edge of the " +
            wep1short + ".");
    }

    else if (str == "4" ||
             str == "tiger evades the dragon" ||
             str == "Tiger Evades The Dragon")
    {
        TP->catch_msg("You execute an intricate series of tight " +
            "slashing motions, alternating between your " +
            wep1short + " and your " + wep2short + ", each " +
            "slash carrying the attacks of your imagined foe " +
            "further and further to one side.\n");
        allbb(" executes an intricate series of tight slashing " +
            "motions, alternating between " + poss + " " + wep1short +
            " and " + poss + " " + wep2short + ", as if driving " +
            "the attacks of an unseen opponent farther and farther " +
            "to one side.");
    }

    else if (str == "5" ||
             str == "dragon strikes the tiger" ||
             str == "Dragon Strikes The Tiger")
    {
        TP->catch_msg("You slip gracefully forwards, towards your " +
            "imagined foe, sweeping your " + wep2short + " in your " +
            "left hand low from left to right across his legs, " +
            "while at the same time spinning the " + wep1short + 
            " in your right hand high, and bring it down from right " +
            "to left in a diagonal slash across his chest.\n");
        allbb(" slips gracefully forwards, sweeping " + poss +
            " " + wep2short + " in " + poss + " left hand " +
            "low from left to right, while at the same time " +
            "the " + wep1short + " in " + poss + " right hand " +
            "spins in a tight circle, rising high then slashing " +
            "downwards from right to left diagonally at an " +
            "unseen target.");
    }

    else if (str == "6" ||
             str == "tiger flanks the dragon" ||
             str == "Tiger Flanks The Dragon")
    {
        TP->catch_msg("You slash the " + wep2short + " in your " +
            "left hand upwards in a curve towards an imagined " +
            "thrust at your chest, bringing up the " + wep1short +
            " in your right hand in a similar manner designed " +
            "to trap and break a blade. As your " + wep1short +
            " strikes home, you quickly spin backwards around " +
            "your right foot, recentering yourself on your " +
            "imagined opponent's left side.\n");
        allbb(" slashes the " + wep2short + " in " + poss + " " +
            "left hand upwards in a curve towards the air in " +
            "front of " + poss + " chest, bringing up the " +
            wep1short + " in " + poss + " right hand a fraction " +
            "of a second later. As the " + wep1short + " connects " +
            "with the " + wep2short + ", " + pro + " abruptly " +
            "spins backwards in a motion that would take " + obj +
            " from before an unseen enemy to the enemy's left " +
            "hand side.");
    }

    else if (str == "7" ||
             str == "tiger stalks the dragon" ||
             str == "Tiger Stalks The Dragon")
    {
        TP->catch_msg("You crouch low, and begin slowly " +
            "stepping sideways, circling your imagined foe. " +
            "As you step, you alternatingly flip your " +
            wep1short + " and " + wep2short + ", much in " +
            "the manner of a tiger's tail as he stalks his " +
            "prey.\n");
        allbb(" crouches low, and begins slowly stepping sideway, " +
            "as if circling an unseen opponent. " + capitalize(pro) +
            " spins " + poss + " " + wep1short + " and " + wep2short + 
            " alternatingly ever few seconds, and you're reminded " +
            "of a jungle cat's tail twitching as it stalks its " +
            "prey."); 
    }

    else if (str == "8" ||
             str == "dragon unleashes fire" ||
             str == "Dragon Unleashes Fire")
    {
        TP->catch_msg("You suddenly charge forwards at your " +
            "unseen foe, your " + wep1short + " and " + wep2short +
            " become a blur of steel as you swirl them before " +
            "you in overlapping figure-eights, and see the " + 
            "imagined attacks of your foe clashing helplessly " +
            "off of your onslaught until you strike the final " +
            "blow.\n");
         allbb(" suddenly charges forwards, " + poss + " " +
            wep1short + " and " + wep2short + " becoming blurs " +
            "of steel as they criss-cross each other in " +
            "whirling figure-eights before " + obj + ". You " +
            "suspect little could survive such an onslaught.");
    }
    else
    {
        write("No such form, " + str + ". Use 'bform2 list' " +
            "to see available two-weapon forms.\n");
    }
    return 1;
}

/*
 * Function name: do_form3
 * Description  : Allows the player to perform a sort of 'practice'
 *                kata with a two-handed sword.
 * Arguments    : str - Arguments passed to the 'bform3' command.
 * Returns      : 0 - Do nothing.
 *                1 - Do emote.
 */
public int
do_form3(string str)
{
    object *weplist;
    string wepshort,
           poss,
           pro,
           obj;

    if (!str || !strlen(str) || str == "list")
    {
        write("Available forms for a two-handed sword:\n" +
            "\t1: Wall Of Stone\n" +
            "\t2: Wind Clears The Ground\n" +
            "\t3: Crack Of Lightning\n" +
            "\t4: Wind Drives Stone\n" +
            "\t5: Water Cuts Through Earth\n" +
            "\t6: Rushing Water\n" +
            "\t7: Falling Of The Mountain\n" +
            "\t8: Shatter The Stone\n");
        return 1;
    }

    if (TP->query_stat(SS_STR) < FORM_STR_MIN)
    {
        NF("You are not strong enough for the two-handed sword " +
            "forms.\n");
        return 0;
    }

    weplist = filter(TP->query_weapon(-1), &operator(==)(W_SWORD) @
        &->query_wt());
    weplist = filter(weplist, &operator(==)(W_BOTH) @ 
        &->query_hands());

    if (!sizeof(weplist))
    {
        NF("You'll need to wield a two-handed sword to perform this.\n");
        return 0;
    }

    wepshort = weplist[0]->short();
    poss = TP->query_possessive();
    pro = TP->query_pronoun();
    obj = TP->query_objective();

    if (str == "1" ||
        str == "wall of stone" ||
        str == "Wall Of Stone")
    {
        TP->catch_msg("You brace your feet, and tense all of your " +
            "muscles, holding your " + wepshort + " vertically and " +
            "low in front of you, blocking all but the strongest " +
            "attacker's slashes.\n");
        allbb(" braces " + poss + " feet, and flexes all of " + poss +
            " muscles, holding " + poss + " " + wepshort + 
            " vertically and low in front of " + obj + ". " +
            capitalize(pro) + " appears as immobile as a wall, " +
            "and you doubt any attempt to knock the blade away " +
            "would succeed.");
    }

    else if (str == "2" ||
             str == "wind clears the ground" ||
             str == "Wind Clears The Ground")
    {
        TP->catch_msg("You swing your " + wepshort + " widely, " +
            "cutting a swath through the imagined enemies on "+
            "your right hand side, ending in a crouch. You quickly " +
            "reverse the crouch, swinging your blade vertically " +
            "over your head and down, completing the slash with " +
            "another swing to the opposite side, completing a full " +
            "circle.\n");
        allbb(" swings " + poss + " " + wepshort + " widely, " +
           "cutting a swath through anything that may have been on " +
           poss + " right hand side, ending in a crouch. " +
           capitalize(pro) + " quickly reverses the crouch to face " +
           "the other way, bringing the weapon up over " + poss + " " +
           "head and down in front of him, then completes the slash " +
           "with another swing to the opposite side, completing a " +
           "full circle, like a scythe through grass.");
    }

    else if (str == "3" ||
             str == "crack of lightning" ||
             str == "Crack Of Lightning")
    {
        TP->catch_msg("Tucking your " + wepshort + " in, you leap " +
            "into a forward roll, bowling beneath your imagined " +
            "enemies attack and knocking him to the ground. " +
            "Rising to your feet, you quickly reverse your grip " +
            "on your blade and slam it down through the prone " +
            "opponent's chest like a lightning strike.\n");
        allbb(" tucks " + poss + " " + wepshort + " in, and leaps " +
            "into a forward roll. Regaining " + poss + " feet, " +
            pro + " quickly reverses " + poss + " grip on the " +
            wepshort + " and slams it down into the ground at " +
            poss + " feet.");
    }

    else if (str == "4" ||
             str == "wind drives stone" ||
             str == "Wind Drives Stone")
    {
        TP->catch_msg("You deftly execute a forward roll with your " +
            wepshort + " tucked to one side, moving beneath your " +
            "imagined opponent's attack. As your roll ends, rather " +
            "than regain your footing, you use the momentum to " +
            "brutal slash across your opponent.\n");
        allbb(" deftly executes a forward roll with " + poss + " " +
            wepshort + " tucked to one side. As " + poss + " roll " +
            "ends, rather than regain " + poss + " footing, " + pro +
            " remains crouched, using the forward momentum to " +
            "add extra weight to a brutal slash at an unseen foe.");
    }

    else if (str == "5" ||
             str == "water cuts through earth" ||
             str == "Water Cuts Through Earth")
    {
        TP->catch_msg("You begin weaving your " + wepshort + " in " +
            "and out of unseen enemy attacks, calmly countering " +
            "or deflecting each slash and thrust, until you've " +
            "worked your blade into a position where your opponent " +
            "has dropped his guard, and drive the blade home " +
            "into his chest.\n");
        allbb(" begins weaving " + poss + " " + wepshort + " in " +
            "a tight pattern of blocks and parries, until suddenly " +
            "the tip of the blade is directly before where an " +
            "opponent's chest would be. " + capitalize(pro) + 
            " makes a single, brutal thrust, which would end the " +
            "fight.\n");
    }

    else if (str == "6" ||
             str == "rushing water" ||
             str == "Rushing Water")
    {
        TP->catch_msg("You begin slowly swirling your " + wepshort + 
            " into a figure eight before you, its long blade tracing " +
            "a shield before you almost twice as wide as you are " +
            "tall. You advance on your unseen enemy, and abruptly " +
            "change the hypnotic weave into a very fatal diagonal " +
            "slash across the enemy's throat.\n");
        allbb(" begins slowly swirling " + poss + " " + wepshort +
            " into a figure eight in the air before " + obj + ", its " +
            "long blade tracing an invisible shield almost twice as " +
            "wide as " + pro + " is tall. " + capitalize(pro) + " " +
            "advances on an unseen enemy, and abruptly the hypnotic " +
            "motion of " + poss + " " + wepshort + " becomes a " +
            "very fatal slash where an opponent's throat would be.");
    }

    else if (str == "7" ||
             str == "falling of the mountain" ||
             str == "Falling Of The Mountain")
    {
        TP->catch_msg("You begin a rapid advance, slashing your " +
            wepshort + " at your unseen enemy in brutal, simple chops " +
            "and slashes. Finally, you quickly spin to the outside, " +
            "and reverse your blade to slip beneath the enemy's " +
            "rib-cage as he starts to block the crude chop he " +
            "has come to expect.\n");
        allbb(" begins a rapid advance, slashing " + poss + " " +
            wepshort + " at an unseen enemy in brutal, simple chops " +
            "and slashes. Finally, " + pro + " quickly spins to the " +
            "outside, reversing " + poss + " grip on the blade, " +
            "and deftly slips it beneath what would be an opponent's " +
            "ribcage.");
    }

    else if (str == "8" ||
             str == "shatter the stone" ||
             str == "Shatter The Stone")
    {
        TP->catch_msg("You begin parrying your unseen ememy's " +
            "attacks with your " + wepshort + ". Following the " +
            "pattern, you wait for the proper moment, and then " +
            "drive the pommel of your sword against your foe's " +
            "breastplate, then bring the heavy blade crashing " +
            "down in a chop meant to destroy your foe's weapon, " +
            "rather than him.\n");
        allbb(" begins parrying unseen attacks calmy and deftly. " +
            "Soon, " + poss + " eyes harden on an imagined foe, " +
            " and " + pro + " reverses " + poss + " grip on " +
            poss + " " + wepshort + ", slamming its pommel towards " +
            "the unseen enemy's chest, then brings the heavy blade " +
            "down in a brutal, weapon-breaking chop.");
    }
    else
    {
        write("No such form, " + str + ". Use 'bform3 list' " +
            "to see available two-weapon forms.\n");
    }
    return 1;
}
