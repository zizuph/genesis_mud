/*
 *	/d/Gondor/anorien/nimrais/quest/rock.c
 *
 *	Coded by Randon and Olorin.
 *
 *	Modification log:
 *	27-Jan-1997, Olorin:	General revision,
 *				changed inheritance.
 *  25-March-2020, added random gem drop.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "dirdefs.h"
 
public int     climb(string str);
public int     do_enter(string str);
public string  long_desc();
public void    do_shiver(mixed who);
public void    living_check();
public void    reset_room();
string		   gem_types();

static object  Eyrie,
               Eagle;
 
public void
create_gondor()
{
    set_short("on a projecting rock");
    set_long(long_desc);
    add_item(({ "wall", "mountain wall" }), "It is very steep and rather "
      + "smooth. You could climb down, though.\n");
    add_item(({"eagle", "flying eagle"}),BSN(
      "High above the rock on which you are standing, " +
      "you can see an eagle circling the mountain. "));
    add_item(({"rock", "cliff", "cliff face"}), BSN(
      "The rock is projecting out from the cliff face high over the " +
      "hills below you. You cannot climb any higher here. Close to where " +
      "the rock projects from the rock wall, there are a few plants " +
      "growing."));
    add_item(({"view", "hills"}), BSN(
      "From your position high up on this rock, you have a tremendous view " +
      "north. You can see the northern foothills of the White Mountains " +
      "stretching out below you. Of those, the most prominent are the beacon " +
      "hills, which run in a line between the Druadan Forest far to the " +
      "northeast from here and the Firienwood on the borders of Rohan " +
      "about as far to the northwest. " +
      "Beyond the line of the beacon hills you can see the plains of Anorien."));
    add_item(({"beacons","hill","hills","beacon hills"}), BSN(
      "The beacon hills are the northernmost hills of the White Mountains. " +
      "On top of those hills, there are guards which will light " +
      "beacon fires in times of war, calling for help from Rohan or Gondor. " +
      "They are from east to west Amon Din, Eilenach, Nardol, Erelas, " +
      "Min-Rimmon, Calanhad, and the Halifirien on the borders of Rohan " +
      "in Firienwood."));
    add_item(({"firienwood","halifirien"}), BSN(
      "The Halifirien is the westernmost of the beacon hills between " +
      "Rohan and Gondor. It rises out of the green of Firienwood on the borders " +
      "of Rohan far northwest of here. "));
    add_item(({"druadan forest","amon din","eilenach"}), BSN(
      "Amon Din is the easternmost of the beacon hills between Gondor " +
      "and Rohan. From here, it rises behind dark Druadan Forest and Eilenach " +
      "in Druadan Forest. From the top of Amon Din, one can see the Mindolluin " +
      "and the Tower of Minas Tirith."));
    add_item(({"nardol","erelas","min-rimmon","calenhad"}), BSN(
      "Nardol, Erelas, Min-Rimmon, and Calenhad are the beacon hills between " +
      "Druadan Forest and Firienwood. They are the northernmost tops " +
      "of the White Mountains, rising south of the wide green plains of " +
      "Anorien. "));
    add_item(({"anorien","plain","plains","road"}), BSN(
      "Far north of the foothills of the White Mountains you can see " +
      "the wide green plains of Anorien. A dark band is barely visible " +
      "running over the plains just north of the hills, this might be the " +
      "road from Edoras to Minas Tirith."));



    set_up_herbs( ({ HERB_DIR+"frostheal", HERB_DIR+"madwort", }), 
		 ({"ground", "cliff", "rock"}), 8);

   clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);

    reset_room();
}


string
gem_types() 
{
    string *gemtypes =
                 ({"agate_fire", "alexandrite", "beryl_red", "diamond", 
                   "emerald", "jade", "moonstone", "opal","pearl", 
                   "pearl_black", "ruby", "topaz", "topaz_yellow", 
                   "tourmaline_pink"});
    return ONE_OF_LIST(gemtypes);
}
 
public void
reset_room()
{
    ::reset_room();

    if (!objectp(Eyrie))
    {
        Eyrie = clone_object(THIS_DIR + "obj/eyrie");
        Eyrie->move(TO);
    }

    switch (random(3))
    {
        case 0:
        case 1:
            break;
        case 2:
            setuid();
            seteuid(getuid());

            clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);
            break;
        default:
            break;
    }
}
 
public void
init()
{
    ::init();
    add_action(climb,    "climb");
    add_action(do_enter, "enter");
}
 
public void
add_eagle()
{
    Eagle = clone_object(THIS_DIR + "monster/eagle");
    remove_item("eagle");
    Eagle->move(TO);
    tell_room(TO, "The eagle descends from the sky.\n");
    tell_room(find_object("/d/Gondor/anorien/nimrais/quest/base"),
        "A bird descends onto the projecting rock.\n");
}
 
public object query_is_eagle() { return Eagle; }
 
public object query_eyrie() { return Eyrie; }

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
	set_alarm(15.0 + rnd()*20.0, 0.0, &do_shiver(ob));
}
 
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    set_alarm(10.0, 0.0, living_check);
}
 
void
do_shiver(mixed who)
{
    if (!objectp(who)) 
	return;
    if (!present(who, TO)) 
	return;
    who->catch_msg("Brrrrr!!!\n");
    say(QCTNAME(who) + " shivers from cold.\n", who);
    set_alarm(15.0 + rnd()*20.0, 0.0, &do_shiver(who));
}
 
public void
living_check()
{
    if (!sizeof(FILTER_LIVE(all_inventory(TO))) && Eyrie)
	Eyrie->quest_check();
}
 
public string
long_desc()
{
    string text;
    text = "You are standing on a rock projecting from the cliff face "
       + "from where you have a splendid view to the north. "
       + "You are shivering from the cold because of the icy winds. ";
 
    if (tod() == "night")
        text += "As it is night, you can see many stars glimmering in the "
              + "sky. ";
    if (tod() == "early morning" || tod() == "morning")
        text += "The sun is on its way to the sky. ";
    if (tod() == "noon" || tod() == "afternoon")
        text += "The sun is shining. ";
    if (tod() == "evening")
        text += "The sun is setting in the horizon. ";
 
    if (tod() != "night")
        text += "Far below you can see the base of the mountain. ";
 
    text += "You see an eagle's eyrie here. It is close to the mountain wall, "
          + "so it is somewhat protected from the winds. You cannot climb "
          + "higher because the wall is too smooth and steep, "
          + "but you might be able to climb down again. ";
    if (!objectp(Eagle))
        text += "You see an eagle circling the mountain. ";
 
    return BS(text + "\n");
}
 
public int
climb(string str)
{
    int skillvalue, rnd, acrobat;
 
    NF("Climb what?\n");
    if (str == "up") {
        write("You can't climb higher, because the wall is too smooth and "
            + "steep.\n");
        return 1;
    }
    if (str == "down") {
        skillvalue = TP->query_skill(SS_CLIMB);
        acrobat = TP->query_skill(SS_ACROBAT);
        acrobat = 100 - ((80 * acrobat) / 100);
        /* I don't know if this check is really needed, but maybe some
           players have a teleport spell. :) --Randor    */
        if (skillvalue < 10) {
            write("Your aren't very skilled in climbing, so you dare not "
                + "try it.\n");
            return 1;
        }
        rnd = random(20);
        if (skillvalue + rnd > 25) {
            write("You skillfully climb down the wall.\n");
            say(QCTNAME(TP) + " begins to climb down the wall.\n", TP);
            TP->move_living("M", THIS_DIR + "wall3", 1);
            say(QCTNAME(TP) + " descends from the projecting rock.\n", TP);
            return 1;
        }
        if (skillvalue + rnd > 20) {
            write("You begin to climb down, but you lose your grip!\n\n" +
              "Fortunately you don't fall much.\n");
            say(QCTNAME(TP) + " begins to climb down the wall.\n"
              + CAP(TP->query_pronoun()) + " loses " +
              TP->query_possessive() + " grip!\n", TP);
            /* Just some scratches... */
            TP->heal_hp(-random(20) - 20);
            TP->move_living("M", THIS_DIR + "wall3", 1);
            say(QCTNAME(TP) + " loses " + TP->query_possessive() +
              " grip while descending from the projecting rock,\n" +
              "but doesn't fall much.\n", TP);
            return 1;
         }
 
         write("You begin to climb down, but you lose your grip!\n");
         say(QCTNAME(TP) + " begins to climb down the wall.\n"
           + CAP(TP->query_pronoun()) + " loses " +
           TP->query_possessive() + " grip!\n", TP);
         tell_room(find_object(THIS_DIR + "wall3"), "You hear a terrible "+
           "scream as someone falls by.\n");
         find_object(THIS_DIR + "wall3")->do_fall(TP,1);
         return 1;
    }
    return 0;
}

public int 
do_enter(string str)
{
    if(!strlen(str) || ((str != "eyrie") && (str != "nest")))
	NF("Enter what, the eyrie?\n");
    else
	NF("You cannot enter the eyrie, it is large, but not that large!\n");
    return 0;
}
