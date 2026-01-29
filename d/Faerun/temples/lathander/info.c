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
    material    = "a silver disk and polished smooth",
    symbol      = "a sunrise made of rose, red, and yellow gems",
    cult_type   = "cult",
    deity_name  = "Lathander",
    deity_pron  = "his",
    emblem_file = "lathander/emblem";

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
    "Lathander, the Morninglord, is a powerful, exuberant deity, who is popular among commoners, nobles, merchants, and the young. Although occasionally given to excess, abundant enthusiasm, and vanity, he is an optimistic and perseverant deity who blesses new ventures.\n" + 
"\n" + 
"He is the neutral good deity of creativity, dawn, renewal, birth, athletics, spring, self-perfection, vitality and youth. He favours those who dispel the undead and blesses those who plant new life. Lathander is also the god called upon to bless birth and fertility related ceremonies.\n" + 
"\n" + 
"Lathander is a vibrant power that enjoys doing physical things for the sake of doing them. His many followers work in various creative arts, such as music, painting, entertaining, and the creation of works of fine art.\n\n"; 
}