/* Kender Mask for Kender Questby Gwyneth, August 1999 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

int see_invis = 0;

void
create_armour()
{
    set_name(({"mask", "_kender_quest_mask_"}));
    set_adj("sparkly");
    add_adj("red");
    set_short("sparkly red mask");
    set_long("Wow! A sparkly red mask! You can detect a small glow " + 
        "around the eyeholes.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 120);
    add_prop(OBJ_M_NO_GIVE, "The only person you should give this mask " + 
        "to is Merldon. You can 'return mask'.\n");
    add_prop(OBJ_M_NO_DROP, "The only person you should give this mask " + 
        "to is Merldon. You can 'return mask'.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "This mask was enchanted by a wizard who " + 
        "had it borrowed by the kender Merldon. Merldon gives it to " + 
        "questers in order to see the magic portal which is invisible.\n");
    add_prop(MAGIC_AM_ID_INFO, ({ "This mask has been enchanted.\n", 20,
        "The mask was enchanted by a wizard to be able to see invisible " + 
        "portals.\n", 40}));
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    set_at(A_HEAD);
    set_ac(0);
    set_af(TO);
}

void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);
    if (!interactive(inv))
    {
        set_alarm(1.0,0.0,&tell_room(E(TO),"The sparkly red mask suddenly " + 
            "bursts into flames.\n"));
        set_alarm(1.1,0.0,&remove_object());
    }
}

void
init()
{
    ::init();
    add_action("return_mask", "return");
}

int
return_mask(string str)
{
    object kender_merldon, who;
    string name, kname;
    who = E(TO);
    name = who->query_real_name();
    kender_merldon = find_living("merldon");
    kname = kender_merldon->query_real_name();
    if ((str == "mask") || (str == "mask to merldon") ||
      (str == "mask to Merldon"))
    {
       if (present(kender_merldon, E(who)))
       {
           remove_prop(OBJ_M_NO_GIVE);
           remove_prop(OBJ_M_NO_DROP);
           who->command("give mask to merldon");
           return 1;
       }
       else
       {
           NF("Merldon isn't here to return the mask to!\n");
           return 0;
       }
    }
    NF("Return what?\n");
}

/* Function name : Wear
 * Description : Gives an emote to room and wearer when worn.
 * Returns : 1 or 0
*/

mixed
wear(object what)
{
    if (what != TO)
       return 0;

    write("You tie the red sparkly mask around your head, adjusting " + 
        "the eyeholes so you can see out of them easily. Your eyes " + 
        "start to tingle slightly.\n");
    say(QCTNAME(TP) + " ties the red sparkly mask around " + HIS(TP) + 
        " head.\n");
    if (!TP->query_prop(LIVE_I_SEE_INVIS))
    {
        TP->add_prop(LIVE_I_SEE_INVIS, 1);
        see_invis = 1;
    }
    return 1;
}

/* Function name : Remove
 * Description : Gives an emote to room and wearer when item is removed.
 * Returns : 1 or 0
*/

mixed
remove(object what)
{
    if (what != TO || !TP)
      return 0;

    write("You untie the red sparkly mask from around your head. You " + 
        "blink slightly as the world seems to become dimmer.\n");
    say(QCTNAME(TP) + " unties the red sparkly mask from around " + HIS(TP) + 
        " head. " + C(HE(TP)) + " blinks slightly.\n");
    if (see_invis)
    {
        TP->remove_prop(LIVE_I_SEE_INVIS);
        see_invis = 0;
    }
    return 1;
}
int
query_recover()
{
    return 0;
}

