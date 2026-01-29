/* Locket by Gwyneth, August 1999 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

int open = 0;

void
create_armour()
{
    set_name(({ "locket", "_kender_quest_locket_" }));
    set_adj("tarnished");
    add_adj("silver");
    set_short("tarnished silver locket");
    set_long("This tarnished silver locket has a thin chain with a clasp " + 
        "in the back. The locket itself can be opened or closed. Right " + 
        "now it is " + 
        "@@locket_state@@" + 
        "\n");
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 60);
    add_cmd_item(TO->query_names(), "open", "@@open_locket");
    add_cmd_item(TO->query_names(), "close", "@@close_locket");
    set_at(A_NECK);
    set_ac(0);
    set_af(TO);
}

string
close_locket()
{
    say(QCTNAME(TP) + " closes the tarnished silver locket with a soft " + 
        "'click'\n");
    open = 0;
    return "You close the tarnished silver locket with a soft 'click'.\n";
}

string
open_locket()
{
    say(QCTNAME(TP) + " opens the tarnished silver locket with a soft " +
        "'click'\n");
    open = 1;
    return "You open the tarnished silver locket with a soft 'click'.\n";
}
        
string
locket_state()
{
    if (open)
        return "open. There is a picture of two kender inside, perhaps " + 
            "related by their similar features.";
    else
        return "closed.";
}

/* Function name : Wear
 * Description : Gives an emote to room and wearer when worn.
 * Returns : 1 or 0
*/

mixed
wear(object what)
{
    if (what != TO)
       return 0;

    write("You clasp the tarnished silver locket around your neck. It " + 
        "rests easily on your chest.\n"); 
    say(QCTNAME(TP) + " clasps the tarnished silver locket around " + HIS(TP) + 
        " neck.\n");
    return 1;
}

/* Function name : Remove
 * Description : Gives an emote to room and wearer when item is removed.
 * Returns : 1 or 0
*/

mixed
remove(object what)
{
    if (what != TO || !TP)
      return 0;

    write("You unclasp the tarnished silver locket, and remove it.\n"); 
    say(QCTNAME(TP) + " unclasps the tarnished silver locket from " + 
        "around " + HIS(TP) + " neck, and removes it.\n");
    return 1;
}

