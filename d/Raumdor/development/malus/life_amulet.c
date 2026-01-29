/* 2018 (Shanoga) */

#include "defs.h"
inherit "/std/armour.c";

#define SKILL_TYPE SS_ELEMENT_LIFE
#define SKILL_AMOUNT 10
#define MAX_CHARGE 2000
#define LIQUID_ADJ "golden-hued"

int charge = 0;

void
create_armour()
{
    ::create_armour();
    set_name("amulet");
    set_adj(({"small", "silver-banded"}));
    set_short("small silver-banded amulet");
    set_long("@@amulet_description@@");
    add_item(({"sphere", "small sphere", "translucent sphere"}),
      "@@sphere_description@@");
    set_at(A_NECK);
    set_ac(1);
    set_af(TO);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({80, "life"}));
    add_prop(MAGIC_AM_ID_INFO,
      ({
        "This amulet powerfully radiates life magic.\n", 20,
        "The wearer of this amulet will have increased mastery of life " +
        "magic.\n", 30,
        "It has the potential to heal wounds.\n", 40,
        "Someone must clutch it to invoke this effect.\n", 60,
        "The strength of its healing effect can be increased by freeing " +
        "souls otherwise burdened by certain dark magic.\n", 80,
      }));
    add_prop(OBJ_S_WIZINFO,
      "This amulet is obtained by converting the lich's phylactery via the " +
      "Lord of Drakmere. It is charged by killing Raumdor undead, " +
      "proportional to the undead's size. If charged, a player can 'clutch' " +
      "it to heal up to " + MAX_CHARGE + " HP.\n");
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_M_NO_BUY, 1);
}

string
sphere_description()
{
    int i;
    string *description = ({
        "The sphere is hollow and vacant.\n",
        "There is a shallow layer of " + LIQUID_ADJ +
            " liquid settled on the bottom of the sphere.\n",
        "A small amount of " + LIQUID_ADJ +
            " liquid rests on the bottom of the sphere.\n",
        "A " + LIQUID_ADJ +
            " liquid shifts and swirls within the lower part sphere.\n",
        "The sphere is about half-full with a " + LIQUID_ADJ +
            " liquid that whirls around, surging in different directions.\n",
        "The better part of the sphere is filled with a " + LIQUID_ADJ +
            " liquid that churns around briskly, motes of white " +
            "light sparkling within.\n",
        "A " + LIQUID_ADJ + " liquid nearly fills the sphere, whirling " +
            " swiftly with streaks of glistening white light.\n",
        "The sphere is completely full of a " + LIQUID_ADJ + " liquid " +
            "that is spinning rapidly with radiant white light flashing " +
            "in bands near the surface.\n",
    });

    if (charge <= 0)
        return description[0];
    if (charge >= MAX_CHARGE)
        return description[-1];

    return description[
        1 + (charge / ((MAX_CHARGE / (sizeof(description) - 2)) + 1))];
}

string
amulet_description()
{
    return "This amulet is made up a small, translucent sphere banded " +
           "by two perpendicular silver rings. Its silver chain affixed " +
           "where the silver bands intersect. " + sphere_description();
}

/*
 * Function name: wear
 * Description  : Adds the bonus skill and special description when the
 *              : amulet is worn
 * Arguments    : object ob - the amulet
 */
int
wear(object ob)
{
    TP->set_skill_extra(
      SKILL_TYPE, TP->query_skill_extra(SKILL_TYPE) + SKILL_AMOUNT);
    TELL(TP,
      "As you lift the chain over your head, the amulet rests lightly on " +
      "your chest and the touch of the chain on your neck sends an " +
      "invigorating shiver throughout your body.\n");
    return 0;
}

/*
 * Function name: remove
 * Description  : Removes the bonus skill and special description when
 *              : the amulet is removed
 * Arguments    : object ob - the amulet
 */
int
remove(object ob)
{
    TP->set_skill_extra(
      SKILL_TYPE, TP->query_skill_extra(SKILL_TYPE) - SKILL_AMOUNT);
    TELL(TP,
      "The invigorating feeling passes from you as you lift the chain from " +
      "your neck and remove the amulet from your chest.\n");
    return 0;
}

/*
 * Function name: query_charge
 * Description  : Returns the number of charge stored
 * Returns      : int - the number of charge stored
 */
int
query_charge()
{
    return charge;
}

/*
 * Function name: set_charge
 * Description  : Sets the number of charge stored (for testing)
 * Returns      : int - the number of charge to set
 */
void
set_charge(int new_charge)
{
    return charge = min(new_charge, MAX_CHARGE);
}

void
do_charge(object ob)
{
    charge = min(MAX_CHARGE, charge + ob->query_average_stat());
    add_item(({"liquid", LIQUID_ADJ + " liquid"}), "Though thicker than " +
      "water, it flows with ease. Its soft, golden luster evokes a " +
      "feeling of warmth.\n");
}

int
do_clutch(string str)
{
    if (PARSE_COMMAND_ONE(str, INV(TP), "[the] %i") != TO)
    {
        DEFAULT_NOTIFY;
        return 0;
    }

    TELL_SEEN(TP, QCTNAME(TP) + " clutches " + HIS(TP) + " "
      + QSHORT(TO) + ".\n");

    if (query_worn() != TP || !charge)
    {
        write("You clutch of the amulet, but nothing happens.\n");
        return 1;
    }

    write(
      "The fluid in the amulet flashes for a moment, then disappears. You " +
      "feel a warmth fill your body and heal your wounds.\n");
    TELL_SEEN(TP, "The amulet flashes for a moment. " + QCTNAME(TP) +
      " looks revitalized!\n");
    TP->heal_hp(charge);
    charge = 0;
    remove_item("liquid");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_clutch, "clutch");
}
