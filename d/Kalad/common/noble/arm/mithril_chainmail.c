inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */
/* Changed the long description Damaris 9/2002 */

void
create_armour()
{
    ::create_armour();
    set_name("chainmail");
    add_name("mail");
    set_adj("ancient");
    add_adj("mithril");
    set_af(TO);
    set_short("ancient mithril chainmail");
    set_long("This "+short()+" has obviously been forged from "+
        "ancient times and quite magical. It is extraordinarily "+
        "light and solid as rock. Upon careful inspection along "+
        "the silver breastplate there are runes that glimmer with a strange "+
        "black light.\n");
    add_item(({"rune", "runes"}),
        "It is obvious that the runes are magical, however you are "+
        "unable to make out their meaning.\n");
    add_item(({"silver breastplate"}),
        "The silver breastplate has runes that glimmer.\n");
    set_ac(45); /* mithril and magical enhanced */
    set_am( ({ -2, 3, -1 }) );
    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT,4000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This armour glows brightly with "+
                    "a magical radiance. It is very much magical and very strong "+
                    "againts the element of fire.\n",20}));
    add_prop(OBJ_S_WIZINFO,"This is the captain of the noble castle "+
        "guards armour. It is rather tough to get, but it is a very "+
        "good chainmail made of the magical metal mithril. It also "+
        "protects against fire.\n");
}


mixed
wear(object arm)
{
    TP->add_magic_effect(TO);    
    say("The runes on the "+short()+" glow a bright red.\n");
    write("The runes on the armour glow bright red.\n");
    set_long("This "+short()+" has obviously been forged from "+
        "ancient times and quite magical. It is extraordinarily "+
        "light and solid as rock. Upon careful inspection along "+
        "the silver breastplate there are runes that glimmer with a strange "+
        "crimson light.\n");
    return 0;
}

mixed
remove(object arm)
{
    if (!objectp(query_worn()))
        return 0;
    
    set_this_player(query_worn());
    
    TP->remove_magic_effect(TO);
    say("The runes on " + QTPNAME(query_worn()) + " " + QSHORT(TO) + " dim down to a black color.\n");
    write("The runes on the armour dim down to a black color.\n");
    set_long("This "+short()+" has obviously been forged from "+
        "ancient times and quite magical. It is extraordinarily "+
        "light and solid as rock. Upon careful inspection along "+
        "the silver breastplate there are runes that glimmer with a strange "+
        "black light.\n");
    return 0;
}

mixed
query_magic_protection(string prop, object what)
{
    if(what == query_worn() && prop == MAGIC_I_RES_FIRE)
        return ({30, 1});
    return ::query_magic_protection(prop,what);
}

