
/*  
   Squashed tomato for throwing at people in the pillory in Gelan.   
   Can be thrown in various ways. 

   Coded by Maniac 11/11/95 
*/

inherit "/std/food";
inherit "/cmd/std/command_driver";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "object.h"


string *land = ({"on the nose", "in the left eye", "in the right eye",
                 "in the mouth", "on the left cheek", 
                 "on the right cheek", "in the left ear", 
                 "in the right ear"});

string *splat_types = ({"a wickedly messy", "a tremendously messy", 
                        "a horribly messy", "a wonderfully messy", 
                        "an extremely messy", "a very squelchy" });

void
special_effect(int n)
{
    write("Yeuch!\n");
}

string
desc()
{
    return capitalize(short()) + ", perfect for pelting " +
        "someone in the pillory in Gelan. You may throw one in a " +
        "variety of ways: pitch/lob/spin/toss tomato at <player>.\n";
}

void
create_food()
{
    string s;

    set_name("tomato");
    set_pname("tomatoes");
    set_adj(({"rotten", "squashy"}));
    set_short("rotten squashy tomato"); 
    set_pshort("rotten squashy tomatoes");
//    set_long("A rotten squashy tomato, perfect for pelting " +
//             "someone in the pillory in Gelan. You may throw it in a " +
    set_long("@@desc@@"); 
    add_prop(OBJ_I_VALUE, 0);
    set_amount(1);
}


/* Function to handle the action of throwing the tomato in various ways
   at players. */
int
do_throw(string str)
{
    object tp, *p; 
    string v, tv, hit_des_pre_me, hit_des_pre_them, hit_des_post, splat, s;

    s = "rotten squashy tomato";

    tp = this_player();
    v = query_verb();

    if (!stringp(str)) 
        str = "";

    p = parse_this(str, "[the] [rotten] [squashy] [tomato] [at] %l"); 

    if (!sizeof(p)) {
        notify_fail(capitalize(v) + " what at whom?\n");
        return 0;
    }


    if (sizeof(p) > 1) {
        notify_fail("You can only " + v + " the tomato at one " +
                    "person at once.\n");
        return 0;
    }


    splat = "with " + splat_types[random(sizeof(splat_types))] + " splat!";
    switch (v) {  
        case "pitch" :
                      hit_des_pre_them = ("sends a " + s + 
                                    " whizzing at high speed towards");
                      hit_des_pre_me = ("send the " + s +
                                    " whizzing at high speed towards");
                      break;
        case "lob" : hit_des_pre_them = ("lobs a " + s + " high " +
                                    "into the air above");
                     hit_des_pre_me = ("lob the " + s + " high " +
                                    "into the air above");
                     break;
        case "toss" : 
        case "throw" : 
                      hit_des_pre_them = ("slowly tosses a " + s + 
                                          " at");
                      hit_des_pre_me = ("slowly toss the " + s +
                                          " at");
                      break;
        default : 
                     hit_des_pre_them = 
                              ("cleverly spins a " + s + " at");  
                     hit_des_pre_me = 
                              ("cleverly spin the " + s + " at");  
                     break;
    }

    if (!p[0]->query_prop(LIVE_I_STUNNED) && 
        (random(this_player()->query_stat(SS_DEX)) < 
         random(p[0]->query_stat(SS_DEX) / 2))) {
        actor("You " +  hit_des_pre_me, p, ". It misses."); 
        target(" " + hit_des_pre_them + " you. It misses.", p);  
        all2act(" " + hit_des_pre_them, p, ". It misses.");   
        return 1;
    }

    hit_des_post = (land[random(sizeof(land))] + " " + splat); 

    actor("You " +  hit_des_pre_me, p, ". It hits " + 
           p[0]->query_objective() + " " + hit_des_post);
    target(" " + hit_des_pre_them + " you. It hits you " + 
           hit_des_post, p);
    all2act(" " + hit_des_pre_them, p, ". It hits " + 
           p[0]->query_objective() + " " + hit_des_post);

    set_heap_size(num_heap() - 1);
    return 1;
}


void
init()
{
     ::init();
     add_action(do_throw, "pitch");
     add_action(do_throw, "lob"); 
     add_action(do_throw, "spin");
     add_action(do_throw, "toss");
     add_action(do_throw, "throw");
}

