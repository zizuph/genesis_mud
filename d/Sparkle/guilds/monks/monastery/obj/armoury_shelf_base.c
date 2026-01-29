/*******************************************************************\
| ARMOURY_SHELF_BASE.C                                              |
\*******************************************************************/

/*
 * 20181020 Ckrik switch to list view
 * 03/09/12 Arandir     Created
 * 10/10/21 Lavellan    Modified for new saving rack system.
 *          Inherited by individual racks now, not all clones of same object.
 *
 */

#pragma no_clone

#include <language.h>

#include <macros.h>     //for IS_CLONE
#include <stdproperties.h>
#include <wa_types.h>
#include <files.h>

#include "../defs.h"

inherit DG_OBJ_TABLE_BASE;
inherit "/d/Genesis/specials/lib/item_recovery_lib.c";

//-------------------------------------------------------------------

/*
 * Function name : m_configure_shelf
 * Descriptions  : Sets basic characteristics of the shelf
 *
 */

void m_configure_shelf(
    string *asAdj,
    string sShort,
    string sPrefix)
{
    add_adj (asAdj);
    set_short (sShort);
    dg_set_description_prefix (sPrefix);
}


/*
 * Function name : create_container
 *
 */

void create_container ()
{
    ::create_container ();

    set_name("shelf");
    set_adj(({ "wooden", "armoury" }));

    set_long("The wooden shelf is made of thick and rough " +
              "oak boards, anchored at both ends in the " +
              "stone walls. An extra beam of the same " +
              "wood supports the boards in the middle, " +
              "making the entire structure look sturdy " +
              "indeed.\n");

    add_prop(CONT_I_MAX_WEIGHT, 4000000);
    add_prop(CONT_I_MAX_VOLUME, 4000000);

    if (IS_CLONE)
    {
        set_enable_logging(0);
        set_enable_recovery(1);
        init_database();
        set_alarm(0.0, 0.0, &recover_objects_from_database()); 
    }
}

//-------------------------------------------------------------------

void enter_inv(object oWhat, object oFrom)
{
    ::enter_inv(oWhat, oFrom);
    environment()->m_observe_drop(oFrom, oWhat);
    if (oFrom == this_object())
    {
        return;
    }
    add_rack_entry(oWhat);
}


void leave_inv (object oWhat, object oWhere)
{
    ::leave_inv(oWhat, oWhere);
    environment()->m_observe_take(oWhere, oWhat);
  
  
    if (oWhere == this_object())
    {
        // Not actually leaving this container, just return
        return;
    }
    remove_rack_entry(oWhat);
}

int sort_generic(object *a, object *b, function rank)
{
    if (rank(a[0]) < rank(b[0]))
    {
        return -1;
    }
    if (rank(a[0]) > rank(b[0]))
    {
        return 1;
    }
    if (a[0]->short() < b[0]->short())
    {
        return -1;
    }
    if (a[0]->short() > b[0]->short())
    {
        return 1;
    }
    return 0;
}

int score_weapon(object ob)
{
    if (ob->is_earthsea_unarmed_enhancer())
    {
        return W_JAVELIN + 1000;
    }
    return ob->query_wt();
}

int sort_weapon(object *a, object *b)
{
    return sort_generic(a, b, &score_weapon());
}

