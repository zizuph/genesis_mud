/*
 * Shelves for northern store room of gear in Tower of Arms.
 *
 * Mortis 09.2014
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../../../local.h"

inherit "/std/receptacle";

object pouch1, pouch2, pouch3, sheath1, sheath2, sheath3, scab1, scab2, scab3,
       holster1, holster2, holster3, bp1, bp2, bp3, sack1, sack2, sack3, sack4,
       satch1, satch2, satch3, sbag1, sbag2, sbag3, band1, band2, band3, loot1,
       loot2, loot3, ruck1, ruck2, ruck3, knap1, knap2, knap3;

string what_cust();
string what_col();
string what_mat();

void
reset_container()
{
    if (!pouch1)
    {
        string ptype = one_of_list(({"belt-pouch", "thigh-pouch"}));
        pouch1 = clone_object(MERCH + "obj/lgeneral");
        pouch1->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + ptype);
        pouch1->add_prop(CONT_I_CLOSED, 1);
        pouch1->move(TO);
    }
    if (!pouch2)
    {
        string ptype = one_of_list(({"belt-pouch", "thigh-pouch"}));
        pouch2 = clone_object(MERCH + "obj/lgeneral");
        pouch2->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + ptype);
        pouch2->add_prop(CONT_I_CLOSED, 1);
        pouch2->move(TO);
    }
    if (!pouch3)
    {
        string ptype = one_of_list(({"belt-pouch", "thigh-pouch"}));
        pouch3 = clone_object(MERCH + "obj/lgeneral");
        pouch3->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + ptype);
        pouch3->add_prop(CONT_I_CLOSED, 1);
        pouch3->move(TO);
    }
    if (!sheath1)
    {
        string ptype = one_of_list(({"belt-sheath", "thigh-sheath",
                                     "wrist-sheath", "boot-sheath"}));
        sheath1 = clone_object(MERCH + "obj/lgeneral");
        sheath1->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + ptype);
        sheath1->move(TO);
    }
    if (!sheath2)
    {
        string ptype = one_of_list(({"belt-sheath", "thigh-sheath",
                                     "wrist-sheath", "boot-sheath"}));
        sheath2 = clone_object(MERCH + "obj/lgeneral");
        sheath2->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + ptype);
        sheath2->move(TO);
    }
    if (!sheath3)
    {
        string ptype = one_of_list(({"belt-sheath", "thigh-sheath",
                                     "wrist-sheath", "boot-sheath"}));
        sheath3 = clone_object(MERCH + "obj/lgeneral");
        sheath3->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + ptype);
        sheath3->move(TO);
    }
    if (!scab1)
    {
        scab1 = clone_object(MERCH + "obj/lgeneral");
        scab1->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "scabbard");
        scab1->move(TO);
    }
    if (!scab2)
    {
        scab2 = clone_object(MERCH + "obj/lgeneral");
        scab2->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "scabbard");
        scab2->move(TO);
    }
    if (!scab3)
    {
        scab3 = clone_object(MERCH + "obj/lgeneral");
        scab3->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "scabbard");
        scab3->move(TO);
    }
    if (!holster1)
    {
        string ptype = one_of_list(({"back-holster", "side-holster"}));
        holster1 = clone_object(MERCH + "obj/lgeneral");
        holster1->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + ptype);
        holster1->move(TO);
    }
    if (!holster2)
    {
        string ptype = one_of_list(({"belt-sheath", "thigh-sheath",
                                     "wrist-sheath", "boot-sheath"}));
        holster2 = clone_object(MERCH + "obj/lgeneral");
        holster2->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + ptype);
        holster2->move(TO);
    }
    if (!holster3)
    {
        string ptype = one_of_list(({"belt-sheath", "thigh-sheath",
                                     "wrist-sheath", "boot-sheath"}));
        holster3 = clone_object(MERCH + "obj/lgeneral");
        holster3->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + ptype);
        holster3->move(TO);
    }
    if (!bp1)
    {
        bp1 = clone_object(MERCH + "obj/lgeneral");
        bp1->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "backpack");
        bp1->add_prop(CONT_I_CLOSED, 1);
        bp1->move(TO);
    }
    if (!bp2)
    {
        bp2 = clone_object(MERCH + "obj/lgeneral");
        bp2->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "backpack");
        bp2->add_prop(CONT_I_CLOSED, 1);
        bp2->move(TO);
    }
    if (!bp3)
    {
        bp3 = clone_object(MERCH + "obj/lgeneral");
        bp3->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "backpack");
        bp3->add_prop(CONT_I_CLOSED, 1);
        bp3->move(TO);
    }
        if (!sack1)
    {
        sack1 = clone_object(MERCH + "obj/lgeneral");
        sack1->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "sack");
        sack1->add_prop(CONT_I_CLOSED, 1);
        sack1->move(TO);
    }
    if (!sack2)
    {
        sack2 = clone_object(MERCH + "obj/lgeneral");
        sack2->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "sack");
        sack2->add_prop(CONT_I_CLOSED, 1);
        sack2->move(TO);
    }
    if (!sack3)
    {
        sack3 = clone_object(MERCH + "obj/lgeneral");
        sack3->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "sack");
        sack3->add_prop(CONT_I_CLOSED, 1);
        sack3->move(TO);
    }
    if (!sack4)
    {
        sack4 = clone_object(MERCH + "obj/lgeneral");
        sack4->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "sack");
        sack4->add_prop(CONT_I_CLOSED, 1);
        sack4->move(TO);
    }
    if (!satch1)
    {
        satch1 = clone_object(MERCH + "obj/lgeneral");
        satch1->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "satchel");
        satch1->add_prop(CONT_I_CLOSED, 1);
        satch1->move(TO);
    }
    if (!satch2)
    {
        satch2 = clone_object(MERCH + "obj/lgeneral");
        satch2->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "satchel");
        satch2->add_prop(CONT_I_CLOSED, 1);
        satch2->move(TO);
    }
    if (!satch3)
    {
        satch3 = clone_object(MERCH + "obj/lgeneral");
        satch3->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "satchel");
        satch3->add_prop(CONT_I_CLOSED, 1);
        satch3->move(TO);
    }
    if (!sbag1)
    {
        sbag1 = clone_object(MERCH + "obj/lgeneral");
        sbag1->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "saddlebag");
        sbag1->add_prop(CONT_I_CLOSED, 1);
        sbag1->move(TO);
    }
    if (!sbag2)
    {
        sbag2 = clone_object(MERCH + "obj/lgeneral");
        sbag2->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "saddlebag");
        sbag2->add_prop(CONT_I_CLOSED, 1);
        sbag2->move(TO);
    }
    if (!sbag3)
    {
        sbag3 = clone_object(MERCH + "obj/lgeneral");
        sbag3->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "saddlebag");
        sbag3->add_prop(CONT_I_CLOSED, 1);
        sbag3->move(TO);
    }
    if (!band1)
    {
        band1 = clone_object(MERCH + "obj/lgeneral");
        band1->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "bandeleria");
        band1->move(TO);
    }
    if (!band2)
    {
        band2 = clone_object(MERCH + "obj/lgeneral");
        band2->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "bandeleria");
        band2->move(TO);
    }
    if (!band3)
    {
        band3 = clone_object(MERCH + "obj/lgeneral");
        band3->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "bandeleria");
        band3->move(TO);
    }
    if (!loot1)
    {
        loot1 = clone_object(MERCH + "obj/lgeneral");
        loot1->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "lootsack");
        loot1->add_prop(CONT_I_CLOSED, 1);
        loot1->move(TO);
    }
    if (!loot2)
    {
        loot2 = clone_object(MERCH + "obj/lgeneral");
        loot2->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "lootsack");
        loot2->add_prop(CONT_I_CLOSED, 1);
        loot2->move(TO);
    }
    if (!loot3)
    {
        loot3 = clone_object(MERCH + "obj/lgeneral");
        loot3->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "lootsack");
        loot3->add_prop(CONT_I_CLOSED, 1);
        loot3->move(TO);
    }
    if (!ruck1)
    {
        ruck1 = clone_object(MERCH + "obj/lgeneral");
        ruck1->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "rucksack");
        ruck1->add_prop(CONT_I_CLOSED, 1);
        ruck1->move(TO);
    }
    if (!ruck2)
    {
        ruck2 = clone_object(MERCH + "obj/lgeneral");
        ruck2->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "rucksack");
        ruck2->add_prop(CONT_I_CLOSED, 1);
        ruck2->move(TO);
    }
    if (!ruck3)
    {
        ruck3 = clone_object(MERCH + "obj/lgeneral");
        ruck3->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "rucksack");
        ruck3->add_prop(CONT_I_CLOSED, 1);
        ruck3->move(TO);
    }
    if (!knap1)
    {
        knap1 = clone_object(MERCH + "obj/lgeneral");
        knap1->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "knapsack");
        knap1->add_prop(CONT_I_CLOSED, 1);
        knap1->move(TO);
    }
    if (!knap2)
    {
        knap2 = clone_object(MERCH + "obj/lgeneral");
        knap2->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "knapsack");
        knap2->add_prop(CONT_I_CLOSED, 1);
        knap2->move(TO);
    }
    if (!knap3)
    {
        knap3 = clone_object(MERCH + "obj/lgeneral");
        knap3->set_general_data(what_cust() + "&&" + what_col() + "&&"
                                + what_mat() + "&&" + "knapsack");
        knap3->add_prop(CONT_I_CLOSED, 1);
        knap3->move(TO);
    }
}

void
create_container()
{
    set_name("shelves");
    add_name(({"row", "rows", "shelf"}));
    set_adj(({"small", "iron"}));

    set_short("wall with rows of shelves");
    set_long( "Rows of wooden shelves line the northern wall for storing "
    + "gear.\n");

    add_prop(CONT_I_MAX_WEIGHT,  250000);
    add_prop(CONT_I_MAX_VOLUME,  250000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The shelves are bolted into the wall and cannot "
    + "be taken.\n");
    add_prop(CONT_I_ATTACH, 1); // This doesn't do anything :(

    reset_container();
}

public varargs string
short(object for_obj)
{
    /* This line is copied from object.c as we don't want the 
     * instance of short in receptacle to be used. Thanks, Mercade.
     */
    return check_call(obj_short, for_obj);
}


public varargs string
plural_short(object for_obj)
{
     /* This line is copied from object.c as we don't want the 
     * instance of short in receptacle to be used. Thanks, Mercade.
     */
    string plural_short_description = check_call(obj_pshort, for_obj);

    return check_call(obj_pshort, for_obj);
}

int
close(object obj) // This isn't preventing the shelves from being close-able. :(
{
    string objname = obj->query_name();

    string arty = obj->short();
    object where = E(obj);
    write("There is no way to close the " + arty + ".\n");
    return 3;
}

string 
what_cust()
{
    return one_of_list(({"dark", "flat", "fur-trimmed", "glistening",
    "heavy", "light", "noble", "ornate", "plain", "rich", "supple", 
    "thin"}));
}

string
what_col()
{
    return one_of_list(({"black", "white", "charcoal", "grey", "brown",
    "mottled-brown", "crimson", "maroon", "yellow", "forest-green",
    "mottled-green", "olive-green", "blue", "raven-blue", "purple",
    "silvery"}));
}

string
what_mat()
{
    return one_of_list(({"hard", "hide", "leather", "soft", "studded",
    "suede"}));
}
