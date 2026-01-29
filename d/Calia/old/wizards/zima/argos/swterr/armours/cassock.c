/* Stolen Cassock
** This Cassock is a quest item. It is stolen from the Library/Museum
** in the city. The quest is to find and return it to the Curator.
** The Cassock is found with 'search forest' in swterr/rooms/sfor13.c
** where the woodsmen who stole it hid it. The woodsmen will attack
** and not allow a player with the cassock to leave their campsite
**
** History:
** Date         Coder         Action
** --------- -------------  ---------------------------------
** 8/10/95   Zima           Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
#include "defs.h"
 
void create_armour() {
    set_name("cassock");
    add_name(STOLEN_CASSOCK);
    set_adj("white");
    set_short("white cassock");
    set_long("It is a white cassock embroidered with three evergreen "+
             "leaves on the front.\n");
    set_ac(1);
    set_at(TS_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}
