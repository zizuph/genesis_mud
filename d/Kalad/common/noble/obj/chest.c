inherit "/std/receptacle.c";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_receptacle()
{
    set_name("chest");
    set_adj("oak");
    add_adj("ornate");
    set_short("ornate oak chest");
    add_prop(CONT_I_MAX_WEIGHT,2000);
    add_prop(CONT_I_MAX_VOLUME,2000);
    add_prop(CONT_I_WEIGHT,500);
    add_prop(CONT_I_VOLUME,500);    
    add_prop(CONT_I_CLOSED,1);
    set_long("This is a beautifully made ornate wooden chest. It "+
    "looks polished and well taken care of.\n");
}

