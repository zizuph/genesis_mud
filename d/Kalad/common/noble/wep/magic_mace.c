/*
* /d/Kalad/common/noble/wep/m_mace.c
* Purpose    : Magical mace; need good club skill, strong mana.
* Located    : 
* Created By : Sarr
* Modified By: Sarr, Rico
* First Modif: 12.Feb.97
* 2021-11-07 Meton Changed from no-sell to keep
*/

inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"

    void
    create_weapon()
    {
    ::create_weapon();

    set_name("mace");
    set_adj("wicked");
    add_adj("giant");
    set_short("wicked giant mace");
    set_long("You see a long steel shaft with leather strips "+
        "wrapped around it for a better grip. On the steel shaft, "+
        "a large, heavy steel ball is planted. Protruding from the "+
        "steel ball are razor sharp spikes with four edges to them. "+
        "The whole thing is strangely light, and you sense something "+
        "magical about it.\n");

    set_hit(39);
    set_pen(33);
    set_hands(W_RIGHT);
    set_wf(TO); 
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON | W_IMPALE); /* Spikes impale */

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 30, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "The steel of this mace was apparently augmented with "+
            "the use of magic in its forging.\n", 15,
        "This weapon shall resist the attempts of the unskilled "+
            "to wield it.\n", 20,
        "The sharpness of the spikes have been further honed through "+
            "enchantment, lending additional injury to its crushing "+
            "weight.\n", 30,
        "The weapon has been embued with a malevolent yet minor "+
            "eldritch sentience. Let even the wielder beware.\n", 35,
        "Then weapon shall, when wielded, exact a toll on its "+
            "wielder's concentration.\n", 60,
        }));
    add_prop(OBJ_S_WIZINFO,"This is a mace made from magically "+
        "enhanced steel. It makes for a very nasty weapon. It drains "+
        "500 mana when you wield it. You must have 40 club skill to "+
        "wield it.\n");
    //add_prop(OBJ_M_NO_SELL, "The giant mace is a priceless " +
        //"weapon!\n");
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 5365);
    add_prop(OBJ_I_VOLUME, 1520);
    }

    mixed
    wield(object wep)
    {
    set_this_player(E(wep));

    if(TP->query_skill(SS_WEP_CLUB) < 40 )
    {
        say(QCTNAME(TP) + " is not skilled enough to wield the "+
            short() + ".\n");

        return "You are not skilled enough to manage this weapon.\n";
    }

    if(TP->query_mana() < 500 )
    {
        say(QCTNAME(TP) + " lacks the mental strength to wield "+
            "the " + short() + ".\n");

        return "You lack the mental strength to wield this weapon.\n";
    }

    write("As you wield the " + short() + ", a purple aura surrounds "+
        "the spiked ball.\n");
    say("As " + QTNAME(TP) + " wields the " + short() + ", a purple "+
        "aura surrounds the spiked ball.\n");
    write("You feel your mind being drained by the power in the "+
        short() + ".\n");

    TP->add_mana(-500);
    TO->set_short("glowing wicked giant mace");

    return 1;
    }

    mixed
    unwield(object wep)
    {
        set_this_player(query_wielded());

    write("You release your grip on the " + short() + ".\n");
    say(QCTNAME(TP) + " releases " + HIS(TP) + " grip on the "+
        short() + ".\n");

    TO->set_short("wicked giant mace");

    return 1;
    }
