/*
 * emotes.c
 *
 * Included in the soul. The emotes for the Anghoth of Mordor club.
 *
 *   Alto, 01 June 2002
 *
 */

#include "battlesong.h"

/* Function name: agbattlesong
 * Description  : Anghoth emote to sing morgul battlesongs.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agbattlesong(string str)
{
    int     verse = 0;
    string  song;

    NF("You do not know any battle song of that name!\n");

    if (strlen(str))
    {
        if (sscanf(str, "%d", verse) == 1)
        {
            if (verse <= 0)
                return 0;
            else if (verse > sizeof(BATTLE_SONG))
            {
                NF("You do not know verse number "+LANG_WNUM(verse)+".\n");
                return 0;
            }
            song = BATTLE_SONG[verse-1];
        }
        else
        return 0;
    }
    else
    song = ONE_OF_LIST(BATTLE_SONG);

    all(" sings in a booming sinister voice a battle song of Mordor:");
    write("You sing one verse of the battle song of Mordor:\n");
    tell_room(ENV(TP),"\n"+song+"\n");
    return 1;
}


/* Function name: agwarn
 * Description  : Anghoth emote to warn others.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agwarn(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You sternly warn all present that you will not tolerate "
            + "insults to your Lord.\n");
        all(" warns all present that " + PRONOUN(TP) + " will not "
            + "tolerate "
            + "insults to " + POSSESSIVE(TP) + " Lord.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Warn who?");
    }

    actor("You sternly warn", oblist, " that you will not tolerate such "
        + "insults to your Lord.");
    target(" sternly warns you that " + PRONOUN(TP) + " will not "
        + "tolerate "
        + "such insults to " + POSSESSIVE(TP) + " Lord.", oblist);
    all2act(" sternly warns", oblist, " that " + PRONOUN(TP) + " will not "
        + "tolerate such insults to " + POSSESSIVE(TP) + " Lord.");
    return 1;
}

/* Function name: agwarn2
 * Description  : Anghoth emote to warn others.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agwarn2(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You sternly warn all present that any further disrespect to "
            + "your Lord will ultimately end in dire consequences.\n");
        all(" warns all present that any further disrespect to " 
            + POSSESSIVE(TP) + " Lord will ultimately end in "
            + "dire consequences.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Warn who?");
    }

    actor("You let", oblist, " know that any further disrespect to your "
        + "Lord will result in swift retribution.");
    target(" lets you know that any further disrespect to " 
        + POSSESSIVE(TP) 
        + " Lord will ultimately lead to your demise.", oblist);
    all2act(" lets", oblist, " know that any further disrespect to " 
        + POSSESSIVE(TP) + " Lord will ultimately lead to swift retribution.");
    return 1;
}

/* Function name: aglook
 * Description  : Anghoth emote to demonstrate allegiance to Morgul.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
aglook(string str)
{
    write("You look wistfully to the East remembering that your "
        + "allegiance will always be with Mordor.\n");
    all(" looks wistfully to the East in declaration of "
        + POSSESSIVE(TP) + " allegiance to Mordor.");
    return 1;
}

/* Function name: aggrovel
 * Description  : Anghoth emote to grovel before a mage.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
aggrovel(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You grovel on the ground in a pitiful show of obeisance "
            + "to Minas Morgul.\n");
        all(" grovels on the ground in a pitiful show of obeisance to "
            + "Minas Morgul.");
        return 1;
    }

    oblist = parse_this(str, "[before] [the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Grovel before who?");
    }

    actor("You grovel before", oblist, " pitifully showing your obeisance "
        + "to Minas Morgul.");
    target(" grovels before you, pitifully declaring " + POSSESSIVE(TP) 
        + " obeisance to the designs of the Dark Lord.", oblist);
    all2act(" grovels before", oblist, ", a pitiful reminder of " 
        + POSSESSIVE(TP) + " allegiance to Minas Morgul.");
    return 1;
}

/* Function name: agexamine
 * Description  : Anghoth emote to examine supplicants.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agexamine(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You examine all present and wonder if any are worthy of "
            + "your Lord's attention.\n");
        all(" examines all present to determine if any are worthy of "
            + POSSESSIVE(TP) + " Lord's attention.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Examine who?");
    }

    actor("You examine", oblist, " and wonder if that pitiful wretch "
        + "is worthy of your Lord's attention.");
    target(" examines you with unholy eyes, considering your value to " 
        + POSSESSIVE(TP) + " Lord.", oblist);
    all2act(" considers", oblist, ", wondering if " + PRONOUN(TP)
        + " should risk bringing this wretch before " 
        + POSSESSIVE(TP) + " Lord.");
    return 1;
}


/* Function name: agwonder
 * Description  : Anghoth emote to wonder about supplicants.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agwonder(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You wonder if there are any present who have not received "
            + "permission from a Lord of Morgul to do business in "
            + "His city.\n");
        all(" wonders if there are any present who have not received "
            + "permission from a Lord of Morgul to do business in "
            + "His city.");
        return 1;
    }

    oblist = parse_this(str, "[about] [the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Wonder <about> who?");
    }

    actor("You look at the wretch", oblist, " and wonder if it has "
        + "indeed received the permission of a Lord of Morgul to do business "
        + "in His city.");
    target(" looks looks at you wondering if you have indeed been granted "
        + "leave to do business in Minas Morgul.", oblist);
    all2act(" looks at", oblist, " wondering if " 
        + oblist[0]->query_pronoun() + " has been granted permission to do "
        + "business in the City of Ringwraiths.");
    return 1;
}


/* Function name: agsuspicion
 * Description  : Anghoth emote to be suspicious.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agsuspicion(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You look around suspiciously, ever vigilant against those "
            + "who would spy for the Rebels of Gondor.\n");
        all(" looks around suspiciously, ever vigilant against those "
            + "who would spy for the Rebels of Gondor.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("About whom do you have a suspicion?");
    }

    actor("You look suspiciously at", oblist, ", ever vigilant against "
        + "those who would spy for the Rebels of Gondor.");
    target(" looks suspiciously at you, ever vigilant against spies that "
        + "would usurp the power of the Dark Lord.", oblist);
    all2act(" looks suspiciously at", oblist, ", ever vigilant against "
        + "spies that would usurp the power of the Dark Lord.");
    return 1;
}

/* Function name: agfinger
 * Description  : Anghoth emote to finger weapons.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agfinger(string str)
{
    write("You finger your weapons to demonstrate that spies will not "
        + "be tolerated who would interfere with the designs of Melkor.\n");
    all(" fingers " + POSSESSIVE(TP) + " weapons to demonstrate that spies "
        + "will not be tolerated who would interfere with the designs "
        + "of Mordor.");
    return 1;
}


/* Function name: agcry
 * Description  : Anghoth emote: victory cry.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agcry(string str)
{
    write("You cry out in bloodlust having just slain an enemy of the "
        + "Lidless Eye.\n");
    all(" cries out in bloodlust having just slain an enemy of the "
        + "Lidless Eye.");
    return 1;
}


/* Function name: agscream
 * Description  : Anghoth emote: victory cry.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agscream(string str)
{
    write("You scream a horrific battecry and rush to the aid of your "
        + "Liege.\n");
    all(" screams a horrific battlecry and rushes to the aid of "
        + POSSESSIVE(TP) + " Liege.");
    return 1;
}

/* Function name: agslap
 * Description  : Anghoth emote to slap someone silly.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agslap(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("Slap who?\n");
        all(" looks as though " + PRONOUN(TP) + " would like to "
            + "slap someone.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Slap who?");
    }

    actor("You slap", oblist, " forcefully and spit on the wretch for "
        + "defying the will of the Dark Lord.");
    target(" slaps you forcefully for daring to defy the will of the "
        + "Dark Lord.", oblist);
    all2act(" slaps", oblist, " forcefully and spits upon the wretch "
        + "for daring to defy the will of the Dark Lord.");
    return 1;
}


/* Function name: agmove
 * Description  : Anghoth emote to move in front of a liege lord.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agmove(string str)
{
    object *oblist;
    string sponsor, name;

    if (!strlen(str))
    {
        write("Move <in front of> who?\n");
        return 1;
    }

    oblist = parse_this(str, "[in][front][of][the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Move <in front of> who?");
    }

    sponsor = oblist[0]->query_real_name();
    name = TP->query_real_name();

    if (MANAGER->query_anghoth_sponsor(name) != CAP(sponsor))
    {
        actor("You decide against moving in front of", oblist, " as that "
            + "individual is not your sworn Liege. Only your Lord may claim "
            + "your life as Shield.");
        return 1;
    }

    if (MANAGER->query_ashuk(name))
    {
        actor("You decide against moving in front of", oblist, " as that "
            + "individual has fallen from the favour of the Eye. You must "
            + "find a new Lord.");
        return 1;
    }


    actor("You step in front of your Lord", oblist, " in order to protect " 
        + oblist[0]->query_objective() + " from attack.");
    target(" steps in front of you to protect you from attack.", oblist);
    all2act(" steps in front of", oblist, " in order to protect "
        + oblist[0]->query_possessive() + " sworn Liege from attack.");
    return 1;
}


/* Function name: agstruck
 * Description  : Anghoth emote: being dumbstruck.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agstruck(string str)
{
    write("You are struck dumbfounded at the incompetence of those "
        + "who do not serve Mordor.\n");
    all(" is struck dumbfounded at the incompetence of those who "
        + "do not serve Mordor.");
    return 1;
}

/* Function name: ageye
 * Description  : Anghoth emote to give someone the eye.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
ageye(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("Eye who with suspicion?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Eye who?");
    }

    actor("You eye", oblist, " with suspicion, wondering whether or not "
        + oblist[0]->query_pronoun() + " should be dealt the death blow "
        + "here and now.");
    target(" eyes you with suspicion, wondering if you should be dealt "
        + "the death blow here and now.", oblist);
    all2act(" eyes", oblist, " with suspicion, wondering whether or not "
        + oblist[0]->query_pronoun() + " should be dealt the death blow "
        + "here and now.");
    return 1;
}

/* Function name: agwarcry
 * Description  : Anghoth emote: a war cry.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agwarcry(string str)
{
    write("You cry out, 'For the Dark Lord and Melkor!' as you rush "
        + "in to attack.\n");
    all(" cries out, 'For the Dark Lord and Melkor!' as "
        + PRONOUN(TP) + " rushes in to attack.");
    return 1;
}

/* Function name: agexalt
 * Description  : Anghoth emote: a war cry.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agexalt(string str)
{
    write("You drive your weapon into the corpse of your enemy, "
        + "exalting in the name of Melkor!\n");
    all(" drives " + POSSESSIVE(TP) + " weapon into the corpse of "
        + POSSESSIVE(TP) + " enemy, exalting in the name of Melkor!");
    return 1;
}

/* Function name: agtap
 * Description  : Anghoth emote: tap your foot impatiently.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agtap(string str)
{
    write("You tap your foot impatiently, not wishing to be blamed "
        + "for the tardiness of some wretch beneath you.\n");
    all(" taps " + POSSESSIVE(TP) + " foot impatiently, not wishing to be "
        + "blamed for the tardiness of some wretch beneath "
        + POSSESSIVE(TP) + " station.");
    return 1;
}

/* Function name: agglare
 * Description  : Anghoth emote to give someone the eye.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agglare(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("Glare at who?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Glare at who?");
    }

    actor("You glare at", oblist, ", wondering when you will be given leave "
        + "to cleanse His lands of such offal.");
    target(" glares dangerously at you, wondering when " + PRONOUN(TP)
        + " will be given leave to cleanse His lands of offal "
        + "such as you.", oblist);
    all2act(" glares dangerously at", oblist, " wondering when "
        + PRONOUN(TP) + " will be given leave to cleanse His lands of such "
        + "offal.");
    return 1;
}

/* Function name: aggreet
 * Description  : Anghoth emote to greet someone.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
aggreet(string str)
{
    object *oblist;
    string greeting;

    switch (random(3))
    {
    case 0:
        greeting = "Lord of All!";
        break;
    case 1:
        greeting = "Giver of Freedom!";
        break;
    case 2:
        greeting = "Mightiest of the Valar!";
        break;
    default:
    break;
    }

    if (!strlen(str))
    {
        write("You raise your hand in greeting, saying: Hail Melkor, "
            + greeting + "\n");
        all(" raises " + POSSESSIVE(TP) + " hand in greeting, saying: "
            + "Hail Melkor, " + greeting);
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Greet who?");
    }

    actor("You raise your hand in greeting to", oblist, ", saying: "
        + "Hail Melkor, " + greeting);
    target(" raises " + POSSESSIVE(TP) + " hand to you, saying: Hail "
        + "Melkor, " + greeting, oblist);
    all2act(" raises " + POSSESSIVE(TP) + " hand to", oblist, ", saying: Hail "
        + "Melkor, " + greeting);
    return 1;

}

/* Function name: agfarewell
 * Description  : Anghoth emote to say farewell to someone.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
public int
agfarewell(string str)
{
    object *oblist;
    string farewell;

    switch (random(3))
    {
    case 0:
        farewell = "Shadows keep you.";
        break;
    case 1:
        farewell = "Dark travels.";
        break;
    case 2:
        farewell = "Eye guide you.";
        break;
    default:
    break;
    }

    if (!strlen(str))
    {
        write("You make a gesture of farewell, saying: "
            + farewell + "\n");
        all(" makes a gesture of farewell saying: " + farewell);
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("To whom do you wish to say farewell?");
    }

    actor("You gesture at", oblist, " in farewell, saying: "
        + farewell);
    target(" gestures at you in farewell, saying: "
        + farewell, oblist);
    all2act(" gestures at", oblist, " in farewell, saying: " + farewell);
    return 1;

}
