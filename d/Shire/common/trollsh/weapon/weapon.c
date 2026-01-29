#include <cmdparse.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Genesis/gems/gem.h"
#include "/d/Shire/sys/defs.h"

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Shire/common/trollsh/weapon/gem_weapon";

 void setup_weapon();

// determines what weapon to make
int wep_num;

 


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}



string long_desc() 
{

    string str;

    switch (wep_num)
    {
        case 0:     // axe
            str = "This is a " + short() + ", once forged by the elves " +
            "ages ago. It was used in countless wars against the Dark One, " +
            "but was stolen during one of their battles. The Dark One took " +
            "the axe and twisted it to his own designs and now it is " +
            "corrupted and full of evil powers. Dark and evil runes cover " +
            "the once fair axe" + query_jewel_desc() + "\n";
        break;

        case 1:     // sword
            str  = "This is a " + short() + " and forged ages ago by " +
            "elves. It is forged of mithril and very light and " +
            "perfectly balanced. The blade is double edged, with a ridge " +
            "running from the grip towards the tip. Graceful elvish runes " +
            "once decorated the blade. They have been fouled by evil " +
            "and are now cryptic looking." + query_jewel_desc() + "\n";
        break;

        case 2:     // halberd
            str = "This is a " + short() + " and forged ages ago by " +
            "elves in ages past. The head was forged of mithril and " +
            "looks dangerous. The staff is made from a long wooden pole. " +
            "The pole is polished with metal grips. Once a beautiful " +
            "weapon, it has been corrupted by orcs and trolls."+
            query_jewel_desc() + "\n";
        break;

        case 3:     // club
            str = "This is a "+ short() + ". It was forged by dwarves " +
            "ages ago and looks deadly. A spiked steel ball hangs from " +
            "a long chain, which is attached to a heavy wooden pole. It " +
            "is a dangerous looking weapon, which has become more so since " +
            "it was stolen from Khazad-dum and twisted by the hands of " +
            "trolls." + query_jewel_desc() + "\n";
        break;
    }	
  return str;

}

void setup_weapon()
{
    switch (wep_num)
    {
        case 0:     // axe
            wep_type = "axe";
            gem_place = "handle";
            set_hands(W_ANYH);
            wt_type  = W_AXE;
            wep_skill = SS_WEP_AXE;
            set_dt(W_SLASH | W_IMPALE);
            add_prop(OBJ_I_WEIGHT, 800); /* lighter than because it's mithril */
            add_prop(OBJ_I_VOLUME, 200);

        break;

        case 1:     // sword
            wep_type = "sword";
            gem_place = "handle";
            set_hands(W_ANYH);
            wt_type  = W_SWORD;
            wep_skill = SS_WEP_SWORD;
            set_dt(W_SLASH | W_IMPALE);
            add_prop(OBJ_I_WEIGHT,  800);
            add_prop(OBJ_I_VOLUME,  200);

            add_item(({"cryptic runes","runes","rune", "base runes"}),
                "The runes decorate the " + gem_place + " and the blade " +
                "of the " + short() + ". They are evil looking and seem " +
                "to shine with a dark power.\n");
            add_item(({"blade"}),
                "The blade is made of mithril and very light. A ridge " +
                "runs down the middle of the blade, strengthening it. " +
                "Cryptic runes run up the blade on either side of the " +
                "ridge.\n");
            add_item(({"ridge"}),
                "The ridge runs up the blade, strengthening it without " +
                "making the blade any heavier. Runes run along both " +
                "sides of it.\n");
            add_item(({"handle"}),
                "The handle connects to the blade and is wrapped with " +
                "dark leather. It is large enough so that the blade can " +
                "be wielded by one hand." + query_jewel_desc() + "\n");
            add_item(({"leather", "dark leather"}),
                "The dark leather is made from some unknown animal. It is " +
                "polished smooth from countless hands which have wielded " +
                "the blade yet appears as new as the day it was wrapped " +
                "around the grip.\n");
        break;

        case 2:     // halberd
            wep_type = "halberd";
            gem_place = "handle";
            wt_type  = W_POLEARM;
            wep_skill = SS_WEP_POLEARM;
            set_dt(W_SLASH | W_IMPALE);
            set_hands(W_BOTH);
            add_prop(OBJ_I_WEIGHT,  800); 
            add_prop(OBJ_I_VOLUME,  500); 
            add_item(({"head"}),
                "The head is made from mithril and is a convex blade that has been attached to the top of the weapon. The blade curves outward, and looks like it can slice through anything. A long spear is set on top of the halberd.\n");
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
        break;

        case 3:     // club
            wep_type = "flail";
            gem_place = "handle";
            set_dt(W_SLASH | W_BLUDGEON);
            wt_type  = W_CLUB;
            wep_skill = SS_WEP_CLUB;
            set_hands(W_ANYH);
            add_prop(OBJ_I_WEIGHT,  800); 
            add_prop(OBJ_I_VOLUME,  400);
            add_name("double ball flail");
            add_name("club");

            add_item(({"ball", "spiked balls", "spiked ball", "balls"}),
                "The balls are the size of a fist, smooth, and made from mithril. Nasty looking spikes protrude from all over the balls, making them look deadly. Separate chains are connected to the ends of both balls, and are attached to a wide ring. The ring is fastened to the end of the handle.\n");
            add_item(({"chain", "chains"}),
                "They are two chains made from links of mithril. They are connected to each ball seperately and to a ring at the top of the handle.\n");
            add_item(({"handle"}),
                "The handle is made of wood and long. Each end of the handle is capped with metal to give it strength. The top of the handle has a large ring with two chains connected to it.\n");
            add_item(({"ring"}),
                "The ring is large and connects to the top of the handle. It allows the balls to swing independent of each other, making the weapon more deadly.\n");
            add_item(({"metal caps", "metal cap"}),
                "The metal caps are small and made of mithril. They are attached to both ends of the handle.\n");
            
        break;
    }
}

