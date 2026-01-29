
/* 
 * Meeting Place for Neidar and Shieldbearers at the heart
 * of the Great Barrel Vault of the Iron Delving Brewery
 *
 * Possible to randomly sample barrels on the tiers
 * in the vault
 *
 * ... /d/Ansalon/guild/neidar/rooms/meetcircle.c
 *
 * Vitwitch 12/2020
 */

#include "/d/Ansalon/common/defs.h"
#include "../guild.h"
#include "/d/Ansalon/estwilde/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Krynn/common/clock/clock.h"

#define CIRCLETABSIT "_meetcircle_i_sitting_at_table"

#define BREWOBJECT "/d/Ansalon/estwilde/obj/brewcraft_beerbottle.c"

inherit DWARF_IN;

object bottle;

void
reset_dwarf_room()
{
}


int
bottle_check()
{             
  object *inv;

  inv = deep_inventory(this_player());
  inv = filter(inv, &->id("_brewcraft_beer_bottle"));

  // there be bottles in possession of the exitter 

  if ( sizeof(inv) )
  {
      write("As you make to leave, you suddenly remember that "+
        "you have some undrunk bottles of brew upon you! Your "+
        "sudden remembrance is sparked by a deep warning "+
        "growl coming down from on high.\n");

      tell_room(E(TP),"There is a deep growl from above that brings "
         + QNAME(TP) + " to an abrupt halt -- undrunk bottles all a-clinking.\n",
          TP);

      return 1;
  }

  return 0;
}


void
create_dwarf_room()
{
    set_short("the Circle of Axe and Shield within the Great "+
              "Barrel Vault of Iron Delving");

    set_long("@@long_descr");

    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item(({"bottles","ring of bottles","ring"}),
        "A ring of tall bottles stands in the middle of the oaken table; "+
        "but a dwarven arms-length from its edge. In the labrynthine "+
        "darkness of the barrel-tiers, from where these bottles are "+
        "filled, no one is entirely sure which barrel of brew is "+
        "being tapped at any given sitting. To a dry-throated dwarf, "+
        "not afraid of the wide unknown, it is but a small thing to "+
        "claim a bottle and sup at the table.\n");

    add_item(({"table","oak table","oaken table"}),
        "The old oaken table is roughly circular like the Circle of Axe and "+
        "Shield in which it stands -- so all dwarves and their allies are "+
        "equal in this place -- all may be heard -- all within reach of the "+
        "ring of bottles at its centre. Runes are carved in the surface of "+
        "table. They do not seem to be arcane or scholarly in nature, "+
        "but perhaps the product of hours of wide-ranging discussion "+
        "involving very many bottles of brew procured from hereabouts.\n");

    add_item(({"circle","axes","shields","standing circle","circle of axe and shield"}),
        "Many of the greatest axes and shields, broken and battered in battles past, "+
        "are bound together in a scarred and colourful barricade. "+
        "Inside the Circle, heroes gather -- outside the Circle, darkness gathers. \n");

    set_tell_time(250);
    add_tell("Shadows loom and recede in the half-light high above the circle.\n");
    add_tell("Barrels can be heard to roll and rock mysteriously in their tiers.\n");
    add_tell("A long gaseous burp, on high in the dark, is followed by the sound of a smashing bottle.\n");

    add_exit(IRON + "brewery4","out","@@bottle_check",0);

    reset_dwarf_room();
}


