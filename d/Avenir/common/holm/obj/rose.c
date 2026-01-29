// -*-C++-*- 
// Fire Rose        /d/Avenir/common/holm/obj/rose.c       
// creator(s):      Lilith  01/20/97
// purpose:         Enchanted rose for Beast Treasure
// last update:     
// note:            The petals of this flower burst into flames 
//                  when dropped. They can be used to block exits
//                  for a short period of time.
//                  Related objects: petal.c and flames.c
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";
#include "/d/Avenir/common/holm/holm.h"
#define  ROSE_PROP  "_Magic_Rose_Owner"

int ipetal = 5;

void
create_object()
{
    set_name("fire rose");
    add_name(({"rose", "rosebud", "bud", "Magic_Rose"}));
    set_short("orange-red rosebud");
    add_adj(({"red", "orange", "enchanted", "fire", "rose"}));
    set_long ("This rose is unique. It is known as a fire rose because "+
        "the orange-red color of its petals is in constant, flickering "+
        "flickering motion reminiscent of flames. It is perhaps the "+
        "most beautiful flower you have ever seen.\n");

    add_item(({"petal", "petals"}), "@@petal_desc");
    add_prop(OBJ_S_WIZINFO,  "This rose is enchanted. "+
        "The petals of this rose can be plucked. "+
        "The petals will burst into flame when dropped. "+
        "When tossed in the direction of an exit, the petal's flames "+
        "will block that exit for a short period of time. "+
        "Fools and those skilled in the art of illusion will be able "+
        "to pass through the flames, in addition to the whomever holds "+
        "this rose.\n");

    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "This rose is enchanted.\n", 10,
        "The petals of this rose can be plucked.\n", 15,
        "The petals will burst into flame when dropped.\n", 30,
        "When tossed in the direction of an exit, the petal's flames "+
        "will block that exit for a short period of time.\n", 45,
        "Fools and those skilled in the art of illusion will be able "+
        "to pass through the flames, in addition to the whomever holds "+
        "this rose.\n", 60 }));
 
    add_prop(OBJ_I_VALUE,  6000);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_M_NO_BUY, "It is absolutely priceless. A lifetime of "+
        "drudgery and thrift and you still wouldn't have enough plats "+
        "to buy it!");
    seteuid(getuid());
}

string
petal_desc()
{
    string str;
    switch(ipetal)
    {
        case 0: 
          str = "There aren't anymore petals.\n";
          break;
        case 1..2:
          str = "The petals are orange-red in colour that flickers "+
                "and swirls before your eyes. There is only one or "+
                "two petals left.\n";
          break;
        case 3:
          str = "Even with the petals half-gone, this rose is a thing "+
                "of beauty!\n";
          break;
        case 4:
          str = "The petals are orange-red in colour that flickers "+
                "and swirls before your eyes. It appears that two of "+
                "the petals are missing.\n";
          break;
        case 5:
          str = "The petals are orange-red in colour that flickers "+
                "and swirls before your eyes. The rose is in near-"+
                "perfect condition. Only one of the unusual orange-red "+
                "petals is missing.\n";
          break;
        default:
          str = "The petals swirl with orange-red color.\n";
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

    if (!ipetal)
    {
        write("There aren't any petals left to pluck.\n");
        return 1;
    }
    
    write("You grasp a velvet-smooth petal between thumb and fore"+
        "finger and gently pluck it from the rose.\n");

    ipetal--;
    petal = clone_object(HOLM_OBJ + "petal");
    petal->move(TP, 1);

    return 1;
} 

void
init()
{
    ::init();
    add_action(do_pluck,    "pluck");
    add_action(do_pluck,    "pull");
}

void
enter_env(object dest, object old)
{
    if (interactive(dest))
    {
        dest->add_prop(ROSE_PROP, 1);
    }
         
   :: enter_env(dest, old);
}

void
leave_env(object from, object to)
{
    from->remove_prop(ROSE_PROP);
    
    ::leave_env(from, to);
}


       
