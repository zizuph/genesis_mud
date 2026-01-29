/*
 * trunk.c
 *
 * A standard trunk cloned into villager homes in Tabor Sogh
 * which contains random contents. Good aligned players taking
 * these villager's possessions will find their alignmet
 * going straight to hell ;)
 *
 * Khail - January 17 / 98.
 */
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"

#define K_STOLE_FROM_CHEST    "_khal_live_i_stole_from_chest"
#define K_VILLAGER_BELONGING  "_khal_obj_i_villager_belonging"

inherit "/std/receptacle";

/*
 * Function name: reset_receptacle
 * Description  : Resets variables. Here, it ensures that
 *                there's something in the chest, and that it
 *                is closed and locked.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_receptacle()
{
    int items = random(2) + 1;
    int i;
    object ob;

    /* If there's already something in the trunk, don't */
    /* clone new items for it. */
    if (sizeof(all_inventory()))
    {
        add_prop(CONT_I_CLOSED, 1);
        add_prop(CONT_I_LOCK, 1);
        return;
    }

    seteuid(getuid());

    /* Clone 'items' random items. */
    for (i = 0; i <= items; i++)
    {
      /* Pick a one of five items at random. */
        switch (random(5))
        {
            case 0:
                ob = clone_object("/d/Khalakhor/common/kilts/kilt_garrow");
                break;
            case 1:
                ob = clone_object("/d/Khalakhor/common/wep/dirk");
                break;
            case 2:
                ob = clone_object("/std/coins");
                ob->set_coin_type("silver");
                ob->set_heap_size(10 + random(20));
                break;
            case 3:
                ob = clone_object("/d/Khalakhor/common/arm/vest_wool");
                break;
            default:
                ob = clone_object("/d/Khalakhor/common/arm/breeches");
          /* Identify the item as belonging in the chest. */
          /* This is so we don't penalize players for taking */
          /* their own things out of the chest if they've put */
          /* them in for some reason. */
        }
        ob->move(TO, 1);
        ob->add_prop(K_VILLAGER_BELONGING, 1);
    }
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);
}

/*
 * Function name: try_break
 * Description  : Called for a VBFC response if players try
 *                to break the trunk.
 * Arguments    : n/a
 * Returns      : ""
 */
public string
try_break()
{
    write("You hammer away on the trunk for awhile in " +
        "a futile attempt to break it open.\n");
    say(QCTNAME(TP) + " hammers away at the trunk for " +
        "awhile in a futile attempt to break itopen.\n");
    return "";
}

/*
 * Function name: try_kick
 * Description  : Called for a VBFC response if players try
 *                to kick the trunk.
 * Arguments    : n/a
 * Returns      : ""
 */
public string
try_kick()
{
    write("You back off and give the chest a good swift " +
        "kick.\n");
    say(QCTNAME(TP) + " backs off and gives the chest a good " +
        "swift kick.\n");
    tell_room(environment(TO), "A loud popping sound " +
        "echoes through the room!\n");
    write("That popping sound was your toe!\n");
    TP->command("$scream");
    write("You hop around the room on one foot like a " +
        "madman, holding onto your poor injured toe with " +
        "both hands until the throbbing stops.\n");
    say(QCTNAME(TP) + " hops around the room on one foot " +
        "like a madman, frantically holding onto " + HIS_HER(TP) +
        "his apparently injured toe.\n");
    return "";
}

/*
 * Function name: create_receptacle
 * Description  : Turns this object into a trunk.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_receptacle()
{
    add_name(({"trunk","receptacle","chest"}));
    add_pname(({"trunks","receptacles","chests"}));
    set_adj(({"heavy","wooden"}));
    set_short("heavy wooden trunk");
    set_pshort("heavy wooden trunks");
    set_long("This heavy wooden trunk contains what few meagre " +
        "possessions the owner of this home owns. Heavy wood " +
        "planks bound in iron straps make for a secure method " +
        "of keeping them safe, right down to the heavy lock " +
        "on the front.\n");
    add_item(({"wood","planks","wood planks"}),
        "They appear to be made from some sort of hardwood, " +
        "possibly oak, and very thick.\n");
    add_item(({"lock","heavy lock"}),
        "The lock is built right into the chest, and though " +
        "sturdy, it looks none too complicated.\n");
    add_item(({"straps","iron straps","iron","strap","iron strap"}),
        "The iron straps binding the trunk together aren't " +
        "fancy, but then iron doesn't have to be pretty to be " +
        "effective.\n");
    add_item(({"lid","top"}),
        "The lid of the trunk is slightly curved on the top, " +
        "but just as strong as the rest of the trunk.\n");
    add_cmd_item(query_names(),
        ({"break","smash","kick"}),
        ({VBFC_ME("try_break"), VBFC_ME("try_break"),
          VBFC_ME("try_kick")}));

    set_key(2398983);
    set_pick(30);

    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 200000);
    add_prop(CONT_I_MAX_VOLUME, 400000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The chest is far to heavy and bulky " +
        "for you to move.\n");
    add_prop(OBJ_I_VALUE, 400);

    enable_reset(30);
    reset_receptacle();
}

/*
 * Function name: prevent_leave
 * Description  : Called when someone tries removing an object
 *                from this trunk.
 * Arguments    : ob - Object pointer to what the player is trying
 *                     to remove.
 * Returns      : 1 - Can't remove from this object.
 *                0 - Can remove from this object.
 */
public int
prevent_leave(object ob)
{
    int align;

    align = TP->query_alignment();

  /* Ignore players who have a low alignment or have */
  /* already been penalized for stealing (to prevent */
  /* players from using this as an easy way to drive */
  /* down alignment.) Also ignore any object that */
  /* don't have the K_VILLAGER_BELONGING prop. */
    if (TP->query_alignment() <= 400 || 
        TP->query_prop(K_STOLE_FROM_CHEST) ||
        !(ob->query_prop(K_VILLAGER_BELONGING)))
        return 0;

  /* Deliver a nasty message to 'goody' thieves. */
    write("Stealing this poor villager's " + ob->short() + "?" +
        " And you have the nerve to call yourself " +
        TP->query_align_text() + "! This fares poorly for " +
        "your reputation.\n");

  /* Reduce the thieve's alignment by 1/10 */
    TP->set_alignment(align - align/10);
  /* Add a prop to the player identifying him as having */
  /* stolen from the chest. */
    TP->add_prop(K_STOLE_FROM_CHEST, 1);
    return 0;
}
