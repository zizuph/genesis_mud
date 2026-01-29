/*
 * Weapon rack for southern store room in Tower of Arms.
 *
 * Mortis 09.2014
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../../../local.h"

inherit "/std/receptacle";

object arm1, arm2, arm3, arm4, arm4, arm5, arm6, arm7, arm8, arm9, arm10,
       arm11, arm12, arm13, arm14, arm15, arm16, arm17, arm18, arm19, arm20,
       arm21, arm22, arm23, arm24, arm25, arm26, arm27, arm28, arm29, arm30,
       arm31, arm32, arm33, arm34, arm35, arm36, arm37, arm38, arm39, arm40;

string what_type();

void
reset_container()
{
    if (!arm1)
    {
        arm1 = clone_object(OBJ + what_type());
        arm1->move(TO);
    }
    if (!arm2)
    {
        arm2 = clone_object(OBJ + what_type());
        arm2->move(TO);
    }
    if (!arm3)
    {
        arm3 = clone_object(OBJ + what_type());
        arm3->move(TO);
    }
    if (!arm4)
    {
        arm4 = clone_object(OBJ + what_type());
        arm4->move(TO);
    }
    if (!arm5)
    {
        arm5 = clone_object(OBJ + what_type());
        arm5->move(TO);
    }
    if (!arm6)
    {
        arm6 = clone_object(OBJ + what_type());
        arm6->move(TO);
    }
    if (!arm7)
    {
        arm7 = clone_object(OBJ + what_type());
        arm7->move(TO);
    }
    if (!arm8)
    {
        arm8 = clone_object(OBJ + what_type());
        arm8->move(TO);
    }
    if (!arm9)
    {
        arm9 = clone_object(OBJ + what_type());
        arm9->move(TO);
    }
    if (!arm10)
    {
        arm10 = clone_object(OBJ + what_type());
        arm10->move(TO);
    }
    if (!arm11)
    {
        arm11 = clone_object(OBJ + what_type());
        arm11->move(TO);
    }
    if (!arm12)
    {
        arm12 = clone_object(OBJ + what_type());
        arm12->move(TO);
    }
    if (!arm13)
    {
        arm13 = clone_object(OBJ + what_type());
        arm13->move(TO);
    }
    if (!arm14)
    {
        arm14 = clone_object(OBJ + what_type());
        arm14->move(TO);
    }
    if (!arm15)
    {
        arm15 = clone_object(OBJ + what_type());
        arm15->move(TO);
    }
    if (!arm16)
    {
        arm16 = clone_object(OBJ + what_type());
        arm16->move(TO);
    }
    if (!arm17)
    {
        arm17 = clone_object(OBJ + what_type());
        arm17->move(TO);
    }
    if (!arm18)
    {
        arm18 = clone_object(OBJ + what_type());
        arm18->move(TO);
    }
    if (!arm19)
    {
        arm19 = clone_object(OBJ + what_type());
        arm19->move(TO);
    }
    if (!arm20)
    {
        arm20 = clone_object(OBJ + what_type());
        arm20->move(TO);
    }
    if (!arm21)
    {
        arm21 = clone_object(OBJ + what_type());
        arm21->move(TO);
    }
    if (!arm22)
    {
        arm22 = clone_object(OBJ + what_type());
        arm22->move(TO);
    }
    if (!arm23)
    {
        arm23 = clone_object(OBJ + what_type());
        arm23->move(TO);
    }
    if (!arm24)
    {
        arm24 = clone_object(OBJ + what_type());
        arm24->move(TO);
    }
    if (!arm25)
    {
        arm25 = clone_object(OBJ + what_type());
        arm25->move(TO);
    }
    if (!arm26)
    {
        arm26 = clone_object(OBJ + what_type());
        arm26->move(TO);
    }
    if (!arm27)
    {
        arm27 = clone_object(OBJ + what_type());
        arm27->move(TO);
    }
    if (!arm28)
    {
        arm28 = clone_object(OBJ + what_type());
        arm28->move(TO);
    }
    if (!arm29)
    {
        arm29 = clone_object(OBJ + what_type());
        arm29->move(TO);
    }
    if (!arm30)
    {
        arm30 = clone_object(OBJ + what_type());
        arm30->move(TO);
    }
    if (!arm31)
    {
        arm31 = clone_object(OBJ + what_type());
        arm31->move(TO);
    }
    if (!arm32)
    {
        arm32 = clone_object(OBJ + what_type());
        arm32->move(TO);
    }
    if (!arm33)
    {
        arm33 = clone_object(OBJ + what_type());
        arm33->move(TO);
    }
    if (!arm34)
    {
        arm34 = clone_object(OBJ + what_type());
        arm34->move(TO);
    }
    if (!arm35)
    {
        arm35 = clone_object(OBJ + what_type());
        arm35->move(TO);
    }
    if (!arm36)
    {
        arm36 = clone_object(OBJ + what_type());
        arm36->move(TO);
    }
    if (!arm37)
    {
        arm37 = clone_object(OBJ + what_type());
        arm37->move(TO);
    }
    if (!arm38)
    {
        arm38 = clone_object(OBJ + what_type());
        arm38->move(TO);
    }
    if (!arm39)
    {
        arm39 = clone_object(OBJ + what_type());
        arm39->move(TO);
    }
    if (!arm40)
    {
        arm40 = clone_object(OBJ + what_type());
        arm40->move(TO);
    }
}

void
create_container()
{
    set_name("rack");
    add_name(({"racks"}));
    set_adj(({"constabulary", "weapon"}));

    set_short("constabulary weapon rack");
    set_long("Racks line the southern wall for storing weapons.\n");

    add_prop(CONT_I_MAX_WEIGHT,  250000);
    add_prop(CONT_I_MAX_VOLUME,  250000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The racks are bolted into the wall and cannot "
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
what_type()
{
    return one_of_list(({"gwep_club_cmdr", "gwep_spear", "gwep_sword"}));
}

