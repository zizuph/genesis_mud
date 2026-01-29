/*
 * Axe used by trollshaw trolls and similar to 
 * /d/Shire/common/weapon/trollaxe
 * Thanks to Merrydock for the emote suggestions
 * -- Finwe, September 2001
 */

inherit "/std/weapon";
inherit "/d/Shire/common/lib/tell";
inherit "/lib/keep";
//inherit "/cmd/std/command_driver";


#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include "defs.h"
#include "recover"

#define SHORT   this_object()->query_short()

create_weapon() {
    set_name(({"axe","waraxe"}));
    set_short("huge troll waraxe");
    set_pshort("huge troll waraxes");
    set_adj(({"troll","huge", "steel"}));
    set_long("This is a double bladed axe with a long broad shaft. " +
        "The long broad shaft is made of steel and wrapped with " +
        "leather. The double blades are attached to the top of " +
        "the handle. The axe looks deadly in the right hands. It " +
        "looks like you can swing it.\n");
    add_item(({"blade", "double blades", "axe blades", "blades"}),
        "Two deadly looking blades are attached to the axe. They " +
        "are half moon-shaped and look very sharp.\n");
    add_item(({"shaft", "handle", "broad shaft", "long broad shaft"}), 
        "The handle is made of steel and wrapped with some leather, thereby allowing the wielder a better grip on the handle.\n");
    set_hit(35);
    set_pen(35);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    add_prop(OBJ_I_VOLUME,1150);
    set_keep(0);
    set_hands(W_ANYH);

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
    notify_fail("You must wield the " + SHORT + " first!\n");
    if(!query_wielded())
        return 0;

    notify_fail("Swing what? The axe?\n");
    if(!str)
        return 0;
   
    if(str == "axe" || str == "waraxe")
    {
        switch(SKILL)
        {
            case 90 .. 200:
            write("You balance your " +SHORT+ " in your hand and " +
                "flip it with ease back and forth. Next you " +
                "swing it with great precision through the air " +
                "while flipping the axe in its shaft.\n");
            say(QCTNAME(TP)+" balances "+HIS_HER(TP)+ " "+SHORT+ 
                " in " +HIS_HER(TP)+" hand with ease, then " +
                "swings it with great precision through the air " +
                "while flipping the axe in its shaft.\n");
            break;

            case 70 .. 89:
            write("You swing your "+SHORT+" with great precision "+
                "almost cleaving the air.\n");
            say(QCTNAME(this_player()) + " swings " +HIS_HER(TP)+ 
            " "+SHORT + " with great precision almost cleaving " +
            "the air with it.\n");
            break;
                 
            case 60 .. 69:
            write("You swing your "+SHORT+" through the air " +
                "above your head.\n");
            say(QCTNAME(this_player()) + " swings " +HIS_HER(TP)+ 
                " "+SHORT+ " through the air above " +HIS_HER(TP)+ 
                " head.\n");
            break;
         
            case 50 .. 59:
            write("You balance your "+SHORT+" in your hands and " +
                "flip it back and forth with ease. Next, you make " +
                "a careful swing through the air with it.\n");
            say(QCTNAME(this_player()) + " balances " +HIS_HER(TP)+ 
                " "+SHORT+" in " +HIS_HER(TP)+ " hands with ease " +
                "and then makes a slow swing with it through the air.\n");
            break;
        
            case 40 .. 49:
            write("You swing your "+SHORT+" through the air.\n");
            say(QCTNAME(this_player()) + " swings " +HIS_HER(TP)+ 
                " "+SHORT+" through the air.\n");
            break;
        
            case 30 .. 39:
            write("You swing your "+SHORT+" clumsily in the air " +
                "and almost cut yourself in the attempt.\n");
            say(QCTNAME(this_player()) + " swings " +HIS_HER(TP)+ 
                " "+SHORT+" through the air in an attempt to look " +
                "graceful. Unfortunantely it fails as " +
                QTNAME(this_player()) + " almost cuts " +
                this_player()->query_objective() + "self in the attempt.\n");
            break;
        
            default:
            write("You try to swing your "+SHORT+" through the " +
                "air. The result is devastating. You almost drop " +
                "it on your feet and you injure yourself in the " +
                "attempt!\n");
            say(QCTNAME(this_player()) + " tries to swing " +
                HIS_HER(TP)+" "+SHORT+" through the air. The " +
                "result is devastating. "+QCTNAME(this_player()) + 
                " almost drops the " +SHORT+" on " +HIS_HER(TP)+ 
                " feet and injures "+HIM_HER(TP)+" in the attempt!\n");
           
            this_player()->heal_hp( -(40-SKILL));
            this_player()->add_panic(random(4)+1);
            this_player()->command("drop " + SHORT);
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
