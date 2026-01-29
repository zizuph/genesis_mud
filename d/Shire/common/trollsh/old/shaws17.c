/* File: /d/Shire/common/trollsh/trollsh17.c */
#include "defs.h"
#include <ss_types.h>
#include <macros.h>
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/

void
create_shawrom()
{

    set_short("Southeast in the Trollshaw, on a ridge");
    set_extraline(
      "You find yourself on the edge of a small cliff. "
      +"The cliff is formed by the ridge ending abruptly to the "
      +"southeast. It seems it's a rather long way down. But you can't "
      +"be sure since the pine trees and the bush down there, is very "
      +"unpredictably scattered and are covering the ground. To the north "
      +"the ridge leads down into area where there are more pines than "
      +"bushes. ");


    add_item("cliff","@@cliff_bend");
/*
    add_call("jump","[off] [down] [from] 'cliff'","cliff_jump");
*/

    WEST("shaws14");
    NORTH("shaws18");
}

string
cliff_bend()
{

    SAYBB(" leans out over the cliff to look down but quickly "
      + "steps back, you wonder why....\n");

    WRITE ("The cliff is formed by the ridge you are standing on. "
      +"As you bend over the edge to look down you feel a little "
      +"out of balance and quickly move back. "+
      "You realize a fall from this height would definately kill you.\n");
    return "";

}


void
cliff_jump(string str)
{
    object ob;
    /*
       if (ob->query_stat(SS_DIS) < 80)
	    {

	    WRITE("You step forward to jump off the cliff........\n"
		  +"Nope, you don't dare... NO WAY. It's Way to far down!!! \n");
	    SAY(QCTNAME(ob) + " step forward to jump of the cliff. Suddently "
		  + HE_SHE(ob) +" stop... It seems " + HE_SHE(ob) + " don't dare.");

	    }
    */
    SAY("Suddenly "+QCTNAME(ob)+" picks up speed and runs for the edge of "
      +" the cliff, "+HE_SHE(ob)+" makes a big leap out in the air and "
      +" start to fall down. SMOISH !!!! oops! "
      +" It seems it was a bit further down there than "+QCTNAME(ob)
      +" thought. You can't see the body down there, but you are pretty "
      +" sure noone could have survived a fall like that. Besides, there "
      +" are blood splattered around some bushes down there. "
      + QCTNAME(ob) + " must be dead.");

    WRITE("You pick up speed and jump off the cliff...................\n"
      +"When you get ouside the cliff you realize what a suicide this was. "
      +"You move faster and faster through the air before you notice the gr..\n"
      +"SPLOISHHH!!!!!\n All turns black. \n It seems this was a BIG mistake.\n");

    ob->move_living("M",TROLLSH_DIR + "deathrom");	
    ob->heal_hp(-1000000);
    ob->do_die();
}

