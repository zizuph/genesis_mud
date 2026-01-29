/*
 *  temple5.c
 *
 *  This is the entrance to the sanctuary, the tome holds
 *  the key to opening it, encryped in a foreign language.
 *  This room clones the blessing, as you enter into the
 *  sanctuary.
 *
 *  Created by Carnak, January 2016
 */

#pragma save_binary

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
inherit MITHAS_IN;

#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

#include "./local.h"

#define OTHER_ROOM      "/d/Ansalon/goodlund/nethosak/chislev_temple/temple8.c"
#define ROOM            "/d/Ansalon/goodlund/nethosak/chislev_temple/temple5.c"

#define I_AM_SITTING "_i_am_sitting"

public int      pass_tapestry(string str);
public int      altar;

int sit_bench(string str);
int rise_bench(string str);

create_mithas_room()
{
    set_short("The temple's atrium");
    set_long("@@long_desc");
	
    add_exit(TDIR +"temple1", "southwest", &pass_tapestry("southwest"));
    add_exit(TDIR +"temple3", "southeast", &pass_tapestry("southeast"));
    add_exit("", "down", "@@go_down", 0, 1);

    add_item(({"floor","ground","rocks","smooth rocks"}),
    "The floor is tiled with smooth rocks in different hues which "+
    "forms a beautiful floral pattern, in the center of which "+
    "there is a depression filled with water. The floor is, unlike "+
    "the rest of the temple, untouched by nature.\n");
	 
    add_item(({"ruin","temple","building"}),
    "This must be the temple of an ancient druid order that once "+
    "populated Mithas.\n");

    add_item(({"stones","blocks","granite blocks","granite stones"}),
    "The stones are square gray granite blocks which have "+
    "been worn down by time and harsh weather.\n");

    add_item(({"walls","roots","wall","west wall","east wall",
    "eastern wall","western wall","cracks"}),
    "The roots have found their way into the cracks between "+
    "the stones that make up the walls, seemingly reinforcing "+
    "the structural stability.\n");
	 
    add_item(({"wooden roof","roof","hatch","ceiling"}),
    "The wooden roof appears to be in good condition, "+
    "supported by beams resting on the eastern and "+
    "western walls. A hatch in the roof just above the "+
    "southern wall has been propped open, allowing light to "+
    "spread throughout the temple during the day.\n");
	 
    add_item(({"doorway","arched doorway","arch","hallway",
	"doorways","arched doorways"}),
    "There are two stone doorways in the form of arches, they "+
    "lead southwest and southeast towards a hallway.\n");

    add_item(({"decorations","decor"}),
    "Along the walls are seemingly delicate <stone benches and "+
    "small round basins. The floor has been decorated to form "+
    "a beautiful floral pattern.\n");
	 
    add_item(({"south wall","southern wall"}),
    "The south wall stretches east and westwards towards "+
    "arched doorways which lead into the hallway. The stones "+
    "appear to be from the same source as the rest of the "+
    "walls, however the wall stops just short of the roof, "+
    "allowing light and fresh air from the hatch above it to "+
    "fill the atrium on warm summer days.\n");
	 
    add_item(({"hues","pattern","floral pattern"}),
    "The floor is crafted from smooth rocks in varying hues "+
    "to create an intricate floral pattern.\n");
	 
    add_item(({"northern wall","north wall"}),
    "A stone dais has been built against the northern wall "+
    "upon which an altar has been raised.\n");
	 
    add_item(({"dais","platform","stone platform"}),
    "The dais is a stone platform build against the northern "+
    "wall, upon which an altar has been raised.\n");
	 
    add_item(({"altar","base"}),
    "The altar stands upon a dais against the northwen wall, "+
    "signs of intricate patterns can be seen on the base of "+
    "the altar, but much like the benches, time has whittled "+
    "its beauty, leaving a coarse surface. Upon the altar "+
    "rests a leather-bound tome which is marked with a "+
    "feather of brown, yellow and green.\n");
	 
    add_item(({"basins","basin","small basins","small basin",
	"round basin","round basins","small round basin",
	"small round basins"}),
    "The basins contain remnants of incense and firewood, "+
    "it appears these can be used in both ritual rites and "+
    "to heat up the temple during winter.\n");
	 
    add_item(({"benches","bench","stone benches","stone bench",
	"delicate bench","delicate benches","delicate stone bench",
	"delicate stone benches"}),
    "The stone benches look delicate to the touch, they "+
    "must have once been beautifully sculpted, but time "+
    "has whittled their intricate patterns leaving them "+
    "with a plain look, only hints remaining of their "+
    "former beauty.\n");
    
    add_item(({"depression", "water","water-filled depression",
    "center"}),
    "This is a water-filled depression, located in the center "+
    "of the atrium. Its purpose is for purification during "+
    "rituals.\n");
	 
    add_item(({"atrium","hall","grand hall","heart of the temple"}),
    "This grand hall is the heart of the temple, at the northern "+
    "wall a dais has been raised to support an altar. The floor "+
    "has been carefully crafted from smooth rocks in varying "+
    "hues to create an intricate floral pattern which draws "+
    "your focus towards the shallow water-filled depression in "+
    "the center of the room. Along the walls are seemingly "+
    "delicate stone benches and small round basins.\n");
    
    add_item(({"tome","leather-bound tome","emblem","feather"}),
    "Upon the altar rests a leather-bound tome which is marked "+
    "with an emblem of a brown, yellow and green feather.\n");
	
    add_cmd_item(({"emblem"}),"touch", "@@slide_altar");
    add_cmd_item(({"tome","leather-bound tome"}),"read",
    "@@read_tome");
	  
    altar = 1;
}

