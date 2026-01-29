#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/brewcraft/brewcraft.h"

#define START_ROOM "/d/Ansalon/estwilde/iron_delving/brewery1.c"

#define BREWGRAIL "/d/Ansalon/estwilde/obj/brewcraft_beergrail"

#define BREWGOBLIN_I_HAS_BLOWN_MECH "_brewgoblin_i_has_blown_mech"
#define BARRELHOLE_I_GRAIL_CAN_ENTER "_barrelhole_i_grail_can_enter"
#define BARRELHOLE_I_MORTAL_CAN_ENTER "_barrelhole_i_mortal_can_enter"
#define BARRELHOLE_I_MORTAL_DENIED_ENTRY "_barrelhole_i_mortal_denied_entry"
#define BARRELHOLE_I_OPEN "_barrelhole_i_open"
#define BARRELHOLE_I_LIBR_HERE "_barrelhole_i_libr_here"


inherit DWARF_IN;

/* prototypes */

int is_grail( object ob );

/* functions */

void
reset_dwarf_room()
{
}


locked_south_if_not_found()
{
    if (TP->query_prop(BREWGOBLIN_I_HAS_BLOWN_MECH))
        return 0;
    write("The end of the closed barrelcot is firmly closed "+
        "and seems immune to being physically forced.\n");
    return 1;
}

unseen_south_if_not_found()
{
    if (TP->query_prop(BREWGOBLIN_I_HAS_BLOWN_MECH))
        return 0;
    return 1;
}


locked_onward_if_not_found()
{
    if ( (TP->query_prop(BARRELHOLE_I_MORTAL_CAN_ENTER)) &&
         barrelhole_is_open(TP) )
        return 0;
    write("The end of the closed barrelcot is firmly closed "+
        "and seems immune to being physically forced.\n");
    return 1;
}

unseen_onward_if_not_found()
{
    if (TP->query_prop(BARRELHOLE_I_MORTAL_CAN_ENTER))
        return 0;
    return 1;
}

locked_north_if_not_found()
{
    if ( TP->query_prop(BARRELHOLE_I_MORTAL_DENIED_ENTRY) )
        return 0;
    write("The end of the closed barrelcot is firmly closed "+
        "and seems immune to being physically forced.\n");
    return 1;
}

unseen_north_if_not_found()
{
    if ( TP->query_prop(BARRELHOLE_I_MORTAL_DENIED_ENTRY) )
        return 0;
    return 1;
}


void
create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(IRON + "brewery3","east");
    add_exit(IRON + "tavern","up");

    add_exit(IRON + "brewery_tunnel","south","@@locked_south_if_not_found",
               0,"@@unseen_south_if_not_found");
    add_exit(IRON + "brewery5","onward","@@locked_onward_if_not_found",
               0,"@@unseen_onward_if_not_found");
    add_exit(IRON + "brewery6","north","@@locked_north_if_not_found",
               0,"@@unseen_north_if_not_found");

    add_item(({"barrel","barrels","cot","cots","barrel cots","barrelcots","barrelcot"}),
      "These barrelcots are stout old brewery "+
      "barrels that have had their ends laid open to "+
      "visitors to climb inside upon a straw pallet, " +
      "pull the end closed, and catch forty winks. "+
      "There is a small slot in each open barrelcot "+
      "-- the exact width of a gold coin -- adjacent "+
      "to the locking mechanism. The first and last barrelcots are closed.\n");

    add_item("trapdoor","The trapdoor allows one to go <up>. Smoke and noise emanate from above.\n");

    add_item(({"smoke","tobacco smoke"}),"Tiny puffs of smoke from the room above, "+
                "occasionally waft about the trapdoor when boots stomp upon it.\n");

    add_item(({"noise","noises","sounds"}),"From the room above, "+
                "comes incidental noises of dwarven boots stomping, "+
                "dwarven voices cheering, "+
                "and the occasional breakage of glassware.  From the "+
                "room to the east come the noises "+
                "of industry and innovation in the art and craft of "+
                "brewing.\n");

    add_item("doorway","The doorway to the east seems to lead to a "+
              "large chamber.\n");

    add_item(({"small slot", "slot", "locking mechanism", "mechanism"}),
       "The small slot seems just the right size to accept a gold coin, "+
       "and would seem to allow the locking mechanism to close for "+
       "anyone wanting to <climb inside> and sleep in a barrelcot.\n");

    add_item(({"device","odd device"}),
       "The odd device on the closed last barrelcot, does not seem "+
       "capable of accepting a coin of any type. If anything it looks like "+
       "a mouthpiece that one could <blow> into?\n");

    add_item(({"last barrelcot", "last cot", "last barrel"}),
       "The very last barrelcot in the back row against the south wall is "+
       "firmly closed. Next to the barrel-end is an odd device, unlike "+
       "that on "+
       "any of the other barrelcots.\n");

    add_item(({"short length of rope","length of rope","rope"}),
       "The rope runs through a hole beside the closed end of "+
       "the first barrelcot. It appears to be woven from ancient reeds. "+
       "It looks like one could <pull> the rope.\n");

    add_item(({"stencil","stencil of a arrowhead","arrowhead"}),
       "The faded stencil was burnt into the wood of the barrel-end some "+
       "time ago -- "+
       "it is very faint. Looking closely, you make it out as not "+
       "a downward pointing arrowhead as you first thought. The stencil "+
       "is of a broad conical jar with a pointed base and a narrow lid on "+
       "top. Two wavy lines cross the body of the jar, perhaps denoting "+
       "liquid within.\n");
    
    add_item(({"first barrelcot", "first cot", "first barrel"}),
       "The very first barrelcot in the front row against the north wall is "+
       "firmly closed. A stencil of an arrowhead is burnt into the barrel-end. "+
       "Next to it is a short length of rope.\n");

    add_cmd_item("inside", "climb", "@@climb_inside");

    reset_dwarf_room();
}

