/*
 * /d/Gondor/guilds/rangers/soul/grsay.c
 *
 * Included in the soul. The ability for rangers to speak to one
 * another with hand signals.
 *
 * Original grsay (Adunaic) coded by Elessar.
 *
 * Modification log:
 *   Alto, February 2002. Move. Changed from Adunaic to hand signals
 *     that can only be understood by other rangers.
 *   Gwyneth, April 2002 - Borrowed from Auberon who hacked it May 2001
 *     for the kender speak from Cirion's Sybarite language of 1996.
 *   Gwyneth, June 2004 - Upped understanding difficulty level and
 *     changed so that they speak in Adunaic instead of use hand
 *     signals in combat.
 *   Gwyneth, July 12, 2004 - Removed retaining of real names. Raised difficulty.
 */

#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include "grsay.h"
#include <macros.h>
#include <ss_types.h>

int understand_hand_signal(object pl);
int use_hand_signal(string str);
string replace(string str);
string *construct_str(string *oldstr);
void grsay_to(object me, object who, string *newstr, string *oldstr, 
              string what, int fighting);

int
understand_hand_signal(object pl)
{
    int  langsk = pl->query_skill(SS_LANGUAGE);

    if ((RANGERS_MEMBER(pl) && (langsk > 10)) || pl->query_wiz_level())
        return 1;
    else 
        return 0;
}

int
use_hand_signal(string str)
{
    int i = 0, j = 0, size, size2, fighting = 0;
    object *obj;
    string *newstr, *oldstr;
   
    /* Adunaic when the Ranger is fighting. */
    if (this_player()->query_attack())
        fighting = 1;

    if (!strlen(str)) 
    {
        NF("Use hand signals to communicate what?\n");
        return 0;
    }

    str += " ";
    /*
     * Check take from /std/living/cmdhooks.c:
     * We do not want people to add too many spaces and use the grsay
     * command as a way to generate emotions themselves. However, we do
     * not want to waste this on wizards and we also test whether people
     * haven't used too many spaces. You cannot make an emotion with
     * only a few. This wildmatch is 40% faster than the explode/implode
     * stuff, so as long as people don't use 8 spaces more than 40% of
     * the time, this check pays itself back.
     */
    if (!TP->query_wiz_level() &&
      wildmatch("*       *", str))
    {
        str = implode((explode(str, " ") - ({ "" }) ), " ");
    }

    if (fighting)
        write("You say in Adunaic: " + str + "\n");
    else
        write("You communicate with hand signals: " + str + "\n");

    obj = filter(all_inventory(ENV(TP)), interactive) - ({ TP });
    for (i = 0, size = sizeof(obj); i < size; i++)
    {
        if (!understand_hand_signal(obj[i]))
        {
            if (CAN_SEE(obj[i],TP))
            {
                oldstr = explode(str, " ");
                newstr = allocate(sizeof(oldstr));
                for(j = 0, size2 = sizeof(oldstr); j < size2; j++)
                    newstr[j] = replace(oldstr[j]);

                 grsay_to(TP, obj[i], newstr, oldstr, str, fighting);
             }
        }
        else
        { 
            if (CAN_SEE(obj[i],TP))
            {
                if (fighting)
                    obj[i]->catch_tell(TP->query_The_name(obj[i])
                        + " says in Adunaic: " + str + "\n");
                else
                    obj[i]->catch_tell(TP->query_The_name(obj[i])
                        + " communicates with hand signals: " + str + "\n");
            }
        }
    }

    return 1;
}

/*
 * Function name: replace
 * Description  : Replaces a word with one from the list of defines
 *                of the same length. Retains player names,
 *                capitalizations and punctuation.
 * Arguments    : string str - one word to replace
 * Returns      : A replacement word of the same
 *                string length in the new language.
 */
string
replace(string str)
{
    string back, nihil;

    switch(strlen(str))
    {
    case 1: back = W1[random(sizeof(W1))]; break;
    case 2: back = W2[random(sizeof(W2))]; break;
    case 3: back = W3[random(sizeof(W3))]; break;
    case 4: back = W4[random(sizeof(W4))]; break;
    case 5: back = W5[random(sizeof(W5))]; break;
    case 6: back = W6[random(sizeof(W6))]; break;
    case 7: back = W7[random(sizeof(W7))]; break;
    default: back = W8[random(sizeof(W8))]; break;
    }

    /* Retain names of living people
    if(stringp(str) && find_living(lower_case(str)))
        back = CAP(str);
    */

  /* Retain capitializations */
    if(str == CAP(str))
        back = CAP(back);

    /* Retain punctuation */
    if(sscanf(str, "%s.", nihil))
        back += ".";
    if(sscanf(str, "%s!", nihil))
        back += "!";
    if(sscanf(str, "%s?", nihil))
        back += "?";
    if(sscanf(str, "%s,", nihil))
        back += ",";

    return back;
}