void
init()
{
    ::init();
    add_action(sit_bench,"sit");
    add_action(rise_bench,"stand");
    add_action(rise_bench,"rise");
}

int
pass_tapestry(string str)
{
	
    if (TP->query_prop(I_AM_SITTING))
    {
        write("You rise from the delicate stone bench.\n");
        TP->remove_prop(I_AM_SITTING);
    }
	
    switch (str)
    {
        case "southwest":
        write("You step through the arched doorway to the southeast, "+
        "leaving the atrium.\n");
        say(QCTNAME(TP) + " steps through the arched doorway, leaving "+
        "the atrium.\n");
            break;
		
        case "southeast":
        write("You step through the arched doorway to the southeast, "+
        "leaving the atrium.\n");
        say(QCTNAME(TP) + " steps through the arched doorway, leaving "+
        "the atrium.\n");
            break;
    }
    return 0;
}

int
read_tome()
{
    if (TP->query_skill(SS_LANGUAGE) < (20+random(15)))
    {
        write("The runic language in this tome is far beyond your "+
        "comprehension.\n");
    }
    else
    {
        write("This tome is written in an ancient and obscure "+
        "language, beyond your comprehension. What little you "+
        "are able to piece together, depicts the rise and fall "+
        "of an ancient druid order who worshipped Chislev, "+
        "referred to in this tome as 'The Wild One'. The "+
        "temple appears to have been built around a holy "+
        "place, to guard it from the forces of decay. Your "+
        "instincts tell you there is more to this tome than "+
        "meets the eye, its emblem shimmering ever so slightly. "+
        "You get an urge to touch it.\n");
        say(QCTNAME(TP) + " reads an entry in the leather-bound book "+
        "upon the altar.\n");
    }
    return 1;
}

public int
set_altar(int i)
{
    altar = i;
}

public int
query_altar()
{
    return altar;
}

string
altar_desc()
{
    if (query_altar())
    {
        return "";
    }
    else
    {
        return " There is an open passage leading down beneath the altar.";
    }
}



/*
 * Function     : move_altar
 * Description  : This opens the exit down into the sanctuary
 */

public void
move_altar()
{
    if (query_altar())
    {
        tell_room(ROOM, "The altar begins to slide sideways, opening "+
        "a passage leading down into a cellar.\n");
        tell_room(OTHER_ROOM, "The altar begins to slide sideways "+
        "opening a passage leading up into the temple atrium.\n");
        ROOM->set_altar(0);
        OTHER_ROOM->set_altar(0);
        set_alarm(4.0,0.0, &move_altar());
    }
    else
    {
        tell_room(ROOM, "The altar slides back into place, blocking the "+
        "passage down.\n");
        tell_room(OTHER_ROOM, "The altar slides back into place, "+
        "blocking the passage up.\n");
        ROOM->set_altar(1);
        OTHER_ROOM->set_altar(1);
    }
}

