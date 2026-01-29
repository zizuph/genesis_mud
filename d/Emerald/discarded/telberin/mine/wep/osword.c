 
/* mine/wep/osword.c is cloned by mine/npc/chaoslord.c */
 
inherit "/std/weapon";

#pragma save_binary
#include "/d/Emerald/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
 
int gripped = 0;

void
create_weapon()
{
    set_name("sword");
    add_name("longsword");
    set_adj("onyx");
    set_short("onyx longsword");
    set_long("This glittering black sword is made of a magical "+
             "material found only in a few places in the world, onyx. "+
             "It's glittering black blade twinkles like the night sky.\n");
 
    set_default_weapon(29, 28, W_SWORD, W_SLASH, W_LEFT, TO);
    /* Changed from 40, 45 to 29, 28 (good quality broadsword). */
    add_prop(OBJ_I_WEIGHT, 8000 + random(500));
    add_prop(OBJ_I_VOLUME, 1500 + random(200));
    add_prop(OBJ_I_VALUE, 1900 + random(151));
 
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "A glittering black blade looking like a broadsword, you feel " +
            "strong emanations of the enchantment sphere. ",20,  "You feel "+
            "a deep current of strength and transferal within the " +
            "blade.\n",40}));
    add_prop(OBJ_S_WIZINFO,  "This is the blade obtained from "+
             "the chaoslord in the mines of Emerald '/d/Emerald/room/mine"+
             "/maze31'"+
             ". It is a magical weapon but does not extend any special attacks "+
             "to the wielder, although it does possess one magical ability. "+
             "The wielder may grip the hilt tightly, gaining 3-5 points "+ 
             "of strength for a count of 5 or so.  This is possible "+
             "once every 200 or so counts.\n");
}
 
public mixed
wield(object wep)
{
    if(TP->query_skill(SS_WEP_SWORD) < 60)
    {
        return "Something within the sword resists you.\n";
    }
    return 0;
}
 
void renew_grip()
{
    gripped = 0;
}


int do_grip(string str)
{
    if(!str) return 0;
    NF("Grip what?\n");
    if(str == "hilt" || str == "hilt tightly")
    {
        if(str == "hilt tightly" && !gripped && TO->query_wielded())
        {
            write("You feel strength flow into your body as you "+
                  "grip the hilt of the "+short()+" tightly.\n");
            say(QCTNAME(TP)+" grips the hilt of the "+short()+" tightly.\n");
            set_alarm(200.0,0.0,"renew_grip");
            gripped = 1;
            TP->add_tmp_stat(SS_STR,3+random(3),5);
            return 1;
        }
        else if(str == "hilt tightly" && (gripped || !TO->query_wielded()))
        {
            write("You grip the hilt of the "+short()+" tightly.\n");
            say(QCTNAME(TP)+" grips the hilt of the "+short()+" tightly.\n");
            return 1;
        }
        else
            write("You grip the hilt of the "+short()+".\n");
        say(QCTNAME(TP)+" grips the hilt of the "+short()+".\n");
        return 1;
    } 
    return 0;
}


void init()
{
    ::init();
    add_action("do_grip","grip");
}
