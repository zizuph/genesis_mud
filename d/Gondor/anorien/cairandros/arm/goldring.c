/*
 * /d/Gondor/anorien/cairandros/arm/goldring.c
 * Lesser ring of Middle-Earth, protection from scrying
 * May also be used in the One Ring quest
 * 
 * Spell code provided by Arman, modified by Varian
 * to alert Morgul Mages when the ring is used.
 *
 * Varian - March, 2020
 */

inherit "/std/armour";
inherit "/d/Genesis/specials/examples/std_magic_lib";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

int turned;
// int charge = 3;

#define NOSCRY   "/d/Gondor/spells/antiscry_spell_effect"
#define MAGES(ob) ob->query_guild_member("Morgul Mages")

void
create_armour()
{
    setuid();
    seteuid(getuid());

    set_name("ring");
    add_name("lesser_ring");
    set_adj("simple");
    add_adj("golden");
    set_short("simple golden ring");
    set_long("This looks like a simple golden ring, but you feel a " +
    	"powerful warmth eminating from it, almost as if it wants " +
        "to twist itself around your finger.\n");

    set_at(A_L_FINGER);
    set_ac(1);

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO,"This is one of the lesser rings of " +
        "Middle Earth. For reference, Gandalf originally thought " +
        "that Bilbo's ring was one of the lesser rings. There is a " +
        "potential plan that a building of the One Ring quest " +
        "could include using lesser rings to potentially be " +
        "discovered as the One Ring, thus initiating the quest. " +
        "This would be one example of those rings. In the meantime, " +
        "this ring will be designed to also attract the attention " +
        "of the most dedicated servants of Sauron, allowing it " +
        "to perhaps be role-played with as a potential One Ring.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"This appears to be a magic ring from the lands of " +
        "Middle Earth. You get the strong feeling that this " +
        "ring could help conceal you from magically prying " +
        "eyes.\n", 30}));

    add_magic_obj_spell("[the] [simple] [golden] 'ring'",
       ({ "twist" }), "/d/Gondor/spells/antiscry_spell_effect.c");

    set_magic_obj_effect(({"_goldring_protect_divination_object_"}));

    set_af(this_object());
}

/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    add_magic_obj_effects(wearer);
    return 0;
} 
/* wear */

/*
 * Function name: remove
 * Description  : This function might be called when someone tries to remove
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
mixed
remove(object obj)
{
    remove_magic_obj_effects(wearer);
    return 0;
} 
/* remove */

public status
verify_magic_obj_spell_cast(string arg, object spell)
{
/*
    if(!charge)
    {
        write("You feel as if the ring is rejecting you.\n");
        return 0;
    }
*/
    if(!this_object()->query_worn())
    {
        write("You would need to be wearing the ring to twist it " +
            "around your finger.\n");
        return 0;
    }

    if(NOSCRY->has_spell_object(E(TO)))
    {
        write("You can already feel the ring twisting tightly " +
            "around your finger!\n");
        return 0;
    }

    if(NOSCRY->query_ability_preparing(E(TO)))
    {
        write("The ring is already starting to tighten as it " +
            "twists around your finger!\n");
        return 0;
    }

    object *players;
    string domain;

    int i;

    if(MAGES(this_player()) || (E(TO)))
    {
    players = users();
    for (i = 0; i < sizeof(players); i++)
    {
        domain = environment(this_player())->query_domain();
        if(MAGES(players[i]))
        players[i]->catch_msg("You feel a strange itch pulling " +
            "you in the direction of " + domain + ".\n");
    }
    } 
    // charge = charge - 1;
    return 1;
}

init()
{
    init_spell_commands();
}

/*
 * Function:    cmd_parse_spell_action
 * Description: Parses actions for spell commands and targets to trigger
 *              spells added to the item.
 * Argument:    string arg - the argument which is parsed
 */
public int
cmd_parse_spell_action(string arg)
{
    int result = ::cmd_parse_spell_action(arg);
    
    if (!result)
        notify_fail("Twist what, the simple golden ring?\n");
        return result;
} 
/* cmd_parse_spell_action */