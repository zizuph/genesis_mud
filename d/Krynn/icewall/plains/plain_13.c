/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <language.h>
#include <macros.h>
inherit ICEINROOM;

object bear;
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
reset_icewall_room() 
{
    if (!bear) 
    {
	bear = clone_object(ICE_CAST_M + "polar_bear");
	bear->move(TO);
    }
}

void
create_icewall_room() 
{
    set_short("Bear Cave");
    set_long("You have entered the cave of a polar bear. You see its nest made out "
	     + "of strips of cloth and hide. On the ground are various "
	     + "bones from previous meals. "
	     + "The snow just inside the entrance is covered with tracks. "
	     + "\n");
    
    add_item("snow","It was blown into the entrance by the outside wind.\n");
    add_item("entrance","You see harsh weather through it.\n");
    add_item("weather","You suppose it is a storm.\n");
    add_item("tracks","They are polar bear tracks.\n");
    add_item("nest","It is a warm nest. The polar bear sleeps here.\n");
    add_item(({"cloth","hide"}),"It lines the nest, making it warm.\n");
    add_item("bones","They are mostly from fish but a few are from "
	     + LANG_ADDART(QRACE(TP)) + ".\n");
    
    add_exit(ICE_PLAINS+"plain_11","west");
    
    reset_icewall_room();
}

