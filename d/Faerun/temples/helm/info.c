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
    material    = "an oval disk and a brushed finish",
    symbol      = "a staring eye with a blue pupil on the front of an upright war gauntlet",
    cult_type   = "cult",
    deity_name  = "Helm",
    deity_pron  = "his",
    emblem_file = "helm/emblem";

int min_guild   = AL_NEUT_GOOD;


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
    "Helm, also known as the Vigilant One, the Great Guard, and The Watcher, is the god of guardians, protection and protectors, and worshipped by guards and paladins. He has long been seen as a cold and focused deity who impartially takes the role of defender and sometimes also as an enforcer.\n" +
"\n" +
"He an unflinching and dedicated deity. He is often viewed as emotionless and unconcerned with moral issues in the face of duty. However, he is merely dedicated to his work and takes pride in putting work ahead of all other things. He is fond of children and more tolerant of their minor infractions than anyone else's. Many believe that Helm would give his own life to guard something entrusted to him.\n" +
"\n" +
"Helm is a very old deity. He is the eternal sentry and always represented and seen wearing a full suit of armor that represents the weight of his heavy responsibility. Nonetheless, Helm gets--and has always gotten--the job at hand done without complaint. The people of the Realms widely admired these qualities in what they see as a humble and reassuring god.\n" +
"\n" +
"Far back in time, the deity Lathander caused a divine purge known as the Dawn Cataclysm. During that time, Helm's lover, a lesser deity of pragmatism called Murdane, was victim. Helm has begrudged the Morninglord of this ever since. However, Helm reserves his real opposition for deities whose plots threaten the people and stability of Faerun.\n" +
"\n\n";
}