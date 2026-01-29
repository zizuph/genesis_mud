/*
 * servant.c
 *
 * A servant typical to the Temple of Takhisis
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include DL_CLOCK

inherit AM_FILE

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("servant");
    
    set_race_name("human");
    set_adj("short");
    add_adj("servile");
    set_long("This is a servant working in the Temple of Takhisis. " +
    "His job is to greet the members of the Priesthood as they " +
    "wake up.\n");

    set_default_answer(QCTNAME(TO) + " murmurs: I know nothing about that.\n");
    add_ask(" [for] [the] 'time' ",VBFC_ME("give_time"));

    add_prop(CONT_I_HEIGHT, 165);
    add_prop(CONT_I_WEIGHT, 55000);

    set_stats(({65,65,65,50,50,60}));
    set_hp(query_max_hp());

    set_all_hitloc_unarmed(3);

    set_alignment(-200);
    set_knight_prestige(200);

}

string
give_time()
{
    string str;
    int h;
    int m;

    h = GET_TIME[KHOUR];
    m = GET_TIME[KMINUTE];

    if (m < 20)
    	str = "It has just struck ";
    else if (m < 40)
        str = "It is well past ";
    else
    {
    	str = "It will soon strike ";
    	h++;
    }
    if (h>23)
        h -= 24;

    switch(h)
    {
    	case 0:
    	    str += "midnight";
    	    break;
    	case 1..12:
    	    str += LANG_WNUM(h);
    	    break;
    	case 13..23:
    	    str += LANG_WNUM(h-12);
    	    break;
    }

    command("say " + str + ".");
    return "";
}
    
    	
