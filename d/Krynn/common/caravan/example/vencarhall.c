#pragma strict_types
#include "/d/Shire/defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>




create_room()
{
    set_short("A rand hall");
    set_long("This is the grand entrance hall of this manor." +
        "Right in front of you there are the stairs leading up to "
        "the second floor of the building. The stairs have collapsed " +
        "and is now in pieces all over the hall .On the floor is a huge red " +
        "carpet covering almost the entire hall. There are open doors " +
        "leading into the kitchen area, a library and what seems to be a " +
        "workroom.\n");
    add_item("floor","You quickly look at the dusty floor but all there is " +
        "to be seen is the old worn out carpet.\n");
    add_item(({"wall","walls"}),"You take a step towards one of the walls. " +
        "It has the normal signs of what most walls have after many years " +
        "of usage.\n");
    add_item(({"stair","stairs","staircase","pieces"}),"You reach forward to " +
        "look at the stairs. When you get closer you can see they where in a " +
        "very poor condition when they broke down. Parts of the remains are scattered " +
        "around the floor.\n");
    add_item("remains","You kneel down and take a closer look at the remains. " +
        "Something looks like a part of a step but it has been a long time " +
        "since someone used it to reach the second floor.\n");
    add_item("step","You lift the step from the ground and touch its worn " +
        "out surface. Clearly this it not how it used to look when the " +
        "carpenter once made it. On the longside of the step you can feel " +
        "two small holes after the metal pins that once connected the step to " +
        "the platform on the second floor.\n");
    add_item(({"pin","pins"}),"You cast a brief look around the dusty floor " +
        "to see if you can find some pins that was used to connect the " +
        "top step of the stairs to the platform of the second floor.\n" +
        "Alas, after a quick search you realise there is nothing to be found.\n");
    add_item("platform","You lift your head and look up at the unreachable " +
        "corridor on the second floor. Above your head you can see the platform, " +
        "and the metal hooks where the stairs where once attached before " +
        "they collapsed. " + "@@desc_platform@@" + "\n");
    add_item("carpet","You reach down and touch this dusty old carpet. Once " +
        "red, but now the colour has almost completely vanished. Years of use " +
        "clearly took its toll.\n");
    add_item("dust","You kneel down and take up some of the dust from the carpet. " +
        "Slowly you let the fine dust glide though your fingers back down onto the " +
        "carpet again.\n");
    add_item("hooks","You narrow your eyes and view the hooks fastened to the " +
        "platform high above you. On a quick glance it seems to be impossible " +
        "to reach them from down here.\n");
    set_terrain(TERRAIN_RESIDENCE);
    add_exit(THIS_DIR + "kitchen","north");
    add_exit(THIS_DIR + "library","west");
    add_exit(THIS_DIR + "workroom","east");
    add_exit(THIS_DIR + "main_entrance","out");
    reset_room();
}

reset_room()
{

    object troll;
    if (!present("cave troll", this_object()))
        troll = clone_object("/d/Shire/monster/troll");
        troll->move(this_object());
}

init()
{
    ::init();
    add_action("do_knock", "knock");
    add_action("jump_platform","jump");
}

int
do_knock(string str)
{
  if (strlen(str) && (str == "on wall")
  {
      write("You walk up to a wall and place your ear close. Knocking on " +
          "the wall doesnt make you happier as nothing can be detected behind " +
          "it.\n");
      return 1;
  }
  if (strlen(str) && (str == "on walls")
  {
      write("You walk around the room and to examine the walls. Placing your " +
          "ear close and tap the walls makes you no happier as nothing can " +
          "be detected behind either of them.\n");
      return 1;

  {
  else
      if (strlen(str))
          {
              write("You make a move to knock on something, but decide its " +
                  "unnecesarry.\n");
              return 1;
          }
    return 0;
}

string
desc_platform()
{
    object *ob, opp;
    object *liv;
    string str;

    if (LOAD_ERR(THIS_DIR + "platform"))
        return "";

    opp = find_object(THIS_DIR + "platform");

    if (!opp)
        return "";

    if (opp->query_prop(OBJ_I_LIGHT) <= 0)
        return "It is dark up the platform, so you can't percieve any details.\n";

    ob = FILTER_CAN_SEE(all_inventory(opp), TP);

    if (!sizeof(ob))
        return "You can't see anything special on the platform.\n";

    return "On the other side you can see "
         + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".\n";
}

int
jump_platform(string str)
{
    if (strlen(str) && (str == "to platform" || str == "to hooks")
    {
        if ((this_player->query_race()) == "dwarf" || "hobbit" || "gnome")
        {
            write("You gather your strength and jump to reach the platform, " +
                "but you cant reach it. If you where taller perhaps...\n");
            say(QCTNAME(TP) + " bends down and take a jump towards the platform " +
                "but fails miserably and falls down again.\n");
            tell_room(THIS_DIR + "platform",
                CAP(LANG_ADDART(TP->query_nonmet_name())) +
                " takes a jump towards the platform but fail and fall back down " +
                "into the hall again.\n");
            return 1;
        }
        else
        {
            write("Gathering all of your strength you jump towards the hinges " +
                "and easily manage to get a grip and swing your body up on the " +
                "platform.\n");
            this_player()->move_living("M", THIS_DIR + "platform", 1);
            say(QCTNAME(TP) + " bends down and take a huge jump towards the " +
                "platform and manages to get a foothold on the second floor.\n");
            tell_room(THIS_DIR + "platform",
                CAP(LANG_ADDART(TP->query_nonmet_name())) +
                " takes a huge jump and manages to get a grip on the hinges " +
                "and climb up onto the platform.\n");
            return 1;
        }
    }
}