int score_armour(object ob)
{
    switch(ob->query_at())
    {
        case A_ARMS: return 1;
        case A_L_ARM: return 1;
        case A_R_ARM: return 1;
        case W_LEFT: return 1;
        case W_RIGHT: return 1;
        case A_BACK: return 6;
        case A_BODY: return 2;
        case A_TORSO: return 2;
        case A_FEET: return 7;
        case A_L_FOOT: return 7;
        case A_R_FOOT: return 7;
        case A_EARS: return 8;
        case A_L_EAR: return 8;
        case A_R_EAR: return 8;
        case A_FINGERS: return 12;
        case A_ANY_FINGER: return 12;
        case A_L_FINGER: return 12;
        case A_R_FINGER: return 12;
        case A_HANDS: return 11;
        case A_L_HAND: return 11;
        case A_R_HAND: return 11;
        case A_HEAD: return 0;
        case A_LEGS: return 3;
        case A_NECK: return 9;
        case A_ROBE: return 4;
        case A_SHIELD: return 5;
        case A_SHOULDERS: 10;
        case A_L_SHOULDER: 10;
        case A_R_SHOULDER: 10;
        case A_WRISTS: return 13;
        case A_L_WRIST: return 13;
        case A_R_WRIST: return 13;
        case A_WAIST: return 14;
        case A_L_HIP: return 15;
        case A_L_HIP: return 15;
        case A_L_ANKLE: return 16;
        case A_R_ANKLE: return 16;
        default: return 17;
    }
}

int sort_armour(object *a, object *b)
{
    return sort_generic(a, b, &score_armour());
}

int score_other(object ob)
{
    if (function_exists("create_arrow", ob))
    {
        return 0;
    }
    if (IS_WEARABLE_OBJECT(ob))
    {
        return 1;
    }
    if (IS_HERB_OBJECT(ob))
    {
        return 10;
    }
    if (IS_POTION_OBJECT(ob))
    {
        return 20;
    }
    if (IS_DRINK_OBJECT(ob))
    {
        return 30;
    }
    if (ob->id("leftover"))
    {
        return 40;
    }
    if (IS_FOOD_OBJECT(ob))
    {
        return 50;
    }
    if (IS_KEY_OBJECT(ob))
    {
        return 60;
    }
    if (IS_TORCH_OBJECT(ob))
    {
        return 70;
    }
    if (ob->id("vial"))
    {
        return 100;
    }
    if (IS_COINS_OBJECT(ob))
    {
        return 1000;
    }
    if (ob->query_gem())
    {
        return 2000;
    }
    return 10000;
}

int sort_other(object *a, object *b)
{
    return sort_generic(a, b, &score_other());
}

string render_weapon_type(object ob)
{
    if (ob->is_earthsea_unarmed_enhancer())
    {
        return "unarmed";
    }
    switch(ob->query_wt())
    {
        case W_SWORD: return "sword";
        case W_AXE: return "axe";
        case W_KNIFE: return "knife";
        case W_CLUB: return "club";
        case W_POLEARM: return "polearm";
        case W_MISSILE: return "missile";
        case W_JAVELIN: return "javelin";
        default: return "-";
    }
}

string render_armour_type(object ob)
{
    switch(ob->query_at())
    {
        case A_ARMS: return "arms";
        case A_L_ARM: return "arms";
        case A_R_ARM: return "arms";
        case W_LEFT: return "arms";
        case W_RIGHT: return "arms";
        case A_BACK: return "back";
        case A_BODY: return "torso";
        case A_TORSO: return "torso";
        case A_FEET: return "feet";
        case A_L_FOOT: return "feet";
        case A_R_FOOT: return "feet";
        case A_EARS: return "ears";
        case A_L_EAR: return "ears";
        case A_R_EAR: return "ears";
        case A_FINGERS: return "ring";
        case A_ANY_FINGER: return "ring";
        case A_L_FINGER: return "ring";
        case A_R_FINGER: return "ring";
        case A_HANDS: return "hands";
        case A_L_HAND: return "hands";
        case A_R_HAND: return "hands";
        case A_HEAD: return "helmet";
        case A_LEGS: return "legs";
        case A_NECK: return "neck";
        case A_ROBE: return "robe";
        case A_SHIELD: return "shield";
        case A_SHOULDERS: "shoulders";
        case A_L_SHOULDER: "shoulders";
        case A_R_SHOULDER: "shoulders";
        case A_WRISTS: return "wrists";
        case A_L_WRIST: return "wrists";
        case A_R_WRIST: return "wrists";
        case A_WAIST: return "waist";
        case A_L_HIP: return "hips";
        case A_L_HIP: return "hips";
        case A_L_ANKLE: return "ankles";
        case A_R_ANKLE: return "ankles";
        default: return "-";
    }
}
string render_other_type(object ob)
{
    if (function_exists("create_arrow", ob))
    {
        return "arrow";
    }
    if (IS_WEARABLE_OBJECT(ob))
    {
        return "wearable";
    }
    if (ob->id("leftover"))
    {
        return "leftover";
    }
    if (IS_HERB_OBJECT(ob))
    {
        return "herb";
    }
    if (IS_DRINK_OBJECT(ob))
    {
        return "drink";
    }
    if (IS_FOOD_OBJECT(ob))
    {
        return "food";
    }
    if (IS_KEY_OBJECT(ob))
    {
        return "key";
    }
    if (IS_TORCH_OBJECT(ob))
    {
        return "torch";
    }
    if (IS_COINS_OBJECT(ob))
    {
        return "money";
    }
    if (ob->query_gem())
    {
        return "gem";
    }
    if (ob->id("vial"))
    {
        return "vial";
    }
    if (IS_POTION_OBJECT(ob))
    {
        return "potion";
    }
    return "-";
}

