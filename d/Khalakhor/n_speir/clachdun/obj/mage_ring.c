/*
 * A mage's ring by Igneous
 *
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include "local.h"

inherit "/lib/wearable_item";
inherit "/lib/keep";
inherit "/d/Khalakhor/std/object";

#define RING_ARMOUR ARM_DIR + "ring_arm"

// Prototypes
string read_words();

void
create_khalakhor_object()
{
    set_name("ring");
    set_short("ornate jeweled ring");
    set_adj(({"ornate", "golden", "jeweled"}));
    set_long("This "+short()+" is a delicate and precious item, which "+
      "looks to be centuries old.  Set within the golden band of the ring "+
      "are three strange jewels, of a type that you have never seen before.  "+
      "Incribed in the band are some unknown words written in a strange "+
      "wispy language.\n");
    add_item(({"jewels", "three jewels", "jewel"}), "Embeded into the "+
      "golden band of the short three jewels sparkle and shine.\n");
    add_item("first jewel", "The first jewel is coloured a cloudly purple "+
      "and is extremely jagged and misshapened.\n");
    add_item("second jewel", "The second jewel is colourless and formed into "+
      "a prefect oval shape.\n");
    add_item("third jewel", "The third jewel is coloured a brilliant sky "+
      "blue and its shape seems to be a perfect medium of the other two "+
      "jewels.\n");

    add_item(({"words", "unknown words", "wispy words"}), read_words);

    set_slots(A_ANY_FINGER);
    set_wf(this_object());
    set_layers(0);
    set_looseness(0);

    set_keep(1);

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment"}));

    add_prop(OBJ_I_WEIGHT, 50 + random(101));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 10);
    add_prop(OBJ_I_VALUE, 10000 + random(5000));
}

string
read_words()
{
    switch(this_player()->query_skill(SS_LANGUAGE))
    {
    case 0..60:
	return "The words are strange and beyond your comprehension.\n";
    case 61..80:
	return "All you are able to make out is one word 'Protector'.\n";
    default:
	return "The words say 'I am your Protector, from all things "+
	"evil, good and of balance.'\n";
    }
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public mixed
wear(object arm)
{
    object mag_arm;

    if (this_player()->query_guild_style_occ() == "fighter" ||
      this_player()->query_guild_style_occ() == "thief")
    {
	return "The "+short()+" resists your attempt to wear it.\n";
    }
    setuid(); seteuid(getuid());
    mag_arm = clone_object(RING_ARMOUR);
    mag_arm->move(this_player(), 1);
    mag_arm->wear_me();
    return 0;
}

public mixed
remove(object arm)
{
    object mag_arm;

    if (objectp(mag_arm = present("_Khalakhor_mage_ring_armour",query_worn())))
    {
	mag_arm->remove_me();
	mag_arm->remove_object();
    }
    return 0;
}

/* Function name: appraise_object (MASK)
 * Description  : Appraise the object.
 * Arguments    : int num - The appraise number, randomized.
 * Returns      : n/a
 */

public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}
