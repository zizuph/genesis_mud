/* file name:    /d/Avenir/common/holm/t_camp/obj/wiz_robe.c
*  creator(s):   (Rangorn , Feb 97)
*  revisions:    Lilith Oct/Nov 97
*  purpose:      A magic robe that resists fire.
*/
inherit "/d/Avenir/inherit/cloth_arm";
inherit "/lib/keep";

#include "../holm.h";
#include <wa_types.h>
#include <formulas.h>

void
create_armour()
{
    if (!IS_CLONE)
        return;

    set_name("robe");
    set_adj("flowing");
    add_adj(({"ermine", "scarlet", "white"}));
    set_short("flowing ermine-lined robe");
    set_long("A flowing robe made of silken webcloth. It is the "+
        "ultimate in luxury, being expertly tailored for the most "+
        "discerning of clients, magic users. Lined with ermine "+
        "to add warmth, it is surprisingly lightweight. A white "+
        "pattern swirls restlessly within the folds of the scarlet "+
        "cloth. Occasionally the two colors collapse into each "+
        "other and form a new pattern.\n");
   add_item(({"lining", "ermine"}), "It is the siler-white fur of "+
        "ermine trapped in Terel's Silver Forest.\n");
   add_item(({"pattern", "scarlet", "red", "white"}),
       "The white patterns swirl with great energy, as "+
       "though trying to break free of entrapment.\n");

    set_ac(35);      // It is webcloth
    set_at(A_ROBE);
    set_af(TO);

    add_prop(OBJ_I_WEIGHT, 1000 + random(600));
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(40) + random (200));

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }));
    add_prop(MAGIC_I_RES_FIRE, 40);
    add_prop(MAGIC_I_RES_MAGIC, 20);
    add_prop(OBJ_S_WIZINFO, "This robe makes wearer resistant " +
            "to fire spells (RES: 40) and magic (RES: 20).\n");

    add_prop(MAGIC_AM_ID_INFO,
          ({ "A sibiliant voice whispers in your ear:\n"+
             "   Fear is a self-perpetuated illusion\n"+
             "   Over which Hahabi rules, Lord of the Third Hour.\n", 10,
             "   Flame is Hahabi's tool, Flame his gift\n"+
             "   To those with courage to wear this robe.\n", 20,
             "   Fire resists Fire. Magic resists Magic.\n", 40 }));
}

int
wear(object ob)
{
    if (DIS(TP) > (90 + random(30)))
    {
        TP->catch_msg("Upon wearing the robe you feel a sudden shock, as "+
            "if someone had jabbed you in the ribs with a red-hot poker.\n");
        say(QCTNAME(TP) + " suddenly jerks as " + TP->query_pronoun() +
            " wears " + TP->query_possessive() +" "+ short() +".\n");
        TP->add_magic_effect(this_object());
        return 1;
    }
    return -1;
}

int
remove(object ob)
{
    object tp = query_worn();
    tp->remove_magic_effect(this_object());
    return 0;
}

void
leave_env(object to,object from)
{
    ::leave_env(to,from);

    if (!living(from))
        return;
    from->remove_magic_effect(TO);
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (protectee == query_worn())
    {
        if (prop == MAGIC_I_RES_FIRE)
        {
            protectee->catch_msg("The patterns on your "+ short()+" suddenly "+
                "coalesce into flickering flames, then equally as suddenly, " +
                "subside into a random swirling pattern.\n");
            tell_room(environment(this_object()), "The patterns on the "+ short()+
                " that " +QCTNAME(protectee)+ " is wearing suddenly coalesce " +
                "into flickering flames, then subside into a new pattern.\n",
                protectee);
	    return ({ 40, 1});
        }
        if (prop == MAGIC_I_RES_MAGIC)
        {
            protectee->catch_msg("The patterns on your "+ short() +" suddenly "+
                "collapse into each other and you can almost feel the " +
                "powers of the robe trying to break free.\n");
            tell_room(environment(this_object()), "The patterns on the "+
                short()+" that " +QCTNAME(protectee)+ " is wearing " +
                "suddenly collapse into each other and then form a new "+
                "pattern.\n", protectee);
	    return ({ 20, 1});
        }

    }
}
