/* Created by Stevenson */
/* Minotaurs and Village loading code added by Macker */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object leader;


void
clone_mins()
{
    clone_object(PLAINS_L + "minotaur")->move(TO);
    clone_object(PLAINS_L + "minotaur")->move(TO);
    clone_object(PLAINS_L + "minotaur")->move(TO);
    clone_object(PLAINS_L + "minotaur")->move(TO);
    clone_object(PLAINS_L + "minotaur")->move(TO);
    clone_object(PLAINS_L + "minotaur")->move(TO);
    (leader = clone_object(PLAINS_L + "m_minotaur"))->move(TO);
    leader->form_team();
}

void
reset_icewall_room()
{
    if (!leader && !random(5))
      clone_mins();
}

void
load_village()
{
    (VILLAGE + "gathering.c")->load_me();
}

void
load_thanoi()
{
    (ICE_PLAINS + "plain_8.c")->load_me();
}

void
create_icewall_room() 
{
    set_short("Icy Plains");
    set_long("You are on the frozen plains of Icewall. There is "
	     + "a peculiar sense of quiet in the area. You wonder "
	     + "what life could possibly survive in this harsh "
	     + "climate. Around you to the north and the east are "
	     + "very high, snowcapped mountains."
	     + "\n");
    
    add_item("mountains","They form a natural barrier to prevent "
	     + "unwanted visitors from invading.\n");
    add_item("ice","It is very slippery--be careful.\n");
    
    add_exit(ICE_OUT+"path_7.c","northwest");
    add_exit(ICE_PLAINS+"plain_2","northeast");
    set_alarm(4.0, 0.0, "load_village");
    set_alarm(2.0, 0.0, "load_thanoi");
    /*
       Why load the village? Well, since this is called here, by the
       time players reach the village the npc's will be nice and
       scattered randomly with weapons already wielded and no annoying
       "arrives" messages to clutter up their screens.
       (This was added by Macker)
       */
    clone_mins();
}