int
climb_inside(string str)
{
    if ( str != "inside" && str != "inside a barrelcot") return 0; 
    write("Climbing inside a barrelcot, one can see that it is " +
          "quite comfortable. With a gold coin in the slot, one "+
          "could pull the barrel-end closed and <sleep> a spell.\n");
    return 1;
}

int
blow_into(string str)
{
    if ( !str || !(str == "into mouthpiece") )
    {
        write("Blow into what?\n"); 
        return 1; 
    }
    else
    {
        tell_room(E(TP), QCNAME(TP) + " closes in on the odd device "+
             "on the last barrelcot and does something to it.\n",TP);

        if(TP->query_race_name() == "goblin" ||
           TP->query_race() == "goblin" ||
           TP->query_race_name() == "hobgoblin" ||
           TP->query_race_name() == "minotaur" ||
           TP->query_race_name() == "ogre" ||
           TP->query_prop(DWARF_ENEMY) ||
           TP->query_wiz_level() != 0)
        {
            write("Blowing into the mouthpiece of the closed barrelcot, your " +
                  "breath fills the odd device and you hear a subtle click "+
                  "within. You intuit that you have found a secret passage! A "+
                  "hidden tunnel <south> from the brewery.\n");

            TP->add_prop(BREWGOBLIN_I_HAS_BLOWN_MECH,1);
        }
        else
        {
            write("Blowing into the mouthpiece of the closed barrelcot, your " +
                  "breath fills the odd device, making a wheezy whistling noise. "+
                  "The inert mouthpiece tastes of blood and ash.\n");
        }
        return 1;
    }
}


int
barrelhole_is_occupied()
{
    int rval = 0;
    object barrelhole;

    barrelhole = find_object(IRON + "brewery5.c");

    if ( objectp(barrelhole) )
        rval = barrelhole->query_prop(BARRELHOLE_I_LIBR_HERE);

    return rval;
}


varargs int
barrelhole_is_open( object player )
{
    int rval = 0;
    object barrelhole;

    barrelhole = find_object(IRON + "brewery5.c");

    if ( objectp(barrelhole) )
        rval = barrelhole->query_prop(BARRELHOLE_I_OPEN);

    if ( !player ) return rval;

    if ( player->query_prop(BARRELHOLE_I_GRAIL_CAN_ENTER) )
        return 1; 

    if ( barrelhole->query_patron_banned(player) )
        return 0;

    return rval;
}


int
is_grail( object ob )
{
    return ( wildmatch(sprintf("%s*",BREWGRAIL),file_name(ob)) );
}

