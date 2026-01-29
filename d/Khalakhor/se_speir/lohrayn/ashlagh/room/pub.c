/*
* pub.c
*
*  Pub of Baile Ashlagh
*
* Zima - June 10, 98
*
* Modified - added inherit "/d/Khalakhor/lib/pub"
* with updated menu
* Damaris 01/2001
*/
#pragma strict_types
 
inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/pub";
 
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"
string
dummy_menu()
{
    read_menu("menu");
    return "";
} 
#define NUM_PATRONS 2
object pubtender;
object *patron = allocate(NUM_PATRONS);
 
public int * query_local_coords() { return ({2, 7}); }
 
//
// fix_food - masked to fix problem for heap unit value
//
public object fix_food(mixed data)
{
    object ob;
    ob = ::fix_food(data);
    ob->add_prop(HEAP_I_UNIT_VALUE, 0);
    return ob;
}
 
//
// fix_drink - masked to fix problem for heap unit value
//
public object fix_drink(mixed data)
{
    object ob;
    ob = ::fix_drink(data);
    ob->add_prop(HEAP_I_UNIT_VALUE, 0);
    return ob;
}
 
//
// order - mask so player can't order if no pubtender
//
public int order(string item)
{
   if (pubtender && present(pubtender,TO))
      return ::order(item);
   TP->catch_tell("There is no one here to sell you anything!\n");
   return 1;
}
 
//
// create_pubtender
//
public void create_pubtender()
{
    ::reset_room();
    if (!pubtender)
        {
        pubtender = clone_object(NPC + "pubkeeper");
        pubtender->equip_me();
        pubtender->move(TO);
        tell_room(TO, QCTNAME(pubtender) + " straightens " +
            "up from behind the bar.\n");
        }
    else if (!present(pubtender))
        {
        if (pubtender->query_attack()) return;
        tell_room(environment(pubtender), QCTNAME(pubtender) +
            " suddenly looks around with a start, and rushes " +
            "off somewhere.\n");
        pubtender->move_living("M", TO);
        tell_room(TO, QCTNAME(pubtender)+" rushes in from the courtyard.\n");
        }
}
 
//
// create_patron
//
public void create_patron(int i, string name)
{
   if (patron[i]) return;
   seteuid(getuid());
   patron[i] = clone_object(NPC+name);
   patron[i]->equip_me();
   patron[i]->move(TO);
   tell_room(TO,QCNAME(patron[i])+" wanders in from the courtyard.\n");
}
 
//
// reset_room
//
public void reset_room()
{
   create_pubtender();
   create_patron(0,"villager");
   create_patron(1,"guard");
}
 
//
// create_khalakhor_room
//
public void
create_khalakhor_room()
{
    set_short("The Taigh Leann");
    set_long("You're in the Taigh Leann which is the village tavern. "+
        "The walls are mostly bare and windowless, a prudent arrangement "+
        "in the event of altercations. A clay-brick hearth on the "+
        "west wall warms the pub from the chill. There is a bar running "+
        "along the south side of the tarvern, behind which a long "+
        "shelf houses glasses, bottles, ales and spirits. There are a "+
        "few small wooden tables and benches scattered about.\n");
 
    add_item(({"walls", "wall"}),
        "They look the way they do on the outside, planks of wood "+
        "painted in pastel blue, framed and crossed with thick dark "+
        "brown beams.\n");
    add_item(({"bar"}),
        "Nothing very fancy, the bar is made from a few planks " +
        "of wood which have been highly polished. There is a small "+
        "sign tacked to it.\n");
    add_item(({"table","tables"}),
        "The tables are long and low, constructed in similar " +
        "fashion to the bar, except fronted with a few small " +
        "benches.\n");
    add_item(({"benches","bench"}),
        "They are long and low, fairly simple, made of similar material "+
        "as the bar.\n");
   add_item("menu", &dummy_menu());
 
    INSIDE;
 
    add_drink(({"leann","beer","mug","mug of beer","mug of leann"}),
        ({"mug of leann","leann"}), "golden",
        150, 12, 12,
        "mug of leann", "mugs of leann",
        "It is a mug of leann, or celtic beer.\n", "");
    add_drink(({"bitter","pint","pint of bitter"}),
        ({"pint of bitter","bitter"}), "golden", 550, 27, 82,
        "pint of bitter","pints of bitter",
        "The large wooden mug contains a full pint of a strong-" +
        "smelling, golden bitter.\n", "");
    add_drink("whiskey", "whiskey", "golden",
        100, 40, 170,
        "glass of whiskey", "glasses of whiskey",
        "The small glass contains a golden whiskey with a " +
        "strong, smooth aroma.\n", "");
 
    add_food("herring", "herring", "fried",
        50, 10,
        "fried herring", "fried herrings",
        "The small herring has been deboned and fried.\n", "");
    add_food(({"mutton", "mutton steak"}), "steak", "mutton",
        500, 110,
        "mutton steak", "mutton steaks",
        "The mutton steak has been broiled over a fire.\n", "");

    add_exit("court3","north");
    reset_room();
}
void
pub_hook_menu_header()
{
    write(sprintf("%|76s\n\n", "Taigh Leann Menu"));
}  
//
// initialize pub support
//
void init()
{
    ::init();
    init_pub();
}
