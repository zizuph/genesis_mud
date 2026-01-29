/*
 * Standard file for Minas Morgul
 * 
 * July 1993 by Olorin
 * 
 * modelled on Hamurabbi's town.c for Edoras
 * and Elessar's street.c for Minas Tirith
 *
 * Modification log:
 * Olorin, December 1995: Changed feeling.c to be inherited.
 */
#pragma strict_types

inherit "/std/room";
inherit "/d/Gondor/morgul/feeling.c";
inherit "/d/Gondor/common/lib/time.c";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void   add_barrack_street(string extra = 0);
public void   add_dark_street(string extra = 0);
public void   add_morgul_road(string extra = 0);
public void   add_top_walls(string extra = 0);
public void   add_tower(string extra = 0);
public void   add_walls(string extra = 0);

static string  extraline,
               side,
	       roadstr,
               short_desc;
static int     road;       /* 1 = wall,        2 = Morgul Road, 
                              3 = Dark Street, 4 = Barracks Street 
                              5 = inside a building,
                              9 = extra: short_desc
                              0 = in Minas Morgul              */

public void
create_morgul_room()
{
}

nomask void
create_room()
{
    create_morgul_room();

    add_prop(ROOM_M_NO_TELEPORT, "The Dark Lord of Arda prevents your magicks " +
                                 "to work properly and you can not teleport to your " +
                                 "destination.\n");

    switch(road)
    {
    case 0:  
        roadstr = "in the "+side+"ern parts of Minas Morgul"; break;
    case 1:  
        roadstr = "on top of the "+side+"ern walls of Minas Morgul"; 
        add_top_walls();
        break;
    case 2:  
        roadstr = "on the Morgul Road in the "+side+"ern parts of Minas Morgul"; 
        add_morgul_road();
        add_tower();
        break;
    case 3:  
        roadstr = "on Dark Street in the "+side+"ern parts of Minas Morgul"; 
        add_dark_street();
        break;
    case 4:  
        roadstr = "on Barracks Street in the "+side+"ern parts of Minas Morgul"; 
        add_barrack_street();
        add_walls();
        break;
    case 5:  
        roadstr = "in a dark building in the "+side+"ern parts of Minas Morgul"; 
        add_prop(ROOM_I_INSIDE,1);
        add_prop(ROOM_I_LIGHT,0);
        break;
    case 9:
        if (!stringp(short_desc))
            roadstr = "in Minas Morgul";
        else
            roadstr = short_desc;
        break;
    default:
        roadstr = "in Minas Morgul";
         break;
    }

    set_short(roadstr);
    set_long("@@describe@@");
    add_item(({"shadow","shadows"}), "@@exa_shadow@@");
}

