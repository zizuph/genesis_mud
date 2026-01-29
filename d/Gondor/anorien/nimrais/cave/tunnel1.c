/*
 *	/d/Gondor/anorien/nimrais/cave/tunnel1.c
 *
 *	December 1995, Olorin
 */
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define HIM(x)	((x)->query_objective())

public void
create_room()
{
    set_short("the end of a narrow tunnel");
    set_long(BSN("The tunnel ends here at a hole leading down into "
      + "darkness. It winds upwards to the northwest, rising steeply in "
      + "that direction. Water is trickling down on the ground, into the "
      + "hole below."));

    add_item(({"ground", "floor", "water", "stream", }), BSN("The thin stream of "
      + "water is trickling downwards on the tunnel floor. It disappears "
      + "into the hole in the ground."));
    add_item(({"hole", }), BSN("The hole in the ground is just barely "
      + "large enough to let you pass. It is the only drain for the water "
      + "coming down the tunnel. Beneath it are only shadows."));
    add_item(({"shadows", "cave", }), BSN("It is impossible to make out from "
      + "here what night be hidden in the shadows beneath the hole in the "
      + "ground."));
    add_item(({"tunnel", "walls", }), BSN(
        "The smooth walls are proof that this tunnel probably was not mined "
      + "but washed out of the rock by the steady flow of water through "
      + "the surrounding layers of rock. Right here the tunnel coming down "
      + "from the northwest seems to come to an end, with only a small niche "
      + "in the opposite wall."));
    add_item(({"niche", }), "@@exa_niche@@");
    add_cmd_item(({"niche", "into niche", }), ({"squeeze", "enter"}), "@@enter_niche@@");

    add_exit(ANO_DIR + "nimrais/cave/tunnel2", "northwest", "@@blocked_nw@@", 1);
    add_exit(ANO_DIR + "nimrais/cave/back",    "down",      "@@blocked_d@@",  1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
}

public int
blocked_nw()
{
    if ((ANO_DIR + "nimrais/cave/tunnel2")->query_heap_state() == 1)
    {
        write("The tunnel is blocked by an avalanche of rocks coming down towards you.\n"
          +   "Instead of walking foolhardily into the danger, you should better run away, fast!\n");
        return 1;
    }
    return 0;
}

public int
blocked_d()
{
    if ((ANO_DIR + "nimrais/cave/tunnel2")->query_heap_state() > 1)
    {
        write("The cave below the tunnel is filled with a heap of rocks and stones.\n"
          +   "It is impossible to climb down there.\n");
        return 1;
    }
    return 0;
}

public string
enter_niche()
{
    int     is;
    object *objs;

    (ANO_DIR + "nimrais/cave/niche")->load_me();
    objs = all_inventory(find_object(ANO_DIR + "nimrais/cave/niche"));
    objs = FILTER_LIVE(objs);
    if (is = sizeof(objs))
        return "The niche is too small for more than one person to "
             + "squeeze into it.\n";

    write("You squeeze yourself into the narrow niche.\n");
    say(QCTNAME(TP)+" squeezes "+HIM(TP)+"self into a narrow niche in "
      + "the wall to the southeast.\n");
    TP->move_living("M", ANO_DIR + "nimrais/cave/niche");
    return "";
}

public string
exa_niche()
{
    int     is;
    object *objs;
    string  desc = "The small niche in the southeast wall of the tunnel "
      + "is somewhat above the ground level of the tunnel. It was probably "
      + "washed out of the rock before the hole "
      + "in the ground existed, through which the water now drains. It is "
      + "shallow and narrow, but one might be able to enter it.";

    (ANO_DIR + "nimrais/cave/niche")->load_me();
    objs = all_inventory(find_object(ANO_DIR + "nimrais/cave/niche"));
    objs = FILTER_LIVE(objs);
    if (is = sizeof(objs))
        desc += " " + CAP(COMPOSITE_LIVE(objs)) +  (is == 1 ?
                " is squeezing "+HIM(objs[0])+"self" :
                " are squeezing themsevles")
             +  " into the niche.";

    return BSN(desc);
}

public void
clean_up()
{
    FILTER_DEAD(all_inventory(TO))->remove_object();
}

public void
cavein()
{
    int     sl,
            i;
    object *liv;

    tell_room(TO, "An avalanche of rocks and stones comes sliding down from above.\n");

    liv = FILTER_LIVE(all_inventory(TO));

    for (i = 0, sl = sizeof(liv); i < sl; i++)
        if (random(liv[i]->query_stat(SS_DIS)) < liv[i]->query_whimpy())
            liv[i]->run_away("down");

    tell_room(TO, "You are buried beneath the rocks.\n");
    liv = FILTER_LIVE(all_inventory(TO));
    for (i = 0, sl = sizeof(liv); i < sl; i++)
    {
        liv[i]->heal_hp(- (liv[i]->query_max_hp() + 1));
        liv[i]->do_die(TO);
        if (interactive(liv[i]))
            log_file("traps", liv[i]->query_name() + " killed by rock "
              + "avalanche in "+file_name(TO)+" at "+ctime(time())+".\n");
    }

    tell_room(ANO_DIR + "nimrais/cave/niche", "An avalanche of rocks and stones "
      + "comes down the tunnel with a tremendous roar and a lot of dust.\n"
      + "Luckily for you, the avalanache disappears through the hole in the "
      + "ground into the cave below.\n");
    tell_room(ANO_DIR + "nimrais/cave/entrance",
        "A loud roar and puffs of dust are coming from the back of the cave.\n"
      + "It is probably not advisable to go there now.\n");

    set_alarm(1.0, 0.0, clean_up);
}

