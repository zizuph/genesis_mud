
inherit "/d/Avenir/inherit/weapon";
#include "/d/Avenir/common/bazaar/bazaar.h"


void
create_weapon()
{
   set_short("backscratcher");
   set_name("backscratcher");
   add_name(({"scratcher", "device", "utensil"}));
   add_adj("wooden");

  
   add_prop(OBJ_I_WEIGHT, 250);  	/* 0.25 kg */
   add_prop(OBJ_I_VOLUME, 500);         /* 0.5  L  */    
   add_prop(OBJ_I_VALUE,  70);
   
   set_long(
     "A long wooden stick with a miniature cupped hand at one end "+
     "and a handle at the other. With it, a person can scratch all "+
     "of those places which are so hard to reach under armour.\n"+
     "For instructions on the proper use of this device, use "+
     "<help scratcher>.\n");
   add_item("handle", "The far end of the wooden stick. It has "+
     "been wrapped in oiled leather for an easy grip.\n");
   add_item("hand", "It is a small wooden hand that is cupped "+
      "in such a way as to be useful for scratching.\n");
   add_cmd_item("scratcher", "help", 
       "To use the backscratcher, type: 'itch <body part>'\n");

}
void
init()
{
   ::init();
   add_action("scr_func", "itch");
}

int
scr_func(string arg)
{
/*
    notify_fail("Itch where with the backscratcher?\n");
    return 0;
*/
    if (!query_wielded()) 
    {
        write("You need to wield it, first.\n");
        return 1;
    }

    if (!arg) 
    {
        write("You idly scratch yourself where it itches.\n");
        say(QCTNAME(TP) + " idly scratches "+ 
        TP->query_objective() +"self where it itches.\n");
        return 1;
    }
    if (arg == "back" || arg == "spine") 
    {
        write("Raising your arm, you tuck the backscratcher "+
            "behind you.\nYou give your "+ arg +" a nice long, "+
            "satisfying scratch right where it itches.\n");
        say(QCTNAME(TP) + " gets a blissful look on "+
            TP->query_possessive() +" face as he scratches "+
            TP->query_possessive() +" back with the backscratcher.\n");
            TP->command("sigh hap");
            write("Heavenly!\n");
        return 1;
    }
    if (arg == "butt" || arg == "bottom" || arg == "ass" || arg == "behind") 
    {
        write("With a flick of your wrist the backscratcher "+
            "is in position.\nYou give your bottom a fierce, "+
            "intensely satisfying scratching.\n");
        say("With a flick of "+TP->query_possessive() +" wrist, "+
            QCTNAME(TP) +" uses the backscratcher on "+ 
            TP->query_possessive() +" behind, giving it a fierce, "+
            "intensely satisfying scratching.\n"); 
       return 1;
    }
    if (arg == "eye" || arg == "eyebrow" || arg == "nose" || arg == "face") {
        write("You hold the scratcher up to your face. It looks "+
            "like it could do a lot of damage...maybe even cost "+
            "you an eye.\nYou decide that your "+ arg +" doesn't "+
            "itch that much after all.\n");
        say(QCTNAME(TP) +" seems to examine the backscratcher "+
            "closely.\n");
        return 1;
    }

    if (arg == "toe" || arg == "toes" || arg == "foot" || arg == "feet") 
    {
        write("You dig at your "+ arg +" with the scratcher. It "+
            "feels great.\nWhen you are finished scratching, you "+
            "bang the device against your leg to clear it of "+
            "the toe-jam that has collected in the little cupped "+
            "hand.\n");
        say(QCTNAME(TP) +" digs at "+ TP->query_possessive() +
            " "+ arg +" with the backscratcher.\n");
        return 1;
    }

    if (arg == "balls" || arg == "chin" || arg == "armpit" ||
        arg == "arm" || arg == "leg" || arg == "neck"
        || arg == "thigh" || arg == "hand" )
    {
        write("You scratch your "+ arg +" with the backscratcher.\n");
        say(QCTNAME(TP) +" gives "+ TP->query_possessive() +" "+ arg +
            " a very satisfying scratch with the backscratcher.\n");
        return 1;
    }
    
   write("You can't seem to reach it with the scratcher.\n");
   return 1;
}




