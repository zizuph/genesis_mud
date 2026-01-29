/*
 * Axe used by Moria trolls and similar to 
 * /d/Shire/common/trollsh/weapon/trollaxe
 * Thanks to Merrydock for the emote suggestions
 * -- Finwe, September 2001
 * Converted to 2 handed to conform to current standards
 * -- Finwe, Feburary 2002
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

#define SHORT   this_object()->query_short()

create_weapon() {
    set_name(({"axe","waraxe"}));
    set_short("huge dwarven waraxe");
    set_pshort("huge dwarven waraxes");
    set_adj(({"dwarven","huge", "steel"}));
    set_long("This "+short()+" is made of steel and appears to be quite " +
        "ancient looking. The long broad shaft is made of smooth oak " +
        "and has an impressive blade set on its top. The handle is " +
        "wrapped with leather to give it a better grip when wielded. It " +
        "looks like you can swing the blade with great precision.\n");
    add_item("blade",
        "The blade is curved and double edge. It look sharp and " +
        "deadly even though there are some small notches in " +
        "the blade.\n");
    add_item("notches",
        "The notches are small, scattered across the blade. " +
        "There are only a couple of them and don't affect the " +
        "effectiveness of the blade. It still looks deadly.\n");
    add_item(({"shaft", "handle", "broad shaft", "long broad shaft"}), 
        "The handle is made of oak. The handle is strapped with " +
        "leather for a better grip when wielding this huge waraxe.\n");
    set_hit(35);
    set_pen(35);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    add_prop(OBJ_I_VOLUME,1150);
    set_keep();

}

int
query_hands()
{
find_player("lavellan")->catch_tell("Axe " + file_name(this_player()) + "\n");
    if(!this_player()) return W_BOTH;
    if(STR(TP)>50) return W_ANYH;
    else return W_BOTH;
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
