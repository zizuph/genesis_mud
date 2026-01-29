/*
 * Specific info relating to the deity
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

// variables for the emblem and temple
string adj1     = "small",
    adj2        = "round",
    emblem_name = "token",
    material    = "silver and polished to a dull shine", 
    symbol      = "unknown symbol", 
    cult_type   = "order", 
    deity_name  = "Unknown",
    deity_pron  = "his",
    emblem_file = "myrkul/emblem";

int min_guild   = AL_NEUTRAL;

string god_token   = "_" + deity_name + "_token";


       

/*
 * This is what the emblem will look like with the above settings. 
 * Text enclosed in [ ] is from a variable above:
 *
    This is a [small] [round] [token] made of [silver and polished to a 
    dull shine]. It identifies you as a member of the [order] of [Unknown]. 
    On the front is the likeness of [unknown symbol]. On the back are 
    the words 'type <clinfo> for more info'.
*/

string deity_descr = "A description of the deity, what they're like, " +
    "a description of their symbol, etc.";

// sample text for the sign in the temple
string read_sign()
{   return "\n\n" + deity_descr + "\n\n";
}