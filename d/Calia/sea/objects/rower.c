
/* 
    Rowing boat, varying types. 

    Coded by Maniac, 30/7/96
 */ 

#pragma save_binary

inherit "/d/Calia/std/boat"; 

#include <language.h>

#define ROWER_SIZE ({ ({ "large", "twelve feet", "four feet", 5 }), \
                      ({ "sleek", "ten feet", "four feet", 4 }), \
                      ({ "small", "eight feet", "three feet", 3 }) }) 

#define ROWER_COLOUR ({  "beige", "white", "grey", \
                         "blue", "red" })

#define ROWER_DESIGN ({ "beautiful mermaid",  \
                        "vicious sea snake", \
                        "gangling octopus", \
                        "terrifying shark", \
                        "sleek dolphin", \
                        "speeding swordfish", \
                        "head of a water kroug on a spear", \
                        "proud Calian warrior", \
                        "deep sea hippopotamus" }) 


string bd; 


void
create_boat()
{
    string *rs = ROWER_SIZE;  
    string *rc = ROWER_COLOUR; 
    string *rd = ROWER_DESIGN; 

    string d2, d3; 
    mixed d1; 

    d1 = rs[random(sizeof(rs))]; 
    d2 = rc[random(sizeof(rc))]; 
    d3 = rd[random(sizeof(rd))]; 

    set_name("boat"); 
    set_adj(({d1[0], d2, "rowing"})); 
    set_short(d1[0] + " " + d2 + " rowing boat"); 

    bd = ("A " + d1[0] + " " + d2 + " rowing boat, some " + 
          d1[1] + " long and " + d1[2] + " wide. ");  

    set_max_passengers(d1[3]); 

    set_long(bd + "On its side is painted a picture of " + 
             LANG_ADDART(d3) + ".\n"); 

   add_item(({"picture", "side"}), "You see nothing special " +
                                   "about the picture.\n"); 
}


void
config_boat_inside()
{
    ::config_boat_inside(); 

    query_boat_in()->set_long(bd + "\n");  
    query_boat_in()->remove_item("boat"); 
    query_boat_in()->add_item("boat", bd + "\n"); 
}

