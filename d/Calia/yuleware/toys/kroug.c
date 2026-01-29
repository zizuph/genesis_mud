/* Christmas Toy - krougish papa doll */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name(({"doll", "toy"}));
    set_adj(({"krougish", "papa"}));
    set_long("A small but heavy wooden doll of krougish " +
        "manufacture, resembling a snarling male kroug. It's " +
        "ornamented with sharp bronze spikes and plates that " +
        "resemble armor. Its expression is mean and smug " +
        "enough to make you want to shake it, and it doesn't " +
        "look at all suitable for hugging or cuddling.\n");
    set_short("krougish papa doll");    /*  added by Uhclem  */

// Items to look at

    add_item(({"sharp bronze spikes", "bronze spikes", "spikes", "plates",
        "points", "edges"}),
        "The doll's bronze armor has been carefully covered with needle-" +
        "sharp points and razor-sharp edges. Careless handling of " +
        "the doll could easily result in nasty cuts and punctures.\n");

// Object properties

    add_prop(OBJ_I_WEIGHT, 500);    /*  changed by Uhclem  */
    add_prop(OBJ_I_VOLUME, 1000);    /*  changed by Uhclem  */
    add_prop(OBJ_I_VALUE, 250);

    add_prop(OBJ_M_NO_SELL, "The merchant says to you: Who'd " +
        "want to buy this? It'd give a child nightmares!\n");
}

/*
 * Function name: shake
 * Description:   Frightens children.
 * Arguments:     doll, papa doll, krougish papa doll
 * Returns:       int 1 or 0
 */

int shake(string str)
{
//  LOCAL FUNCTION DEFINITIONS:
    object tp = this_player();
    object target;

    if (!stringp(str)) /* player didn't specify something to 'shake' */
        {
        return 0;
        }

    if (parse_command(str, all_inventory(tp), "%o", target))
        {
            if (target != this_object()) return 0;

            write("You shake the kougish papa doll.\nThe " +
            "krougish papa doll snarls: Bah humbug!\n");

            say(QCTNAME(this_player())+ " shakes a krougish " +
            "papa doll.\nThe krougish papa doll snarls: " +
            "Bah humbug!\n");

        return 1;
        }
    return 0;
} 

/*
 * Function name: hug
 * Description:   Doll provides no comfort.
 * Arguments:     doll, papa doll, krougish papa doll
 * Returns:       int 1 or 0
 */

int hug(string str)
{
//  LOCAL FUNCTION DEFINITIONS:
    object tp = this_player();
    object target;

    if (!stringp(str)) /* player didn't specify something to 'hug' */
        {
        return 0;
        }

    if (parse_command(str, all_inventory(tp), "%o", target))
        {
            if (target != this_object()) return 0;

            write("You " + query_verb() + " the krougish papa " +
            "doll, causing sharp points and edges to stab painfully " +
            "into your exposed flesh.\n");

            say(QCTNAME(this_player())+ " " + query_verb() + 
            "s the krougish papa doll.\n");

            return 1;
        }
    return 0;
} 

// This is to let people manipulate the toy.

public void
init()
{
    ::init();
    add_action(shake, "shake");
    add_action(hug, "hug");
    add_action(hug, "cuddle");
}