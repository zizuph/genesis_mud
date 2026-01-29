/* 
      Flight room for polymorphed dragons

      Arman 2017
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/tharkadan/local.h"

inherit "/d/Krynn/std/outside_room";

mapping gLoc = ([]);
public string destination_room = "/d/Krynn/tharkadan/room/vale2"; 
public string failed_destination;

#define WOHS_DRAGON_DESTINATION "_wohs_dragon_destination_prop"

string  *fall_locs = ({ ROOM + "vale3.c", 
                        ROOM + "path9.c", 
                        ROOM + "fforest2.c", 
                        ROOM + "fforest3.c",
                        ROOM + "path12.c" });

string
tod_drag_desc()
{
    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
            return "The sun is just rising above the clouds in the " +
                "eastern sky, illuminating them a brilliant white.\n";
	    break;
        case TOD_TWILIGHT:
	    return "The sun setting in the west turns the clouds " +
                "beneath you a vivid pink.\n";
            break;
        case TOD_NIGHT:
            return "The night sky above you is filled with stars, while " +
                "the twin moons Solinari and Lunitari illuminate the " +
                "clouds beneath you with a reddish white light.\n";
	    break;
	case TOD_DAY:
            return "The sun rises high above you, illuminating the " +
              "clouds beneath you a brilliant white.\n";    
            break;
    }
}

void
create_room()
{
    set_short("high in the sky above the Tharkadan mountain range");
    set_long("You find yourself flying high in the sky, skimming " +
         "over the top of a carpet of clouds and the snow-covered " +
         "Tharkadan mountain range. " +tod_drag_desc());
    add_item(({"clouds","carpet of clouds","carpet","billowing clouds" }),
         "Beneath you billowing clouds roll across the sky, covering " +
         "the ground below you from sight, with only snow-capped peaks " +
         "poking through.\n");
    add_item(({"mountains","snow","snow-covered mountains","peaks",
         "snow-capped peaks","tharkadan mountain range","mountain range",
         "range"}), "Below you can make out the snow-capped peaks of " +
         "the mountains of the Tharkadan mountain range.\n");
    add_item(({"sky"}),"You are flying high in the sky above the " +
         "clouds! The ground is far beneath you, out of sight.\n");
    add_item(({"ground"}),"The ground is far beneath you, although you " +
         "cannot see it thanks to a carpet of clouds that stretch " +
         "across the sky.\n");

    add_item("sun", "@@sun_desc");
    add_item(({"moons", "moon"}), "@@moon_desc"); 
    add_item("solinari", "@@solinari_desc");
    add_item("lunitari", "@@lunitari_desc");
    add_item("nuitari", "@@nuitari_desc");

    add_prop(ROOM_IN_AIR, 1);
    add_prop(ROOM_M_NO_ATTACK, "They are flying too far away for you " +
         "to attack.\n");
    add_prop(ROOM_M_NO_TELEPORT, 1);

}

/*
public void
set_destination_loc(string pl, string room)
{
    destination_room = room;
    gLoc[pl] = room;
}

mapping
query_destination_loc()
{
    return gLoc;
}
*/

varargs void
msg(string str1, object pl, string str2 = "")
{
    pl->catch_msg(str1 + "\n");
    if (strlen(str2))
    {
        tell_room(this_object(), str2 + "\n", pl);
    }
}

void
do_act(object pl)
{
    if (!pl || (environment(pl) != this_object()))
    {
        return;
    }

    switch (random(3))
    {
        case 0:
            msg("You beat your wings as you swiftly fly towards your " +
                "destination.", pl, QCTNAME(pl)+ " beats " + HIS(pl)+ 
                " wings as " +HE(pl)+ " flies swiftly towards " +
                HIS(pl)+ " destination.");
            break;
        case 1:
            msg("You glide gracefully through the clouds, your " +
                "leathery wings fully extended.", pl, QCTNAME(pl)+ 
                " glides gracefully through the clouds, " 
                +HIS(pl)+ " leathery wings fully extended.");
            break;
        case 2:
            msg("You dive down towards the clouds, gaining some speed.", 
                pl, QCTNAME(pl)+ " dives down towards the clouds, " +
                "gaining speed.");
            break;
        case 3:
            msg("", pl);
    }

    set_alarm(15.0 + itof(random(10)), 0.0, &do_act(pl));
}

public string
query_dragon_destination()
{
    if(!destination_room)
      return failed_destination;
    else
      return destination_room;
}

