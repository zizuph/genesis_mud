#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/room";

void
create_room()
{
    set_short("A grand hall");
    set_long("This is the grand entrance hall of the manor house. " +
        "The high ceiling is decorated in dusty cobwebs, and the "+
        "walls are dingy and bare. Before you are the stairs that once "+
        "led to the upper floor of the building. The stairs have "+
        "collapsed and are now in pieces all over the hall. On the "+
        "floor are the remains of a huge red carpet. There are open " +
        "doors leading into the kitchen area, a library, and what "+
        "seems to be a workroom.\n");
    add_item("floor","You quickly look at the dusty floor but all there is " +
        "to be seen is the old worn out carpet.\n");
    add_item(({"wall","walls"}),"You take a step towards one of the walls. " +
        "It has the normal signs of what most walls have after many years " +
        "of neglect.\n");
    add_item(({"stair","stairs","staircase","pieces"}),"You lean forward " +
        "to look at the stairs. When you get closer you can see they were " +
        "in a very poor condition when they broke down from the platform above. Parts of the " +
        "remains are scattered around the floor.\n");
    add_item("remains","You kneel down and take a closer look at the " +
        "remains. Something looks like a part of a step but it has been a " +
        "long time since someone used it to reach the platform on the " +
        "second floor.\n");
    add_item("step","You lift the step from the ground and touch its worn " +
        "out surface. Clearly this it not how it used to look when the " +
        "carpenter once made it. On the long side of the step you can feel " +
        "two small holes, maybe made by the metal pins that once connected " +
        "the step to the platform on the second floor.\n");
    add_item(({"holes","surface"}),"The surface of the loose step is very " +
        "smooth after years of usage. The small holes in the " +
        "side are there to keep the step in place with the help of two small " +
        "metal hooks sticking out from the plaform above.\n");
    add_item(({"pin","pins"}),"You cast a brief look around the dusty floor " +
        "to see if you can find some pins that were used to connect the " +
        "top step of the stairs to the platform of the second floor.\n" +
        "Alas, after a quick search you realise there is nothing to be " +
        "found.\n");
    add_item("platform","You lift your head and look up at the " +
        "corridor on the second floor. Above your head you can see the " +
        "platform and the metal hooks where the stairs where once attached " +
        "before they collapsed. It might be possible to jump to the " +
        "platform from down here. " + "@@desc_platform@@");
    add_item("carpet","@@desc_carpet");
    add_item("dust","You kneel down and take up some of the dust from the " +
        "carpet. Slowly you let the fine dust glide though your fingers " +
        "back down onto the carpet again.\n");
    add_item("hooks","You look at the hooks fastened to " +
        "the platform high above you. Its not far up, but you cannot reach " +
        "them from down here. But it is very close.\n");
    add_item(({"ceiling"}),
        "The ceiling was once grand, but whatever was painted on it has "+
        "faded under the layer of dust and cobwebs.\n");
    add_item(({"cobwebs", "cobweb"}),
        "These dusty old cobwebs appear to have been abandoned by the " +
        "spiders that once made them, adding to the impression that " +
        "nothing at all lives in this house.\n");
    add_item("upper floor","@@desc_upper");
    set_terrain(TERRAIN_RESIDENCE);
    add_exit("kitchen","north");
    add_exit("library","west");
    add_exit("workroom","east");
    add_exit("south_side","out");
    reset_room();
}

void
reset_room()
{


}

void
init()
{
    ::init();
    add_action("do_knock", "knock");
    add_action("jump_platform","jump");
}

int
do_knock(string str)
{
  if (strlen(str) && (str == "on wall"))
  {
      write("You walk up to a wall and place your ear close. Knocking on " +
          "the wall doesnt make you happier as nothing can be detected " +
          "behind it.\n");
      return 1;
  }
  if (strlen(str) && (str == "on walls"))
  {
      write("You walk around the room and to examine the walls. Placing " +
          "your ear close and tap the walls makes you no happier as nothing " +
          "can be detected behind either of them.\n");
      return 1;

  }
  if (strlen(str))
  {
      write("You make a move to knock on something, but decide its " +
             "useless.\n");
             return 1;
  }
  else
  return 0;
}

string
desc_platform()
{
    object *ob, opp;
    string str;

    if (LOAD_ERR(THIS_DIR + "platform"))
        return "You cant see anything up on the platform.\n";

    opp = (find_object(THIS_DIR + "platform"));

    if (!opp)
        return "You cant see anything up on the platform.\n";

    if (opp->query_prop(OBJ_I_LIGHT) <= 0)
        return "It is dark up the platform, so you can't percieve any " +
        "details.\n";

    ob = FILTER_CAN_SEE(all_inventory(opp), TP);

    if (!sizeof(ob))
        return "You can't see anything special on the platform.\n";

    return "Up on the platform you see "
         + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".\n";
}

string
desc(object ob)
{
    if (living(ob))
        return COMPOSITE_LIVE(ob);
    else
        return LANG_ADDART(ob->short());
}

int
jump_platform(string str)
{
    if (!(str))
    {
        write("Jump where?\n");
        return 1;
    }

    if (strlen(str) &&
        (str == "to platform" || str == "to hooks" || str == "platform"))
    {
            write("Gathering all of your strength you jump towards the " +
                "platform. You manage to get a grip on one of the hinges "+
                "and swing your body up onto the platform.\n");

            say(({METNAME + " crouches down, and making a mightly leap "+
                "towards the platform, manages to get a handhold and "+
                "swing up onto it.\n",
            TART_NONMETNAME + " crouches down, and making a mightly leap "+
                "towards the platform, manages to get a handhold and "+
                "swing up onto it.\n",
            "You feel a movement in the room"}), TP);
        tell_room(THIS_DIR + "platform",
            ({METNAME + " takes a huge jump and manages to get a grip " +
                "and swings up onto the platform.\n",
            TART_NONMETNAME + " takes a huge jump and manages to get a grip " +
                "and swings up onto the platform.\n",
            "You hear a loud THUD right beside you as if something just " +
                "landed here.\n"}), TP);
            TP->move_living("M", THIS_DIR + "platform", 1);
            return 1;
    }
}


string
desc_upper()
{
    string txt;

    txt = "You look up at what you can see of the upper " +
        "floor from down here. But from this position " +
        "it is hard to see much at all.\n";


    say(({METNAME + " looks up at what can be seen from down here " +
        "of the upper floor.\n",
        TART_NONMETNAME + " looks up at what can be seen from down here " +
        "of the upper floor.\n",
        ""}), TP);

    return txt;


}

string
desc_carpet()
{
    string txt;

    txt = "You kneel down and take up some of the dust from the " +
        "carpet. Slowly you let the fine dust glide though your " +
        "fingers back down onto the carpet again.\n";


    say(({METNAME + " kneels down and take up some of the dust from the " +
        "carpet. Slowly " +TP->query_pronoun()+ " let the fine dust glide " +
        "though " +TP->query_possessive()+ " fingers back down onto the " +
        "carpet again.\n",
        TART_NONMETNAME + " kneels down and take up some of the dust from the " +
        "carpet. Slowly " +TP->query_pronoun()+ " let the fine dust glide " +
        "though " +TP->query_possessive()+ " fingers back down onto the " +
        "carpet again\n",
        "Suddenly some dust swirls around on the carpet.\n"}), TP);

    return txt;


}
