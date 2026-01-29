#include <cmdparse.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Genesis/gems/gem.h"
#include "/d/Shire/sys/defs.h"
inherit "/lib/keep";
inherit "/std/weapon";
inherit "/d/Shire/common/trollsh/weapon/gem_weapon";

void
create_weapon()
{
// defined in gem_wep.c
    wep_type = "halberd";
    gem_place = "handle";
    wt_type  = W_POLEARM;
    wep_skill = SS_WEP_POLEARM;
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT,  800); 
    add_prop(OBJ_I_VOLUME,  500); 

    set_name(wep_type);
    set_pname(wep_type);
    add_name("_"+ wep_type);
    set_adj(({"corrupted", "mithril"}));
    set_short("corrupted mithril " + wep_type);
    set_pshort("corrupted mithril " + wep_type + "s");

    set_long("This is a " + short() + " and forged ages ago by " +
        "elves in ages past. The head was forged of mithril and " +
        "looks dangerous. The staff is made from a long wooden pole. " +
        "The pole is polished with metal grips. Once a beautiful " +
        "weapon, it has been corrupted by orcs and trolls.@@query_jewel_desc@@\n");

    add_item(({"cryptic runes","runes","rune", "base runes"}),
        "The runes decorate the " + gem_place + " and the blade of the " + 
        short() + ". They are evil looking and seem to shine with a " +
        "dark power.\n");
    add_item(({"mithril","true silver", "silver-steel", 
            "moria-silver","grey-gleam"}),
        "Mithril is the rarest metal in all the world. It is " +
        "lightweight yet durable, retaining its edge against the " +
        "hardest objects.\n");

    add_item(({"head"}),
        "The head is made from mithril and is a convex blade attached to the top of the weapon. The blade curves outward and looks like it can slice through anything. A long spear is set on top of the halberd.\n");
    add_item(({"spear"}),
        "The spear is about an arm's length and sits securely at the top of the " + short() + ". It is hexagonal in shape, wider at the base and narrowing to a deadly point.\n");
    add_item(({"blade"}),
        "The blade is made up of two parts. The larger part is a convex shaped blade attached to the side of the top, just below the spear. The blade is deadly looking, and can problaby slash through almost anything. Opposite the blade is a small tail that flares out and downwards slightly.\n");
    add_item(({"tail"}),
        "The tail is small yet deadly looking. It is connected to the opposite side of the blade. The tail  flares out slightly and downwards. It has three sharp looking points.\n");
    add_item(({"grips"}),
        "They are darkened metal rectangular strips of metal wrapped around the handle. They are designed so the wielder can hold the weapon better. One is at the base of the handle and the other about half way up.\n");
    add_item(({"handle"}),
        "The handle is very long, made from polished wood. It looks sturdy and able to withstand a heavy beating during battles. A spear and a blade top the handle. Two grips are wrapped around the handle.\n");

    set_hit(35);
    set_pen(35);

    set_wt(wt_type);
    set_hands(W_ANYH);
    set_dt(W_SLASH|W_IMPALE);
    set_wf(this_object());

// starting gem
   set_wep_jewel("jade", GEM_SLIGHTLY_RARE);

    add_prop(OBJ_I_WEIGHT,  7500); /* lighter than because it's mithril */
    add_prop(OBJ_I_VOLUME, 20000);
    add_prop(OBJ_I_VALUE ,  1+random(10));
    add_prop(OBJ_M_NO_BUY,     1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,({"The wep is magically enchanted.\n", 5,
       "Dark runes cover the " + gem_place + " of the weapon of Grothaur. " +
       "They pierce your mind, saying that it may be commanded " +
       "or be fortified by it. You may also wipe its blade clean.", 25, 
       "The enchanted weapon has greater hit and penetration than normal " +
       "weapons and has several unique abilities. Failure to wield it " +
       "may result in bodily harm.\n",
       55}));

    add_prop(OBJ_S_WIZINFO, "The weapon is enchanted by use of gems that"   +
       " players must insert into the weapon. When no gems are inserted,"+
       " the wep loses its power and becomes an ordinary wep. To wield"  +
       " the wep, the wielder must have > 100 str, > 100 dis, 60 or"     +
       " better in the wep skill and 20 or better in the spellcraft"     +
       " skill. Since the wep is made of mithril, it is lighter than a"  +
       " standard steel wep, and therefore can be wielded by any race."  +
       " The wep may heal the wielder, but at a cost from the inserted"  +
       " gems. When a player attempts to wield the wep and fails, a"     +
       " portion of their life is taken from them.\n\tInserted gems are" +
       " what gives the wep its power, the rarer the gem group, the"     +
       " longer the power lasts. Also, as the wep is used to heal, this" +
       " takes a portion of the power from the wep. When the power is"   +
       " used up, the gem crumbles and the wep becomes 'normal' with no" +
       " powers. The wielder must insert a new gem to into the weapon"   +
       " to recharge it. Inserted gems cannot be removed.\n");
}

void
init()
{
    ::init();

    add_action(action_wep_fortify,  "fortify");
    add_action(action_wep_impress,  "impress");
    add_action(action_wep_insert ,  "insert");
    add_action(action_wep_wipe,     "wipe");
    add_action(action_gem_pry ,     "pry");
}

string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}


public mixed
wield(object wep)
{
    if (sizeof(TP->query_weapon(-1)) == 2)
    {
        if (MASTER_OB(TP->query_weapon(-1)[0]) == "/d/Shire/common/trollsh/weapon/gem_" + wep_type && MASTER_OB(TP->query_weapon(-1)[1]) == "/d/Shire/common/trollsh/weapon/gem_" + wep_type)

            return "You can only wield one of these at a time.\n";
    }
    return 0;
}
