/*  
*   /d/Kalad/common/wild/pass/giants/obj/stomach.c
*
*   A bodypart from wolves, to allow looting items with value
*   without the question of how the wolf was carrying that 
*   robe/sword etc.
*
*   Created by Meton, Okt 2021.
*/



inherit "/std/object.c";
#include "/d/Kalad/defs.h"
#include "../local.h"

#define DIRTY_OBJECT        "/d/Kalad/std/dirtiness"
#define DIRTY_OBJECT_ID     "_kalad_dirty_object"

create_object()
{
    ::create_object();
    set_name("misshapen stomach");
    add_name("stomach");
    set_short("misshapen stomach");
    set_pshort("misshapen stomachs");
    set_long("A nasty blood cowered sack, cut from a wolf. You could cut "
        + "it open to see which object causes the lumps and velts in this "
        + "organ.\n");
    add_prop(OBJ_M_NO_SELL,"It is too disgusting.\n");
    add_prop(OBJ_I_VALUE,250);
    add_prop(OBJ_I_VOLUME,2500);
    add_prop(OBJ_I_WEIGHT,5000);

}
void
init()
{
    ::init();
    AA(cut,cut);
}

/*
 * Function name:        cut
 * Description  :        Checks if player has sharp weapon and gives item
                            if the player does. Makes player filthy.
 * Arguments    :        stomach - to cut stomach.
 * Returns      :        1 - success, 0 - failure
 */
int
cut(string str)
{
    
    setuid();
    seteuid(getuid(TO));

    object item, *weapons, *ob;
    int i, slash;

    if(!str || str != "stomach")
    {
        NF("What do you want to cut? The stomach?\n");
        return 0;
    }

    weapons = this_player()->query_weapon(-1);
    for (i = 0 ; i < sizeof(weapons) ; i++)
    {
        if (weapons[i]->query_dt() & W_SLASH)
        {
            slash = 1;
            break;
        }
    }

    if (!slash)
    {
        notify_fail("Better find something sharper than that to cut with.\n");
        return 0;
    }

    ob = filter(all_inventory(this_player()), 
        &operator(==)(DIRTY_OBJECT_ID) @ &->query_name());

    if (!sizeof(ob))
    {
        clone_object(DIRTY_OBJECT)->move(this_player());
    }
    
    item = clone_object(one_of_list(WOLFITEM));
    item->move(TP);

    TP->add_prop(LIVE_I_DIRTY, TP->query_prop(LIVE_I_DIRTY) + 50);

    write("You cut the misshapen stomach open, and a " + item->short()
        + " tumbles out with all the other things that the wolf ate and "
        + "had not digested yet.\n");
    say(QCTNAME(TP) + " cuts open a misshapen stomach, and is covered in "
        + "various semidigested fluids.\n");

    TO->remove_object();
    return 1;
}
