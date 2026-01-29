/* 
 * Cart used by hobbit for push cart quest
 * Finwe, January 2005
 */

#include "defs.h"
#include "qbits.h"
#include <cmdparse.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/object";
inherit QUESTMASTER;

#define CART_DIR    OBJ_DIR
#define CART_QUEST_PROP "_fix_cart_quest_"

int wheel_fixed = 1,
    in_mud = 0, 
    has_supplies = 0, 
    min_str = 45,
    min_dex = 45;

public int check_supplies();
void fix_wheel(object player, int stage);


void
create_object()
{
    FIXEUID;
    set_name("cart");
    set_adj("wooden");
    set_short("wooden cart");
    set_long("@@long_descr@@\n");
    add_item(({"pony"}),
        "This pony is smaller than most. It is dark gray with a shaggy " +
        "mane and tail. It is sturdy looking and connected to the front " +
        "of the cart.\n"); 
    add_item(({"wheel", "wagon wheel", "cart wheel"}), 
        "@@wheel_descr@@\n");        

    add_prop(OBJ_I_NO_GET, 1);          /* Not gettable       */
    add_prop(CONT_I_LIGHT, 1);
    add_prop(CONT_I_IN,1);              /* It's a container!  */
    add_prop(CONT_I_RIGID,1);           /* A rigid object     */
    add_prop(CONT_I_TRANSP,0);          /* Not transparant    */
    add_prop(CONT_I_MAX_VOLUME,200000); /* Can contain 20 Ltr */
    add_prop(CONT_I_MAX_WEIGHT,200000); /* Can contain 20 Kg */

    add_prop(OBJ_I_VALUE, 0);

}
void
init()
{
    ::init();

    add_action("push_cart", "push");
    add_action("check_wheel", "fix");
    add_action("check_wheel", "repair");
    add_action("check_wheel", "mend");
}

int push_cart(string str)
{
    int stat;

    stat = TP->query_stat(SS_STR);
    
    if(wheel_fixed == 0 )
    {
        write("One of the wheels is broken. You can't push it out of " +
            "the mud without fixing it first.\n");
        return 1;
    }

    if(wheel_fixed == 1)
    {    

        if(str == "wagon" || str == "cart")
        {
// if player didn't repair cart, they won't get exp for just pushing it.
/*
            if(!TP->query_prop(CART_QUEST_PROP)) 
                                                 
                {
                    write("Since you didn't repair the cart, you spook " +
                        "the pony. It jumps and whinnies loudly, running " +
                        "away with the cart clattering behind it.\n");
                    say(QCTNAME(TP) + " spooked the pony. It suddenly " +
                        "jumps away and whinnies loudly, running away with " +
                        "the cart clattering behind it.\n");
                    TO->remove_object();
                    return 1;
                }
*/
            if (stat >=min_str)
            {

                write("You pushed the cart successfully out of the mud!\n");
                in_mud = 1;

                if(TP->test_bit("shire", GROUP1, CART_QUEST_BIT))

                {
                    write("You suddenly realize you have done this before.\n");
                    write("The pony jumps and dashes off with the cart " +
                        "clattering behind it.\n");
                    say(QCTNAME(TP) + " pushes the " + short() + ". The pony " +
                        "jumps and dashes off with the cart clattering " +
                        "behind it.\n");
                    TO->remove_object();
                    return 1;
                }
                TP->remove_prop(CART_QUEST_PROP);
                write("The pony whinnies and trots away.\n");
                say(QCTNAME(TP) + " pushes the cart. The pony whinnies " +
                    "and trots away.\n");
                TP->catch_msg("You feel more experienced.\n");
                TP->set_bit(GROUP1, CART_QUEST_BIT);
                TP->add_exp_quest(CART_QUEST_EXP);
                log_quest(TP, CART_QUEST_LNG, CART_QUEST_BIT, CART_QUEST_EXP);
                set_alarm (0.0, 0.0, &remove_object ());
                return 1;
            }
            else 
            {
                write("You grunt and groan, but are too weak to push " +
                    "the cart.\n");
                return 1;
            }
        }
        NF("Push what, maybe the cart?\n");
        return 0;
    }
}

