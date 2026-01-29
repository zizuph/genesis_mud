/***************************************************************
 * Name: Runed-covered Dark-bladed Spear.                      *
 * By  : Elmore.                                               *
 * Date: 26/03-2001                                            *
 * Desc: This is a newbie weapon that can be found at random   *
 *       places in Krynn and Ansalon. The weapon improves      *
 *       the smaller the wielder are, giving him or her both   *
 *       speed and improved hit and pen of the weapon.         *
 ***************************************************************/

inherit "/std/weapon";
#include "/d/Ansalon/common/defs.h";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

int pen = 15;
int hit = 15;
int speed = 0;
int type = 0;

string *weaponType = ({ "knife", "sword", "spear", "hammer",
                        "axe"});

string *weaponDesc = ({ "This is a very good newbie knife.\n",
                        "This is a very good newbie sword.\n",
                        "This is a very good newbie spear.\n",
                        "This is a very good newbie hammer.\n",
                        "This is a very good newbie axe.\n"});

create_weapon()
{
    type = random(sizeof(weaponType)); 

    set_name(weaponType[type]);
    set_adj("rune-covered");
    add_adj("steel");
    set_short("rune-covered steel "+ weaponType[type]);
    set_long(weaponDesc[type]);
    set_hit(hit);
    set_pen(pen);

    if (weaponType[type]=="sword")
    {
        set_wt(W_SWORD);
        set_dt(W_SLASH);
    }
    if (weaponType[type]=="axe")
    {
        set_wt(W_AXE);
        set_dt(W_SLASH);
    }
    if (weaponType[type]=="spear")
    {
        set_wt(W_POLEARM);
        set_dt(W_IMPALE);
    }
    if (weaponType[type]=="hammer")
    {
        set_wt(W_CLUB);
        set_dt(W_BLUDGEON);
    }
    if (weaponType[type]=="knife")
    {
        set_wt(W_KNIFE);
        set_dt(W_IMPALE);
    }

    set_hands(W_ANYH);
    set_wf(TO);
    add_prop(OBJ_I_VOLUME, (3600+random(1000)));
    add_prop(OBJ_I_WEIGHT, (3600+random(1000)));
}

mixed
wield(object what)
{
    pen = 65 - ((TP->query_stat(0))/2);
    if (pen <= 24)
        pen = 25;

    hit = 65 - ((TP->query_stat(2))/2);
    if (hit <= 24)
        hit = 25;

    speed = 150 - (TP->query_average_stat());
    if (speed < 0)
        speed = 0;

    set_pen(pen);
    set_hit(hit);
    TP->change_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) + speed);
    TP->update_weapon(TO);

    return 0;
}

mixed
unwield(object what)
{
    TP->change_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) - speed);
    return 0;
}
