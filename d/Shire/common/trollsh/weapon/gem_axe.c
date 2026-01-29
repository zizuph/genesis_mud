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
    wep_type = "axe";
    gem_place = "handle";
    set_hands(W_ANYH);
    wt_type  = W_AXE;
    wep_skill = SS_WEP_AXE;
    
    set_name(wep_type);
    set_pname(wep_type);
    add_name("_"+ wep_type);
    set_adj(({"corrupted", "mithril"}));
    set_short("corrupted mithril " + wep_type);
    set_pshort("corrupted mithril " + wep_type + "s");

    set_long("This is a " + short() + ", once forged by the elves " +
        "ages ago. It was used in countless wars against the Dark One, " +
        "but was stolen during one of their battles. The Dark One took " +
        "the axe and twisted it to his own designs and now it is " +
        "corrupted and full of evil powers. Dark and evil runes cover " +
        "the once fair axe.@@query_jewel_desc@@\n");

    add_item(({"runes", "dark runes", "dark and evil runes", "evil runes"}),
        "The runes look like they were once fair, inscribed by elven " +
        "hands. Now they have been corrupted and twisted by fell beings. " +
        "They glow with an evil presence.\n");
    add_item(({"axe head", "head of axe", "head of the axe"}),
        "The head of the axe is made of two mithril blades that " +
        "are half oval in shape and magically attached to the " +
        "blade. The edges of the blades are razor sharp and look " +
        "like they can easily cut through anything. Cryptic runes " +
        "decorate the head of the axe.\n");
    add_item(({"axe handle", "handle"}),
        "The axe handle is made of mithril, round and very smooth. " +
        "At the top of the handle is attached the head of the axe. " +
        "The base of the handle is wrapped in leather to give the " +
        "wielder a better grip on the handle.@@query_jewel_desc@@\n");
    add_item(({"leather on axe handle", "axe handle leather"}),
        "The leather is from some beast. It is brown and wrapped " +
        "around the base of the axe handle, to help the user get " +
        "a better grip on the handle.\n");
    add_item(({"mithril","true silver", "silver-steel", 
            "moria-silver","grey-gleam"}),
        "Mithril is the rarest metal in all the world. It is " +
        "lightweight yet durable, retaining its edge against the " +
        "hardest objects.\n");


    set_hit(35);
    set_pen(35);

    set_wt(wt_type);
    set_hands(W_ANYH);
    set_dt(W_SLASH|W_IMPALE);
    set_wf(this_object());

// starting gem
   set_wep_jewel("jade", GEM_SLIGHTLY_RARE);

    add_prop(OBJ_I_WEIGHT,  800); /* lighter than because it's mithril */
    add_prop(OBJ_I_VOLUME, 200);
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

//    add_action(action_wep_fortify,  "fortify");
//    add_action(action_wep_impress,  "impress");
    add_action(action_wep_insert ,  "insert");
//    add_action(action_wep_wipe,     "wipe");
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
//    if (sizeof(TP->query_weapon(-1)) == 2)
//    {
//        if (MASTER_OB(TP->query_weapon(-1)[0]) == "/d/Shire/common/trollsh/weapon/gem_" + wep_type && MASTER_OB(TP->query_weapon(-1)[1]) == "/d/Shire/common/trollsh/weapon/gem_" + wep_type)
//
//            return "You can only wield one of these at a time.\n";
//    }
    return 0;
}
