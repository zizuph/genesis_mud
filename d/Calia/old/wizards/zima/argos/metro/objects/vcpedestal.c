/**
*** A pedestal found in the visitors center of Argos
***
*** 3/3/95    Zima       Created
***
**/
inherit "std/object";
#include <stdproperties.h>
 
void create_object() {
    set_name("pedestal");
    set_adj(({"ornate","wooden"}));
    set_short("ornate wooden pedestal");
    set_long("It is an ornate wooden pedestal with a book and a bottle "+
             "of ink sitting on top.\n");
 
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(OBJ_M_NO_INS, 1);
}
