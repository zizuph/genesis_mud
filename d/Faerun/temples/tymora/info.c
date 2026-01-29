/*
 * Specific info relating to the deity
 */

#include "/d/Faerun/defs.h"
#include "defs.h"



// variables for the emblem and temple
string adj1     = "large",
    adj2        = "round",
    emblem_name = "coin",
    material    = "polished silver",
    symbol      = "Tymora's happy face surrounded by shamrocks",
    deity_name  = "Tymora",
    deity_pron  = "her",
    emblem_file = TYMORA_DIR + "emblem";

int min_guild   = AGREEABLE;


/*
 * This is what the emblem will look like with the above settings.
 * Text enclosed in [ ] is from a variable above:
 *
    This is a [adj1] [adj2] [emblem_name] made of [material]. 
    It identifies you as a member of the [cult_type] of [deity_name].
    On the front is the likeness of [symbol]. On the back are the 
    words 'type <clinfo> for more info'.
*/

// text for the sign in the temple
string read_sign()
{   
    string sign_text = "";
    sign_text = read_file(TYMORA_DIR + "god_info.txt");
    
    return sign_text;
}