/*
 * /d/Kalad/common/guilds/khiraa/dk/obj/black_coin.c
 * Purpose    : A darkness coin used by the knight spell kdark
 * Located    : knight spell
 * Created By : Sarr 28.Mar.97
 * Modified By: 
 */

inherit "/std/object";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

void
create_object()
{
    set_name("coin");
    add_name("_dk_coin_");
    add_adj("abysmal-black");
    set_short("abysmal-black coin");
    set_long("This is a coin shaped object that is blacker than "+
    "black. It radiates darkness.\n");
    add_prop(OBJ_I_WEIGHT,3);
    add_prop(OBJ_I_VOLUME,1);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_LIGHT,-1);
}

void
set_coin_remove_time(float i)
{
    set_alarm(i,0.0,"remove_coin");
}

void
remove_coin()
{
    if(living(E(TO)))
    {
        tell_object(E(TO),"Your "+short()+" blinks out of "+
        "existance, and the room gets lighter.\n");
        tell_room(E(E(TO)),QCTNAME(E(TO))+"'s "+short()+" blinks out "+
        "of existance, and the room gets lighter.\n",E(TO));
    }
    else
    {
        tell_room(E(TO),"The "+short()+" blinks out of existance, and "+
        "the room gets lighter.\n");
    }
    remove_object();
}