string
describe() 
{
    int     feeling = query_feeling(TP);
    object  clock = find_object(CLOCK);
    string  time = clock->query_time_of_day(),
            moon = clock->query_moon(),
            long_desc = "You are "+roadstr+".";

    if (!query_prop(ROOM_I_INSIDE)) 
    {
        long_desc += " It is "+time+".";
        switch(time)
        {
        case "night":
            switch(moon)
            {
            case "dark":
                long_desc += " The air is chilly, and the dark sky is full of clouds.";
                switch (feeling)
                {
                case -1: 
                    long_desc += " Comfortable darkness is all around, filling you with"
                      + " the feeling of security and calmness.";
                    break;
                case  1:
                    long_desc += " The darkness is oppressive; shadows seem to threaten "
                      + "you from everywhere.";
                    break;
                }
                break;
            case "full":
                long_desc += " The full moon is shining through clouds,";
                switch (feeling)
                {
                case -1: 
                    long_desc += " that filter out most of its harsh light so that he "
                      + "cannot penetrate the cloak of darkness enveloping you.";
                    break;
                case  0:
                    long_desc += " creating a ghastly feeling.";
                    break;
                case  1:
                    long_desc += " casting frightening shadows onto every wall.";
                    break;
                }
                break;
            case "waxing crescent":
            case "waning crescent":
                long_desc += " The moon is a thin sickle behind dark clouds,";
                switch (feeling)
                {
                case -1: 
                    long_desc += " hardly noticeable and powerless to penetrate the "
                      + "comforting darkness.";
                    break;
                case  0:
                    long_desc += " hardly visible.";
                    break;
                case  1:
                    long_desc += " almost completely hidden and powerless to penetrate "
                      + "the suffocating blanket of darkness that lies heavily upon you.";
                    break;
                }
                break;
            case "waxing gibbous":
            case "waning gibbous":
                long_desc += " The moon is a pale gibbous shape behind dark clouds,";
                switch (feeling)
                {
                case -1: 
                    long_desc += " powerless to penetrate the comforting darkness.";
                    break;
                case  0:
                    long_desc += " hardly visible.";
                    break;
                case  1:
                    long_desc += " powerless to penetrate the suffocating blanket of "
                      + "darkness that lies heavily upon you.";
                    break;
                }
                break;
            }
            break;
        case "early morning":
            long_desc += " The black clouds above the mountain ridge in the "
              + "east are beginning to glow red,";
            switch (feeling)
            {
            case -1: 
                long_desc += " but down here in the valley, the friendly "
                  + "black of the night is still unbroken.";
                break;
            case  0: 
                long_desc += " a sure sign that finally the sun has risen to "
                  + "give light to a new day.";
                break;
            case  1: 
                long_desc += " but here in the valley, the shadows still reign "
                  + "and terrorize you with their great shapeless black masses.";
                break;
            }
            break;
        case "morning":
            long_desc += " Dark clouds veil the sun that has risen over the "
              + "mountain range in the east,";
            switch (feeling)
            {
            case -1: 
                long_desc += " giving ample protection against the fearful light, "
                  + "and surrounding you with gentle shadows.";
                break;
            case  0: 
                long_desc += " blocking out the light almost completely.";
                break;
            case  1: 
                long_desc += " making the morning even more oppressive and gloomy "
                  + "than the night.";
                break; 
            }
            break;
        case "noon":
        case "afternoon":
            long_desc += " Dark clouds like a leaden wall cover the whole sky. "
              + "Hardly a single beam of the sun can pierce the";
            switch (feeling)
            {
            case -1: 
                long_desc += " calming darkness, giving you security and comfort.";
                break;
            case  0: 
                long_desc += " darkness and shadows.";
                break;
            case  1: 
                long_desc += " terrible shadows around you.";
                break; 
            }
            break;
        case "evening":
            long_desc += " Through a thick layer of clouds the sinking sun is "
              + "sending the last rays from the west.";
            switch (feeling)
            {
            case -1: 
                long_desc += " The dark embrace of the night is nigh, giving "
                  + "you hope and joy.";
                break;
            case  0: 
                long_desc += " Soon the night will have you.";
                break;
            case  1: 
                long_desc += " Nightfall is threatening, and out of every "
                  + "corner more shadows seem to creep, trying to reach and "
                  + "devour you.";
                break; 
            }
            break;
        }
    }

    if (strlen(extraline))
        long_desc += " " + extraline;

    switch (feeling)
    {
    case -1:
        break;
    case  0:
        long_desc += " This place seems to be out of a terrible dream. It is "
          + "oppressive and makes you feel nervous.";
        break;
    case  1:
        long_desc += " This dreadful place makes you fear for your life. "
          + "Dark shadows all around seem to weigh upon you like a terrible "
          + "burden, draining your life.";
        break;
    }

    return BSN(long_desc);
}

public void
init()
{
    ::init();

    add_action(check_time, "time");
}

public void    set_extraline(string s) { extraline = s; }
public int     set_road(int i) { road = i; return i; }
public string  set_roadstr(string s) { roadstr = s; return roadstr; }
public int     query_road(int i) { return road; }

public int 
set_side(string str) 
{ 
    if (!strlen(str)) return 0;
        side = str;
    return 1;
}

public string query_side() { return side; }

public object
clone_npc(object npc, string npc_file)
{
    if (objectp(npc))
        return npc;
    npc = clone_object(npc_file);
    npc->arm_me();
    npc->move_living("down", TO);

    return npc;
}

public void
clone_npcs(object *npcs, string filename, float delay = 30.0)
{
    int     n = sizeof(npcs),
            i;

    for (i = 0; i < n; i++)
    {
        if (!objectp(npcs[i]))
        {
            npcs[i] = clone_npc(npcs[i], filename);
            set_alarm(delay / 2.0 + rnd() * delay, 0.0,
                &clone_npcs(npcs, filename, delay));
            break;
        }
    }
}

public int
query_allow_escape(object enemy, object attacker)
{
    int     chance;

    if (enemy->query_npc())
        return 1;

    chance = 50 + attacker->query_stat(SS_DEX) - enemy->query_stat(SS_DEX);
    if (chance > 90)
        chance = 90;
    else if (chance < 10)
        chance = 10;
    if (random(100) < chance)
        return 0;
    return 1;
}

