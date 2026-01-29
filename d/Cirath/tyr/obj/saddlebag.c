/*
* /d/Genesis/std/wearable_pack.c
*
*   Changed to a giant hair saddlebag for Tyr shop.
*   Nov 2020 Meton.
*/

#pragma save_binary
#pragma strict_types

#include <wa_types.h>

inherit "/d/Genesis/std/pack";
inherit "/lib/keep";
inherit "/lib/wearable_item";
#include <stdproperties.h>
#include <macros.h>


string recover;

/* Ensure here that the player removes the pack first if 
 * it leaves his/her inventory.
 */
void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);

    wearable_item_leave_env(old, dest);
}

/* Ensure that the player can properly appraise this item. 
 */
void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}

/******** Creation and Initialisation Functions ********/

public void
create_wearable_pack()
{
    set_name(({"saddlebag","hairy saddlebag", "hair pack",
        "hair saddlebag"}));
    set_short("hairy saddlebag");
    set_pshort("hairy saddlebags");
    set_long("A saddlebag woven from giant hair, very coarse and rough. "
        + "A small tag is fixed to it.\n");
    
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 250000);
    add_prop(CONT_I_VOLUME, 9000);
    add_prop(CONT_I_MAX_VOLUME, 250000);

    add_prop(OBJ_I_VALUE, 450);

    add_item(({"tag", "small tag"}),
      "        +---------------------------------------------+\n"
    + "        | There are small pictograms on this tag      |\n"
    + "        | showing a man doing various things:         |\n"
    + "        |                                             |\n"
    + "        | strap saddlebag on mount                    |\n"
    + "        | unstrap saddlebag on mount                  |\n"
    + "        | fill saddlebag on mount                     |\n"
    + "        | open saddlebag on mount                     |\n"
    + "        | close saddlebag on mount                    |\n"
    + "        | empty saddlebag on mount                    |\n"
    + "        | hpack (looking into the saddlebag)          |\n"
    + "        |. . . . . . . . . . . . . . . . . . . . . . .|\n"
    + "        | The last pictogram looks a bit like Trink,  |\n"
    + "        | the sly friendly half-elf that runs the     |\n"
    + "        | tarnished cup in Tyr.                       |\n"
    + "        +---------------------------------------------+\n");

}

nomask void
create_pack()
{
    set_slots(A_BACK);
    set_layers(15);
    set_looseness(8);    
    create_wearable_pack();
}

string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg);
}