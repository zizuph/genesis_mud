/* A Studded armour - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
                               
void
create_armour()
{
    set_name("mail");
    set_pname("mails");
    add_pname("armours");
    set_short("studded mail");
    set_pshort("studded mails");
    set_long(
        "This armour consists mainly of hardened leather, which has " +
        "large metal studds set into it.\n");

    add_adj("studded");

    set_ac(15); /* standard studded mail */

    set_am(({ 0, 1, -1}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 3200);
    add_prop(OBJ_I_VOLUME, 1100);
}