int
check_exit()
{
    int     feeling = query_feeling(TP),
            panic;
    string  dir = query_verb();
    object  attacker;

    if (objectp(attacker = TP->query_attack()))
    {
        if (objectp(present(attacker, TO)) && !interactive(attacker) &&
            !query_allow_escape(TP, attacker))
        {
            TP->catch_msg(QCTNAME(attacker)+" stops you from running away!\n");
            say(QCTNAME(attacker)+" stops "+QTNAME(TP)+" from leaving.\n",
                ({TP, attacker}) );
            return 1;
        }
    }

    if (feeling > -1)
    {
        panic = 120 - TP->query_stat(SS_DIS);
        if (panic > 90)
            panic = 90;
        else if (panic < 0)
            panic = 0;
        panic = random(panic) + 10;
        panic = (feeling+1) * panic;
        TP->add_panic(panic);

        switch (panic)
        {
        case 171..1000:
            write(BSN("Panic ties up your throat, cold sweat is drenching your "
              + "clothes, and fright seems to bind your limbs. Creeping, with "
              + "terrifying slowness, you drag yourself further "+dir+"."));
            break;
        case 141..170:
            write(BSN("Terror lies like a terrible weight upon your shoulders, "
              + "and almost makes it impossible to move; you barely manage "
              + "to go further "+dir+"."));
            break;
        case 111..140:
            write("Terror and panic fill you when you walk "+dir+".\n");
            break;
        case 81..110:
            write("In spite of the panic you feel rising inside you, you walk "+dir+".\n");
            break;
        case 61..80:
            write("Terrible shadows frighten you from every corner when you walk "+dir+".\n");
            break;
        case 41..60:
            write("Without hope you walk "+dir+", bowed down as if under a terrible burden.\n");
            break;
        case 21..40:
            write("This places gives you the creeps, but you take heart and go "+dir+".\n");
            break;
        default:
            break;
        }
        TP->add_fatigue(-panic/20);
    }
    if (TP->query_wiz_level()) 
        write("Wizinfo: feeling: " + feeling + ", panic: " + panic + ", fatigue: " + panic/20 + "\n");
    return 0; 
}

public int
block_npc()
{
    if (TP->query_npc() && !objectp(TP->query_attack()))
        return 1;
    return check_exit();
}

public int
stairs(string where = "up the flight of stairs leading to the first floor")
{
    if (TP->query_npc() && !objectp(TP->query_attack()))
        return 1;
    if (check_exit())
        return 1;
    write("You climb "+where+".\n");
    say(QCTNAME(TP) + " climbs "+where+".\n");
    return 0;
}

public int
tower_stairs(string where = "down")
{
    if (check_exit())
        return 1;
    switch (where)
    {
    case "down":
        write("You climb down the flight of stairs into the basement of the tower.\n");
        break;
    case "uptop":
        write("You climb up the flight of stairs onto the top of the tower.\n");
        break;
    case "top":
        write("You climb down the flight of stairs into the tower.\n");
        break;
    case "up":
        write("You climb up the flight of stairs to the ground floor of the tower.\n");
        break;
    }
    return 0;
}
public int
set_short_desc(string str)
{
    if (!stringp(str))
        return 0;

    if (road != 9)
    {
        write("THERE IS A BUG HERE! \n" +
            "Please make a bug report! \n" +
            "Error number: " + road + ".\n");
        return 0;
    }
    short_desc = str;
    return 1;
}
  
public int
block_exit()
{
    object  stopper;

    if (objectp(stopper = TP->query_attack()))
    {
        write(CAP(LANG_ADDART(stopper->query_nonmet_name()))
          + " stops you from going there!\n");
        return 1;
    }
    if (objectp(stopper = present("_morgul_monster",TO)))
    {
        if (CAN_SEE_IN_ROOM(stopper) && CAN_SEE(stopper, TP))
        {
            write(CAP(LANG_ADDART(stopper->query_nonmet_name()))
              + " stops you from going there!\n");
            stopper->init_attack();
            return 1;
        }
    }
    return check_exit();
}

public string
exa_window(string desc, string street_file)
{
    object  street = find_object(street_file),
           *people;

    people = FILTER_LIVE(all_inventory(street));
    if (sizeof(people))
        desc += " You can see " + COMPOSITE_LIVE(people) + " on the street.";
    else
        desc += " There is no one on the street.";

    return BSN(desc);
}

public string
exa_shadow()
{
    int     feeling = query_feeling(TP);
    switch(feeling)
    {
    case -1:
        return "The shadows around you are offering comfortable darkness.\n";
        break;
    case 0:
        return "Impenetrable dark shadows surround you, enveloping you "
          + "like frightening clouds.\n";
        break;
    case 1:
        return "Dark shadows hang everywhere, pressing heavily down on you, "
          + "inspiring nothing but the blackest despair.\n";
        break;
  }
}

