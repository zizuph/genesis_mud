inherit "/d/Shire/eastroad/std/er_base.c";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <ss_types.h>


#define EXIT1 MICH_DIR + "fairroad1","north",0,1
#define EXIT2 MICH_DIR + "cabin","south","@@enter",1


object dog;


void
create_er_room()
{
    area = "in";
    areaname = "Michel Delving";
    land = "the Shire";
    areatype = 3;
    areadesc = "floral garden";
    treetype = "willow";

    add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
    extraline = "You are in a small garden in front of a tiny cabin. "
    + "There is smoke coming from the chimney of the cabin. "
    + "The garden is well kept and the owner probably spends several "
    + "hours every day pruning the flowers and bushes.";

    add_item(({"bush","bushes"}), 
      "The bushes are of several varieties and they all smell like the "
      + "sweetest perfume.\n");

    add_item("cabin",
      "While rather small it appears to be a very cozy little hideout.\n");

    add_item(({"flower","flowers"}), 
      "They are mostly roses, but here and there you can see a tulip.\n");

    add_prop(ROOM_M_NO_ATTACK, "The dog won't let you get that close to him, but neither will he let you pass.\n"); /* cant kill dog */




    add_exit(EXIT1);
    add_exit(EXIT2);
}




void
enter_inv(object ob,object from)
{
    ::enter_inv(ob, from);

    if(!dog && living(ob) && !(ob->query_npc()) && !present("corpse")) {
	dog = clone_object(MICH_DIR + "npc/guard_dog");
	dog->move(TO);
    }
}

enter() {
    int sk;
    sk = this_player()->query_skill(SS_SNEAK);

    if(!dog)
	return 0;

    if(sk > 35) {
	write("You manage to sneak by the dog, and into the cabin.\n");
	say(QCTNAME(this_player()) + " manages to pass the dog without being"
	  + " noticed.\n");
	return 0;
    }

    write("The dog will not let you pass.\n");
    say("The dog will not let " + QCTNAME(this_player()) + " pass.\n");

    return 1;

}