int f_weapon(object ob)
{
    return IS_WEAPON_OBJECT(ob);
}

int f_armour(object ob)
{
    return IS_ARMOUR_OBJECT(ob);
}

int f_other(object ob)
{
    return !IS_WEAPON_OBJECT(ob) && !IS_ARMOUR_OBJECT(ob);
}

void describe_generic(object *obarr, object fo, function render_type)
{
    if (sizeof(obarr) == 0) return;
    int quantity = 0;
    string short_desc;
    if (IS_HEAP_OBJECT(obarr[0]))
    {
        quantity = obarr[0]->num_heap();
        short_desc = obarr[0]->singular_short();
    }
    else
    {
        quantity = sizeof(obarr);
        short_desc = obarr[0]->short();
    } 
    
    string type_desc = render_type(obarr[0]);

    fo->catch_tell(sprintf("| %-:51s | %-:14s | %4d |\n",
        short_desc, type_desc, quantity));
}

public void show_list(object fo, object *obarr)
{
    mixed* weapon_arr = sort_array(unique_array(filter(obarr, f_weapon), "short"), sort_weapon);
    mixed* armour_arr = sort_array(unique_array(filter(obarr, f_armour), "short"), sort_armour);
    mixed* other_arr = sort_array(unique_array(filter(obarr, f_other), "short"), sort_other);

    if (sizeof(weapon_arr) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "  Weapon                                                Type             Qty   \n" +
            "+-----------------------------------------------------+----------------+------+\n");
        foreach(object *obs : weapon_arr) {
            describe_generic(obs, fo, &render_weapon_type());
        }
        fo->catch_tell(
            "+-----------------------------------------------------+----------------+------+\n");
    }
    if (sizeof(armour_arr) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "  Armour                                                Type             Qty   \n" +
            "+-----------------------------------------------------+----------------+------+\n");
        foreach(object *obs : armour_arr) {
            describe_generic(obs, fo, &render_armour_type());
        }
        fo->catch_tell(
            "+-----------------------------------------------------+----------------+------+\n");
    }
    if (sizeof(other_arr) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "  Other                                                 Type             Qty   \n" +
            "+-----------------------------------------------------+----------------+------+\n");
        foreach(object *obs : other_arr) {
            describe_generic(obs, fo, &render_other_type());
        }
        fo->catch_tell(
            "+-----------------------------------------------------+----------------+------+\n");
    }
}

void describe_contents(object fo, object *obarr)
{
    fo->catch_tell(show_sublocs(fo));

    if (sizeof(obarr) > 0)
    {
        show_list(fo, obarr);
    }
    else
    {
        fo->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
    }
}

//-------------------------------------------------------------------
