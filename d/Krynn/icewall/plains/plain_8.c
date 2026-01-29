/* Created by Stevenson */
/* Thanoi stuff added by Macker */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#define PLAIN_13 (ICE_PLAINS + "plain_13")
inherit ICEOUTROOM;

object penguin;
int tnum = 0;
object leader4 = 0, leader2 = 0, loner = 0;


void
make_4_team()
{
    if (leader4)
      return;
    clone_object(PLAINS_L + "thanoi.c")->move(TO);
    clone_object(PLAINS_L + "thanoi.c")->move(TO);
    clone_object(PLAINS_L + "thanoi.c")->move(TO);
    (leader4 = clone_object(PLAINS_L + "m_thanoi"))->move(TO);
    leader4->form_team();
}

void
make_2_team()
{
    if (leader2)
      return;
    clone_object(PLAINS_L + "thanoi.c")->move(TO);
    (leader2 = clone_object(PLAINS_L + "m_thanoi"))->move(TO);
    leader2->form_team();
}

void
make_solo()
{
    if (loner)
      return;
    loner = clone_object(PLAINS_L + "m_thanoi.c");
    loner->remove_adj("dominant");
    loner->add_adj("loner");
    loner->move(TO);
}

void
make_2_team_13()
{
    PLAIN_13->make_2_team();
}

void
make_solo_13()
{
    PLAIN_13->make_solo();
}

/* To be quite honest, the teaming doesn't work
   exactly as I planned. It seems the thanoi just want to form
   certain teams and sometimes ignore my intended teams for them.
   *sigh*. Oh well. I suppose accidental randomness isn't so bad
   is it? *smrik* It adds to the variety of possibilities anywa ;) 
*/
void
reset_icewall_room()
{
    
    if (!penguin) 
    {
	penguin = clone_object(ICE_CAST_M+"penguin");
	penguin->move(TO);
    }
    
    if (tnum + 4 <= 14)
    {
	make_4_team();
	tnum += 4;
    }
    if (tnum + 4 <= 14)
    {
	PLAIN_13->make_4_team();
	tnum += 4;
    }
    if (tnum + 2 <= 14)
    {
	set_alarm(10.0, 0.0, "make_2_team");
	tnum += 2;
    }
    if (tnum + 2 <= 14)
    {
	set_alarm(10.0, 0.0, "make_2_team_13");
                tnum += 2;
    }
    if (tnum + 1 <= 14)
    {
	set_alarm(20.0, 0.0, "make_solo"); 
	tnum += 1;
    }
    if (tnum + 1 <= 14)
    {
	set_alarm(20.0, 0.0, "make_solo_13");
	tnum += 1;
    }
}


void
create_icewall_room() 
{
    set_short("On the icy plains");
    set_long("You are on the frozen plains of Icewall. There is "
	     + "a peculiar sense of quiet in the area. You wonder "
	     + "what life could possibly survive in this harsh "
	     + "climate. Around you to the north and the east are "
	     + "very high, snowcapped mountains."
	     + "\n");
    
    add_exit(ICE_PLAINS+"plain_7","northwest");
    add_exit(ICE_PLAINS+"plain_6","southwest");
    add_exit(ICE_PLAINS+"plain_10","south");
    add_exit(ICE_PLAINS+"plain_12","east");
    add_exit(ICE_PLAINS+"plain_11","northeast");
    
    reset_icewall_room();
}

void
reduce_tnum()
{
    tnum -= 1;
}

