/*
 *  chislev_clearing.c
 *
 *  The 'druid.c' is cloned in this room, and aside from
 *  that, its only special features is being a garden in
 *  the woods and thus it contains all herbs listed in 
 *  the herb file 'MixedForest', the no_find herb
 *  message is masked to create a more fitting return
 *  for this room.
 * 
 *  Created by Carnak, January 2016
 */
#pragma save_binary

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"

inherit MITHAS_OUT;

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Krynn/common/herbsearch.h"

#include "./local.h"

#define GROUP        0
#define Q_BIT        6
#define Q_EXP      250


#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

public int      do_search(string str);
public int      pass_tapestry();
object druid;

string *herbs = HERB_MASTER->query_herbs("mixedforest");

/*
 * Function     : add_herblist
 * Description  : This adds all the herbs listed in the mixedforest
 *                herblist.
 */

add_herblist()
{
    foreach(string h: herbs)
    {
        add_herb_file(h);
    }
}

/*
 * Function     : no_find
 * Description  : This alters the message recieved when there are
 *                no herbs left
 */

string
no_find()
{
    return "You attempt to pick another herb, but your instincts "+
    "prevent you, this area is protected by Chislev herself.\n";
}

void
reset_mithas_room()
{
    set_searched(0); /* Sets a random amount of herbs */
    if(!objectp(druid))
    {
        druid = clone_object(TDIR + "living/druid");
        druid->arm_me();
        druid->move(TO);
    }
}

create_mithas_room()
{
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
	
    add_herblist();
	
    reset_mithas_room();
	
    set_short("In a small clearing");
    set_long("@@long_descr");
	
    add_exit("", "west", &pass_tapestry());
	
    add_item(({"forest","ancient forest"}),
    "The forest looks ancient. Old logs and branches fill the "+
    "forest floor and the strong smell of decay and moisture "+
    "fills the air. The forest consists of different sorts of "+
    "trees, a mixture of pines and oaktrees.\n");
    
    add_item(({"trees","oak trees","pine trees","pines","oaks"}),
    "The trees here consist of a mixture of pines and oak trees.\n");
    
    add_item(({"canopy", "treetops"}),
    "The canopy above you looks thick, only a few sunrays are "+
    "able to enter the forest. You notice a few birds above you, "+
    "but they quickly vanish in the thick canopy.\n");
    
    add_item(({"herbs","plants","foliage","opulent foliage"}),
    "There are a lot of different herbs here, if you wish to "+
    "look at a specific one, perhaps you should search for it.\n");
    
    add_item(({"temple","building","northern section","section",
    "ancient temple", "ruin","ruins","structure"}),
    "The northern section of the temple lay in utter ruin and "+
    "only mounds of stones are left to behold. The vegetation "+
    "grows more intense towards the north, which likely caused "+
    "its collapse.\n");
	 
    add_item(({"wooden roof","roof","stone roof","second floor"}),
    "The wooden roof appears to be in pristine condition. "+
    "A part of the roof on the hallway leading north, "+
    "towards the collapse, appears to be constructed of stones, "+
    "indicating that the temple once had a second floor.\n");
    
    add_item(({"roots","walls", "cracks"}),
    "The roots have found their way into the cracks between the "+
    "stones that make up the walls, seemingly reinforcing the "+
    "structural stability.\n");
    
    add_item(({"vegetation"}),
    "The vegetation that adorn the ruins has grown with time to "+
    "mask the presence of this structure.\n");
    
    add_item(({"moss","fungi","fungus"}),
    "The moss and fungi grow widespread in this area.\n");
    
    add_item(({"stones","mound","mounds"}),
    "The granite stones are encompassed in roots and covered in "+
    "patches of moss and fallen leaves.\n");
    
    add_item(({"wall","surrounding wall","low standing wall",
    "vestibule","temple vestibule","remnants","low wall",
    "wall of stone", "stone wall"}),
    "The low wall is likely the remnants of a temple vestibule, "+
    "ravaged by time.\n");
	 
    add_item(({"clearing","garden","herbal garden"}),
    "The clearing is used as an herbal garden, guarded by a low "+
    "standing wall of stones, keeping animals away from the "+
    "opulent foliage.\n");
	 
    add_item(({"door","wooden door"}),
    "The wooden door hangs on crooked hinges and stuck on the "+
    "elevated threshold, one would have to lift the door to "+
    "open it.\n");
    
    add_item(({"threshold","steps","stair"}),
    "The stone steps leading into the temple are slightly "+
    "elevated to form a threshold and keeping the wooden door "+
    "in place, one would have to lift the door to open it.\n");
	 
    add_cmd_item(({"door","wooden door"}),"lift", "@@lift_door");
    add_cmd_item(({"door","wooden door"}),"open", "@@pass_tapestry");
    add_cmd_item(({"soil","pile", "blessed pile", "blessed soil"}),
    "sprinkle", "@@do_soil");

}

