/* Change Log:
 * 21-february 2004, Vencar - made the items gained slightly more random
 *                            more changes will follow (soonish) when
 *                            my caravan opens he will also maybe have
 *                            a good lance or club.
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"


int bag_taken = 0;
object pouch;

void
create_object()
{
    set_name(({"remains","warhorse remains", "half-eaten remains"}));
    set_short("the half-eaten remains of a large warhorse");
    set_long("This is the half-eaten remains of a large warhorse. Something immensely " +
      "large and powerful has ripped the back half of the steed off in what looks like " +
      "one bite! A bloodied horse blanket lies in tatters around it, however you do make " +
      "out on it the livery of a Knight of Solamnia. "+
      "@@bag_message@@" +"\n");
    add_prop(OBJ_I_VOLUME, 300000);
    add_prop(OBJ_I_WEIGHT,5000000);

    add_cmd_item(({"pouch from half-eaten remains", "pouch from saddle",
        "pouch from ruined saddle",
    "pouch from remains","pouch from half-eaten remains of a large warhorse"}),
      ({"get","take"}),"@@get_bag");
    setuid; seteuid(getuid());
}

void
remove_remains()
{
    tell_room(E(TO),"The half-eaten remains of a large warhorse decay, "+
      "adding to the pile of bones filling this cave.\n");
    TO->remove_object();
}

string
bag_message()
{
    if(bag_taken == 1)
    {
    return "";
    }
    else
    return "You notice a pouch hanging from the ruined saddle.";
}

string
get_bag()
{

    int itemcount = 0;

    if(P("dragon", E(TO)))
    {
       write("The dragon turns quickly towards you, driving you away from " +
         "the remains of the warhorse.\n");
       return "";
    }



    if(bag_taken == 1)
    {
    write("There is no pouch to get from the saddle.\n");
    return "";
    }
    else
    write("You remove the pouch from the ruined saddle.\n");
    say(QCTNAME(TP)+ " removes a pouch from the ruined saddle "+
      "still attached to the half-eaten warhorse corpse.\n");
    pouch = clone_object("/d/Ansalon/kalaman/obj/pouch");
    pouch->move(TP);

    /* 75% of the times a scry crystal will be found */
    if (random(3))
    {
        clone_object("/d/Ansalon/kalaman/obj/scry_crystal")->move(pouch,1);
        itemcount += 1;
    }

    /* #0     #1   number of previous items found gives chance of
    /* 75% - 66%  of the time a dwarven potion will be found */
    if (random((3 - itemcount)))
    {
        clone_object("/d/Ansalon/estwilde/obj/dwarf_potion")->move(pouch,1);
        itemcount += 1;
    }

    /* #0     #1     #2  number of previous items found gives chance of
     * 75%    66%    50% of a speed potion will be found*/
    if (random((3 - itemcount)))
    {
        clone_object("/d/Krynn/common/potions/speed_potion")->move(pouch,1);
        itemcount += 1;
    }
    /* #0     #1    #2   #3 number of previous items found gives chance of
     * 75%    66%   50%   0% of a stone potion will be found*/
    if (random((3 - itemcount)))
    {
        clone_object("/d/Krynn/common/potions/stone_potion")->move(pouch,1);
        itemcount += 1;
    }

    /* #0     #1    #2+  number of previous items found gives chance of
    /* 66     50     0 a steel potion will be found */

    if (random((2 - itemcount)))
    {
        clone_object("/d/Krynn/common/potions/steel_potion")->move(pouch,1);
        itemcount += 1;
    }

    // 50% chance of cloning a protection from lightning scroll

    if (random(2))
    {    
        clone_object("/d/Krynn/common/scrolls/prot_lightning_scroll")->move(pouch,1); 
    }   

    bag_taken = 1;
    set_alarm(30.0,0.0,&remove_remains());
    return "";
}