string
long_descr()
{
    string str0, str1, str2, str3;

    str0 = "This is a clearing of sorts; a circle two dragonlengths across within "+
    "the Great Barrel Vault of Iron Delving.  The towering "+
    "barrel-tiers seem to have been pushed aside, disrupting their labrynthine order, "+
    "to make room enough to gather a sturdy cohort of dwarves under a high hill "+
    "in Estwilde. With cool dark shadows all about in the reaches of the Vault, "+
    "this circle at its centre is warm and lit.";

    if ( CLOCK->query_night() )
        str1 = "A ring of torches cast light and warmth over the scene.";
    else
        str1 = "Beams of sunlight stream from windows in the hill side above.";

    str2 = "The standing circle is marked by crossed axes and shields; battered "+
     "and scarred by battle, commemorating the victories and losses of the Neidar "+
     "Clan. The centre of the circle is dominated by a massive and ancient oaken "+
     "table, low enough to the ground so that it is comfortable for dwarves to "+
     "sit at and discuss matters weighty at great length; all the while supping on "+
     "the brews of the Vault to keep their throats and beards from drying out.";
    
    str3 = "A ring of bottles stand in the middle of the great table.";

    return sprintf("%s %s %s %s\n", str0, str1, str2, str3);
}

int
claim_it(string str)
{
    string name, str1;
    object brew;
    int num;

    NF("claim what?\n");
    if (!str)
	return 0;

    if (sscanf(str, "%d %s", num, str1) != 2)
	num = 1;

    if (num > 1)
    {
	NF("One can only hold one bottle in one hand -- leaving the other free for an axe or shield! Try again!\n");
	return 0;
    }
    if (num < 1)
        return 0;

    brew = clone_object(BREWOBJECT);
    brew->move(TP);

    TP->catch_msg("You claim a bottle of Iron Delving brew, tapped from a barrel in the surrounding darkness.\n");
    say(QCTNAME(TP) + " claims a bottle of Iron Delving brew.\n", TP);

    return 1;
}


int
sit_down(string str)
{
        if(TP->query_prop(CIRCLETABSIT))
        {
                write("You are already sitting at the table! Are you drunk?\n");
                return 1;
        }
        if(str == "around table" | str == "around the table" | str == "at table" | str == "at the table" | 
            str == "by table" | str == "by the table" | str == "table" | str == "the table")
        {
                TP->catch_msg("You draw a heavy stool out from under the round table and sit upon it.\n");
                say(QCTNAME(TP) + " sits down on a heavy stool at the round table.\n");
                TP->add_prop(CIRCLETABSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," who is sitting at the table");
                return 1;
        }
        else
        {
                TP->catch_msg("Where would you like to sit? At the table?\n");
                return 1;
        }
        return 1;
}


int
stand_up(string str)
{
    if(str == "up")
    {
        if(TP->query_prop(CIRCLETABSIT))
        {

            TP->catch_msg("You stand up.\n");
            say(QCTNAME(TP)+" stands up.\n");
            TP->remove_prop(CIRCLETABSIT);
            TP->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }

    }
    else
    {
        TP->catch_msg("Stand? Stand up?\n");
        return 1;
    }

    return 1;
}

int
fill_bottle(string str)
{
    if( wildmatch("*bottle*",lower_case(str)))
    {
        TP->catch_msg("Fill the bottle? The bottle of brew is full. "+
                       "Drink-up! Carry it away in your belly!\n");
    }
    else
    {
        TP->catch_msg("Fill? Fill what?\n");
        return 1;
    }

    return 1;
}

int
check_stand_up()
{
    if(TP->query_prop(CIRCLETABSIT))
    {
            TP->catch_msg("You stand up from the round table to leave.\n");
            say(QCTNAME(TP) + " stands up from the round table to leave.\n");
            TP->remove_prop(LIVE_S_EXTRA_SHORT);
            TP->remove_prop(CIRCLETABSIT);
    }
    return 0; // always allow to go out.
}


void
init()
{
    ::init();
    add_action("claim_it", "claim");
    add_action("sit_down","sit");
    add_action("stand_up","stand");
    add_action("fill_bottle","fill"); // preventing liquor takeaways
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    set_long("@@long_descr");
    if (interactive(ob))
        start_room_tells();
}

void leave_inv(object ob, object to)
{

    ::leave_inv(ob, to);
    if(!objectp(to) || !objectp(ob))
                return;
    check_stand_up();
}