void
init()
{
    ::init();
    add_action(do_search,   "search");
}

/*
 *  Function:       do_search
 *  Description:    Prevents the player from herbing if s/he hasnt
 *                  done the quest.
 */
int
do_search(string str)
{
    if (!TP->test_bit("ansalon", GROUP, Q_BIT))
    {
        this_player()->catch_msg("Your instincts prevent you as you "+
        "attempt to harvest this bountiful earth, you feel as if it "+
        "is guarded by something greater than yourself. The residing "+
        "druid may be able to offer you advice on the matter.\n");
        
        TP->add_prop(C_QUEST, 1);
        return 1;
    }
    return 0;
}

/*
 *  Function:       do_soil
 *  Description:    Rewards the player when successfully completing
 *                  the quest.
 */
int
do_soil()
{
    if (!present("_chislev_dirt", this_player()))
        return 0;
    
    mixed *ob = filter(all_inventory(this_player()),
                &operator(==)("_chislev_dirt") @ &->query_name());
    
    write("You sprinkle the blessed soil throughout the garden, "+
    "tending to the earth.\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player()) +
    " sprinkles dirt throughout the garden.\n",
    this_player(), this_player());
    
    if(this_player()->test_bit("ansalon", GROUP, Q_BIT))
    {
        this_player()->catch_msg("Your reverance of nature knows no "+
        "bounds, however this time you feel no different.\n");
        this_player()->remove_prop(C_QUEST);
        ob->remove_object();
        return 1;
    }
    
    this_player()->catch_msg("You have contributed to the growth of "+
    "nature, and may now harvest the bounty of Chislev.\nYou feel "+
    "slightly more experienced.\n");
    
    if(this_player()->query_wiz_level())
    {
        this_player()->catch_msg("xp : " + Q_EXP + "\n");
    }
    
    write_file(TLOG + "questpioneers",
    ctime(time()) + ": " + this_player()->query_name() + " - " +
    "avg: " + this_player()->query_average_stat() + "\n");
    
    this_player()->add_exp(Q_EXP, 0);
    this_player()->set_bit(GROUP, Q_BIT);
    A_QUEST_LOG("quest","Venerate Nature", this_player(), Q_EXP);
    this_player()->remove_prop(C_QUEST);
    set_searched(0);
    ob->remove_object();
    return 1;
}

string
long_descr()
{
    return tod_descr()+ "" +season_descr()+
    "You are standing in a clearing, just outside of an ancient "+
    "temple. The clearing is used as an herbal garden, guarded "+
    "by a low standing wall of stones, keeping animals away from "+
    "the opulent foliage. The surrounding wall is likely the "+
    "remnants of a temple vestibule, ravaged by time.\n";
}

int
lift_door()
{
    write("You lift the door, freeing it from the elevated "+
    "threshold, pulling it open.\n");
    say(QCTNAME(TP) + " opens the door and steps inside, closing it "+
    "behind "+HIM(TP)+".\n");
	
    TP->move_living("M",TDIR + "temple9.c", 1, 0);
	
    write("You close the door behind you.\n");
    say(QCTNAME(TP) + " arrives from outside, closing the door "+
    "behind " + HIM(TP) + ".\n");
    return 1;
}

int
pass_tapestry()
{
    write("You attempt to open the door, but fail. The door appears "+
    "to be stuck on the threshold.\n");
    say(QCTNAME(TP) + " tries to open the wooden door, but fails.\n");
    return 1;
}