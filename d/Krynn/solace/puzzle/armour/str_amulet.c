/* Amulet of strength. ~solace/puzzle/objects/str_amulet */

/* Based on an idea by Zork. */
/* modified by Teth 96/11/14, added magic_info */
/* Removed hints at id. Teth 96/11/17 */

inherit "/std/armour";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h" 

void create_armour()
{
    set_name("golden amulet");
    add_name("amulet");
    set_short("golden amulet");
    set_pshort("golden amulets");
    set_long("This is a golden amulet on which is painted a picture of a "+
        "blazing sun. It could be your imagination, but it seems to glow "+
        "a little every time your heart beats.\n");

    set_ac(0);
    set_af(TO);
    set_at(A_NECK);
    set_am(({ 0, 0, 0 }));

    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_WEIGHT, 136);
    add_prop(OBJ_I_VOLUME, 136);

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO,
        "This amulet adds a bonus of 5 to the strength stat " +
        "upon wearing it. This bonus is removed when the " +
        "amulet is removed.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"This amulet is magically enchanted.\n", 5,
        "This amulet adds a measure of strength to its " +
        "wearer.\n", 20, "This amulet gives its wearer " +
        "increased strength for the time that it is worn. " +
        "It matters not the strength of the wearer, the amulet " +
        "gives an equal amount of strength to anyone.\n", 51}));
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
}

nomask mixed wear(object what)
{
    int dummy = TP->query_stat_extra(0) + 5;

    TP->set_stat_extra(0, dummy);

    TP->catch_msg("You feel something in your body change as you " +
        "wear the amulet.\n");
    tell_room(E(TP), QCTNAME(TP)+" changes somehow as "+PRONOUN(TP)+
        " wears "+POSSESSIVE(TP)+ " amulet.\n", TP);

    return 0;
}

nomask mixed remove(object what)
{
    int dummy = TP->query_stat_extra(0) - 5;

    TP->set_stat_extra(0, dummy);

    TP->catch_msg("You feel something change within you as you " +
        "remove the amulet.\n");
    tell_room(E(TP), QCTNAME(TP)+" seems to change somehow as "+PRONOUN(TP)+
        " removes "+POSSESSIVE(TP)+" amulet.\n", TP);

    return 0;
}