public void
add_tower(string extra = 0)
{
    string  desc = 
        "Like a dark and menacing shadow the great tower of Minas Morgul "
      + "is rising into the black sky. The black rock of the tower seems "
      + "to swallow all light and to emanate terror and threats. Only high "
      + "on the tower, almost at the top, there is a blood red light "
      + "shining out through a small window.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({ "tower", }), BSN(desc));
}

public void
add_ruin(string extra = 0)
{
    string  desc = 
        "When the city was young, this must have been the house of a well "
      + "to-do family, but now centuries of neglect are showing. Where "
      + "once there was a door, there is only a gaping dark hole left now.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"building","house","ruin"}), BSN(desc));
}

public void
add_barracks(string extra = 0)
{
    string  desc = 
        "Formerly, this was probably the home of a wealthy citizen, but "
      + "now the building is in a poor condition. Some repairs have been "
      + "done almost haphazardly, and all windows have been closed with "
      + "wooden boards. Where once was a door, there remains only a dark "
      + "hole leading into the building.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"building","barrack","barracks"}), BSN(desc));

    add_item(({"hole","door"}), BSN(
        "Where once there was a door, all that is left now is a dark "
      + "gaping hole leading into the building. Beyond it you can see "
      + "nothing but darkness and shadows."));
    add_item(({"window","windows","board","boards"}), BSN(
        "Wooden boards have been nailed across all the windows of the "
      + "building, giving it a derelict appearance. It looks like the "
      + "creatures living here tried to block out all light from the house.\n"));
}

public void
add_house(string extra = 0)
{
    string  desc = 
        "This once was the house of a wealthy dunadan nobleman. Now it looks "
      + "rather run-down and in bad repair, but it is obviously still "
      + "inhabited. The door into the building is stuck open, most of the "
      + "windows have been closed using shutters.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"building","house","home"}), BSN(desc));

    add_item(({"door","entrance"}), BSN(
        "It is a strong wooden door. It hangs only partially on its hinges "
      + "so that it is impossible to close it."));
    add_item(({"window","windows","shutter","shutters"}), BSN(
        "All the windows on the ground floor have been closed with shutters. "
      + "Looking more closely you notice that the shutters have been nailed "
      + "to the walls so they cannot be opened. On the first floor, a few "
      + "windows are open, and it looks as if someone is living behind "
      + "those windows."));

}

public void
add_walls(string extra = 0)
{
    string  desc = 
        "The mighty city walls are rising for at least fifty feet above "
      + "your head. They have been formed from giant boulders that have been "
      + "hewn with great care so that you can hardly see the cracks between "
      + "them. On top of the walls, from time to time, you can see guards "
      + "patrolling.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"wall","walls","city wall"}), BSN(desc));
}

public void
add_top_walls(string extra = 0)
{
    string  desc = 
        "The mighty city walls are rising for at least fifty feet above the "
      + "streets of the city below. They have been formed from giant "
      + "boulders that were hewn with great care so that you can hardly see "
      + "the cracks between them. The tops of the walls are crowned by "
      + "battlements with embrasures facing outwards.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"wall","walls","city wall"}), BSN(desc));
}

public void
add_stairs(string extra = 0)
{
    string  desc = 
        "The narrow flight of stairs is leading up to the top of the walls "
      + "here. It does not take much imagination to realize that the stairs "
      + "are here so that the defenders of the city can man the walls "
      + "quickly in case of an attack.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"stairs","steps"}), BSN(desc));
}

public void
add_stairs_down(string extra = 0)
{
    string  desc = 
        "The narrow flight of stairs is leading down to the streets of the "
      + "city here. It does not take much imagination to realize that the "
      + "stairs are here so that the defenders of the city can man the walls "
      + "quickly in case of an attack.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"stairs","steps"}), BSN(desc));
}

public void
add_morgul_road(string extra = 0)
{
    string  desc = 
        "The road has been made of large square stone slabs that were hewn "
      + "from dark rock. On both sides of the road, there is a gutter "
      + "border by a high curb.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"street","road","ground"}), BSN(desc));

    add_item(({"water","curb","gutter"}), BSN(
        "In the gutter on both sides of the road, small rivulets of dirty "
      + "water are running down towards the Morgul Gate and the vale of the "
      + "Morgulduin. The gutter is bounded by the stone slabs of the road "
      + "on one side and a high curb made of dark stones on the other. In "
      + "places the curb has been damaged, probably by heavy carts."));
}

