/*
 *  Updates:
 *       Zizuph, 2021-12-25:
 *         Turn into a spell enhancer, power 40.
*/

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

inherit "/lib/keep";
#include <const.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"

/* Global variable */
static int alarm_id = 0;
static int weight_id = 0;

public void
create_object()
{
    set_name("orb");
    add_name("_WoHS_sacrificial_black_orb");
    set_adj("midnight-black");
    add_adj("black");
    set_short("midnight-black orb");

    set_long("This is a strange midnight-black orb of a size that would fit " +
       "well in your hand. Smooth and very cold to the touch, it is crafted " +
       "from a mineral you are not familiar with... in fact it looks like it " +
       "comes from somewhere beyond this world!\n");
 
    add_prop(OBJ_I_WEIGHT, 235);
    add_prop(OBJ_I_VOLUME, 79);
    add_prop(OBJ_I_VALUE, 3 * 12 * 12 * 12);

/* Important to keep the arguments in the correct order
 * or the magic system will bail out trying to identify it.
 *
 * // Stralle
 */
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO, ({
	"There is something magical about the midnight-black orb.\n", 1,
	"It is an ancient relic crafted from a fallen piece of the black " +
        "moon by worshippers of the Devouring Dark, Nuitari.\n", 30,
        "When held by those skilled in the Dark Arts, the " +
        "orb absorbs light surrounding it.\n", 40 }) );

    add_prop(OBJ_S_WIZINFO, "This magic orb is an artifact of the dark god " +
        "of magic, Nuitari. When held by a player with spellcraft skill greater " +
        "than 80 and alignment less than -200 the orb has the property " +
        "OBJ_I_LIGHT set to DARKNESS_HELD.\n");

    set_spellpower_elements(({
        SS_ELEMENT_DEATH, SS_ELEMENT_AIR, SS_ELEMENT_WATER,
        SS_ELEMENT_FIRE, SS_ELEMENT_EARTH
    }));
 
    set_slots(W_ANYH);

    will_not_recover = (random(100) < PERCENTAGE_OF_RECOVERY_LOST);

    //Enable default item expiration
    set_item_expiration();
}

void
effect_on(object player)
{
    if (objectp(player))
    {
    tell_object(player, "The midnight-black orb begins to vibrate in your hand " +
         "as darkness engulfs you!\n");
    if (environment(player))
    {
        tell_room(environment(player), "Darkness suddenly engulfs you!\n",
          player);
    }
    }
    add_prop(OBJ_I_LIGHT, DARKNESS_HELD);

    set_magic_spellpower(40);
    alarm_id = 1;
}
 

 
void
effect_off(object player)
{
    if (objectp(player))
    {
    tell_object(player, "The darkness disappears as you release the midnight-"+
         "black orb.\n");
    if (environment(player))
    {
        tell_room(environment(player),"The darkness surrounding you disperses, " +
          "melting into the ground around you.\n",
          player);
    }
    }
    add_prop(OBJ_I_LIGHT, 0);

    set_magic_spellpower(0);
    alarm_id = 0;
}

void
weight_up(object player)
{
    if (objectp(player))
    {
    tell_object(player, "The midnight-black orb suddenly feels very heavy!\n");
    }

    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_I_WEIGHT, 23500);
 
    set_magic_spellpower(0);
    weight_id = 1;
}
 

 
void
weight_down(object player)
{
    if (objectp(player))
    {
    tell_object(player, "You feel less burdened as you release the midnight-"+
         "black orb.\n");
    }

    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_I_WEIGHT, 235);
 
    set_magic_spellpower(0);
    weight_id = 0;
}


public mixed
hold()
{
    if((TP->query_alignment() < -200) && (TP->query_skill(SS_SPELLCRAFT) > 80))
      set_alarm(0.5,0.0,&effect_on(this_player()));

    if(TP->query_alignment() > 400)
      set_alarm(0.5,0.0,&weight_up(this_player()));      
 
    return 0;
}

public mixed
release()
{
    if(alarm_id)
      set_alarm(0.5,0.0,&effect_off(this_player()));  

    if(weight_id)
      set_alarm(0.5,0.0,&weight_down(this_player()));

    return 0;
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    holdable_item_leave_env(env, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_holdable_item();
    write(item_spellpower_desc());
}

string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
}
 
void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    ::init_keep_recover(arg);
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
