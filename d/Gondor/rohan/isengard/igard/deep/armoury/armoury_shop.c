/*
 *  IGARD_DEEP_ARMOURY + "armoury_shop.c"
 *
 *  The armoury shop of Isengard.
 *    Modified from Gondor shops coded by others.
 *
 *  Last modified by Alto, 27 November 2001
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/lib/shop.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

public void        set_standard_equip(mixed x);
public int         do_buy(string args);
public int         do_list(string args);
public int         do_show(string str);

public string      long_func();
public void        set_standard_equip(mixed x);

object             clone_it(string str);
object             *clone_and_buy_it(string str1, string str2, string str3);
static string      *standard_equip;
public int         spring_trap();
public int	        catch_all(string str);
static object      Squad, Squad2, Squad3;


/* Below are defines for the standard armour objects for sale in the shop */

#ifndef SHOP_ITEMS
#define SHOP_ITEMS 1
#define I_BRACERS           IGARD_ARM + "i_bracers"
#define I_CHAINMAIL         IGARD_ARM + "i_chainmail"
#define I_HELMET            IGARD_ARM + "i_helmet"
#define I_LEATHER           IGARD_ARM + "i_leather"
#define I_GREAVES           IGARD_ARM + "i_greaves"
#define I_SHIELD            IGARD_ARM + "i_shield"
#define I_SHOES             IGARD_ARM + "i_shoes"
#define I_GCHAIN            IGARD_ARM + "igard_gchainmail"
#define I_GHELM             IGARD_ARM + "igard_ghelmet"
#define I_GSHIELD           IGARD_ARM + "igard_gshield"
#define IGARD_FOUND_EVIDENCE      "_igard_found_evidence"
#endif

#define IGARD_SHOP_ITEMS  ({ I_BRACERS, I_CHAINMAIL, I_HELMET, I_LEATHER, I_GREAVES, I_SHIELD, I_SHOES, I_GCHAIN, I_GHELM, I_GSHIELD })
#define STORE_ROOM    IGARD_DEEP_ARMOURY + "store_room"


public void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_long(long_func);
    set_short("The Armoury of Isengard");
    set_shop_name("The Armoury of Isengard");
    set_standard_equip(IGARD_SHOP_ITEMS);
    set_keeper_file(IGARD_NPC + "shopkeeper");

    add_item(({"shop", "armoury", "room", "surroundings"}), long_func);

    add_item(({"rock", "black rock", "stone"}), "This area is delved "
        + "into the black rock of Isengard, which is in places natural and "
        + "in others carved by the hands of Men.\n");
    add_item(({"isengard", "fortification"}), "You are somewhere below "
        + "the fortification of Isengard.\n");
    add_item(({"plain", "great plain", "plain of isengard", 
        "great plain of isengard"}), "It is somewhere above you.\n");
    add_item(({"wall", "walls"}), "The walls are delved from black rock "
        + "beneath the plain of Isengard. The rock glistens in the guttering "
        + "torchlight.\n");
    add_item(({"ceiling", "roof"}), "The ceiling is smooth and solid "
        + "black rock that arches high above your head. It seems unbreakable "
        + "and timeless.\n");
    add_item(({"floor", "ground"}), "The floor here is made from black "
        + "rock and worn smooth by tens of thousands of booted feet over "
        + "many long years.\n");
    add_item(({"torch", "torches"}), "Torches are mounted in iron "
        + "brackets set into the walls. They gutter and "
        + "hiss as the wind of your passing stirs them.\n");
    add_item(({"bracket", "iron bracket", "brackets", "iron brackets"}), 
        "Set into the walls, iron brackets bear torches "
        + "that gutter and hiss in the wind of your passing.\n");
    add_item(({"depths", "depths of isengard"}), "All around you the "
        + "depths of Isengard creak and groan.\n");
    add_item(({"hook", "hooks"}), "Sturdy bronze hooks are mounted on the "
        + "circular walls of the room. Armours hang from almost all of "
        + "them.\n");
    add_item(({"rack", "racks"}), "Wooden and iron racks are stuffed into "
        + "almost every available space in the room. They are filled with "
        + "pieces of armour.\n");
    add_item(({"case", "cases"}), "Many large cases surround you, all "
        + "stuffed with smaller pieces of armoured gear.\n");
    add_item(({"shelf", "shelves"}), "The walls of the room are lined with "
        + "numerous shelves, all filled to capacity with armours.\n");
    add_item(({"armour", "armours", "pieces", "pieces of armour", "gear"}),
        "There are pieces of armour crammed into every conceivable space "
        + "in this room. To see what is available, you should <list armours> "
        + "for a comprehensive list.\n");

    add_item(({"plaque", "large plaque", "sign"}), &exa_poster());
    add_item(({"word", "words"}), "Why don't you try reading them?\n");
    add_cmd_item(({"plaque", "large plaque", "words", "sign"}), 
        "read", &exa_poster());

    add_exit(IGARD_DEEP_ARMOURY + "entry_stair7",        "south");

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}


