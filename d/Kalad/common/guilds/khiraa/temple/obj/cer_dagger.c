/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/cer_dagger.c
 * Purpose    : This ceremony dagger of the joinroom.
 * Located    : ~khiraa/temple/obj/thanatos.c
 * Created By : Sarr 16.Mar.97
 * Modified By: 
 */ 

inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"


void
create_weapon()
{
    ::create_weapon();
    set_name("dagger");
    set_adj("ebony");
    add_adj("ornate");
    set_short("ornate ebony dagger");
    set_long("This dagger, made of blackened steel, has a long, thin, razor-"+
    "sharp blade. The short hilt is wraped in black cloth, to give a better "+
    "grip on it. Red rubies and green emeralds adorn its cross-piece. A "+
    "grim looking skull made of gold is placed at the bottom of the "+
    "hilt.\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_KNIFE);
    set_hit(12);
    set_pen(12);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,300);
}