void
do_arrive(object pl)
{
    if (!pl || (environment(pl) != this_object()))
    {
        return;
    }

    msg("With a predatory shriek, you dive down through the clouds and " +
        "land at your destination.", pl, "With a predatory shriek, " +
        QTNAME(pl)+ " dives down through the clouds and out of sight.");
    pl->move_living("M", query_dragon_destination(), 1, 0);
    tell_room(E(pl), "A shriek from the skies draws your attention to " +
        QTNAME(pl)+ " flying swiftly towards you and gracefully " +
        "landing.\n", ({ pl }) );
    pl->remove_prop(WOHS_DRAGON_DESTINATION);

    return;
}

void
remove_nonliving(object ob)
{
      tell_room(E(ob), "The " +ob->short()+ " falls through the clouds " +
           "and vanishes below.\n", ({ ob }) );
      ob->remove_object();
      return;
}

void
remove_nondragon2(object ob)
{
   string random_room = fall_locs[random(sizeof(fall_locs))];

   if(E(ob) != TO)
       return;

   msg("You plummet to the ground with a crash, the serpentine figurine " +
        "glowing briefly and slowing your fall from being fatal.", ob, 
        QCTNAME(ob) + " falls into the clouds and vanishes from sight.");

   ob->move_living("M", random_room, 1, 0);
   tell_room(E(ob), "A shriek from above draws your attention to " +
        QTNAME(ob)+ " falling from the sky and crashing into the ground " +
        "before you!\n", ({ ob }) );

    ob->heal_hp(-3000);
    return;
}


void
remove_nondragon(object ob)
{
    msg("No longer in dragon form, you begin to plummet down to " +
        "earth! You shriek, and frantically flap your arms as you try " +
        "and figure out how to fly!", ob, "No longer in dragon form, " +
        QTNAME(ob)+ " begins plummeting down towards the ground!");

    set_alarm(8.0, 0.0, &remove_nondragon2(ob));

    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!ob->query_prop(LIVE_I_IS))
    {
      set_alarm(2.0, 0.0, &remove_nonliving(ob));
      return;
    }

    if(ob->query_race() != "dragon" && !ob->query_wiz_level())
    {
      set_alarm(2.0, 0.0, &remove_nondragon(ob));
      return;
    }

    if(ob->query_prop(WOHS_DRAGON_DESTINATION))
      destination_room = ob->query_prop(WOHS_DRAGON_DESTINATION);

    //if teleport fails, you get sent back to where you came from.
    failed_destination = file_name(from);

    set_alarm(100.0 + itof(random(35)), 0.0, &do_arrive(ob));
    set_alarm(10.0 + itof(random(5)), 0.0, &do_act(ob));
}

void
leave_inv(object from, object to)
{
    ::leave_inv(from, to);
}

public string
sun_desc()
{
    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
            return "The sun is hanging low in the northern sky.\n";
	    break;
        case TOD_TWILIGHT:
	    return "The sun is sinking into the northern sky.\n";
            break;
        case TOD_NIGHT:
            return "There is no sun to be seen.\n";
	    break;
	case TOD_DAY:
            return "The sun is shining brightly in the daytime sky.\n";    
            break;
    }
}

public string
moon_desc()
{
    if (GET_TIMEOFDAY != TOD_DAY)
        return "You can see two moons in the sky, they are Solinari and " +
            "Lunitari.\n";
    else
        return "You can't see any moons in the daylight.\n";

}

public string
solinari_desc()
{
    if (GET_TIMEOFDAY != TOD_DAY)
        return "Solinari is a " + GET_MOON_PHASE(SOLINARI) + " silver " +
            "moon.\n";
    else
        return "Solinari is not visible in daylight.\n";
}

public string
lunitari_desc()
{
    if (GET_TIMEOFDAY != TOD_DAY)
        return "Lunitari is a red " + GET_MOON_PHASE(LUNITARI) + 
            " moon.\n";
    else
        return "Lunitari is not visible in daylight.\n";
}
 
public string
nuitari_desc()
{
    if (!TP->query_prop("_i_can_see_nuitari"))
      return 0;
    if (GET_TIMEOFDAY != TOD_DAY)
        return "Nuitari is a black " + GET_MOON_PHASE(NUITARI) + 
            " moon.\n";
    else
        return "Nuitari is not visible in daylight.\n";
}
