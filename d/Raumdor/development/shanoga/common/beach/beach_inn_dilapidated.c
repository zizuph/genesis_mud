inherit "/d/Raumdor/room_std.c";
inherit "/lib/pub";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Raumdor/defs.h"
object obj;

void
create_room()
{
    set_short("The Battered Bastion");
      
    set_long("You are in a dilapidated pub just beyond the borders of the forest. Chairs and tables are scattered around to give travelers a place to rest and wait for the "+
    "relative safety of daylight before venturing into the forest. As it is daytime, the barkeep is focused on cleaning up from the previous night's visitors and preparing for "+
    "another busy night ahead. There is a raised stage along the wall farthest from the door.\n");
    
    
    
    add_item("bar", "A well-worn wooden surface with high chairs to sit on.\n");
    add_item(({"high chairs","stools"}), "There are some high bar stools along the bar.\n");
    add_item("menu", "It is haphazardly nailed to a post by the bar. You can read it.\n");
    add_item("chairs", "There are chairs scattered about the room that you can sit in.\n"); 
    add_item("tables", "If the tables were ever set up in an organized fashion, it has long been forgotten. You can see a broken table in one corner with some broken chairs.\n");
    add_item("stage", "There is a stage on the back wall where musicians often perform at night.\n");
    add_item("broken table", "Whether from extended use or raucous behaviour, this table has been damaged and set aside for the staff to repair later.");
    add_item("broken chair", "Whether from long-term use or a barfight, this chair has been damaged and set aside for the staff to repair later.");
    add_item("broken chairs", "Whether from long-term use or a barfight, these chairs have been damaged and set aside for the staff to repair later.");
    add_cmd_item("menu", "read", "@@read");
    add_prop(ROOM_I_INSIDE,1); 
    add_drink( ({ "beer", "beers", "Raumdor", "Raumdor beer" }),
      "beer", "Raumdor", 100, 8, 12, 0, 0,
      "Dark black beer.\n", 0);
    add_drink( ({ "wine", "wines", "red", "red wine" }),
      "wine", "red", 100, 20, 80, 0, 0,
      "It has a deep red color and smells strong.\n", 0);
    add_drink(({"whiskey","whiskeys","dark","dark whiskey"}),"whiskey",
      "dark",65,25,100,0,0,"A very potent looking drink. It smells "+
      "like whiskey, but is very dark in color.\n",0);
    add_drink(({"rum","rums","heavy","heavy rum"}),"rum","heavy",100,62,
      140,0,0,"A powerful looking drink. It looks thick and heavy, "+
      "and smells strong.\n",0);
    add_food( ({ "chicken", "chickens","spiced chicken" }),
      "chicken", "spiced", 60, 60, 0, 0,
      "Mmmm...smells wonderful.\n", 0);
    add_food( ({ "tofu", "plate of tofu and rice", "tofus", "rice" }),
      ({"tofu","rice"}), "tofu", 80, 80, "plate of tofu and rice", 
      "plates of tofu and rice",
      "Spicy, hot and sour rice with tofu chunks.\n", 0);
    add_food( ({ "beef", "mongolian", "plate of mongolian beef",
    "plate", "plates" }),
      "beef", "mongolian", 120, 120, "plate of mongolian beef",
      "plates of mongolian beef",
      "Steamy hot and spicy! A real man's meal.\n", 0);
    add_food(({"pork","mu shu","plate of mu shu pork","plate","plates"}),
      "pork","mu shu",160,160,"plate of mu shu pork",
      "plates of mu shu pork","A full plate piled high with steamy "+
      "rice and pork in special spicy sauce!\n",0);
    //add_exit(RAUM(drakmere/r07),"northwest",0,-1,-1);
    //add_exit(RAUM(drakmere/shop/inn2),"east",0,-1,-1);
    //obj = clone_object(RAUM(npc/barkeep.c));
    obj = clone_object("/d/Raumdor/development/barkeep_dev.c");
    obj->arm_me();
    obj->move_living("M",TO);
}
void
reset_room()
{
    if(!obj)
    {
    obj = clone_object(RAUM(drakmere/npc/b_maid.c));
    obj->arm_me();
    obj->move_living("xxx",TO);
    }
}


void
init()
{
    ::init(); 

    init_pub();
}

int
read(string str)
{
    write(
      "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"+
      "@       The Bloody Skull Inn        @\n"+
      "@-----------------------------------@\n"+
      "@ Raumdor beer   -  12 cc           @\n"+
      "@ Red wine       -  80 cc           @\n"+
      "@ Dark whiskey   - 100 cc           @\n"+
      "@ Heavy rum      - 140 cc           @\n"+
      "@                                   @\n"+
      "@ Spiced chicken -  60 cc           @\n"+
      "@ Tofu and rice  -  80 cc           @\n"+
      "@ Mongolian beef - 120 cc           @\n"+
      "@ Mu shu pork    - 160 cc           @\n"+
      "@                                   @\n"+
      "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    return 1;
}


/*
+~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
} @  The Battered Bastion  @ }
}                            }
} Raumdor Beer    ~    12 cc }
} Red Wine        ~    80 cc }
} Dark Whiskey    ~   100 cc }
} Heavy Rum       ~   140 cc }
}                            }
} Ham Sandwich    ~    60 cc }
} Tofu and Rice   ~    80 cc }
} Mongolian Beef  ~   120 cc }
} Mu Shu Pork     ~   160 cc }
} ~~~~~~~~~~~~~~~~~~~~~~~~~~ }
}     Food may be ordered    }
} 'to go' for an extra 12 cc }
} and it will be packaged to }
}  withstand the rot of the  }
}           forest           }
}                            }
} You can order any drink in }
}   a bottle to protect it   }
} from the rot of the forest }
} @                        @ }
+~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
*/
