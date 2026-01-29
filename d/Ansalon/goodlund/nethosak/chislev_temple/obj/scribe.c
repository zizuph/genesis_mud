/*
 *  scribe.c
 * 
 *  This is a hint to find the area that I created as my
 *  apprenticeship task, a temple of chislev, inside this
 *  corpse lie maps, showing its location.
 *
 *  Created by Carnak, March 2016
 */
inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Ansalon/goodlund/nethosak/chislev_temple/local.h"

int map = 0;

public int
query_map()
{
    return map;
}

public void
reset_map()
{
    map = 0; 
}

void
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_name("remains");
    add_name("human");
    add_name("corpse");
    set_adj("brown-robed");
    set_short("corpse of a brown-robed human");
    set_long("@@long_desc");

    add_item(({"furled scroll","scroll"}),
    "The scroll appears to be a map, you could probably get it " +
    "from the corpse without a guilty concience.\n");
    
    add_prop(OBJ_S_SEARCH_FUN, "search_corpse");
    
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET, "What would possess you to try and "+
    "lay claim to a corpse?\n");

}


/*
 * Function     : desc_changes
 * Description  : This adds and removes part of the long description
 *                of the corpse, depending on awareness, wisdom and
 *                scroll availability.
 */
 
string
desc_changes()
{
    string str = "";
    
    if (!map && this_player()->query_skill(SS_AWARENESS) > random(50))
        str = "\nThe right hand firmly grasps a furled scroll.";
    
    if (this_player()->query_stat(SS_WIS) > (100 + random(50)))
        return " The bruises on the body indicates that he was " +
        "bludgeoned to death and its position suggests that he " +
        "was running away, not lasting long before collapsing " +
        "and succumbing to his wounds." + str;
    
    return "" + str;
}

string
long_desc()
{
    return "This is the remains of a brown-robed human, " +
    "whose body tell the tale of a slow and horrible death." +
    desc_changes() + "\n";
}


/*
 * Function     : do_take
 * Description  : This handles the retrieval of scrolls, might
 *                add a fun robe at some point in time.
 */
