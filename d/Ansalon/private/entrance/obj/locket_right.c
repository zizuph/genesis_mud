/* Locket by Gwyneth, August 1999 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define WHOLE_LOCKET "/d/Ansalon/private/entrance/obj/locket_whole"

int open = 0;

void
create_armour()
{
    set_name(({ "locket", "_locket_right_" }));
    set_adj("tarnished");
    add_adj("broken");
    add_adj("silver");
    set_short("tarnished broken silver locket");
    set_long("This tarnished silver locket has a thin chain with a clasp " + 
        "in the back. There is only half of the locket though. The other " + 
        "half is missing.\n");
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_WEIGHT, 75);
    add_prop(OBJ_I_VOLUME, 30);
    set_at(A_NECK);
    set_ac(0);
    set_af(TO);
}

void
enter_env(object from, object to)
{
    object left_locket;
    if (left_locket = present("_locket_left_", E(TO)))
    {
        setuid();
        seteuid(getuid());
        left_locket->remove_object();
        clone_object(WHOLE_LOCKET)->move(E(TO));
        write("The two halves of the locket merge together.\n");
        set_alarm(0.1,0.0,"merge_lockets");
    }
    ::enter_env(from, to);
}

void
merge_lockets()
{
    remove_object();
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

    write("You clasp the broken locket around your neck. Its " + 
        "rough edge rubs against your skin.\n"); 

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

    write("You unclasp the broken locket, and remove it, rubbing your " + 
        "scratched skin.\n"); 
    say(QCTNAME(TP) + " unclasps the broken locket from " + 
        "around " + HIS(TP) + " neck, and removes it.\n");
    return 1;
}

