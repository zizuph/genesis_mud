// file name         /d/Avenir/common/dead/obj/rose 
//                  copy of /d/Avenir/common/holm/obj/rose.c       
// creator(s):      Lilith  01/20/97
// purpose:         Enchanted rose for Mascarvin Quest
// last update:     Lilith, Sept 2021: updated MAGIC ID info.
// note:            The 5 petals of this rosebud burst into flames 
//                  when dropped. They can be used to block exits
//                  for a short period of time (15-30sec).
//                  Related objects: rose_petal.c and rose_flames.c
//                  This object autoloads until the petals are used up.
//                  It cannot be dropped or given.
// bug(s):
// to-do:

inherit "/std/object";
#include "/d/Avenir/common/dead/dead.h"
#include "/d/Genesis/specials/defs.h"
#define  ROSE_PROP  "_Avenir_Magic_Rose_Prop"
#define  TOSS_PROP  "_Avenir_Fire_Petal_Tosser"

int ipetal;      /* How many petals do I have left? */

public void set_petals(int p) {    ipetal = p;       }
public int  query_petals()    {    return ipetal;    }

void
init_arg(string arg)
{
	 sscanf(arg, "#PETALS#%d", ipetal);
	 set_petals(ipetal);
}
mixed
query_auto_load()
{
	 return (MASTER + ":#PETALS#" + ipetal);
}


public string my_long()
{
    return 
    "This simple little rosebud is unique. It is known as a "+
	    "fire rose because the orange-red color of its petals is in "+
		"constant, flickering motion reminiscent of flames. "+
		"It is unusually warm in your hand and perhaps the most beautiful "+
		"flower you have ever seen. It looks like it has "+ ipetal +
        (ipetal == 1 ? " petal" : " petals") +
		". You feel an urge to pluck a petal from the rose.\n";
}

void
create_object()
{
	/* Simple roses start with 5 petals. */
	if (!ipetal)
		set_petals(5);
	
    set_name("_Avenir_fire_rose");
    add_name(({"rose", "rosebud", "bud", "flower", "_Mascarvin_rose"}));
    set_short("orange-red rosebud");
    add_adj(({"red", "orange", "orange-red", "enchanted", "fire", 
	    "death", "mascarvin"}));
    set_long(my_long);

    add_item(({"petal", "petals"}), "@@petal_desc");
    add_prop(OBJ_S_WIZINFO,  "This rose is enchanted. "+
        "The petals of this rose can be plucked. "+
        "The petals will burst into flame when dropped. "+
		"Provided block is globally allowed, "+
        "when tossed in the direction of an exit, the petal's flames "+
        "will block that exit for a short period of time (15-30sec). "+
        "Those with int<50 and those with illusion>40-59 will be able "+
        "to pass through the flames, in addition to whomever holds "+
        "tossed the petal.\n");

    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "This rose is enchanted.\n", 10,
        "The petals of this rose can be plucked.\n", 15,
        "The petals will burst into flame when dropped.\n", 20,
        "When tossed in the direction of an exit, the petal's flames "+
        "will block that exit for a short period of time, if wizards "+
		"permit blocking at the time.\n", 25,
        "Fools and those skilled in the art of illusion will be able "+
        "to pass through the flames, in addition to the whomever tossed "+
        "the petal.\n", 30 }));

    add_prop(OBJ_M_NO_BUY, "It is absolutely priceless. A lifetime of "+
        "drudgery and thrift and you still wouldn't have enough plats "+
        "to buy it!"); 
    add_prop(OBJ_M_NO_SELL, "No shopkeeper would dare to buy this from "+
	    "you!\n");	
    add_prop(OBJ_M_NO_DROP, "The gifts of the Gods are not so easily "+
	    "disposed of!"); 
	add_prop(OBJ_M_NO_GIVE, "You dare not risk offending Mascarvin by "+
	    "giving away this rose."); 
	
    add_prop(OBJ_I_VALUE,  1750); // 1 plats give or take.
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 200);
    seteuid(getuid());
}

string
petal_desc()
{
    string str;
    switch(ipetal)
    {
        case 0: 
          str = "There aren't any more petals.\n";
          break;
        case 1:
          str = "There is just one petal left.\n";
          break;
		case 2:
          str = "There are just two petals left of this once-magnificent "+
		        "rose.\n";
          break;

        case 3:
          str = "Even with just three petals left, this rose is a thing "+
                "of beauty!\n";
          break;
        case 4:
          str = "The petals are orange-red in colour that flickers "+
                "and swirls before your eyes. It appears that one of "+
                "the petals are missing.\n";
          break;
        case 5:
          str = "The petals are orange-red in colour that flickers "+
                "and swirls before your eyes. The rose is in "+
                "perfect condition. None of the unusual orange-red "+
                "petals is missing.\n";
          break;
        default:
          str = "The petals are swirling with orange-red color.\n";
          break;
    }

    return str;
}

int 
do_pluck(string str)
{
    object petal;
    
    notify_fail("Pluck what from where?\n");
    if (!str || !strlen(str))    
        return 0;

    notify_fail("Try <pluck petal from rose>.\n");
    if (!parse_command(str, ({ }),
        "[a] 'petal' / 'petals' [from] [the] 'rose'"))
        return 0;    
		
    // Sanity check. It should remove when the last one is plucked
	// but just in case....
    if (query_petals() < 1)
    {
        TP->catch_msg("There aren't any petals left to pluck.\nThe rose has fallen apart.\n");
		TO->remove_object();
        return 1;
    }
    
    if (PVP_ABILITY_DISABLED)
	{
		write("Plucking petals from this rose has been "+
		    "temporarily disabled by wizards.\n");
		return 1;
	}
    
    write("You grasp a velvet-smooth petal between thumb and fore"+
        "finger and gently pluck it from the rose.\n");

    ipetal--;
    petal = clone_object(OBJ + "rose_petal");
    petal->move(TP, 1);

    if (query_petals() < 1)
	{
		TP->catch_msg("The orange-red rosebud falls apart.\n");
	    TO->remove_object();
	}
    return 1;
} 

void
init()
{
    ::init();
    add_action(do_pluck,    "pluck");
    add_action(do_pluck,    "pull");
}

       