int
do_take(string str)
{
    string  item;
    object  ob1, ob2, ob3, ob4,
            ob5, ob6, ob7, ob;
            
    if (!strlen(str))
        return 0;
    
    if (parse_command(str, ({ }), "[the] [furled] [brown] %s 'from' 'hand' / " +
                                  "'remains' / 'corpse' / 'human'", item))
    {
        if (IN_ARRAY(item, ({"maps", "scrolls", "all"})))
        {
            this_player()->catch_msg("You retrieve the belongings of the " +
            "brown-robed human and decide to bury him in the woods.\n");
        
        switch(map)
        {
            case 0:
            ob7 = clone_object(TDIR + "map/mithas_map")->move(this_player(), 1);
                
            case 1:
            ob6 = clone_object(TDIR + "map/kendermore_map")->move(this_player(), 1);
                
            case 2:
            ob5 = clone_object(TDIR + "map/flotsam_map")->move(this_player(), 1);
                
            case 3:
            ob4 = clone_object(TDIR + "map/bloodbay_map")->move(this_player(), 1);
                
            case 4:
            ob3 = clone_object(TDIR + "map/barren_map")->move(this_player(), 1);
            
            case 5:
            ob2 = clone_object(TDIR + "map/balifor_map")->move(this_player(), 1);
                
            case 6:
            ob1 = clone_object(TDIR + "map/ansalon_map")->move(this_player(), 1);
        }
            
            //ob = clone_object(TOBJ + "brown_robe")->move(this_player(), 1);
            tell_room(environment(this_player()), QCTNAME(this_player()) +
            " retrieves the belongings from the remains and buries it in " +
            "the forest.\n",
            this_player());
            remove_object();
            return 1;
        }
        
        if (IN_ARRAY(item, ({"robe"})))
        {
            /* Havent coded the robe, making it seem unprofitable to remove it */
            
            if (file_size(TOBJ + "brown_robe") < 1)
            {
                this_player()->catch_msg("The robe is torn and has lost all " +
                "value, you decide to leave it.\n");
                
                tell_room(environment(this_player()), QCTNAME(this_player()) +
                " finds a place in the forest to allow the remains its final " +
                "rest, burying it to safeguard it from predation.\n",
                this_player());
                this_player()->catch_msg("You move the remains to a more " +
                "fitting place for its final rest, burying it in the forest " +
                "to safeguard it from predation.\n");
                remove_object();
                return 1;
            }
            
            this_player()->catch_msg("You retrieve a brown hooded robe and " +
            "bury the naked remains to ease your concience, for stealing " +
            "the very clothes on his back.\n");
            tell_room(environment(this_player()), QCTNAME(this_player()) +
            " retrieves a brown hooded robe from the remains and then buries " +
            "it in the forest.\n", this_player());
            ob = clone_object(TOBJ + "brown_robe")->move(this_player(), 1);
            remove_object();
            return 1;
        }
        
        if (!IN_ARRAY(item, ({"map", "scroll"})))
            return 0;
        
        switch(map)
        {
            case 0:
            this_player()->catch_msg("You pry the dead mans hand open and " +
            "retrieve the furled scroll.\n");
            tell_room(environment(this_player()), QCTNAME(this_player()) +
            " retrieves a scroll from the remains.\n", this_player());
            ob7 = clone_object(TDIR + "map/mithas_map")->move(this_player(), 1);
                break;
                
            case 1:
            this_player()->catch_msg("You take a scroll from the corpse, there " +
            "are still quite a few remaining.\n");
            tell_room(environment(this_player()), QCTNAME(this_player()) +
            " retrieves a scroll from the remains.\n", this_player());
            ob6 = clone_object(TDIR + "map/kendermore_map")->move(this_player(), 1);
                break;
                
            case 2:
            this_player()->catch_msg("You take a scroll from the corpse, there " +
            "are still quite a few remaining.\n");
            tell_room(environment(this_player()), QCTNAME(this_player()) +
            " retrieves a scroll from the remains.\n", this_player());
            ob5 = clone_object(TDIR + "map/flotsam_map")->move(this_player(), 1);
                break;
                
            case 3:
            this_player()->catch_msg("You take a scroll from the corpse, there " +
            "are still a few remaining.\n");
            tell_room(environment(this_player()), QCTNAME(this_player()) +
            " retrieves a scroll from the remains.\n", this_player());
            ob4 = clone_object(TDIR + "map/bloodbay_map")->move(this_player(), 1);
                break;
                
            case 4:
            this_player()->catch_msg("You take a scroll from the corpse, there " +
            "are still a few remaining.\n");
            tell_room(environment(this_player()), QCTNAME(this_player()) +
            " retrieves a scroll from the remains.\n", this_player());
            ob3 = clone_object(TDIR + "map/barren_map")->move(this_player(), 1);
                break;
                
            case 5:
            this_player()->catch_msg("You take a scroll from the corpse, there " +
            "is still one remaining.\n");
            tell_room(environment(this_player()), QCTNAME(this_player()) +
            " retrieves a scroll from the remains.\n", this_player());
            ob2 = clone_object(TDIR + "map/balifor_map")->move(this_player(), 1);
                break;
                
            case 6:
            this_player()->catch_msg("You take a scroll from the corpse, there " +
            "are no remaining scrolls in the corpses belongings.\n");
            tell_room(environment(this_player()), QCTNAME(this_player()) +
            " retrieves a scroll from the remains.\n", this_player());
            ob1 = clone_object(TDIR + "map/ansalon_map")->move(this_player(), 1);
                break;
                
            default:
            this_player()->catch_msg("You find nothing aside from the robe in "+
            "the remaining belongings.\n");
            return 1;
        }
        
        map++;
        return 1;
    }
    
    return 0;
}

string
search_corpse(object searcher, string what)
{
    if (!CAN_SEE_IN_ROOM(this_player()))
    {
        return "You are unable to find what you wish to search due to a loss " +
        "of sight.\n";
    }
    
    switch(map)
    {
        case 0..3:
        return "There are several scrolls in the belongings of the corpse along " +
        "with a brown-hooded robe, perhaps you could get them.\n";
        
        case 4..5:
        return "There are a few scrolls in the belongings of the corpse along " +
        "with a brown-hooded robe, perhaps you could get them.\n";
        
        case 6:
        return "There is a single scroll in the belongings of the corpse along " +
        "with a brown-hooded robe, perhaps you could get them.\n";
        
        default:
        return "There is nothing but a brown-hooded robe in the corpses " +
        "belongings.\n";   
    }
    
    return "";
}

void
init()
{
    ::init();
    add_action(do_take,         "take");
    add_action(do_take,         "get");
}