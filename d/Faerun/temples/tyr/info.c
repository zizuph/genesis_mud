/*
 * Specific info relating to the deity
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

//#define TOKEN_NAME  "_temple_token"

// variables for the emblem and temple
string adj1     = "smooth",
    adj2        = "shield-shaped",
    emblem_name = "emblem",
    material    = "a rectangular disk with a smooth finish",
    symbol      = "a set of balanced scales resting on a warhammer",
    cult_type   = "cult",
    deity_name  = "Tyr",
    deity_pron  = "his",
    emblem_file = TYR_DIR + "emblem"; /* path for emblem */

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
"Tyr, also known as Tyr Grimjaws, Tyr the Even-Handed, Wounded Tyr, the Maimed God, and Blind Tyr, is a noble warrior and the god of justicewho is strong in spirit and dedicated to justice. He lost his left hand to Kezef the Chaos Hound and is sometimes depicted as blind.\n" +
"\n" +
"This god sees himself as a father figure who wants to deal with others with love, courage, and the strength of the bonds of family, he knows that such can never be in an imperfect world. He is instead viewed by outsiders as a stern arbiter of justice.\n" +
"\n" +
"Tyr and his followers are devoted to the cause of justice, to the righting of wrongs and the deliverance of vengeance. This is not necessarily equality or fairness, as some make the maimed god out to represent, but rather the discovery of truth and the punishment of the guilty. Tyr's followers tend to be stiff-necked about theology, and see matters in black and white terms. He is most popular with bureaucrats, judges, and merchants who make the entire system move efficiently.\n" +
"\n\n";
}