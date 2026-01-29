inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include "camp.h"

object scout, guard;

void add_stuff() 
{
    if(!scout)
    {
	scout=clone_object(ORCMAKER_DIR+"orcmaker");
	clone_object(GREEN_DIR + "obj/backpack")->move(scout, 1);
	scout->set_power(50+random(6));
	scout->set_type(SCOUT);
	scout->add_act("sneak north");
	scout->add_act("sneak south");
	scout->add_act("sneak west");
	scout->add_act("sneak east");
	scout->add_act("sneak northwest");
	scout->add_act("sneak northeast");
	scout->add_act("sneak southwest");
	scout->add_act("sneak southeast");
	scout->move(TO, 1);
    }
    if(!guard)
    {
	guard=clone_object(ORCMAKER_DIR+"orcmaker");
	guard->set_power(90+random(26));
	guard->set_type(GUARD);
	guard->set_random_move(29);
	guard->set_restrain_path(({GREEN_DIR + "camp"}));
	guard->move(TO);
    }
}


void reset_room()
{
    add_stuff();
}


create_room()
{
    create_camproom();
    set_short("Within the camp");
    set_long("Tents surround you to the south and "+
      "east as you try to make out details through the haze that blankets "+
      "this camp near Greenfields. You stand in the portion of "+
      "the camp where average members of this orc army live. "+
      "But there are a lot of them, so look out!\n");


    add_item(({"haze","greenfields","details"}),
      "The haze covers most of the camp and obscures "+
      "the smallest of details from sight.\n");

    add_exit(GREEN_DIR + "camp/camp12","northeast",0);
    add_exit(GREEN_DIR + "camp/camp09","east",0);
    add_exit(GREEN_DIR + "camp/camp04","southeast",0);
    add_exit(GREEN_DIR + "camp/camp03","south",0);
    set_tent_name("tent08");
    enable_reset();
    add_stuff();

    STANDARDS;
}
