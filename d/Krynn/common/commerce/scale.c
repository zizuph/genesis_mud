/*
 * Made by Boron in July 2002, so Knights could bring it to the
 * black smith Chert and get it made into a cool body armour
 * (a modified platemail)
 */
inherit "/std/armour";
inherit "/d/Genesis/lib/commodity";

inherit "/lib/keep";
#include <wa_types.h>
#include <formulas.h>

public void
create_armour()
{
    set_name("scale");
    set_pname("scales");
    add_name(({"armour", "shield"}));
    add_pname(({"armours", "shields"}));
    set_adj("dragon");
    add_adj(({"bloody"}));
    set_short("dragon scale");
    set_pshort("dragon scales");
    set_ac(25 + (random(2)));
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_long("This triangular, solid scale has been removed from the " +
      "breast of a grown krynnish dragon. It is unnaturally hard " +
      "though weights little, and light reflects easily from its " +
      "glossy surface. In the Age of Dreams, dragon scales were a " +
      "common trading commodity. Today however, when the evil dragons rule " +
      "the skies and the good ones remain lost or dead, obtaining " +
      "such a scale is risky to the extreme... As no child of Takhisis " +
      "would part with his magical armour willingly. A large dragon " +
      "scale, similarly to an Ankheg's shell, can be used as a natural " +
      "shield or reforged into magical armour.\n");

    set_commodity_name ("scale"); // required to link this
                                  // object with the domain server
    set_commodity_value(300);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO,"This shield is made from the scales of a " +
             "dragon. A Krynnian dragon is magical, thus transferring it " +
             "to this armour. The magic of the dragon provides " +
             "resistance against LIGHT and FIRE. This is not default in " +
             "this armour, but it can be transfered to other armours, by " +
             "the commerce system. Ie. This is an ingredient for a smith " +
             "to make a nice protective armour.\n");
    add_prop(MAGIC_AM_ID_INFO,
             ({"This shield is made from the scales of a Krynnian dragon. " +
                 "A Krynnian dragon is magical and so is this shield.\n", 20,
                 "This shield offers no protection as it is now.\n", 50,
                 "There is a potential  protection from this armour against " +
                 "natural threats",50,
                 " such as fires and lightning.\n", 70}));
    add_prop(MAGIC_AM_MAGIC,({100, "enchantment"}));
    add_prop(MAGIC_AM_MAGIC,({100, "enchantment"}));


    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25) );

}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}