public string
long_func()
{
    string  longtxt;

    longtxt = 
        "This is the Armoury of Isengard. It is a huge circular room spanning "
        + "fifty yards in all directions. Stacked upon a multitude of hooks, "
        + "racks, cases and shelves are thousands of pieces of armour. Only "
        + "an army preparing for war would need such protection. Despite the "
        + "size of the room and the arched ceiling, the room has a rather "
        + "cramped feeling to it. "
        + "There is large plaque on the wall next to the doorway.\n"; 

    return longtxt;
}



public void
set_standard_equip(mixed x)
{
    if (stringp(x))
        standard_equip = ({ x });
    else if (pointerp(x))
        standard_equip = x;
    else
        standard_equip = IGARD_SHOP_ITEMS;
}


object
clone_it(string str)
{
    int n, s;
    object ob;
    string *s_arr,
        *adjs;

    seteuid(getuid());

    s_arr = explode(str, " ");
    if ((s = sizeof(s_arr)) > 1)
        str = s_arr[s - 1];
    s_arr -= ({ str });
    --s;
    n = -1;
    while (++n < sizeof(standard_equip) && !objectp(ob))
    {
        if (standard_equip[n]->id(str))
        {
            adjs = standard_equip[n]->query_adjs();
            if (!s || (s == sizeof(adjs & s_arr)))
                ob = clone_object(standard_equip[n]);
        }
    }
    return ob;
}


object *
clone_and_buy_it(string str1, string str2, string str3)
{
    int price, i, j, k, n,
        num = sizeof(query_money_types()),
        *value_arr = allocate(2 * num),
        *arr, error, err;
    object ob;

    if (!strlen(str1))
	       return 0;

    ob = clone_it(str1);
    if (!objectp(ob))
    {
       	return 0;
    }

    price = query_buy_price(ob);
  
    if (err = ob->move(this_player()))
    {
        shop_hook_buy_cant_carry(ob, err);
        ob->remove_object();
        return 0;
    }
  
    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
    {
        shop_hook_buy_cant_pay(ob, arr);
        ob->remove_object();
        return 0;
    }
  
    if (error = arr[sizeof(arr) - 1])
    {
        if (error < -1)
        {
            /* Couldn't take the money from player, the coins were stuck */
            shop_hook_buy_magic_money(ob);
            ob->remove_object();
        }
        /* We don't want the money so no move error to us, if there was one
           it was because the player couldn't hold all coins, and if so the
           drop text is already written, but the deal is still on :) */
    }
  
    for (k = 0; k < 2 * num; k++)
        value_arr[k] += arr[k];
  
    if (objectp(ob))
        shop_hook_buy_pay_money(
            text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));
  
    return ({ ob });
}


public int
do_buy(string args)
{
    int     res;
    object *item;
    string  str, str2, str3;
  
    if (!args || args == "")
    {
        NF("The shopkeeper says: Buy what? Grrrr!\n");
        return 0;
    }

    if (sscanf(args,"%s for %s and get %s", str, str2, str3) != 3)
    {
        str3 = "";
	       if (sscanf(args,"%s for %s", str, str2) != 2)
        {
	            str2 = "";
	            str = args;
        }
    }

    if (res = ::do_buy(args))
        return res;

    else
    {
	       item = clone_and_buy_it(str,str2,str3);
	           if (sizeof(item))
            return shop_hook_bought_items(item);
        else
            return 0;
    }
    return 0;
}


public int
do_list(string args)
{
    string list_txt;
    int n, s;
       if (args != "armours" && args)
           return ::do_list(args);
       else if (!args || args == "")
           {
               ::do_list(args);
               write(" --- Please <list armours>\n");
               return 1;
           }
       write("Armours in stock: \n\n"+
           "-----------------------------------------------------------\n");
           s = sizeof(standard_equip);
           while (n < s)
              {
              call_other(standard_equip[n], "load_me");
              /*
              shop_hook_list_object(find_object(standard_equip[n]),
              standard_equip[n]->query_prop(OBJ_I_VALUE));
              */
              shop_hook_list_object(find_object(standard_equip[n]),
              query_buy_price(find_object(standard_equip[n])));
              n++;
              }
       write("-----------------------------------------------------------\n");
       return 1;
}


public int
do_show(string str)
{
    object ob;

    if (!str || str == "")
    {
        NF("The shopkeeper says: Show what?\n");
        return 0;
    }

    if (::do_show(str))
	       return 1;

    if (!objectp(ob = clone_it(str)))
       	return 0;

    shop_hook_appraise_object(ob);
    ob->appraise_object();
    ob->remove_object();
    return 1;
}


