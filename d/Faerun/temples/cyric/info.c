/*
 * Specific info relating to the deity
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

//#define TOKEN_NAME  "_temple_token"

// variables for the emblem and temple
string adj1     = "small",
    adj2        = "round",
    emblem_name = "emblem",
    material    = "bone and polished to a dull shine",
    symbol      = "a jawless skull on a black or purple sunburst",
    cult_type   = "cult",
    deity_name  = "Cyric",
    deity_pron  = "his",
    emblem_file = "cyric/emblem";

int min_guild   = AL_EVIL;


/*
 * This is what the emblem will look like with the above settings.
 * Text enclosed in [ ] is from a variable above:
 *
    This is a [small] [round] [emblem] made of [bone and polished to a
    dull shine]. It identifies you as a member of the [cult] of [Myrkul].
    On the front is the likeness of [a white human skull against a black
    field]. On the back are the words 'type <clinfo> for more info'.
*/

// text for the sign in the temple
string read_sign()
{   return "\n\n"+
    "Cyric, the Prince of Lies, The Black Son, or Lord of Madness, is an extremely " + 
"powerful and evil God. He has no allies within the Gods, but many, many " + 
"enemies. His symbol is a jawless skull on a black or purple sunburst. His " + 
"followers are many especially amongst corrupt officials, thieves and " + 
"assassins. He became a divine being due to the events which occurred during " + 
"the Time of Troubles.\n" + 
"\n" + 
"He won over many followers during that time, and also stole the domains of " + 
"other fallen gods, most notably Bhaal and Leira. Cyric is unpredictable, " + 
"somewhat insane, and egocentric. He delights in placing people in power " + 
"through intrigue, then tearing them down at his whim.\n" + 
"\n" + 
"When Cyric wishes to appear, he usually does so by haunting the dreams of " + 
"his worshippers as a bloody wraith, or by manifesting as a cloud of " + 
"poisonous smoke before his enemies rather than sending an avatar. He " + 
"sometimes manifests as a sudden gloom containing the phantom images of " + 
"whirling human skulls--and the dark, intent gaze of two black eyes. At " + 
"other times he sends nightmares or various undead creatures to do his " + 
"bidding or show his favor or displeasure.\n" + 
"\n" + 
"Cyric is not above masquerading as another deity to gain the worship of " + 
"mortals and the power derived from their worship.\n" +
"\n" +
"If you choose to devote your life to Cyric, examine the altar.\n\n";
}