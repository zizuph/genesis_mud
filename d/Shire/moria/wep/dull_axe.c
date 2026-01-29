/*
 * Another axe used by Moria trolls. 
 * Once used by dwarves of moria, the axe is now mangled and in 
 * poor shape but still deadly.
 * -- Finwe, February 2002
 * Thanks to Merrydock for the emote suggestions
 * -- Finwe, September 2001
 */
inherit "/std/weapon";
inherit "/d/Shire/common/lib/tell";
inherit "/lib/keep";
inherit "/cmd/std/command_driver";


#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include "defs.h"
#include "recover"

#define HIT 39
#define PEN 39

create_weapon()
{
    set_name(({"axe","dwarven"}));
    set_short("dull-colored dwarven axe");
    set_adj(({"dull-colored","dwarven", "steel"}));
    set_long("This axe was forged of steel and by dwarves long " +
        "ago. However, it has been misused and probably " +
        "looted from an armoury or a corpse. The handle is " +
        "made of wood and wrapped with criss-cross straps of " +
        "leather for better grip. The double blades are attached " +
        "to the top of the handle with a sharp point at the top " +
        "of the handle.\n");
    add_item(({"blade", "double blades", "blades"}),
        "The blades are curved and double edge. Once they look " +
        "like they were cared for and full of life. Now, whatever " +
        "magic was embued into the blades is gone forever, leaving " +
        "them dull-colored. Still, the blades look sharp and deadly " +
        "in the right hands.\n");
    add_item(({"shaft", "handle", "broad shaft", "long broad shaft"}), 
        "The handle is made of wood, wrapped with leather in a " +
        "criss-cross fashion. The leather provides a better grip " +
        "when wielding this huge axe.\n");
    add_item(({"point", "sharp point"}),
        "The sharp point at the top of the axe extends a hand's " +
        "length, making the axe more dangerous. The point is " +
        "sharpend and is used by skilled warriors for slashing " +
        "their opponents.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_VOLUME,1150);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(20) -10);
    set_hands(W_ANYH);

    set_keep(0);
}

void
init()
{
   /*******************************************
    *  PLEASE ADD EMOTES IN ALPHABETIC ORDER  *
    *******************************************/
    
   ::init();

   add_action("swing_axe","swing");
}

int
swing_axe(string str) 
{
    int SKILL = this_player()->query_skill(SS_WEP_AXE);
    notify_fail("You must wield the " +short()+" first!\n");
    if(!query_wielded())
        return 0;

    notify_fail("Swing what? The axe?\n");
    if(!str)
        return 0;
   
    if(str == "axe")
    {
        switch(SKILL)
        {
            case 90 .. 200:
            write("You balance your " +short()+ " in your hand and " +
                "flip it with ease back and forth. Next you " +
                "swing it with great precision through the air " +
                "while flipping the axe in its shaft.\n");
            say(QCTNAME(TP)+" balances "+HIS_HER(TP)+ " "+short()+ 
                " in " +HIS_HER(TP)+" hand with ease, then " +
                "swings it with great precision through the air " +
                "while flipping the axe in its shaft.\n");
            break;

            case 70 .. 89:
            write("You swing your "+short()+" with great precision "+
                "almost cleaving the air.\n");
            say(QCTNAME(this_player()) + " swings " +HIS_HER(TP)+ 
            " "+short() + " with great precision almost cleaving " +
            "the air with it.\n");
            break;
                 
            case 60 .. 69:
            write("You swing your "+short()+" through the air " +
                "above your head.\n");
            say(QCTNAME(this_player()) + " swings " +HIS_HER(TP)+ 
                " "+short()+ " through the air above " +HIS_HER(TP)+ 
                " head.\n");
            break;
         
            case 50 .. 59:
            write("You balance your "+short()+" in your hands and " +
                "flip it back and forth with ease. Next, you make " +
                "a careful swing through the air with it.\n");
            say(QCTNAME(this_player()) + " balances " +HIS_HER(TP)+ 
                " "+short()+" in " +HIS_HER(TP)+ " hands with ease " +
                "and then makes a slow swing with it through the air.\n");
            break;
        
            case 40 .. 49:
            write("You swing your "+short()+" through the air.\n");
            say(QCTNAME(this_player()) + " swings " +HIS_HER(TP)+ 
                " "+short()+" through the air.\n");
            break;
        
            case 30 .. 39:
            write("You swing your "+short()+" clumsily in the air " +
                "and almost cut yourself in the attempt.\n");
            say(QCTNAME(this_player()) + " swings " +HIS_HER(TP)+ 
                " "+short()+" through the air in an attempt to look " +
                "graceful. Unfortunantely it fails as " +
                QTNAME(this_player()) + " almost cuts " +
                HIS_HER(TP) + "self in the attempt.\n");
            break;
        
            default:
            write("You try to swing your "+short()+" through the " +
                "air. The result is devastating. You almost drop " +
                "it on your feet and you injure yourself in the " +
                "attempt!\n");
            say(QCTNAME(this_player()) + " tries to swing " +
                HIS_HER(TP)+" "+short()+" through the air. The " +
                "result is devastating. "+QCTNAME(this_player()) + 
                " almost drops the " +short()+" on " +HIS_HER(TP)+ 
                " feet and injures "+HIM_HER(TP)+" in the attempt!\n");
           
            this_player()->heal_hp( -(40-SKILL));
            this_player()->add_panic(random(4)+1);
            this_player()->command("drop " + short());
            if(this_player()->query_hp() <= 0)
            {
                this_player()->command("wince");
                this_player()->set_hp(1);
            }
            break;
        }
        return 1;
    }
    return 0;
}