public void
add_barrack_street(string extra = 0)
{
    string  desc = 
        "The street is made of small square cobblestones. In many places one "
      + "or more stones are missing. The holes are partially filled with mud "
      + "or have been filled with gravel. The whole street looks to be in "
      + "bad repair and to be generally run down.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"street","road","ground"}), BSN(desc));

    add_item(({"gutter","water","garbage","rivulet","puddle"}), BSN(
        "The gutter is filled with dirty water and stinking garbage. Where "
      + "the rot is blocking the flow of the water down towards the drains "
      + "that must be at the city walls, large puddles have formed, that "
      + "emanate a devastating smell."));
}

public void
add_dark_street(string extra = 0)
{
    string  desc = 
        "The street is made of small round cobblestones. In a few places one "
      + "or more stones are missing and the holes have been filled with "
      + "gravel. The gutter is full of stinking garbage, and a streamlet of "
      + "dirty water is running down towards the city wall in it.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"street","road","ground"}), BSN(desc));

    add_item(({"gutter","water","garbage","rivulet","puddle"}), BSN(
        "A thin stream of dirty water is running through the gutter. Where "
      + "garbage is blocking the flow of the water, stinking puddles are "
      + "covering the street."));
}

public void
add_view_east(string extra = 0)
{
    string  desc = 
        "East of the city, the Morgul Road is winding down the slopes of the "
      + "Ephel Duath from the pass that is visible between the mountain tops "
      + "at the horizon. Whoever comes down that road, descending from the "
      + "pass visible between the mountain tops to the east, has to pass "
      + "through the city. Often did the armies of the Dark Lord come down "
      + "that road to attack the city until they finally captured it a "
      + "thousand years ago, thus opening the main route from Mordor to "
      + "Ithilien.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"view","pass","mountains","ephel duath","slopes"}),
	BSN(desc));
}

public void
add_view_north(string extra = 0)
{
    string  desc = 
        "To the north of the walls, the Morgul Road is winding down the "
      + "slopes to the bridge across the Morgulduin. Far below in the vale "
      + "through the fumes rising from the water, you can see the black "
      + "river running westwards. On the other side of the vale, steep "
      + "rock cliffs are rising high into the sky.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"view","vale","morgulduin","river","cliffs"}), BSN(desc));
}

public void
add_view_northwest(string extra = 0)
{
    string  desc = 
        "From here you have an excellent view of the Morgul vale and the "
      + "Morgul road that climbs up the slopes on the far side of the river. "
      + "Farther away one can make out the green forests of Ithilien that "
      + "start spreading west where the grey feet of the Ephel Duath end. "
      + "Beyond the tree tops the wide blue band of the Anduin stretches "
      + "from south to north.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"view","vale","morgul vale","river","forests","ithilien",
	"anduin"}), BSN(desc));
}

public void
add_view_south(string extra = 0)
{
    string  desc = 
        "The southern city wall was built right onto the cliffs that form "
      + "the southern border of the Morgul vale. There is only a small "
      + "cleft between the wall and the sheer and unclimbable mountain face.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"view","cliffs","mountains","rock"}), BSN(desc));
}

public void
add_gatehouse(string extra = 0)
{
    add_item(({"beds", "bed", "corner"}), BSN(
        "In a corner, you can see several beds for guards on stand-by duty. "
      + "The beds are made of a simple wooden frame, covered by canvas."));
    add_item(({"walls", "wall", "fixture", "fixtures"}), BSN(
        "On the walls you can see fixtures to hold weapons and armour. "
      + "Right now they are empty. The weapons and armour are probably in use."));
}

public void
add_mountain(string extra = 0)
{
    string  desc = 
        "To the east, you can see the dark heights of the Ephel Duath, the "
      + "Mountains of Shadow, rising towards the horizon. Behind them lies "
      + "Mordor, the Black Land.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"building","barrack","barracks"}), BSN(desc));
    add_item(({"mountain","mountains","mountain ridge","ephel duath",
        "shadowy mountains","mountains of shadow","shadow mountains"}),
	BSN(desc));
}

public void
add_tunnel_ceiling(string extra = 0)
{
    string  desc =
        "The ceiling and the floor seem to be made of the same dark "
      + "boulders as the walls, only they seem to have been hewn into "
      + "long slabs and then polished.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"ceiling","roof","floor","ground"}), BSN(desc));
}

public void
add_tunnel_wall(string extra = 0)
{
    string  desc =
        "The walls of the basement are made from smoothly hewn black "
      + "boulders. The walls look like they are the foundation of a "
      + "mighty building rising over your head. They are so black that "
      + "it seems as if they are swallowing any light that might come "
      + "down here.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({"wall","walls","stones"}), BSN(desc));
}