int
grail_bearer( object player )
{
    int rval;

    if ( !objectp(player) ) return 0; 

    rval = sizeof( filter( all_inventory(player), is_grail ) );
    return min(1,rval);

}

void
rope_pulled( object player )
{
    string preamble, afterword;

    preamble = "A pinpoint of light appears at the end of the barrelcot. "+
               "You feel the possessions about your person being appraised, "+
               "one after another.";
    afterword = "The pinpoint of light vanishes.";

    if ( grail_bearer(player) && !barrelhole_is_occupied() )
    {
        write(preamble + " Moments later, you hear a loud click. "+
         "In your mind, an ethereal voice bids you pass <onward> if "+
         "you would offer your grail in libation to Ninkasi. "
           + afterword + "\n");

        player->add_prop(BARRELHOLE_I_GRAIL_CAN_ENTER,1);
        player->add_prop(BARRELHOLE_I_MORTAL_CAN_ENTER,1);
        player->remove_prop(BARRELHOLE_I_MORTAL_DENIED_ENTRY);
        return;
    }
    else 
    {
        if ( barrelhole_is_open(player) )
        {
            write(preamble + " A curious sound, as though from a rain storm"+
                "in the distance, reaches your ears. "+
                "Moments later, you hear a loud click. "+
                "An ethereal voice intones that you may pass <onward> in "+
                "supplication to Ninkasi. " + afterword + "\n");

            player->add_prop(BARRELHOLE_I_MORTAL_CAN_ENTER,1);
            player->remove_prop(BARRELHOLE_I_MORTAL_DENIED_ENTRY);
            return;
        }
    }

    write(preamble + " " + afterword + 
          " The end of the barrelcot is ajar. You can go <north> "+
          "to enter the barrelcot.\n");
    player->remove_prop(BARRELHOLE_I_MORTAL_CAN_ENTER);
    player->add_prop(BARRELHOLE_I_MORTAL_DENIED_ENTRY,1);
    return;

}


int
pull_rope(string str)
{
    if ( !str || !(str == "the rope") )
    {
        write("Pull what? Pull the rope?\n"); 
    }
    else
    {
        tell_room(E(TP), QCNAME(TP) + " pulls the short rope beside the "+
             "first barrelcot.\n",TP);

        write("Pulling on the short woven rope beside the first barrelcot "+
          "causes it to become taut against something.\n");

        set_alarm(2.0,0.0,&rope_pulled(TP));
    }
    return 1;
}


public void
hook_smelled(string str)
{
    write("The scents of aged wood and straw dominate; "+
           "with hints of smoke and malted grain.\n");
}

void 
init()
{    
    ::init();
    add_action("sleep", "sleep");
    add_action("blow_into","blow");
    add_action("pull_rope","pull");
}

string
short_descr()
{
    return "entrance vestibule of the Iron Delving Brewery";
}

string
long_descr()
{
    return "The entrance of the Iron Delving Brewery is "+
        "neat and clean; a sign that this is an establishment "+
        "Hill Dwarves take much pride in. "+
        "You can smell faint traces of the heavy scent of dwarven "+
        "sweat and tobacco smoke emanating from a trapdoor leading "+
        "directly upwards. The occasional bang and clang of "+
        "industrious dwarves working in the brew chamber to the east "+
        "disturb the relative quiet of this place. "+
        "There are a number of odd shaped cots "+
        "fashioned from old barrels that have been placed here -- "+
        "a welcome gesture to those who may have exhausted themselves "+
        "brewing or drinking by day or night.\n";
}

int
sleep(string str)
{
    NF("Sleep where?\n");
    NF("Sleep where? In a barrelcot?\n");
    if (str != "in a cot" && str != "in a barrelcot")
        return 0;    
    if (!present("gold coin",TP))
    {
        write("A single gold coin will fit in the slot of a barrelcot.\n");
        return 1;
    }
    if (!MONEY_MOVE(1,"gold",TP,0))
    {
        write("You pay 1 gold coin to sleep in a barrelcot. When you " +
            "next enter the Realms you will do so from this room, " +
            "safe in the bosom of Iron Delving Brewing.\n");
        this_player()->set_temp_start_location(START_ROOM);
        return 1;
    }
    return 0;
}