/*
 * Function name: construct_str
 * Description  : Constructs a new string from one given with replace()
 * Argument     : the array of words to be replaced into
 *                the new language.
 * Returns      : The array of words in the translated
 *                string.
 */
string
*construct_str(string *oldstr)
{
    int i, size;
    string *newstr;

    for(i = 0, size = sizeof(oldstr); i < size; i++)
        newstr[i] = replace(oldstr[i]);

    return newstr;
}

/* Function name: grsay_to
 * Description  : Sends a somewhat garbled message
 * Arguments    :
 */
void
grsay_to(object me, object who, string *newstr, string *oldstr, string what,
  int fighting)
{
    int i, size, lang = who->query_skill(SS_LANGUAGE);
    string endstr = "";

    if(lang < 25)
    {
        if (fighting)
            who->catch_tell(me->query_The_name(who) + " says something " +
                "in Adunaic.\n");
        else
            who->catch_tell(me->query_The_name(who) + " makes some sort of " +
                "gesture.\n");
        return;
    }

    if(lang < 45)
    {
        if (fighting)
            who->catch_tell(me->query_The_name(who) + " says something in " +
                "Adunaic.\n");
        else
            who->catch_tell(me->query_The_name(who) + " makes some hand " +
                "gestures that appear to have some meaning.\n");
        return;
    }

    if(lang < 70)
    {
        for(i = 0, size = sizeof(newstr); i < size; i++)
        {
            if (random(5) > 2) 
                endstr += "... ";
            else
                endstr += newstr[i] + " ";
        }

        if (fighting)
            who->catch_tell(me->query_The_name(who) + " says in Adunaic: " +
                endstr + "\n");
        else
            who->catch_tell(me->query_The_name(who) + " communicates with " +
                "hand signals: " + endstr + "\n");
        return;
    }

  /* I think that Sybarite, Elemental Mantras, Draco, etc. are so hard as
     to make language skill not very useful, so am intentianally making it
     quite a bit easier than those (difficulty 90, 87.5, and 100 
     respectively).

     Gwyneth--Changed to random (160), which means those with skill of 80
     should understand about 50% of the conversation.

     --Changed difficulty to 70 + random(12). Rangers, especially
     RoN, should have some secret abilities. Too many guilds have high
     language skill to make signaling useful without this higher level.
     However, it will still be understandable to some. --Serif

     Gwyneth--Changed it back from random(12) as it doesn't flat out give
     the whole meaning. The words are randomized in the following manner:
       <25 - they see hand movements
       <45 - they see hand movements that seem like they have meaning,
              but can't understand a thing.
       <70 - They could see a sentence such as the following:
             "The quick brown fox jumps over the lazy dog." as:
             "... ... don't lot tricky ... men ... lord."
              Each word that is translated is translated to another
              word from a list with the same length. fox->lot, etc.
              The ... are unseen words, but with <70 skill, they
              have 100% error rate.
       >=70 - the words are substituted as above, but with a chance
              of success in seeing the word. Currently, the chance
              for success at level 80 is 50% (lang > random(160))
              and at skill level 100, it is 62.5%. At 100 skill level,
              you would get a sentence such as:
              "The quick brown fox jumps over the lazy dog."
              "Die quick brown ... jumps ... the lazy loot."
              This is assuming that random works right, and that is
              assuming a lot. Still, it is the best we have, and
              makes things interesting.
   */
    for(i = 0, size = sizeof(newstr); i < size; i++)
    {
        if((lang) > random (180))
            endstr += oldstr[i] + " ";
        else if (random(5) > 2) 
            endstr += "... ";
        else 
            endstr += newstr[i] + " ";
    }

    if (fighting)
        who->catch_tell(me->query_The_name(who) + " says in Adunaic: " +
            endstr + "\n");
    else
        who->catch_tell(me->query_The_name(who) + " communicates with " +
            "hand signals: " + endstr + "\n");
    return;
}
