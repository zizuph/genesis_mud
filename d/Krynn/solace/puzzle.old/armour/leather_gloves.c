/* Leather gloves. ~solace/puzzle/armour/leather_gloves */

inherit "/std/armour";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

int remove_alarm;

void create_armour()
{
    set_name("pair of leather gloves");
    add_name("leather gloves");
    add_name("gloves");
    set_pname("pairs of leather gloves");
    set_long("A pair of leather gloves with a strap to bind them tight "+
        "around hands. You notice that they grip very well.\n");

    set_ac(4);
    set_af(TO);

    /*       Imp  Sla  Blu  */
    set_am(({ 0,  -2,   2 }));

    set_at(A_HANDS);

    set_likely_cond(2);
    set_likely_break(1);

    add_prop(OBJ_I_VOLUME, 450);
    add_prop(OBJ_I_WEIGHT, 600);

    add_prop("mystic_armour",1);
    /* Since this is a quest item, we add the mystic
     * prop so they can do the quest as well
     */
}

mixed remove(object obj)
{
    if(obj == TO)
        if(!pointerp(get_alarm(remove_alarm)))
            set_alarm(0.5, 0.0, "move_me_away");

    return 1;
}

void move_me_away()
{
    object obj = E(TO);

    if(LIVING(obj))
    {
        obj->catch_msg("You drop "+LANG_THESHORT(TO)+".\n");
        tell_room(E(obj), QCTNAME(obj)+" drops "+LANG_ASHORT(TO)+".\n", obj);

        TO->move(E(obj));
    }
}