public mixed
wield(object what)
{
    int heal;

// Grothaur wields weapon without any problems.
    if (TP->query_real_name() == "grothaur")
        return 0;
   
    if (sizeof(TP->query_weapon(-1)) == 2)
    {
        if (MASTER_OB(TP->query_weapon(-1)[0]) == "/d/Shire/common/trollsh/weapon/weapon" && MASTER_OB(TP->query_weapon(-1)[1]) == "/d/Shire/common/trollsh/weapon/weapon")

            return "You can only wield one corrupted mithril weapon at a time.\n";
    }   

    /* we will stop newbies to try to wield it */
    if (this_player()->query_base_stat(SS_STR) < 35)
    {
       write("You try to lift the " + short() + " enough to wield it, " + 
        "but fail!\n");
       say(QCTNAME(this_player()) + " tries to lift the " + short() +
             " high enough to wield it, but fails!\n");

       return "The " + short() + " is too heavy!\n";
    }


    if (!query_wep_jewel() || (query_wep_points() <= 0))
       return 0;
    
//    if ((this_player()->query_race_name() != "elf")      &&
       if((this_player()->query_skill(wep_skill) > 59)    &&
        (this_player()->query_skill(SS_SPELLCRAFT) > 19) &&
        (this_player()->resolve_task(TASK_DIFFICULT,({TS_STR,TS_DIS}))>0))
    {
        write("Straining your entire body and mind to the limit, you " +
              "barely manage to gain control of the " + short() + 
              ". A presence from within it seems to have accepted you " +
              "as its new owner.\n");
        say(QCTNAME(this_player()) + " breaks out into a sweat as " +
              this_player()->query_pronoun() + " attempts to gain " +
              "control of the " + short() + ".\n");
    
        set_alarm(10.0, 0.0, &notify_wield(this_player()));
        return 0;
    }

    write("You strain with all your might but are simply not able to " +
        "wield the " + short() + ". An unholy power curses you!\n");
    say("A portion of " + QCTNAME(this_player()) + "'s life-force is" +   
          " drained by the " + short() + "!\n");

    heal = (query_wep_drain() * query_max_points() / 10);

    this_player()->heal_hp(-heal);
    add_wep_points(heal);

    if (this_player()->query_hp() <= 0)
       this_player()->do_die(this_object());
//               this_player()->heal_hp(5);

    return "A portion of your life-force was drained by the " + short() + 
        ", leaving you on the brink of death!\n";
}

/******************************************************************************
 *****************************************************************************/

void
create_weapon()
{

    wep_num = random(4);
    setup_weapon();

    set_name(wep_type);
    set_pname(wep_type);
    add_name("_"+ wep_type);
    set_adj(({"corrupted", "mithril"}));
    set_short("corrupted mithril " + wep_type);
//    set_pshort("corrupted mithril " + wep_type+);
/*
    set_long("This is a " + short() + " and forged ages ago by elves " +
        "of Lindon. It is forged of mithril and very light and perfectly " +
        "balanced. The blade is double edge, with a ridge running " +
        "from the grip towards the tip. Graceful elvish runes once " +
        "decorated the blade. They have been fouled by evil and are " +
        "now cryptic looking." + query_jewel_desc() + "\n");
*/
    set_long("@@long_desc");

    add_item(({"mithril","true silver", "silver-steel", 
            "moria-silver","grey-gleam"}),
        "Mithril is the rarest metal in all the world. It is " +
        "lightweight yet durable, retaining its edge against the " +
        "hardest objects.\n");

    set_hit(35);
    set_pen(35);

    set_wt(wt_type);
    set_wf(this_object());

// starting gem
   set_wep_jewel("jade", GEM_SLIGHTLY_RARE);

    add_prop(OBJ_I_VALUE ,  1+random(10));
    add_prop(OBJ_M_NO_BUY,     1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,({"The weapon is magically enchanted.\n", 5,
       "A dark presence emanates from the weapon. It's evil power seems " +
       "to call to you", 25, "The enchanted weapon has greater hit and " +
       "penetration than normal weapons.\n",
       55}));

    add_prop(OBJ_S_WIZINFO, "The weapon is enchanted by use of gems that " +
        "players must insert into the weapon. When no gems are inserted, " +
        "the weapon loses its power and becomes an ordinary weapon. To " +
        "wield the weapon, the wielder must have > 100 str, > 100 dis, " +
        "60 or better in the wep skill and 20 or better in the spellcraft " +
        "skill. Since the weapon is made primarily of mithril, it is " +
        "lighter than a standard steel weapon.\n\n" + 
        "Inserted gems are what gives the weapon its power, the rarer the " +
        "gem group, the longer the power lasts. When the power is used " +
        "up, the gem crumbles and the weapon becomes 'normal' with no " +
        "powers. The wielder must insert a new gem to into the weapon to " +
        "recharge it. Inserted gems cannot be removed without destroying " +
        "them.\n");
    set_keep(1);
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