string
long_descr()
{
    string long_desc = "This is a wooden cart. It is rectangular shaped " +
        "and used by to transport goods and supplies by a farmer. It looks " +
        "like it was abandoned by the owner, who is probably off trying " +
        "to get help. " ;
        
    if(in_mud == 0)
    {
        long_desc += "The front is connected to a pony, which is struggling " +
        "to pull the cart free. The back end of the cart is stuck in the mud.";
    }
    else
    {
        long_desc += "It is free of the mud.";
    }

    return long_desc;
}

string
wheel_descr()
{
    string wheel_check = "The wheel is large and made of wood. " ;
        
    if(wheel_fixed == 0)
    {
        wheel_check += "It is broken and in need of repair. A long piece " +
        "of metal would probably fix it good enough.";
    }
    else
    {
        wheel_check += "It has a strip of iron wrapped around it holding " +
        "the wheel together. This will do until a new wheel is found and " +
        "put on the cart.";
    }

    return wheel_check;
}

public int check_supplies()
{
    object nails, hammer, band;
    has_supplies = 0;

// check to see if player has all the items
    if (!objectp(hammer = present("hammer", TP)))
        write("You don't have the tools to fix the wheel.\n");
    else
        has_supplies++;
    
    if (!objectp(nails = present("_shire_nails", TP)))
        write("You don't have the supplies needed to fix the wheel.\n");
    else
        has_supplies++;

    if (!objectp(band = present("_shire_iron_band", TP)))
        write("You don't have anything to repair the wheel with.\n");
    else
        has_supplies++;

}

int check_wheel(string str)
{
    int stat_str, stat_dex;

    stat_str = TP->query_stat(SS_STR);
    stat_dex = TP->query_stat(SS_DEX);

//    if (!parse_command(str, TP, " [the] [broken] [wagon] [cart] [wheels] 'cart' / " +
//        "'wagon'"))

    if((str !="broken wheel"))
    {
        write("Fix what, the broken wheel?\n");
        return 1;
    }

    if( (stat_str < min_str) && (stat_dex < min_dex) )
    {
        write("You lack the understanding to fix the cart.\n");
        return 1;
    }

    if(wheel_fixed == 1)
    {
        write("You do not see any problems with the wheels.\n");
        return 1;
    }
    check_supplies();
    if(has_supplies !=3) return 1;




// let's fix this mama jama.
    TP->add_prop(CART_QUEST_PROP,1);
    write("You examine the wheel carefully and find a break in it.\n");
    say(QCTNAME(TP)+ " examines the wheel on the cart and finds a break.\n",TP);
    set_alarm(2.0,0.0,&fix_wheel(TP,1));
    return 1;
}


void
fix_wheel(object player, int stage)
{
    float time;
    object nails, band;

    nails = present("_shire_nails", TP);
    band = present("_shire_iron_band", TP);


    switch (stage)
    {
        case 1:
            write("You take the strip of iron, place it over the break, " +
                "and hammer it onto the wheel.\n");
            say(QCTNAME(TP)+ " takes the strip of iron, places it over the " +
                "break, and hammers it onto the wheel.\n",TP);
            time = 5.0;
            break;
        case 2:
            write("...Tap..Tap....Tap..Tap....Tap..Tap....Tap..Tap...\n");
            say("...Tap..Tap....Tap..Tap....Tap..Tap....Tap..Tap...\n",TP);
            time = 4.0;
            break;
        case 3:
            write("You wrap the strip of iron around the wheel completely " +
                "and hammer it in place.\n");
            say(QCTNAME(TP)+ " wraps the strip of iron around the wheel " +
                "completely and hammers it in place.\n",TP);
            time = 4.0;
            break;
        case 4:
            write("...Tap..Tap....Tap..Tap....Tap..Tap....Tap..Tap...\n");
            say("...Tap..Tap....Tap..Tap....Tap..Tap....Tap..Tap...\n",TP);
            time = 3.0;
            break;
        case 5:
            write("You spin the wheel around several times to make sure " +
                "it's fixed.\n");
            say(QCTNAME(TP)+ " spins the wheel around several times to " +
                "make sure it's fixed.\n",TP);
            time = 2.0;
            break;
        case 6:
            write("You step back admiring your completed work.\n");
            say(QCTNAME(TP)+ " steps back and admires " + HIS_HER(TP) + 
                " completed work.\n",TP);
            time = 1.0;
            break;
        case 7:
            nails->remove_object();
            band->remove_object();
            wheel_fixed = 1;
            has_supplies = 0;
           return;
    }
    
    set_alarm(time, 0.0, &fix_wheel(player, ++stage));

}    
