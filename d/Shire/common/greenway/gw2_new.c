inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/std/make_money.c"
//#include <money.h>
#include <tasks.h>
#include "/sys/macros.h"

object shadow;

#define STAND_PARENT	"/d/Shire/common/"
#define STAND_DIR     STAND_PARENT + "greenway/"

#define SHADOW STAND_DIR + "dirty_shadow"
#define MIN_AWARE 10

//   Prototypes
void give(object ob);
string do_search(object searcher, string str);

int give_id;
int puddle_searched = 0, 
    money_count = 1;



void
create_shire_room()
{


    set_short("The Greenway");
    set_long("@@long_desc");

    add_item(({ "field", "fields" }), "The crops in the fields are bending in "
      + "the wind\n");
    add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
      + "and mules. There are also a few that indicate horses.\n");
    add_item(({ "bird", "birds" }), "They are only small black specks in the "
      + "sky.\n");
    add_item("puddle", "You wouldn't want to fall into that.\n");

    add_exit(STAND_DIR + "gw1", "north", "@@north");
    add_exit(STAND_PARENT + "hollin/f0000", "east");
    add_exit(STAND_PARENT + "gondorlink", "south", "@@south");

    reset_shire_room();

}

string long_desc() {

    string str;

    str = "You are travelling on an old road winding its way through "
    + "the fields surounding it. The tracks on the road are "
    + "quite fresh and implies that the road is in constant use. "
    + "You can hear the birds sing in the distance. In the "
    + "middle of the road is a big puddle.\n";

    return str;

}

int south() {
    if(!this_player()->query_dirty_shadow()) {
	if (TP->resolve_task(TASK_ROUTINE, ({TS_DEX,SS_AWARENESS})) <= 0)
	{
	    write("As you tread your way south you stumble and fall into the "
	      + "puddle.\n");
	    say(QCTNAME(this_player()) + " goes south but stumbles and falls into the "
	      + "puddle.\n");

	    give_id = set_alarm(0.1, 0.0, &give(this_player()));
	    return 1;
	}

    }

    return 0;

}

int north() {

    if(!this_player()->query_dirty_shadow()) {

	if (TP->resolve_task(TASK_ROUTINE, ({TS_DEX,SS_AWARENESS})) <= 0)
	{

	    write("As you tread your way north you stumble and fall into the "
	      + "puddle.\n");
	    say(QCTNAME(this_player()) + " goes north but stumbles and fall "
	      + "into the puddle.\n");

	    give_id = set_alarm(0.1, 0.0, &give(this_player()));
	    return 1;
	}

    }

    return 0;

}

void
give(object ob) {

    remove_alarm(give_id);
    shadow = clone_object(SHADOW);
    shadow->shadow_me(ob);
    shadow->destruct_dirty_shadow();
}


public void reset_shire_room()
{
    puddle_searched = 0;
    money_count = money_count + 1;
}



string
do_search(object searcher, string str)
{
    int awareness;
write (puddle_searched + " " + money_count +"\n");
    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < MIN_AWARE + random (MIN_AWARE)) return 0;
    if(!str || (str!= "dolly" && str != "mud puddle")) return 0;
    if (!present("coin"))
	MONEY_MAKE_GC(21)->move(this_object(), 1);
    say(QCTNAME(searcher)+ " finds something in the puddle.\n");
    return "You find some money in the puddle.\n";
}