int
slide_altar()
{
    if (TP->query_prop(I_AM_SITTING))
    {
        write("How could you possible reach that from where you "+
        "are sitting?\n");
        return 1;
    }
	
    say(QCTNAME(TP) + " touches the emblem on the "+
    "leather-bound tome.\n");
	  
    if (query_altar())
    {
        write("As you touch the emblem on the leather-bound tome, "+
        "a tingling sensation spreads in your arm.\n");
        move_altar();
    }
    else
    {  
        write("As you touch the emblem on the leather-bound tome, "+
        "but nothing happens.\n");
    }
    return 1;
}

/*
 * Function     : go_down
 * Description  : This adds the sanctuary blessing and moves the
 *                player into the sanctuary
 */

int
go_down()
{
    if (query_altar())
    {
        write("There is no obvious exit down.\n");
        return 1;
    }
	
    if (TP->query_prop(I_AM_SITTING))
    {
        write("You rise from the delicate stone bench.\n");
        TP->remove_prop(I_AM_SITTING);
    }
	
    if (TP->query_relaxed_from_combat())
    {
        write("You descend the stairs of the altar passage.\n");
        say(QCTNAME(TP) + " descends the stairs of the "+
        "altar passage.\n");
        tell_room(OTHER_ROOM, QCTNAME(TP) + " descends the "+
        "stairs of the altar passage.\n");
        TP->move_living("M",TDIR + "temple8.c", 0, 0);
        
        /*  This if statement was added to include a quest  */
        if (this_player()->query_prop(C_QUEST) &&
           !present("_chislev_dirt", environment(TP)) &&
           !present("_chislev_dirt", TP))
        {
            tell_room(environment(TP), "The earth is parted as "+
            "roots sprout out of the ground to form a gnarled "+
            "basin.\n", this_object(), this_object());
            TP->catch_msg("\nA soothing voice enters your mind: "+
            "My blessing is yours to claim, mortal.\n"+
            "\nYour eyes wander towards the newly risen basin.\n");
            object quest;
            quest = clone_object(TOBJ + "basin");
            quest->move(environment(TP),1);
        }
        
        object blessing;
        if (blessing = present("_blessing_of_chislev_", TP))
            blessing->remove_object();
	
        blessing = clone_object(TDIR + "obj/blessing");
        blessing->move(TP);
        return 1;
    }
	
    write("You suddenly feel weakened as you attempt to descend "+
    "the stairway, as if prevented a force greater than yourself.\n");
    say(QCTNAME(TP) + " lingers infront of the stairway, unwilling "+
    "to descend.\n");
    return 1;
}

int
sit_bench(string str)
{
    notify_fail("Sit on what?\n");
    if ((!str) || (!strlen(str)) || (str != "on bench") && (str != "bench"))
        return 0;
	
    if (TP->query_prop(I_AM_SITTING))
    {
        write("You are already sitting down.\n");
        return 1;
    }
	
    write("You walk towards one of the delicate stone benches and "+
    "take a seat.\n");
    say(QCTNAME(TP) + " takes a seat on a delicate stone bench.\n");
    TP->add_prop(I_AM_SITTING, 1);
    return 1;
}

int
rise_bench(string str)
{
    if (TP->query_prop(I_AM_SITTING))
    {
        write("You rise from the delicate stone bench.\n");
        say(QCTNAME(TP) + " rises from the delicate stone bench.\n");
        TP->remove_prop(I_AM_SITTING);
        return 1;
    }
    return 0;
}

string
long_desc()
{ 
    return tod_desc()+ "" +season_desc()+
    "This grand hall is the heart of the temple, at the "+
    "northern wall a dais has been raised to support an "+
    "altar. The floor has been carefully crafted from "+
    "smooth rocks in varying hues to create an intricate "+
    "floral pattern which draws your focus towards the "+
    "shallow water-filled depression in the center of "+
    "the room. Along the walls are seemingly delicate "+
    "stone benches and small round basins."+altar_desc()+"\n";
}