public string
exa_poster()
{
    return "\n"
+" -------------------------------------------------------------------\n"
+"| _____________        ___  A R M O U R Y    ____________        _  |\n"
+"||                                                                | |\n"
+"||   To view the armours in stock, <list armours>                   |\n"
+"||                                                                  |\n"
+"||   To purchase one of our fine items, <buy> the armour of         |\n"
+"|    your choice.                                                 | |\n"
+"|                                                                 | |\n"
+"|    You may also <value> and <sell> some items here, but         | |\n"
+"||   we will keep anything we buy, so you had better mean it.     | |\n"
+"||                                                                  |\n"
+"||   Note also that we SELL armours, we have no need for            |\n"
+"||   buying them!                                                 | |\n"
+"|                                   ------------------------------  |\n"
+" -------------------------------------------------------------------\n";
}


public void
spring_trap()
{
    int toughness;
    object trappee;
    string alertphrase, alertphrase2, alertphrase3;

    trappee = TP;
    toughness = TP->query_average_stat();

    switch(random(5))
    {
        case 0:
            alertphrase  = "Hey look! Its a filthy spy!";
            alertphrase2 = "Get it! Get it! Don't let it get away!";
            alertphrase3 = "Lets kill it, no need for a trial.";
            break;
        case 1:
            alertphrase  = "A spy!";
            alertphrase2 = "Catch it quick!";
            alertphrase3 = "I'll make it feel welcome, oh yes!";
            break;
        case 2:
            alertphrase  = "Hmm. It seems we have a spy in our midst.";
            alertphrase2 = "Must be the one the Boss sent us to look for?";
            alertphrase3 = "It would be easiest to just kill it now.";
            break;
        case 3:
            alertphrase  = "Look what I found!";
            alertphrase2 = "That's a spy if I ever saw one!";
            alertphrase3 = "Get it! Get it! Don't let it escape!";
            break;
        case 4:
            alertphrase  = "Arrrrgh! This maggot is a spy!";
            alertphrase2 = "Kill it! Kill it!";
            alertphrase3 = "We have it now!";
            break;
        case 5:
            alertphrase  = "That was almost too easy!";
            alertphrase2 = "What a pathetic spy!";
            alertphrase3 = "Let us not bother the Boss with it. Kill it now!";
            break;
        default:
            break;
    }

    
    if (!objectp(Squad))
    {

    switch (toughness)
    {
    case 0..20:
        Squad = clone_object(IGARD_NPC + "igard_orc.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();
        break;
    case 21..40:
        Squad = clone_object(IGARD_NPC + "igard_orc.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_orc2.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();
        break;
    case 41..60:
        Squad = clone_object(IGARD_NPC + "igard_orc3.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_orc4.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();
        break;
    case 61..80:
        Squad = clone_object(IGARD_NPC + "igard_orc2.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_orc3.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_orc4.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase3);
        Squad2->ambush_retreat();
        break;
    case 81..100:
        Squad = clone_object(IGARD_NPC + "igard_orc3.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_orc4.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase3);
        Squad2->ambush_retreat();
        break;
    case 101..120:
        Squad = clone_object(IGARD_NPC + "igard_orc4.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_orc4.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase3);
        Squad2->ambush_retreat();
        break;
    case 121..140:
        Squad = clone_object(IGARD_NPC + "igard_orc4.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase3);
        Squad2->ambush_retreat();
        break;
    default:
        Squad = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase3);
        Squad2->ambush_retreat();
        break;
    }
    return;
    }
}

public int 
catch_all(string str)
{
    string  vb = query_verb();
    object trappee;
    trappee = TP;

    TO->remove_item("net");

    if (!AMBUSHED) 
        return 0;

    if (!TP->query_enemy() || !TP->query_attack())
    {
    TP->remove_prop(IGARD_AMBUSHED);
    TO->remove_item("net");

    write("You finally work your way out of the meshing by ripping "
        + "it to shreds!\n");
    tell_room(environment(trappee), QCTNAME(trappee) + " finally works "
        + HIS_HER(trappee) + " way out of the meshing by ripping it to "
        + "shreds!\n", ({trappee}));

    return 0;
    }
    
    add_item(({"net", "netting", "mesh", "meshing"}), "The netting "
        + "is not all that tough, but it is so gnarled and stretched "
        + "that it is almost impossible to break out of.\n");

    switch (vb)
    {
    case "north":
    case "northeast":
    case "northwest":
    case "southwest":
    case "southeast":
    case "west":
    case "up":
    case "down":
    case "south":
    case "east":
        WRITE("You are tangled in meshing and cannot seem to break away!");
        return 1;
        break;
    default:
        return 0;
    }
}

public int
initiate_trap()
{
    add_action(catch_all, "", 1);
}

public void
find_evidence(object player)
{
    setuid();
    seteuid(getuid());
    
    if (player->query_prop(IGARD_FOUND_EVIDENCE))
        {
        return;
        }
    
    write("You find a discarded invoice on the floor and pick it up!\n");

    clone_object(IGARD_OBJ + "i_evidence_obj.c")->move(player);
    
    player->add_prop(IGARD_FOUND_EVIDENCE, 1);

}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob) && ob->query_prop(IGARD_EVIDENCE_TOURING))
     find_evidence(ob);

}
