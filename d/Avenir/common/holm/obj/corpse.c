//-*-C++-*-
// file name:   /d/Avenir/common/holm/obj/corpse.c 
// creator(s):  Lilith 12 March 97
// revised:     
// purpose:     Decoration for the Beast's Lab :) 
// note:         
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/container";
#include "../holm.h"
#include <wa_types.h>

int icorp, ihang;

/* Function name: reset_placed_functions
 * Description:   This function is called from the placer module to 
 *                reset the object. Can be used to fill the object with 
 *                contents. 
 *
 *    For when it is called see:
 *    /d/Avenir/smis/std/placer_mod.c
 *
 *    If it returns 1, the placer will do nothing, but if it returns 0,
 *    the placer will clone a new object.
 *
 */
int
reset_placed_functions()
{
    object horn;
    icorp = random(4);
    ihang = 0;

    if (sizeof(all_inventory(this_object())) < 1)
    {
        horn = clone_object(HOLM_OBJ + "b_horn");
        horn->move(TO, 1);
    }
    return 1;
}

void
create_container()
{
    set_name("corpse");
    add_name(({"experiment", "_beast_corpse"}));
    add_adj(({"chained", "manacled", "fettered"}));
    set_short("@@my_short");
    set_long("@@my_long");
    
    add_item(({"chain", "chains"}), "@@chain_check");
    add_prop(OBJ_M_NO_GET, "The corpse is too heavy for you.\n");

    setuid();
    seteuid(getuid());

    reset_placed_functions();
}

string
my_long()
{
    string str;
    switch (icorp)
    {
        case 0:
            str = "looks fairly fresh.\n";           
            break;
        case 1:
            str = "looks to be a few hours old.\n";
            break;
        case 2:
            str = "is stiff and beginning to smell.\n";
            break;
        case 3:
            str = "has been here for a few days at least, "+
                  "judging by the state of decay and the "+
                  "gut-wrenching stench.\n";
            break;
    }
    return "This is the corpse of some indeterminate individual "+
           "who appears to have been the subject of an experimental "+
           "surgical procedure. The corpse "+ str;
}

string
my_short()
{
    string str;
    if (!ihang)
        str = "corpse chained to the wall";
    else
        str = "unidentifiable corpse";
    return str;
}    
    
string
chain_check()
{
    if (!ihang)
        return "The corpse is attached to the wall by chains. "+
               "You might be able to free the corpse by chiseling "+
               "the chains from the wall.\n";
    else
        return "Manacles and fetters encircle the wrists and ankles "+
               "of the corpse. It appears that it was once chained "+
               "to a wall.\n";        
}

/*
 * Function name:  do_item_filter
 * Description:    Filter player inventory for wielded weapons.
 * Returns:        0 - if no wielded weapons, 1 - if there are.
 */   
int
do_item_filter(object ob)
{
    if ( (ob->query_wt() != W_KNIFE) && (ob->query_wt() != W_SWORD) &&
        (!ob->id("chisel")) )
        return 0;
    return objectp(ob->query_wielded());
}

/*
 * Function name:  free_me()
 * Description:    add_action for freeing corpse from a wall.
 * Returns:        0 - if not possible, 1 - if successful
 */   
int
free_me(string str)
{
    string qvb;
    int rnd;
    object *wep;
    qvb = query_verb();

    notify_fail(capitalize(qvb) +" what?\n");
    if (!str)    
        return 0;
 
    notify_fail("There aren't any chains attached to the wall.\n");
    if (ihang > 0)
        return 0;

    notify_fail("Perhaps you should try to chisel the chains from "+
        "the wall?\n");
    if (!parse_command(str, ({ }),
        "[a] / [the] 'chains' / 'chain' [from] [the] 'wall'"))
        return 0;    

    wep = filter(all_inventory(this_player()), do_item_filter);
    if (!sizeof(wep))
    {
        write("You need to be wielding something appropriate for "+
            "chiseling rock.\n");
        return 1;
    }
    rnd = random(10);
    if (rnd > 7)
    {
        write("You succeed in chiseling the chains from the "+ 
            "wall.\nThe corpse slumps down onto the ground.\n"); 
        say(QCTNAME(TP) +" succeeds in chiseling the chains "+
            "from the wall.\nThe corspe slumps down onto the "+
            "ground.\n");
        ihang = 1;
        return 1;
    }
    write("You manage to chisel some stone away from where the "+
       "chains are mounted in the wall.\n");
    say(QCTNAME(TP) +" manages to chisel some stone away from "+
        "where the chains are mounted in the wall.\n");
    return 1;
}            

void
init()
{
    ::init();

    add_action(free_me, "free", 1);
    add_action(free_me, "chisel", 1);
}


