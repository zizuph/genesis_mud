
/* 
    ~Calia/gelan/cadet/gm_uniform.c

    guildmaster's uniform for the Cadets of Gelan

    coded by Maniac@Genesis 11/4/97

    Copyright (C) Miguel Leith 1997
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "cadet.h"

void
create_armour()
{
    set_name("uniform");
    set_adj(({"forest-green", "canvas", "green"}));
    set_short("forest-green canvas uniform"); 
    set_pshort("forest-green canvas uniforms"); 
    set_long("A forest-green canvas uniform.\n"); 
    set_ac(20);
    set_at(A_BODY | A_ARMS);
    set_am(({ 0, 0, 0 }) );
}

