// Grace & Tep 1995: Toothpick
// Updates: Lilith Sep 2021, made toothpick "slash" as well as "impale"
inherit "/d/Avenir/inherit/weapon";
#include "/d/Avenir/common/bazaar/bazaar.h"


void
create_weapon()
{
    set_short("toothpick");
    set_name("toothpick");
    add_name(({"pick", "sliver"}));
    add_adj(({"wooden", "small", "slender"}));
  
    add_prop(OBJ_I_WEIGHT, 25);  	/* 0.025 kg */
    add_prop(OBJ_I_VOLUME, 5);         /* 0.005  L  */    
    add_prop(OBJ_I_VALUE,  10);
    
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);
    set_hit(1);
    set_pen(1);

    set_long(
     "A very small, slender sliver of wood used for picking "+
     "the teeth and gums.\nTo use it properly, just 'clean "+
     "teeth', 'suck toothpick', or 'roll toothpick'.\n");
}

void
pick_result()
{
    int rnd;
    rnd = random(3);

    switch(rnd)
    {
        case 0:
            write("You succeed in dislodging a lump of something. "+
               "It leaves a nasty taste on your tongue.\n");
            break;
        case 1:
            write("You taste your own blood as the tip of the tooth"+
                "pick pricks your gums.\n");
            break;
        case 2:
            write("You dislodge something with your picking, and "+
                "it sure stinks!\n");
            break;
    }
}
                    
int
pick_func(string arg)
{
    if (!arg)
    {
    notify_fail("Clean what with the toothpick? Your teeth?\n");
    return 0;
    }

    if (!query_wielded()) 
    {
        write("You need to wield it, first.\n");
        return 1;
    }

    if (arg == "tooth" || arg == "teeth" || arg == "gums") 
    {
        write("You open your mouth and pick carefully at your "+
            arg + " with the toothpick.\n");
        say(QCTNAME(TP) + " carefully cleans "+
            TP->query_possessive() +" "+ arg +
            " with a toothpick.\n");        
        set_alarm(3.0, 0.0, pick_result);
        return 1;
    }

   write("Cleaning that with a toothpick isn't wise.\n");
   return 1;
}

int
suck_func(string arg)
{
    notify_fail("Suck what? The toothpick?\n");
    if (!arg)
        return 0;

    if (arg == "toothpick" || arg == "pick") 
    {
        write("You put the "+ short()+ " in your mouth and suck "+
            "on it.\n");
        say(QCTNAME(TP) + " puts a toothpick in "+
            TP->query_possessive() +" mouth and "+
            "sucks on it.\n");        
        return 1;
    }
}

int
roll_func(string arg)
{
    notify_fail("Roll what? The toothpick?\n");
    if (!arg)
        return 0;

    if (arg == "toothpick" || arg == "pick") 
    {
        write("You put the "+ short()+ " in your mouth and roll "+
            "it across your lips with your tongue.\n");
        say(QCTNAME(TP) + " puts a toothpick in "+
            TP->query_possessive() +" mouth and rolls it across "+
            TP->query_possessive() +" lips with "+
            TP->query_possessive() +" tongue.\n");
        return 1;
    }
}

void
init()
{
   ::init();
   add_action(pick_func, "clean");
   add_action(suck_func, "suck");
   add_action(roll_func, "roll");
}



